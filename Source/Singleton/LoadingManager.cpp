#include "BitFlag.h"

#include "DxLib.h"

#include "Master.h"

#include "EndManager.h"
#include "GameManager.h"
#include "LoadingManager.h"
#include "SceneManager.h"

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
	if (mullLoadingFlag.GetFlag(LOADING_NUMBER::SCENE) && !Master::mpEndManager->GetBitEndflag().Bool())
	{
		SetUseASyncLoadFlag(TRUE);

		Master::mpGameManager->GetSceneManager()->NextScene();

		while ((GetASyncLoadNum() != 0) && !Master::mpEndManager->EndFlag())
		{
		}
		if (GetASyncLoadNum() != 0)
		{
			Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::LOADING_FLAG);
		}

		SetUseASyncLoadFlag(FALSE);
		mullLoadingFlag.DisableFlag(LOADING_NUMBER::SCENE);
	}
}