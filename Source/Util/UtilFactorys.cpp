#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "AnimationEnum.h"
#include"KeyStateEnum.h" 
#include "StateEnum.h"
#include "AnimationData.h"
#include "StateData.h"

#include "DxLib.h"

#include "Master.h"

#include "Animation.h"
#include "CameraManager.h"
#include "FSMAnimation.h"
#include "FSMCamera.h"
#include "FSMCharacter.h"
#include "FSMScene.h"
#include "FSMUI.h"
#include "GameManager.h"
#include "ModelBase.h"
#include "ModelEffect.h"
#include "ModelGraph.h"
#include "ModelMovie.h"
#include "ModelMV1.h"
#include "ModelPolygonIndexed.h"
#include "ObjectBases.h"
#include "ResourceEffect.h"
#include "ResourceManager.h"
#include "Resource3DModel.h"
#include "SceneManager.h"
#include "StateAnimation.h"
#include "StateAnimationController.h"
#include "StateBase.h"
#include "StateCamera.h"
#include "StateConfigUi.h"
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
#include "UtilStateConditionFunction.h"

namespace
{
using AnimationCriteria = std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>>;

template <typename StateType>
class AnimationDataState : public StateType
{
private:
	OneAnimationData mAnimationData;

public:
	AnimationDataState(const AnimationCriteria& criteria, const OneAnimationData& animationData)
		: StateType(criteria)
		, mAnimationData(animationData)
	{
	}

	void OnEnter(STATE_ANEMATION_DATA* stateData, int previousState) override
	{
		stateData->nowAnimationData = &mAnimationData;
		StateType::OnEnter(stateData, previousState);
	}
};

class MV1ExternalAnimationState : public StateMVOneOnlyAnimation
{
private:
	OneAnimationData mAnimationData;

public:
	MV1ExternalAnimationState(const AnimationCriteria& criteria, int modelHandle, const OneAnimationData& animationData)
		: StateMVOneOnlyAnimation(criteria, modelHandle)
		, mAnimationData(animationData)
	{
		SetMyAniamtionData(mAnimationData);
	}

	void OnEnter(STATE_ANEMATION_DATA* stateData, int previousState) override
	{
		stateData->nowAnimationData = &mAnimationData;
		StateMVOneOnlyAnimation::OnEnter(stateData, previousState);
	}
};

class MV1OperationAnimationState : public StateMVOneOperationAnimation
{
private:
	OneAnimationData mAnimationData;

public:
	MV1OperationAnimationState(const AnimationCriteria& criteria, int modelHandle, const OneAnimationData& animationData)
		: StateMVOneOperationAnimation(criteria, UtilCalc::VZero, UtilCalc::VZero, UtilCalc::VZero, modelHandle)
		, mAnimationData(animationData)
	{
		SetMyAniamtionData(mAnimationData);
	}

	void OnEnter(STATE_ANEMATION_DATA* stateData, int previousState) override
	{
		stateData->nowAnimationData = &mAnimationData;
		StateMVOneOperationAnimation::OnEnter(stateData, previousState);
	}
};

bool IsAnimationMoveAllowed(ANIMATION_FACTORY_NUMBER factoryNumber, ANIMATION_MOVE_TYPE moveType)
{
	switch (factoryNumber)
	{
	case ANIMATION_FACTORY_NUMBER::TOWN:
	case ANIMATION_FACTORY_NUMBER::DUNGEON:
		return moveType == ANIMATION_MOVE_TYPE::IDLE || moveType == ANIMATION_MOVE_TYPE::WALK;
	case ANIMATION_FACTORY_NUMBER::BATTLE:
		return moveType != ANIMATION_MOVE_TYPE::DISPLAY_MOVE &&
			moveType != ANIMATION_MOVE_TYPE::FADE_IN &&
			moveType != ANIMATION_MOVE_TYPE::FADE_OUT;
	case ANIMATION_FACTORY_NUMBER::SHOT_ATTACK:
		return moveType == ANIMATION_MOVE_TYPE::IDLE ||
			moveType == ANIMATION_MOVE_TYPE::ATTACK_IN ||
			moveType == ANIMATION_MOVE_TYPE::ATTACK ||
			moveType == ANIMATION_MOVE_TYPE::ATTACK_OUT;
	case ANIMATION_FACTORY_NUMBER::UI:
		return moveType == ANIMATION_MOVE_TYPE::IDLE ||
			moveType == ANIMATION_MOVE_TYPE::DISPLAY_MOVE ||
			moveType == ANIMATION_MOVE_TYPE::FADE_IN ||
			moveType == ANIMATION_MOVE_TYPE::FADE_OUT;
	}
	return false;
}

OneAnimationData CreateOneAnimationData(const LoadAnimationData& source)
{
	OneAnimationData result{};
	result.number = source.animationIndex;
	result.loopFlag = source.animationLoopFlag;
	result.modelType = source.modelType;
	result.blendMode = source.blendMode;
	result.blendParameter = source.blendParameter;

	switch (source.modelType)
	{
	case ANIMATION_TYPE::MV1_MODEL_ONLY:
	case ANIMATION_TYPE::MV1_MODEL_MOVE:
		result.number = Master::mpResourceManager->Get3DModelResource()->GetResourceHandle(source.animationPath);
		break;
	case ANIMATION_TYPE::EFFECT:
	{
		float effectSize = source.size;
		result.number = Master::mpResourceManager->GetEffectResource()->GetResourceHandle(source.animationPath, &effectSize);
		break;
	}
	default:
		break;
	}

	return result;
}
}

// // アニメション有限状態マシン作成
// FSMAnimation* UtilFactorys::FSMAnimationFactory(Animation* animation, ANIMATION_FACTORY_NUMBER animationFactoryNumber, LOAD_ANIMATION_DATA_FACTORY_NUMBER ladoAnimationDataFactorynumber, std::vector<std::vector<LoadAnimationData>> loadAnimationData)
// {
// 	// FSM生成
// 	FSMAnimation* fsm = new FSMAnimation();
	
// 	// HACK: 一時的にnullではじいてる
// 	// 必要変数取得
// 	std::vector<AnimationDatas*> animationDatas;
// 	std::vector<ModelBase*> modelBases;
// 	animationDatas.clear();
// 	modelBases.clear();
// 	if (animation != nullptr)
// 	{
// 		animationDatas = animation->GetAnimationDatas();
// 		modelBases = animation->GetModelsController()->GetModelList();
		
// 		// サイズ設定
// 		fsm->IncreaseAnimationStateSize((int)animationDatas.size());
// 	}
// 	else
// 	{
// 		fsm->IncreaseAnimationStateSize(0);
// 	}

// 	switch (animationFactoryNumber)
// 	{
// 	case ANIMATION_FACTORY_NUMBER::TOWN:
// 		switch (ladoAnimationDataFactorynumber)
// 		{
// 		case LOAD_ANIMATION_DATA_FACTORY_NUMBER::ROBOT:
// 		case LOAD_ANIMATION_DATA_FACTORY_NUMBER::HUMAN:
// 			fsm->RegisterState(new StateIdleAnimationController());
// 			fsm->RegisterState(new StateMoveAnimationController());
// 			break;
// 		}
// 		break;

// 	case ANIMATION_FACTORY_NUMBER::DUNGEON:
// 		switch (ladoAnimationDataFactorynumber)
// 		{
// 		case LOAD_ANIMATION_DATA_FACTORY_NUMBER::ROBOT:
// 		case LOAD_ANIMATION_DATA_FACTORY_NUMBER::HUMAN:
// 			fsm->RegisterState(new StateIdleAnimationController());
// 			fsm->RegisterState(new StateMoveAnimationController());
// 			break;
// 		}
// 		break;

// 	case ANIMATION_FACTORY_NUMBER::BATTLE:
// 		switch (ladoAnimationDataFactorynumber)
// 		{
// 		case LOAD_ANIMATION_DATA_FACTORY_NUMBER::HUMAN:
// 			fsm->RegisterState(new StateIdleAnimationController());
// 			fsm->RegisterState(new StateMoveAnimationController());
// 			fsm->RegisterState(new StateAttackEndAnimationController());
// 			break;

// 		case LOAD_ANIMATION_DATA_FACTORY_NUMBER::ROBOT:
// 			fsm->RegisterState(new StateIdleAnimationController());
// 			fsm->RegisterState(new StateMoveAnimationController());

// 			fsm->RegisterState(new StateSpceialAttackInAnimationController());
// 			fsm->RegisterState(new StateSpceialAttackAnimationController());
// 			fsm->RegisterState(new StateSpceialAttackOutAnimationController());

// 			fsm->RegisterState(new StateJumpAttackInAnimationController());
// 			fsm->RegisterState(new StateJumpAttackAnimationController());
// 			fsm->RegisterState(new StateJumpAttackOutAnimationController());

// 			StateNormalAttackInAnimationController* stateNormalAttackInAnimationController = new StateNormalAttackInAnimationController();
// 			fsm->RegisterState(stateNormalAttackInAnimationController);
// 			stateNormalAttackInAnimationController->SetAddEndTime(1000);// TODO: 何かし形を変える
// 			fsm->RegisterState(new StateNormalAttackOutAnimationController());
// 			break;
// 		}
// 		break;

// 	case ANIMATION_FACTORY_NUMBER::SHOT_ATTACK:
// 		switch (ladoAnimationDataFactorynumber)
// 		{
// 		case LOAD_ANIMATION_DATA_FACTORY_NUMBER::SHOT_ATTACK:
// 		case LOAD_ANIMATION_DATA_FACTORY_NUMBER::JUMP_ROBOT_ATTACK:
// 		case LOAD_ANIMATION_DATA_FACTORY_NUMBER::ROBOT_SPCEIAL:
// 			fsm->RegisterState(new StateAttackIdleAnimationController());

