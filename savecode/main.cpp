#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <string>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
bool isRunning = false;
bool isSaving = false;
std::ifstream ifs;
std::ofstream ofs;
std::string path;
int num = 0;

SDL_Window* window = nullptr;

void run();
void loop();

#ifdef __EMSCRIPTEN__
extern "C" {
    EMSCRIPTEN_KEEPALIVE
    void emDataLoaded() {
        std::cout << "[C++] IndexedDB 동기화 완료. 파일 읽기를 시도합니다." << std::endl;
        
        ifs.open("/save/save.txt");
        if (ifs.is_open()) {
            ifs >> num;
            ifs.close();
            std::cout << "[C++] 불러온 세이브 데이터 숫자: " << num << std::endl;
        } else {
            std::cout << "[C++] 기존 세이브 파일이 없습니다. 0부터 시작합니다." << std::endl;
            num = 0;
        }
        
        run();
    }

    EMSCRIPTEN_KEEPALIVE
    void emDataSaved() {
        isSaving = false;
        std::cout << "[C++] 파일 저장 완료! 입력 잠금이 해제되었습니다." << std::endl;
    }
}

void emFileInit() {
    EM_ASM({
        try {
            FS.mkdir('/save');
        } catch (e) {}

        FS.mount(FS.filesystems.IDBFS, {}, '/save');
        console.log("IndexedDB 마운트 및 동기화 시작...");
        
        FS.syncfs(true, function (err) {
            if (err) {
                console.error("Failed to load save data from IndexedDB:", err);
            } else {
                console.log("Save data loaded successfully from IndexedDB.");
            }
            // 💡 맹글링 대응: 앞에 언더바 '_'를 붙여서 호출
            _emDataLoaded(); 
        });
    });
}

void emFileWrite() {
    if (isSaving) return; // 이미 저장 중이면 중복 요청 방지
    isSaving = true;      // 💡 저장 시작 (입력 차단)
    std::cout << "[C++] 파일 저장 중... 입력이 차단됩니다." << std::endl;

    ofs.open("/save/save.txt");
    if (ofs.is_open()) {
        ofs << num;
        ofs.close();
    }
   
    EM_ASM({
        FS.syncfs(false, function (err) {
            if (err) {
                console.error("Failed to persist save to IndexedDB:", err);
            }
            // 💡 저장이 끝나면 C++ 측 잠금 해제 함수 호출
            _emDataSaved();
        });
    });
}
#endif

void init() {
    path = (std::string)SDL_GetBasePath() + "save.txt";
    ifs.open(path);
    if (!ifs.is_open()) {
        std::ofstream createFile(path);
        createFile << 0;
        createFile.close();
        ifs.open(path);
    }
    ifs >> num;
    ifs.close();
}

void run() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return;
    }
    
    window = SDL_CreateWindow(
        "SDL2 기본 윈도우", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    isRunning = true;

    #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(loop, 0, 0);
    #endif
}

void loop() {
    #ifdef __EMSCRIPTEN__
    if (isSaving) return;
    if (!isRunning) {
        emFileWrite();
        emscripten_cancel_main_loop();
        return;
    }
    #endif

    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        if (event.type == SDL_MOUSEBUTTONUP) {
            num += 1;
            std::cout << "현재 숫자: " << num << std::endl;
            #ifdef __EMSCRIPTEN__
            emFileWrite();
            #else
            ofs.open(path);
            ofs << num;
            ofs.close();
            #endif
        }
        if (event.type == SDL_KEYDOWN) {
            num = 0;
            #ifdef __EMSCRIPTEN__
            emFileWrite();
            #else
            ofs.open(path);
            ofs << num;
            ofs.close();
            #endif
        }
    }
}

int main(int argc, char** argv) {
    #ifdef __EMSCRIPTEN__
    emFileInit();
    #else
    init();
    run();

    while (isRunning) {
        loop();
        SDL_Delay(16);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    ofs.open(path);
    ofs << num;
    ofs.close();
    #endif
    return 0;
}