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
#include "ModelEffect.h"
#include "ModelGraph.h"
#include "ModelMovie.h"
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
#include "UtilCalc.h"
#include "UtilFactorys.h"

// アニメション有限状態マシン作成
FSMAnimation* UtilFactorys::FSMAnimationFactory(AnimationBase* animation, ANIMATION_FACTORY_NUMBER animationFactoryNumber, LOAD_ANIMATION_DATA_FACTORY_NUMBER ladoAnimationDataFactorynumber, std::vector<std::vector<LoadAnimationData>> loadAnimationData)
{
	// FSM生成
	FSMAnimation* fsm = new FSMAnimation();
	
	// HACK: 一時的にnullではじいてる
	// 必要変数取得
	std::vector<AnimationDatas*> animationDatas;
	std::vector<ModelBase*> modelBases;
	animationDatas.clear();
	modelBases.clear();
	if (animation != nullptr)
	{
		animationDatas = animation->GetAnimationDatas();
		modelBases = animation->GetModelsController()->GetModelList();
		
		// サイズ設定
		fsm->IncreaseAnimationStateSize((int)animationDatas.size());
	}
	else
	{
		fsm->IncreaseAnimationStateSize(0);
	}

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
			fsm->RegisterState(new StateAttackEndAnimationController());
			break;

		case LOAD_ANIMATION_DATA_FACTORY_NUMBER::ROBOT:
			fsm->RegisterState(new StateIdleAnimationController());
			fsm->RegisterState(new StateMoveAnimationController());

			fsm->RegisterState(new StateSpceialAttackInAnimationController());
			fsm->RegisterState(new StateSpceialAttackAnimationController());
			fsm->RegisterState(new StateSpceialAttackOutAnimationController());

			fsm->RegisterState(new StateNormalAttackInAnimationController());
			fsm->RegisterState(new StateNormalAttackOutAnimationController());
			break;
		}
		break;

	case ANIMATION_FACTORY_NUMBER::SHOT_ATTACK:
		switch (ladoAnimationDataFactorynumber)
		{
		case LOAD_ANIMATION_DATA_FACTORY_NUMBER::SHOT_ATTACK:
		case LOAD_ANIMATION_DATA_FACTORY_NUMBER::ROBOT_SPCEIAL:
			fsm->RegisterState(new StateAttackIdleAnimationController());

			fsm->RegisterState(new StateAttackInAnimationController());
			fsm->RegisterState(new StateAttackAnimationController());
			fsm->RegisterState(new StateAttackEndAnimationController());
			break;
		}
		break;

	case ANIMATION_FACTORY_NUMBER::UI:
		switch (ladoAnimationDataFactorynumber)
		{
		case LOAD_ANIMATION_DATA_FACTORY_NUMBER::UI_BASE:
		case LOAD_ANIMATION_DATA_FACTORY_NUMBER::UI_BASE_MOVIE:
			fsm->RegisterState(new StateIdleAnimationController());
			fsm->RegisterState(new State2DMoveAnimationController());
			fsm->RegisterState(new StateFadeOutAnimationController());
			fsm->RegisterState(new StateFadeInAnimationController());
			break;

		case LOAD_ANIMATION_DATA_FACTORY_NUMBER::UI_FADE:
			fsm->RegisterState(new StateIdleAnimationController());
			fsm->RegisterState(new State2DMoveAnimationController());
			fsm->RegisterState(new StateFadeOutAnimationController());
			fsm->RegisterState(new StateFadeInAnimationController());
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
			// TODO: テンプレートでswitch分の中身簡単にできる気がする
			MODEL_TYPE setModelType = animationDatas[i]->animDatas[loadAnimationData[i][j].animationType].modelType;
			// アニメションステート生成
			switch (setModelType)
			{
			case MODEL_TYPE::NONE:
				if (setStateMap.find(setModelType) == setStateMap.end())
				{
					StateNoneAnimation* statenoneAnimation = new StateNoneAnimation();
					statenoneAnimation->SetModelBase(modelBases[i]);
					setStateMap[setModelType] = statenoneAnimation;
				}
				break;

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

			case MODEL_TYPE::EFFECT:
				if (setStateMap.find(setModelType) == setStateMap.end())
				{
					StateEffectAnimation* stateEffectAnimation = new StateEffectAnimation(modelBases[i]->GetHandlePointer());
					stateEffectAnimation->SetModelBase(modelBases[i]);
					setStateMap[setModelType] = stateEffectAnimation;
				}
				break;

			case MODEL_TYPE::GRAPH:
				if (setStateMap.find(setModelType) == setStateMap.end())
				{
					StateGraphAnimation* stateGraphAnimation = new StateGraphAnimation();
					stateGraphAnimation->SetModelBase(modelBases[i]);
					setStateMap[setModelType] = stateGraphAnimation;
				}
				break;

			case MODEL_TYPE::MOVIE:
				if (setStateMap.find(setModelType) == setStateMap.end())
				{
					StateMovieAnimation* stateMovieAnimation = new StateMovieAnimation();
					stateMovieAnimation->SetModelBase(modelBases[i]);
					setStateMap[setModelType] = stateMovieAnimation;
				}
				break;

			case MODEL_TYPE::FADE:
				if (setStateMap.find(setModelType) == setStateMap.end())
				{
					StateFadeGraphAnimation* stateFadeGraphAnimation = new StateFadeGraphAnimation();
					stateFadeGraphAnimation->SetModelBase(modelBases[i]);
					setStateMap[setModelType] = stateFadeGraphAnimation;
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
		case MODEL_TYPE::NONE:
			animationData.number = -1;
			animationData.loopFlag = loadAnimationData[i].animationLoopFlag;
			animationData.modelType = loadAnimationData[i].modelType;

			// 設定
			animationDataMap->animDatas[loadAnimationData[i].animationType] = animationData;
			break;

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

		case MODEL_TYPE::EFFECT:
			// エフェクトリソース取得
			animationData.number = Master::mpResourceManager->GetEffectResource(loadAnimationData[i].animationPath);
			animationData.loopFlag = loadAnimationData[i].animationLoopFlag;
			animationData.modelType = loadAnimationData[i].modelType;

			// 設定
			animationDataMap->animDatas[loadAnimationData[i].animationType] = animationData;		
			break;

		case MODEL_TYPE::GRAPH:
		case MODEL_TYPE::MOVIE:
			animationData.loopFlag = loadAnimationData[i].animationLoopFlag;
			animationData.modelType = loadAnimationData[i].modelType;

			// 設定
			animationDataMap->animDatas[loadAnimationData[i].animationType] = animationData;	
			break;

		case MODEL_TYPE::FADE:
			animationData.loopFlag = loadAnimationData[i].animationLoopFlag;
			animationData.modelType = loadAnimationData[i].modelType;

			// ブレンド設定
			animationData.blendMode = loadAnimationData[i].blendMode;
			animationData.blendParameter = loadAnimationData[i].blendParameter;

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

		if (animation != nullptr)
		{
			// TODO: データマネージャーから取得できる形式にしたい
			animation->SetAnimationTime(ANIMATION_TYPE::IDLE, 0);
			animation->SetAnimationTime(ANIMATION_TYPE::WALK, 0);
			animation->SetAnimationTime(ANIMATION_TYPE::JUMP_IN, 0);
			animation->SetAnimationTime(ANIMATION_TYPE::JUMP, 0);
			animation->SetAnimationTime(ANIMATION_TYPE::JUMP_OUT, 0);
			animation->SetAnimationTime(ANIMATION_TYPE::ATTACK, 1156);
			animation->AddAnimationData(UtilFactorys::AnimationDataFactory(loadAnimationData));
		}
		break;

	case LOAD_ANIMATION_DATA_FACTORY_NUMBER::ROBOT:
		for (int i = 0; i < 7; i++)
		{
			LoadAnimationData loadAnimaData;
			loadAnimaData.animationIndex = i;
			loadAnimaData.modelType = MODEL_TYPE::MV1_MODEL_ONLY;
			loadAnimationData.push_back(loadAnimaData);
		}
		// HACK: データマネージャーから取得できるようにする
		loadAnimationData[0].animationType = ANIMATION_TYPE::IDLE;
		loadAnimationData[0].animationLoopFlag = true;
		loadAnimationData[0].animationPath = ResourceManager::msResourceFile + "3D/Robot/Animation/robotSphere@anim_Idle_Loop_S.mv1";

		loadAnimationData[1].animationType = ANIMATION_TYPE::WALK;
		loadAnimationData[1].animationLoopFlag = true;
		loadAnimationData[1].animationPath = ResourceManager::msResourceFile + "3D/Robot/Animation/robotSphere@anim_open_Walk_Loop.mv1";

		loadAnimationData[2].animationType = ANIMATION_TYPE::SPCEIAL_ATTACK_IN;
		loadAnimationData[2].animationLoopFlag = false;
		loadAnimationData[2].animationPath = ResourceManager::msResourceFile + "3D/Robot/Animation/robotSphere@anim_open_GoToRoll.mv1";

		loadAnimationData[3].animationType = ANIMATION_TYPE::SPCEIAL_ATTACK;
		loadAnimationData[3].animationLoopFlag = false;
		loadAnimationData[3].animationPath = ResourceManager::msResourceFile + "3D/Robot/Animation/robotSphere@anim_cloed_Roll_Loop.mv1";
		loadAnimationData[3].modelType = MODEL_TYPE::MV1_MODEL_MOVE;

		loadAnimationData[4].animationType = ANIMATION_TYPE::SPCEIAL_ATTACK_OUT;
		loadAnimationData[4].animationLoopFlag = false;
		loadAnimationData[4].animationPath = ResourceManager::msResourceFile + "3D/Robot/Animation/robotSphere@anim_closed_StopRoll.mv1";

		loadAnimationData[5].animationType = ANIMATION_TYPE::NORMAL_ATTACK_IN;
		loadAnimationData[5].animationLoopFlag = false;
		loadAnimationData[5].animationPath = ResourceManager::msResourceFile + "3D/Robot/Animation/robotSphere@anim_close.mv1";

		loadAnimationData[6].animationType = ANIMATION_TYPE::NORMAL_ATTACK_OUT;
		loadAnimationData[6].animationLoopFlag = false;
		loadAnimationData[6].animationPath = ResourceManager::msResourceFile + "3D/Robot/Animation/robotSphere@anim_closed_StopRoll.mv1";

		if (animation != nullptr)
		{
			// TODO: データマネージャーから取得できる形式にしたい アニメションが終わったら次に行くのも追加したい
			animation->SetAnimationTime(ANIMATION_TYPE::IDLE, 0);
			animation->SetAnimationTime(ANIMATION_TYPE::WALK, 0);
			// animation->SetAnimationTime(ANIMATION_TYPE::ATTACK_IN,  2024/*(60 / 0.5) * 17*/);
			// animation->SetAnimationTime(ANIMATION_TYPE::ATTACK, 	20400 /*(6 / 0.5) * 17 * 1/*回転数*/);
			// animation->SetAnimationTime(ANIMATION_TYPE::ATTACK_OUT, 1632/*(48 / 0.5) * 17*/);
			animation->SetAnimationTime(ANIMATION_TYPE::SPCEIAL_ATTACK_IN, 2024);
			animation->SetAnimationTime(ANIMATION_TYPE::SPCEIAL_ATTACK, 2040);
			animation->SetAnimationTime(ANIMATION_TYPE::SPCEIAL_ATTACK_OUT, 1632);
			animation->SetAnimationTime(ANIMATION_TYPE::NORMAL_ATTACK_IN, 1088/*(48 / 0.5) * 17*/);
			animation->SetAnimationTime(ANIMATION_TYPE::NORMAL_ATTACK_OUT, 1632/*(48 / 0.5) * 17*/);
			animation->AddAnimationData(UtilFactorys::AnimationDataFactory(loadAnimationData));
		}
		break;

	case LOAD_ANIMATION_DATA_FACTORY_NUMBER::SHOT_ATTACK:
		for (int i = 0; i < 4; i++)
		{
			LoadAnimationData loadAnimaData;
			loadAnimaData.animationIndex = i;
			loadAnimaData.animationLoopFlag = false;
			loadAnimaData.modelType = MODEL_TYPE::NONE;
			loadAnimaData.animationPath = "";
			loadAnimationData.push_back(loadAnimaData);
		}
		// HACK: データマネージャーから取得できるようにする
		loadAnimationData[0].animationType = ANIMATION_TYPE::IDLE;
		
		loadAnimationData[1].animationType = ANIMATION_TYPE::ATTACK_IN;
		
		loadAnimationData[2].animationType = ANIMATION_TYPE::ATTACK;
		loadAnimationData[2].modelType = MODEL_TYPE::EFFECT;
		loadAnimationData[2].animationPath = ResourceManager::msResourceFile + "Effect/Laser.efkefc";
		
		loadAnimationData[3].animationType = ANIMATION_TYPE::ATTACK_OUT;
		
		if (animation != nullptr)
		{
			// TODO: データマネージャーから取得できる形式にしたい アニメションが終わったら次に行くのも追加したい
			animation->SetAnimationTime(ANIMATION_TYPE::IDLE, 0);
			animation->SetAnimationTime(ANIMATION_TYPE::ATTACK_IN, 1088);
			animation->SetAnimationTime(ANIMATION_TYPE::ATTACK, 1632);
			animation->SetAnimationTime(ANIMATION_TYPE::ATTACK_OUT, 0);
			animation->AddAnimationData(UtilFactorys::AnimationDataFactory(loadAnimationData));
		}
		break;

	case LOAD_ANIMATION_DATA_FACTORY_NUMBER::ROBOT_SPCEIAL:
		for (int i = 0; i < 4; i++)
		{
			LoadAnimationData loadAnimaData;
			loadAnimaData.animationIndex = i;
			loadAnimaData.animationLoopFlag = false;
			loadAnimaData.modelType = MODEL_TYPE::NONE;
			loadAnimaData.animationPath = "";
			loadAnimationData.push_back(loadAnimaData);
		}
		// HACK: データマネージャーから取得できるようにする
		loadAnimationData[0].animationType = ANIMATION_TYPE::IDLE;
		
		loadAnimationData[1].animationType = ANIMATION_TYPE::ATTACK_IN;
		
		loadAnimationData[2].animationType = ANIMATION_TYPE::ATTACK;
		
		loadAnimationData[3].animationType = ANIMATION_TYPE::ATTACK_OUT;
		
		if (animation != nullptr)
		{
			// TODO: データマネージャーから取得できる形式にしたい アニメションが終わったら次に行くのも追加したい
			animation->SetAnimationTime(ANIMATION_TYPE::IDLE, 0);
			animation->SetAnimationTime(ANIMATION_TYPE::ATTACK_IN, 2024);
			animation->SetAnimationTime(ANIMATION_TYPE::ATTACK, 2040);
			animation->SetAnimationTime(ANIMATION_TYPE::ATTACK_OUT, 1632);
			animation->AddAnimationData(UtilFactorys::AnimationDataFactory(loadAnimationData));
		}
		break;

	case LOAD_ANIMATION_DATA_FACTORY_NUMBER::UI_BASE:
		for (int i = 0; i < 4; i++)
		{
			LoadAnimationData loadAnimaData;
			loadAnimaData.animationIndex = i;
			loadAnimaData.animationLoopFlag = false;
			loadAnimaData.modelType = MODEL_TYPE::GRAPH;
			loadAnimaData.animationPath = "";
			loadAnimationData.push_back(loadAnimaData);
		}
		
		loadAnimationData[0].animationType = ANIMATION_TYPE::IDLE;
		loadAnimationData[1].animationType = ANIMATION_TYPE::DISPLAY_MOVE;
		loadAnimationData[2].animationType = ANIMATION_TYPE::FADE_OUT;
		loadAnimationData[3].animationType = ANIMATION_TYPE::FADE_IN;
		
		if (animation != nullptr)
		{
			// TODO: データマネージャーから取得できる形式にしたい アニメションが終わったら次に行くのも追加したい
			animation->SetAnimationTime(ANIMATION_TYPE::IDLE, 0);
			animation->SetAnimationTime(ANIMATION_TYPE::DISPLAY_MOVE, 0);
			animation->SetAnimationTime(ANIMATION_TYPE::FADE_OUT, 0);
			animation->SetAnimationTime(ANIMATION_TYPE::FADE_IN, 0);
			animation->AddAnimationData(UtilFactorys::AnimationDataFactory(loadAnimationData));
		}
		break;

	case LOAD_ANIMATION_DATA_FACTORY_NUMBER::UI_BASE_MOVIE:
		for (int i = 0; i < 4; i++)
		{
			LoadAnimationData loadAnimaData;
			loadAnimaData.animationIndex = i;
			loadAnimaData.animationLoopFlag = false;
			loadAnimaData.modelType = MODEL_TYPE::MOVIE;
			loadAnimaData.animationPath = "";
			loadAnimationData.push_back(loadAnimaData);
		}
		
		loadAnimationData[0].animationType = ANIMATION_TYPE::IDLE;
		loadAnimationData[1].animationType = ANIMATION_TYPE::DISPLAY_MOVE;
		loadAnimationData[2].animationType = ANIMATION_TYPE::FADE_OUT;
		loadAnimationData[3].animationType = ANIMATION_TYPE::FADE_IN;
		
		if (animation != nullptr)
		{
			// TODO: データマネージャーから取得できる形式にしたい アニメションが終わったら次に行くのも追加したい
			animation->SetAnimationTime(ANIMATION_TYPE::IDLE, 0);
			animation->SetAnimationTime(ANIMATION_TYPE::DISPLAY_MOVE, 0);
			animation->SetAnimationTime(ANIMATION_TYPE::FADE_OUT, 0);
			animation->SetAnimationTime(ANIMATION_TYPE::FADE_IN, 0);
			animation->AddAnimationData(UtilFactorys::AnimationDataFactory(loadAnimationData));
		}
		break;

	case LOAD_ANIMATION_DATA_FACTORY_NUMBER::UI_FADE:
		for (int i = 0; i < 4; i++)
		{
			LoadAnimationData loadAnimaData;
			loadAnimaData.animationIndex = i;
			loadAnimaData.animationLoopFlag = false;
			loadAnimaData.modelType = MODEL_TYPE::GRAPH;
			loadAnimaData.animationPath = "";
			loadAnimationData.push_back(loadAnimaData);
		}
		
		loadAnimationData[0].animationType = ANIMATION_TYPE::IDLE;
		loadAnimationData[1].animationType = ANIMATION_TYPE::DISPLAY_MOVE;
		loadAnimationData[2].animationType = ANIMATION_TYPE::FADE_OUT;
		loadAnimationData[2].blendMode = DX_BLENDMODE_ALPHA;
		loadAnimationData[2].blendParameter = 11;
		loadAnimationData[2].modelType = MODEL_TYPE::FADE;
		loadAnimationData[3].animationType = ANIMATION_TYPE::FADE_IN;
		loadAnimationData[3].blendMode = DX_BLENDMODE_ALPHA;
		loadAnimationData[3].blendParameter = -11;
		loadAnimationData[3].modelType = MODEL_TYPE::FADE;
		
		if (animation != nullptr)
		{
			// TODO: データマネージャーから取得できる形式にしたい アニメションが終わったら次に行くのも追加したい
			animation->SetAnimationTime(ANIMATION_TYPE::IDLE, 0);
			animation->SetAnimationTime(ANIMATION_TYPE::DISPLAY_MOVE, 0);
			animation->SetAnimationTime(ANIMATION_TYPE::FADE_OUT, 25 * 17);
			animation->SetAnimationTime(ANIMATION_TYPE::FADE_IN, 25 * 17);
			animation->AddAnimationData(UtilFactorys::AnimationDataFactory(loadAnimationData));
		}
		break;
	}

	return loadAnimationData;
}

// キャラクタ攻撃情報作成
CharacterAttackData UtilFactorys::CharacterAttackDataFactory(CHARACTER_ATTACK_DATA_FACTORY__ATTACK_METHOD factoryNumberAttackMethod, CHARACTER_ATTACK_DATA_FACTORY__MODEL_TYPE factoryNumberModelType)
{
	// 初期化
	CharacterAttackData characterAttackData;
	characterAttackData.attackDataNumber = -1;
	characterAttackData.modelController = new ModelsControllerBase();
	characterAttackData.animation = new AnimationBase();
	// 変数にポインタを渡し見やすくする
    ModelsControllerBase* modelController = characterAttackData.modelController;
    AnimationBase* animation = characterAttackData.animation;
	// モデル初期化
	modelController->Initilize();
	// アニメーション初期化
	animation->Initilize();
	animation->SetModelsController(modelController);
	

	// モデル設定
	switch (factoryNumberAttackMethod)
	{
	case CHARACTER_ATTACK_DATA_FACTORY__ATTACK_METHOD::SHOT_NORMAL:
		modelController->AddModel(UtilFactorys::ModelFactory(MODEL_TYPE::EFFECT, "", VGet(0.0f, 1.0f, 3.0f), UtilCalc::VZero, VScale(UtilCalc::VOne, 100.0f)));
		break;
	
	case CHARACTER_ATTACK_DATA_FACTORY__ATTACK_METHOD::SHOT_SPCEIAL:
		switch (factoryNumberModelType)
		{
		case CHARACTER_ATTACK_DATA_FACTORY__MODEL_TYPE::ROBOT:
			modelController->AddModel(UtilFactorys::ModelFactory(MODEL_TYPE::EFFECT, "", UtilCalc::VZero, UtilCalc::VZero, VScale(UtilCalc::VOne, 20.0f)));
			break;
		}
		break;
	}

	// アニメーション設定
 	std::vector<std::vector<LoadAnimationData>> setcharacterLoadAnimationData;
	switch (factoryNumberAttackMethod)
	{
	case CHARACTER_ATTACK_DATA_FACTORY__ATTACK_METHOD::SHOT_NORMAL:
	 	// 読み込み用アニメーションデータ設定
	 	setcharacterLoadAnimationData.push_back(UtilFactorys::LoadAnimationDataFactory(animation, LOAD_ANIMATION_DATA_FACTORY_NUMBER::SHOT_ATTACK));
	 	// アニメーション有限状態マシン設定
	 	animation->SetFsm(UtilFactorys::FSMAnimationFactory(animation, ANIMATION_FACTORY_NUMBER::SHOT_ATTACK, LOAD_ANIMATION_DATA_FACTORY_NUMBER::SHOT_ATTACK, setcharacterLoadAnimationData));
		break;
	
	case CHARACTER_ATTACK_DATA_FACTORY__ATTACK_METHOD::SHOT_SPCEIAL:
		switch (factoryNumberModelType)
		{
		case CHARACTER_ATTACK_DATA_FACTORY__MODEL_TYPE::ROBOT:
		 	// 読み込み用アニメーションデータ設定
			setcharacterLoadAnimationData.push_back(UtilFactorys::LoadAnimationDataFactory(animation, LOAD_ANIMATION_DATA_FACTORY_NUMBER::ROBOT_SPCEIAL));
			// アニメーション有限状態マシン設定
			animation->SetFsm(UtilFactorys::FSMAnimationFactory(animation, ANIMATION_FACTORY_NUMBER::SHOT_ATTACK, LOAD_ANIMATION_DATA_FACTORY_NUMBER::ROBOT_SPCEIAL, setcharacterLoadAnimationData));
			break;
		}
		break;
	}

	return characterAttackData;
}

// カメラ有限状態マシン作成
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
		fsmCharacter->RegisterState(new NormalAttackPlayerState());
		fsmCharacter->RegisterState(new SpceialAttackPlayerState());

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
		fsmCharacter->RegisterState(new MoveEnemyState());
		fsmCharacter->RegisterState(new AttackInEnemyState());
		fsmCharacter->RegisterState(new AttackEnemyState());
		fsmCharacter->RegisterState(new EscapeEnemyState());
		fsmCharacter->RegisterState(new LeftAvoidEnemyState());
		fsmCharacter->RegisterState(new RightAvoidEnemyState());

		fsmCharacter->SetCurrentState((int)ENEMY_STATE::IDLE_ENEMY_STATE, character);

		Master::mpGameManager->GetTargetManager()->SetTarget(character, TARGET_TYPE::ENEMY);
		break;

	case CHARACTER_FACTORY_NUMBER::BOSS_ENEMY:
		fsmCharacter->RegisterState(new IdleBossEnemyState());
		fsmCharacter->RegisterState(new MoveBossEnemyState());
		fsmCharacter->RegisterState(new AttackInBossEnemyState());
		fsmCharacter->RegisterState(new AttackBossEnemyState());
		fsmCharacter->RegisterState(new EscapeEnemyState());
		fsmCharacter->RegisterState(new LeftAvoidEnemyState());
		fsmCharacter->RegisterState(new RightAvoidEnemyState());

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
	fsmScene->RegisterState(new GameOverScene());

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
		fsmUI->RegisterState(new StartGameUIState());
		fsmUI->RegisterState(new NormalGameUIState());
		fsmUI->RegisterState(new PauseGameUIState());

		fsmUI->SetCurrentState((int)GAME_UI_STATE::START_GAME_UI_STAE, ui);
		break;

	case UI_FACTORY_NUMBER::RESULT:
		fsmUI->RegisterState(new StartResultUIState());

		fsmUI->SetCurrentState((int)RESULT_UI_STATE::START_RESULT_UI_STATE, ui);
		break;
	}

	return fsmUI;
}

