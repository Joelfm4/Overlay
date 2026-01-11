#pragma once

#include <vector>
#include <mutex>

#include "Object.h"



class RenderQueue {

public:

    void PushObject(const Object& object) {

        std::lock_guard<std::mutex> lock(mutex_);
        writeBuffer_.push_back(object);

    }

    void PushObjects(const std::vector<Object>& objects) {

        std::lock_guard<std::mutex> lock(mutex_);
        writeBuffer_.insert(writeBuffer_.end(), objects.begin(), objects.end());
    
    }

    std::vector<Object> GetAndClear() {

        std::lock_guard<std::mutex> lock(mutex_);

        readBuffer_.clear();
        swap(writeBuffer_, readBuffer_);

        return readBuffer_;

    }



private:
	std::mutex mutex_;
    std::vector<Object> writeBuffer_;
    std::vector<Object> readBuffer_;

};
