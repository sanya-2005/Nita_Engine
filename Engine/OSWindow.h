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
	/// ������� ����.
	/// </summary>
	/// <param name="hinst">���������� ���������� Win32.</param>
	/// <param name="cmdShow">�������� ��� Win32 ����������.</param>
	bool Create(void* hinst, int cmdShow, uint height, uint width, std::wstring title);
	int MessageLoop();

	WindowHandle GetWindowHandle();
	Size GetWindowSize();
	bool shouldClosed();

	bool IsEvents();
	Event* PopEvent();

	/// <summary> 
	/// �������� ������ ����.
	/// </summary>
	void UpdateWindowSize();
};