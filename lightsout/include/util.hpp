#pragma once
#include "includes.hpp"

class Game;
#ifdef __EMSCRIPTEN__
void emInitSave();
void emLoadFile();
void emSaveFile();
#endif
void loadFile(Game&);
void saveFile(Game&);
