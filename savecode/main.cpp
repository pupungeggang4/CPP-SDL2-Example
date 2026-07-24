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
std::ifstream ifs;
std::ofstream ofs;
int num = 0;

SDL_Window* window = nullptr;

void run() {
    // Init SDL2
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << SDL_GetError() << std::endl;
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
    emscripten_set_main_loop(loop, 0, 1);
    #endif
}

#ifdef __EMSCRIPTEN__
extern "C" {
    EMSCRIPTEN_KEEPALIVE
    void on_save_data_loaded() {
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
                _on_save_data_loaded(); 
            } else {
                console.log("Save data loaded successfully from IndexedDB.");
                _on_save_data_loaded(); 
            }
        });
    });
}

void emFileWrite() {
    ofs.open("/save/save.txt");
    if (ofs.is_open()) {
        ofs << num;
        ofs.close();
    }
   
    EM_ASM({
        FS.syncfs(false, function (err) {
            if (err) console.error("Failed to persist save to IndexedDB:", err);
        });
    });
}
#endif

void loop() {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        if (event.type == SDL_MOUSEBUTTONUP) {
            num += 1;
            std::cout << "현재 숫자: " << num << std::endl;
        }
    }
    
    #ifdef __EMSCRIPTEN__
    if (!isRunning) {
        emFileWrite();
        emscripten_cancel_main_loop();
    }
    #endif
}

int main(int argc, char** argv) {
    #ifdef __EMSCRIPTEN__
    emFileInit();
    #else
    std::string path = (std::string)SDL_GetBasePath() + "save.txt";
    ifs.open(path);
    if (!ifs.is_open()) {
        std::ofstream createFile(path);
        createFile << 0;
        createFile.close();
        ifs.open(path);
    }
    ifs >> num;
    ifs.close();

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
