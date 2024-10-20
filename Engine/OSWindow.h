#pragma once
#include "utils.h"
#include "Event.h"

#include <string>

using WindowHandle = void*;

class OSWindow
{
private:
	WindowHandle windowHandle;

	std::wstring windowClassName;
	std::wstring title;

	uint height;
	uint width;

	bool isClosed;

	OSEventQueue* osEventQueue;

public:

	/// <summary> 
	/// создать окно.
	/// </summary>
	/// <param name="hinst">дескриптор приложения Win32.</param>
	/// <param name="cmdShow">параметр для Win32 приложения.</param>
	bool Create(void* hinst, int cmdShow, uint height, uint width, std::wstring title);
	int MessageLoop();

	WindowHandle GetWindowHandle();
	Size GetWindowSize();
	bool shouldClosed();

	bool IsEvents();
	Event* PopEvent();

	/// <summary> 
	/// обновить размер окна.
	/// </summary>
	void UpdateWindowSize();
};