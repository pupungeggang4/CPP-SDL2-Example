win-msys:
	g++ main.cpp -o build/main.exe -IC:\msys64\ucrt64\include -LC:\msys64\ucrt64\lib -lmingw32 -lSDL2main -lSDL2

mac-brew:
	g++ main.cpp -o build/main.out -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2 -lSDL2_ttf

empp:
	em++ main.cpp -o build/index.html -Os -lidbfs.js -s USE_SDL=2 -s FORCE_FILESYSTEM=1 -s EXPORTED_FUNCTIONS="['_main']"

dummy:

