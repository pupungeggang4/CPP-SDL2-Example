#include <iostream>
#include <fstream>
#include <string>
#include <emscripten.h>

class AppContext {
public:
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

    void run_file_operations() {
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

        std::ofstream outFile(path);
        if (outFile.is_open()) {
            outFile << num;
            outFile.close();
            std::cout << "[C++] 파일 쓰기 완료. 다음 값: " << num << std::endl;
        }

        save_idbfs();
    }
};

extern "C" {
    EMSCRIPTEN_KEEPALIVE
    void run_business_logic(uintptr_t context_ptr) {
        if (context_ptr == 0) return;
        AppContext* app = reinterpret_cast<AppContext*>(context_ptr);
        app->run_file_operations();
        delete app;
    }
}

void mount_idbfs(AppContext* app_instance) {
    std::cout << "[C++] IDBFS 가상 디렉토리 생성 및 마운트 시작..." << std::endl;
    
    EM_ASM({
        if (!FS.analyzePath('/persistent').exists) {
            FS.mkdir('/persistent');
        }
        FS.mount(IDBFS, {}, '/persistent');
        const appPtr = $0; 
        FS.syncfs(true, function (err) {
            if (err) {
                console.error("[JS] 초기 로딩 실패:", err);
            } else {
                console.log("[JS] 브라우저 디스크로부터 이전 데이터 로드 완료!");
                _run_business_logic(appPtr); 
            }
        });
    }, app_instance);
}

int main() {
    // 1. 전역 변수를 쓰지 않기 위해 C++ 힙(Heap) 메모리에 인스턴스를 동적 생성합니다.
    AppContext* app = new AppContext();
    mount_idbfs(app);
    return 0;
}
