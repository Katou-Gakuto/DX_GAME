#pragma once

#include "StateEnum.h"

class CharacterBase;
class SceneManager;
class UIBase;

/*------------------------------*/
/*【ステート遷移条件関数】*/
/*------------------------------*/

namespace UtilStateConditionFunction {
	/* プレイヤー状態遷移条件 */

	/// <summary>移動キーが押されているか判定</summary>
	/// <param name="character">キャラクター</param>
	/// <returns>移動キーが押されているならtrue</returns>
	bool ShouldTransitionToMove(CharacterBase* character);

	/// <summary>移動キーが押されていないか判定</summary>
	/// <param name="character">キャラクター</param>
	/// <returns>移動キーが押されていないならtrue</returns>
	bool ShouldTransitionToIdle(CharacterBase* character);

	/// <summary>攻撃アニメーションが終了しているか判定</summary>
	/// <param name="character">キャラクター</param>
	/// <returns>攻撃アニメーションが終了しているならtrue</returns>
	bool IsAttackAnimationFinished(CharacterBase* character);

	/// <summary>攻撃アニメーション終了時、移動キーが押されているか判定</summary>
	/// <param name="character">キャラクター</param>
	/// <returns>攻撃アニメーション終了時、移動キーが押されているならtrue</returns>
	bool ShouldTransitionToMoveAfterAttack(CharacterBase* character);

	/// <summary>通常攻撃キーが押されているか判定</summary>
	/// <param name="character">キャラクター</param>
	/// <returns>通常攻撃キーが押されているならtrue</returns>
	bool ShouldTransitionToNormalAttack(CharacterBase* character);

	/// <summary>特殊攻撃キーが押されているか判定</summary>
	/// <param name="character">キャラクター</param>
	/// <returns>特殊攻撃キーが押されているならtrue</returns>
	bool ShouldTransitionToSpecialAttack(CharacterBase* character);

	/// <summary>ジャンプ攻撃キーが押されているか判定</summary>
	/// <param name="character">キャラクター</param>
	/// <returns>ジャンプ攻撃キーが押されているならtrue</returns>
	bool ShouldTransitionToJumpAttack(CharacterBase* character);

	/* エネミー状態遷移条件 */
    
    /// <summary>プレイヤーとの距離に基づいて攻撃状態へ遷移するか判定</summary>
    /// <param name="character">キャラクター</param>
    /// <returns>攻撃状態へ遷移する場合はtrue</returns>
    bool IsAttackCondition(CharacterBase* character);

    /// <summary>プレイヤーとの距離に基づいて移動状態へ遷移するか判定</summary>
    /// <param name="character">キャラクター</param>
    /// <returns>移動状態へ遷移する場合はtrue</returns>
    bool IsMoveCondition(CharacterBase* character);

    /// <summary>プレイヤーとの距離に基づいて待機状態へ遷移するか判定</summary>
    /// <param name="character">キャラクター</param>
    /// <returns>待機状態へ遷移する場合はtrue</returns>
    bool IsIdleCondition(CharacterBase* character);

	/// <summary>プレイヤーの方角を向いているか判定</summary>
	/// <param name="character">キャラクター</param>
	/// <returns>プレイヤーの方角を向いているならtrue</returns>
	bool IsFacingPlayer(CharacterBase* character);

	/* シーン状態遷移条件 */

	/// <summary>ウェーブ設定が可能か判定</summary>
	/// <param name="sceneManager">シーンマネージャー</param>
	/// <returns>ウェーブ設定が可能ならtrue</returns>
	bool CanSetNextWave(SceneManager* sceneManager);

	/// <summary>ゲーム終了条件を満たしているか判定</summary>
	/// <param name="sceneManager">シーンマネージャー</param>
	/// <returns>ゲーム終了条件を満たしているならtrue</returns>
	bool ShouldEndGame(SceneManager* sceneManager);

	/* UI状態遷移条件 */

	/// <summary>メニューキーが押されているか判定</summary>
	/// <param name="ui">UIベース</param>
	/// <returns>メニューキーが押されているならtrue</returns>
	bool IsMenuKeyPressed(UIBase* ui);
}
