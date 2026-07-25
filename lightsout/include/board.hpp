#pragma once
#include "includes.hpp"

class Board {
    public:
        std::random_device rd;
        std::mt19937 gen;
        int neighbor[5][2] = {{-1, 0}, {0, -1}, {0, 0}, {0, 1}, {1, 0}};

        int row = 7, col = 7, left = 0, move = 0;
        int cell[7][7] = {0};

        Board();
        void reset();
        bool isInside(int, int);
        void flip(int, int);
};
