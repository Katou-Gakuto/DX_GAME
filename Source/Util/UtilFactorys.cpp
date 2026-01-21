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
#include "StateAnimationController.h"
#include "StateBase.h"
#include "StateCamera.h"
#include "StateEnemy.h"
#include "StateGameUI.h"
#include "StateMapEnemy.h"
#include "StatePlayer.h"
#include "StateResultUI.h"
#include "StateScene.h"
#include "StateTitleUI.h"
#include "TargetManager.h"
#include "UtilFactorys.h"

// アニメション有限状態マシン作成
FSMAnimation* UtilFactorys::FSMAnimationFactory(AnimationBase* animation, ANIMATION_FACTORY_NUMBER animationFactoryNumber, LOAD_ANIMATION_DATA_FACTORY_NUMBER ladoAnimationDataFactorynumber, std::vector<std::vector<LoadAnimationData>> loadAnimationData)
{
	// FSM生成
	FSMAnimation* fsm = new FSMAnimation();
	
	// 必要変数取得
	std::vector<AnimationDatas*> animationDatas = animation->GetAnimationDatas();
	std::vector<ModelBase*> modelBases = animation->GetModelsController()->GetModelList();

	// サイズ設定
	fsm->IncreaseAnimationStateSize((int)animationDatas.size());

	switch (animationFactoryNumber)
	{
	case ANIMATION_FACTORY_NUMBER::TOWN:
		switch (ladoAnimationDataFactorynumber)
		{
		case LOAD_ANIMATION_DATA_FACTORY_NUMBER::ROBOT:
		case LOAD_ANIMATION_DATA_FACTORY_NUMBER::HUMAN:
			fsm->RegisterState(new StateIdleAnimationController());
			fsm->RegisterState(new StateMoveAnimationController());
			break;
		}
		break;

	case ANIMATION_FACTORY_NUMBER::DUNGEON:
		switch (ladoAnimationDataFactorynumber)
		{
		case LOAD_ANIMATION_DATA_FACTORY_NUMBER::ROBOT:
		case LOAD_ANIMATION_DATA_FACTORY_NUMBER::HUMAN:
			fsm->RegisterState(new StateIdleAnimationController());
			fsm->RegisterState(new StateMoveAnimationController());
			break;
		}
		break;

	case ANIMATION_FACTORY_NUMBER::BATTLE:
		switch (ladoAnimationDataFactorynumber)
		{
		case LOAD_ANIMATION_DATA_FACTORY_NUMBER::HUMAN:
			fsm->RegisterState(new StateIdleAnimationController());
			fsm->RegisterState(new StateMoveAnimationController());
			fsm->RegisterState(new StateAttackAnimationController());
			break;

		case LOAD_ANIMATION_DATA_FACTORY_NUMBER::ROBOT:
			fsm->RegisterState(new StateIdleAnimationController());
			fsm->RegisterState(new StateMoveAnimationController());
			fsm->RegisterState(new StateAttackInAnimationController());
			fsm->RegisterState(new StateAttackMiddleAnimationController());
			fsm->RegisterState(new StateAttackOutAnimationController());
			break;
		}
		break;
	}

	// モデルの数分設定する
	for (int i = 0; i < loadAnimationData.size(); i++)
	{
		std::map<MODEL_TYPE, IStateAnimation*> setStateMap;

		for (int j = 0; j < loadAnimationData[i].size(); j++)
		{
			MODEL_TYPE setModelType = animationDatas[i]->animDatas[loadAnimationData[i][j].animationType].modelType;
			// アニメションステート生成
			switch (setModelType)
			{
			case MODEL_TYPE::MV1_MODEL:
				if (setStateMap.find(setModelType) == setStateMap.end())
				{
					// HACK: 外部から固定するフレームの名前を取得できるようにする
					StateMVOneAnimation* stateMVOneAnimation = new StateMVOneAnimation(modelBases[i]->GetHandle(), "root");
					stateMVOneAnimation->SetModelBase(modelBases[i]);
					setStateMap[setModelType] = stateMVOneAnimation;
				}
				break;

			case MODEL_TYPE::MV1_MODEL_MOVE:
				if (setStateMap.find(setModelType) == setStateMap.end())
				{
					// HACK: 仮設定
					StateMVOneOperationAnimation* stateMVOneOperationAnimation = new StateMVOneOperationAnimation(modelBases[i]->GetHandle(), VGet(00.0f, 00.0f, 00.0f), VGet(10.0f, 0.0f, 0.0f), VGet(0.0f, 0.0f, 0.0f));
					stateMVOneOperationAnimation->SetModelBase(modelBases[i]);
					setStateMap[setModelType] = stateMVOneOperationAnimation;
				}
				break;

			case MODEL_TYPE::MV1_MODEL_ONLY:
				if (setStateMap.find(setModelType) == setStateMap.end())
				{
					StateMVOneOnlyAnimation* stateMVOneOnlyAnimation = new StateMVOneOnlyAnimation(modelBases[i]->GetHandle());
					stateMVOneOnlyAnimation->SetModelBase(modelBases[i]);
					setStateMap[setModelType] = stateMVOneOnlyAnimation;
				}
				break;
			}
		}

		fsm->SetAnimationStateDatas(i, setStateMap);
	}

	// 初期化
	fsm->Initilize(animation);

	return fsm;
}

