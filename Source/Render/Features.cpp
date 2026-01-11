#include "Features.h"


void Visual::Run() {

	std::vector<Object> viewObjects;

	while (running) {

		viewObjects.clear();

		for (std::size_t i = 0; i < 10; ++i) {

			for (std::size_t j = 0; j < 10; ++j) {

				viewObjects.push_back(Circle{
					.color = ImColor(0.80f, 0.52f, 0.25f, 1.0f),
					.center = {50.f * i, 50.f * j},
					.radius = 20.f,
					});

			}

		}

		renderQueue.PushObjects(viewObjects);

		std::this_thread::sleep_for(std::chrono::milliseconds(10));

	}


}
