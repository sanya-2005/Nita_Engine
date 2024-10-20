#include "NitaEngine.h"
#include "Win32Utils.h"
#include "Log.h"
#include "Matrix.h"

#include <exception>
using namespace Win32Utils;

Logger* logger;
NitaEngine* engine;

int APIENTRY wWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPWSTR    lpCmdLine,
                     int       nCmdShow)
{    
    bool isInit = true;

    logger = new Logger(LogFile | Console);
    logger->SetMaxLogLevel(DetailInfo);

    OSWindow* appWindow = new OSWindow();
    std::wstring title = L"Nita Engine";

    if (!appWindow->Create(hInstance, nCmdShow, 880, 1620, title))
    {
        ShowMessageBox(L"Error create OS Window", L"Fatal Error", MessageBoxType::Error);
        isInit = false;
    }

    try
    {
        engine = new NitaEngine();

        if (!engine->Init(*appWindow))
        {
            ShowMessageBox(L"Error Init Engine", L"Fatal Error", MessageBoxType::Error);
            isInit = false;
        }
    }
    catch (std::exception& ex)
    {
        logger->WriteLine("ERROR", "Exception");
        logger->WriteLine(ex.what());
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

    if (isInit)
    {
        result = engine->Run();
    }

    engine->Destroy();

    return result;
}
