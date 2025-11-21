#include <string>

#include "Master.h"

#include "CameraManager.h"
#include "GameManager.h"
#include "KeyState.h"
#include "ObjectBases.h"
#include "StatePlayer.h"
#include "TargetManager.h"
#include "TimeManager.h"
#include "UtilCalc.h"

/*------------------*/
/*     【共通】     */
/*------------------*/

/*------------------------*/
/*【プレイヤー共通処理用】*/
/*------------------------*/
PlayerProcess::PlayerProcess()
: mpKeyState(Master::mpKeyState)
, mpCameraManager(Master::mpGameManager->GetCameraManager())
{
}

// 移動共通処理
void PlayerProcess::SetPlayerMove(CharacterBase* character)
{
	if (mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::W))
	{
		character->SetFrontMove();
	}
	if (mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::S))
	{
		character->SetBackMove();
	}
	if (mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::A))
	{
		character->SetLeftMove();
	}
	if (mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::D))
	{
		character->SetRightMove();
	}


	if (mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::Q))
	{
		character->SetUpMove();
	}
	if (mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::E))
	{
		character->SetDownMove();
	}
}

// 移動キーを押していれば「true」
bool PlayerProcess::GetPlayerMoveFlag()
{
	return mpKeyState->GetNowWordKeyFlags_Board() & (((unsigned long long)1 << (int)KEY_BOARD_WORD::W) |
													 ((unsigned long long)1 << (int)KEY_BOARD_WORD::A) |
													 ((unsigned long long)1 << (int)KEY_BOARD_WORD::S) |
													 ((unsigned long long)1 << (int)KEY_BOARD_WORD::D));
}

// 攻撃キーを押していれば「true」
bool PlayerProcess::GetPlayerAttackFlag()
{
	return mpKeyState->GetWordKeyDown_Board(KEY_BOARD_WORD::L);
}

// カメラに合わせて移動方向を設定
void PlayerProcess::SetMoveDir_Camera(CharacterBase* character)
{
	character->SetMoveDir(mpCameraManager->GetCameraData().GetDirection());
}

// 描画
void PlayerProcess::PlayerProcessDraw(CharacterBase* character)
{
	// HACK: モデルが出来たら消す

	VECTOR pos1;
	VECTOR pos2;

	SetUseZBufferFlag(true);

	pos1 = VGet(-10000.0f / 2.0f, 0.0f, -10000.0f / 2.0f);
	pos2 = VGet(-10000.0f / 2.0f, 0.0f, 10000.0f / 2.0f);
	for (int i = 0; i < 50; i++)
	{
		DrawLine3D(pos1, pos2, GetColor(0, 255, 0));
		pos1.x += 10000.0f / 50;
		pos2.x += 10000.0f / 50;
	}

	pos1 = VGet(-10000.0f / 2.0f, 0.0f, -10000.0f / 2.0f);
	pos2 = VGet(10000.0f / 2.0f, 0.0f, -10000.0f / 2.0f);
	for (int i = 0; i < 50; i++)
	{
		DrawLine3D(pos1, pos2, GetColor(255, 0, 0));
		pos1.z += 10000.0f / 50;
		pos2.z += 10000.0f / 50;
	}

	DrawString(500 , 10 , (std::to_string(character->GetPos().x) + "\n" + std::to_string(character->GetPos().y) + "\n" + std::to_string(character->GetPos().z)).c_str(), GetColor(255, 255, 0));
}

// 死亡
void PlayerProcess::PlayerDeath(CharacterBase* character)
{
	Master::mpGameManager->GetTargetManager()->Delete(character, TARGET_TYPE::PLAYER);
}

/*--------------------------*/
/*     【基本ステート】     */
/*--------------------------*/

/*--------------------------*/
/*【Idleプレイヤーステート】*/
/*--------------------------*/
IdlePlayerState::IdlePlayerState()
: PlayerProcess()
{
	mStateNumber = (int)PLAYER_STATE::IDLE_PLAYER_STATE;
}

// この状態に入った時の処理
void IdlePlayerState::OnEnter(CharacterBase* character)
{
}

// この状態を出る時の処理
void IdlePlayerState::OnExit(CharacterBase* character)
{
}

// ステート変更確認
int IdlePlayerState::StateCheck(CharacterBase* character)
{
	if (GetPlayerMoveFlag())
	{
		return (int)PLAYER_STATE::MOVE_PLAYER_STATE;
	}

	return mStateNumber;
}

