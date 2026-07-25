#pragma once
#include "includes.hpp"

class Game;
class Scene {
    public:
        Scene();
        void start(Game&);
        void render(Game&);
        void update(Game&);
        //void handleMouse(Game&);
};