// 			fsm->RegisterState(new StateAttackInAnimationController());
// 			fsm->RegisterState(new StateAttackAnimationController());
// 			fsm->RegisterState(new StateAttackEndAnimationController());
// 			break;
// 		}
// 		break;

// 	case ANIMATION_FACTORY_NUMBER::UI:
// 		switch (ladoAnimationDataFactorynumber)
// 		{
// 		case LOAD_ANIMATION_DATA_FACTORY_NUMBER::UI_BASE:
// 		case LOAD_ANIMATION_DATA_FACTORY_NUMBER::UI_BASE_MOVIE:
// 			fsm->RegisterState(new StateIdleAnimationController());
// 			fsm->RegisterState(new State2DMoveAnimationController());
// 			fsm->RegisterState(new StateFadeOutAnimationController());
// 			fsm->RegisterState(new StateFadeInAnimationController());
// 			break;

// 		case LOAD_ANIMATION_DATA_FACTORY_NUMBER::UI_FADE:
// 			fsm->RegisterState(new StateIdleAnimationController());
// 			fsm->RegisterState(new State2DMoveAnimationController());
// 			fsm->RegisterState(new StateFadeOutAnimationController());
// 			fsm->RegisterState(new StateFadeInAnimationController());
// 			break;
// 		}
// 		break;
// 	}

// 	// モデルの数分設定する
// 	for (int i = 0; i < loadAnimationData.size(); i++)
// 	{
// 		std::map<ANIMATION_TYPE, IStateAnimation*> setStateMap;

// 		for (int j = 0; j < loadAnimationData[i].size(); j++)
// 		{
// 			// TODO: テンプレートでswitch分の中身簡単にできる気がする
// 			ANIMATION_TYPE setModelType = animationDatas[i]->animDatas[loadAnimationData[i][j].animationType].modelType;
// 			// アニメションステート生成
// 			switch (setModelType)
// 			{
// 			case ANIMATION_TYPE::NONE:
// 				if (setStateMap.find(setModelType) == setStateMap.end())
// 				{
// 					StateNoneAnimation* statenoneAnimation = new StateNoneAnimation();
// 					statenoneAnimation->SetModelBase(modelBases[i]);
// 					setStateMap[setModelType] = statenoneAnimation;
// 				}
// 				break;

// 			case ANIMATION_TYPE::MV1_MODEL:
// 				if (setStateMap.find(setModelType) == setStateMap.end())
// 				{
// 					// HACK: 外部から固定するフレームの名前を取得できるようにする
// 					StateMVOneAnimation* stateMVOneAnimation = new StateMVOneAnimation(modelBases[i]->GetHandle(), "root");
// 					stateMVOneAnimation->SetModelBase(modelBases[i]);
// 					setStateMap[setModelType] = stateMVOneAnimation;
// 				}
// 				break;

// 			case ANIMATION_TYPE::MV1_MODEL_MOVE:
// 				if (setStateMap.find(setModelType) == setStateMap.end())
// 				{
// 					// HACK: 仮設定
// 					StateMVOneOperationAnimation* stateMVOneOperationAnimation = new StateMVOneOperationAnimation(modelBases[i]->GetHandle(), VGet(00.0f, 00.0f, 00.0f), VGet(10.0f, 0.0f, 0.0f), VGet(0.0f, 0.0f, 0.0f));
// 					stateMVOneOperationAnimation->SetModelBase(modelBases[i]);
// 					setStateMap[setModelType] = stateMVOneOperationAnimation;
// 				}
// 				break;

// 			case ANIMATION_TYPE::MV1_MODEL_ONLY:
// 				if (setStateMap.find(setModelType) == setStateMap.end())
// 				{
// 					StateMVOneOnlyAnimation* stateMVOneOnlyAnimation = new StateMVOneOnlyAnimation(modelBases[i]->GetHandle());
// 					stateMVOneOnlyAnimation->SetModelBase(modelBases[i]);
// 					setStateMap[setModelType] = stateMVOneOnlyAnimation;
// 				}
// 				break;

// 			case ANIMATION_TYPE::EFFECT:
// 				if (setStateMap.find(setModelType) == setStateMap.end())
// 				{
// 					StateEffectAnimation* stateEffectAnimation = new StateEffectAnimation(modelBases[i]->GetHandlePointer());
// 					stateEffectAnimation->SetModelBase(modelBases[i]);
// 					setStateMap[setModelType] = stateEffectAnimation;
// 				}
// 				break;

// 			case ANIMATION_TYPE::GRAPH:
// 				if (setStateMap.find(setModelType) == setStateMap.end())
// 				{
// 					StateGraphAnimation* stateGraphAnimation = new StateGraphAnimation();
// 					stateGraphAnimation->SetModelBase(modelBases[i]);
// 					setStateMap[setModelType] = stateGraphAnimation;
// 				}
// 				break;

// 			case ANIMATION_TYPE::MOVIE:
// 				if (setStateMap.find(setModelType) == setStateMap.end())
// 				{
// 					StateMovieAnimation* stateMovieAnimation = new StateMovieAnimation();
// 					stateMovieAnimation->SetModelBase(modelBases[i]);
// 					setStateMap[setModelType] = stateMovieAnimation;
// 				}
// 				break;

// 			case ANIMATION_TYPE::FADE:
// 				if (setStateMap.find(setModelType) == setStateMap.end())
// 				{
// 					StateFadeGraphAnimation* stateFadeGraphAnimation = new StateFadeGraphAnimation();
// 					stateFadeGraphAnimation->SetModelBase(modelBases[i]);
// 					setStateMap[setModelType] = stateFadeGraphAnimation;
// 				}
// 				break;
// 			}
// 		}

// 		fsm->SetAnimationStateDatas(i, setStateMap);
// 	}

// 	// 初期化
// 	fsm->Initilize(animation);

// 	return fsm;
// }

// // アニメーションデータ作成
// AnimationDatas* UtilFactorys::AnimationDataFactory(std::vector<LoadAnimationData> loadAnimationData)
// {
// 	AnimationDatas* animationDataMap = new AnimationDatas();
// 	OneAnimationData animationData;
// 	animationData.animationHandle = -1;
// 	animationData.animationCount = 0.0f;
// 	animationDataMap->animDatas.clear();

// 	for (int i = 0; i < loadAnimationData.size(); i++)
// 	{
// 		switch (loadAnimationData[i].modelType)
// 		{
// 		case ANIMATION_TYPE::NONE:
// 			animationData.number = -1;
// 			animationData.loopFlag = loadAnimationData[i].animationLoopFlag;
// 			animationData.modelType = loadAnimationData[i].modelType;

// 			// 設定
// 			animationDataMap->animDatas[loadAnimationData[i].animationType] = animationData;
// 			break;

// 		case ANIMATION_TYPE::MV1_MODEL:
// 			// アニメション添え字設定
// 			animationData.number = loadAnimationData[i].animationIndex;
// 			animationData.loopFlag = loadAnimationData[i].animationLoopFlag;
// 			animationData.modelType = loadAnimationData[i].modelType;

// 			// 設定
// 			animationDataMap->animDatas[loadAnimationData[i].animationType] = animationData;
// 			break;

// 		case ANIMATION_TYPE::MV1_MODEL_MOVE:
// 		case ANIMATION_TYPE::MV1_MODEL_ONLY:
// 			// アニメション読み込み
// 			animationData.number = Master::mpResourceManager->Get3DModelResource()->GetResourceHandle(loadAnimationData[i].animationPath);
// 			animationData.loopFlag = loadAnimationData[i].animationLoopFlag;
// 			animationData.modelType = loadAnimationData[i].modelType;

// 			// 設定
// 			animationDataMap->animDatas[loadAnimationData[i].animationType] = animationData;
// 			break;

// 		case ANIMATION_TYPE::EFFECT:
// 			// エフェクトリソース取得
// 			animationData.number = Master::mpResourceManager->GetEffectResource()->GetResourceHandle(loadAnimationData[i].animationPath, &loadAnimationData[i].size);
// 			animationData.loopFlag = loadAnimationData[i].animationLoopFlag;
// 			animationData.modelType = loadAnimationData[i].modelType;

// 			// 設定
// 			animationDataMap->animDatas[loadAnimationData[i].animationType] = animationData;		
// 			break;

// 		case ANIMATION_TYPE::GRAPH:
// 		case ANIMATION_TYPE::MOVIE:
// 			animationData.loopFlag = loadAnimationData[i].animationLoopFlag;
// 			animationData.modelType = loadAnimationData[i].modelType;

// 			// 設定
// 			animationDataMap->animDatas[loadAnimationData[i].animationType] = animationData;	
// 			break;

// 		case ANIMATION_TYPE::FADE:
// 			animationData.loopFlag = loadAnimationData[i].animationLoopFlag;
// 			animationData.modelType = loadAnimationData[i].modelType;

// 			// ブレンド設定
// 			animationData.blendMode = loadAnimationData[i].blendMode;
// 			animationData.blendParameter = loadAnimationData[i].blendParameter;

// 			// 設定
// 			animationDataMap->animDatas[loadAnimationData[i].animationType] = animationData;
// 			break;
// 		}
// 	}

// 	return animationDataMap;
// }

// /*読み込み用アニメーションデータ作成*/
// std::vector<LoadAnimationData> UtilFactorys::LoadAnimationDataFactory(Animation* animation, LOAD_ANIMATION_DATA_FACTORY_NUMBER number)
// {
// 	std::vector<LoadAnimationData> loadAnimationData;
// 	loadAnimationData.clear();

