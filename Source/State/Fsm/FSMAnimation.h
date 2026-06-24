#pragma once
#include <cassert>

#include "AnimationData.h"
#include "StateData.h"

#include "FSM.h"
#include "StateAnimation.h"

// TODO: 1つのモデルに対して複数のアニメーションを後から適用できるようにする
/*----------*/
/*【アニメーション有限状態マシン】
/*----------*/
class FSMAnimation : public FSMBase<IStateAnimation, int, STATE_ANEMATION_DATA>
{
private:
	// // アニメーションステート達
	// std::vector<std::map<MODEL_TYPE, IStateAnimation*>> mmAnimationStates;
public:
	FSMAnimation();

    // 初期設定を限定するために呼び出せないようにする
    void RegisterState(IStateAnimation* state) override
	{
		assert(false && " : 呼び出すな");
		// HACK: これでエラーが出なければこの中で使用したらエラーを出させるようにする
	}

    /// <summary>初期化</summary>
    //void Initilize(AnimationBase* animation);
	/// <summary>終了</summary>
	void Finalize(AnimationBase* animation);

	// /*アニメーション状態達のサイズを増やす*/
	// void IncreaseAnimationStateSize(int size);

	// /// <summary>アニメーションステート情報設定</summary>
	// void SetAnimationStateDatas(int animationStateIndex, std::map<MODEL_TYPE, IStateAnimation*> animationStateMap);

	/// <summary>更新</summary>
	void Update(AnimationBase* animation, std::vector<AnimationDatas*> animationDatas);

	/// <summary>次のステート設定</summary>
	// TODO: 構造体でアニメーションを設定出来るように変更する
	//inline void SetNextState(ANIMATION_TYPE animationType) { mnNextState = animationType; }

	/// <summary>現在のステートと同じ種類かを確認する</summary>
	//bool CheckNowStateSameType(ANIMATION_TYPE animationType) { return mmStateMap[mCurrentState]->CheckSameType(animationType); }
	
// private:
// 	/*新しいステートを設定する*/
// 	void NewStateSetting(int animationIndex, AnimationBase* animation, MODEL_TYPE oldModelType);

// 	/*次のステートが現在のステートと違うならステート変更処理をする*/
// 	void ChangeState(int animationStateIndex, AnimationBase* animation, ANIMATION_TYPE oldAnimationType);

// 	/*現在のステート取得*/
// 	IStateAnimation* GetAnimationState(int index, AnimationBase* animation, ANIMATION_TYPE animationType);
};