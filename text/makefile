win-mingw:
	g++ main.cpp -o build/main.exe -lSDL2_main -lSDL2 -lSDL2_ttf -lmingw32

mac-brew:
	g++ main.cpp -o build/main.out -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2 -lSDL2_ttf

empp:
	em++ main.cpp -o build/index.html -O2 -sUSE_SDL=2 -sUSE_SDL_TTF=2 -sMAX_WEBGL_VERSION=2 --preload-file "asset@asset"
