#include "RenderQueue.h"


void RenderQueue::PushObject(const Object& object) {

	std::lock_guard<std::mutex> lock(mutex);
	writeBuffer.push_back(object);

}


void RenderQueue::PushObjects(const std::vector<Object>& objects) {

	std::lock_guard<std::mutex> lock(mutex);
	writeBuffer.insert(writeBuffer.end(), objects.begin(), objects.end());

}


std::vector<Object> RenderQueue::GetAndClear() {

	std::lock_guard<std::mutex> lock(mutex);

	readBuffer.clear();
	swap(writeBuffer, readBuffer);

	return readBuffer;

}

