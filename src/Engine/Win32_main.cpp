#include "NitaEngine.h"
#include "Log.h"
#include "Math/Matrix.h"
#include "EngineCore/Exceptions.h"

Logger* logger;
NitaEngine* engine;

int APIENTRY wWinMain(HINSTANCE hInstance,
                      HINSTANCE hPrevInstance,
                      LPWSTR    lpCmdLine,
                      int       nCmdShow)
{
    logger = new Logger(LogFile | Console);

#ifdef _DEBUG
    logger->SetMaxLogLevel(DetailInfo);
#endif

    std::wstring title = L"Nita Engine";

    try
    {
        OSWindow* appWindow = new OSWindow();

        appWindow->Create(hInstance, nCmdShow, 880, 1620, title);

        engine = new NitaEngine();


        engine->Init(*appWindow);
    }
    catch (InitializationException& ex)
    {
        logger->WriteLine(ex.Message());
        return -1;
    }

    Math::Matrix4f mat;

    for (int i = 0; i < 4; i++)
    {
        mat[i][i] = 1;
    }

    std::string buff;
    float* p = mat.Pointer();

    for (int i = 0; i < 16; i++)
    {
        buff.append(std::to_string(*p));
        buff.append(" ");

        if (((i + 1) % 4) == 0)
        {
            buff.append("\n");
        }

        p++;
    }
    
    logger->WriteLine(buff, "");

    Math::Vector2f vec1;
    Math::Vector2f vec2;

    vec1[0] = 1;
    vec1[1] = 2;

    vec2[0] = 4;
    vec2[1] = 3;

    vec1 = vec1 + vec2;

    int result = -1;

    result = engine->Run();

    engine->Destroy();

    return result;
}