// アニメーションデータ作成
AnimationDatas* UtilFactorys::AnimationDataFactory(std::vector<LoadAnimationData> loadAnimationData)
{
	AnimationDatas* animationDataMap = new AnimationDatas();
	OneAnimationData animationData;
	animationData.animationHandle = -1;
	animationData.animationCount = 0.0f;
	animationDataMap->animDatas.clear();

	for (int i = 0; i < loadAnimationData.size(); i++)
	{
		switch (loadAnimationData[i].modelType)
		{
		case MODEL_TYPE::MV1_MODEL:
			// アニメション添え字設定
			animationData.number = loadAnimationData[i].animationIndex;
			
			animationData.loopFlag = loadAnimationData[i].animationLoopFlag;
			
			animationData.modelType = loadAnimationData[i].modelType;

			// 設定
			animationDataMap->animDatas[loadAnimationData[i].animationType] = animationData;
			break;

		case MODEL_TYPE::MV1_MODEL_MOVE:
		case MODEL_TYPE::MV1_MODEL_ONLY:
			// アニメション読み込み
			animationData.number = Master::mpResourceManager->GetModelHandle(loadAnimationData[i].animationPath);

			animationData.loopFlag = loadAnimationData[i].animationLoopFlag;
			
			animationData.modelType = loadAnimationData[i].modelType;

			// 設定
			animationDataMap->animDatas[loadAnimationData[i].animationType] = animationData;
			break;
		}
	}

	return animationDataMap;
}

