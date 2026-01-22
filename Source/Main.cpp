#include "Game.h"


INT APIENTRY WinMain(HINSTANCE instance, HINSTANCE prevInstance, PSTR cmdLine, INT showCmd) {

	Game* game = new Game(instance, prevInstance, cmdLine, showCmd);

	game->Run();

	delete game;

}

