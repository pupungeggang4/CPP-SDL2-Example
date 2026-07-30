#pragma once
#include "includes.hpp"

class Game;
#ifdef __EMSCRIPTEN__
void emGameInit(Game*);
void emSyncFile(Game*);
extern "C" void emGameRun(Game*);
extern "C" void emSynced(Game*);
#endif
void saveSequence(Game*);
void loadFile(Game&);
void saveFile(Game&);
