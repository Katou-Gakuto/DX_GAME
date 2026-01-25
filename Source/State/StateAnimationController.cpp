#include "DxLib.h"

#include "Master.h"

#include "StateAnimationController.h"
#include "StateBase.h"
#include "TimeManager.h"

/*--------------------*/
/*     【ベースアニメーションコントローラーステート】
/*--------------------*/
// TODO: ネクストステートをメンバでそれぞれ持つようにする
/*----------*/
/*【アニメションコントローラーステート共通処理用】
/*----------*/
StateAnimationControllerProcess::StateAnimationControllerProcess()
: mnEndTime(0)
{
}

// 終了時間設定
void StateAnimationControllerProcess::SetEndTime(AnimationBase* animation, ANIMATION_TYPE state)
{
    mnEndTime = animation->GetAnimationTime(state) + Master::mpTimeManager->GetGameTime();
}

// 終了時間確認(一定時間経っていれば「true」を返す)
bool StateAnimationControllerProcess::ChackEndTime()
{
    return mnEndTime <= Master::mpTimeManager->GetGameTime();
}
// 変更確認
ANIMATION_TYPE StateAnimationControllerProcess::ChangeCheck(AnimationBase* animation, ANIMATION_TYPE nextState)
{
    if ((nextState == ANIMATION_TYPE::ATTACK_IN) && !animation->SearchAnimationType(nextState))
    {
        return ANIMATION_TYPE::ATTACK;
    }

    return nextState;
}

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
    return ChangeCheck(animation, nextState);
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
    return ChangeCheck(animation, nextState);
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
void StateAttackAnimationController::OnEnter(AnimationBase* animation, ANIMATION_TYPE oldState)
{
    SetEndTime(animation, mStateNumber);
}

// この状態を出る時の処理
void StateAttackAnimationController::OnExit(AnimationBase* animation, ANIMATION_TYPE newState)
{
}

// ステート変更確認
ANIMATION_TYPE StateAttackAnimationController::CheckState(AnimationBase* animation, ANIMATION_TYPE nextState)
{
    if (ChackEndTime())
    {
        return ChangeCheck(animation, nextState);
    }
    
    return mStateNumber;
}

/*----------*/
/*【攻撃開始アニメションコントローラーステート】
/*----------*/
StateAttackInAnimationController::StateAttackInAnimationController()
: IStateAnimationController()
, StateAnimationControllerProcess()
{
    mStateNumber = ANIMATION_TYPE::ATTACK_IN;
}

// この状態に入った時の処理
void StateAttackInAnimationController::OnEnter(AnimationBase* animation, ANIMATION_TYPE oldState)
{
    SetEndTime(animation, mStateNumber);
}

// この状態を出る時の処理
void StateAttackInAnimationController::OnExit(AnimationBase* animation, ANIMATION_TYPE newState)
{
}

// ステート変更確認
ANIMATION_TYPE StateAttackInAnimationController::CheckState(AnimationBase* animation, ANIMATION_TYPE nextState)
{
    if (ChackEndTime())
    {
        return ANIMATION_TYPE::ATTACK;
    }
    
    return mStateNumber;
}

/*----------*/
/*【攻撃終了アニメションコントローラーステート】
/*----------*/
StateAttackOutAnimationController::StateAttackOutAnimationController()
: IStateAnimationController()
, StateAnimationControllerProcess()
{
    mStateNumber = ANIMATION_TYPE::ATTACK_OUT;
}

// この状態に入った時の処理
void StateAttackOutAnimationController::OnEnter(AnimationBase* animation, ANIMATION_TYPE oldState)
{
    SetEndTime(animation, mStateNumber);
}

// この状態を出る時の処理
void StateAttackOutAnimationController::OnExit(AnimationBase* animation, ANIMATION_TYPE newState)
{
}

// ステート変更確認
ANIMATION_TYPE StateAttackOutAnimationController::CheckState(AnimationBase* animation, ANIMATION_TYPE nextState)
{
    if (ChackEndTime())
    {
        return nextState;
    }
    
    return mStateNumber;
}

/*----------*/
/*【通常攻撃開始アニメションコントローラーステート】
/*----------*/
StateNormalAttackInAnimationController::StateNormalAttackInAnimationController()
: IStateAnimationController()
, StateAnimationControllerProcess()
{
    mStateNumber = ANIMATION_TYPE::NORMAL_ATTACK_IN;
}

// この状態に入った時の処理
void StateNormalAttackInAnimationController::OnEnter(AnimationBase* animation, ANIMATION_TYPE oldState)
{
    SetEndTime(animation, mStateNumber);
}

// この状態を出る時の処理
void StateNormalAttackInAnimationController::OnExit(AnimationBase* animation, ANIMATION_TYPE newState)
{
}

// ステート変更確認
ANIMATION_TYPE StateNormalAttackInAnimationController::CheckState(AnimationBase* animation, ANIMATION_TYPE nextState)
{
    if (ChackEndTime())
    {// HACK: すぐアニメーション出るようになってる 変える
        return ANIMATION_TYPE::NORMAL_ATTACK_OUT;
    }
    
    return mStateNumber;
}

/*----------*/
/*【通常攻撃終了アニメションコントローラーステート】
/*----------*/
StateNormalAttackOutAnimationController::StateNormalAttackOutAnimationController()
: IStateAnimationController()
, StateAnimationControllerProcess()
{
    mStateNumber = ANIMATION_TYPE::NORMAL_ATTACK_OUT;
}

// この状態に入った時の処理
void StateNormalAttackOutAnimationController::OnEnter(AnimationBase* animation, ANIMATION_TYPE oldState)
{
    SetEndTime(animation, mStateNumber);
}

// この状態を出る時の処理
void StateNormalAttackOutAnimationController::OnExit(AnimationBase* animation, ANIMATION_TYPE newState)
{
}

// ステート変更確認
ANIMATION_TYPE StateNormalAttackOutAnimationController::CheckState(AnimationBase* animation, ANIMATION_TYPE nextState)
{
    if (ChackEndTime())
    {
        return nextState;
    }
    
    return mStateNumber;
}


/*--------------------*/
/*     【派生アニメーションコントローラーステート】
/*--------------------*/
StateAttackMiddleAnimationController::StateAttackMiddleAnimationController()
: StateAttackAnimationController()
{
}

// ステート変更確認
ANIMATION_TYPE StateAttackMiddleAnimationController::CheckState(AnimationBase* animation, ANIMATION_TYPE nextState)
{
    if (ChackEndTime())
    {
        return ANIMATION_TYPE::ATTACK_OUT;
    }
    
    return mStateNumber;
}

// ステート変更確認
ANIMATION_TYPE StateAttackIdleAnimationController::CheckState(AnimationBase* animation, ANIMATION_TYPE nextState)
{
    if (ChackEndTime())
    {
        return ANIMATION_TYPE::ATTACK_IN;
    }
    
    return mStateNumber;
}