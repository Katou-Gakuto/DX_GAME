#include "../Header/Master.h"

#include "../Header/DataManager.h"
#include "../Header/EndManager.h"
#include "../Header/FSM.h"
#include "../Header/SceneManager.h"
#include "../Header/ShotCharacter.h"
#include "../Header/StateBase.h"
#include "../Header/StateScene.h"
#include "../Header/TitleUI.h"
#include "../Header/UtilFactorys.h"

/*--------------------------*/
/*【スタートシーンステート】*/
/*--------------------------*/
StartScene::StartScene()
{
	mbStartFlag = false;
	mStateNumber = SCENE::START;
}

void StartScene::OnEnter(SceneManager* sceneManager)
{
	Master::mpEndManager->SetEndFlag(mbStartFlag, END_FLAG_NUMBER::START_SCENE_FLAG);
	mbStartFlag = true;
	sceneManager->SetNextScene(SCENE::TITLE);
}

void StartScene::OnExit(SceneManager* sceneManager)
{
}


/*--------------------------*/
/*【タイトルシーンステート】*/
/*--------------------------*/
TitleScene::TitleScene()
{
	mStateNumber = SCENE::TITLE;
}

void TitleScene::OnEnter(SceneManager* sceneManager)
{
	TitleUI* title = new TitleUI();
	title->Initilize();
	title->SetFsm(UtilFactorys::FSMUIFactory(title, UI_FACTORY_NUMBER::TITLE));
}
void TitleScene::OnExit(SceneManager* sceneManager)
{
}


/*--------------------------*/
/*【町シーンステート】*/
/*--------------------------*/
TownScene::TownScene()
{
	mStateNumber = SCENE::TOWN;
}

void TownScene::OnEnter(SceneManager* sceneManager)
{
	mStateNumber = sceneManager->GetNowScene();
	ShotCharacter* player = new ShotCharacter(true, Master::mpDataManager->GetPlayPlayerData().status);
	player->Initilize();
	switch (sceneManager->GetNowScene())
	{
	case SCENE::TOWN:
		break;
	case SCENE::TOWN_1:
		break;
	case SCENE::TOWN_2:
		break;
	case SCENE::TOWN_3:
		break;
	}
}
void TownScene::OnExit(SceneManager* sceneManager)
{
}


/*----------------------------*/
/*【ダンジョンシーンステート】*/
/*----------------------------*/
DungeonScene::DungeonScene()
{
	mStateNumber = SCENE::DUNGEON;
}

void DungeonScene::OnEnter(SceneManager* sceneManager)
{
	mStateNumber = sceneManager->GetNowScene();
	ShotCharacter* player = new ShotCharacter(true, Master::mpDataManager->GetPlayPlayerData().status);
	player->Initilize();
	switch (sceneManager->GetNowScene())
	{
	case SCENE::DUNGEON:
		break;
	case SCENE::DUNGEON_1:
		break;
	case SCENE::DUNGEON_2:
		break;
	case SCENE::DUNGEON_3:
		break;
	}
}
void DungeonScene::OnExit(SceneManager* sceneManager)
{
}


/*------------------------*/
/*【バトルシーンステート】*/
/*------------------------*/
BattleScene::BattleScene()
{
	mStateNumber = SCENE::BATTLE;
}

void BattleScene::OnEnter(SceneManager* sceneManager)
{
	mStateNumber = sceneManager->GetNowScene();
	ShotCharacter* player = new ShotCharacter(true, Master::mpDataManager->GetPlayPlayerData().status);
	player->Initilize();
	switch (sceneManager->GetNowScene())
	{
	case SCENE::BATTLE :
		break;
	case SCENE::BATTLE_1:
		break;
	case SCENE::BATTLE_2:
		break;
	case SCENE::BATTLE_3:
		break;
	}
}
void BattleScene::OnExit(SceneManager* sceneManager)
{
}


/*--------------------------*/
/*【リザルトシーンステート】*/
/*--------------------------*/
ResultScene::ResultScene()
{
	mStateNumber = SCENE::RESULT;
}

void ResultScene::OnEnter(SceneManager* sceneManager)
{
	mStateNumber = sceneManager->GetNowScene();
	switch (sceneManager->GetNowScene())
	{
	case SCENE::RESULT:
		break;
	}
}
void ResultScene::OnExit(SceneManager* sceneManager)
{
}