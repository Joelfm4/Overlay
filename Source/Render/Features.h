#pragma once

#include <vector>
#include <thread>

#include "Object.h"
#include "RenderQueue.h"



class Visual {

public:

	Visual(std::atomic<bool>& running, RenderQueue& renderQueue);

	void Run();


private:

    std::atomic<bool>& running;
    RenderQueue& renderQueue;


};

