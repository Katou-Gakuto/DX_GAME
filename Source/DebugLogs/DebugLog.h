#pragma once
#include <fstream>
#include <map>
#include <string>
#include <vector>

#ifdef _DEBUG

// デバッグ用
namespace DEBUG
{
	// デバッグ用マップデータ種類	(追加自由)
	enum DEBUG_MAP_TYPE
	{
		DEBUG_BASE = 0,
		DEBUG_EFFECT,
		DEBUG_UNDISCOVERED,
		DEBUG_GRAPH,
		DEBUG_3D_MODEL,
		DEBUG_SCENE_TITLE,
	};

	// デバッグ用処理種類
	enum class DEBUG_PROCESS_TYPE
	{
		NONE = -1,
		FUNCTION_CALL,		// 関数呼び出し含む
		TIME,				// 時間描画
    	ALL_FILE_OUTPUT,	// 全デバッグファイルに出力
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
		std::string logString;
		int debugMapType;
	};

	static bool DebugOutputFileFlag;

	static std::string LogFileString;
	static std::vector<DEBUG_PROCESS_TYPE> LogFileProcess;

	static std::map<int, DEBUG::DEBUG_FILE_DATA> PlusLogFileData;

	static HANDLE DebugProcessHandle;

	/// <summary>デバッグ初期化</summary>
	void DebugInitialization(bool debugOutputFlag);

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


/*------------------------------------------------------------【見本】------------------------------------------------------------*/

// 初期設定は【LogDebug/debug_0.txt】にデバッグ情報出力
// 
//【初期設定】
//#ifdef _DEBUG
//    DEBUG::DebugInitialization(true);
//	
//    // デバッグ初期化
//    DEBUG::DebugInitialization(true/*【デバッグファイルを生成するフラグ】*/);
//	
//    // デバッグテキストの出力先を新しいファイルにする
//    {
//　　　　// 基本ファイルをデフォルトから新しいファイルにする (LogDebug/debug_/*【ここの数字が変わる】*/.txt)
//        EBUG::DebugCreateLogFileName();
//        // 基本ファイル出力時追加出力設定
//        DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::FUNCTION_CALL);
//        // 基本ファイル出力時追加出力設定
//        DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::TIME);
// 
//        // 全ファイル  追加出力設定
//        {
//            /**/
//　　　　    // 出力先ファイル情報追加
//            DEBUG::DebugCreateLogFileName(DEBUG::DEBUG_MAP_TYPE::DEBUG_SCENE_TITLE/*【タグ】*/, "_title"/*【追加ファイル名】*/);
//            // 追加ファイル出力時追加出力設定
//            DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::ALL_FILE_OUTPUT/*【追加出力設定】*/, DEBUG::DEBUG_MAP_TYPE::DEBUG_SCENE_TITLE/*【タグ】*/);//*/
//            
//        }
//
//        // 関数呼び出しと時間  追加出力設定
//        {
//            /**/
//　　　　    // 出力先ファイル情報追加
//            DEBUG::DebugCreateLogFileName(DEBUG::DEBUG_MAP_TYPE::DEBUG_EFFECT, "_effect");
//            // 追加ファイル出力時追加出力設定
//            DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::FUNCTION_CALL, DEBUG::DEBUG_MAP_TYPE::DEBUG_EFFECT);
//            // 追加ファイル出力時追加出力設定
//            DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::TIME, DEBUG::DEBUG_MAP_TYPE::DEBUG_EFFECT);//*/
//        }
// 
//        // 何も追加しないことでつなげて見せる
//        {
//            /**/
//　　　　    // 出力先ファイル情報追加
//            DEBUG::DebugCreateLogFileName(DEBUG::DEBUG_MAP_TYPE::DEBUG_UNDISCOVERED, "_graph");//*/
//        }
//
//        // つなげ対象
//        {
//            /**/
//　　　　    // 出力先ファイル情報追加
//            DEBUG::DebugCreateLogFileName(DEBUG::DEBUG_MAP_TYPE::DEBUG_GRAPH, "_graph");
//            // 追加ファイル出力時追加出力設定
//            DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::FUNCTION_CALL, DEBUG::DEBUG_MAP_TYPE::DEBUG_GRAPH);
//            // 追加ファイル出力時追加出力設定
//            DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::TIME, DEBUG::DEBUG_MAP_TYPE::DEBUG_GRAPH);//*/
//        }
//
//        // 除外
//        {
//            /*/
//　　　　    // 出力先ファイル情報追加
//            DEBUG::DebugCreateLogFileName(DEBUG::DEBUG_MAP_TYPE::DEBUG_3D_MODEL, "_3d_model");
//            // 追加ファイル出力時追加出力設定
//            DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::FUNCTION_CALL, DEBUG::DEBUG_MAP_TYPE::DEBUG_3D_MODEL);
//            // 追加ファイル出力時追加出力設定
//            DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::TIME, DEBUG::DEBUG_MAP_TYPE::DEBUG_3D_MODEL);//*/
//        }
//    }
//#endif
//
// 
// 
//【使用例】
//    int test = 0;
// 
//#ifdef _DEBUG
//    // 基本ファイルにのみ出力
//    DEBUG::SaveText(std::to_string(test) + "\n");
//    // 基本ファイルと_effect付きファイルに出力
//    DEBUG::SaveText(std::to_string(test) + "\n", DEBUG::DEBUG_MAP_TYPE::DEBUG_EFFECT);
//#endif
// 
//    if (test == 0)
//    {
//#ifdef _DEBUG
//        DEBUG::SaveText(std::to_string(test) + " : (o_ _)", DEBUG::DEBUG_MAP_TYPE::DEBUG_UNDISCOVERED);
//#endif
//    }
//#ifdef _DEBUG
//    DEBUG::SaveText("ﾉ彡☆\n", DEBUG::DEBUG_MAP_TYPE::DEBUG_GRAPH);
// 
//    DEBUG::SaveText("除外しているなら基本ファイルのみ\n", DEBUG::DEBUG_MAP_TYPE::DEBUG_3D_MODEL);
//#endif
//	
//    return 0;
//}