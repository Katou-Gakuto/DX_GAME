#pragma comment(lib, "winmm.lib")

#include "DxLib.h"

#include "Master.h"

#include "DataManager.h"
#include "DrawManager.h"
#include "EndManager.h"
#include "FadeManager.h"
#include "GameManager.h"
#include "ImguiManager.h"
#include "KeyState.h"
#include "LoadingManager.h"
#include "ResourceManager.h"
#include "StageDataManager.h"
#include "StopManager.h"
#include "TelopManager.h"
#include "TimeManager.h"

#ifdef _DEBUG
#include "XmlArrange.h"

#include "DebugLogs/DebugLog.h"
#endif

#include "SoundManager.h"

// マスター静的メンバ変数初期化
DataManager* Master::mpDataManager = new DataManager();
DrawManager* Master::mpDrawManager = new DrawManager();
EndManager* Master::mpEndManager = new EndManager();
FadeManager* Master::mpFadeManager = new FadeManager();
GameManager* Master::mpGameManager = new GameManager();
ImguiManager* Master::mpImguiManager = new ImguiManager();
KeyState* Master::mpKeyState = new KeyState();
LoadingManager* Master::mpLoadingManager = new LoadingManager();
ResourceManager* Master::mpResourceManager = new ResourceManager();
StageDataManager* Master::mpStageDataManager = new StageDataManager();
StopManager* Master::mpStopManager = new StopManager();
TelopManager* Master::mpTelopManager = new TelopManager();
TimeManager* Master::mpTimeManager = new TimeManager();

SoundManager* Master::mpSoundManager = new SoundManager();

/// <summary>
/// メイン
/// </summary>
/// <param name="hInstance">HINSTANCE</param>
/// <param name="hPrevInstance">HINSTANCE</param>
/// <param name="lpCmdLine">LPSTR</param>
/// <param name="nCmdShow">int</param>
/// <returns>int</returns>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
	// Excel用XMLファイルを生成
	XmlArrange* pXmlArrange = new XmlArrange();
	pXmlArrange->Arrange();
	delete pXmlArrange;
	
	// デバッグ初期化
	DEBUG::DebugInitialization(/**/true/*/false/**/);
	
	// デバッグテキストの出力先を新しいファイルにする
	{
		DEBUG::DebugCreateLogFileName();
		DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::FUNCTION_CALL);
		DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::TIME);

		DEBUG::DebugCreateLogFileName(DEBUG::DEBUG_MAP_TYPE::DEBUG_UNDISCOVERED, "_graph");

		DEBUG::DebugCreateLogFileName(DEBUG::DEBUG_MAP_TYPE::DEBUG_SCENE_TITLE, "_title");
		DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::ALL_FILE_OUTPUT, DEBUG::DEBUG_MAP_TYPE::DEBUG_SCENE_TITLE);
/**/
		DEBUG::DebugCreateLogFileName(DEBUG::DEBUG_MAP_TYPE::DEBUG_EFFECT, "_effect");
		DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::FUNCTION_CALL, DEBUG::DEBUG_MAP_TYPE::DEBUG_EFFECT);
		DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::TIME, DEBUG::DEBUG_MAP_TYPE::DEBUG_EFFECT);//*/
/**/
		DEBUG::DebugCreateLogFileName(DEBUG::DEBUG_MAP_TYPE::DEBUG_GRAPH, "_graph");
		DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::FUNCTION_CALL, DEBUG::DEBUG_MAP_TYPE::DEBUG_GRAPH);
		DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::TIME, DEBUG::DEBUG_MAP_TYPE::DEBUG_GRAPH);//*/
/**/
		DEBUG::DebugCreateLogFileName(DEBUG::DEBUG_MAP_TYPE::DEBUG_3D_MODEL, "_3d_model");
		DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::FUNCTION_CALL, DEBUG::DEBUG_MAP_TYPE::DEBUG_3D_MODEL);
		DEBUG::DebugLogAddData(DEBUG::DEBUG_PROCESS_TYPE::TIME, DEBUG::DEBUG_MAP_TYPE::DEBUG_3D_MODEL);//*/

/*/
		DEBUG::DebugCreateLogFileName(DEBUG::DEBUG_MAP_TYPE::DEBUG_GAME_MANAGER_WND_PROC, "_GameManager");//*/
	}
#endif

#ifdef _DEBUG
	Master::mpImguiManager->DxInit();
#endif

	// DxLib_Init前初期化
	Master::mpGameManager->DxLib_PreInit();

	// DXライブラリ初期化処理
	if(DxLib_Init() == -1)
	{
		return -1;		// エラーが起きたら直ちに終了
	}

#ifdef _DEBUG
	Master::mpImguiManager->Initilize();
#endif

	// 初期化
	Master::mpGameManager->Initilize();

	Master::mpSoundManager->Initilize();

	// ループ
	while (!Master::mpEndManager->EndFlag()) {

		// ローディング処理
		if (Master::mpLoadingManager->GetLoadingFlag() && !Master::mpFadeManager->GetFadeFlag())
		{
			// 読み込み
			Master::mpLoadingManager->Loading();
		}

		
		// メイン処理
		if (Master::mpTimeManager->GetNextUpdateFlag())
		{

#ifdef _DEBUG
			Master::mpImguiManager->Update();
#endif
			// 更新
			Master::mpGameManager->Update();

			// 必要であれば削除する
			Master::mpGameManager->DeleteAllIfNeeded();

			// 描画
			Master::mpGameManager->Draw();
		}
	}

	// 削除
	Master::AllDelete();

	// DXライブラリ使用の終了処理
	DxLib_End();

	// ソフトの終了
	return 0;
}
