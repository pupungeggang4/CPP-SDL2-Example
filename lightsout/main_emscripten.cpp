#include "includes.hpp"
#include "util.hpp"
#include "game.hpp"
#include <stdio.h>

int main(int argc, char** argv) {
    shared_ptr<Game> game = make_shared<Game>();
    game->run();
    emscripten_set_main_loop_arg(
        [](void* arg) {
            static_cast<Game*>(arg)->loop(); 
        }, 
    game.get(), 0, 0);
    return 0;
}