// 	switch (number)
// 	{
// 	case LOAD_ANIMATION_DATA_FACTORY_NUMBER::HUMAN:
// 		for (int i = 0; i < 6; i++)
// 		{
// 			LoadAnimationData loadAnimaData;
// 			loadAnimaData.animationIndex = i;
// 			loadAnimaData.modelType = ANIMATION_TYPE::MV1_MODEL;
// 			loadAnimationData.push_back(loadAnimaData);
// 		}
// 		// HACK: データマネージャーから取得できるようにする
// 		loadAnimationData[0].animationType = ANIMATION_MOVE_TYPE::IDLE;
// 		loadAnimationData[0].animationLoopFlag = true;
// 		loadAnimationData[1].animationType = ANIMATION_MOVE_TYPE::WALK;
// 		loadAnimationData[1].animationLoopFlag = true;
// 		loadAnimationData[2].animationType = ANIMATION_MOVE_TYPE::JUMP_IN;
// 		loadAnimationData[2].animationLoopFlag = false;
// 		loadAnimationData[3].animationType = ANIMATION_MOVE_TYPE::JUMP;
// 		loadAnimationData[3].animationLoopFlag = false;
// 		loadAnimationData[4].animationType = ANIMATION_MOVE_TYPE::JUMP_OUT;
// 		loadAnimationData[4].animationLoopFlag = false;
// 		loadAnimationData[5].animationType = ANIMATION_MOVE_TYPE::ATTACK;
// 		loadAnimationData[5].animationLoopFlag = false;

// 		if (animation != nullptr)
// 		{
// 			// TODO: データマネージャーから取得できる形式にしたい
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::IDLE, 0);
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::WALK, 0);
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::JUMP_IN, 0);
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::JUMP, 0);
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::JUMP_OUT, 0);
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::ATTACK, 1156);
// 			animation->AddAnimationData(UtilFactorys::AnimationDataFactory(loadAnimationData));
// 		}
// 		break;

// 	case LOAD_ANIMATION_DATA_FACTORY_NUMBER::ROBOT:
// 		for (int i = 0; i < 10; i++)
// 		{
// 			LoadAnimationData loadAnimaData;
// 			loadAnimaData.animationIndex = i;
// 			loadAnimaData.modelType = ANIMATION_TYPE::MV1_MODEL_ONLY;
// 			loadAnimationData.push_back(loadAnimaData);
// 		}
// 		// HACK: データマネージャーから取得できるようにする
// 		loadAnimationData[0].animationType = ANIMATION_MOVE_TYPE::IDLE;
// 		loadAnimationData[0].animationLoopFlag = true;
// 		loadAnimationData[0].animationPath = ResourceManager::msResourceFile + "3D/Robot/Animation/robotSphere@anim_Idle_Loop_S.mv1";

// 		loadAnimationData[1].animationType = ANIMATION_MOVE_TYPE::WALK;
// 		loadAnimationData[1].animationLoopFlag = true;
// 		loadAnimationData[1].animationPath = ResourceManager::msResourceFile + "3D/Robot/Animation/robotSphere@anim_open_Walk_Loop.mv1";

// 		loadAnimationData[2].animationType = ANIMATION_MOVE_TYPE::SPCEIAL_ATTACK_IN;
// 		loadAnimationData[2].animationLoopFlag = false;
// 		loadAnimationData[2].animationPath = ResourceManager::msResourceFile + "3D/Robot/Animation/robotSphere@anim_open_GoToRoll.mv1";

// 		loadAnimationData[3].animationType = ANIMATION_MOVE_TYPE::SPCEIAL_ATTACK;
// 		loadAnimationData[3].animationLoopFlag = false;
// 		loadAnimationData[3].animationPath = ResourceManager::msResourceFile + "3D/Robot/Animation/robotSphere@anim_cloed_Roll_Loop.mv1";
// 		loadAnimationData[3].modelType = ANIMATION_TYPE::MV1_MODEL_MOVE;

// 		loadAnimationData[4].animationType = ANIMATION_MOVE_TYPE::SPCEIAL_ATTACK_OUT;
// 		loadAnimationData[4].animationLoopFlag = false;
// 		loadAnimationData[4].animationPath = ResourceManager::msResourceFile + "3D/Robot/Animation/robotSphere@anim_closed_StopRoll.mv1";

// 		loadAnimationData[5].animationType = ANIMATION_MOVE_TYPE::NORMAL_ATTACK_IN;
// 		loadAnimationData[5].animationLoopFlag = false;
// 		loadAnimationData[5].animationPath = ResourceManager::msResourceFile + "3D/Robot/Animation/robotSphere@anim_close.mv1";

// 		loadAnimationData[6].animationType = ANIMATION_MOVE_TYPE::NORMAL_ATTACK_OUT;
// 		loadAnimationData[6].animationLoopFlag = false;
// 		loadAnimationData[6].animationPath = ResourceManager::msResourceFile + "3D/Robot/Animation/robotSphere@anim_closed_StopRoll.mv1";

// 		loadAnimationData[7].animationType = ANIMATION_MOVE_TYPE::JUMP_ATTACK_IN;
// 		loadAnimationData[7].animationLoopFlag = false;
// 		loadAnimationData[7].animationPath = ResourceManager::msResourceFile + "3D/Robot/Animation/robotSphere@anim_close.mv1";

// 		loadAnimationData[8].animationType = ANIMATION_MOVE_TYPE::JUMP_ATTACK;
// 		loadAnimationData[8].animationLoopFlag = false;
// 		loadAnimationData[8].animationPath = ResourceManager::msResourceFile + "3D/Robot/Animation/robotSphere@anim_cloed_Roll_Loop.mv1";

// 		loadAnimationData[9].animationType = ANIMATION_MOVE_TYPE::JUMP_ATTACK_OUT;
// 		loadAnimationData[9].animationLoopFlag = false;
// 		loadAnimationData[9].animationPath = ResourceManager::msResourceFile + "3D/Robot/Animation/robotSphere@anim_cloed_Roll_Loop.mv1";

// 		if (animation != nullptr)
// 		{
// 			// TODO: データマネージャーから取得できる形式にしたい アニメションが終わったら次に行くのも追加したい
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::IDLE, 0);
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::WALK, 0);
// 			// animation->SetAnimationTime(ANIMATION_MOVE_TYPE::ATTACK_IN,  2040/*(60 / 0.5) * 17*/);
// 			// animation->SetAnimationTime(ANIMATION_MOVE_TYPE::ATTACK, 	20400 /*(6 / 0.5) * 17 * 1/*回転数*/);
// 			// animation->SetAnimationTime(ANIMATION_MOVE_TYPE::ATTACK_OUT, 1632/*(48 / 0.5) * 17*/);
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::SPCEIAL_ATTACK_IN, 2040);
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::SPCEIAL_ATTACK, 2040);
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::SPCEIAL_ATTACK_OUT, 1632);
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::NORMAL_ATTACK_IN, 1088/*(48 / 0.5) * 17*/);
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::NORMAL_ATTACK_OUT, 1632/*(48 / 0.5) * 17*/);

// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::JUMP_ATTACK_IN, 1088/*(48 / 0.5) * 17*/);
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::JUMP_ATTACK, 1088/*(48 / 0.5) * 17*/);
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::JUMP_ATTACK_OUT, 1632/*(48 / 0.5) * 17*/);
// 			animation->AddAnimationData(UtilFactorys::AnimationDataFactory(loadAnimationData));
// 		}
// 		break;

// 	case LOAD_ANIMATION_DATA_FACTORY_NUMBER::SHOT_ATTACK:
// 		for (int i = 0; i < 4; i++)
// 		{
// 			LoadAnimationData loadAnimaData;
// 			loadAnimaData.animationIndex = i;
// 			loadAnimaData.animationLoopFlag = false;
// 			loadAnimaData.modelType = ANIMATION_TYPE::NONE;
// 			loadAnimaData.animationPath = "";
// 			loadAnimationData.push_back(loadAnimaData);
// 		}
// 		// HACK: データマネージャーから取得できるようにする
// 		loadAnimationData[0].animationType = ANIMATION_MOVE_TYPE::IDLE;
		
// 		loadAnimationData[1].animationType = ANIMATION_MOVE_TYPE::ATTACK_IN;
// 		loadAnimationData[1].modelType = ANIMATION_TYPE::EFFECT;
// 		loadAnimationData[1].animationPath = ResourceManager::msResourceFile + "Effect/Laser.efkefc";
		
// 		loadAnimationData[2].animationType = ANIMATION_MOVE_TYPE::ATTACK;
		
// 		loadAnimationData[3].animationType = ANIMATION_MOVE_TYPE::ATTACK_OUT;
		
// 		if (animation != nullptr)
// 		{
// 			// TODO: データマネージャーから取得できる形式にしたい アニメションが終わったら次に行くのも追加したい
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::IDLE, 0);
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::ATTACK_IN, 2088);
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::ATTACK, 3650);
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::ATTACK_OUT, 0);
// 			animation->AddAnimationData(UtilFactorys::AnimationDataFactory(loadAnimationData));
// 		}
// 		break;

// 	case LOAD_ANIMATION_DATA_FACTORY_NUMBER::JUMP_ROBOT_ATTACK:
// 		for (int i = 0; i < 4; i++)
// 		{
// 			LoadAnimationData loadAnimaData;
// 			loadAnimaData.animationIndex = i;
// 			loadAnimaData.animationLoopFlag = false;
// 			loadAnimaData.modelType = ANIMATION_TYPE::NONE;
// 			loadAnimaData.animationPath = "";
// 			loadAnimationData.push_back(loadAnimaData);
// 		}
// 		// HACK: データマネージャーから取得できるようにする
// 		loadAnimationData[0].animationType = ANIMATION_MOVE_TYPE::IDLE;
		
// 		loadAnimationData[1].animationType = ANIMATION_MOVE_TYPE::ATTACK_IN;
		
// 		loadAnimationData[2].animationType = ANIMATION_MOVE_TYPE::ATTACK;
		
