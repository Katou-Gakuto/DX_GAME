#pragma once
#include <fstream>
#include <map>
#include <string>
#include <vector>

#ifdef _DEBUG

// デバッグ用
namespace DEBUG
{
	// デバッグ用マップデータ種類
	enum DEBUG_MAP_TYPE
	{
		DEBUG_BASE = 0,
		DEBUG_EFFECT,
		DEBUG_UNDISCOVERED,
		DEBUG_GRAPH,
		DEBUG_3D_MODEL,
	};

	// デバッグ用処理種類
	enum class DEBUG_PROCESS_TYPE
	{
		NONE = -1,
		FUNCTION_CALL,
		TIME,
	};

	// デバッグ用追加ファイル別データ
	struct DEBUG_FILE_DATA
	{
		std::vector<DEBUG_PROCESS_TYPE> debugType;
		
		std::string plusFileName;
	};

	// デバッグ用SaveText関数内データ
	struct DEBUG_SAVE_TEXT_FUNCTION_DATA
	{
		std::string timeString;
	};

	static std::string LogFileString;
	static std::vector<DEBUG_PROCESS_TYPE> LogFileProcess;

	static std::map<int, DEBUG::DEBUG_FILE_DATA> PlusLogFileData;

	static HANDLE DebugProcessHandle;

	/// <summary>デバッグ初期化</summary>
	void DebugInitialization();

	/// <summary>デバッグ出力先を追加する(上書き)</summary>
	void DebugCreateLogFileName(DEBUG_MAP_TYPE debugMapType = DEBUG_MAP_TYPE::DEBUG_BASE, std::string plusFileName = "");

	/// <summary>デバッグ出力情報追加</summary>
	void DebugLogAddData(DEBUG_PROCESS_TYPE debugProcessType, DEBUG_MAP_TYPE debugMapType = DEBUG_MAP_TYPE::DEBUG_BASE);
	
	/// <summary>デバッグ出力情報削除</summary>
	void DebugLogSubData(DEBUG_PROCESS_TYPE debugProcessType, DEBUG_MAP_TYPE debugMapType = DEBUG_MAP_TYPE::DEBUG_BASE);

	/// <summary>文字列をファイルに追加する</summary>
	void SaveText(std::string logString, DEBUG_MAP_TYPE debugMapType = DEBUG_MAP_TYPE::DEBUG_BASE);

	/// <summary>デバッグ種類別の処理</summary>
	void ProcessByDebugType(std::ofstream *file, DEBUG_PROCESS_TYPE debugProcessType, DEBUG_SAVE_TEXT_FUNCTION_DATA debugSaveTextFunctionData);

	/// <summary>関数名を取得</summary>
	/// <returns>関数(ファイル名.行数)/関数(ファイル名.行数)</returns>
	std::string FunctionCallHistoryAcquisition(int deleteNumber = 1);

	/// <summary>時間文字列取得</summary>
	std::string TimeToString();
}

#endif