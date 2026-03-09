#include <string>

#include "AttackEnum.h"
#include "CameraData.h"

#include "Master.h"

#include "CameraManager.h"
#include "GameManager.h"
#include "KeyState.h"
#include "MapManager.h"
#include "ObjectBases.h"
#include "SceneManager.h"
#include "StatePlayer.h"
#include "StopManager.h"
#include "ResourceManager.h"
#include "TargetManager.h"
#include "TimeManager.h"
#include "UtilCalc.h"

/*------------------*/
/*     【共通】     */
/*------------------*/

/*------------------------*/
/*【プレイヤー共通処理用】*/
/*------------------------*/
int PlayerProcess::mnTargetNumber = -1;
PlayerProcess::PlayerProcess()
: mpKeyState(Master::mpKeyState)
, mpCameraManager(Master::mpGameManager->GetCameraManager())
{
	mnTargetNumber = -1;
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


	// if (mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::Q))
	// {
	// 	character->SetUpMove();
	// }
	// if (mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::E))
	// {
	// 	character->SetDownMove();
	// }
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
bool PlayerProcess::GetPlayerNormalAttackFlag()
{
	return mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::L);
}

// 特殊攻撃キーを押していれば「true」
bool PlayerProcess::GetPlayerSpceialAttackFlag()
{
	return mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::R);
}

// ターゲット変更キーを押していれば「true」
bool PlayerProcess::GetTargetChangeFlag()
{
	return mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::Y);
}

// カメラに合わせて移動方向を設定
void PlayerProcess::SetMoveDir_Camera(CharacterBase* character)
{
	character->SetMoveDir(mpCameraManager->GetCameraData().GetDirection());
}

// ターゲット変更
void PlayerProcess::TargetChange()
{
	mnTargetNumber += 1;

	if (mnTargetNumber >= Master::mpGameManager->GetTargetManager()->GetTargets(TARGET_TYPE::ENEMY).size())
	{
		mnTargetNumber = -1;
	}
}

// ターゲットにカメラを向ける
void PlayerProcess::SetTargetCamera(CharacterBase* character)
{
	CharacterBase* targetEnemy = Master::mpGameManager->GetTargetManager()->GetTargets(TARGET_TYPE::ENEMY)[mnTargetNumber];

	CameraData cameraData = mpCameraManager->GetCameraData();
	cameraData.angle.y = -UtilCalc::VDegChange(UtilCalc::VMoveVecToAngle(VSub(character->GetPos(), targetEnemy->GetPos()), UtilCalc::VZero, UtilCalc::PiTwo)).y + UtilCalc::RadPi;
	mpCameraManager->SetCameraData(cameraData);
}

// ターゲットアリのカメラ処理
void PlayerProcess::TargetCameraProcess(CharacterBase* character)
{
	if (GetTargetChangeFlag())
	{
		TargetChange();
	}

	if (mnTargetNumber != -1)
	{
		SetTargetCamera(character);
	}

	SetMoveDir_Camera(character);
}


// HACK: 仮実装
#include "SceneEnum.h"

#include "UtilChange.h"
// 描画
void PlayerProcess::PlayerProcessDraw(CharacterBase* character)
{
	// HACK: 仮実装
	if ((UtilChange::SceneState(Master::mpGameManager->GetSceneManager()->GetNowScene()) == SCENE::BATTLE) ||
		(UtilChange::SceneState(Master::mpGameManager->GetSceneManager()->GetNowScene()) == SCENE::BATTLE_LOOP))
	{
		// HACK: これを更新のモデル描画前に移動させる
		Vector2_Int frameSize = ResourceManager::mstDisplaySize.LeftUp_Ratio(HP_FRAME_SIZE);
		Vector2_Int leftUp = ResourceManager::mstDisplaySize.LeftUp_Ratio(HP_LEFT_UP);
		Vector2_Int rightDown = ResourceManager::mstDisplaySize.LeftUp_Ratio(HP_RIGHT_DOWN);

		DrawBox(leftUp.x - frameSize.x, leftUp.y - frameSize.y, rightDown.x + frameSize.x, rightDown.y + frameSize.y, GetColor(0, 0, 0), TRUE);

		DrawBox(leftUp.x, leftUp.y, rightDown.x, rightDown.y, GetColor(100, 100, 100), TRUE);
		DrawBox(leftUp.x, leftUp.y, leftUp.x + ((rightDown.x - leftUp.x) * ((float)character->GetStatus()->hp / (float)character->GetStatus()->maxHp)) , rightDown.y, GetColor(255, 255, 255), TRUE);	
	}

	// VECTOR pos1;
	// VECTOR pos2;

	// SetUseZBufferFlag(true);

	// float size = /*/1000000.0f;//*/ 10000.0f;
	// int number = /*/5000; //*/ 50;
	// pos1 = VGet(-size / 2.0f, 0.0f, -size / 2.0f);
	// pos2 = VGet(-size / 2.0f, 0.0f, size / 2.0f);
	// for (int i = 0; i < number; i++)
	// {
	// 	DrawLine3D(pos1, pos2, GetColor(0, 255, 0));
	// 	pos1.x += size / number;
	// 	pos2.x += size / number;
	// }

	// pos1 = VGet(-size / 2.0f, 0.0f, -size / 2.0f);
	// pos2 = VGet(size / 2.0f, 0.0f, -size / 2.0f);
	// for (int i = 0; i < number; i++)
	// {
	// 	DrawLine3D(pos1, pos2, GetColor(255, 0, 0));
	// 	pos1.z += size / number;
	// 	pos2.z += size / number;
	// }

	//DrawString(500 , 10 , (std::to_string(character->GetPos().x) + "\n" + std::to_string(character->GetPos().y) + "\n" + std::to_string(character->GetPos().z)).c_str(), GetColor(255, 255, 0));

	if (Master::mpStopManager->GetStopFlag(STOP_FLAG_TYPE::UI_MODEL))
	{
		return;
	}
	Master::mpGameManager->GetMapManager()->DrawMinMap();
}

