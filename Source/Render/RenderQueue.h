#pragma once

#include <vector>
#include <mutex>

#include "Object.h"



class RenderQueue {

public:

    void PushObject(const Object& object) {

        std::lock_guard<std::mutex> lock(mutex);
        writeBuffer.push_back(object);

    }

    void PushObjects(const std::vector<Object>& objects) {

        std::lock_guard<std::mutex> lock(mutex);
        writeBuffer.insert(writeBuffer.end(), objects.begin(), objects.end());
    
    }

    std::vector<Object> GetAndClear() {

        std::lock_guard<std::mutex> lock(mutex);

        readBuffer.clear();
        swap(writeBuffer, readBuffer);

        return readBuffer;

    }



private:
	std::mutex mutex;
    std::vector<Object> writeBuffer;
    std::vector<Object> readBuffer;

};
