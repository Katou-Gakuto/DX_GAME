#pragma once
#include <string>

namespace DEBUG
{
	static std::string LogFileString;

	void DebugCreateLogFileName();

	void SaveText(std::string logString);
}