// 		loadAnimationData[3].animationType = ANIMATION_MOVE_TYPE::ATTACK_OUT;
// 		loadAnimationData[3].modelType = ANIMATION_TYPE::EFFECT;
// 		loadAnimationData[3].size = 50.0f;
// 		loadAnimationData[3].animationPath = ResourceManager::msResourceFile + "Effect/StairBroken.efkefc";
		
// 		if (animation != nullptr)
// 		{
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::IDLE, 0);
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::ATTACK_IN, 1088);
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::ATTACK, 1632);
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::ATTACK_OUT, 17 * 50);
// 			animation->AddAnimationData(UtilFactorys::AnimationDataFactory(loadAnimationData));
// 		}
// 		break;

// 	case LOAD_ANIMATION_DATA_FACTORY_NUMBER::ROBOT_SPCEIAL:
// 		for (int i = 0; i < 4; i++)
// 		{
// 			LoadAnimationData loadAnimaData = LoadAnimationData();
// 			loadAnimaData.animationIndex = i;
// 			loadAnimaData.animationLoopFlag = false;
// 			loadAnimaData.modelType = ANIMATION_TYPE::NONE;
// 			loadAnimaData.animationPath = "";
// 			loadAnimationData.push_back(loadAnimaData);
// 		}
// 		// HACK: データマネージャーから取得できるようにする
// 		loadAnimationData[0].animationType = ANIMATION_MOVE_TYPE::IDLE;
		
// 		loadAnimationData[1].animationType = ANIMATION_MOVE_TYPE::ATTACK_IN;
		
// 		loadAnimationData[2].animationType = ANIMATION_MOVE_TYPE::ATTACK;
// 		loadAnimationData[2].modelType = ANIMATION_TYPE::EFFECT;
// 		loadAnimationData[2].size = 10.0f;
// 		loadAnimationData[2].animationPath = ResourceManager::msResourceFile + "Effect/drill.efkefc";
		
// 		loadAnimationData[3].animationType = ANIMATION_MOVE_TYPE::ATTACK_OUT;
		
// 		if (animation != nullptr)
// 		{
// 			// TODO: データマネージャーから取得できる形式にしたい アニメションが終わったら次に行くのも追加したい
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::IDLE, 0);
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::ATTACK_IN, 2024);
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::ATTACK, 2040);
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::ATTACK_OUT, 1632);
// 			animation->AddAnimationData(UtilFactorys::AnimationDataFactory(loadAnimationData));
// 		}
// 		break;

// 	case LOAD_ANIMATION_DATA_FACTORY_NUMBER::UI_BASE:
// 		for (int i = 0; i < 4; i++)
// 		{
// 			LoadAnimationData loadAnimaData;
// 			loadAnimaData.animationIndex = i;
// 			loadAnimaData.animationLoopFlag = false;
// 			loadAnimaData.modelType = ANIMATION_TYPE::GRAPH;
// 			loadAnimaData.animationPath = "";
// 			loadAnimationData.push_back(loadAnimaData);
// 		}
		
// 		loadAnimationData[0].animationType = ANIMATION_MOVE_TYPE::IDLE;
// 		loadAnimationData[1].animationType = ANIMATION_MOVE_TYPE::DISPLAY_MOVE;
// 		loadAnimationData[2].animationType = ANIMATION_MOVE_TYPE::FADE_OUT;
// 		loadAnimationData[3].animationType = ANIMATION_MOVE_TYPE::FADE_IN;
		
// 		if (animation != nullptr)
// 		{
// 			// TODO: データマネージャーから取得できる形式にしたい アニメションが終わったら次に行くのも追加したい
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::IDLE, 0);
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::DISPLAY_MOVE, 0);
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::FADE_OUT, 0);
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::FADE_IN, 0);
// 			animation->AddAnimationData(UtilFactorys::AnimationDataFactory(loadAnimationData));
// 		}
// 		break;

// 	case LOAD_ANIMATION_DATA_FACTORY_NUMBER::UI_BASE_MOVIE:
// 		for (int i = 0; i < 4; i++)
// 		{
// 			LoadAnimationData loadAnimaData;
// 			loadAnimaData.animationIndex = i;
// 			loadAnimaData.animationLoopFlag = false;
// 			loadAnimaData.modelType = ANIMATION_TYPE::MOVIE;
// 			loadAnimaData.animationPath = "";
// 			loadAnimationData.push_back(loadAnimaData);
// 		}
		
// 		loadAnimationData[0].animationType = ANIMATION_MOVE_TYPE::IDLE;
// 		loadAnimationData[1].animationType = ANIMATION_MOVE_TYPE::DISPLAY_MOVE;
// 		loadAnimationData[2].animationType = ANIMATION_MOVE_TYPE::FADE_OUT;
// 		loadAnimationData[3].animationType = ANIMATION_MOVE_TYPE::FADE_IN;
		
// 		if (animation != nullptr)
// 		{
// 			// TODO: データマネージャーから取得できる形式にしたい アニメションが終わったら次に行くのも追加したい
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::IDLE, 0);
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::DISPLAY_MOVE, 0);
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::FADE_OUT, 0);
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::FADE_IN, 0);
// 			animation->AddAnimationData(UtilFactorys::AnimationDataFactory(loadAnimationData));
// 		}
// 		break;

// 	case LOAD_ANIMATION_DATA_FACTORY_NUMBER::UI_FADE:
// 		for (int i = 0; i < 4; i++)
// 		{
// 			LoadAnimationData loadAnimaData;
// 			loadAnimaData.animationIndex = i;
// 			loadAnimaData.animationLoopFlag = false;
// 			loadAnimaData.modelType = ANIMATION_TYPE::GRAPH;
// 			loadAnimaData.animationPath = "";
// 			loadAnimationData.push_back(loadAnimaData);
// 		}
		
// 		loadAnimationData[0].animationType = ANIMATION_MOVE_TYPE::IDLE;
// 		loadAnimationData[1].animationType = ANIMATION_MOVE_TYPE::DISPLAY_MOVE;
// 		loadAnimationData[2].animationType = ANIMATION_MOVE_TYPE::FADE_OUT;
// 		loadAnimationData[2].blendMode = DX_BLENDMODE_ALPHA;
// 		loadAnimationData[2].blendParameter = 11;
// 		loadAnimationData[2].modelType = ANIMATION_TYPE::FADE;
// 		loadAnimationData[3].animationType = ANIMATION_MOVE_TYPE::FADE_IN;
// 		loadAnimationData[3].blendMode = DX_BLENDMODE_ALPHA;
// 		loadAnimationData[3].blendParameter = -11;
// 		loadAnimationData[3].modelType = ANIMATION_TYPE::FADE;
		
// 		if (animation != nullptr)
// 		{
// 			// TODO: データマネージャーから取得できる形式にしたい アニメションが終わったら次に行くのも追加したい
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::IDLE, 0);
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::DISPLAY_MOVE, 0);
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::FADE_OUT, 25 * 17);
// 			animation->SetAnimationTime(ANIMATION_MOVE_TYPE::FADE_IN, 25 * 17);
// 			animation->AddAnimationData(UtilFactorys::AnimationDataFactory(loadAnimationData));
// 		}
// 		break;
// 	}

// 	return loadAnimationData;
// }

// // キャラクタ攻撃情報作成
// CharacterAttackData UtilFactorys::CharacterAttackDataFactory(CHARACTER_ATTACK_DATA_FACTORY__ATTACK_METHOD factoryNumberAttackMethod, CHARACTER_ATTACK_DATA_FACTORY__ANIMATION_TYPE factoryNumberModelType)
// {
// 	// 初期化
// 	CharacterAttackData characterAttackData;
// 	characterAttackData.attackDataNumber = -1;
// 	characterAttackData.modelController = new ModelsControllerBase();
// 	characterAttackData.animation = new Animation();
// 	// 変数にポインタを渡し見やすくする
//     ModelsControllerBase* modelController = characterAttackData.modelController;
//     Animation* animation = characterAttackData.animation;
// 	// モデル初期化
// 	modelController->Initilize();
// 	// アニメーション初期化
// 	animation->Initilize();
// 	animation->SetModelsController(modelController);
	

// 	// モデル設定
// 	switch (factoryNumberAttackMethod)
// 	{
// 	case CHARACTER_ATTACK_DATA_FACTORY__ATTACK_METHOD::SHOT_NORMAL:
// 		modelController->AddModel(UtilFactorys::ModelFactory(ANIMATION_TYPE::EFFECT, "", VGet(0.0f, 1.0f, 3.0f), UtilCalc::VZero, VScale(UtilCalc::VOne, 100.0f)));
// 		break;
	
// 	case CHARACTER_ATTACK_DATA_FACTORY__ATTACK_METHOD::SHOT_SPCEIAL:
// 		switch (factoryNumberModelType)
// 		{
// 		case CHARACTER_ATTACK_DATA_FACTORY__ANIMATION_TYPE::ROBOT:
// 			modelController->AddModel(UtilFactorys::ModelFactory(ANIMATION_TYPE::EFFECT, "", UtilCalc::VZero, UtilCalc::VZero, VScale(UtilCalc::VOne, 20.0f)));
// 			break;
// 		}
// 		break;
	
// 	case CHARACTER_ATTACK_DATA_FACTORY__ATTACK_METHOD::JUMP_ATTACK:
// 		switch (factoryNumberModelType)
// 		{
// 		case CHARACTER_ATTACK_DATA_FACTORY__ANIMATION_TYPE::ROBOT:
// 			modelController->AddModel(UtilFactorys::ModelFactory(ANIMATION_TYPE::EFFECT, "", VGet(0.0f, 1.0f, 3.0f), UtilCalc::VZero, VScale(UtilCalc::VOne, 100.0f)));
// 			break;
// 		}
// 		break;
// 	}

