gcc:
	g++ main_desktop.cpp -o build/main.out

emcc:
	emcc main_emscripten.cpp -o build/index.html -s FORCE_FILESYSTEM=1 -lidbfs.js -s EXPORTED_FUNCTIONS="['_main', '_run_business_logic']"
