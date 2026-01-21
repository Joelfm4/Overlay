#pragma once

#include <vector>
#include <thread>

#include "Object.h"
#include "RenderQueue.h"



class Visual {

public:

	Visual(std::atomic<bool>& running, RenderQueue& renderQueue) : running(running), renderQueue(renderQueue) {}

	void Run();


private:

	/* Variables */
    std::atomic<bool>& running;
    RenderQueue& renderQueue;


};

