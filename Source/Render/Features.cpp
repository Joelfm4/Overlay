#include "Features.h"


void Visual::Run() {

	std::vector<Object> viewObjects;

	while (running) {


		// -------------------------------------------------------------------- //
		//                                  ESP                                 //
		// -------------------------------------------------------------------- //

		viewObjects.clear();


		viewObjects.push_back(Rect{
				.color = ImColor(0.15f, 0.81f, 0.95f, 1.0f),
				.min = {500.f, 500.f},
				.max = {650.f, 750.f},
			}
		);

		viewObjects.push_back(Text{
				.color = ImColor(0.15f, 0.81f, 0.95f, 1.0f),
				.pos = { 551.f, 485.f},
				.text = "Joelfm4",
			}
		);


		renderQueue.PushObjects(viewObjects);

	}


	std::this_thread::sleep_for(std::chrono::milliseconds(10));

}
