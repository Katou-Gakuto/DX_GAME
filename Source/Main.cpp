#pragma comment(lib, "winmm.lib")

#include "DxLib.h"

#include "Master.h"

#include "DataManager.h"
#include "EndManager.h"
#include "FadeManager.h"
#include "GameManager.h"
#include "ImguiManager.h"
#include "KeyState.h"
#include "LoadingManager.h"
#include "ResourceManager.h"
#include "StopManager.h"
#include "TelopManager.h"
#include "TimeManager.h"

#ifdef _DEBUG
#include "XmlArrange.h"
#endif

// マスター静的メンバ変数初期化
DataManager* Master::mpDataManager = new DataManager();
EndManager* Master::mpEndManager = new EndManager();
FadeManager* Master::mpFadeManager = new FadeManager();
GameManager* Master::mpGameManager = new GameManager();
ImguiManager* Master::mpImguiManager = new ImguiManager();
KeyState* Master::mpKeyState = new KeyState();
LoadingManager* Master::mpLoadingManager = new LoadingManager();
ResourceManager* Master::mpResourceManager = new ResourceManager();
StopManager* Master::mpStopManager = new StopManager();
TelopManager* Master::mpTelopManager = new TelopManager();
TimeManager* Master::mpTimeManager = new TimeManager();

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
#ifdef _DEBUG && true
	// Excel用XMLファイルを生成
	XmlArrange* pXmlArrange = new XmlArrange();
	pXmlArrange->Arrange();
	delete pXmlArrange;
#endif

#ifndef _DEBUG
	// log.txtを生成しない
	SetOutApplicationLogValidFlag(FALSE);
#endif

	// ウインドウモードで起動
	ChangeWindowMode(true);

	// DirectX11を使用するようにする
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// TODO: 変更できるようにする
	SetGraphMode(1280, 960, 32);

#ifdef _DEBUG
	Master::mpImguiManager->DxInit();
#endif

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
