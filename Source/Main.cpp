#pragma comment(lib, "winmm.lib")

#include "DxLib.h"

#include "Master.h"

#include "DataManager.h"
#include "EndManager.h"
#include "FadeManager.h"
#include "GameManager.h"
#include "KeyState.h"
#include "LoadingManager.h"
#include "ResourceManager.h"
#include "StopManager.h"
#include "TimeManager.h"

#if _DEBUG
#include "XmlArrange.h"
#endif

// マスター静的メンバ変数初期化
DataManager* Master::mpDataManager = new DataManager();
EndManager* Master::mpEndManager = new EndManager();
FadeManager* Master::mpFadeManager = new FadeManager();
GameManager* Master::mpGameManager = new GameManager();
KeyState* Master::mpKeyState = new KeyState();
LoadingManager* Master::mpLoadingManager = new LoadingManager();
ResourceManager* Master::mpResourceManager = new ResourceManager();
StopManager* Master::mpStopManager = new StopManager();
TimeManager* Master::mpTimeManager = new TimeManager();

// HACK: exeファイルが一段上に隠れるからプロジェクトファイルの場所を変えてリソースのファイル座標を書き換える

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
#if _DEBUG
	// Excel用XMLファイルを生成
	XmlArrange* pXmlArrange = new XmlArrange();
	pXmlArrange->Arrange();
	delete pXmlArrange;
#endif

	// ウインドウモードで起動
	ChangeWindowMode(true);

	// DXライブラリ初期化処理
	if(DxLib_Init() == -1)
	{
		return -1;		// エラーが起きたら直ちに終了
	}

	// TODO: 変更できるようにする
	//SetGraphMode(640, 480, 16);

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
