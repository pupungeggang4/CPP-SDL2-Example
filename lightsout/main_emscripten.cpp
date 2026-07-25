#include "includes.hpp"
#include "util.hpp"
#include "game.hpp"

shared_ptr<Game> game = make_shared<Game>();

int main(int argc, char** argv) {
    emGameInit(game.get());
    return 0;
}