// 	// アニメーション設定
//  	std::vector<std::vector<LoadAnimationData>> setcharacterLoadAnimationData;
// 	switch (factoryNumberAttackMethod)
// 	{
// 	case CHARACTER_ATTACK_DATA_FACTORY__ATTACK_METHOD::SHOT_NORMAL:
// 	 	// 読み込み用アニメーションデータ設定
// 	 	setcharacterLoadAnimationData.push_back(UtilFactorys::LoadAnimationDataFactory(animation, LOAD_ANIMATION_DATA_FACTORY_NUMBER::SHOT_ATTACK));
// 	 	// アニメーション有限状態マシン設定
// 	 	animation->SetFsm(UtilFactorys::FSMAnimationFactory(animation, ANIMATION_FACTORY_NUMBER::SHOT_ATTACK, LOAD_ANIMATION_DATA_FACTORY_NUMBER::SHOT_ATTACK, setcharacterLoadAnimationData));
// 		break;
	
// 	case CHARACTER_ATTACK_DATA_FACTORY__ATTACK_METHOD::SHOT_SPCEIAL:
// 		switch (factoryNumberModelType)
// 		{
// 		case CHARACTER_ATTACK_DATA_FACTORY__ANIMATION_TYPE::ROBOT:
// 		 	// 読み込み用アニメーションデータ設定
// 			setcharacterLoadAnimationData.push_back(UtilFactorys::LoadAnimationDataFactory(animation, LOAD_ANIMATION_DATA_FACTORY_NUMBER::ROBOT_SPCEIAL));
// 			// アニメーション有限状態マシン設定
// 			animation->SetFsm(UtilFactorys::FSMAnimationFactory(animation, ANIMATION_FACTORY_NUMBER::SHOT_ATTACK, LOAD_ANIMATION_DATA_FACTORY_NUMBER::ROBOT_SPCEIAL, setcharacterLoadAnimationData));
// 			break;
// 		}
// 		break;
	
// 	case CHARACTER_ATTACK_DATA_FACTORY__ATTACK_METHOD::JUMP_ATTACK:
// 		switch (factoryNumberModelType)
// 		{
// 		case CHARACTER_ATTACK_DATA_FACTORY__ANIMATION_TYPE::ROBOT:
// 		 	// 読み込み用アニメーションデータ設定
// 			setcharacterLoadAnimationData.push_back(UtilFactorys::LoadAnimationDataFactory(animation, LOAD_ANIMATION_DATA_FACTORY_NUMBER::JUMP_ROBOT_ATTACK));
// 			// アニメーション有限状態マシン設定
// 			animation->SetFsm(UtilFactorys::FSMAnimationFactory(animation, ANIMATION_FACTORY_NUMBER::SHOT_ATTACK, LOAD_ANIMATION_DATA_FACTORY_NUMBER::JUMP_ROBOT_ATTACK, setcharacterLoadAnimationData));
// 			break;
// 		}
// 		break;
// 	}

std::vector<LoadAnimationData> UtilFactorys::LoadAnimationDataFactory(LOAD_ANIMATION_DATA_FACTORY_NUMBER number)
{
	std::vector<LoadAnimationData> animationData;
	auto add = [&animationData](ANIMATION_MOVE_TYPE moveType, ANIMATION_TYPE modelType, int index, bool loop, const std::string& path = std::string(), float size = 1.0f, int blendMode = 0, int blendParameter = 0)
	{
		LoadAnimationData data{};
		data.animationType = moveType;
		data.modelType = modelType;
		data.animationIndex = index;
		data.animationLoopFlag = loop;
		data.animationPath = path;
		data.size = size;
		data.blendMode = blendMode;
		data.blendParameter = blendParameter;
		animationData.push_back(data);
	};

	const std::string robotAnimationPath = ResourceManager::msResourceFile + "3D/Robot/Animation/";
	switch (number)
	{
	case LOAD_ANIMATION_DATA_FACTORY_NUMBER::HUMAN:
		add(ANIMATION_MOVE_TYPE::IDLE, ANIMATION_TYPE::MV1_MODEL, 0, true);
		add(ANIMATION_MOVE_TYPE::WALK, ANIMATION_TYPE::MV1_MODEL, 1, true);
		add(ANIMATION_MOVE_TYPE::JUMP_IN, ANIMATION_TYPE::MV1_MODEL, 2, false);
		add(ANIMATION_MOVE_TYPE::JUMP, ANIMATION_TYPE::MV1_MODEL, 3, false);
		add(ANIMATION_MOVE_TYPE::JUMP_OUT, ANIMATION_TYPE::MV1_MODEL, 4, false);
		add(ANIMATION_MOVE_TYPE::ATTACK, ANIMATION_TYPE::MV1_MODEL, 5, false);
		break;

	case LOAD_ANIMATION_DATA_FACTORY_NUMBER::ROBOT:
		add(ANIMATION_MOVE_TYPE::IDLE, ANIMATION_TYPE::MV1_MODEL_ONLY, 0, true, robotAnimationPath + "robotSphere@anim_Idle_Loop_S.mv1");
		add(ANIMATION_MOVE_TYPE::WALK, ANIMATION_TYPE::MV1_MODEL_ONLY, 0, true, robotAnimationPath + "robotSphere@anim_open_Walk_Loop.mv1");
		add(ANIMATION_MOVE_TYPE::SPCEIAL_ATTACK_IN, ANIMATION_TYPE::MV1_MODEL_ONLY, 0, false, robotAnimationPath + "robotSphere@anim_open_GoToRoll.mv1");
		add(ANIMATION_MOVE_TYPE::SPCEIAL_ATTACK, ANIMATION_TYPE::MV1_MODEL_MOVE, 0, false, robotAnimationPath + "robotSphere@anim_cloed_Roll_Loop.mv1");
		add(ANIMATION_MOVE_TYPE::SPCEIAL_ATTACK_OUT, ANIMATION_TYPE::MV1_MODEL_ONLY, 0, false, robotAnimationPath + "robotSphere@anim_closed_StopRoll.mv1");
		add(ANIMATION_MOVE_TYPE::NORMAL_ATTACK_IN, ANIMATION_TYPE::MV1_MODEL_ONLY, 0, false, robotAnimationPath + "robotSphere@anim_close.mv1");
		add(ANIMATION_MOVE_TYPE::NORMAL_ATTACK_OUT, ANIMATION_TYPE::MV1_MODEL_ONLY, 0, false, robotAnimationPath + "robotSphere@anim_closed_StopRoll.mv1");
		add(ANIMATION_MOVE_TYPE::JUMP_ATTACK_IN, ANIMATION_TYPE::MV1_MODEL_ONLY, 0, false, robotAnimationPath + "robotSphere@anim_close.mv1");
		add(ANIMATION_MOVE_TYPE::JUMP_ATTACK, ANIMATION_TYPE::MV1_MODEL_MOVE, 0, false, robotAnimationPath + "robotSphere@anim_cloed_Roll_Loop.mv1");
		add(ANIMATION_MOVE_TYPE::JUMP_ATTACK_OUT, ANIMATION_TYPE::MV1_MODEL_MOVE, 0, false, robotAnimationPath + "robotSphere@anim_cloed_Roll_Loop.mv1");
		break;

	case LOAD_ANIMATION_DATA_FACTORY_NUMBER::SHOT_ATTACK:
		add(ANIMATION_MOVE_TYPE::IDLE, ANIMATION_TYPE::NONE, -1, false);
		add(ANIMATION_MOVE_TYPE::ATTACK_IN, ANIMATION_TYPE::EFFECT, -1, false, ResourceManager::msResourceFile + "Effect/Laser.efkefc");
		add(ANIMATION_MOVE_TYPE::ATTACK, ANIMATION_TYPE::NONE, -1, false);
		add(ANIMATION_MOVE_TYPE::ATTACK_OUT, ANIMATION_TYPE::NONE, -1, false);
		break;

	case LOAD_ANIMATION_DATA_FACTORY_NUMBER::ROBOT_SPCEIAL:
		add(ANIMATION_MOVE_TYPE::IDLE, ANIMATION_TYPE::NONE, -1, false);
		add(ANIMATION_MOVE_TYPE::ATTACK_IN, ANIMATION_TYPE::NONE, -1, false);
		add(ANIMATION_MOVE_TYPE::ATTACK, ANIMATION_TYPE::EFFECT, -1, false, ResourceManager::msResourceFile + "Effect/drill.efkefc", 10.0f);
		add(ANIMATION_MOVE_TYPE::ATTACK_OUT, ANIMATION_TYPE::NONE, -1, false);
		break;

	case LOAD_ANIMATION_DATA_FACTORY_NUMBER::JUMP_ROBOT_ATTACK:
		add(ANIMATION_MOVE_TYPE::IDLE, ANIMATION_TYPE::NONE, -1, false);
		add(ANIMATION_MOVE_TYPE::ATTACK_IN, ANIMATION_TYPE::NONE, -1, false);
		add(ANIMATION_MOVE_TYPE::ATTACK, ANIMATION_TYPE::NONE, -1, false);
		add(ANIMATION_MOVE_TYPE::ATTACK_OUT, ANIMATION_TYPE::EFFECT, -1, false, ResourceManager::msResourceFile + "Effect/StairBroken.efkefc", 50.0f);
		break;

	case LOAD_ANIMATION_DATA_FACTORY_NUMBER::UI_BASE:
		add(ANIMATION_MOVE_TYPE::IDLE, ANIMATION_TYPE::GRAPH, -1, false);
		add(ANIMATION_MOVE_TYPE::DISPLAY_MOVE, ANIMATION_TYPE::GRAPH, -1, false);
		add(ANIMATION_MOVE_TYPE::FADE_OUT, ANIMATION_TYPE::GRAPH, -1, false);
		add(ANIMATION_MOVE_TYPE::FADE_IN, ANIMATION_TYPE::GRAPH, -1, false);
		break;

	case LOAD_ANIMATION_DATA_FACTORY_NUMBER::UI_BASE_MOVIE:
		add(ANIMATION_MOVE_TYPE::IDLE, ANIMATION_TYPE::MOVIE, -1, false);
		add(ANIMATION_MOVE_TYPE::DISPLAY_MOVE, ANIMATION_TYPE::MOVIE, -1, false);
		add(ANIMATION_MOVE_TYPE::FADE_OUT, ANIMATION_TYPE::MOVIE, -1, false);
		add(ANIMATION_MOVE_TYPE::FADE_IN, ANIMATION_TYPE::MOVIE, -1, false);
		break;

	case LOAD_ANIMATION_DATA_FACTORY_NUMBER::UI_FADE:
		add(ANIMATION_MOVE_TYPE::IDLE, ANIMATION_TYPE::GRAPH, -1, false);
		add(ANIMATION_MOVE_TYPE::DISPLAY_MOVE, ANIMATION_TYPE::GRAPH, -1, false);
		add(ANIMATION_MOVE_TYPE::FADE_OUT, ANIMATION_TYPE::FADE, -1, false, std::string(), 1.0f, DX_BLENDMODE_ALPHA, 11);
		add(ANIMATION_MOVE_TYPE::FADE_IN, ANIMATION_TYPE::FADE, -1, false, std::string(), 1.0f, DX_BLENDMODE_ALPHA, -11);
		break;
	}

	return animationData;
}

