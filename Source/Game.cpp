#include "Game.h"



Game::Game(HINSTANCE instance, HINSTANCE prevInstance, PSTR cmdLine, INT showCmd) :
	instance(instance),
	prevInstance(prevInstance),
	cmdLine(cmdLine),
	showCmd(showCmd)
{}


void Game::Run() {

	/* Instances */
	RenderQueue renderQueue;
	Overlay overlay(instance, prevInstance, cmdLine, showCmd);
	Menu menu;


	std::atomic<bool> running { true };


	/* Threads */
	std::thread ViewThread([&]() {
		Visual visual(running, renderQueue);
		visual.Run();
	});


	// -------------------------------------------------------------------- //
	//                               Main Loop                              //
	// -------------------------------------------------------------------- //

	std::vector<Object> objects;

	bool showMenu = false;


	while (running) {

		MSG msg;

		while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {

			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				running = false;

		}


		if (!running) break;

		if (GetAsyncKeyState(VK_INSERT) & 1) showMenu = !showMenu;


		// ############################ Render

		objects = renderQueue.GetAndClear();

		overlay.BeginFrame();

		if (showMenu) {

			menu.Display();

			overlay.SetClickThrough(true);

		} else overlay.SetClickThrough(false);


		overlay.DrawObjects(objects);

		overlay.EndFrame();

		// ############################


	}


	ViewThread.join();


}
