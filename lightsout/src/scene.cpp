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
    std::cout << game.board->row << std::endl;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            SDL_Rect dstRect = {120 + i * 80, 40 + j * 80, 80, 80};
            //if (game.board->cell[i][j]) SDL_RenderCopy(game.renderer, Asset::on, NULL, &dstRect);
            //else SDL_RenderCopy(game.renderer, Asset::off, NULL, &dstRect);
            SDL_RenderCopy(game.renderer, Asset::on, NULL, &dstRect);
        }
    }
    SDL_RenderCopy(game.renderer, Asset::cellText, NULL, &game.rectCellText);
    SDL_RenderCopy(game.renderer, Asset::moveText, NULL, &game.rectMoveText);

    std::string num = std::to_string(game.numCell);
    for (int i = 0; i < num.length(); i++) {
        int l = (int)num[i] - '0';
        SDL_Rect dstRect = {220 + i * 16, 4, 16, 32};
        if (l >= 0 && l <= 9)
        SDL_RenderCopy(game.renderer, Asset::numText[l], NULL, &dstRect);
    }

    num = std::to_string(game.numMove);
    for (int i = 0; i < num.length(); i++) {
        int l = (int)num[i] - '0';
        SDL_Rect dstRect = {724 + i * 16, 4, 16, 32};
        if (l >= 0 && l <= 9)
        SDL_RenderCopy(game.renderer, Asset::numText[l], NULL, &dstRect);
    }
}

void Scene::update(Game& game) {
}
