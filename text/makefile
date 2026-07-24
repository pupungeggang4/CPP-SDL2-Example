win-mingw:
	g++ main.cpp -o build/main.exe -lSDL2_main -lSDL2 -lSDL2_ttf -lmingw32

win-msys:
	g++ main.cpp -o build/main.exe -IC:\msys64\ucrt64\include -LC:\msys64\ucrt64\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

mac-brew:
	g++ main.cpp -o build/main.out -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2 -lSDL2_ttf

emcc:
	em++ main.cpp -o build/index.html -O2 -sUSE_SDL=2 -sUSE_SDL_TTF=2 -sMAX_WEBGL_VERSION=2 --preload-file "asset@asset"