FSMAnimation* UtilFactorys::FSMAnimationFactory(Animation* animation, ANIMATION_FACTORY_NUMBER animationFactoryNumber, const std::vector<LoadAnimationData>& loadAnimationData)
{
	if (animation == nullptr || animation->GetModel() == nullptr || loadAnimationData.empty())
	{
		Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::ANIMATION_MISSING_FLAG);
		return nullptr;
	}

	FSMAnimation* fsm = new FSMAnimation();
	const AnimationCriteria criteria;
	const int modelHandle = animation->GetModel()->GetHandle();
	std::set<int> registeredStates;

	for (const LoadAnimationData& source : loadAnimationData)
	{
		if (!IsAnimationMoveAllowed(animationFactoryNumber, source.animationType))
		{
			continue;
		}

		const int stateNumber = static_cast<int>(source.animationType);
		if (registeredStates.find(stateNumber) != registeredStates.end())
		{
			continue;
		}

		const OneAnimationData stateData = CreateOneAnimationData(source);
		if ((source.modelType == ANIMATION_TYPE::MV1_MODEL ||
			source.modelType == ANIMATION_TYPE::MV1_MODEL_ONLY ||
			source.modelType == ANIMATION_TYPE::MV1_MODEL_MOVE) &&
			(modelHandle < 0 || stateData.number < 0))
		{
			Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::ANIMATION_MISSING_FLAG);
			continue;
		}
		if (source.modelType == ANIMATION_TYPE::EFFECT && stateData.number < 0)
		{
			Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::ANIMATION_MISSING_FLAG);
			continue;
		}

		IStateAnimation* state = nullptr;
		switch (source.modelType)
		{
		case ANIMATION_TYPE::NONE:
			state = new StateNoneAnimation(criteria);
			break;
		case ANIMATION_TYPE::MV1_MODEL:
		{
			StateMVOneAnimation* modelState = new StateMVOneAnimation(criteria, modelHandle, "root");
			modelState->SetMyAniamtionData(stateData);
			state = modelState;
			break;
		}
		case ANIMATION_TYPE::MV1_MODEL_ONLY:
			state = new MV1ExternalAnimationState(criteria, modelHandle, stateData);
			break;
		case ANIMATION_TYPE::MV1_MODEL_MOVE:
			state = new MV1OperationAnimationState(criteria, modelHandle, stateData);
			break;
		case ANIMATION_TYPE::EFFECT:
			state = new AnimationDataState<StateEffectAnimation>(criteria, stateData);
			break;
		case ANIMATION_TYPE::GRAPH:
		case ANIMATION_TYPE::POLYGON_INDEXED:
			state = new AnimationDataState<StateGraphAnimation>(criteria, stateData);
			break;
		case ANIMATION_TYPE::MOVIE:
			state = new AnimationDataState<StateMovieAnimation>(criteria, stateData);
			break;
		case ANIMATION_TYPE::FADE:
			state = new AnimationDataState<StateFadeGraphAnimation>(criteria, stateData);
			break;
		case ANIMATION_TYPE::DOT_WEEN:
			state = new AnimationDataState<StateDOTweenAnimation>(criteria, stateData);
			break;
		}

		if (state != nullptr)
		{
			registeredStates.insert(stateNumber);
			fsm->RegisterState(stateNumber, state);
		}
	}

	if (registeredStates.empty())
	{
		Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::ANIMATION_MISSING_FLAG);
	}

	return fsm;
}

CharacterAttackData UtilFactorys::CharacterAttackDataFactory(CHARACTER_ATTACK_DATA_FACTORY__ATTACK_METHOD attackMethod, CHARACTER_ATTACK_DATA_FACTORY__ANIMATION_TYPE modelType)
{
	CharacterAttackData result{};
	result.attackDataNumber = -1;
	result.modelBase = nullptr;

	LOAD_ANIMATION_DATA_FACTORY_NUMBER loadNumber = LOAD_ANIMATION_DATA_FACTORY_NUMBER::SHOT_ATTACK;
	VECTOR position = UtilCalc::VZero;
	VECTOR size = VScale(UtilCalc::VOne, 100.0f);

	switch (attackMethod)
	{
	case CHARACTER_ATTACK_DATA_FACTORY__ATTACK_METHOD::SHOT_NORMAL:
		position = VGet(0.0f, 1.0f, 3.0f);
		break;
	case CHARACTER_ATTACK_DATA_FACTORY__ATTACK_METHOD::SHOT_SPCEIAL:
		if (modelType != CHARACTER_ATTACK_DATA_FACTORY__ANIMATION_TYPE::ROBOT)
		{
			Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::ANIMATION_MISSING_FLAG);
			return result;
		}
		loadNumber = LOAD_ANIMATION_DATA_FACTORY_NUMBER::ROBOT_SPCEIAL;
		size = VScale(UtilCalc::VOne, 20.0f);
		break;
	case CHARACTER_ATTACK_DATA_FACTORY__ATTACK_METHOD::JUMP_ATTACK:
		if (modelType != CHARACTER_ATTACK_DATA_FACTORY__ANIMATION_TYPE::ROBOT)
		{
			Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::ANIMATION_MISSING_FLAG);
			return result;
		}
		loadNumber = LOAD_ANIMATION_DATA_FACTORY_NUMBER::JUMP_ROBOT_ATTACK;
		break;
	default:
		Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::ANIMATION_MISSING_FLAG);
		return result;
	}

	result.modelBase = ModelFactory(ANIMATION_TYPE::EFFECT, std::string(), position, UtilCalc::VZero, size);
	if (result.modelBase == nullptr || result.modelBase->GetAnimation() == nullptr)
	{
		Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::ANIMATION_MISSING_FLAG);
		return result;
	}

	const std::vector<LoadAnimationData> loadAnimationData = LoadAnimationDataFactory(loadNumber);
	result.modelBase->GetAnimation()->SetFsm(FSMAnimationFactory(result.modelBase->GetAnimation(), ANIMATION_FACTORY_NUMBER::SHOT_ATTACK, loadAnimationData));
	return result;
}

// カメラ有限状態マシン作成
FSMCamera* UtilFactorys::FSMCameraFactory()
{
	FSMCamera* fsnCamera = new FSMCamera();

	fsnCamera->RegisterState(new StateFixedCamera());
	fsnCamera->RegisterState(new StateMoveCamera());
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

		fsmCharacter->SetCurrentState(STATE_TYPE_CHARACTER::IDLE_PLAYER_STATE, character);

		Master::mpGameManager->GetTargetManager()->SetTarget(character, TARGET_TYPE::PLAYER);
		break;

	case CHARACTER_FACTORY_NUMBER::DUNGEON_PLAYER:
		fsmCharacter->RegisterState(new IdlePlayerState());
		fsmCharacter->RegisterState(new MovePlayerState());

		fsmCharacter->SetCurrentState(STATE_TYPE_CHARACTER::IDLE_PLAYER_STATE, character);

		Master::mpGameManager->GetTargetManager()->SetTarget(character, TARGET_TYPE::PLAYER);
		break;

	case CHARACTER_FACTORY_NUMBER::BATTLE_PLAYER:
		fsmCharacter->RegisterState(new IdleBattlePlayerState());
		fsmCharacter->RegisterState(new MoveBattlePlayerState());
		fsmCharacter->RegisterState(new NormalAttackPlayerState());
		fsmCharacter->RegisterState(new SpceialAttackPlayerState());
		fsmCharacter->RegisterState(new JumpAttackPlayerState());

		fsmCharacter->SetCurrentState(STATE_TYPE_CHARACTER::IDLE_PLAYER_STATE, character);

		Master::mpGameManager->GetTargetManager()->SetTarget(character, TARGET_TYPE::PLAYER);
		break;

	case CHARACTER_FACTORY_NUMBER::MAP_ENEMY:
		fsmCharacter->RegisterState(new IdleMapEnemyState(mapScene));
		fsmCharacter->RegisterState(new TelopMapEnemyState(mapScene));

		fsmCharacter->SetCurrentState(STATE_TYPE_CHARACTER::IDLE_MAP_ENEMY_STATE, character);

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

		fsmCharacter->SetCurrentState(STATE_TYPE_CHARACTER::IDLE_ENEMY_STATE, character);

		Master::mpGameManager->GetTargetManager()->SetTarget(character, TARGET_TYPE::ENEMY);
		break;

	case CHARACTER_FACTORY_NUMBER::BOSS_ENEMY:
		fsmCharacter->RegisterState(new IdleEnemyState());
		fsmCharacter->RegisterState(new MoveEnemyState());
		fsmCharacter->RegisterState(new AttackInEnemyState());
		fsmCharacter->RegisterState(new AttackEnemyState());
		fsmCharacter->RegisterState(new EscapeEnemyState());
		fsmCharacter->RegisterState(new LeftAvoidEnemyState());
		fsmCharacter->RegisterState(new RightAvoidEnemyState());

		fsmCharacter->SetCurrentState(STATE_TYPE_CHARACTER::IDLE_ENEMY_STATE, character);

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

	// TODO: 仮実装
	fsmScene->RegisterState(new GameLoopScene());
	fsmScene->RegisterState(new BattleLoopScene());

	fsmScene->RegisterState(new GameClearScene());

	fsmScene->SetCurrentState(SCENE::START, sceneManager);

	return fsmScene;
}

