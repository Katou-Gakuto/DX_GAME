#pragma once
#include <vector>

#include "StateEnum.h"
#include "DrawData.h"

#include "ObjectBases.h"
#include "StateBase.h"

class CameraManager;
class KeyState;

/*------------------*/
/*     【共通】     */
/*------------------*/

/*----------------------*/
/*【プレイヤーステート】*/
/*----------------------*/

// enum class PLAYER_STATE
// {
// 	IDLE_PLAYER_STATE = 0,
// 	MOVE_PLAYER_STATE,
// 	NORMAL_ATTACK_PLAYER_STATE,
// 	SPCEIAL_ATTACK_PLAYER_STATE,
	
// 	FLINCH_PLAYER_STATE,	// 怯み
// 	AVOID_PLAYER_STATE,	// 避ける
// 	GUARD_PLAYER_STATE,	// ガード
// 	FALL_DOWN_PLAYER_STATE,	// 倒れる
// 	JUMP_ATTACK_PLAYER_STATE,	// ジャンプ攻撃
// };

/*------------------------*/
/*【プレイヤー共通処理用】*/
/*------------------------*/
class PlayerProcess
{
protected:
	enum PLAYER_DRAW_TYPE
	{
		HP_FRAME,
		HP_RIGHT,
		HP_LEFT,
		PLAYER_DRAW_MAX
	};

	enum PLAYER_DRAW_KEY_TYPE
	{
		PLAYER_DRAW_KEY_INVALID = 0,	// 無効
		PLAYER_DRAW_KEY_VALID,	// 有効
	};

	// キーステート
	KeyState* mpKeyState;

	// カメラ
	CameraManager* mpCameraManager;

	// HACK: カメラモード追加作成してこれらを消す
	// ターゲット番号
	static int mnTargetNumber;

	const Vector2 HP_FRAME_SIZE = Vector2(0.015f, 0.005f);
	const Vector2 HP_LEFT_UP = Vector2(0.01f + HP_FRAME_SIZE.x, 0.01f + HP_FRAME_SIZE.y);
	const Vector2 HP_RIGHT_DOWN = Vector2(0.4f + HP_FRAME_SIZE.x, 0.06f + HP_FRAME_SIZE.y);

	const Vector2_Int HP_GRAPH_SIZE = Vector2_Int(2151, 83);

	// Rキー描画情報
	DRAW_DATA mstRKeyDraw;
	// Lキー描画情報
	DRAW_DATA mstLKeyDraw;

protected:
	PlayerProcess();
	~PlayerProcess() = default;

	/*移動共通処理*/
	void SetPlayerMove(CharacterBase* character);

	/*移動キーを押していれば「true」*/
	bool GetPlayerMoveFlag();

	/*通常攻撃キーを押していれば「true」*/
	bool GetPlayerNormalAttackFlag();

	/*特殊攻撃キーを押していれば「true」*/
	bool GetPlayerSpceialAttackFlag();

	/*ジャンプ攻撃キーを押していれば「true」*/
	bool GetPlayerJumpAttackFlag();

	/*ターゲット変更キーを押していれば「true」*/
	bool GetTargetChangeFlag();

	/*カメラに合わせて移動方向を設定*/
	void SetMoveDir_Camera(CharacterBase* character);

	/*ターゲット変更*/
	void TargetChange();

	/*ターゲットにカメラを向ける*/
	void SetTargetCamera(CharacterBase* character);

	/*ターゲットアリのカメラ処理*/
	void TargetCameraProcess(CharacterBase* character);

	/*HP描画情報設定*/
	void HpDrawInfoSetup(CharacterBase* character);	

	/*描画*/
	void PlayerProcessDraw(CharacterBase* character);

	/*死亡*/
	void PlayerDeath(CharacterBase* character);

	/*LRキー描画情報設定*/
	void L_R_KeyDrawDataSetUp(PLAYER_DRAW_KEY_TYPE keyStatusNumber);

