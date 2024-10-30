#include "GPUResourceStatistic.h"

namespace GPU
{
    GPUResourceStatistic* stats;

    GPUResourceStatistic::~GPUResourceStatistic()
    {
        if (resources.size() != 0)
        {
            logger->WriteLine("not all GPU Resources is freed. Count = " + std::to_string(resources.size()), "GPU", Error);

            logger->WriteLine("Resources list:", "");

            for (std::pair<uintptr_t, std::string> name : resources)
            {
                logger->WriteLine("Resource " + name.second + " at Adress " + std::to_string(name.first), "");
            }
        }
    }
}