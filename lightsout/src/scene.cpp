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
    for (int i = 0; i < game.board->row; i++) {
        for (int j = 0; j < game.board->col; j++) {
            SDL_Rect dstRect = {120 + j * 80, 40 + i * 80, 80, 80};
            if (game.board->cell[i][j]) SDL_RenderCopy(game.renderer, Asset::on, NULL, &dstRect);
            else SDL_RenderCopy(game.renderer, Asset::off, NULL, &dstRect);
        }
    }
    SDL_RenderCopy(game.renderer, Asset::cellText, NULL, &game.rectCellText);
    SDL_RenderCopy(game.renderer, Asset::moveText, NULL, &game.rectMoveText);

    std::string num = std::to_string(game.board->left);
    for (int i = 0; i < num.length(); i++) {
        int l = (int)num[i] - '0';
        SDL_Rect dstRect = {220 + i * 16, 4, 16, 32};
        SDL_RenderCopy(game.renderer, Asset::numText[l], NULL, &dstRect);
    }

    num = std::to_string(game.board->move);
    for (int i = 0; i < num.length(); i++) {
        int l = (int)num[i] - '0';
        SDL_Rect dstRect = {724 + i * 16, 4, 16, 32};
        SDL_RenderCopy(game.renderer, Asset::numText[l], NULL, &dstRect);
    }
}

void Scene::update(Game& game) {
}

void Scene::handleMouse(Game& game, int x, int y, int button) {
    if (button == 1) {
        int crow = (y - 40) / 80;
        int ccol = (x - 120) / 80;
        std::cout << crow << ',' << ccol << std::endl;
        game.board->flip(crow, ccol);
        game.board->move += 1;
    }
}
