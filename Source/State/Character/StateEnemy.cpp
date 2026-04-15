#include "GameDataEnum.h"
#include "GameDatas.h"

#include "Master.h"

#include "DataManager.h"
#include "EnemyCommonProcessing.h"
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
EnemyProcess::EnemyProcess(bool bossFlag)
: EnemyCommonProcessing(STATE_ENEMY_TYPE::BATTLE_ENEMY)
, mpTargetManager(Master::mpGameManager->GetTargetManager())
, mbBossFlag(bossFlag)
{
}

// プレイヤーのステータス設定
void EnemyProcess::SetPlayerStatus()
{
	// ステータス取得
	STATUS playerStatus = Master::mpDataManager->GetPlayPlayerData().status;

	// ステータスを変更
	CharacterBase* playerObject = Master::mpGameManager->GetTargetManager()->GetTarget(TARGET_TYPE::PLAYER);
	STATUS playerObjectStatus = *playerObject->GetStatus();
	playerStatus.hp = playerObjectStatus.hp;

	// ステータスをデータに設定
	Master::mpDataManager->SetPlayPlayerStatus(playerStatus);
}

// 一定範囲内にプレイヤーターゲットがいるなら「true」
bool EnemyProcess::PlayerTargetCheck(CharacterBase* character, float range)
{
    return UtilCalc::SphereCollision(character->GetPos(), range, mpTargetManager->GetTarget(TARGET_TYPE::PLAYER).target->GetPos(), 180.0f);
}

// プレイヤー方向を向いて移動する
void EnemyProcess::PlayerTargetMove(CharacterBase* character)
{
	PlayerTargetAngle(character);

	character->SetFrontMove();
}

// プレイヤーターゲットの方に向く
void EnemyProcess::PlayerTargetAngle(CharacterBase* character)
{
	character->SetMoveDir(VSub(mpTargetManager->GetTarget(TARGET_TYPE::PLAYER).target->GetPos(), character->GetPos()));
}

// 死亡
void EnemyProcess::EnemyDeath(CharacterBase* character)
{
	Master::mpDataManager->AddAcquisitionExp(character->GetStatus()->exp);

	if (mbBossFlag)
	{
		// TODO: ダンジョンリザルトに移動
		// エネミー初期化
		mpTargetManager->TargetInit(TARGET_TYPE::ENEMY);
		Master::mpGameManager->GetSceneManager()->SetNextScene(Master::mpDataManager->GetPlayPlayerData().sceneData[DATA_SCENE::TOWN].sceneType);
		Master::mpDataManager->DeleteEnemyData(Master::mpDataManager->GetPlayPlayerData().sceneData[DATA_SCENE::TOWN].sceneType);
	}
	else
	{
		mpTargetManager->Delete(character, TARGET_TYPE::ENEMY);
		if (mpTargetManager->GetTargets(TARGET_TYPE::ENEMY).size() <= 0)
		{
			SetPlayerStatus();
			Master::mpGameManager->GetSceneManager()->SetNextScene(SCENE::BATTLR_RESULT);
		}
	}
}

// プレイヤーの位置によって数字を返す
ENEMY_COMMAND_NUMBER EnemyProcess::GetPlayerDistance_Command(CharacterBase* character)
{
	CharacterBase* player = mpTargetManager->GetTarget(TARGET_TYPE::PLAYER);

	if (UtilCalc::VDiff(player->GetPos(), character->GetPos()) < 1000.0f)
	{
		return ENEMY_COMMAND_NUMBER::SHORT_RANGE;
	}
	else if (UtilCalc::VDiff(player->GetPos(), character->GetPos()) < 2000.0f)
	{
		return ENEMY_COMMAND_NUMBER::MEDIUM_RANGE;
	}
	else if (UtilCalc::VDiff(player->GetPos(), character->GetPos()) < 3000.0f)
	{
		return ENEMY_COMMAND_NUMBER::LONG_RANGE;
	}
	

	return ENEMY_COMMAND_NUMBER::NONE;
}

