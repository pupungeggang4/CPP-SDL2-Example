win-scoop:
	g++ main.cpp -o main.exe \
	-I"$(USERPROFILE)\scoop\apps\sdl2\current\include" \
	-L"$(USERPROFILE)\scoop\apps\sdl2\current\lib" \
	-lSDL2main -lSDL2;
	cp "$(USERPROFILE)\scoop\apps\sdl2\current\lib\SDL2.dll" .

emcc:
	em++ main.cpp -o build/index.html -sUSE_SDL=2 -sMAX_WEBGL_VERSION=2 -Os
