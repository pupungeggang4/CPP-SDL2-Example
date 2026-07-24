#include <iostream>
#include <fstream>
#include <string>
#include <emscripten.h>

// 데이터와 비즈니스 로직을 담은 독립된 클래스 (전역 변수 없음)
class AppContext {
private:
    int num = 0;
    const std::string path = "/persistent/user_data.txt";

    void save_idbfs() {
        std::cout << "[C++] 가상 RAM -> 브라우저 디스크 동기화 시작..." << std::endl;
        EM_ASM({
            FS.syncfs(false, function (err) {
                if (err) console.error("[JS] 영구 저장 실패:", err);
                else console.log("[JS] 브라우저 디스크 영구 저장 완료!");
            });
        });
    }

public:
    void run_file_operations() {
        // [단계 2] 기존 파일 읽기 시도
        std::ifstream inFile(path);
        if (inFile.is_open()) {
            std::cout << "[C++] 기존에 저장된 데이터 읽기 성공:" << std::endl;
            inFile >> num;
            inFile.close();
        } else {
            std::cout << "[C++] 저장된 데이터가 없습니다. 새로 만듭니다." << std::endl;
            num = 0;
        }

        std::cout << "현재 인스턴스의 값: " << num << std::endl;
        num += 1;

        // [단계 3] 데이터 새로 쓰기
        std::ofstream outFile(path);
        if (outFile.is_open()) {
            outFile << num;
            outFile.close();
            std::cout << "[C++] 파일 쓰기 완료. 다음 값: " << num << std::endl;
        }

        // [단계 4] 영구 저장 호출
        save_idbfs();
    }
};

// ⭐️ JavaScript와 통신하는 C 스타일 인터페이스 인터페이스
extern "C" {
    // 마운트 완료 시 자바스크립트가 호출할 함수
    // C++ 객체의 메모리 주소(포인터)를 정수값(uintptr_t)으로 안전하게 전달받습니다.
    EMSCRIPTEN_KEEPALIVE
    void run_business_logic(uintptr_t context_ptr) {
        if (context_ptr == 0) return;
        
        // 정수형 주소 값을 다시 원본 C++ 객체 포인터로 복원(Type Casting)합니다.
        AppContext* app = reinterpret_cast<AppContext*>(context_ptr);
        
        // 특정 인스턴스의 비즈니스 로직을 안전하게 실행합니다.
        app->run_file_operations();
        
        // 힙(Heap) 메모리에 할당했던 객체를 안전하게 해제하여 메모리 누수를 방지합니다.
        delete app; 
    }
}

// IDBFS를 마운트하고, 현재 동적으로 생성된 인스턴스 주소를 보존합니다.
void mount_idbfs(AppContext* app_instance) {
    std::cout << "[C++] IDBFS 가상 디렉토리 생성 및 마운트 시작..." << std::endl;
    
    // 포인터(메모리 주소)를 EM_ASM 내부의 자바스크립트 변수로 넘겨줍니다.
    EM_ASM({
        if (!FS.analyzePath('/persistent').exists) {
            FS.mkdir('/persistent');
        }
        FS.mount(IDBFS, {}, '/persistent');
        
        // C++에서 넘겨받은 메모리 주소를 자바스크립트 변수로 캡처합니다.
        // $0은 EM_ASM의 첫 번째 인자(app_instance)를 의미합니다.
        const appPtr = $0; 
        
        FS.syncfs(true, function (err) {
            if (err) {
                console.error("[JS] 초기 로딩 실패:", err);
            } else {
                console.log("[JS] 브라우저 디스크로부터 이전 데이터 로드 완료!");
                // ⭐️ 보존해둔 C++ 인스턴스 주소를 인자로 넘겨주며 원격 호출합니다.
                _run_business_logic(appPtr); 
            }
        });
    }, app_instance);
}

int main() {
    // 1. 전역 변수를 쓰지 않기 위해 C++ 힙(Heap) 메모리에 인스턴스를 동적 생성합니다.
    AppContext* app = new AppContext();
    
    // 2. 생성한 인스턴스의 주소를 마운트 함수로 전달합니다.
    mount_idbfs(app);
    
    // main 함수는 즉시 종료되고, 메모리는 비동기 작업이 완전히 끝날 때까지 힙에 유지됩니다.
    return 0;
}
