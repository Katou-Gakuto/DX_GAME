// #include "DxLib.h"

// #include "Master.h"

// #include "StateAnimationController.h"
// #include "StateBase.h"
// #include "TimeManager.h"

// #include "SoundManager.h"

// /*--------------------*/
// /*     【ベースアニメーションコントローラーステート】
// /*--------------------*/
// // TODO: ネクストステートをメンバでそれぞれ持つようにする
// /*----------*/
// /*【アニメションコントローラーステート共通処理用】
// /*----------*/
// StateAnimationControllerProcess::StateAnimationControllerProcess()
// : mstEndTime(0)
// {
// }

// // 終了時間設定
// void StateAnimationControllerProcess::SetEndTime(Animation* animation, ANIMATION_MOVE_TYPE state, int addEndTime)
// {
//     mstEndTime = Master::mpTimeManager->GetGameElapsedTime() + animation->GetAnimationTime(state) + addEndTime;
// }

// // 終了時間確認(一定時間経っていれば「true」を返す)
// bool StateAnimationControllerProcess::ChackEndTime()
// {
//     return mstEndTime < Master::mpTimeManager->GetGameElapsedTime();
// }
// // 変更確認
// ANIMATION_MOVE_TYPE StateAnimationControllerProcess::ChangeCheck(Animation* animation, ANIMATION_MOVE_TYPE nextState)
// {
//     if ((nextState == ANIMATION_MOVE_TYPE::ATTACK_IN) && !animation->SearchAnimationType(nextState))
//     {
//         return ANIMATION_MOVE_TYPE::ATTACK;
//     }

//     return nextState;
// }

// /*----------*/
// /*【待機アニメションコントローラーステート】
// /*----------*/
// StateIdleAnimationController::StateIdleAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_MOVE_TYPE, void>> stateChangeCriterias)
// : IStateAnimationController(ANIMATION_MOVE_TYPE::IDLE, stateChangeCriterias)
// , StateAnimationControllerProcess()
// {
//     mStateNumber = ANIMATION_MOVE_TYPE::IDLE;
// }

// // この状態に入った時の処理
// void StateIdleAnimationController::OnEnter(Animation* animation, ANIMATION_MOVE_TYPE oldState)
// {
// }

// // この状態を出る時の処理
// void StateIdleAnimationController::OnExit(Animation* animation, ANIMATION_MOVE_TYPE nextState)
// {
// }

// // ステート変更確認
// ANIMATION_MOVE_TYPE StateIdleAnimationController::CheckState(Animation* animation, ANIMATION_MOVE_TYPE nextState)
// {
//     return ChangeCheck(animation, nextState);
// }

// /*----------*/
// /*【移動アニメションコントローラーステート】
// /*----------*/
// StateMoveAnimationController::StateMoveAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_MOVE_TYPE, void>> stateChangeCriterias)
// : IStateAnimationController(ANIMATION_MOVE_TYPE::WALK, stateChangeCriterias)
// , StateAnimationControllerProcess()
// {
//     mStateNumber = ANIMATION_MOVE_TYPE::WALK;
// }

// // この状態に入った時の処理
// void StateMoveAnimationController::OnEnter(Animation* animation, ANIMATION_MOVE_TYPE oldState)
// {
// }

// // この状態を出る時の処理
// void StateMoveAnimationController::OnExit(Animation* animation, ANIMATION_MOVE_TYPE nextState)
// {
// }

// // ステート変更確認
// ANIMATION_MOVE_TYPE StateMoveAnimationController::CheckState(Animation* animation, ANIMATION_MOVE_TYPE nextState)
// {
//     return ChangeCheck(animation, nextState);
// }

// /*----------*/
// /*【攻撃開始アニメションコントローラーステート】
// /*----------*/
// StateAttackInAnimationController::StateAttackInAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_MOVE_TYPE, void>> stateChangeCriterias)
// : IStateAnimationController(ANIMATION_MOVE_TYPE::ATTACK_IN, stateChangeCriterias)
// , StateAnimationControllerProcess()
// {
//     mStateNumber = ANIMATION_MOVE_TYPE::ATTACK_IN;
// }

// // この状態に入った時の処理
// void StateAttackInAnimationController::OnEnter(Animation* animation, ANIMATION_MOVE_TYPE oldState)
// {
//     SetEndTime(animation, mStateNumber, mnAddEndTime);
// }

// // この状態を出る時の処理
// void StateAttackInAnimationController::OnExit(Animation* animation, ANIMATION_MOVE_TYPE nextState)
// {
// }

// // ステート変更確認
// ANIMATION_MOVE_TYPE StateAttackInAnimationController::CheckState(Animation* animation, ANIMATION_MOVE_TYPE nextState)
// {
//     if (ChackEndTime())
//     {
//         return ANIMATION_MOVE_TYPE::ATTACK;
//     }
    
//     return mStateNumber;
// }

// // 同分類の種類かを確認する
// bool StateAttackInAnimationController::CheckSameType(ANIMATION_MOVE_TYPE animationType)
// {
//     if ((animationType == ANIMATION_MOVE_TYPE::ATTACK) ||
//         (animationType == ANIMATION_MOVE_TYPE::ATTACK_IN) ||
//         (animationType == mStateNumber))
//     {
//         return true;
//     }

//     return false;
// }

// /*----------*/
// /*【攻撃アニメションコントローラーステート】
// /*----------*/
// StateAttackAnimationController::StateAttackAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_MOVE_TYPE, void>> stateChangeCriterias)
// : IStateAnimationController(ANIMATION_MOVE_TYPE::ATTACK, stateChangeCriterias)
// , StateAnimationControllerProcess()
// {
//     mStateNumber = ANIMATION_MOVE_TYPE::ATTACK;
// }

// // この状態に入った時の処理
// void StateAttackAnimationController::OnEnter(Animation* animation, ANIMATION_MOVE_TYPE oldState)
// {
//     SetEndTime(animation, mStateNumber, mnAddEndTime);
// }

// // この状態を出る時の処理
// void StateAttackAnimationController::OnExit(Animation* animation, ANIMATION_MOVE_TYPE nextState)
// {
// }

// // ステート変更確認
// ANIMATION_MOVE_TYPE StateAttackAnimationController::CheckState(Animation* animation, ANIMATION_MOVE_TYPE nextState)
// {
//     if (ChackEndTime())
//     {
//         return ANIMATION_MOVE_TYPE::ATTACK_OUT;
//     }
    
//     return mStateNumber;
// }

// // 同分類の種類かを確認する
// bool StateAttackAnimationController::CheckSameType(ANIMATION_MOVE_TYPE animationType)
// {
//     if ((animationType == ANIMATION_MOVE_TYPE::ATTACK) ||
//         (animationType == mStateNumber))
//     {
//         return true;
//     }

//     return false;
// }

// /*----------*/
// /*【攻撃終了アニメションコントローラーステート】
// /*----------*/
// StateAttackOutAnimationController::StateAttackOutAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_MOVE_TYPE, void>> stateChangeCriterias)
// : IStateAnimationController(ANIMATION_MOVE_TYPE::ATTACK_OUT, stateChangeCriterias)
// , StateAnimationControllerProcess()
// {
//     mStateNumber = ANIMATION_MOVE_TYPE::ATTACK_OUT;
// }

// // この状態に入った時の処理
// void StateAttackOutAnimationController::OnEnter(Animation* animation, ANIMATION_MOVE_TYPE oldState)
// {
//     SetEndTime(animation, mStateNumber, mnAddEndTime);
// }

// // この状態を出る時の処理
// void StateAttackOutAnimationController::OnExit(Animation* animation, ANIMATION_MOVE_TYPE nextState)
// {
// }

// // ステート変更確認
// ANIMATION_MOVE_TYPE StateAttackOutAnimationController::CheckState(Animation* animation, ANIMATION_MOVE_TYPE nextState)
// {
//     if (ChackEndTime())
//     {
//         return ChangeCheck(animation, nextState);
//     }
    
//     return mStateNumber;
// }

// // 同分類の種類かを確認する
// bool StateAttackOutAnimationController::CheckSameType(ANIMATION_MOVE_TYPE animationType)
// {
//     if ((animationType == ANIMATION_MOVE_TYPE::ATTACK) ||
//         (animationType == ANIMATION_MOVE_TYPE::ATTACK_OUT) ||
//         (animationType == mStateNumber))
//     {
//         return true;
//     }

