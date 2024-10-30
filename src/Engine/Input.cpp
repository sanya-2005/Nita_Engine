#include "Input.h"
#include "OSWindow.h"

#include "windows.h"

Input input;

static KeyboardKeys ConvertVirtualKey(int virtualKey)
{
    switch (virtualKey)
    {
    case 0x41:
        return A;
    case 0x57:
        return W;
    case 0x53:
        return S;
    case 0x44:
        return D;
    case VK_ESCAPE:
        return Esc;
    default:
        return UnknownKey;
    }
}

static int ConvertMouseEngineKey(MouseButtons button)
{
    switch (button)
    {
    case LeftButton:
        if (GetSystemMetrics(SM_SWAPBUTTON))
            return VK_RBUTTON;
        else
            return VK_LBUTTON;
    case RightButton:
        if (GetSystemMetrics(SM_SWAPBUTTON))
            return VK_LBUTTON;
        else
            return VK_RBUTTON;
    case Wheel:
        return VK_MBUTTON;
    default:
        return -1;
    }
}

static int ConvertEngineKey(KeyboardKeys key)
{
    switch (key)
    {
    case A:
        return 0x41;
    case W:
        return 0x57;
    case S:
        return 0x53;
    case D:
        return 0x44;
    case Esc:
        return VK_ESCAPE;
    case UnknownKey:
    default:
        return -1;
    }
}

KeyCache::KeyCache()
{
    keyboardCache = { 
        {A, false}, {W, false}, {S, false}, {D, false}, {Esc, false} 
    };
}

void Input::Capture(OSWindow& window)
{
    SetCapture((HWND)window.GetWindowHandle());
}

void Input::ReleaseCapture()
{
    ::ReleaseCapture();
}

bool Input::IsKeyPressed(KeyboardKeys key)
{
    if (key == UnknownKey)
        return false;

    bool result = GetAsyncKeyState(ConvertEngineKey(key)) & 0x8000;

    cache[key] = result;

    return result;
}

bool Input::IsKeyHolded(KeyboardKeys key)
{
    bool isPressed = cache[key];

    return IsKeyPressed(key) && isPressed;
}

bool Input::IsKeyReleased(KeyboardKeys key)
{
    return !IsKeyPressed(key);
}

bool Input::IsMouseKeyPressed(MouseButtons key)
{
    if (key == UnknownKey)
        return false;

    return GetAsyncKeyState(ConvertMouseEngineKey(key)) & 0x8000;
}

bool Input::IsMouseKeyReleased(MouseButtons key)
{
    if (key == UnknownKey)
        return false;

    return !(GetAsyncKeyState(ConvertMouseEngineKey(key)) & 0x8000);
}

int Input::GetMouseWheelDelta()
{
    return mouseScrollDelta;
}

void Input::SetMouseWheelDelta(int value)
{
    this->mouseScrollDelta = value;
}

void Input::Update()
{
    mouseScrollDelta = 0;
}

MousePosition Input::GetMousePosition()
{
    POINT point;
    GetCursorPos(&point);
    return MousePosition(point.x, point.y);
}

