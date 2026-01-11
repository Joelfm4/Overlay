#include "Render/Overlay.h"
#include "Render/RenderQueue.h"
#include "Render/Features.h"



class Game {

public: 

	Game(HINSTANCE instance, HINSTANCE prevInstance, PSTR cmdLine, INT showCmd) :
		instance(instance),
		prevInstance(prevInstance),
		cmdLine(cmdLine),
		showCmd(showCmd)
	{};



	void Run() {

		/* Instances */
		RenderQueue renderQueue;
		Overlay overlay(instance, prevInstance, cmdLine, showCmd);


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

		while (running) {

			MSG msg;

			while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {

				TranslateMessage(&msg);
				DispatchMessage(&msg);

				if (msg.message == WM_QUIT)
					running = false;

			}

			if (!running)
				break;


			// ############################ Render

			objects = renderQueue.GetAndClear();

			overlay.BeginFrame();
			overlay.DrawObjects(objects);
			overlay.EndFrame();

			// ############################


			ViewThread.join();

		}


	}


private:

	/* Variables */
	HINSTANCE instance;
	HINSTANCE prevInstance;
	PSTR cmdLine;
	INT showCmd;

	/* Screen Resolution */
	int height;
	int width;

};
