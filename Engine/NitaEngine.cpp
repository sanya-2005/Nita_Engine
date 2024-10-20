#include "NitaEngine.h"
#include "Log.h"
#include "Win32Utils.h"
#include "BuildInfo.h"
#include "Event.h"

#include <windows.h>

using namespace DirectX;
using namespace std;

bool NitaEngine::Init(OSWindow& osWindow)
{
	logger->WriteLine(appName, "");
	logger->WriteLine("Version: " + version, "");
	logger->WriteLine("Build Type: " + buildType, "");

	SYSTEMTIME time;

	GetLocalTime(&time);

	string minutes = to_string(time.wMinute);

	if (minutes.size() == 1)
	{
		minutes = "0" + minutes;
	}

	logger->WriteLine("Run date: " + to_string(time.wHour) + ":" + minutes + "\\" + to_string(time.wDay) +
			"\\" + to_string(time.wMonth) + "\\" + to_string(time.wYear), "");

	logger->WriteLine("--------------------------", "");

	this->osWindow = &osWindow;

	RenderEngine* renderEngine = new RenderEngine();

	if (!renderEngine->Init(osWindow))
	{
		logger->WriteLine("Error initializating Render Engine", "Nita Engine");
		return false;
	}

	this->renderEngine = renderEngine;

	level = new Level();

	Object* obj_1 = new Object();
	obj_1->Move({ 1.0, 2.0, 1.0 });

	Mesh* mesh_1 = new Mesh({ { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(-0.5774f, -0.5774f, -0.5774f),  XMFLOAT2(0.0f, 0.0f) },
	{ XMFLOAT3(-1.0f,  1.0f, -1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT3(-0.5774f, 0.5774f, -0.5774f), XMFLOAT2(1.0f, 0.0f) },
	{ XMFLOAT3(1.0f,  1.0f, -1.0f), XMFLOAT3(1.0f, 1.0f, 0.0f), XMFLOAT3(-0.5774f, 0.5774f, 0.5774f), XMFLOAT2(0.0f, 1.0f) },
	{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT3(0.5774f, -0.5774f, -0.5774f), XMFLOAT2(1.0f, 1.0f) },
	{ XMFLOAT3(-1.0f, -1.0f,  1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT3(-0.5774f, -0.5774f, 0.5774f), XMFLOAT2(0.0f, 0.0f) },
	{ XMFLOAT3(-1.0f,  1.0f,  1.0f), XMFLOAT3(0.0f, 1.0f, 1.0f), XMFLOAT3(-0.5774f, 0.5774f, 0.5774f), XMFLOAT2(1.0f, 0.0f) },
	{ XMFLOAT3(1.0f,  1.0f,  1.0f), XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(0.5774f, 0.5774f, 0.5774f), XMFLOAT2(0.0f, 1.0f) },
	{ XMFLOAT3(1.0f, -1.0f,  1.0f), XMFLOAT3(1.0f, 0.0f, 1.0f), XMFLOAT3(0.5774f, -0.5774f, 0.5774f), XMFLOAT2(1.0f, 1.0f) }
							});
	
	mesh_1->AddIndices({
	0, 1, 2, 0, 2, 3,
	4, 6, 5, 4, 7, 6,
	4, 5, 1, 4, 1, 0,
	3, 2, 6, 3, 6, 7,
	1, 5, 6, 1, 6, 2,
	4, 0, 3, 4, 3, 7
					   });

	obj_1->SetMesh(mesh_1);
	level->AddObject(*obj_1);

	Object* obj_2 = new Object();

	Mesh* mesh_2 = new Mesh(*mesh_1);

	obj_2->SetMesh(mesh_2);
	obj_2->Move({ 0.0f, 0.f, 0.f });

	level->AddObject(*obj_2);

	Object* obj_3 = new Object();

	Mesh* mesh_3 = new Mesh(*mesh_1);

	obj_3->SetMesh(mesh_3);
	obj_3->Move({ 2.0f, 0.f, 2.f });

	level->AddObject(*obj_3);

	renderEngine->data->level = level;
	return true;
}

int NitaEngine::Run()
{
	DWORD previousTime = timeGetTime();

	const double targetFramerate = 60.0;
	const double maxTimeStep = 1.0 / targetFramerate;

	int result = 0;
	float angle = 30.0f;

	while (!osWindow->shouldClosed())
	{
		DWORD currentTime = timeGetTime();

		double deltaTime = (currentTime - previousTime) / 1000.0;

		if (deltaTime < maxTimeStep) 
		{
			unsigned long sleepTime = (maxTimeStep - deltaTime) * 1000;
			Sleep(sleepTime);
		}

		previousTime = currentTime;

		result = osWindow->MessageLoop();

		if (osWindow->IsEvents())
		{
			Event* event = osWindow->PopEvent();

			EventTypes type = event->GetEventType();
			
			switch (type)
			{
			case ResizeEvent:
			{
				logger->WriteLine("ResizeEvent is handled", "Event System");

				ResizeEventData* resizeData = (ResizeEventData*)event->GetEventData();

				osWindow->UpdateWindowSize();
				renderEngine->Resize(resizeData->newSize);
			}
			break;
			case CloseEvent:
				logger->WriteLine("CloseEvent is handled", "Event System");
				break;
			}

			delete event;
		}

		for (Object* obj : level->GetObjectsList())
		{
			obj->Rotate(angle * deltaTime);
		}

		renderEngine->Update();
		renderEngine->Render();
	}

	return result;
}

void NitaEngine::Destroy()
{
	logger->WriteLine("Destroy Engine", "Nita Engine");

	renderEngine->Destroy();

	delete renderEngine;
	delete osWindow;
}
