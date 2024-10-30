#include "Wait.h"
#include "Windows.h"

void DLL_API Wait(ulong milliseconds)
{
    Sleep(milliseconds);
}