	/*プレイヤー共通処理 この状態に入った時*/
	void PlayerProcessOnEnter(CharacterBase* character);
	/*プレイヤー共通処理 この状態に出る時*/
	void PlayerProcessOnExit(CharacterBase* character);
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
	// FIXME: 呼び出し側で遷移条件を渡す場合は stateChangeCriterias を渡す
	IdlePlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, void>> stateChangeCriterias);
	~IdlePlayerState() = default;

	/*この状態に入った時の処理*/
	void OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState) override;
	/*この状態を出る時の処理*/
	void OnExit(CharacterBase* character, STATE_TYPE_CHARACTER newState) override;

	/*ステート変更確認*/
	virtual STATE_TYPE_CHARACTER StateCheck(CharacterBase* character) override;

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
/*【移動プレイヤーステート】*/
/*--------------------------*/
class MovePlayerState : public IStateCharacter, public PlayerProcess
{
public:
	// FIXME: 呼び出し側で遷移条件を渡す場合は stateChangeCriterias を渡す
	MovePlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, void>> stateChangeCriterias);
	~MovePlayerState() = default;

	/*この状態に入った時の処理*/
	void OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState) override;
	/*この状態を出る時の処理*/
	void OnExit(CharacterBase* character, STATE_TYPE_CHARACTER newState) override;

	/*ステート変更確認*/
	virtual STATE_TYPE_CHARACTER StateCheck(CharacterBase* character) override;

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
/*【ノーマル攻撃プレイヤーステート】*/
/*--------------------------*/
class NormalAttackPlayerState : public IStateCharacter, public PlayerProcess
{
public:
	// FIXME: 呼び出し側で遷移条件を渡す場合は stateChangeCriterias を渡す
	NormalAttackPlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, void>> stateChangeCriterias);
	~NormalAttackPlayerState() = default;

	/*この状態に入った時の処理*/
	void OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState) override;
	/*この状態を出る時の処理*/
	void OnExit(CharacterBase* character, STATE_TYPE_CHARACTER newState) override;

	/*ステート変更確認*/
	virtual STATE_TYPE_CHARACTER StateCheck(CharacterBase* character) override;

	/*更新*/
	void Update(CharacterBase* character) override;

	/*最終更新*/
	void LastUpdate(CharacterBase* character) override;

	/*描画*/
	void Draw(CharacterBase* character) override;

	/*死亡*/
	void Death(CharacterBase* character) override;
};

/*------------------------------------*/
/*【スペシャル攻撃プレイヤーステート】*/
/*------------------------------------*/
class SpceialAttackPlayerState : public IStateCharacter, public PlayerProcess
{
public:
	// FIXME: 呼び出し側で遷移条件を渡す場合は stateChangeCriterias を渡す
	SpceialAttackPlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, void>> stateChangeCriterias);
	~SpceialAttackPlayerState() = default;

	/*この状態に入った時の処理*/
	void OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState) override;
	/*この状態を出る時の処理*/
	void OnExit(CharacterBase* character, STATE_TYPE_CHARACTER newState) override;

	/*ステート変更確認*/
	virtual STATE_TYPE_CHARACTER StateCheck(CharacterBase* character) override;

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
/*【怯みプレイヤーステート】*/
/*--------------------------*/
class FlinchPlayerState : public IStateCharacter, public PlayerProcess
{
public:
	// FIXME: 呼び出し側で遷移条件を渡す場合は stateChangeCriterias を渡す
	FlinchPlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, void>> stateChangeCriterias);
	~FlinchPlayerState() = default;

	/*この状態に入った時の処理*/
	void OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState) override;
	/*この状態を出る時の処理*/
	void OnExit(CharacterBase* character, STATE_TYPE_CHARACTER newState) override;

	/*ステート変更確認*/
	virtual STATE_TYPE_CHARACTER StateCheck(CharacterBase* character) override;

	/*更新*/
	void Update(CharacterBase* character) override;

	/*最終更新*/
	void LastUpdate(CharacterBase* character) override;

	/*描画*/
	void Draw(CharacterBase* character) override;

	/*死亡*/
	void Death(CharacterBase* character) override;
};

/*----------------------------*/
/*【避けるプレイヤーステート】*/
/*----------------------------*/
class AvoidPlayerState : public IStateCharacter, public PlayerProcess
{
public:
	// FIXME: 呼び出し側で遷移条件を渡す場合は stateChangeCriterias を渡す
	AvoidPlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, void>> stateChangeCriterias);
	~AvoidPlayerState() = default;

	/*この状態に入った時の処理*/
	void OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState) override;
	/*この状態を出る時の処理*/
	void OnExit(CharacterBase* character, STATE_TYPE_CHARACTER newState) override;

	/*ステート変更確認*/
	virtual STATE_TYPE_CHARACTER StateCheck(CharacterBase* character) override;

	/*更新*/
	void Update(CharacterBase* character) override;

	/*最終更新*/
	void LastUpdate(CharacterBase* character) override;

	/*描画*/
	void Draw(CharacterBase* character) override;

	/*死亡*/
	void Death(CharacterBase* character) override;
};

