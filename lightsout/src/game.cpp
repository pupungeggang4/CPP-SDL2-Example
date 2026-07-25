#include "includes.hpp"
#include "asset.hpp"
#include "util.hpp"
#include "board.hpp"
#include "scene.hpp"
#include "game.hpp"

Game::Game() {

}

void Game::run() {
    // Init SDL2.
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Failed to initialize SDL." << std::endl;
        return;
    }

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cout << "Failed to initialize Image. " << IMG_GetError() << std::endl;
        return;
    }

    if (TTF_Init() == -1) {
        std::cout << "SDL_ttf could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    window = SDL_CreateWindow("Lights Out", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, lWidth, lHeight, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_RenderSetLogicalSize(renderer, lWidth, lHeight);

    loadAsset();

    // Init game
    scene = make_shared<Scene>();
    board = make_shared<Board>();
    board->reset();
}

void Game::loop() {
    handleInput();
    scene->update(*this);
    SDL_SetRenderDrawColor(renderer, 255, 255, 127, 255);
    scene->render(*this);
    SDL_RenderPresent(renderer);

    #ifdef __EMSCRIPTEN__
    if (!running) {
        emscripten_cancel_main_loop();
    }
    #endif
}

void Game::handleInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }

        if (event.type == SDL_MOUSEBUTTONUP) {
            scene->handleMouse(*this, event.button.x, event.button.y, event.button.button);
        }

        if (event.type == SDL_KEYUP) {
            #ifndef __EMSCRIPTEN
            if (key == SDLK_L) {
                loadFile(*this);
            }
            #endif
        }
    }
}

void Game::loadAsset() {
    Asset::on = IMG_LoadTexture(renderer, "asset/on.png");
    Asset::off = IMG_LoadTexture(renderer, "asset/off.png");
    Asset::neodgm = TTF_OpenFont("asset/neodgm.ttf", 32);

    SDL_Color textColor = {0, 0, 0, 255};
    SDL_Surface* cellTextSurf = TTF_RenderText_Blended(Asset::neodgm, "Number Left : ", textColor);
    Asset::cellText = SDL_CreateTextureFromSurface(renderer, cellTextSurf);
    rectCellText = {4, 4, cellTextSurf->w, cellTextSurf->h};
    SDL_FreeSurface(cellTextSurf);
    SDL_Surface* moveTextSurf = TTF_RenderText_Blended(Asset::neodgm, "Moves : ", textColor);
    Asset::moveText = SDL_CreateTextureFromSurface(renderer, moveTextSurf);
    rectMoveText = {604, 4, moveTextSurf->w, moveTextSurf->h};
    SDL_FreeSurface(moveTextSurf);

    for (int i = 0; i < 10; i++) {
        SDL_Surface* temp = TTF_RenderText_Blended(Asset::neodgm, std::to_string(i).c_str(), textColor);
        Asset::numText[i] = SDL_CreateTextureFromSurface(renderer, temp);
        SDL_FreeSurface(temp);
    }
}

void Game::disposeAsset() {
    SDL_DestroyTexture(Asset::on);
    SDL_DestroyTexture(Asset::off);
}

void Game::cleanup() {
    disposeAsset();
}
