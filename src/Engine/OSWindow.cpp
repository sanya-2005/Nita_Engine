#include "OSWindow.h"
#include "Log.h"
#include "Win32Utils.h"
#include "EngineCore\Exceptions.h"
#include "Input.h"

#include <windows.h>
#include <string>

using namespace Win32Utils;

static Event* currentEvent = nullptr;

static bool isActive_WndProc = true;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

void OSWindow::Create(void* hinst, int cmdShow, uint height, uint width, std::wstring title)
{
	osEventQueue = new OSEventQueue();

	windowClassName = title + L"Class";

	this->height = height;
	this->width = width;
	this->title = title;
	this->isClosed = false;
    isActive = true;

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
        throw InitializationException("Error register Window class");
	}

	windowHandle = CreateWindowW(windowClassName.c_str(), title.c_str(), WS_OVERLAPPEDWINDOW,
								 CW_USEDEFAULT, 0, width, height, nullptr, nullptr, (HINSTANCE)hinst, nullptr);

	if (!windowHandle)
	{		
        throw InitializationException("Error create Win32 Window");
	}

	ShowWindow((HWND)windowHandle, cmdShow);
	UpdateWindow((HWND)windowHandle);

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

    isActive = isActive_WndProc;

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

bool OSWindow::ShouldClosed()
{
	return isClosed;
}

MousePosition OSWindow::ScreenCoordsToClient(MousePosition screenCoords)
{
    POINT point { (long)screenCoords.x, (long)screenCoords.y };
    
    ScreenToClient((HWND)windowHandle, &point);

    return MousePosition(point.x, point.y);
}

bool OSWindow::IsEvents()
{
	return osEventQueue->IsEvents();
}

Event* OSWindow::PopEvent()
{
	return osEventQueue->GetEvent();   
}
bool OSWindow::IsActive()
{
    return isActive;
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
		//PAINTSTRUCT ps;
		//HDC hdc = BeginPaint(hWnd, &ps);
		//EndPaint(hWnd, &ps);
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
    case WM_MOUSEWHEEL:
    {
        int delta = GET_WHEEL_DELTA_WPARAM(wParam);

        if (delta > 0)
        {
            delta /= delta;
        }
        else if (delta < 0)
        {
            delta /= delta;
            delta *= -1;
        }

        input.SetMouseWheelDelta(delta);
    }
    break;
    case WM_SETFOCUS:
        currentEvent = new Event(nullptr, ActivateWindowEvent);
        break;
    case WM_KILLFOCUS:
        currentEvent = new Event(nullptr, DeactivateWindowEvent);
        break;
    case WM_ACTIVATE:
    {
        int action = LOWORD(wParam);

        if (action == WA_ACTIVE)
        {
            currentEvent = new Event(nullptr, ActivateWindowEvent);
            isActive_WndProc = true;
        }
        else if (action == WA_INACTIVE)
        {
            currentEvent = new Event(nullptr, DeactivateWindowEvent);
            isActive_WndProc = false;
        }
    }
        break;
	default:
		result = (long)DefWindowProcW(hWnd, message, wParam, lParam);
	}
	return result;
}
