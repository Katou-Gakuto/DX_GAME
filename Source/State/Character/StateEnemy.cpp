#include "Master.h"

#include "DataManager.h"
#include "GameManager.h"
#include "StateEnemy.h"
#include "SceneManager.h"
#include "TargetManager.h"
#include "UtilCalc.h"

/*------------------*/
/*     【共通】     */
/*------------------*/

/*----------------------*/
/*【エネミー共通処理用】*/
/*----------------------*/
EnemyProcess::EnemyProcess()
: mpTargetManager(Master::mpGameManager->GetTargetManager())
{
}

// 一定範囲内にプレイヤーターゲットがいるなら「true」
bool EnemyProcess::PlayerTargetCheck(CharacterBase* character, float range)
{
    return UtilCalc::SphereCollision(character->GetPos(), range, mpTargetManager->GetTarget(TARGET_TYPE::PLAYER).target->GetPos(), 180.0f);
}

// プレイヤー方向を向いて移動する
void EnemyProcess::PlayerTargetMove(CharacterBase* character)
{
}

// プレイヤーターゲットの方に向く
void EnemyProcess::PlayerTargetAngle(CharacterBase* character)
{
}

// 死亡
void EnemyProcess::EnemyDeath(CharacterBase* character)
{
	mpTargetManager->Delete(character, TARGET_TYPE::ENEMY);
	if (mpTargetManager->GetTargets(TARGET_TYPE::ENEMY).size() <= 0)
	{
		Master::mpGameManager->GetSceneManager()->SetNextScene(SCENE::BATTLR_RESULT);
	}
}


/*--------------------------*/
/*     【基本ステート】     */
/*--------------------------*/

/*----------------------*/
/*【Idleエネミーテート】*/
/*----------------------*/
IdleEnemyState::IdleEnemyState()
{
	mStateNumber = (int)ENEMY_STATE::IDLE_ENEMY_STATE;
}

// この状態に入った時の処理
void IdleEnemyState::OnEnter(CharacterBase* character)
{
}

// この状態を出る時の処理
void IdleEnemyState::OnExit(CharacterBase* character)
{
}

// ステート変更確認
int IdleEnemyState::StateCheck(CharacterBase* character)
{
	return mStateNumber;
}

// 更新
void IdleEnemyState::Update(CharacterBase* character)
{
}

// 最終更新
void IdleEnemyState::LastUpdate(CharacterBase* character)
{
}

// 描画
void IdleEnemyState::Draw(CharacterBase* character)
{
}

// 死亡
void IdleEnemyState::Death(CharacterBase* character)
{
	EnemyDeath(character);
}

/*----------*/
/*【移動エネミーステート】
/*----------*/
MoveEnemyState::MoveEnemyState()
{
	mStateNumber = (int)ENEMY_STATE::MOVE_ENEMY_STATE;
}

// この状態に入った時の処理
void MoveEnemyState::OnEnter(CharacterBase* character)
{
}

// この状態を出る時の処理
void MoveEnemyState::OnExit(CharacterBase* character)
{
}

// ステート変更確認
int MoveEnemyState::StateCheck(CharacterBase* character)
{
	return mStateNumber;
}

// 更新
void MoveEnemyState::Update(CharacterBase* character)
{
	PlayerTargetMove(character);
}

// 最終更新
void MoveEnemyState::LastUpdate(CharacterBase* character)
{
}

// 描画
void MoveEnemyState::Draw(CharacterBase* character)
{
}

// 死亡
void MoveEnemyState::Death(CharacterBase* character)
{
	EnemyDeath(character);
}

/*----------*/
/*【攻撃エネミーステート】
/*----------*/
AttackEnemyState::AttackEnemyState()
{
	mStateNumber = (int)ENEMY_STATE::ATTACK_ENEMY_STATE;
}

// この状態に入った時の処理
void AttackEnemyState::OnEnter(CharacterBase* character)
{
	character->StartAttck(ATTACK_METHOD_TYPE::NORMAL);
	character->SetAnimation(ANIMATION_TYPE::NORMAL_ATTACK_IN);
}

// この状態を出る時の処理
void AttackEnemyState::OnExit(CharacterBase* character)
{
}

// ステート変更確認
int AttackEnemyState::StateCheck(CharacterBase* character)
{
	if (!character->CheckAnimationType(ANIMATION_TYPE::ATTACK))
	{
		// if (GetPlayerMoveFlag())
		// {
		// 	return (int)ENEMY_STATE::MOVE_ENEMY_STATE;
		// }

		return (int)ENEMY_STATE::IDLE_ENEMY_STATE;
	}

	return mStateNumber;
}

// 更新
void AttackEnemyState::Update(CharacterBase* character)
{
}

// 最終更新
void AttackEnemyState::LastUpdate(CharacterBase* character)
{
}

// 描画
void AttackEnemyState::Draw(CharacterBase* character)
{
}

// 死亡
void AttackEnemyState::Death(CharacterBase* character)
{
	EnemyDeath(character);
}

/*--------------------------*/
/*     【派生ステート】     */
/*--------------------------*/

/*----------------------------*/
/*【Idleボスエネミーステート】*/
/*----------------------------*/

IdleBossEnemyState::IdleBossEnemyState()
{
	mStateNumber = (int)ENEMY_STATE::IDLE_ENEMY_STATE;
}

// 死亡処理
void IdleBossEnemyState::EnemyDeath(CharacterBase* character)
{
	// エネミー初期化
	mpTargetManager->TargetInit(TARGET_TYPE::ENEMY);
	Master::mpGameManager->GetSceneManager()->SetNextScene(Master::mpDataManager->GetPlayPlayerData().townType);
}