// 定型の次のステートを取得する
int EnemyProcess::TemplateNextState(CharacterBase* character, int myState)
{
	switch (GetPlayerDistance_Command(character))
	{
	case ENEMY_COMMAND_NUMBER::SHORT_RANGE:
		return (int)ENEMY_STATE::ATTACK_IN_ENEMY_STATE;
		
	case ENEMY_COMMAND_NUMBER::MEDIUM_RANGE:
		return (int)ENEMY_STATE::MOVE_ENEMY_STATE;
		
	case ENEMY_COMMAND_NUMBER::LONG_RANGE:
		return (int)ENEMY_STATE::IDLE_ENEMY_STATE;
	}


	return myState;
}


/*--------------------------*/
/*     【基本ステート】     */
/*--------------------------*/

/*----------------------*/
/*【Idleエネミーテート】*/
/*----------------------*/
IdleEnemyState::IdleEnemyState(bool bossFlag)
: IStateCharacter()
, EnemyProcess(bossFlag)
{
	mStateNumber = (int)ENEMY_STATE::IDLE_ENEMY_STATE;
}

// この状態に入った時の処理
void IdleEnemyState::OnEnter(CharacterBase* character)
{
	EnemyGraphDataInitialize(character);
}

// この状態を出る時の処理
void IdleEnemyState::OnExit(CharacterBase* character)
{
}

// ステート変更確認
int IdleEnemyState::StateCheck(CharacterBase* character)
{
	return TemplateNextState(character, mStateNumber);
}

// 更新
void IdleEnemyState::Update(CharacterBase* character)
{
}

// 最終更新
void IdleEnemyState::LastUpdate(CharacterBase* character)
{
	HpDrawInfoSetup(character);
}

// 描画
void IdleEnemyState::Draw(CharacterBase* character)
{
    EnemyDataDraw(character);
}

// 死亡
void IdleEnemyState::Death(CharacterBase* character)
{
	EnemyDeath(character);
}

/*----------*/
/*【移動エネミーステート】
/*----------*/
MoveEnemyState::MoveEnemyState(bool bossFlag)
: IStateCharacter()
, EnemyProcess(bossFlag)
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
	return TemplateNextState(character, mStateNumber);
}

// 更新
void MoveEnemyState::Update(CharacterBase* character)
{
	PlayerTargetMove(character);
}

// 最終更新
void MoveEnemyState::LastUpdate(CharacterBase* character)
{
	HpDrawInfoSetup(character);
}

// 描画
void MoveEnemyState::Draw(CharacterBase* character)
{
    EnemyDataDraw(character);
}

// 死亡
void MoveEnemyState::Death(CharacterBase* character)
{
	EnemyDeath(character);
}

/*----------------------------*/
/*【攻撃入りエネミーステート】*/
/*----------------------------*/
AttackInEnemyState::AttackInEnemyState(bool bossFlag)
: IStateCharacter()
, EnemyProcess(bossFlag)
, mbLeftMoveFlag(false)
, mnPreAttackTime(0)
{
	mStateNumber = (int)ENEMY_STATE::ATTACK_IN_ENEMY_STATE;
}

// この状態に入った時の処理
void AttackInEnemyState::OnEnter(CharacterBase* character)
{
}

// この状態を出る時の処理
void AttackInEnemyState::OnExit(CharacterBase* character)
{
}

// ステート変更確認
int AttackInEnemyState::StateCheck(CharacterBase* character)
{
	if (Master::mpTimeManager->GetGameTime() <= (mnPreAttackTime + (ESCAPE_TIME * 5)))
	{
		if (character->GetStatus()->hp < (int)((float)character->GetStatus()->maxHp * 0.5f))
		{
			return (int)ENEMY_STATE::ESCAPE_ENEMY_STATE;
		}
		else
		{
			mbLeftMoveFlag = !mbLeftMoveFlag;
			if (mbLeftMoveFlag)
			{
				return (int)ENEMY_STATE::LEFT_AVOID_ENEMY_STATE;
			}
			else
			{
				return (int)ENEMY_STATE::RIGHT_AVOID_ENEMY_STATE;
			}
		}
	}

	if (UtilCalc::AngleDiff(UtilCalc::VVecToAngle(VSub(mpTargetManager->GetTarget(TARGET_TYPE::PLAYER).target->GetPos(), character->GetPos())). y, character->GetAngle().y) < 0.1f)
	{
		mnPreAttackTime = Master::mpTimeManager->GetGameTime();
		return (int)ENEMY_STATE::ATTACK_ENEMY_STATE;
	}

	return TemplateNextState(character, mStateNumber);
}

