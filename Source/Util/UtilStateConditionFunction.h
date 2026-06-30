#pragma once

#include "StateEnum.h"

#include "Master.h"

#include "KeyState.h"
#include "ObjectBases.h"

//class CharacterBase;
class SceneManager;

/*------------------------------*/
/*【ステート遷移条件関数】*/
/*------------------------------*/

namespace UtilStateConditionFunction
{
	/*キー状態のテンプレート*/
	template<KEY_BOARD_WORD Key, typename StateConditionData>
	/// <summary>キーが押し始めたか判定(キーボード　ワード)</summary>
	/// <param name="StateConditionData">状態遷移条件で使用するデータ</param>
	/// <returns>テンプレートで指定したキーが押され始めたなら「true」</returns>
	bool KeyDownStateCondition_KeyBoardWorad(StateConditionData* stateConditionData)
	{
		return Master::mpKeyState->GetWordKeyDown_Board(Key);
	}
	template<KEY_BOARD_SPECIAL Key, typename StateConditionData>
	/// <summary>キーが押し始めたか判定(キーボード　スペシャル)</summary>
	/// <param name="StateConditionData">状態遷移条件で使用するデータ</param>
	/// <returns>テンプレートで指定したキーが押され始めたなら「true」</returns>
	bool KeyDownStateCondition_KeyBoardSpecial(StateConditionData* stateConditionData)
	{
		return Master::mpKeyState->GetSpecialKeyDown_Board(Key);
	}
	template<KEY_BOARD_NUM_PAD Key, typename StateConditionData>
	/// <summary>キーが押し始めたか判定(キーボード　ナムパッド)</summary>
	/// <param name="StateConditionData">状態遷移条件で使用するデータ</param>
	/// <returns>テンプレートで指定したキーが押され始めたなら「true」</returns>
	bool KeyDownStateCondition_KeyBoardNumpad(StateConditionData* stateConditionData)
	{
		return Master::mpKeyState->GetNumpadKeyDown_Board(Key);
	}

	/*----- テンプレート -----*/
	/*!*/
	template<typename StateConditionData, bool(*Func)(StateConditionData*)>
	/// <summary>指定した状態遷移条件の結果を反転して返す</summary>
	/// <param name="stateConditionData">状態遷移条件で使用するデータ</param>
	/// <returns>指定した状態遷移条件がfalseならtrue、trueならfalse</returns>
    bool NotFunc(StateConditionData* stateConditionData)
    {
        return !Func(stateConditionData);
    }
	/*&*/
	template<typename StateConditionData, bool(*...Funcs)(StateConditionData*)>
	/// <summary>指定したすべての状態遷移条件を満たすか判定</summary>
	/// <param name="stateConditionData">状態遷移条件で使用するデータ</param>
	/// <returns>すべての状態遷移条件を満たしているならtrue</returns>
	bool AndFunc(StateConditionData* stateConditionData)
	{
		return (... && Funcs(stateConditionData));
	}
	/*||*/
	template<typename StateConditionData, bool(*...Funcs)(StateConditionData*)>
	/// <summary>指定したいずれかの状態遷移条件を満たすか判定</summary>
	/// <param name="stateConditionData">状態遷移条件で使用するデータ</param>
	/// <returns>いずれかの状態遷移条件を満たしているならtrue</returns>
	bool OrFunc(StateConditionData* stateConditionData)
	{
		return (... || Funcs(stateConditionData));
	}
	/*!(||)*/
	template<typename StateConditionData, bool(*...Funcs)(StateConditionData*)>
	/// <summary>指定したすべての状態遷移条件を満たしていないか判定</summary>
	/// <param name="stateConditionData">状態遷移条件で使用するデータ</param>
	/// <returns>すべての状態遷移条件を満たしていないならtrue</returns>
	bool NoneFunc(StateConditionData* stateConditionData)
	{
		return !(... || Funcs(stateConditionData));
	}
	/*------------------------*/

	/* UI状態遷移条件 */
	template<int templateNumber>
	/// <summary>選択しているナンバーがテンプレートナンバーと同じならtrue</summary>
	/// <param name="ui">UIオブジェクト</param>
	/// <returns>移動キーが押されているならtrue</returns>
	bool IsSelectedNumber(UIBase* ui)
	{
		return ui->GetSelectNumber() == templateNumber;
	}



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
