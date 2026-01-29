#pragma once

#include "ObjectBases.h"
#include "StateBase.h"

class TargetManager;

// TODO: 移動するシーンを生成時取得

/*------------------*/
/*     【共通】     */
/*------------------*/

/*--------------------*/
/*【エネミーステート】*/
/*--------------------*/

enum class ENEMY_STATE
{
	IDLE_ENEMY_STATE = 0,
	MOVE_ENEMY_STATE,
	ATTACK_ENEMY_STATE,
};

/*----------------------*/
/*【エネミー共通処理用】*/
/*----------------------*/
class EnemyProcess
{
protected:
	// 敵コマンドナンバー
	enum ENEMY_COMMAND_NUMBER
	{
		SHORT_RANGE = 0,
		MEDIUM_RANGE,
		LONG_RANGE,
	};

protected:
	// ターゲットマネージャー
	TargetManager* mpTargetManager;

protected:
	EnemyProcess();
	~EnemyProcess() = default;

	/*一定範囲内にプレイヤーターゲットがいるなら「true」*/
	bool PlayerTargetCheck(CharacterBase* character, float range);

	/*プレイヤー方向を向いて移動する*/
	void PlayerTargetMove(CharacterBase* character);

	/*プレイヤーターゲットの方向に向く*/
	void PlayerTargetAngle(CharacterBase* character);

	/*死亡処理*/
	virtual void EnemyDeath(CharacterBase* character);

	/*プレイヤーの位置によってコマンドを返す*/
	virtual int GetPlayerDistance_Command(CharacterBase* character);

	/*定型の次のステートを取得する*/
	int TemplateNextState(CharacterBase* character, int myState);
};

/*--------------------------*/
/*     【基本ステート】     */
/*--------------------------*/

/*----------------------*/
/*【Idleエネミーテート】*/
/*----------------------*/
class IdleEnemyState : public IStateCharacter, public EnemyProcess
{
public:
	IdleEnemyState();
	~IdleEnemyState() = default;

	/*この状態に入った時の処理*/
	void OnEnter(CharacterBase* character) override;
	/*この状態を出る時の処理*/
	void OnExit(CharacterBase* character) override;

	/*ステート変更確認*/
	virtual int StateCheck(CharacterBase* character) override;

	/*更新*/
	void Update(CharacterBase* character) override;

	/*最終更新*/
	void LastUpdate(CharacterBase* character) override;

	/*描画*/
	void Draw(CharacterBase* character) override;

	/*死亡*/
	void Death(CharacterBase* character) override;
};
// INPROGRESS: 作業中　敵基本行動作成中
/*----------*/
/*【移動エネミーステート】
/*----------*/
class MoveEnemyState : public IStateCharacter, public EnemyProcess
{
public:
	MoveEnemyState();
	~MoveEnemyState() = default;

	/*この状態に入った時の処理*/
	void OnEnter(CharacterBase* character) override;
	/*この状態を出る時の処理*/
	void OnExit(CharacterBase* character) override;

	/*ステート変更確認*/
	virtual int StateCheck(CharacterBase* character) override;

	/*更新*/
	void Update(CharacterBase* character) override;

	/*最終更新*/
	void LastUpdate(CharacterBase* character) override;

	/*描画*/
	void Draw(CharacterBase* character) override;

	/*死亡*/
	void Death(CharacterBase* character) override;
};

/*----------*/
/*【攻撃エネミーステート】
/*----------*/
class AttackEnemyState : public IStateCharacter, public EnemyProcess
{
public:
	AttackEnemyState();
	~AttackEnemyState() = default;

	/*この状態に入った時の処理*/
	void OnEnter(CharacterBase* character) override;
	/*この状態を出る時の処理*/
	void OnExit(CharacterBase* character) override;

	/*ステート変更確認*/
	virtual int StateCheck(CharacterBase* character) override;

	/*更新*/
	void Update(CharacterBase* character) override;

	/*最終更新*/
	void LastUpdate(CharacterBase* character) override;

	/*描画*/
	void Draw(CharacterBase* character) override;

	/*死亡*/
	void Death(CharacterBase* character) override;
};

/*--------------------------*/
/*     【派生ステート】     */
/*--------------------------*/

/*----------------------------*/
/*【Idleボスエネミーステート】*/
/*----------------------------*/
class IdleBossEnemyState : public IdleEnemyState
{
private:
public:
	IdleBossEnemyState();
	~IdleBossEnemyState() = default;

	/*死亡処理*/
	void EnemyDeath(CharacterBase* character) override;
};