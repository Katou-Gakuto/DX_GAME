#include "../Header/BitFlag.h"

#include "DxLib.h"

#include "../Header/Master.h"

#include "../Header/GamaManager.h"
#include "../Header/LoadingManager.h"
#include "../Header/SceneManager.h"

LoadingManager::LoadingManager()
: mullLoadingFlag(BIT_FLAG<unsigned long long>())
{
}
LoadingManager::~LoadingManager()
{
}

//ローディング
void LoadingManager::Loading()
{
	if (mullLoadingFlag.GetFlag(LOADING_NUMBER::SCENE))
	{
		SetUseASyncLoadFlag(TRUE);

		Master::mpGameManager->GetSceneManager()->NextScene();

		while (GetASyncLoadNum() != 0)
		{
		}

		SetUseASyncLoadFlag(FALSE);
		mullLoadingFlag.DisableFlag(LOADING_NUMBER::SCENE);
	}
}