// モデル作成
ModelBase* UtilFactorys::ModelFactory(MODEL_TYPE type, std::string modelPath, VECTOR position, VECTOR angle, VECTOR size, std::vector<DRAW_GRAPH_DATA>* drawData)
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

	case MODEL_TYPE::EFFECT:
	{
		ModelEffect* model = new ModelEffect();
		model->Initilize();
		SetModelPosition(model, position, angle, size);
		return model;
	}

	case MODEL_TYPE::GRAPH:
	{
		ModelGraph* model = new ModelGraph();
		model->Initilize();
		SetModelPosition(model, position, angle, size);
		model->SetDrawDatas(*drawData);
		return model;
	}

	case MODEL_TYPE::MOVIE:
	{
		ModelMovie* model = new ModelMovie();
		model->Initilize();
		SetModelPosition(model, position, angle, size);
		model->SetDrawDatas(*drawData);
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

// 攻撃データ作成
std::map<ATTACK_METHOD_TYPE, AttackData> UtilFactorys::AttackDataFactory(CHARACTER_ATTACK_DATA_FACTORY__MODEL_TYPE modelTypeFactoryNumber, ATTACK_DATA_FACTORY__OBJECT_ATTACK_TYPE objectAttackTypeFactoryNumber)
{
	std::map<ATTACK_METHOD_TYPE, AttackData>  attackDatas;
	AttackData setData = AttackData();

	switch (modelTypeFactoryNumber)
	{
	case CHARACTER_ATTACK_DATA_FACTORY__MODEL_TYPE::ROBOT:
		attackDatas[ATTACK_METHOD_TYPE::NORMAL].attackCharacter = nullptr;
		attackDatas[ATTACK_METHOD_TYPE::SPCEIAL].attackCharacter = nullptr;

		switch (objectAttackTypeFactoryNumber)
		{
		case ATTACK_DATA_FACTORY__OBJECT_ATTACK_TYPE::SHOT:
			attackDatas[ATTACK_METHOD_TYPE::NORMAL].attackMethdType = ATTACK_METHOD_TYPE::NORMAL;
			attackDatas[ATTACK_METHOD_TYPE::NORMAL].attackTime = 2720;
			attackDatas[ATTACK_METHOD_TYPE::NORMAL].attackType = ATTACK_TYPE::SHOT;

			attackDatas[ATTACK_METHOD_TYPE::SPCEIAL].attackMethdType = ATTACK_METHOD_TYPE::SPCEIAL;
			attackDatas[ATTACK_METHOD_TYPE::SPCEIAL].attackTime = 5696;
			attackDatas[ATTACK_METHOD_TYPE::SPCEIAL].attackType = ATTACK_TYPE::UNIQUE_ROBOT;
			break;
		}
		break;
	}

	return attackDatas;
}
/*
	// モデル設定
	character->GetModelsController()->AddModel(UtilFactorys::ModelFactory(MODEL_TYPE::MV1_MODEL, "../Resource/3D/Robot/robotSphere.mv1", UtilCalc::VZero, UtilCalc::VZero, VScale(UtilCalc::VOne, 20.0f)));
	//character->GetModelsController()->AddModel(UtilFactorys::ModelFactory(MODEL_TYPE::MV1_MODEL, "../Resource/3D/Human/Hero.x"));
	// アニメション設定
	 {
	 	AnimationBase* characterAnimation = character->GetAnimation();
	 	std::vector<std::vector<LoadAnimationData>> setcharacterLoadAnimationData;
	 	// 読み込み用アニメーションデータ設定
	 	setcharacterLoadAnimationData.push_back(UtilFactorys::LoadAnimationDataFactory(characterAnimation, LOAD_ANIMATION_DATA_FACTORY_NUMBER::ROBOT));
	 	// アニメーション有限状態マシン設定
	 	characterAnimation->SetFsm(UtilFactorys::FSMAnimationFactory(characterAnimation, animationFactoryNumber, LOAD_ANIMATION_DATA_FACTORY_NUMBER::ROBOT, setcharacterLoadAnimationData));
	 }
*/