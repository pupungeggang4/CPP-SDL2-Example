#pragma once
#include "includes.hpp"

class Board {
    public:
        int neighbor[5][2] = {{-1, 0}, {0, -1}, {0, 0}, {0, 1}, {1, 0}};

        int row = 7, col = 7;
        int cell[7][7] = {0};

        Board();
        bool isInside(int, int);
        void flip(int, int);
};
