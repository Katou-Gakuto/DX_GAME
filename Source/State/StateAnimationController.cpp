#include "DxLib.h"

#include "StateAnimationController.h"
#include "StateBase.h"

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
void StateIdleAnimationController::OnEnter(AnimationBase* modelsController, ANIMATION_TYPE oldState)
{
}

// この状態を出る時の処理
void StateIdleAnimationController::OnExit(AnimationBase* modelsController, ANIMATION_TYPE newState)
{
}

// ステート変更確認
ANIMATION_TYPE StateIdleAnimationController::CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState)
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
void StateMoveAnimationController::OnEnter(AnimationBase* modelsController, ANIMATION_TYPE oldState)
{
}

// この状態を出る時の処理
void StateMoveAnimationController::OnExit(AnimationBase* modelsController, ANIMATION_TYPE newState)
{
}

// ステート変更確認
ANIMATION_TYPE StateMoveAnimationController::CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState)
{
    return nextState;
}

/*----------*/
/*【攻撃アニメションコントローラーステート】
/*----------*/
StateAttackAnimationController::StateAttackAnimationController()
: IStateAnimationController()
, StateAnimationControllerProcess()
{
    mStateNumber = ANIMATION_TYPE::ATTACK;
}

// この状態に入った時の処理
void StateAttackAnimationController::OnEnter(AnimationBase* modelsController, ANIMATION_TYPE oldState)
{
}

// この状態を出る時の処理
void StateAttackAnimationController::OnExit(AnimationBase* modelsController, ANIMATION_TYPE newState)
{
}

// ステート変更確認
ANIMATION_TYPE StateAttackAnimationController::CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState)
{
    if (true/*攻撃アニメーション中フラグ*/ &&
        ((ANIMATION_TYPE::WALK == nextState) || (ANIMATION_TYPE::IDLE == nextState)))
    {
        return mStateNumber;
    }

    return nextState;
}