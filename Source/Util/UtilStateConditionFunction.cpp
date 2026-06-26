#include "ObjectBases.h"
#include "StatePlayer.h"
#include "StateEnemy.h"

#include "Master.h"

#include "DataManager.h"
#include "GameManager.h"
#include "KeyState.h"
#include "TargetManager.h"
#include "TimeManager.h"
#include "UtilCalc.h"
#include "UtilStateConditionFunction.h"

/*------------------------------*/
/*【ステート遷移条件関数】*/
/*------------------------------*/

/* プレイヤー状態遷移条件 */

/// <summary>移動キーが押されているか判定</summary>
bool UtilStateConditionFunction::ShouldTransitionToMove(CharacterBase* character)
{
    // 推測: PlayerProcess::GetPlayerMoveFlag()と同じ判定を行う
    // 根拠: StatePlayer.cppのStateCheckメソッドで使用されている
    // 仮定: キーステートはMaster::mpKeyStateから取得可能
    KeyState* keyState = Master::mpKeyState;
    return keyState->GetNowWordKeyFlags_Board() & (((unsigned long long)1 << (int)KEY_BOARD_WORD::W) |
                                                        ((unsigned long long)1 << (int)KEY_BOARD_WORD::A) |
                                                        ((unsigned long long)1 << (int)KEY_BOARD_WORD::S) |
                                                        ((unsigned long long)1 << (int)KEY_BOARD_WORD::D));
}

/// <summary>移動キーが押されていないか判定</summary>
bool UtilStateConditionFunction::ShouldTransitionToIdle(CharacterBase* character)
{
    return !ShouldTransitionToMove(character);
}

/// <summary>攻撃アニメーションが終了しているか判定</summary>
bool UtilStateConditionFunction::IsAttackAnimationFinished(CharacterBase* character)
{
    // 推測: ATTACKアニメーションタイプでない場合、攻撃終了とみなす
    // 根拠: StatePlayer.cppのStateCheckメソッドで使用されている
    return !character->CheckAnimationType(ANIMATION_MOVE_TYPE::ATTACK);
}

/// <summary>攻撃アニメーション終了時、移動キーが押されているか判定</summary>
bool UtilStateConditionFunction::ShouldTransitionToMoveAfterAttack(CharacterBase* character)
{
    return IsAttackAnimationFinished(character) && ShouldTransitionToMove(character);
}

/// <summary>通常攻撃キーが押されているか判定</summary>
bool UtilStateConditionFunction::ShouldTransitionToNormalAttack(CharacterBase* character)
{
    // 推測: PlayerProcess::GetPlayerNormalAttackFlag()と同じ判定を行う
    // 根拠: StatePlayer.cppのStateCheckメソッドで使用されている
    KeyState* keyState = Master::mpKeyState;
    return keyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::L);
}

/// <summary>特殊攻撃キーが押されているか判定</summary>
bool UtilStateConditionFunction::ShouldTransitionToSpecialAttack(CharacterBase* character)
{
    // 推測: PlayerProcess::GetPlayerSpceialAttackFlag()と同じ判定を行う
    // 根拠: StatePlayer.cppのStateCheckメソッドで使用されている
    KeyState* keyState = Master::mpKeyState;
    return keyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::R);
}

/// <summary>ジャンプ攻撃キーが押されているか判定</summary>
bool UtilStateConditionFunction::ShouldTransitionToJumpAttack(CharacterBase* character)
{
    // 推測: PlayerProcess::GetPlayerJumpAttackFlag()と同じ判定を行う
    // 根拠: StatePlayer.cppのStateCheckメソッドで使用されている
    KeyState* keyState = Master::mpKeyState;
    return keyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::RT);
}

/* エネミー状態遷移条件 */

/// <summary>攻撃状態へ遷移する条件か</summary>
bool UtilStateConditionFunction::IsAttackCondition(CharacterBase* character)
{
    TargetManager* targetManager = Master::mpGameManager->GetTargetManager();
    CharacterBase* player = targetManager->GetTarget(TARGET_TYPE::PLAYER);

    float distance = UtilCalc::VDiff(player->GetPos(), character->GetPos());

    return distance < 1000.0f;
}

