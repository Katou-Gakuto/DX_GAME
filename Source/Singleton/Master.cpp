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
#include "TimeManager.h"

// マスター所持物全削除処理
void Master::AllDelete()
{
	// 終了処理
	mpFadeManager->Finailize();
	mpGameManager->Finailize();
#if _DEBUG
	mpImguiManager->Finalize();
#endif
	mpResourceManager->Finailize();
	
	// 削除
	delete mpDataManager;
	delete mpEndManager;
	delete mpFadeManager;
	delete mpGameManager;
#if _DEBUG
	delete mpImguiManager;
#endif
	delete mpKeyState;
	delete mpLoadingManager;
	delete mpResourceManager;
	delete mpStopManager;
	delete mpTimeManager;
}