// 死亡
void PlayerProcess::PlayerDeath(CharacterBase* character)
{
	Master::mpGameManager->GetTargetManager()->Delete(character, TARGET_TYPE::PLAYER);
	Master::mpGameManager->GetSceneManager()->SetNextScene(SCENE::GAME_OVER);
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
	if (GetTargetChangeFlag())
	{
		TargetChange();
	}

	if (mnTargetNumber != -1)
	{
		SetTargetCamera(character);
	}
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
	TargetCameraProcess(character);

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
/*【ノーマル攻撃プレイヤーステート】*/
/*--------------------------*/
NormalAttackPlayerState::NormalAttackPlayerState()
: PlayerProcess()
{
	mStateNumber = (int)PLAYER_STATE::NORMAL_ATTACK_PLAYER_STATE;
}

// この状態に入った時の処理
void NormalAttackPlayerState::OnEnter(CharacterBase* character)
{
	character->StartAttck(ATTACK_METHOD_TYPE::NORMAL);
	character->SetAnimation(ANIMATION_TYPE::NORMAL_ATTACK_IN);
}

// この状態を出る時の処理
void NormalAttackPlayerState::OnExit(CharacterBase* character)
{
}

// ステート変更確認
int NormalAttackPlayerState::StateCheck(CharacterBase* character)
{
	if (!character->CheckAnimationType(ANIMATION_TYPE::ATTACK))
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
void NormalAttackPlayerState::Update(CharacterBase* character)
{
}

// 最終更新
void NormalAttackPlayerState::LastUpdate(CharacterBase* character)
{
}

// 描画
void NormalAttackPlayerState::Draw(CharacterBase* character)
{
	PlayerProcessDraw(character);
}

// 死亡
void NormalAttackPlayerState::Death(CharacterBase* character)
{
	PlayerDeath(character);
}

/*------------------------------------*/
/*【スペシャル攻撃プレイヤーステート】*/
/*------------------------------------*/
SpceialAttackPlayerState::SpceialAttackPlayerState()
: PlayerProcess()
{
	mStateNumber = (int)PLAYER_STATE::SPCEIAL_ATTACK_PLAYER_STATE;
}

// この状態に入った時の処理
void SpceialAttackPlayerState::OnEnter(CharacterBase* character)
{
	character->SetMoveDir(UtilCalc::VAngleToVec(character->GetAngle()));

	character->StartAttck(ATTACK_METHOD_TYPE::SPCEIAL);
	character->SetAnimation(ANIMATION_TYPE::SPCEIAL_ATTACK_IN);
}

// この状態を出る時の処理
void SpceialAttackPlayerState::OnExit(CharacterBase* character)
{
}

// ステート変更確認
int SpceialAttackPlayerState::StateCheck(CharacterBase* character)
{
	if (!character->CheckAnimationType(ANIMATION_TYPE::ATTACK))
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
void SpceialAttackPlayerState::Update(CharacterBase* character)
{
}

// 最終更新
void SpceialAttackPlayerState::LastUpdate(CharacterBase* character)
{
}

// 描画
void SpceialAttackPlayerState::Draw(CharacterBase* character)
{
	PlayerProcessDraw(character);
}

// 死亡
void SpceialAttackPlayerState::Death(CharacterBase* character)
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
	if (GetPlayerNormalAttackFlag())
	{
		return (int)PLAYER_STATE::NORMAL_ATTACK_PLAYER_STATE;
	}

	if (GetPlayerSpceialAttackFlag())
	{
		return (int)PLAYER_STATE::SPCEIAL_ATTACK_PLAYER_STATE;
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
	if (GetPlayerNormalAttackFlag())
	{
		return (int)PLAYER_STATE::NORMAL_ATTACK_PLAYER_STATE;
	}

	if (GetPlayerSpceialAttackFlag())
	{
		return (int)PLAYER_STATE::SPCEIAL_ATTACK_PLAYER_STATE;
	}

	if (!GetPlayerMoveFlag())
	{
		return (int)PLAYER_STATE::IDLE_PLAYER_STATE;
	}

	return mStateNumber;
}