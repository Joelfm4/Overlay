#pragma once

#include "Render/Overlay.h"
#include "Render/RenderQueue.h"
#include "Render/Features.h"



class Game {

public: 

	Game(HINSTANCE instance, HINSTANCE prevInstance, PSTR cmdLine, INT showCmd);

	void Run();


private:

	/* Variables */
	HINSTANCE instance;
	HINSTANCE prevInstance;
	PSTR cmdLine;
	INT showCmd;

};
