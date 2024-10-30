#pragma once

#ifdef ENGINECORE_PROJ
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif