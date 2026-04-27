#include "DxLib.h"

#include "Master.h"

#include "StateAnimationController.h"
#include "StateBase.h"
#include "TimeManager.h"

#include "SoundManager.h"

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
void StateAnimationControllerProcess::SetEndTime(AnimationBase* animation, ANIMATION_TYPE state, int addEndTime)
{
    mnEndTime = animation->GetAnimationTime(state) + Master::mpTimeManager->GetGameTime() + addEndTime;
}

// 終了時間確認(一定時間経っていれば「true」を返す)
bool StateAnimationControllerProcess::ChackEndTime()
{
    return mnEndTime < Master::mpTimeManager->GetGameTime();
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
    SetEndTime(animation, mStateNumber, mnAddEndTime);
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

// 同分類の種類かを確認する
bool StateAttackInAnimationController::CheckSameType(ANIMATION_TYPE animationType)
{
    if ((animationType == ANIMATION_TYPE::ATTACK) ||
        (animationType == ANIMATION_TYPE::ATTACK_IN) ||
        (animationType == mStateNumber))
    {
        return true;
    }

    return false;
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
    SetEndTime(animation, mStateNumber, mnAddEndTime);
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
        return ANIMATION_TYPE::ATTACK_OUT;
    }
    
    return mStateNumber;
}

// 同分類の種類かを確認する
bool StateAttackAnimationController::CheckSameType(ANIMATION_TYPE animationType)
{
    if ((animationType == ANIMATION_TYPE::ATTACK) ||
        (animationType == mStateNumber))
    {
        return true;
    }

    return false;
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
    SetEndTime(animation, mStateNumber, mnAddEndTime);
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
        return ChangeCheck(animation, nextState);
    }
    
    return mStateNumber;
}

// 同分類の種類かを確認する
bool StateAttackOutAnimationController::CheckSameType(ANIMATION_TYPE animationType)
{
    if ((animationType == ANIMATION_TYPE::ATTACK) ||
        (animationType == ANIMATION_TYPE::ATTACK_OUT) ||
        (animationType == mStateNumber))
    {
        return true;
    }

    return false;
}

/*----------*/
/*【2D移動アニメーションコントローラーステート】
/*----------*/
State2DMoveAnimationController::State2DMoveAnimationController()
: IStateAnimationController()
, StateAnimationControllerProcess()
{
    mStateNumber = ANIMATION_TYPE::DISPLAY_MOVE;
}

// この状態に入った時の処理
void State2DMoveAnimationController::OnEnter(AnimationBase* animation, ANIMATION_TYPE oldState)
{
    SetEndTime(animation, mStateNumber, mnAddEndTime);
}

// この状態を出る時の処理
void State2DMoveAnimationController::OnExit(AnimationBase* animation, ANIMATION_TYPE newState)
{
}

// ステート変更確認
ANIMATION_TYPE State2DMoveAnimationController::CheckState(AnimationBase* animation, ANIMATION_TYPE nextState)
{
    if (ChackEndTime())
    {
        return nextState;
    }
    
    return mStateNumber;
}

/*----------------------------------------------------*/
/*【フェードアウトアニメーションコントローラーステート】*/
/*----------------------------------------------------*/
StateFadeOutAnimationController::StateFadeOutAnimationController()
: IStateAnimationController()
, StateAnimationControllerProcess()
{
    mStateNumber = ANIMATION_TYPE::FADE_OUT;
}

// この状態に入った時の処理
void StateFadeOutAnimationController::OnEnter(AnimationBase* animation, ANIMATION_TYPE oldState)
{
    SetEndTime(animation, mStateNumber, mnAddEndTime);
}

// この状態を出る時の処理
void StateFadeOutAnimationController::OnExit(AnimationBase* animation, ANIMATION_TYPE newState)
{
}

// ステート変更確認
ANIMATION_TYPE StateFadeOutAnimationController::CheckState(AnimationBase* animation, ANIMATION_TYPE nextState)
{
    if (ChackEndTime() || (nextState == ANIMATION_TYPE::FADE_IN))
    {
        return nextState;
    }
    
    return mStateNumber;
}

/*----------------------------------------------------*/
/*【フェードインアニメーションコントローラーステート】*/
/*----------------------------------------------------*/
StateFadeInAnimationController::StateFadeInAnimationController()
: IStateAnimationController()
, StateAnimationControllerProcess()
{
    mStateNumber = ANIMATION_TYPE::FADE_IN;
}

// この状態に入った時の処理
void StateFadeInAnimationController::OnEnter(AnimationBase* animation, ANIMATION_TYPE oldState)
{
    SetEndTime(animation, mStateNumber, mnAddEndTime);
}

// この状態を出る時の処理
void StateFadeInAnimationController::OnExit(AnimationBase* animation, ANIMATION_TYPE newState)
{
}

// ステート変更確認
ANIMATION_TYPE StateFadeInAnimationController::CheckState(AnimationBase* animation, ANIMATION_TYPE nextState)
{
    if (ChackEndTime() || (nextState == ANIMATION_TYPE::FADE_OUT))
    {
        return nextState;
    }
    
    return mStateNumber;
}

/*--------------------*/
/*     【派生アニメーションコントローラーステート】
/*--------------------*/

/*----------*/
/*【攻撃中終了アニメーションステート】
/*----------*/
StateAttackEndAnimationController::StateAttackEndAnimationController()
: StateAttackAnimationController()
{
}

// ステート変更確認
ANIMATION_TYPE StateAttackEndAnimationController::CheckState(AnimationBase* animation, ANIMATION_TYPE nextState)
{
    if (ChackEndTime())
    {
        return ChangeCheck(animation, nextState);
    }
    
    return mStateNumber;
}

/*----------*/
/*【攻撃停止アニメーションステート】
/*----------*/
StateAttackOutStopAnimationController::StateAttackOutStopAnimationController()
: StateAttackOutAnimationController()
{
}

// ステート変更確認
ANIMATION_TYPE StateAttackOutStopAnimationController::CheckState(AnimationBase* animation, ANIMATION_TYPE nextState)
{
    return mStateNumber;
}

/*----------------------------------------------------------------通常攻撃------------------------------------------------------------------*/
/*----------*/
/*【通常攻撃開始アニメションコントローラーステート】
/*----------*/
StateNormalAttackInAnimationController::StateNormalAttackInAnimationController()
: StateAttackInAnimationController()
{
    mStateNumber = ANIMATION_TYPE::NORMAL_ATTACK_IN;
}

// ステート変更確認
ANIMATION_TYPE StateNormalAttackInAnimationController::CheckState(AnimationBase* animation, ANIMATION_TYPE nextState)
{
    if (ChackEndTime())
    {
        Master::mpSoundManager->Set3DSound(SOUND_3D::BEAM_CANNON_SHOT, animation->GetModelsController()->GetModelPosition());
        return ANIMATION_TYPE::NORMAL_ATTACK_OUT;
    }
    
    return mStateNumber;
}

