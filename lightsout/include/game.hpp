#pragma once
#include "includes.hpp"

class Game : public std::enable_shared_from_this<Game> {
    public:
        shared_ptr<Game> self;
        const int lWidth = 800, lHeight = 600;
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Rect rectCellText, rectCellTextNum, rectMoveText, rectMoveTextNum;

        Game();
        void run();
        void loop();
        void loadAsset();
        void disposeAsset();
        void cleanup();
};
