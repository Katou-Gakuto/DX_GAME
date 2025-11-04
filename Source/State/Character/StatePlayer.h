#pragma once

#include "ObjectBases.h"
#include "StateBase.h"

class KeyState;

/*------------------*/
/*     【共通】     */
/*------------------*/

/*----------------------*/
/*【プレイヤーステート】*/
/*----------------------*/

enum class PLAYER_STATE
{
	IDLE_PLAYER_STATE = 0,
	MOVE_PLAYER_STATE,
	ATTACK_PLAYER_STATE,
};

/*------------------------*/
/*【プレイヤー共通処理用】*/
/*------------------------*/
class PlayerProcess
{
protected:
	// キーステート
	KeyState* mpKeyState;

protected:
	PlayerProcess();
	~PlayerProcess() = default;

	/*移動共通処理*/
	void SetPlayerMove(CharacterBase* character);

	/*移動キーを押していれば「true」*/
	bool GetPlayerMoveFlag();

	/*攻撃キーを押していれば「true」*/
	bool GetPlayerAttackFlag();

	/*描画*/
	void PlayerProcessDraw();
};

/*--------------------------*/
/*     【基本ステート】     */
/*--------------------------*/

/*--------------------------*/
/*【Idleプレイヤーステート】*/
/*--------------------------*/
class IdlePlayerState : public IStateCharacter, public PlayerProcess
{
public:
	IdlePlayerState();
	~IdlePlayerState() = default;

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
};

/*--------------------------*/
/*【移動プレイヤーステート】*/
/*--------------------------*/
class MovePlayerState : public IStateCharacter, public PlayerProcess
{
public:
	MovePlayerState();
	~MovePlayerState() = default;

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
};

/*--------------------------*/
/*【攻撃プレイヤーステート】*/
/*--------------------------*/
class AttackPlayerState : public IStateCharacter, public PlayerProcess
{
private:
	// 攻撃時間(硬直)
	int mnAttackTime;

public:
	AttackPlayerState();
	~AttackPlayerState() = default;

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
};

/*--------------------------*/
/*     【派生ステート】     */
/*--------------------------*/

/*--------------------------------*/
/*【Idleバトルプレイヤーステート】*/
/*--------------------------------*/
class IdleBattlePlayerState : public IdlePlayerState
{
public:
	IdleBattlePlayerState();
	~IdleBattlePlayerState() = default;

	/*ステート変更確認*/
	int StateCheck(CharacterBase* character) override;
};

/*--------------------------------*/
/*【移動バトルプレイヤーステート】*/
/*--------------------------------*/
class MoveBattlePlayerState : public MovePlayerState
{
public:
	MoveBattlePlayerState();
	~MoveBattlePlayerState() = default;

	/*ステート変更確認*/
	int StateCheck(CharacterBase* character) override;
};