//     return false;
// }

// /*----------*/
// /*【2D移動アニメーションコントローラーステート】
// /*----------*/
// State2DMoveAnimationController::State2DMoveAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_MOVE_TYPE, void>> stateChangeCriterias)
// : IStateAnimationController(ANIMATION_MOVE_TYPE::DISPLAY_MOVE, stateChangeCriterias)
// , StateAnimationControllerProcess()
// {
//     mStateNumber = ANIMATION_MOVE_TYPE::DISPLAY_MOVE;
// }

// // この状態に入った時の処理
// void State2DMoveAnimationController::OnEnter(Animation* animation, ANIMATION_MOVE_TYPE oldState)
// {
//     SetEndTime(animation, mStateNumber, mnAddEndTime);
// }

// // この状態を出る時の処理
// void State2DMoveAnimationController::OnExit(Animation* animation, ANIMATION_MOVE_TYPE nextState)
// {
// }

// // ステート変更確認
// ANIMATION_MOVE_TYPE State2DMoveAnimationController::CheckState(Animation* animation, ANIMATION_MOVE_TYPE nextState)
// {
//     if (ChackEndTime())
//     {
//         return nextState;
//     }
    
//     return mStateNumber;
// }

// /*----------------------------------------------------*/
// /*【フェードアウトアニメーションコントローラーステート】*/
// /*----------------------------------------------------*/
// StateFadeOutAnimationController::StateFadeOutAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_MOVE_TYPE, void>> stateChangeCriterias)
// : IStateAnimationController(ANIMATION_MOVE_TYPE::FADE_OUT, stateChangeCriterias)
// , StateAnimationControllerProcess()
// {
//     mStateNumber = ANIMATION_MOVE_TYPE::FADE_OUT;
// }

// // この状態に入った時の処理
// void StateFadeOutAnimationController::OnEnter(Animation* animation, ANIMATION_MOVE_TYPE oldState)
// {
//     SetEndTime(animation, mStateNumber, mnAddEndTime);
// }

// // この状態を出る時の処理
// void StateFadeOutAnimationController::OnExit(Animation* animation, ANIMATION_MOVE_TYPE nextState)
// {
// }

// // ステート変更確認
// ANIMATION_MOVE_TYPE StateFadeOutAnimationController::CheckState(Animation* animation, ANIMATION_MOVE_TYPE nextState)
// {
//     if (ChackEndTime() || (nextState == ANIMATION_MOVE_TYPE::FADE_IN))
//     {
//         return nextState;
//     }
    
//     return mStateNumber;
// }

// /*----------------------------------------------------*/
// /*【フェードインアニメーションコントローラーステート】*/
// /*----------------------------------------------------*/
// StateFadeInAnimationController::StateFadeInAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_MOVE_TYPE, void>> stateChangeCriterias)
// : IStateAnimationController(ANIMATION_MOVE_TYPE::FADE_IN, stateChangeCriterias)
// , StateAnimationControllerProcess()
// {
//     mStateNumber = ANIMATION_MOVE_TYPE::FADE_IN;
// }

// // この状態に入った時の処理
// void StateFadeInAnimationController::OnEnter(Animation* animation, ANIMATION_MOVE_TYPE oldState)
// {
//     SetEndTime(animation, mStateNumber, mnAddEndTime);
// }

// // この状態を出る時の処理
// void StateFadeInAnimationController::OnExit(Animation* animation, ANIMATION_MOVE_TYPE nextState)
// {
// }

// // ステート変更確認
// ANIMATION_MOVE_TYPE StateFadeInAnimationController::CheckState(Animation* animation, ANIMATION_MOVE_TYPE nextState)
// {
//     if (ChackEndTime() || (nextState == ANIMATION_MOVE_TYPE::FADE_OUT))
//     {
//         return nextState;
//     }
    
//     return mStateNumber;
// }

// /*--------------------*/
// /*     【派生アニメーションコントローラーステート】
// /*--------------------*/

// /*----------*/
// /*【攻撃中終了アニメーションステート】
// /*----------*/
// StateAttackEndAnimationController::StateAttackEndAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_MOVE_TYPE, void>> stateChangeCriterias)
// : StateAttackAnimationController(stateChangeCriterias)
// {
// }

