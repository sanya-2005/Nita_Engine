#include "NitaEngine.h"
#include "Log.h"
#include "BuildInfo.h"
#include "Event.h"
#include "EngineCore/Exceptions.h"
#include "EngineCore/SystemTime.h"
#include "EngineCore/Wait.h"
#include "Input.h"

using namespace DirectX;
using namespace std;

void NitaEngine::Init(OSWindow& osWindow)
{
	logger->WriteLine(appName, "");
	logger->WriteLine("Version: " + version, "");
	logger->WriteLine("Build Type: " + buildType, "");

    SystemDate date = SystemTime::GetLocalDate();

	string minutes = to_string(date.minute);

	if (minutes.size() == 1)
	{
		minutes = "0" + minutes;
	}

	logger->WriteLine("Run date: " + to_string(date.hour) + ":" + minutes + "\\" + to_string(date.day) +
			"\\" + to_string(date.month) + "\\" + to_string(date.year), "");

	logger->WriteLine("--------------------------", "");

	this->mainWindow = &osWindow;

    FPS = 60;

    isStopped = false;

    GPU::stats = new GPU::GPUResourceStatistic();

	RenderEngine* renderEngine = new RenderEngine();

	if (!renderEngine->Init(osWindow))
	{
		logger->WriteLine("Error initializating Render Engine", "Nita Engine");

        throw InitializationException("Error initializating Render Engine");
	}

	this->renderEngine = renderEngine;

	level = new Level();

	Object* obj_1 = new Object();
	obj_1->Move({ 1.0, 2.0, 1.0 });

	Mesh* mesh_1 = new Mesh({ 
    { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(-0.5774f, -0.5774f, -0.5774f),  XMFLOAT2(0.0f, 0.0f) },
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

    //input.Capture(osWindow);
}

int NitaEngine::Run()
{
	ulong previousTime = SystemTime::GetTime();

	const double maxTimeStep = 1.0 / FPS;

	int result = 0;
	float angle = 30.0f;

	while (!mainWindow->ShouldClosed() && !isStopped)
	{
		ulong currentTime = SystemTime::GetTime();

		double deltaTime = (currentTime - previousTime) / 1000.0;

		if (deltaTime < maxTimeStep) 
		{
			ulong sleepTime = (ulong)((maxTimeStep - deltaTime) * 1000);

            Wait(sleepTime);
		}

        previousTime = currentTime;

        result = mainWindow->MessageLoop();

        input.Update();
        
		if (mainWindow->IsEvents())
		{
			Event* event = mainWindow->PopEvent();

			EventTypes type = event->GetEventType();
			
			switch (type)
			{
			case ResizeEvent:
			{
				logger->WriteLine("ResizeEvent is handled", "Event System");

				ResizeEventData* resizeData = (ResizeEventData*)event->GetEventData();

				mainWindow->UpdateWindowSize();
				renderEngine->Resize(resizeData->newSize);
			}
			break;
			case CloseEvent:
				logger->WriteLine("CloseEvent is handled", "Event System");
				break;
            case ActivateWindowEvent:
                isActive = true;
                break;
            case DeactivateWindowEvent:
                isActive = false;
                break;
			}
            
			delete event;
		}
        else
        {
            if (!isActive)
            {
                continue;
            }

            if (input.IsKeyPressed(A))
            {
                renderEngine->data->viewMatrix *= XMMatrixTranslation(0.25, 0, 0);
            }
            if (input.IsKeyPressed(D))
            {
                renderEngine->data->viewMatrix *= XMMatrixTranslation(-0.25, 0, 0);
            }
            if (input.IsKeyPressed(W))
            {
                renderEngine->data->viewMatrix *= XMMatrixTranslation(0, 0, -0.25);
            }
            if (input.IsKeyPressed(S))
            {
                renderEngine->data->viewMatrix *= XMMatrixTranslation(0, 0, 0.25);
            }
            if (input.IsKeyPressed(Esc))
            {
                Stop();
            }

            for (Object* obj : level->GetObjectsList())
            {
                obj->Rotate(angle * (float)deltaTime);
            }

            renderEngine->Update();
            renderEngine->Render();
        }
	}

	return result;
}

void NitaEngine::Stop()
{
    isStopped = true;
}

void NitaEngine::Destroy()
{
	logger->WriteLine("Destroy Engine", "Nita Engine");
    level->Destroy();

	renderEngine->Destroy();

	delete renderEngine;
    delete GPU::stats;
	delete mainWindow;
}
