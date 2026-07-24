#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <string>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
bool isRunning;
std::ifstream ifs;
std::ofstream ofs;
int num = 0;
bool asyncLock = false;

#ifdef __EMSCRIPTEN__
void emFileInit() {
    EM_ASM({
        try {
            FS.mkdir('/save');
        } catch (e) {
        }

        FS.mount(FS.filesystems.IDBFS, {}, '/save');
        FS.syncfs(true, function (err) {
            if (err) {
                console.error("Failed to load save data from IndexedDB:", err);
            } else {
                console.log("Save data loaded successfully from IndexedDB.");
            }
        });
    });
}

void emFileRead() {
    ifs.open("/save/save.txt");
    ifs >> num;
    ifs.close();
}

void emFileWrite() {
    ofs.open("/save/save.txt");
    ofs << num;
    ofs.close();
   
    EM_ASM(
        FS.syncfs(false, function (err) {
            if (err) {
                console.error("Failed to persist save to IndexedDB:", err);
            } else {
                console.log("Save successfully persisted to IndexedDB!");
            }
        });
    );
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
            std::cout << num << std::endl;
            #ifdef __EMSCRIPTEN__
            emFileWrite();
            #endif
        }

        #ifdef __EMSCRIPTEN__
        if (!isRunning) {
            emscripten_cancel_main_loop();
        }
        #endif
    }
}

int main(int argc, char** argv) {
    #ifdef __EMSCRIPTEN__
    emFileInit();
    emFileRead();
    #else
    // Init file system
    std::string path = "";
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
    #endif

    // Init SDL2
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "SDL2 기본 윈도우", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    isRunning = true;

    #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(loop, 0, 1);
    #else
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

