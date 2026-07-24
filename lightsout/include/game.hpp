#pragma once
#include "includes.hpp"

class Game {
    public:
        SDL_Window* window;
        SDL_Renderer* renderer;

        Game();
        void run();
        void loop();
};
