#pragma once
#include <string>

namespace DEBUG
{
	static std::string LogFileString = "LogDebug/debug_0.txt";

	static HANDLE DebugProcessHandle;

	/// <summary>デバッグ初期化</summary>
	void DebugInitialization();

	/// <summary>デバッグ出力先を新しいファイルにする</summary>
	void DebugCreateLogFileName();

	/// <summary>文字列をファイルに追加する</summary>
	void SaveText(std::string logString);

	/// <summary>関数名を取得</summary>
	/// <returns>関数(ファイル名.行数)/関数(ファイル名.行数)</returns>
	std::string FunctionCallHistoryAcquisition();
}