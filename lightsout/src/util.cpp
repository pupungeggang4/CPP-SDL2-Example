#include "util.hpp"
#include "game.hpp"
#include "board.hpp"

#ifdef __EMSCRIPTEN__
void emGameInit(Game* game) {
	EM_ASM({
		if (!FS.analyzePath('/save').exists) {
			FS.mkdir('/save');
		}
		FS.mount(IDBFS, {}, '/save');
		const appPtr = $0; 
		FS.syncfs(true, function (err) {
			if (err) {
				console.error("Failed to load.", err);
			} else {
				console.log("Loaded successfully.");
				_emGameRun(appPtr);
			}
		});
	}, game);	
}

void emSyncFile(Game* game) {
	EM_ASM({
        FS.syncfs(false, function (err) {
			const appPtr = $0;
            if (err) {
				console.error("Failed to save to IndexedDB", err);
				_emSynced(appPtr);
			}
            else {
				console.log("Saved to IndexedDB");
				_emSynced(appPtr);
			}
        });
    }, game);
}

void emLoadFile(Game& game) {
    std::ifstream ifs("/save/save.txt");
    if (!ifs.is_open()) {
		std::cout << "No file" << std::endl;
        std::ofstream create("/save/save.txt");
        create << "0" << std::endl;
        for (int i = 0; i < 7; i++) {
            create << "0 0 0 0 0 0 0" << std::endl;
        }
        create.close();
        ifs.open("/save/save.txt");
    }

    shared_ptr<Board> board = game.board;

    ifs >> board->move;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            ifs >> board->cell[i][j];
        }
    }
    board->count();
    ifs.close();
}

void emSaveFile(Game& game) {
    std::ofstream ofs("/save/save.txt");
    shared_ptr<Board> board = game.board;

    ofs << board->move << std::endl;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            ofs << board->cell[i][j];
            ofs << std::endl;
        }
    }
    ofs.close();
}

extern "C" {
EMSCRIPTEN_KEEPALIVE
void emGameRun(Game* game) {
	emscripten_set_main_loop_arg(
        [](void* arg) {
            static_cast<Game*>(arg)->loop(); 
        }, 
    game, 0, 0);
	game->run();
}

EMSCRIPTEN_KEEPALIVE
void emSynced(Game* game) {
	std::cout << "Unlock input" << std::endl;
	game->locked = false;
}
}
#endif

void loadFile(Game& game) {
    std::ifstream ifs("save.txt");
    if (!ifs.is_open()) {
        std::ofstream create("save.txt");
        create << "0" << std::endl;
        for (int i = 0; i < 7; i++) {
            create << "0 0 0 0 0 0 0" << std::endl;
        }
        create.close();
        ifs.open("save.txt");
    }

    shared_ptr<Board> board = game.board;

    ifs >> board->move;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            ifs >> board->cell[i][j];
        }
    }
    board->count();
    ifs.close();
}

void saveFile(Game& game) {
    std::ofstream ofs("save.txt");
    shared_ptr<Board> board = game.board;

    ofs << board->move << std::endl;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            ofs << board->cell[i][j];
            ofs << std::endl;
        }
    }
    ofs.close();
}
