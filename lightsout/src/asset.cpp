#include "asset.hpp"

SDL_Texture *Asset::on = nullptr, *Asset::off = nullptr;
SDL_Texture *Asset::cellText = nullptr, *Asset::moveText = nullptr;
SDL_Texture* Asset::numText[10] = {nullptr};
TTF_Font* Asset::neodgm = nullptr;