// // ステート変更確認
// ANIMATION_MOVE_TYPE StateAttackEndAnimationController::CheckState(Animation* animation, ANIMATION_MOVE_TYPE nextState)
// {
//     if (ChackEndTime())
//     {
//         return ChangeCheck(animation, nextState);
//     }
    
//     return mStateNumber;
// }

// /*----------*/
// /*【攻撃停止アニメーションステート】
// /*----------*/
// StateAttackOutStopAnimationController::StateAttackOutStopAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_MOVE_TYPE, void>> stateChangeCriterias)
// : StateAttackOutAnimationController(stateChangeCriterias)
// {
// }

// // ステート変更確認
// ANIMATION_MOVE_TYPE StateAttackOutStopAnimationController::CheckState(Animation* animation, ANIMATION_MOVE_TYPE nextState)
// {
//     return mStateNumber;
// }

// /*----------------------------------------------------------------通常攻撃------------------------------------------------------------------*/
// /*----------*/
// /*【通常攻撃開始アニメションコントローラーステート】
// /*----------*/
// StateNormalAttackInAnimationController::StateNormalAttackInAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_MOVE_TYPE, void>> stateChangeCriterias)
// : StateAttackInAnimationController(stateChangeCriterias)
// {
//     mStateNumber = ANIMATION_MOVE_TYPE::NORMAL_ATTACK_IN;
// }

// // ステート変更確認
// ANIMATION_MOVE_TYPE StateNormalAttackInAnimationController::CheckState(Animation* animation, ANIMATION_MOVE_TYPE nextState)
// {
//     if (ChackEndTime())
//     {
//         Master::mpSoundManager->Set3DSound(SOUND_3D::BEAM_CANNON_SHOT, animation->GetModelsController()->GetModelPosition());
//         return ANIMATION_MOVE_TYPE::NORMAL_ATTACK_OUT;
//     }
    
//     return mStateNumber;
// }

// /*----------*/
// /*【通常攻撃終了アニメションコントローラーステート】
// /*----------*/
// StateNormalAttackOutAnimationController::StateNormalAttackOutAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_MOVE_TYPE, void>> stateChangeCriterias)
// : StateAttackOutAnimationController(stateChangeCriterias)
// {
//     mStateNumber = ANIMATION_MOVE_TYPE::NORMAL_ATTACK_OUT;
// }

// // ステート変更確認
// ANIMATION_MOVE_TYPE StateNormalAttackOutAnimationController::CheckState(Animation* animation, ANIMATION_MOVE_TYPE nextState)
// {
//     if (ChackEndTime())
//     {
//         return nextState;
//     }
    
//     return mStateNumber;
// }
// /*------------------------------------------------------------------------------------------------------------------------------------------*/



// /*----------------------------------------------------------------特殊攻撃------------------------------------------------------------------*/
// /*----------*/
// /*【特殊攻撃開始アニメションコントローラーステート】
// /*----------*/
// StateSpceialAttackInAnimationController::StateSpceialAttackInAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_MOVE_TYPE, void>> stateChangeCriterias)
// : StateAttackInAnimationController(stateChangeCriterias)
// {
//     mStateNumber = ANIMATION_MOVE_TYPE::SPCEIAL_ATTACK_IN;
// }

// // ステート変更確認
// ANIMATION_MOVE_TYPE StateSpceialAttackInAnimationController::CheckState(Animation* animation, ANIMATION_MOVE_TYPE nextState)
// {
//     if (ChackEndTime())
//     {
// 	Master::mpSoundManager->Set3DSound(SOUND_3D::ROBOT_EYES_GLOW, animation->GetModelsController()->GetModelPosition());
//         return ANIMATION_MOVE_TYPE::SPCEIAL_ATTACK;
//     }
    
//     return mStateNumber;
// }
// /*----------*/
// /*【特殊攻撃アニメションコントローラーステート】
// /*----------*/
// StateSpceialAttackAnimationController::StateSpceialAttackAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_MOVE_TYPE, void>> stateChangeCriterias)
// : StateAttackAnimationController(stateChangeCriterias)
// {
//     mStateNumber = ANIMATION_MOVE_TYPE::SPCEIAL_ATTACK;
// }

