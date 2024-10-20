#include "OSWindow.h"
#include "Log.h"
#include "Win32Utils.h"

#include <windows.h>
#include <string>
#include <exception>

using namespace Win32Utils;

static Event* currentEvent = nullptr;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

bool OSWindow::Create(void* hinst, int cmdShow, uint height, uint width, std::wstring title)
{
	osEventQueue = new OSEventQueue();

	windowClassName = title + L"Class";

	this->height = height;
	this->width = width;
	this->title = title;
	this->isClosed = false;

	WNDCLASSEXW wcex = { 0 };

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = (HINSTANCE)hinst;
	wcex.hIcon = nullptr;
	wcex.hCursor = LoadCursorW(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = windowClassName.c_str();
	wcex.hIconSm = nullptr;

	if (RegisterClassExW(&wcex) == 0)
	{
		logger->WriteLine("Error Register Window class", "Win32 Window");
		return false;
	}

	windowHandle = CreateWindowW(windowClassName.c_str(), title.c_str(), WS_OVERLAPPEDWINDOW,
								 CW_USEDEFAULT, 0, width, height, nullptr, nullptr, (HINSTANCE)hinst, nullptr);

	if (!windowHandle)
	{
		logger->WriteLine("Error create Win32 Window", "Win32 Window");
		return false;
	}

	ShowWindow((HWND)windowHandle, cmdShow);
	UpdateWindow((HWND)windowHandle);

	return true;
}

int OSWindow::MessageLoop()
{
	MSG message{ 0 };

	if (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessageW(&message);
	}

	if (message.message == WM_QUIT)
	{
		logger->WriteLine("Window is Closed...", "OS Window");
		isClosed = true;
	}

	if (currentEvent != nullptr)
	{
		osEventQueue->AddEvent(currentEvent);
		currentEvent = nullptr;
	}

	return (int)message.wParam;
}

WindowHandle OSWindow::GetWindowHandle()
{
	return windowHandle;
}

Size OSWindow::GetWindowSize()
{
	return Size(height, width);
}

bool OSWindow::shouldClosed()
{
	return isClosed;
}

bool OSWindow::IsEvents()
{
	return osEventQueue->IsEvents();
}

Event* OSWindow::PopEvent()
{
	return osEventQueue->GetEvent();   
} 

void OSWindow::UpdateWindowSize()
{
	RECT rect;
	GetClientRect((HWND)windowHandle, &rect);

	Size newSize = GetSizeFromRect(rect);

	this->height = newSize.height;
	this->width = newSize.width;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	long result = 0;

	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		currentEvent = new Event(nullptr, CloseEvent);
	}
	break;
	case WM_SIZE:
	{
		ResizeEventData* data = new ResizeEventData();

		RECT rect;
		GetClientRect(hWnd, &rect);

		data->newSize = GetSizeFromRect(rect);

		currentEvent = new Event(data, ResizeEvent);
	}
	break;
	case WM_KEYDOWN:
	{
	}
	break;
	case WM_KEYUP:
		break;
	default:
		result = (long)DefWindowProcW(hWnd, message, wParam, lParam);
	}
	return result;
}
