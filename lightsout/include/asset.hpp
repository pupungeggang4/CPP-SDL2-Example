#pragma once
#include "includes.hpp"

class Asset {
    public:
        static SDL_Texture* on, off;
        static TTF_Font* neodgm;
        static void loadAsset();
        static void disposeAsset();
};
