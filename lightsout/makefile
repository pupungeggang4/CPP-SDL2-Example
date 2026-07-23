win-mingw:
	g++ main.cpp -o build/main.exe -Iinclude -lSDL2_main -lSDL2 -lSDL2_ttf -lSDL2_image -lmingw32

win-msys:
	g++ main.cpp -o build/main.exe -Iinclude -IC:\msys64\ucrt64\include -LC:\msys64\ucrt64\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image

mac-brew:
	g++ main.cpp -o build/main.out -Iinclude -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2 -lSDL2_ttf -lSDL2_image

empp:
	em++ main.cpp -o build/index.html -Iinclude -O2 -sUSE_SDL=2 -sUSE_SDL_TTF=2 -sUSE_SDL_IMAGE=2 -sMAX_WEBGL_VERSION=2 --preload-file "asset@asset"
