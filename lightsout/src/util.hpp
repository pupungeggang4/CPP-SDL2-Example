#include "util.hpp"
#include "game.hpp"
#include "board.hpp"

void loadFile(Game& game) {
    std::ifstream ifs("save.txt");
    if (!ifs.is_open()) {
        std::ofstream create("save.txt");
        create << "0" << std::endl;
        for (int i = 0; i < 7; i++) {
            create << "0 0 0 0 0 0 0" << std::endl;
        }
        create.close();
        ifs.open("save.txt");
    }

    shared_ptr<Board> board = game->board;

    ifs >> board->move;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            ifs >> board->cell[i][j];
        }
    }
    ifs.close();
}

void saveFile(Game& game) {
}
