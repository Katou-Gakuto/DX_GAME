#pragma once

#include "StateEnum.h"
#include "TimeData.h"

#include "EnemyCommonProcessing.h"
#include "ObjectBases.h"
#include "StateCharacterBase.h"

class TargetManager;

// TODO: 移動するシーンを生成時取得

/*------------------*/
// /*     【共通】     */
/*------------------*/

/*--------------------*/
// /*【エネミーステート】*/
/*--------------------*/

// enum class ENEMY_STATE
// {
// 	IDLE_ENEMY_STATE = 0,
// 	MOVE_ENEMY_STATE,
// 	ATTACK_IN_ENEMY_STATE,
// 	ATTACK_ENEMY_STATE,
// 	RIGHT_AVOID_ENEMY_STATE,
// 	LEFT_AVOID_ENEMY_STATE,
// 	ESCAPE_ENEMY_STATE,
// };

/*----------*/
// /*【エネミーコマンドナンバー】
/*----------*/
enum class ENEMY_COMMAND_NUMBER
{
	NONE = -1,
	SHORT_RANGE = 0,
	MEDIUM_RANGE,
	LONG_RANGE,
};

// 逃げ時間
const int ESCAPE_TIME = 17 * 100;

/*----------------------*/
// /*【エネミー共通処理用】*/
/*----------------------*/
class EnemyProcess : public EnemyCommonProcessing
{

protected:
// 	// ターゲットマネージャー
	TargetManager* mpTargetManager;

protected:
	EnemyProcess();
	~EnemyProcess() = default;

// 	/*プレイヤーのステータス設定*/
	void SetPlayerStatus();

// 	/*一定範囲内にプレイヤーターゲットがいるなら「true」*/
	bool PlayerTargetCheck(CharacterBase* character, float range);

// 	/*プレイヤー方向を向いて移動する*/
	void PlayerTargetMove(CharacterBase* character);

// 	/*プレイヤーターゲットの方向に向く*/
	void PlayerTargetAngle(CharacterBase* character);

// 	/*死亡処理*/
	virtual void EnemyDeath(CharacterBase* character);

// 	/*プレイヤーの位置によってコマンドを返す*/
	virtual ENEMY_COMMAND_NUMBER GetPlayerDistance_Command(CharacterBase* character);

// 	/*定型の次のステートを取得する*/
	STATE_TYPE_CHARACTER TemplateNextState(CharacterBase* character, STATE_TYPE_CHARACTER myState);
};

/*--------------------------*/
// /*     【基本ステート】     */
/*--------------------------*/

/*----------------------*/
// /*【Idleエネミーテート】*/
/*----------------------*/
class IdleEnemyState : public IStateCharacter, public EnemyProcess
{
public:
	// FIXME: ??яo??????J???????n?????
	IdleEnemyState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias = {});
	~IdleEnemyState() = default;

	void Finalize(CharacterBase* character) override { EnemyCommonProcessingData_Delete();}

// 	/*この状態に入った時の処理*/
	void OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState) override;
// 	/*この状態を出る時の処理*/
	void OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState) override;
	STATE_TYPE_CHARACTER StateCheck(CharacterBase* character) override;

// 	/*更新*/
	void Update(CharacterBase* character) override;

// 	/*最終更新*/
	void LastUpdate(CharacterBase* character) override;

// 	/*描画*/
	void Draw(CharacterBase* character) override;
	void Death(CharacterBase* character) override;
};

/*----------*/
// /*【移動エネミーステート】
/*----------*/
class MoveEnemyState : public IStateCharacter, public EnemyProcess
{
public:
	// FIXME: ??яo??????J???????n?????
	MoveEnemyState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias = {});
	~MoveEnemyState() = default;

	void Finalize(CharacterBase* character) override { EnemyCommonProcessingData_Delete();}

// 	/*この状態に入った時の処理*/
	void OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState) override;
// 	/*この状態を出る時の処理*/
	void OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState) override;
	STATE_TYPE_CHARACTER StateCheck(CharacterBase* character) override;

// 	/*更新*/
	void Update(CharacterBase* character) override;

// 	/*最終更新*/
	void LastUpdate(CharacterBase* character) override;

// 	/*描画*/
	void Draw(CharacterBase* character) override;
	void Death(CharacterBase* character) override;
};

