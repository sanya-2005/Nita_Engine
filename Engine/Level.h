#pragma once
#include "Object.h"
#include <vector>

class Level
{
private:
	std::vector<Object*> objects;

public:
	void AddObject(Object& object);
	std::vector<Object*>& GetObjectsList();
};