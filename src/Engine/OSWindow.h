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
	/// ������� ����.
	/// </summary>
	/// <param name="hinst">���������� ���������� Win32.</param>
	/// <param name="cmdShow">�������� ��� Win32 ����������.</param>
	void Create(void* hinst, int cmdShow, uint height, uint width, std::wstring title);

	/// <summary>
	/// �������, ���������� ������ ����� ���������
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
	/// �������� ������ ����.
	/// </summary>
	void UpdateWindowSize();
};