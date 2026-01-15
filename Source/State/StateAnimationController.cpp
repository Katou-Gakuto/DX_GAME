#include "DxLib.h"

#include "Master.h"

#include "StateAnimationController.h"
#include "StateBase.h"
#include "TimeManager.h"

/*----------*/
/*【待機アニメションコントローラーステート】
/*----------*/
StateIdleAnimationController::StateIdleAnimationController()
: IStateAnimationController()
, StateAnimationControllerProcess()
{
    mStateNumber = ANIMATION_TYPE::IDLE;
}

// この状態に入った時の処理
void StateIdleAnimationController::OnEnter(AnimationBase* animation, ANIMATION_TYPE oldState)
{
}

// この状態を出る時の処理
void StateIdleAnimationController::OnExit(AnimationBase* animation, ANIMATION_TYPE newState)
{
}

// ステート変更確認
ANIMATION_TYPE StateIdleAnimationController::CheckState(AnimationBase* animation, ANIMATION_TYPE nextState)
{
    return nextState;
}

/*----------*/
/*【移動アニメションコントローラーステート】
/*----------*/
StateMoveAnimationController::StateMoveAnimationController()
: IStateAnimationController()
, StateAnimationControllerProcess()
{
    mStateNumber = ANIMATION_TYPE::WALK;
}

// この状態に入った時の処理
void StateMoveAnimationController::OnEnter(AnimationBase* animation, ANIMATION_TYPE oldState)
{
}

// この状態を出る時の処理
void StateMoveAnimationController::OnExit(AnimationBase* animation, ANIMATION_TYPE newState)
{
}

// ステート変更確認
ANIMATION_TYPE StateMoveAnimationController::CheckState(AnimationBase* animation, ANIMATION_TYPE nextState)
{
    return nextState;
}

/*----------*/
/*【攻撃アニメションコントローラーステート】
/*----------*/
StateAttackAnimationController::StateAttackAnimationController()
: IStateAnimationController()
, StateAnimationControllerProcess()
, mnEndTime(0)
{
    mStateNumber = ANIMATION_TYPE::ATTACK;
}

// この状態に入った時の処理
void StateAttackAnimationController::OnEnter(AnimationBase* animation, ANIMATION_TYPE oldState)
{
    mnEndTime = animation->GetAnimationTime(mStateNumber) + Master::mpTimeManager->GetGameTime();
}

// この状態を出る時の処理
void StateAttackAnimationController::OnExit(AnimationBase* animation, ANIMATION_TYPE newState)
{
}

// ステート変更確認
ANIMATION_TYPE StateAttackAnimationController::CheckState(AnimationBase* animation, ANIMATION_TYPE nextState)
{
    if (mnEndTime > Master::mpTimeManager->GetGameTime())
    {
        return mStateNumber;
    }

    return nextState;
}