#include "../Header/Master.h"

#include "../Header/DataManager.h"
#include "../Header/EndManager.h"
#include "../Header/GameManager.h"
#include "../Header/KeyState.h"
#include "../Header/LoadingManager.h"
#include "../Header/ResourceManager.h"
#include "../Header/TimeManager.h"

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