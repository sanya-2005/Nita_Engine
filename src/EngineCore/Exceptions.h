#pragma once

#include <exception>
#include <string>

class EngineException : public std::exception
{
protected:
    std::string info;
public:
    EngineException(std::string info)
    {
        this->info = info;
    }

    virtual std::string Message()
    {
        return "Engine exception " + info;
    }
};

class InitializationException : public EngineException
{
public:
    InitializationException(std::string info) : EngineException(info)
    {

    }

    std::string Message() override
    {
        return "Error: Initialization failed. Info:\n" + info;
    }
};