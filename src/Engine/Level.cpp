#include "Level.h"

void Level::AddObject(Object& object)
{
    objects.push_back(&object);
}

std::vector<Object*>& Level::GetObjectsList()
{
    return objects;
}

void Level::Destroy()
{
    for (Object* obj : objects)
    {
        obj->Destroy();
        delete obj;
    }
}
