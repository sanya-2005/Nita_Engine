#pragma once

using uint = unsigned int;
using ulong = unsigned long;
using ushort = unsigned short;

using flag = uint;

struct Size
{
    uint height;
    uint width;

    Size(uint height, uint width) : height(height), width(width)
    {
    }

    Size() = default;
};

struct Color
{
    float r;
    float g;
    float b;
    float a;

    Color() = default;

    Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a)
    {

    }

    Color(float r, float g, float b) : r(r), g(g), b(b)
    {
        this->a = 1.0f;
    }

    float* GetArray()
    {
        return &r;
    }
};
