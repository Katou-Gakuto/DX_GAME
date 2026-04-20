#pragma once
#include <string>

namespace DEBUG
{
	static std::string LogFileString = "LogDebug/debug_0.txt";

	void DebugCreateLogFileName();

	void SaveText(std::string logString);
}