#pragma once
#include "EngineCore\Types.h"

#include <string>

enum LogLevels
{
	Default = 0,
	Error = 1,
	Warning = 2,
	Info = 3, 
	DetailInfo = 4,
	NoLogs = -1
};

enum LogOutputModes
{
	LogFile = 1,
	Console = 1 << 1
};

class Logger
{
private:
	void* consoleHandle;
	void* fileHandle;

	LogLevels level;
	flag mode;

	bool isInit;
public:
	Logger(uint outputMode);

	void WriteLine(std::string text, std::string title = "Default", LogLevels logLevel = Default);
	void SetMaxLogLevel(LogLevels loglevel);
	void SetLogOutputMode(flag outputMode);

	~Logger();
};

extern Logger* logger;
