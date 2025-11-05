#include "CharacterEnum.h"
#include "CameraData.h"

#include "Master.h"

#include "CameraManager.h"
#include "DataManager.h"
#include "EndManager.h"
#include "FSM.h"
#include "GameManager.h"
#include "ObjectBases.h"
#include "SceneManager.h"
#include "ShotCharacter.h"
#include "StateBase.h"
#include "StateScene.h"
#include "TargetManager.h"
#include "TitleUI.h"
#include "UtilFactorys.h"

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

	// カメラ作成
	{
		CameraData cameraData = CameraData();
		cameraData.cameraMode = CAMERA_MODE::FIXED;
		cameraData.position = VGet(0.0f, 180.0f, -180.0f);
		cameraData.targetPosition = VGet(0.0f, 180.0f, 0.0f);
		cameraData.threeDFlag = true;
		cameraData.SetColor(F4Get(128, 128, 128, 0));
		mnSceneCameraID = Master::mpGameManager->GetCameraManager()->NewCamera(cameraData);
		Master::mpGameManager->GetCameraManager()->SetCameraMode(mnSceneCameraID);
	}
}
void TitleScene::OnExit(SceneManager* sceneManager)
{
	// カメラ削除
	Master::mpGameManager->GetCameraManager()->DeleteCameraData(mnSceneCameraID);
	mnSceneCameraID = -1;
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
	ShotCharacter* player = new ShotCharacter(true, Master::mpDataManager->GetPlayPlayerData().status, SHOT_TYPE::DEFAULT);
	player->Initilize();
	player->SetFSM(UtilFactorys::FSMCharacterFactory(player, CHARACTER_FACTORY_NUMBER::TOWN_PLAYER));
	Master::mpGameManager->GetTargetManager()->SetTarget(player, TARGET_NUMBER::PLAYER);

	// カメラ作成
	{
		CameraData cameraData = CameraData();
		cameraData.cameraMode = CAMERA_MODE::PLAYER;
		cameraData.plusPosition = VGet(0.0f, 180.0f, 0.0f);
		cameraData.cameraDistance = 550.0f;
		cameraData.targetCharacter = player;
		cameraData.threeDFlag = true;
		cameraData.SetColor(F4Get(128, 128, 128, 0));
		mnSceneCameraID = Master::mpGameManager->GetCameraManager()->NewCamera(cameraData);
		Master::mpGameManager->GetCameraManager()->SetCameraMode(mnSceneCameraID);
	}

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
	// カメラ削除
	Master::mpGameManager->GetCameraManager()->DeleteCameraData(mnSceneCameraID);
	mnSceneCameraID = -1;
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
	ShotCharacter* player = new ShotCharacter(true, Master::mpDataManager->GetPlayPlayerData().status, SHOT_TYPE::DEFAULT);
	player->Initilize();
	player->SetFSM(UtilFactorys::FSMCharacterFactory(player, CHARACTER_FACTORY_NUMBER::DUNGEON_PLAYER));
	Master::mpGameManager->GetTargetManager()->SetTarget(player, TARGET_NUMBER::PLAYER);

	// カメラ作成
	{
		CameraData cameraData = CameraData();
		cameraData.cameraMode = CAMERA_MODE::PLAYER;
		cameraData.plusPosition = VGet(0.0f, 180.0f, 0.0f);
		cameraData.cameraDistance = 550.0f;
		cameraData.targetCharacter = player;
		cameraData.threeDFlag = true;
		cameraData.SetColor(F4Get(128, 128, 128, 0));
		mnSceneCameraID = Master::mpGameManager->GetCameraManager()->NewCamera(cameraData);
		Master::mpGameManager->GetCameraManager()->SetCameraMode(mnSceneCameraID);
	}

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
	// カメラ削除
	Master::mpGameManager->GetCameraManager()->DeleteCameraData(mnSceneCameraID);
	mnSceneCameraID = -1;
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

	CharacterBase* player = nullptr;
	switch (Master::mpDataManager->GetPlayPlayerData().status.characterType)
	{
	case CHARACTER_TYPE::ROBOT:
		player = new ShotCharacter(true, Master::mpDataManager->GetPlayPlayerData().status, SHOT_TYPE::DEFAULT);
		player->Initilize();
		player->SetPos(VGet(10.0f, 0.0f, 10.0f));
		break;
	}
	player->SetFSM(UtilFactorys::FSMCharacterFactory(player, CHARACTER_FACTORY_NUMBER::BATTLE_PLAYER));
	Master::mpGameManager->GetTargetManager()->SetTarget(player, TARGET_NUMBER::PLAYER);

	// カメラ作成
	{
		CameraData cameraData = CameraData();
		cameraData.cameraMode = CAMERA_MODE::PLAYER;
		cameraData.plusPosition = VGet(0.0f, 180.0f, 0.0f);
		cameraData.cameraDistance = 550.0f;
		cameraData.targetCharacter = player;
		cameraData.threeDFlag = true;
		cameraData.SetColor(F4Get(128, 128, 128, 0));
		mnSceneCameraID = Master::mpGameManager->GetCameraManager()->NewCamera(cameraData);
		Master::mpGameManager->GetCameraManager()->SetCameraMode(mnSceneCameraID);
	}

	{// 敵
		ShotCharacter* enemy = new ShotCharacter(true, Master::mpDataManager->GetPlayPlayerData().status, SHOT_TYPE::DEFAULT);
		enemy->Initilize();
		enemy->SetPos(VGet(0.0f, 0.0f, 300.0f));
	}

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
	// カメラ削除
	Master::mpGameManager->GetCameraManager()->DeleteCameraData(mnSceneCameraID);
	mnSceneCameraID = -1;
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