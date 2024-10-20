#pragma once
#include "utils.h"
#include <string>

typedef struct tagRECT RECT;

namespace Win32Utils
{
	Size GetSizeFromRect(RECT& rect);
	
	enum MessageBoxType 
	{
		Normal = 0x00000000L,
		Error = 0x00000010L
	};

	void ShowMessageBox(std::wstring text, std::wstring title, MessageBoxType type = Normal);
}