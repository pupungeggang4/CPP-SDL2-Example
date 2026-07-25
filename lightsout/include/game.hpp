#pragma once
#include "includes.hpp"

class Board;
class Scene;

class Game {
    public:
        const int lWidth = 800, lHeight = 600;
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Rect rectCellText, rectCellTextNum, rectMoveText, rectMoveTextNum;

        bool running = true, locked = false;

        shared_ptr<Scene> scene;
        shared_ptr<Board> board;

        Game();
        void run();
        void loop();
        void handleInput();
        void loadAsset();
        void disposeAsset();
        void cleanup();
};
