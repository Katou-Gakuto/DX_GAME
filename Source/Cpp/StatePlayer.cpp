#include "../Header/Master.h"

#include "../Header/KeyState.h"
#include "../Header/StatePlayer.h"


/*------------------------*/
/*【プレイヤー共通処理用】*/
/*------------------------*/
PlayerProcess::PlayerProcess()
{
	mpKeyState = Master::mpKeyState;
}

// 移動共通処理
void PlayerProcess::SetPlayerMove(CharacterBase* character)
{
	if (mpKeyState->GetWordKeyDown_Board(KEY_BOARD_WORD::W))
	{
		character->SetUpMove();
	}
	if (mpKeyState->GetWordKeyDown_Board(KEY_BOARD_WORD::S))
	{
		character->SetDownMove();
	}
	if (mpKeyState->GetWordKeyDown_Board(KEY_BOARD_WORD::A))
	{
		character->SetLeftMove();
	}
	if (mpKeyState->GetWordKeyDown_Board(KEY_BOARD_WORD::D))
	{
		character->SetRightMove();
	}
}

// 移動キーを押していれば「true」
bool PlayerProcess::GetPlayerMoveFlag()
{
	return mpKeyState->GetDownWordKeyFlags_Board() & (unsigned long long)((1 << (int)KEY_BOARD_WORD::W) |
																		  (1 << (int)KEY_BOARD_WORD::A) |
																		  (1 << (int)KEY_BOARD_WORD::S) |
																		  (1 << (int)KEY_BOARD_WORD::D));
}

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
}

// 最終更新
void MovePlayerState::LastUpdate(CharacterBase* character)
{
}

// 描画
void MovePlayerState::Draw(CharacterBase* character)
{
}