/*----------*/
// /*【攻撃入りエネミーステート】
/*----------*/
class AttackInEnemyState : public IStateCharacter, public EnemyProcess
{
private:
// 	// 左回避フラグ
	bool mbLeftMoveFlag;

// 	// 前回攻撃時間
	TIME_DATA mstPreAttackTime;

public:
	// FIXME: ??яo??????J???????n?????
	AttackInEnemyState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias = {});
	~AttackInEnemyState() = default;

	void Finalize(CharacterBase* character) override { EnemyCommonProcessingData_Delete();}

// 	/*この状態に入った時の処理*/
	void OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState) override;
// 	/*この状態を出る時の処理*/
	void OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState) override;
	STATE_TYPE_CHARACTER StateCheck(CharacterBase* character) override;

// 	/*更新*/
	void Update(CharacterBase* character) override;

// 	/*最終更新*/
	void LastUpdate(CharacterBase* character) override;

// 	/*描画*/
	void Draw(CharacterBase* character) override;
	void Death(CharacterBase* character) override;
};

/*----------*/
// /*【攻撃エネミーステート】
/*----------*/
class AttackEnemyState : public IStateCharacter, public EnemyProcess
{
public:
	// FIXME: ??яo??????J???????n?????
	AttackEnemyState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias = {});
	~AttackEnemyState() = default;

	void Finalize(CharacterBase* character) override { EnemyCommonProcessingData_Delete();}

// 	/*この状態に入った時の処理*/
	void OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState) override;
// 	/*この状態を出る時の処理*/
	void OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState) override;
	STATE_TYPE_CHARACTER StateCheck(CharacterBase* character) override;

// 	/*更新*/
	void Update(CharacterBase* character) override;

// 	/*最終更新*/
	void LastUpdate(CharacterBase* character) override;

// 	/*描画*/
	void Draw(CharacterBase* character) override;
	void Death(CharacterBase* character) override;
};

/*------------------------*/
// /*【逃げエネミーステート】*/
/*------------------------*/
class EscapeEnemyState : public IStateCharacter, public EnemyProcess
{
protected:
// 	// 逃げ時間
	TIME_DATA mstEscapeTime;

public:
	// FIXME: ??яo??????J???????n?????
	EscapeEnemyState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias = {});
	~EscapeEnemyState() = default;

	void Finalize(CharacterBase* character) override { EnemyCommonProcessingData_Delete();}

// 	/*この状態に入った時の処理*/
	virtual void OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState) override;
// 	/*この状態を出る時の処理*/
	void OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState) override;
	STATE_TYPE_CHARACTER StateCheck(CharacterBase* character) override;

// 	/*更新*/
	virtual void Update(CharacterBase* character) override;

// 	/*最終更新*/
	void LastUpdate(CharacterBase* character) override;

// 	/*描画*/
	void Draw(CharacterBase* character) override;
	void Death(CharacterBase* character) override;
};

/*--------------------------*/
// /*     【派生ステート】     */
/*--------------------------*/

/*--------------------------*/
// /*【左回避エネミーステート】*/
/*--------------------------*/
class LeftAvoidEnemyState : public EscapeEnemyState
{
public:
	// FIXME: ??яo??????J???????n?????
	LeftAvoidEnemyState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias = {});
	~LeftAvoidEnemyState() = default;

// 	/*この状態に入った時の処理*/
	virtual void OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState) override;

// 	/*更新*/
	virtual void Update(CharacterBase* character) override;
};

/*--------------------------*/
// /*【右回避エネミーステート】*/
/*--------------------------*/
class RightAvoidEnemyState : public EscapeEnemyState
{
public:
	// FIXME: ??яo??????J???????n?????
	RightAvoidEnemyState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias = {});
	~RightAvoidEnemyState() = default;

// 	/*この状態に入った時の処理*/
	virtual void OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState) override;

// 	/*更新*/
	virtual void Update(CharacterBase* character) override;
};

/*
????\??X?e?[?g
?????@?????????????
????????????????????
?v???C???[???????????畷?????????x??????
?v???C???[????????????????????
?v???C???[????Q??????????????????????????????u?????
??HP??????????u??????????狗???????????v???C???[????F???????炸????????????????
??????v???C???[???u???????????????????
??????v???C???[???u????????????o??????????????
???????U???????i?s?????????????????????(???U????)????
??@??????????????????n???@???????
???R??s??????
*/