/*読み込み用アニメーションデータ作成*/
std::vector<LoadAnimationData> UtilFactorys::LoadAnimationDataFactory(AnimationBase* animation, LOAD_ANIMATION_DATA_FACTORY_NUMBER number)
{
	std::vector<LoadAnimationData> loadAnimationData;
	loadAnimationData.clear();

	switch (number)
	{
	case LOAD_ANIMATION_DATA_FACTORY_NUMBER::HUMAN:
		for (int i = 0; i < 6; i++)
		{
			LoadAnimationData loadAnimaData;
			loadAnimaData.animationIndex = i;
			loadAnimaData.modelType = MODEL_TYPE::MV1_MODEL;
			loadAnimationData.push_back(loadAnimaData);
		}
		// HACK: データマネージャーから取得できるようにする
		loadAnimationData[0].animationType = ANIMATION_TYPE::IDLE;
		loadAnimationData[0].animationLoopFlag = true;
		loadAnimationData[1].animationType = ANIMATION_TYPE::WALK;
		loadAnimationData[1].animationLoopFlag = true;
		loadAnimationData[2].animationType = ANIMATION_TYPE::JUMP_IN;
		loadAnimationData[2].animationLoopFlag = false;
		loadAnimationData[3].animationType = ANIMATION_TYPE::JUMP;
		loadAnimationData[3].animationLoopFlag = false;
		loadAnimationData[4].animationType = ANIMATION_TYPE::JUMP_OUT;
		loadAnimationData[4].animationLoopFlag = false;
		loadAnimationData[5].animationType = ANIMATION_TYPE::ATTACK;
		loadAnimationData[5].animationLoopFlag = false;
		// TODO: データマネージャーから取得できる形式にしたい
		animation->SetAnimationTime(ANIMATION_TYPE::IDLE, 0);
		animation->SetAnimationTime(ANIMATION_TYPE::WALK, 0);
		animation->SetAnimationTime(ANIMATION_TYPE::JUMP_IN, 0);
		animation->SetAnimationTime(ANIMATION_TYPE::JUMP, 0);
		animation->SetAnimationTime(ANIMATION_TYPE::JUMP_OUT, 0);
		animation->SetAnimationTime(ANIMATION_TYPE::ATTACK, 1156);
		animation->AddAnimationData(UtilFactorys::AnimationDataFactory(loadAnimationData));
		break;

	case LOAD_ANIMATION_DATA_FACTORY_NUMBER::ROBOT:
		for (int i = 0; i < 5; i++)
		{
			LoadAnimationData loadAnimaData;
			loadAnimaData.animationIndex = i;
			loadAnimaData.modelType = MODEL_TYPE::MV1_MODEL_ONLY;
			loadAnimationData.push_back(loadAnimaData);
		}
		// HACK: データマネージャーから取得できるようにする
		loadAnimationData[0].animationType = ANIMATION_TYPE::IDLE;
		loadAnimationData[0].animationLoopFlag = true;
		loadAnimationData[0].animationPath = "../Resource/3D/Robot/Animation/robotSphere@anim_Idle_Loop_S.mv1";

		loadAnimationData[1].animationType = ANIMATION_TYPE::WALK;
		loadAnimationData[1].animationLoopFlag = true;
		loadAnimationData[1].animationPath = "../Resource/3D/Robot/Animation/robotSphere@anim_open_Walk_Loop.mv1";

		loadAnimationData[2].animationType = ANIMATION_TYPE::ATTACK_IN;
		loadAnimationData[2].animationLoopFlag = false;
		loadAnimationData[2].animationPath = "../Resource/3D/Robot/Animation/robotSphere@anim_open_GoToRoll.mv1";

		loadAnimationData[3].animationType = ANIMATION_TYPE::ATTACK;
		loadAnimationData[3].animationLoopFlag = false;
		loadAnimationData[3].animationPath = "../Resource/3D/Robot/Animation/robotSphere@anim_cloed_Roll_Loop.mv1";
		loadAnimationData[3].modelType = MODEL_TYPE::MV1_MODEL_MOVE;

		loadAnimationData[4].animationType = ANIMATION_TYPE::ATTACK_OUT;
		loadAnimationData[4].animationLoopFlag = false;
		loadAnimationData[4].animationPath = "../Resource/3D/Robot/Animation/robotSphere@anim_closed_StopRoll.mv1";

		// TODO: データマネージャーから取得できる形式にしたい
		animation->SetAnimationTime(ANIMATION_TYPE::IDLE, 0);
		animation->SetAnimationTime(ANIMATION_TYPE::WALK, 0);
		animation->SetAnimationTime(ANIMATION_TYPE::ATTACK_IN,  2024/*(60 / 0.5) * 17*/);
		animation->SetAnimationTime(ANIMATION_TYPE::ATTACK, 	20400 /*(6 / 0.5) * 17 * 1/*回転数*/);
		animation->SetAnimationTime(ANIMATION_TYPE::ATTACK_OUT, 1632/*(48 / 0.5) * 17*/);
		animation->AddAnimationData(UtilFactorys::AnimationDataFactory(loadAnimationData));
		break;
	}

	return loadAnimationData;
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
		
		fsmUI->RegisterState(new CharacterSelectTitleUIState());
		fsmUI->RegisterState(new PlayerNameTitleUIState());
		fsmUI->RegisterState(new InputCheckTitleUIState());
		
		fsmUI->RegisterState(new ScreenSizeTitleUIState());
		fsmUI->RegisterState(new VolumeTitleUIState());

		fsmUI->SetCurrentState((int)TITLE_UI_STATE::START_TITLE_UI_STATE, ui);
		break;

	case UI_FACTORY_NUMBER::TOWN:
	case UI_FACTORY_NUMBER::DUNGEON:
	case UI_FACTORY_NUMBER::BATTLE:
		fsmUI->RegisterState(new NormalGameUIState());
		fsmUI->RegisterState(new PauseGameUIState());

		fsmUI->SetCurrentState((int)GAME_UI_STATE::NORMAL_GAME_UI_STATE, ui);
		break;

	case UI_FACTORY_NUMBER::RESULT:
		fsmUI->RegisterState(new StartResultUIState());

		fsmUI->SetCurrentState((int)RESULT_UI_STATE::START_RESULT_UI_STATE, ui);
		break;
	}

	return fsmUI;
}

// モデル作成
ModelBase* UtilFactorys::ModelFactory(MODEL_TYPE type, std::string modelPath, VECTOR position, VECTOR angle, VECTOR size)
{
	switch (type)
	{
	case MODEL_TYPE::POLYGON_INDEXED:
	{
		ModelPolygonIndexed* model = new ModelPolygonIndexed();
		model->Initilize();
		SetModelPosition(model, position, angle, size);
		return model;
	}

	case MODEL_TYPE::MV1_MODEL:
	case MODEL_TYPE::MV1_MODEL_ONLY:
	{
		ModelMV1* model = new ModelMV1();
		model->Initilize();
		model->SetModelHandle(modelPath.c_str());
		SetModelPosition(model, position, angle, size);
		return model;
	}
	}

	return nullptr;
}

// モデル位置設定
void UtilFactorys::SetModelPosition(ModelBase* model, VECTOR position, VECTOR angle, VECTOR size)
{
	model->SetPosition(position);
	model->SetAngle(angle);
	model->SetSize(size);
}