// UI有限状態マシン作成
FSMUI* UtilFactorys::FSMUIFactory(UIBase* ui, UI_FACTORY_NUMBER number)
{
	FSMUI* fsmUI = new FSMUI();

/* タイトルUI */
	switch (number)
	{
		/*----------------*/
		/*【タイトルUI】*/
		/*----------------*/
	case UI_FACTORY_NUMBER::TITLE:
	{
		fsmUI->RegisterState(new StartTitleUIState({
			STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>(STATE_TYPE_UI::SELECT_TITLE_UI_STATE, UtilStateConditionFunction::KeyDownStateCondition_KeyBoardSpecial<KEY_BOARD_SPECIAL::ENTER, UIBase>),
		}));
		// 選択ステート
		fsmUI->RegisterState(new SelectTitleUIState({
			STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>(STATE_TYPE_UI::NEW_DATA_CHECK_TITLE_UI_STATE, UtilStateConditionFunction::AndFunc<UIBase, 
				UtilStateConditionFunction::KeyDownStateCondition_KeyBoardSpecial<KEY_BOARD_SPECIAL::ENTER, UIBase>,
				UtilStateConditionFunction::IsSelectedNumber<0>
				>),
			STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>(STATE_TYPE_UI::DATA_SELECT_TITLE_UI_STATE, UtilStateConditionFunction::AndFunc<UIBase,
				UtilStateConditionFunction::KeyDownStateCondition_KeyBoardSpecial<KEY_BOARD_SPECIAL::ENTER, UIBase>,
				UtilStateConditionFunction::IsSelectedNumber<1>
				>),
			STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>(STATE_TYPE_UI::TUTORIAL_TITLE_UI_STATE, UtilStateConditionFunction::AndFunc<UIBase,
				UtilStateConditionFunction::KeyDownStateCondition_KeyBoardSpecial<KEY_BOARD_SPECIAL::ENTER, UIBase>,
				UtilStateConditionFunction::IsSelectedNumber<2>
				>),
			STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>(STATE_TYPE_UI::SETTING_TITLE_UI_STATE, UtilStateConditionFunction::AndFunc<UIBase,
				UtilStateConditionFunction::KeyDownStateCondition_KeyBoardSpecial<KEY_BOARD_SPECIAL::ENTER, UIBase>,
				UtilStateConditionFunction::IsSelectedNumber<3>
				>),
			STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>(STATE_TYPE_UI::START_TITLE_UI_STATE, UtilStateConditionFunction::KeyDownStateCondition_KeyBoardSpecial<KEY_BOARD_SPECIAL::BACK_SPACE, UIBase>),
		}));
		
		// セレクトに戻る条件
		STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase> backspaceKey_GoSelectCriteria = STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>(STATE_TYPE_UI::SELECT_TITLE_UI_STATE, UtilStateConditionFunction::KeyDownStateCondition_KeyBoardSpecial<KEY_BOARD_SPECIAL::BACK_SPACE, UIBase>);
		
		// 選択したステート
		fsmUI->RegisterState(new NewDataCheckTitleUIState({
    		STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>(STATE_TYPE_UI::CHARACTER_SELECT_TITLE_UI_STATE, UtilStateConditionFunction::KeyDownStateCondition_KeyBoardSpecial<KEY_BOARD_SPECIAL::ENTER, UIBase>),
			backspaceKey_GoSelectCriteria,
		}));
		fsmUI->RegisterState(new DataSelectTitleUIState({
			backspaceKey_GoSelectCriteria,
		}));
		fsmUI->RegisterState(new TutorialTitleUIState({
			backspaceKey_GoSelectCriteria,
		}));
		fsmUI->RegisterState(new SettingTitleUIState({
			STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>(STATE_TYPE_UI::SCREEN_SIZE_TITLE_UI_STATE,UtilStateConditionFunction::AndFunc<UIBase,
				UtilStateConditionFunction::KeyDownStateCondition_KeyBoardSpecial<KEY_BOARD_SPECIAL::ENTER, UIBase>,
				UtilStateConditionFunction::IsSelectedNumber<0>
				>),
			STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>(STATE_TYPE_UI::VOLUME_TITLE_UI_STATE, UtilStateConditionFunction::AndFunc<UIBase,
				UtilStateConditionFunction::KeyDownStateCondition_KeyBoardSpecial<KEY_BOARD_SPECIAL::ENTER, UIBase>,
				UtilStateConditionFunction::IsSelectedNumber<1>
				>),
			backspaceKey_GoSelectCriteria,
		}));

		// 一つ前のステートに戻る条件
		STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase> backspaceKey_GoBackStateCriteria = STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>(STATE_TYPE_UI::NEW_DATA_CHECK_TITLE_UI_STATE, UtilStateConditionFunction::KeyDownStateCondition_KeyBoardSpecial<KEY_BOARD_SPECIAL::BACK_SPACE, UIBase>);
		
		// データ作成関係
		fsmUI->RegisterState(new CharacterSelectTitleUIState({
				STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>(STATE_TYPE_UI::PLAYER_NAME_TITLE_UI_STATE, UtilStateConditionFunction::KeyDownStateCondition_KeyBoardSpecial<KEY_BOARD_SPECIAL::ENTER, UIBase>),
				backspaceKey_GoBackStateCriteria,
		}));
		backspaceKey_GoBackStateCriteria.ChangeNumber = STATE_TYPE_UI::CHARACTER_SELECT_TITLE_UI_STATE;
		fsmUI->RegisterState(new PlayerNameTitleUIState({
			STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>(STATE_TYPE_UI::INPUT_CHECK_TITLE_UI_STATE, UtilStateConditionFunction::KeyDownStateCondition_KeyBoardSpecial<KEY_BOARD_SPECIAL::ENTER, UIBase>),
			backspaceKey_GoBackStateCriteria,
		}));
		backspaceKey_GoBackStateCriteria.ChangeNumber = STATE_TYPE_UI::PLAYER_NAME_TITLE_UI_STATE;
		fsmUI->RegisterState(new InputCheckTitleUIState({
			backspaceKey_GoBackStateCriteria,
		}));

		// 設定関係
		backspaceKey_GoBackStateCriteria.ChangeNumber = STATE_TYPE_UI::SETTING_TITLE_UI_STATE;
		fsmUI->RegisterState(new ScreenSizeTitleUIState({
			STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>(STATE_TYPE_UI::SETTING_TITLE_UI_STATE, UtilStateConditionFunction::KeyDownStateCondition_KeyBoardSpecial<KEY_BOARD_SPECIAL::ENTER, UIBase>),
			backspaceKey_GoBackStateCriteria,
		}));
		backspaceKey_GoBackStateCriteria.ChangeNumber = STATE_TYPE_UI::SETTING_TITLE_UI_STATE;
		fsmUI->RegisterState(new VolumeTitleUIState({
			STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>(STATE_TYPE_UI::SETTING_TITLE_UI_STATE, UtilStateConditionFunction::KeyDownStateCondition_KeyBoardSpecial<KEY_BOARD_SPECIAL::ENTER, UIBase>),
			backspaceKey_GoBackStateCriteria,
		}));

		fsmUI->SetCurrentState(STATE_TYPE_UI::START_TITLE_UI_STATE, ui);
/* ゲーム中UI */
	}
		break;

		/*--------------*/
		/*【ゲームUI】*/
		/*--------------*/
	case UI_FACTORY_NUMBER::TOWN:
	case UI_FACTORY_NUMBER::DUNGEON:
	case UI_FACTORY_NUMBER::BATTLE:

		fsmUI->RegisterState(new NormalGameUIState({
			STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>(STATE_TYPE_UI::PAUSE_GAME_UI_STATE, UtilStateConditionFunction::IsMenuKeyPressed),
		}));

		fsmUI->RegisterState(new PauseGameUIState({
			STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>(STATE_TYPE_UI::NORMAL_GAME_UI_STATE, UtilStateConditionFunction::IsMenuKeyPressed),
			STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>(STATE_TYPE_UI::NORMAL_GAME_UI_STATE, UtilStateConditionFunction::AndFunc<UIBase, 
				UtilStateConditionFunction::KeyDownStateCondition_KeyBoardSpecial<KEY_BOARD_SPECIAL::ENTER, UIBase>,
				UtilStateConditionFunction::IsSelectedNumber<GAME_UI_SELECT_NUKMBER::UI_CLOSE>
				>),
			STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>(STATE_TYPE_UI::DRAW_PLAYER_DATA_UI_STATE, UtilStateConditionFunction::AndFunc<UIBase,
				UtilStateConditionFunction::KeyDownStateCondition_KeyBoardSpecial<KEY_BOARD_SPECIAL::ENTER, UIBase>,
				UtilStateConditionFunction::IsSelectedNumber<GAME_UI_SELECT_NUKMBER::UI_DRAW_PLAYER_DATA>
				>),
			STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>(STATE_TYPE_UI::SELECT_CONFIG_STATE, UtilStateConditionFunction::AndFunc<UIBase,
				UtilStateConditionFunction::KeyDownStateCondition_KeyBoardSpecial<KEY_BOARD_SPECIAL::ENTER, UIBase>,
				UtilStateConditionFunction::IsSelectedNumber<GAME_UI_SELECT_NUKMBER::UI_CONFIG_CHANGE>
				>),
			STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>(STATE_TYPE_UI::GAME_END_UI_STATE, UtilStateConditionFunction::AndFunc<UIBase,
				UtilStateConditionFunction::KeyDownStateCondition_KeyBoardSpecial<KEY_BOARD_SPECIAL::ENTER, UIBase>,
				UtilStateConditionFunction::IsSelectedNumber<GAME_UI_SELECT_NUKMBER::UI_GAME_END>
				>),
		}));

		// ポーズへ戻る条件
		STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase> backspaceKey_GoPauseCriteria(STATE_TYPE_UI::PAUSE_GAME_UI_STATE,
			UtilStateConditionFunction::KeyDownStateCondition_KeyBoardSpecial<KEY_BOARD_SPECIAL::BACK_SPACE, UIBase>
		);

		fsmUI->RegisterState(new DrawPlayerDataState({backspaceKey_GoPauseCriteria,}));
		//fsmUI->RegisterState(new ConfigChangeState({pauseBackCriteria,}));
		fsmUI->RegisterState(new GameEndState({
			// GameEndStateは遷移条件なし
		}));

		// コンフィグ
		fsmUI->RegisterState(new ConfigSelectState({
			STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>(STATE_TYPE_UI::MINIMAP_CONFIG_STATE, UtilStateConditionFunction::AndFunc<UIBase,
				UtilStateConditionFunction::KeyDownStateCondition_KeyBoardSpecial<KEY_BOARD_SPECIAL::ENTER, UIBase>,
				UtilStateConditionFunction::IsSelectedNumber<0>
				>),
			STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>(STATE_TYPE_UI::SOUND_CONFIG_STATE, UtilStateConditionFunction::AndFunc<UIBase,
					UtilStateConditionFunction::KeyDownStateCondition_KeyBoardSpecial<KEY_BOARD_SPECIAL::ENTER, UIBase>,
					UtilStateConditionFunction::IsSelectedNumber<1>
				>),
			STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>(STATE_TYPE_UI::CAMERA_CONFIG_STATE, UtilStateConditionFunction::AndFunc<UIBase,
				UtilStateConditionFunction::KeyDownStateCondition_KeyBoardSpecial<KEY_BOARD_SPECIAL::ENTER, UIBase>,
				UtilStateConditionFunction::IsSelectedNumber<2>
				>),
			backspaceKey_GoPauseCriteria,
		}));

		STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase> backspaceKey_GoConfigSelectCriteria(STATE_TYPE_UI::SELECT_CONFIG_STATE, UtilStateConditionFunction::KeyDownStateCondition_KeyBoardSpecial<KEY_BOARD_SPECIAL::BACK_SPACE, UIBase>);
		fsmUI->RegisterState(new MinimapConfigState({backspaceKey_GoConfigSelectCriteria,}));
		fsmUI->RegisterState(new SoundConfigState({backspaceKey_GoConfigSelectCriteria,}));
		fsmUI->RegisterState(new CameraConfigState({backspaceKey_GoConfigSelectCriteria,}));
		

/* リザルトUI */
		//fsmUI->SetCurrentState((int)GAME_UI_STATE::START_GAME_UI_STAE, ui);
		fsmUI->SetCurrentState(STATE_TYPE_UI::NORMAL_GAME_UI_STATE, ui);
		break;

		/*----------------*/
		/*【リザルトUI】*/
		/*----------------*/
	case UI_FACTORY_NUMBER::RESULT:
		fsmUI->RegisterState(new StartResultUIState({}));

		fsmUI->SetCurrentState(STATE_TYPE_UI::START_RESULT_UI_STATE, ui);
		break;
	}

	return fsmUI;
}

