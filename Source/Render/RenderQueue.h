#pragma once

#include <vector>
#include <mutex>

#include "Object.h"



class RenderQueue {

public:

    void PushObject(const Object& object);


    void PushObjects(const std::vector<Object>& objects);


    std::vector<Object> GetAndClear();


private:

	std::mutex mutex;
    std::vector<Object> writeBuffer;
    std::vector<Object> readBuffer;

};
