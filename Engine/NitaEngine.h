#pragma once
#include "OSWindow.h"
#include "RenderEngine.h"
#include "INonCopyable.h"
#include "Level.h"

#include <string>

/*
* Nita Engine (кодовое имя: D3D Engine)
*/
class NitaEngine : INonCopyable
{
private:
	OSWindow* osWindow;
	RenderEngine* renderEngine;
	Level* level;

public:
	bool Init(OSWindow& osWindow);
	int Run();
	void Destroy();
};