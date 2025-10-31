#include "Master.h"

#include "DataManager.h"
#include "EndManager.h"
#include "GameManager.h"
#include "KeyState.h"
#include "LoadingManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"

// マスター所持物全削除処理
void Master::AllDelete()
{
	// 終了処理
	mpGameManager->Finailize();
	mpResourceManager->Finailize();
	
	// 削除
	delete mpDataManager;
	delete mpEndManager;
	delete mpGameManager;
	delete mpKeyState;
	delete mpLoadingManager;
	delete mpResourceManager;
	delete mpTimeManager;
}