#pragma once
#include "EngineCore\Types.h"
#include "Event.h"
#include "Input.h"

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
    bool isActive;

	OSEventQueue* osEventQueue;

public:

	/// <summary> 
	/// создать окно.
	/// </summary>
	/// <param name="hinst">дескриптор приложения Win32.</param>
	/// <param name="cmdShow">параметр для Win32 приложения.</param>
	void Create(void* hinst, int cmdShow, uint height, uint width, std::wstring title);

	/// <summary>
	/// Функция, содержащая работу цикла сообщений
	/// </summary>
	int MessageLoop();

	WindowHandle GetWindowHandle();
	Size GetWindowSize();
	bool ShouldClosed();

    MousePosition ScreenCoordsToClient(MousePosition screenCoords);

	bool IsEvents();
	Event* PopEvent();
    bool IsActive();

	/// <summary> 
	/// обновить размер окна.
	/// </summary>
	void UpdateWindowSize();
};