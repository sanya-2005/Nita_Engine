#include "Log.h"
#include "Win32Utils.h"
#include <windows.h>

Logger::Logger(uint outputMode)
{
	isInit = false;
	level = Default;
	mode = outputMode;

	if (outputMode & LogFile)
	{
		fileHandle = CreateFileW(L"log.txt", GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (fileHandle == INVALID_HANDLE_VALUE)
		{
			Win32Utils::ShowMessageBox(L"Error create log file", L"Fatal Error", Win32Utils::Error);
			isInit = false;
		}
		else
		{
			isInit = true;
		}
	}

	if (outputMode & Console)
	{
		if (AllocConsole())
		{
			consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

			isInit = true;
		}
		else
		{
			isInit = false;
		}
	}

	if (!isInit)
	{
		Win32Utils::ShowMessageBox(L"Error initializating Logger", L"Error", Win32Utils::Error);
	}
}

static std::string LoglevelsToString(LogLevels level)
{
	switch (level)
	{
	case Default:
		return "Default";
		break;
	case Error:
		return "Error";
		break;
	case Warning:
		return "Warning";
		break;
	case Info:
		return "Info";
		break;
	case DetailInfo:
		return "Detail Info";
		break;
	case NoLogs:
	default:
		return "";
		break;
	}
}

void Logger::WriteLine(std::string text, std::string title, LogLevels logLevel)
{
	if (((int)logLevel <= (int)level) && isInit)
	{
		std::string str;
		std::string levelStr = LoglevelsToString(logLevel);

		if (title == "")
		{
			str = text + "\n";
		}
		else
		{
			str = "[" + title + "]" + ":" + levelStr + " - " + text + "\n";
		}

		if (mode & LogFile)
		{
			WriteFile(fileHandle, str.c_str(), sizeof(char) * str.size(), nullptr, nullptr);
		}

		if (mode & Console)
		{
			WriteConsoleA(consoleHandle, str.c_str(), sizeof(char) * str.size(), nullptr, nullptr);
		}
	}
}

void Logger::SetMaxLogLevel(LogLevels loglevel)
{
	level = loglevel;
}

void Logger::SetLogOutputMode(flag outputMode)
{
	mode = outputMode;
}

Logger::~Logger()
{
	if (fileHandle != nullptr)
	{
		CloseHandle(fileHandle);
	}

	if (consoleHandle != nullptr)
	{
		FreeConsole();
	}
}