/*----------*/
/*【通常攻撃終了アニメションコントローラーステート】
/*----------*/
StateNormalAttackOutAnimationController::StateNormalAttackOutAnimationController()
: StateAttackOutAnimationController()
{
    mStateNumber = ANIMATION_TYPE::NORMAL_ATTACK_OUT;
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
/*------------------------------------------------------------------------------------------------------------------------------------------*/



/*----------------------------------------------------------------特殊攻撃------------------------------------------------------------------*/
/*----------*/
/*【特殊攻撃開始アニメションコントローラーステート】
/*----------*/
StateSpceialAttackInAnimationController::StateSpceialAttackInAnimationController()
: StateAttackInAnimationController()
{
    mStateNumber = ANIMATION_TYPE::SPCEIAL_ATTACK_IN;
}

// ステート変更確認
ANIMATION_TYPE StateSpceialAttackInAnimationController::CheckState(AnimationBase* animation, ANIMATION_TYPE nextState)
{
    if (ChackEndTime())
    {
	Master::mpSoundManager->Set3DSound(SOUND_3D::ROBOT_EYES_GLOW, animation->GetModelsController()->GetModelPosition());
        return ANIMATION_TYPE::SPCEIAL_ATTACK;
    }
    
    return mStateNumber;
}
/*----------*/
/*【特殊攻撃アニメションコントローラーステート】
/*----------*/
StateSpceialAttackAnimationController::StateSpceialAttackAnimationController()
: StateAttackAnimationController()
{
    mStateNumber = ANIMATION_TYPE::SPCEIAL_ATTACK;
}

// ステート変更確認
ANIMATION_TYPE StateSpceialAttackAnimationController::CheckState(AnimationBase* animation, ANIMATION_TYPE nextState)
{
    if (ChackEndTime())
    {
        return ANIMATION_TYPE::SPCEIAL_ATTACK_OUT;
    }
    
    return mStateNumber;
}

/*----------*/
/*【特殊攻撃終了アニメションコントローラーステート】
/*----------*/
StateSpceialAttackOutAnimationController::StateSpceialAttackOutAnimationController()
: StateAttackOutAnimationController()
{
    mStateNumber = ANIMATION_TYPE::SPCEIAL_ATTACK_OUT;
}

// ステート変更確認
ANIMATION_TYPE StateSpceialAttackOutAnimationController::CheckState(AnimationBase* animation, ANIMATION_TYPE nextState)
{
    if (ChackEndTime())
    {
        return nextState;
    }
    
    return mStateNumber;
}
/*------------------------------------------------------------------------------------------------------------------------------------------*/



/*----------------------------------------------------------------ジャンプ攻撃------------------------------------------------------------------*/
/*----------*/
/*【ジャンプ攻撃開始アニメションコントローラーステート】
/*----------*/
StateJumpAttackInAnimationController::StateJumpAttackInAnimationController()
: StateAttackInAnimationController()
{
    mStateNumber = ANIMATION_TYPE::JUMP_ATTACK_IN;
}

// ステート変更確認
ANIMATION_TYPE StateJumpAttackInAnimationController::CheckState(AnimationBase* animation, ANIMATION_TYPE nextState)
{
    if (ChackEndTime())
    {
        return ANIMATION_TYPE::JUMP_ATTACK;
    }
    
    return mStateNumber;
}
/*----------*/
/*【ジャンプ攻撃アニメションコントローラーステート】
/*----------*/
StateJumpAttackAnimationController::StateJumpAttackAnimationController()
: StateAttackAnimationController()
{
    mStateNumber = ANIMATION_TYPE::JUMP_ATTACK;
}

// ステート変更確認
ANIMATION_TYPE StateJumpAttackAnimationController::CheckState(AnimationBase* animation, ANIMATION_TYPE nextState)
{
    if (ChackEndTime())
    {
        return ANIMATION_TYPE::JUMP_ATTACK_OUT;
    }
    
    return mStateNumber;
}

/*----------*/
/*【ジャンプ攻撃終了アニメションコントローラーステート】
/*----------*/
StateJumpAttackOutAnimationController::StateJumpAttackOutAnimationController()
: StateAttackOutAnimationController()
{
    mStateNumber = ANIMATION_TYPE::JUMP_ATTACK_OUT;
}

// ステート変更確認
ANIMATION_TYPE StateJumpAttackOutAnimationController::CheckState(AnimationBase* animation, ANIMATION_TYPE nextState)
{
    if (ChackEndTime())
    {
        return nextState;
    }
    
    return mStateNumber;
}
/*------------------------------------------------------------------------------------------------------------------------------------------*/

/*----------*/
/*【攻撃専用待機アニメーションステート】
/*----------*/
StateAttackIdleAnimationController::StateAttackIdleAnimationController()
: StateIdleAnimationController()
{
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