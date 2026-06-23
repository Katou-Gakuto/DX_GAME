#pragma once
#include <vector>

#include "StateEnum.h"
#include "StateData.h"

#ifdef _DEBUG
#include "Master.h"
#include "EndManager.h"
#include "DebugLogs/DebugLog.h"
#endif

/*------------------*/
/*【ステートベース】*/
/*------------------*/
template<typename number, typename stateData>
class StateBase
{
protected:
	// ステートナンバー
	number mStateNumber = (number) - 1;

	// ステート変更条件
	std::vector<STATE_CHANGE_CRITERIA_DATA<number, stateData>> mfpStateChangeCriterias;
public:
	StateBase(std::vector<STATE_CHANGE_CRITERIA_DATA<number, stateData>> stateChangeCriterias, number stateNumber)
	: mStateNumber(stateNumber)
	, mfpStateChangeCriterias(stateChangeCriterias)
	{
	}

	virtual ~StateBase() = default;

	/// <summary>初期化</summary>
	virtual void Initilize(stateData* onData) = 0;
	
	/// <summary>この状態に入った時の処理</summary>
	virtual void OnEnter(stateData* enterData, number preState) = 0;
	/// <summary>この状態を出る時の処理</summary>
	virtual void OnExit(stateData* exitData, number newState) = 0;	

	/// <summary>ステート取得</summary>
	inline number GetStateNumber() const { return mStateNumber; }

	/// <summary>次のステートを取得する</summary>
	virtual number GetNextState(stateData* changeConditionData)
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
			if (stateChangeCriteriaData.ChangeFlag(changeConditionData))
			{
				return stateChangeCriteriaData.ChangeNumber;
			}
		}
	}

	/// <summary>ステート設定</summary>
	/// <param name="stateNumber">設定ステートナンバー</param>
	inline void SetStatenumber(number stateNumber) { mStateNumber = stateNumber; }

	/// <summary>ステート変更条件設定</summary>
	/// <param name="stateNumber">設定ステート変更条件</param>
	inline void SetStateChangeCriterias(std::vector<STATE_CHANGE_CRITERIA_DATA<number, stateData>> stateChangeCriterias) { mfpStateChangeCriterias = stateChangeCriterias; }
};

// /*----------*/
// /*【アニメション操作ステートベース】
// /*----------*/
// class IStateAnimationController : public StateBase<ANIMATION_TYPE, STATE_ANEMATION_DATA>
// {
// protected:
// 	// 追加終了時間
// 	int mnAddEndTime;
	
// public:
// 	IStateAnimationController(ANIMATION_TYPE stateNumber, std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_TYPE, STATE_ANEMATION_DATA>> stateChangeCriterias)
// 	: StateBase(stateNumber, stateChangeCriterias)
// 	{
// 	}
// 	virtual ~IStateAnimationController() = default;

// 	/// <summary>初期化</summary>
// 	virtual void Initilize(AnimationBase* animation){}
	
// 	// /// <summary>この状態に入った時の処理</summary>
// 	// virtual void OnEnter(AnimationBase* animation, ANIMATION_TYPE preState) = 0;
// 	// /// <summary>この状態を出る時の処理</summary>
// 	// virtual void OnExit(AnimationBase* animation, ANIMATION_TYPE newState) = 0;

// 	// /// <summary>ステート変更確認</summary>
// 	// virtual ANIMATION_TYPE CheckState(AnimationBase* animation, ANIMATION_TYPE nextState) = 0;

// 	/// <summary>同分類の種類かを確認する</summary>
// 	virtual bool CheckSameType(ANIMATION_TYPE animationType)
// 	{
// 		return mStateNumber == animationType;
// 	}

// 	/// <summary>追加終了時間設定</summary>
// 	void SetAddEndTime(int addEndTime) 
// 	{ mnAddEndTime = addEndTime; }
// };