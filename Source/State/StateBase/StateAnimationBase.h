#pragma once
#include <vector>

#include "StateData.h"
#include "AnimationData.h"

#include "StateBase.h"

enum class MODEL_TYPE;
enum class CAMERA_MODE;
enum class DOT_WEEN_TYPE;
enum class SCENE;

class AnimationBase;

/*----------*/
/*【アニメーションステートベース】
/*----------*/
class IStateAnimation : public StateBase<int, STATE_ANEMATION_DATA>
{
protected:
	// アニメーションステート設定情報ナンバー
	int mnAnimationStateSettingInfoNumber;
// 	// モデルベース
// 	ModelBase* mpModelBase;


public:
	IStateAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias, int stateNumber)
	: StateBase(stateChangeCriterias, stateNumber)
	{
	}
	virtual ~IStateAnimation() = default;

	/// <summary>次のステートを取得する</summary>
	int GetNextState(STATE_ANEMATION_DATA* stateAnimationData) override
	{
		for (auto& stateChangeCriteriaData : mfpStateChangeCriterias)
		{
#ifdef _DEBUG
			if (stateChangeCriteriaData.ChangeFlag == nullptr)
			{
				Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::STATE_NULL_FUNCTION_FLAG);
				DEBUG::SaveText("ステート未設定", DEBUG::DEBUG_MAP_TYPE::DEBUG_FAILURE_LOG);
				return mStateNumber;
			}
#endif
			if (stateChangeCriteriaData.ChangeFlag(stateAnimationData))
			{
				return stateChangeCriteriaData.ChangeNumber;
			}
		}

		return stateAnimationData->nextState;
	}

	// /// <summary>この状態に入った時の処理</summary>
	// virtual void OnEnter(AnimationBase* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, MODEL_TYPE oldModelType) = 0;
	// /// <summary>この状態を出る時の処理</summary>
	// virtual void OnExit(AnimationBase* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, MODEL_TYPE newModelType) = 0;
	
	/// <summary>初期化</summary>
	virtual void Initilize(STATE_ANEMATION_DATA* stateAnimationData){}
	/// <summary>終了</summary>
	virtual void Finalize(STATE_ANEMATION_DATA* stateAnimationData) = 0;

	/// <summary>更新</summary>
	virtual void Update(STATE_ANEMATION_DATA* stateAnimationData) = 0;

	/// <summary>アニメーションムーブ種類が同類なら「true」を返す</summary>
	/// <param name="animationMoveType">アニメーションムーブ種類</param>
	/// <returns>同類か</returns>
	virtual bool CheckSimilarAnimationMoveType(ANIMATION_ENUM::ANIMATION_MOVE_TYPE animationMoveType) = 0;

	// /// <summary>アニメーションステート設定情報ナンバー取得</summary>
	// int GetAnimationStateSettingInfoNumber() { return mnAnimationStateSettingInfoNumber; }
	// /// <summary>アニメーションステート設定情報ナンバー設定</summary>
	// void SetAnimationStateSettingInfoNumber(int infoNumber) { mnAnimationStateSettingInfoNumber = infoNumber; }

	// /// <summary>モデル設定</summary>
	// /// <param name="modelBase">モデル</param>
	// void SetModelBase(ModelBase* modelBase);
};