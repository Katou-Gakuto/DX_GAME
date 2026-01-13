#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "AnimationEnum.h"
#include "AnimationData.h"

#include "DxLib.h"

#include "Master.h"

#include "CameraManager.h"
#include "FSM.h"
#include "GameManager.h"
#include "ModelBase.h"
#include "ModelMV1.h"
#include "ModelPolygonIndexed.h"
#include "ObjectBases.h"
#include "SceneManager.h"
#include "StateAnimation.h"
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

// アニメション有限状態マシン作成
FSMAnimation* UtilFactorys::FSMAnimationFactory(std::vector<AnimationData> animationDatas, std::vector<std::vector<LoadAnimationData>> loadAnimationData)
{
	FSMAnimation* fsm = new FSMAnimation();
	fsm->IncreaseAnimationStateSize(animationDatas.size());

	for (int i = 0; i < animationDatas.size(); i++)
	{
		std::map<ANIMATION_TYPE, MODEL_TYPE> setModelTypeMap;
		std::map<MODEL_TYPE, IStateAnimation*> setStateMap;

		for (int j = 0; j < loadAnimationData[i].size(); j++)
		{
			// HACK: 仮処置
			MODEL_TYPE setModelType = MODEL_TYPE::MV1_MODEL;

			setModelTypeMap[loadAnimationData[i][j].animationType] = setModelType;

			switch (setModelType)
			{
			case MODEL_TYPE::MV1_MODEL:
				if (setStateMap.find(setModelType) == setStateMap.end())
				{
					setStateMap[setModelType] = new StateMVOneAnimation();
				}
				break;
			}
		}

		fsm->SetAnimationStateDatas(i, animationDatas[i].animationType, setModelTypeMap, setStateMap);
	}

	return fsm;
}

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
FSMCharacter* UtilFactorys::FSMCharacterFactory(CharacterBase* character, CHARACTER_FACTORY_NUMBER number, SCENE mapScene)
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
		fsmCharacter->RegisterState(new IdleMapEnemyState(mapScene));
		fsmCharacter->RegisterState(new TelopMapEnemyState(mapScene));

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
ModelBase* UtilFactorys::ModelFactory(MODEL_TYPE type, std::string modelPath)
{
	switch (type)
	{
	case MODEL_TYPE::POLYGON_INDEXED:
	{
		ModelPolygonIndexed* model = new ModelPolygonIndexed();
		model->Initilize();
		return model;
	}

	case MODEL_TYPE::MV1_MODEL:
	case MODEL_TYPE::MV1_MODEL_ONLY:
	{
		ModelMV1* model = new ModelMV1();
		model->Initilize();
		model->SetModelHandle(modelPath.c_str());
		return model;
	}
	}

	return nullptr;
}

// アニメーションデータ作成
AnimationData UtilFactorys::AnimationDataFactory(MODEL_TYPE type, std::vector<LoadAnimationData> loadAnimationData)
{
	switch (type)
	{
	case MODEL_TYPE::MV1_MODEL:
	{
		AnimationData animationData;
		for (int i = 0; i < loadAnimationData.size(); i++)
		{
			// アニメション添え字設定
			animationData.animationNumber[loadAnimationData[i].animationType] = loadAnimationData[i].animationIndex;
		}		
		return animationData;
	}

	case MODEL_TYPE::MV1_MODEL_ONLY:
	{
		AnimationData animationData;
		for (int i = 0; i < loadAnimationData.size(); i++)
		{
			// アニメション読み込み
			animationData.animationNumber[loadAnimationData[i].animationType] = Master::mpResourceManager->GetModelHandle(loadAnimationData[i].animationPath);
		}
		return animationData;
	}
	}

	return AnimationData();
}