#pragma once
#include "includes.hpp"

#ifdef __EMSCRIPTEN__
class Game;
void emInitSave();
void emLoadFile();
void emSaveFile();
#endif