// 更新
void AttackInEnemyState::Update(CharacterBase* character)
{
	PlayerTargetMove(character);
}

// 最終更新
void AttackInEnemyState::LastUpdate(CharacterBase* character)
{
	HpDrawInfoSetup(character);
}

// 描画
void AttackInEnemyState::Draw(CharacterBase* character)
{
    EnemyDataDraw(character);
}

// 死亡
void AttackInEnemyState::Death(CharacterBase* character)
{
	EnemyDeath(character);
}

/*----------*/
/*【攻撃エネミーステート】
/*----------*/
AttackEnemyState::AttackEnemyState(bool bossFlag)
: IStateCharacter()
, EnemyProcess(bossFlag)
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
		return TemplateNextState(character, mStateNumber);
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
	HpDrawInfoSetup(character);
}

// 描画
void AttackEnemyState::Draw(CharacterBase* character)
{
    EnemyDataDraw(character);
}

// 死亡
void AttackEnemyState::Death(CharacterBase* character)
{
	EnemyDeath(character);
}

/*------------------------*/
/*【逃げエネミーステート】*/
/*------------------------*/
EscapeEnemyState::EscapeEnemyState(bool bossFlag)
: IStateCharacter()
, EnemyProcess(bossFlag)
, mnEscapeTime(0)
{
	mStateNumber = (int)ENEMY_STATE::ESCAPE_ENEMY_STATE;
}

// この状態に入った時の処理
void EscapeEnemyState::OnEnter(CharacterBase* character)
{
	VECTOR setVec = VSub(mpTargetManager->GetTarget(TARGET_TYPE::PLAYER).target->GetPos(), character->GetPos());
	character->SetMoveDir(VGet(-setVec.x, -setVec.y, -setVec.z));

	mnEscapeTime = Master::mpTimeManager->GetGameTime() + ESCAPE_TIME;
}

// この状態を出る時の処理
void EscapeEnemyState::OnExit(CharacterBase* character)
{
}

// ステート変更確認
int EscapeEnemyState::StateCheck(CharacterBase* character)
{
	if (Master::mpTimeManager->GetGameTime() > mnEscapeTime)
	{
		return TemplateNextState(character, mStateNumber);
	}

	return mStateNumber;
}

// 更新
void EscapeEnemyState::Update(CharacterBase* character)
{
	character->SetFrontMove();
}

// 最終更新
void EscapeEnemyState::LastUpdate(CharacterBase* character)
{
	HpDrawInfoSetup(character);
}

// 描画
void EscapeEnemyState::Draw(CharacterBase* character)
{
    EnemyDataDraw(character);
}

// 死亡
void EscapeEnemyState::Death(CharacterBase* character)
{
	EnemyDeath(character);
}

/*--------------------------*/
/*     【派生ステート】     */
/*--------------------------*/

/*--------------------------*/
/*【左回避エネミーステート】*/
/*--------------------------*/
LeftAvoidEnemyState::LeftAvoidEnemyState(bool bossFlag)
: EscapeEnemyState(bossFlag)
{
	mStateNumber = (int)ENEMY_STATE::LEFT_AVOID_ENEMY_STATE;
}

// この状態に入った時の処理
void LeftAvoidEnemyState::OnEnter(CharacterBase* character)
{
	PlayerTargetAngle(character);
	mnEscapeTime = Master::mpTimeManager->GetGameTime() + ESCAPE_TIME;
}

// 更新
void LeftAvoidEnemyState::Update(CharacterBase* character)
{
	character->SetFrontMove();
	character->SetLeftMove();
}

/*--------------------------*/
/*【右回避エネミーステート】*/
/*--------------------------*/
RightAvoidEnemyState::RightAvoidEnemyState(bool bossFlag)
: EscapeEnemyState(bossFlag)
{
	mStateNumber = (int)ENEMY_STATE::RIGHT_AVOID_ENEMY_STATE;
}

// この状態に入った時の処理
void RightAvoidEnemyState::OnEnter(CharacterBase* character)
{
	PlayerTargetAngle(character);
	mnEscapeTime = Master::mpTimeManager->GetGameTime() + ESCAPE_TIME;
}

// 更新
void RightAvoidEnemyState::Update(CharacterBase* character)
{
	character->SetFrontMove();
	character->SetRightMove();
}