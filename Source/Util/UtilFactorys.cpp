#include "Master.h"

#include "CameraManager.h"
#include "FSM.h"
#include "GameManager.h"
#include "ModelBase.h"
#include "ModelMV1.h"
#include "ModelPolygonIndexed.h"
#include "ObjectBases.h"
#include "SceneManager.h"
#include "StateBase.h"
#include "StateCamera.h"
#include "StateEnemy.h"
#include "StateMapEnemy.h"
#include "StatePlayer.h"
#include "StateResultUI.h"
#include "StateScene.h"
#include "StateTitleUI.h"
#include "TargetManager.h"
#include "UtilFactorys.h"

/*カメラ有限状態マシン作成*/
FSMCamera* UtilFactorys::FSMCameraFactory()
{
	FSMCamera* fsnCamera = new FSMCamera();

	fsnCamera->RegisterState(new StateFixedCamera());
	fsnCamera->RegisterState(new StateCharacterCamera());
	fsnCamera->RegisterState(new StatePlayerCamera());

	return fsnCamera;
}

// キャラクター有限状態マシン作成
FSMCharacter* UtilFactorys::FSMCharacterFactory(CharacterBase* character, CHARACTER_FACTORY_NUMBER number)
{
	FSMCharacter* fsmCharacter = new FSMCharacter();

	switch (number)
	{
	case CHARACTER_FACTORY_NUMBER::TOWN_PLAYER:
		fsmCharacter->RegisterState(new IdlePlayerState());
		fsmCharacter->RegisterState(new MovePlayerState());

		fsmCharacter->SetCurrentState((int)PLAYER_STATE::IDLE_PLAYER_STATE, character);

		Master::mpGameManager->GetTargetManager()->SetTarget(character, TARGET_TYPE::PLAYER);
		break;

	case CHARACTER_FACTORY_NUMBER::DUNGEON_PLAYER:
		fsmCharacter->RegisterState(new IdlePlayerState());
		fsmCharacter->RegisterState(new MovePlayerState());

		fsmCharacter->SetCurrentState((int)PLAYER_STATE::IDLE_PLAYER_STATE, character);

		Master::mpGameManager->GetTargetManager()->SetTarget(character, TARGET_TYPE::PLAYER);
		break;

	case CHARACTER_FACTORY_NUMBER::BATTLE_PLAYER:
		fsmCharacter->RegisterState(new IdleBattlePlayerState());
		fsmCharacter->RegisterState(new MoveBattlePlayerState());
		fsmCharacter->RegisterState(new AttackPlayerState());

		fsmCharacter->SetCurrentState((int)PLAYER_STATE::IDLE_PLAYER_STATE, character);

		Master::mpGameManager->GetTargetManager()->SetTarget(character, TARGET_TYPE::PLAYER);
		break;

	case CHARACTER_FACTORY_NUMBER::MAP_ENEMY:
		fsmCharacter->RegisterState(new IdleMapEnemyState());
		fsmCharacter->RegisterState(new TelopMapEnemyState());

		fsmCharacter->SetCurrentState((int)MAP_ENEMY_STATE::IDLE_MAP_ENEMY_STATE, character);

		Master::mpGameManager->GetTargetManager()->SetTarget(character, TARGET_TYPE::ENEMY);
		break;

	case CHARACTER_FACTORY_NUMBER::ENEMY:
		fsmCharacter->RegisterState(new IdleEnemyState());

		fsmCharacter->SetCurrentState((int)ENEMY_STATE::IDLE_ENEMY_STATE, character);

		Master::mpGameManager->GetTargetManager()->SetTarget(character, TARGET_TYPE::ENEMY);
		break;

	case CHARACTER_FACTORY_NUMBER::BOSS_ENEMY:
		fsmCharacter->RegisterState(new IdleBossEnemyState());

		fsmCharacter->SetCurrentState((int)ENEMY_STATE::IDLE_ENEMY_STATE, character);

		Master::mpGameManager->GetTargetManager()->SetTarget(character, TARGET_TYPE::ENEMY);
		break;
	}

	return fsmCharacter;
}

// シーン有限状態マシン作成
FSMScene* UtilFactorys::FSMSceneFactory(SceneManager* sceneManager)
{
	FSMScene* fsmScene = new FSMScene();

	fsmScene->RegisterState(new StartScene());
	fsmScene->RegisterState(new TitleScene());
	fsmScene->RegisterState(new TownScene());
	fsmScene->RegisterState(new DungeonScene());
	fsmScene->RegisterState(new BattleScene());
	fsmScene->RegisterState(new ResultScene());

	fsmScene->SetCurrentState(SCENE::START, sceneManager);

	return fsmScene;
}

// UI有限状態マシン作成
FSMUI* UtilFactorys::FSMUIFactory(UIBase* ui, UI_FACTORY_NUMBER number)
{
	FSMUI* fsmUI = new FSMUI();

	switch (number)
	{
	case UI_FACTORY_NUMBER::TITLE:
		fsmUI->RegisterState(new StartTitleUIState());
		fsmUI->RegisterState(new SelectTitleUIState());
		fsmUI->RegisterState(new NewDataCheckTitleUIState());
		fsmUI->RegisterState(new DataSelectTitleUIState());
		fsmUI->RegisterState(new TutorialTitleUIState());
		fsmUI->RegisterState(new SettingTitleUIState());

		fsmUI->SetCurrentState((int)TITLE_UI_STATE::START_TITLE_UI_STATE, ui);
		break;

	case UI_FACTORY_NUMBER::RESULT:
		fsmUI->RegisterState(new StartResultUIState());

		fsmUI->SetCurrentState((int)RESULT_UI_STATE::START_RESULT_UI_STATE, ui);
		break;
	}

	return fsmUI;
}

// モデル作成
ModelBase* UtilFactorys::ModelFactory(MODEL_FACTORY_NUMBER number)
{
	ModelBase* model = nullptr;

	switch (number)
	{
	case MODEL_FACTORY_NUMBER::POLYGON_INDEXED:
		model = new ModelPolygonIndexed();
		model->Initilize();
		break;

	case MODEL_FACTORY_NUMBER::MV1:
		model = new ModelMV1();
		model->Initilize();
		break;
	}

	return model;
}