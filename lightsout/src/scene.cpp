#include "scene.hpp"
#include "asset.hpp"
#include "board.hpp"
#include "game.hpp"

Scene::Scene() {
}

void Scene::start(Game& game) {
    
}

void Scene::render(Game& game) {
    SDL_RenderClear(game.renderer);
    //std::cout << game.board->row << std::endl;

    SDL_RenderCopy(game.renderer, Asset::cellText, NULL, &game.rectCellText);
    SDL_RenderCopy(game.renderer, Asset::moveText, NULL, &game.rectMoveText);

    std::string num = std::to_string(game.numCell);
    for (int i = 0; i < num.length(); i++) {
        int l = (int)num[i] - '0';
        SDL_Rect dstRect = {220 + i * 16, 4, 16, 32};
        SDL_RenderCopy(game.renderer, Asset::numText[l], NULL, &dstRect);
    }

    num = std::to_string(game.numMove);
    for (int i = 0; i < num.length(); i++) {
        int l = (int)num[i] - '0';
        SDL_Rect dstRect = {724 + i * 16, 4, 16, 32};
        SDL_RenderCopy(game.renderer, Asset::numText[l], NULL, &dstRect);
    }
}

void Scene::update(Game& game) {
}
