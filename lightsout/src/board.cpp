#include "board.hpp"

Board::Board() {
}

void Board::reset() {
    gen = std::mt19937(rd());
    std::uniform_int_distribution<int> dis(0, row * col - 1);

    move = 0; left = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cell[i][j] = 0;
        }
    }
    for (int i = 0; i < 8; i++) {
        int index = dis(gen);
        int c = index % col;
        int r = (index - c) / col;
        flip(r, c);
    }
    left = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (cell[i][j] == 1) left += 1;
        }
    }
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
    left = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (cell[i][j] == 1) left += 1;
        }
    }
}