// // ステート変更確認
// ANIMATION_MOVE_TYPE StateSpceialAttackAnimationController::CheckState(Animation* animation, ANIMATION_MOVE_TYPE nextState)
// {
//     if (ChackEndTime())
//     {
//         return ANIMATION_MOVE_TYPE::SPCEIAL_ATTACK_OUT;
//     }
    
//     return mStateNumber;
// }

// /*----------*/
// /*【特殊攻撃終了アニメションコントローラーステート】
// /*----------*/
// StateSpceialAttackOutAnimationController::StateSpceialAttackOutAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_MOVE_TYPE, void>> stateChangeCriterias)
// : StateAttackOutAnimationController(stateChangeCriterias)
// {
//     mStateNumber = ANIMATION_MOVE_TYPE::SPCEIAL_ATTACK_OUT;
// }

// // ステート変更確認
// ANIMATION_MOVE_TYPE StateSpceialAttackOutAnimationController::CheckState(Animation* animation, ANIMATION_MOVE_TYPE nextState)
// {
//     if (ChackEndTime())
//     {
//         return nextState;
//     }
    
//     return mStateNumber;
// }
// /*------------------------------------------------------------------------------------------------------------------------------------------*/



// /*----------------------------------------------------------------ジャンプ攻撃------------------------------------------------------------------*/
// /*----------*/
// /*【ジャンプ攻撃開始アニメションコントローラーステート】
// /*----------*/
// StateJumpAttackInAnimationController::StateJumpAttackInAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_MOVE_TYPE, void>> stateChangeCriterias)
// : StateAttackInAnimationController(stateChangeCriterias)
// {
//     mStateNumber = ANIMATION_MOVE_TYPE::JUMP_ATTACK_IN;
// }

// // ステート変更確認
// ANIMATION_MOVE_TYPE StateJumpAttackInAnimationController::CheckState(Animation* animation, ANIMATION_MOVE_TYPE nextState)
// {
//     if (ChackEndTime())
//     {
//         return ANIMATION_MOVE_TYPE::JUMP_ATTACK;
//     }
    
//     return mStateNumber;
// }
// /*----------*/
// /*【ジャンプ攻撃アニメションコントローラーステート】
// /*----------*/
// StateJumpAttackAnimationController::StateJumpAttackAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_MOVE_TYPE, void>> stateChangeCriterias)
// : StateAttackAnimationController(stateChangeCriterias)
// {
//     mStateNumber = ANIMATION_MOVE_TYPE::JUMP_ATTACK;
// }

// // ステート変更確認
// ANIMATION_MOVE_TYPE StateJumpAttackAnimationController::CheckState(Animation* animation, ANIMATION_MOVE_TYPE nextState)
// {
//     if (ChackEndTime())
//     {
//         return ANIMATION_MOVE_TYPE::JUMP_ATTACK_OUT;
//     }
    
//     return mStateNumber;
// }

// /*----------*/
// /*【ジャンプ攻撃終了アニメションコントローラーステート】
// /*----------*/
// StateJumpAttackOutAnimationController::StateJumpAttackOutAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_MOVE_TYPE, void>> stateChangeCriterias)
// : StateAttackOutAnimationController(stateChangeCriterias)
// {
//     mStateNumber = ANIMATION_MOVE_TYPE::JUMP_ATTACK_OUT;
// }

// // ステート変更確認
// ANIMATION_MOVE_TYPE StateJumpAttackOutAnimationController::CheckState(Animation* animation, ANIMATION_MOVE_TYPE nextState)
// {
//     if (ChackEndTime())
//     {
//         return nextState;
//     }
    
//     return mStateNumber;
// }
// /*------------------------------------------------------------------------------------------------------------------------------------------*/

// /*----------*/
// /*【攻撃専用待機アニメーションステート】
// /*----------*/
// StateAttackIdleAnimationController::StateAttackIdleAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_MOVE_TYPE, void>> stateChangeCriterias)
// : StateIdleAnimationController(stateChangeCriterias)
// {
// }

// // ステート変更確認
// ANIMATION_MOVE_TYPE StateAttackIdleAnimationController::CheckState(Animation* animation, ANIMATION_MOVE_TYPE nextState)
// {
//     if (ChackEndTime())
//     {
//         return ANIMATION_MOVE_TYPE::ATTACK_IN;
//     }
    
//     return mStateNumber;
// }