#pragma once
#include "DLLMacros.h"
#include "Types.h"

struct SystemDate
{
    ushort year;
    ushort month;
    ushort day;
    ushort hour;
    ushort minute;

    SystemDate(ushort year, ushort month, ushort day, ushort hour, ushort minute) : year(year), 
        month(month), day(day), hour(hour), minute(minute)
    {

    }
};

class DLL_API SystemTime
{
public:
    static ulong GetTime();

    static SystemDate GetLocalDate();
};