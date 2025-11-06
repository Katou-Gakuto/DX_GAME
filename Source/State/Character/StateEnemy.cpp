#include "Master.h"

#include "GameManager.h"
#include "StateEnemy.h"
#include "SceneManager.h"
#include "TargetManager.h"

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
	return false;
}

// プレイヤー方向を向いて移動する
void EnemyProcess::PlayerTargetMove(CharacterBase* character)
{
}

// プレイヤーターゲットに向かって攻撃
void EnemyProcess::PlayerTargetAttack(CharacterBase* character)
{
}

// 死亡
void EnemyProcess::EnemyDeath(CharacterBase* character)
{
	mpTargetManager->Delete(character, TARGET_NUMBER::ENEMY);
	if (mpTargetManager->GetTargets(TARGET_NUMBER::ENEMY).size() <= 0)
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