// INPROGRESS: 作業中
// モデル作成
ModelBase* UtilFactorys::ModelFactory(ANIMATION_TYPE type, std::string modelPath, VECTOR position, VECTOR angle, VECTOR size, std::vector<DRAW_GRAPH_DATA>* drawData)
{
	auto initializeModel = [position, angle, size](ModelBase* model)
	{
		model->MyAnimationSetting(new Animation());
		SetModelPosition(model, position, angle, size);
		return model;
	};

	switch (type)
	{
	case ANIMATION_TYPE::POLYGON_INDEXED:
	{
		return initializeModel(new ModelPolygonIndexed());
	}

	case ANIMATION_TYPE::MV1_MODEL:
	case ANIMATION_TYPE::MV1_MODEL_ONLY:
	{
		ModelMV1* model = new ModelMV1();
		model->SetModelHandle(modelPath.c_str());
		return initializeModel(model);
	}

	case ANIMATION_TYPE::EFFECT:
	{
		return initializeModel(new ModelEffect());
	}

	case ANIMATION_TYPE::GRAPH:
	{
		if (drawData == nullptr)
		{
			Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::ANIMATION_MISSING_FLAG);
			return nullptr;
		}
		ModelGraph* model = new ModelGraph();
		model->SetDrawDatas(*drawData);
		return initializeModel(model);
	}

	case ANIMATION_TYPE::MOVIE:
	{
		if (drawData == nullptr)
		{
			Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::ANIMATION_MISSING_FLAG);
			return nullptr;
		}
		ModelMovie* model = new ModelMovie();
		model->SetDrawDatas(*drawData);
		return initializeModel(model);
	}
	}

	Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::ANIMATION_MISSING_FLAG);
	return nullptr;
}
void UtilFactorys::SetModelPosition(ModelBase* model, VECTOR position, VECTOR angle, VECTOR size)
{
	model->SetPosition(position);
	model->SetAngle(angle);
	model->SetSize(size);
}

// 攻撃データ作成
std::map<ATTACK_METHOD_TYPE, AttackData> UtilFactorys::AttackDataFactory(CHARACTER_ATTACK_DATA_FACTORY__ANIMATION_TYPE modelTypeFactoryNumber, ATTACK_DATA_FACTORY__OBJECT_ATTACK_TYPE objectAttackTypeFactoryNumber)
{
	std::map<ATTACK_METHOD_TYPE, AttackData>  attackDatas;
	AttackData setData = AttackData();

	switch (modelTypeFactoryNumber)
	{
	case CHARACTER_ATTACK_DATA_FACTORY__ANIMATION_TYPE::ROBOT:
		attackDatas[ATTACK_METHOD_TYPE::NORMAL].attackCharacter = nullptr;
		attackDatas[ATTACK_METHOD_TYPE::SPCEIAL].attackCharacter = nullptr;
		attackDatas[ATTACK_METHOD_TYPE::JUMP].attackCharacter = nullptr;

		switch (objectAttackTypeFactoryNumber)
		{
		case ATTACK_DATA_FACTORY__OBJECT_ATTACK_TYPE::SHOT:
			attackDatas[ATTACK_METHOD_TYPE::NORMAL].attackMethdType = ATTACK_METHOD_TYPE::NORMAL;
			attackDatas[ATTACK_METHOD_TYPE::NORMAL].attackTime = 2720;
			attackDatas[ATTACK_METHOD_TYPE::NORMAL].attackType = ATTACK_TYPE::SHOT;

			attackDatas[ATTACK_METHOD_TYPE::SPCEIAL].attackMethdType = ATTACK_METHOD_TYPE::SPCEIAL;
			attackDatas[ATTACK_METHOD_TYPE::SPCEIAL].attackTime = 5696;
			attackDatas[ATTACK_METHOD_TYPE::SPCEIAL].attackType = ATTACK_TYPE::UNIQUE_ROBOT;
			

			attackDatas[ATTACK_METHOD_TYPE::JUMP].attackMethdType = ATTACK_METHOD_TYPE::JUMP;
			attackDatas[ATTACK_METHOD_TYPE::JUMP].attackTime = 5696;
			attackDatas[ATTACK_METHOD_TYPE::JUMP].attackType = ATTACK_TYPE::JUMP_ATTACK;
			break;
		}
		break;
	}

	return attackDatas;
}
/*
	// モデル設定
	character->GetModelsController()->AddModel(UtilFactorys::ModelFactory(ANIMATION_TYPE::MV1_MODEL, "../Resource/3D/Robot/robotSphere.mv1", UtilCalc::VZero, UtilCalc::VZero, VScale(UtilCalc::VOne, 20.0f)));
	//character->GetModelsController()->AddModel(UtilFactorys::ModelFactory(ANIMATION_TYPE::MV1_MODEL, "../Resource/3D/Human/Hero.x"));
	// アニメション設定
	 {
		Animation* characterAnimation = character->GetAnimation();
		std::vector<std::vector<LoadAnimationData>> setcharacterLoadAnimationData;
		// 読み込み用アニメーションデータ設定
		setcharacterLoadAnimationData.push_back(UtilFactorys::LoadAnimationDataFactory(characterAnimation, LOAD_ANIMATION_DATA_FACTORY_NUMBER::ROBOT));
		// アニメーション有限状態マシン設定
		characterAnimation->SetFsm(UtilFactorys::FSMAnimationFactory(characterAnimation, animationFactoryNumber, LOAD_ANIMATION_DATA_FACTORY_NUMBER::ROBOT, setcharacterLoadAnimationData));
	 }
*/