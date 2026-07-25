#include "board.hpp"

Board::Board() {
}

bool Board::isInside(int r, int c) {
    return r >= 0 && r < row && c >= 0 && c < col;
}

void Board::flip(int r, int c) {
    for (int i = 0; i < 5; i++) {
        int crow = r + neighbor[i][0];
        int ccol = c + neighbor[i][1];

        if (isInside(crow, ccol)) {
            cell[crow][ccol] = 1 - cell[crow][ccol];
        }
    }
}
