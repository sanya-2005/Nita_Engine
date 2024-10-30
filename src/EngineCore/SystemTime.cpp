#include "SystemTime.h"
#include <windows.h>

ulong SystemTime::GetTime()
{
    return timeGetTime();
}

SystemDate SystemTime::GetLocalDate()
{
    SYSTEMTIME time;

    GetLocalTime(&time);

    return SystemDate(time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute);
}