/// <summary>移動状態へ遷移する条件か</summary>
bool UtilStateConditionFunction::IsMoveCondition(CharacterBase* character)
{
    TargetManager* targetManager = Master::mpGameManager->GetTargetManager();
    CharacterBase* player = targetManager->GetTarget(TARGET_TYPE::PLAYER);

    float distance = UtilCalc::VDiff(player->GetPos(), character->GetPos());

    return distance < 3000.0f;
}

/// <summary>待機状態へ遷移する条件か</summary>
bool UtilStateConditionFunction::IsIdleCondition(CharacterBase* character)
{
    TargetManager* targetManager = Master::mpGameManager->GetTargetManager();
    CharacterBase* player = targetManager->GetTarget(TARGET_TYPE::PLAYER);

    float distance = UtilCalc::VDiff(player->GetPos(), character->GetPos());

    return distance < 4000.0f;
}
// /// <summary>プレイヤーとの距離に基づいて次の状態を判定</summary>
// STATE_TYPE_CHARACTER GetNextStateByPlayerDistance(CharacterBase* character)
// {
// 	// 推測: EnemyProcess::GetPlayerDistance_Command()と同じ判定を行う
// 	// 根拠: StateEnemy.cppのStateCheckメソッドで使用されている
// 	// 仮定: ターゲットマネージャーからプレイヤーを取得可能
// 	TargetManager* targetManager = Master::mpGameManager->GetTargetManager();
// 	CharacterBase* player = targetManager->GetTarget(TARGET_TYPE::PLAYER);

// 	float distance = UtilCalc::VDiff(player->GetPos(), character->GetPos());

// 	if (distance < 1000.0f)
// 	{
// 		return STATE_TYPE_CHARACTER::ATTACK_IN_ENEMY_STATE;
// 	}
// 	else if (distance < 3000.0f)
// 	{
// 		return STATE_TYPE_CHARACTER::MOVE_ENEMY_STATE;
// 	}
// 	else if (distance < 4000.0f)
// 	{
// 		return STATE_TYPE_CHARACTER::IDLE_ENEMY_STATE;
// 	}

// 	return character->GetStateNumber();
// }

/// <summary>プレイヤーの方角を向いているか判定</summary>
bool UtilStateConditionFunction::IsFacingPlayer(CharacterBase* character)
{
    // 推測: AttackInEnemyStateのStateCheckメソッドの条件を再現
    // 根拠: StateEnemy.cppのAttackInEnemyState::StateCheck()で使用されている
    TargetManager* targetManager = Master::mpGameManager->GetTargetManager();
    CharacterBase* player = targetManager->GetTarget(TARGET_TYPE::PLAYER);

    float angleDiff = UtilCalc::AngleDiff(
        UtilCalc::VVecToAngle(VSub(player->GetPos(), character->GetPos())).y,
        character->GetAngle().y
    );

    return angleDiff < 0.1f;
}

/* シーン状態遷移条件 */

/// <summary>ウェーブ設定が可能か判定</summary>
bool UtilStateConditionFunction::CanSetNextWave(SceneManager* sceneManager)
{
    // 推測: DataManagerのSetNextWave()メソッドを使用
    // 根拠: StateScene.cppのGameLoopScene::OnEnter()で使用されている
    return Master::mpDataManager->SetNextWave();
}

/// <summary>ゲーム終了条件を満たしているか判定</summary>
bool UtilStateConditionFunction::ShouldEndGame(SceneManager* sceneManager)
{
    // 推測: ウェーブ設定が不可能な場合、ゲーム終了とみなす
    // 根拠: StateScene.cppのGameLoopScene::OnEnter()で使用されている
    return !CanSetNextWave(sceneManager);
}

/* UI状態遷移条件 */

/// <summary>メニューキーが押されているか判定</summary>
bool UtilStateConditionFunction::IsMenuKeyPressed(UIBase* ui)
{
    // 推測: GameUIProcess::IsMenuKeyPressed()と同じ判定を行う
    // 根拠: StateGameUI.cppのUpdateメソッドで使用されている
    KeyState* keyState = Master::mpKeyState;
    return keyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::X);
}