// 更新
void IdlePlayerState::Update(CharacterBase* character)
{
}

// 最終更新
void IdlePlayerState::LastUpdate(CharacterBase* character)
{
}

// 描画
void IdlePlayerState::Draw(CharacterBase* character)
{
	PlayerProcessDraw(character);
}

// 死亡
void IdlePlayerState::Death(CharacterBase* character)
{
	PlayerDeath(character);
}

/*--------------------------*/
/*【移動プレイヤーステート】*/
/*--------------------------*/
MovePlayerState::MovePlayerState()
: PlayerProcess()
{
	mStateNumber = (int)PLAYER_STATE::MOVE_PLAYER_STATE;
}

// この状態に入った時の処理
void MovePlayerState::OnEnter(CharacterBase* character)
{
}

// この状態を出る時の処理
void MovePlayerState::OnExit(CharacterBase* character)
{
}

// ステート変更確認
int MovePlayerState::StateCheck(CharacterBase* character)
{
	if (!GetPlayerMoveFlag())
	{
		return (int)PLAYER_STATE::IDLE_PLAYER_STATE;
	}

	return mStateNumber;
}

// 更新
void MovePlayerState::Update(CharacterBase* character)
{
	SetMoveDir_Camera(character);

	SetPlayerMove(character);
}

// 最終更新
void MovePlayerState::LastUpdate(CharacterBase* character)
{
}

// 描画
void MovePlayerState::Draw(CharacterBase* character)
{
	PlayerProcessDraw(character);
}

// 死亡
void MovePlayerState::Death(CharacterBase* character)
{
	PlayerDeath(character);
}

/*--------------------------*/
/*【移動プレイヤーステート】*/
/*--------------------------*/
AttackPlayerState::AttackPlayerState()
: PlayerProcess()
, mnAttackTime(0)
{
	mStateNumber = (int)PLAYER_STATE::ATTACK_PLAYER_STATE;
}

// この状態に入った時の処理
void AttackPlayerState::OnEnter(CharacterBase* character)
{
	mnAttackTime = (character->StartAttck() + Master::mpTimeManager->GetGameTime());
}

// この状態を出る時の処理
void AttackPlayerState::OnExit(CharacterBase* character)
{
}

// ステート変更確認
int AttackPlayerState::StateCheck(CharacterBase* character)
{
	if (mnAttackTime <= Master::mpTimeManager->GetGameTime())
	{
		if (GetPlayerMoveFlag())
		{
			return (int)PLAYER_STATE::MOVE_PLAYER_STATE;
		}

		return (int)PLAYER_STATE::IDLE_PLAYER_STATE;
	}

	return mStateNumber;
}

// 更新
void AttackPlayerState::Update(CharacterBase* character)
{
}

// 最終更新
void AttackPlayerState::LastUpdate(CharacterBase* character)
{
}

// 描画
void AttackPlayerState::Draw(CharacterBase* character)
{
	PlayerProcessDraw(character);
}

// 死亡
void AttackPlayerState::Death(CharacterBase* character)
{
	PlayerDeath(character);
}

/*----------------------------*/
/*     【バトルステート】     */
/*----------------------------*/

/*--------------------------------*/
/*【Idleバトルプレイヤーステート】*/
/*--------------------------------*/
IdleBattlePlayerState::IdleBattlePlayerState()
: IdlePlayerState()
{

}

// ステート変更確認
int IdleBattlePlayerState::StateCheck(CharacterBase* character)
{
	if (GetPlayerAttackFlag())
	{
		return (int)PLAYER_STATE::ATTACK_PLAYER_STATE;
	}

	if (GetPlayerMoveFlag())
	{
		return (int)PLAYER_STATE::MOVE_PLAYER_STATE;
	}

	return mStateNumber;
}

/*--------------------------------*/
/*【移動バトルプレイヤーステート】*/
/*--------------------------------*/
MoveBattlePlayerState::MoveBattlePlayerState()
: MovePlayerState()
{

}

// ステート変更確認
int MoveBattlePlayerState::StateCheck(CharacterBase* character)
{
	if (GetPlayerAttackFlag())
	{
		return (int)PLAYER_STATE::ATTACK_PLAYER_STATE;
	}

	if (!GetPlayerMoveFlag())
	{
		return (int)PLAYER_STATE::IDLE_PLAYER_STATE;
	}

	return mStateNumber;
}