#pragma comment(lib, "winmm.lib")

#include "DxLib.h"

#include "Master.h"

#include "DataManager.h"
#include "EndManager.h"
#include "FadeManager.h"
#include "GameManager.h"
#if _DEBUG
#include "ImguiManager.h"
#endif
#include "KeyState.h"
#include "LoadingManager.h"
#include "ResourceManager.h"
#include "StopManager.h"
#include "TelopManager.h"
#include "TimeManager.h"

#if _DEBUG
#include "XmlArrange.h"
#endif

// マスター静的メンバ変数初期化
DataManager* Master::mpDataManager = new DataManager();
EndManager* Master::mpEndManager = new EndManager();
FadeManager* Master::mpFadeManager = new FadeManager();
GameManager* Master::mpGameManager = new GameManager();
#if _DEBUG
ImguiManager* Master::mpImguiManager = new ImguiManager();
#endif
KeyState* Master::mpKeyState = new KeyState();
LoadingManager* Master::mpLoadingManager = new LoadingManager();
ResourceManager* Master::mpResourceManager = new ResourceManager();
StopManager* Master::mpStopManager = new StopManager();
TelopManager* Master::mpTelopManager = new TelopManager();
TimeManager* Master::mpTimeManager = new TimeManager();


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	//switch (msg)
	//{
	//case WM_CLOSE:
	//	break;

	//case WM_DESTROY:
	//	PostQuitMessage(0);
	//	return 0;
	//}

	//return DefWindowProc(hWnd, msg, wp, lp);

	return 0;

	/*
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);

	// メッセージ処理はDxLibで行っているようだ

	return 0;
}
	*/
}

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
#if _DEBUG && false
	// Excel用XMLファイルを生成
	XmlArrange* pXmlArrange = new XmlArrange();
	pXmlArrange->Arrange();
	delete pXmlArrange;
#endif

	// ウインドウモードで起動
	ChangeWindowMode(true);

	// DirectX11を使用するようにする
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// TODO: 変更できるようにする
	SetGraphMode(800, 600, 16);

#if _DEBUG
	DxLib::SetHookWinProc(WndProc);
	DxLib::SetAlwaysRunFlag(true);
#endif

	// DXライブラリ初期化処理
	if(DxLib_Init() == -1)
	{
		return -1;		// エラーが起きたら直ちに終了
	}

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
