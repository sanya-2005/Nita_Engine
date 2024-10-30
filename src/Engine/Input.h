#pragma once
#include "EngineCore/Types.h"
#include "NonCopyable.h"

#include <map>

enum KeyboardKeys
{
    A = 0,
    W,
    S,
    D,
    E,
    Q,
    R,
    I,
    O,
    P,
    M,
    Esc,
    UnknownKey
};

enum MouseButtons
{
    LeftButton,
    RightButton,
    Wheel
};

struct MousePosition
{
    uint x;
    uint y;

    MousePosition(uint x, uint y) : x(x), y(y)
    {

    }
};

class KeyCache
{
private:
    std::map<KeyboardKeys, bool> keyboardCache;

public:
    KeyCache();

    bool& operator[](KeyboardKeys key)
    {
        return keyboardCache[key];
    }
};

class OSWindow;

class Input : NonCopyable
{
private:
    int mouseScrollDelta;
    KeyCache cache;

public:
    void Capture(OSWindow& window);
    void ReleaseCapture();

    bool IsKeyPressed(KeyboardKeys key);
    bool IsKeyHolded(KeyboardKeys key);
    bool IsKeyReleased(KeyboardKeys key);

    bool IsMouseKeyPressed(MouseButtons key);
    bool IsMouseKeyReleased(MouseButtons key);

    int GetMouseWheelDelta();
    void SetMouseWheelDelta(int value);

    void Update();

    MousePosition GetMousePosition();
};

extern Input input;