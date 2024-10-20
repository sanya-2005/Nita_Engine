#include "Level.h"

void Level::AddObject(Object& object)
{
    objects.push_back(&object);
}

std::vector<Object*>& Level::GetObjectsList()
{
    return objects;
}
