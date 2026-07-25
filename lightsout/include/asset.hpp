#pragma once
#include "includes.hpp"

class Asset {
    public:
        static SDL_Texture *on, *off;
        static SDL_Texture *cellText, *moveText;
        static SDL_Texture* numText[10];
        static TTF_Font* neodgm;
};
