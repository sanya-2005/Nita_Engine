#pragma once
#include "EngineCore/Types.h"
#include "Log.h"

#include <map>

namespace GPU
{
    class GPUResourceStatistic
    {
    private:
        std::map<uintptr_t, std::string> resources;

    public:
        void AddResource(uintptr_t ptrAdress, std::string name)
        {
            resources.emplace(ptrAdress, name);
        }

        void RemoveResource(uintptr_t ptrAdress)
        {
            resources.erase(ptrAdress);
        }

        ~GPUResourceStatistic();
    };

    extern GPUResourceStatistic* stats;
}
