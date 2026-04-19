#include <fstream>
#include <filesystem>
#include <string>

#include "DebugLog.h"


void DEBUG::DebugCreateLogFileName()
{
    int count = 1;
    std::string filename;

    while (true) {
        filename = "LogDebug/debug_" + std::to_string(count) + ".txt";
        if (!std::filesystem::exists(filename)) {
            break;
        }
        count++;
    }

    DEBUG::LogFileString = filename;
}

void DEBUG::SaveText(std::string logString)
{
    std::ofstream file(DEBUG::LogFileString, std::ios::app);

    if (!file) {
        return;
    }

    file << logString << std::endl;
}