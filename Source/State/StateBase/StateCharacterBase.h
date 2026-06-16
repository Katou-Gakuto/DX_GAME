#pragma once
#include <vector>

#include "StateEnum.h"

#include "StateBase.h"

class CharacterBase;

/*------------------------------*/
/*【キャラクターステートベース】*/
/*------------------------------*/
class IStateCharacter : public StateBase<STATE_TYPE_CHARACTER, CharacterBase>
{
protected:
	// // 共通キャラクターステート
	// enum COMMON_CHARACTER_STATE
	// {
	// 	IDEL_COMMON_CHARACTER_STATE = 0,	// 通常
	// 	MOVE_COMMON_CHARACTER_STATE,	// 移動
	// 	FLINCH_COMMON_CHARACTER_STATE,	// 怯み
	// 	AVOID_COMMON_CHARACTER_STATE,	// 回避
	// 	GUARD_COMMON_CHARACTER_STATE,	// ガード
	// 	FALL_DOWN_COMMON_CHARACTER_STATE,	// 倒れる

	// 	ATTACK_COMMON_CHARACTER_STATE,	// 攻撃
	// 	NORMAL_ATTACK_COMMON_CHARACTER_STATE,	// 通常攻撃
	// 	SPCEIAL_ONE_ATTACK_COMMON_CHARACTER_STATE,	// 特殊攻撃 1
	// 	SPCEIAL_TWO_ATTACK_COMMON_CHARACTER_STATE,	// 特殊攻撃 1

	// 	COMMON_CHARACTER_STATE_MAX	// 共通キャラクターステート最大数
	// };
	// // INPROGRESS: ステート条件金曜過ぎたら変更

public:
	IStateCharacter(STATE_TYPE_CHARACTER stateNumber, std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias)
	: StateBase(stateNumber, stateChangeCriterias)
	{
	}
	virtual ~IStateCharacter() = default;

	/// <summary>初期化</summary>
	virtual void Initilize(CharacterBase* character) {}
	/// <summary>終了</summary>
	virtual void Finalize(CharacterBase* character) {}

	// /*この状態に入った時の処理*/
	// virtual void OnEnter(CharacterBase* character) = 0;
	// /*この状態を出る時の処理*/
	// virtual void OnExit(CharacterBase* character) = 0;

	/*ステート変更確認*/
	virtual STATE_TYPE_CHARACTER StateCheck(CharacterBase* character) = 0;
	/*更新*/
	virtual void Update(CharacterBase* character) = 0;
	/*最終更新*/
	virtual void LastUpdate(CharacterBase* character) = 0;

	/*描画*/
	virtual void Draw(CharacterBase* character) = 0;

	/*死亡*/
	virtual void Death(CharacterBase* character) = 0;
};