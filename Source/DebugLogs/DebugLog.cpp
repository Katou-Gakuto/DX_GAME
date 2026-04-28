#include <windows.h>

#include <dbghelp.h>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>

#include "DebugLog.h"



#pragma comment(lib, "dbghelp.lib")

// デバッグ初期化
void DEBUG::DebugInitialization()
{
    DEBUG::DebugProcessHandle = GetCurrentProcess();
    SymInitialize(DEBUG::DebugProcessHandle, NULL, TRUE);
    SymSetOptions(SYMOPT_LOAD_LINES);
}

// デバッグ出力先を新しいファイルにする
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

// 文字列をファイルに追加する
void DEBUG::SaveText(std::string logString)
{
    std::ofstream file(DEBUG::LogFileString, std::ios::app);

    if (!file) {
        return;
    }

    file << logString;
}

// 関数名を取得
std::string DEBUG::FunctionCallHistoryAcquisition()
{
    // スタックフレームから関数名取得
    void* stack[50];
    USHORT stackFrames = CaptureStackBackTrace(0, 50, stack, NULL);

    /*---------- 変数宣言 ----------*/
    SYMBOL_INFO* symbol =
        (SYMBOL_INFO*)calloc(sizeof(SYMBOL_INFO) + 256, 1);

    symbol->MaxNameLen = 255;
    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

    IMAGEHLP_LINE64 fileDataLine;
    DWORD displacement = 0;
    fileDataLine.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

    // 文字列取得用宣言
    std::string functionCallHistoryString;
    /*------------------------------*/

    // 関数名などに変換(この関数を抜いて処理する)
    for (USHORT i = 1; i < stackFrames; i++)
    {
        DWORD64 address = (DWORD64)stack[i];
        std::ostringstream oneFunctionCallHistoryString;

        // 関数名
        if (SymFromAddr(DEBUG::DebugProcessHandle, address, 0, symbol))
        {
            oneFunctionCallHistoryString << symbol->Name << "(";
        }
        else
        {
            oneFunctionCallHistoryString << "unknown(";
        }

        // ファイル名&行数
        if (SymGetLineFromAddr64(DEBUG::DebugProcessHandle, address, &displacement, &fileDataLine))
        {
            std::string fileName = fileDataLine.FileName;
            size_t fileNamePos = fileName.find_last_of("\\/");

            if (fileNamePos != std::string::npos)
            {
                fileName = fileName.substr(fileNamePos + 1);
            }

            oneFunctionCallHistoryString << fileName << ":" << fileDataLine.LineNumber << ") -> ";
        }
        else
        {
            oneFunctionCallHistoryString << ":) -> ";
        }
        functionCallHistoryString = oneFunctionCallHistoryString.str() + functionCallHistoryString;

        // メインまで行ったら終了
        if (!std::strcmp(symbol->Name, "WinMain") || !std::strcmp(symbol->Name, "main"))
        {
            break;
        }
    }

    // リソース解放
    free(symbol);

    // 関数名たちを返す
    return "\n    " + functionCallHistoryString;
}