/*----------------------------*/
/*【ガードプレイヤーステート】*/
/*----------------------------*/
class GuardPlayerState : public IStateCharacter, public PlayerProcess
{
public:
	// FIXME: 呼び出し側で遷移条件を渡す場合は stateChangeCriterias を渡す
	GuardPlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, void>> stateChangeCriterias);
	~GuardPlayerState() = default;

	/*この状態に入った時の処理*/
	void OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState) override;
	/*この状態を出る時の処理*/
	void OnExit(CharacterBase* character, STATE_TYPE_CHARACTER newState) override;

	/*ステート変更確認*/
	virtual STATE_TYPE_CHARACTER StateCheck(CharacterBase* character) override;

	/*更新*/
	void Update(CharacterBase* character) override;

	/*最終更新*/
	void LastUpdate(CharacterBase* character) override;

	/*描画*/
	void Draw(CharacterBase* character) override;

	/*死亡*/
	void Death(CharacterBase* character) override;
};

/*----------------------------*/
/*【倒れるプレイヤーステート】*/
/*----------------------------*/
class FallDownPlayerState : public IStateCharacter, public PlayerProcess
{
public:
	// FIXME: 呼び出し側で遷移条件を渡す場合は stateChangeCriterias を渡す
	FallDownPlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, void>> stateChangeCriterias);
	~FallDownPlayerState() = default;

	/*この状態に入った時の処理*/
	void OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState) override;
	/*この状態を出る時の処理*/
	void OnExit(CharacterBase* character, STATE_TYPE_CHARACTER newState) override;

	/*ステート変更確認*/
	virtual STATE_TYPE_CHARACTER StateCheck(CharacterBase* character) override;

	/*更新*/
	void Update(CharacterBase* character) override;

	/*最終更新*/
	void LastUpdate(CharacterBase* character) override;

	/*描画*/
	void Draw(CharacterBase* character) override;

	/*死亡*/
	void Death(CharacterBase* character) override;
};

/*----------------------------------*/
/*【ジャンプ攻撃プレイヤーステート】*/
/*----------------------------------*/
class JumpAttackPlayerState : public IStateCharacter, public PlayerProcess
{
private:
	// 上下速度
	float mfUpDownSpeed;

public:
	// FIXME: 呼び出し側で遷移条件を渡す場合は stateChangeCriterias を渡す
	JumpAttackPlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, void>> stateChangeCriterias);
	~JumpAttackPlayerState() = default;

	/*この状態に入った時の処理*/
	void OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState) override;
	/*この状態を出る時の処理*/
	void OnExit(CharacterBase* character, STATE_TYPE_CHARACTER newState) override;

	/*ステート変更確認*/
	virtual STATE_TYPE_CHARACTER StateCheck(CharacterBase* character) override;

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

/*--------------------------------*/
/*【Idleバトルプレイヤーステート】*/
/*--------------------------------*/
class IdleBattlePlayerState : public IdlePlayerState
{
public:
	// FIXME: 呼び出し側で遷移条件を渡す場合は stateChangeCriterias を渡す
	IdleBattlePlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, void>> stateChangeCriterias);
	~IdleBattlePlayerState() = default;

	/*ステート変更確認*/
	STATE_TYPE_CHARACTER StateCheck(CharacterBase* character) override;
};

/*--------------------------------*/
/*【移動バトルプレイヤーステート】*/
/*--------------------------------*/
class MoveBattlePlayerState : public MovePlayerState
{
public:
	// FIXME: 呼び出し側で遷移条件を渡す場合は stateChangeCriterias を渡す
	MoveBattlePlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, void>> stateChangeCriterias);
	~MoveBattlePlayerState() = default;

	/*ステート変更確認*/
	STATE_TYPE_CHARACTER StateCheck(CharacterBase* character) override;
};