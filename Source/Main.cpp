#pragma comment(lib, "winmm.lib")

#include "DxLib.h"

#include "Master.h"

#include "DataManager.h"
#include "EndManager.h"
#include "GameManager.h"
#include "KeyState.h"
#include "LoadingManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"

/**
* @file 
* @author 
* @date 
*
* @details 
* @note リファレンス https://dxlib.xsrv.jp/dxfunc.html
*/

DataManager* Master::mpDataManager = new DataManager();
EndManager* Master::mpEndManager = new EndManager();
GameManager* Master::mpGameManager = new GameManager();
KeyState* Master::mpKeyState = new KeyState();
LoadingManager* Master::mpLoadingManager = new LoadingManager();
ResourceManager* Master::mpResourceManager = new ResourceManager();
TimeManager* Master::mpTimeManager = new TimeManager();

/**
* @fn WinMain
* @brief Main関数
* @param[in] HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow
* @return int 0 正常終了／-1 エラー
* @details Main関数
*/









/// <summary>
/// 
/// </summary>
/// <param name="hInstance"></param>
/// <param name="hPrevInstance"></param>
/// <param name="lpCmdLine"></param>
/// <param name="nCmdShow"></param>
/// <returns></returns>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	// ウインドウモードで起動
	ChangeWindowMode(true);

	// DXライブラリ初期化処理
	if(DxLib_Init() == -1)
	{
		return -1;		// エラーが起きたら直ちに終了
	}

	// 初期化
	Master::mpGameManager->Initilize();

	// ループ
	while (!Master::mpEndManager->EndFlag()) {
		
		if (Master::mpLoadingManager->GetLoadingFlag())
		{
			// 読み込み
			Master::mpLoadingManager->Loading();
		}
		else
		{
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
	}

	// 削除
	Master::AllDelete();

	// DXライブラリ使用の終了処理
	DxLib_End();

	// ソフトの終了
	return 0;
}
