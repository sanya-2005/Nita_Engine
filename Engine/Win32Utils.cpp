#include "Win32Utils.h"
#include <windows.h>

Size Win32Utils::GetSizeFromRect(RECT& rect)
{
    uint clientWidth = rect.right - rect.left;
    uint clientHeight = rect.bottom - rect.top;

    return Size(clientHeight, clientWidth);
}

void Win32Utils::ShowMessageBox(std::wstring text, std::wstring title, MessageBoxType type)
{
    MessageBoxW(nullptr, text.c_str(), title.c_str(), (long)type);
}
