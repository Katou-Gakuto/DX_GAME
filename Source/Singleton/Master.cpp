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

// マスター所持物全削除処理
void Master::AllDelete()
{
	// 終了処理
	mpFadeManager->Finailize();
	mpGameManager->Finailize();
	mpImguiManager->Finalize();
	mpResourceManager->Finailize();
	mpTelopManager->Finalize();
	
	// 削除
	delete mpDataManager;
	delete mpEndManager;
	delete mpFadeManager;
	delete mpGameManager;
	delete mpImguiManager;
	delete mpKeyState;
	delete mpLoadingManager;
	delete mpResourceManager;
	delete mpStopManager;
	delete mpTelopManager;
	delete mpTimeManager;
}