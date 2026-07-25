#pragma once
#include "includes.hpp"

class Game;
#ifdef __EMSCRIPTEN__
void emGameInit(Game*);
void emSyncFile(Game*);
void emSaveFile(Game&);
void emLoadFile(Game&);
extern "C" void emGameRun(Game*);
extern "C" void emSynced(Game*);
#endif
void loadFile(Game&);
void saveFile(Game&);
