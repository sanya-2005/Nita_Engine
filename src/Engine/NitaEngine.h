#pragma once
#include "OSWindow.h"
#include "RenderEngine.h"
#include "NonCopyable.h"
#include "Level.h"

/*
* Nita Engine (кодовое имя: D3D Engine)
*/
class NitaEngine : NonCopyable
{
private:
	OSWindow* mainWindow;
	RenderEngine* renderEngine;
	Level* level;

    bool isStopped;

    bool isActive;

    int FPS;

public:
	void Init(OSWindow& osWindow);
	int Run();
    void Stop();
	void Destroy();
};