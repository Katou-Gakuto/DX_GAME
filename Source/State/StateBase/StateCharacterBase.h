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
	STATE_TYPE_CHARACTER meMyStateType;
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
	IStateCharacter(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias, STATE_TYPE_CHARACTER stateNumber, STATE_TYPE_CHARACTER stateType)
	: StateBase(stateChangeCriterias, stateNumber)
	, meMyStateType(stateType)
	{
	}
	virtual ~IStateCharacter() = default;

	/// <summary>初期化</summary>
	virtual void Initilize(CharacterBase* character) {}
	/// <summary>終了</summary>
	virtual void Finalize(CharacterBase* character) {}

	
	/*更新*/
	virtual void Update(CharacterBase* character) = 0;
	/*最終更新*/
	virtual void LastUpdate(CharacterBase* character) = 0;

	/*描画*/
	virtual void Draw(CharacterBase* character) = 0;

	/// <summary>ステートナンバーずらしても使える固定ステート種類取得</summary>
	/// <returns>固定ステート種類</returns>
	STATE_TYPE_CHARACTER GetMyStateType() { return meMyStateType; }
};