#pragma once
#include <cassert>

#include "FSM.h"
#include "StateAnimationBase.h"
#include "StateData.h"

/*----------------------*/
/*【アニメーション有限状態マシン】*/
/*----------------------*/
class FSMAnimation
    : public FSMBase<
        IStateAnimation,
        int,
        STATE_ANEMATION_DATA>
{
private:
    STATE_ANEMATION_DATA mStateAnimationData;

public:
    FSMAnimation();

    /// <summary>初期化</summary>
    void Initilize(
        AnimationBase* animation,
        OneAnimationData* oneAnimationData,
        AnimationDatas* animationDatas);

    /// <summary>終了</summary>
    void Finalize();

    /// <summary>更新</summary>
    void Update();

    /// <summary>状態データ取得</summary>
    inline STATE_ANEMATION_DATA&
        GetStateAnimationData()
    {
        return mStateAnimationData;
    }

    /// <summary>
    /// 使用禁止
    /// </summary>
    void RegisterState(
        IStateAnimation* state) override
    {
        assert(false && " : 呼び出すな");
    }

	/// <summary>現在のステートと同じ種類かを確認する</summary>
	bool CheckNowStateSameType(ANIMATION_TYPE animationType) { return mmStateMap[mCurrentState]->CheckSimilarModelType(MODEL_TYPE::EFFECT); }
};