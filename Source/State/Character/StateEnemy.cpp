#include "GameDataEnum.h"
#include "StateEnum.h"
#include "GameDatas.h"

#include "Master.h"

#include "DataManager.h"
#include "EnemyCommonProcessing.h"
#include "GameManager.h"
#include "StateEnemy.h"
#include "SceneManager.h"
#include "TargetManager.h"
#include "UtilCalc.h"
#include "UtilStateConditionFunction.h"

/*------------------*/
/*     【�E通、E    */
/*------------------*/

/*----------------------*/
/*【エネミー共通�E琁E��、E/
/*----------------------*/
EnemyProcess::EnemyProcess()
: EnemyCommonProcessing(STATE_ENEMY_TYPE::BATTLE_ENEMY)
, mpTargetManager(Master::mpGameManager->GetTargetManager())
{
}

// プレイヤーのスチE�Eタス設宁E
void EnemyProcess::SetPlayerStatus()
{
	// スチE�Eタス取征E
	STATUS playerStatus = Master::mpDataManager->GetPlayPlayerData().status;

	// スチE�Eタスを変更
	CharacterBase* playerObject = Master::mpGameManager->GetTargetManager()->GetTarget(TARGET_TYPE::PLAYER);
	STATUS playerObjectStatus = *playerObject->GetStatus();
	playerStatus.hp = playerObjectStatus.hp;

	// スチE�Eタスをデータに設宁E
	Master::mpDataManager->SetPlayPlayerStatus(playerStatus);
}

// 一定篁E��冁E��プレイヤーターゲチE��がいるなら「true、E
bool EnemyProcess::PlayerTargetCheck(CharacterBase* character, float range)
{
    return UtilCalc::SphereCollision(character->GetPos(), range, mpTargetManager->GetTarget(TARGET_TYPE::PLAYER).target->GetPos(), 180.0f);
}

// プレイヤー方向を向いて移動すめE
void EnemyProcess::PlayerTargetMove(CharacterBase* character)
{
	PlayerTargetAngle(character);

	character->SetFrontMove();
}

// プレイヤーターゲチE��の方に向く
void EnemyProcess::PlayerTargetAngle(CharacterBase* character)
{
	character->SetMoveDir(VSub(mpTargetManager->GetTarget(TARGET_TYPE::PLAYER).target->GetPos(), character->GetPos()));
}

// 死亡
void EnemyProcess::EnemyDeath(CharacterBase* character)
{
	Master::mpDataManager->AddAcquisitionExp(character->GetStatus()->exp);

	//if (mbBossFlag)
	{
		// TODO: ダンジョンリザルトに移勁E
		// HACK: ボスフラグでめE��てぁE��が死亡スチE�Eト作�EしてそこでめE��　ボスかどぁE��の判断もそこでめE��
		// // エネミー初期匁E
		// mpTargetManager->TargetInit(TARGET_TYPE::ENEMY);
		// Master::mpGameManager->GetSceneManager()->SetNextScene(Master::mpDataManager->GetPlayPlayerData().sceneData[DATA_SCENE::TOWN].sceneType);
		// Master::mpDataManager->DeleteEnemyData(Master::mpDataManager->GetPlayPlayerData().sceneData[DATA_SCENE::TOWN].sceneType);
	}
//	else
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
	else if (UtilCalc::VDiff(player->GetPos(), character->GetPos()) < 3000.0f)
	{
		return ENEMY_COMMAND_NUMBER::MEDIUM_RANGE;
	}
	// UNDONE: もとに戻ぁE
	//else if (UtilCalc::VDiff(player->GetPos(), character->GetPos()) < 3000.0f)
	else if (UtilCalc::VDiff(player->GetPos(), character->GetPos()) < 4000.0f)
	{
		return ENEMY_COMMAND_NUMBER::LONG_RANGE;
	}
	

	return ENEMY_COMMAND_NUMBER::NONE;
}

// 定型の次のスチE�Eトを取得すめE
STATE_TYPE_CHARACTER EnemyProcess::TemplateNextState(CharacterBase* character, STATE_TYPE_CHARACTER myState)
{
	switch (GetPlayerDistance_Command(character))
	{
	case ENEMY_COMMAND_NUMBER::SHORT_RANGE:
		return STATE_TYPE_CHARACTER::ATTACK_IN_ENEMY_STATE;
		
	case ENEMY_COMMAND_NUMBER::MEDIUM_RANGE:
		return STATE_TYPE_CHARACTER::MOVE_ENEMY_STATE;
		
	case ENEMY_COMMAND_NUMBER::LONG_RANGE:
		return STATE_TYPE_CHARACTER::IDLE_ENEMY_STATE;
	}


	return myState;
}


/*--------------------------*/
/*     【基本スチE�Eト、E    */
/*--------------------------*/

/*----------------------*/
/*【IdleエネミーチE�Eト、E/
/*----------------------*/
IdleEnemyState::IdleEnemyState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias)
: IStateCharacter(stateChangeCriterias, STATE_TYPE_CHARACTER::IDLE_ENEMY_STATE, STATE_TYPE_CHARACTER::IDLE_ENEMY_STATE)
, EnemyProcess()
{
}

// こ�E状態に入った時の処琁E
void IdleEnemyState::OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState)
{
	EnemyGraphDataInitialize(character);
}

// こ�E状態を出る時の処琁E
void IdleEnemyState::OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState)
{
}

// スチE�Eト変更確誁E
STATE_TYPE_CHARACTER IdleEnemyState::StateCheck(CharacterBase* character)
{
	return TemplateNextState(character, mStateNumber);
}

// 更新
void IdleEnemyState::Update(CharacterBase* character)
{
	// UNDONE: もとに戻ぁE
	character->SetPos(VGet(character->GetPos().x, 0.0f, character->GetPos().z));
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
/*【移動エネミースチE�Eト、E
/*----------*/
MoveEnemyState::MoveEnemyState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias)
: IStateCharacter(stateChangeCriterias, STATE_TYPE_CHARACTER::MOVE_ENEMY_STATE, STATE_TYPE_CHARACTER::MOVE_ENEMY_STATE)
, EnemyProcess()
{
}

// こ�E状態に入った時の処琁E
void MoveEnemyState::OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState)
{
}

// こ�E状態を出る時の処琁E
void MoveEnemyState::OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState)
{
}

// スチE�Eト変更確誁E
STATE_TYPE_CHARACTER MoveEnemyState::StateCheck(CharacterBase* character)
{
	return TemplateNextState(character, mStateNumber);
}

// 更新
void MoveEnemyState::Update(CharacterBase* character)
{
	PlayerTargetMove(character);
	// UNDONE: もとに戻ぁE
	character->SetPos(VGet(character->GetPos().x, 0.0f, character->GetPos().z));
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
/*【攻撁E�EりエネミースチE�Eト、E/
/*----------------------------*/
AttackInEnemyState::AttackInEnemyState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias)
: IStateCharacter(stateChangeCriterias, STATE_TYPE_CHARACTER::ATTACK_IN_ENEMY_STATE, STATE_TYPE_CHARACTER::ATTACK_IN_ENEMY_STATE)
, EnemyProcess()
, mbLeftMoveFlag(false)
, mstPreAttackTime(0)
{
}

// こ�E状態に入った時の処琁E
void AttackInEnemyState::OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState)
{
}

// こ�E状態を出る時の処琁E
void AttackInEnemyState::OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState)
{
}

// スチE�Eト変更確誁E
STATE_TYPE_CHARACTER AttackInEnemyState::StateCheck(CharacterBase* character)
{
	// 注愁E こ�E条件はState固有�Eメンバ変数(mstPreAttackTime, mbLeftMoveFlag)に依存してぁE��ため
	//       完�Eに外部関数化することはできません。State側で条件を保持する忁E��があります、E
	//       推測: 時間経過とHPに基づぁE��条件判宁E
	if (Master::mpTimeManager->GetGameElapsedTime() <= (mstPreAttackTime + (ESCAPE_TIME * 5)))
	{
		if (character->GetStatus()->hp < (int)((float)character->GetStatus()->maxHp * 0.5f))
		{
			return STATE_TYPE_CHARACTER::ESCAPE_ENEMY_STATE;
		}
		else
		{
			mbLeftMoveFlag = !mbLeftMoveFlag;
			if (mbLeftMoveFlag)
			{
				return STATE_TYPE_CHARACTER::LEFT_AVOID_ENEMY_STATE;
			}
			else
			{
				return STATE_TYPE_CHARACTER::RIGHT_AVOID_ENEMY_STATE;
			}
		}
	}

	// 外部関数を使用: プレイヤーの方角を向いてぁE��か判宁E
	if (UtilStateConditionFunction::IsFacingPlayer(character))
	{
		mstPreAttackTime = Master::mpTimeManager->GetGameElapsedTime();
		return STATE_TYPE_CHARACTER::ATTACK_ENEMY_STATE;
	}

	return TemplateNextState(character, mStateNumber);
}

// 更新
void AttackInEnemyState::Update(CharacterBase* character)
{
	PlayerTargetMove(character);
	// UNDONE: もとに戻ぁE
	character->SetPos(VGet(character->GetPos().x, 0.0f, character->GetPos().z));
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
/*【攻撁E��ネミースチE�Eト、E
/*----------*/
AttackEnemyState::AttackEnemyState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias)
: IStateCharacter(stateChangeCriterias, STATE_TYPE_CHARACTER::ATTACK_ENEMY_STATE, STATE_TYPE_CHARACTER::ATTACK_ENEMY_STATE)
, EnemyProcess()
{
}

// こ�E状態に入った時の処琁E
void AttackEnemyState::OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState)
{
	character->StartAttck(ATTACK_METHOD_TYPE::NORMAL);
	character->SetAnimation(ANIMATION_MOVE_TYPE::NORMAL_ATTACK_IN);
}

// こ�E状態を出る時の処琁E
void AttackEnemyState::OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState)
{
}

// スチE�Eト変更確誁E
STATE_TYPE_CHARACTER AttackEnemyState::StateCheck(CharacterBase* character)
{
	if (UtilStateConditionFunction::IsAttackAnimationFinished(character))
	{
		return TemplateNextState(character, mStateNumber);
	}

	return mStateNumber;
}

// 更新
void AttackEnemyState::Update(CharacterBase* character)
{
	// UNDONE: もとに戻ぁE
	character->SetPos(VGet(character->GetPos().x, 0.0f, character->GetPos().z));
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
/*【送E��エネミースチE�Eト、E/
/*------------------------*/
EscapeEnemyState::EscapeEnemyState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias)
: IStateCharacter(stateChangeCriterias, STATE_TYPE_CHARACTER::ESCAPE_ENEMY_STATE, STATE_TYPE_CHARACTER::ESCAPE_ENEMY_STATE)
, EnemyProcess()
, mstEscapeTime(0)
{
}

// こ�E状態に入った時の処琁E
void EscapeEnemyState::OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState)
{
	VECTOR setVec = VSub(mpTargetManager->GetTarget(TARGET_TYPE::PLAYER).target->GetPos(), character->GetPos());
	character->SetMoveDir(VGet(-setVec.x, -setVec.y, -setVec.z));

	mstEscapeTime = Master::mpTimeManager->GetGameElapsedTime() + ESCAPE_TIME;
}

// こ�E状態を出る時の処琁E
void EscapeEnemyState::OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState)
{
}

// スチE�Eト変更確誁E
STATE_TYPE_CHARACTER EscapeEnemyState::StateCheck(CharacterBase* character)
{
	// 注愁E こ�E条件はState固有�Eメンバ変数(mstEscapeTime)に依存してぁE��ため
	//       完�Eに外部関数化することはできません。State側で条件を保持する忁E��があります、E
	//       推測: 送E��時間経過に基づぁE��条件判宁E
	if (Master::mpTimeManager->GetGameElapsedTime() > mstEscapeTime)
	{
		return TemplateNextState(character, mStateNumber);
	}

	return mStateNumber;
}

// 更新
void EscapeEnemyState::Update(CharacterBase* character)
{
	character->SetFrontMove();
	// UNDONE: もとに戻ぁE
	character->SetPos(VGet(character->GetPos().x, 0.0f, character->GetPos().z));
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
/*     【派生スチE�Eト、E    */
/*--------------------------*/

/*--------------------------*/
/*【左回避エネミースチE�Eト、E/
/*--------------------------*/
LeftAvoidEnemyState::LeftAvoidEnemyState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias)
: EscapeEnemyState(stateChangeCriterias)
{
	mStateNumber = STATE_TYPE_CHARACTER::LEFT_AVOID_ENEMY_STATE;
}

// こ�E状態に入った時の処琁E
void LeftAvoidEnemyState::OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState)
{
	PlayerTargetAngle(character);
	mstEscapeTime = Master::mpTimeManager->GetGameElapsedTime() + ESCAPE_TIME;
}

// 更新
void LeftAvoidEnemyState::Update(CharacterBase* character)
{
	character->SetFrontMove();
	character->SetLeftMove();
	// UNDONE: もとに戻ぁE
	character->SetPos(VGet(character->GetPos().x, 0.0f, character->GetPos().z));
}

/*--------------------------*/
/*【右回避エネミースチE�Eト、E/
/*--------------------------*/
RightAvoidEnemyState::RightAvoidEnemyState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias)
: EscapeEnemyState(stateChangeCriterias)
{
	mStateNumber = STATE_TYPE_CHARACTER::RIGHT_AVOID_ENEMY_STATE;
}

// こ�E状態に入った時の処琁E
void RightAvoidEnemyState::OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState)
{
	PlayerTargetAngle(character);
	mstEscapeTime = Master::mpTimeManager->GetGameElapsedTime() + ESCAPE_TIME;
}

// 更新
void RightAvoidEnemyState::Update(CharacterBase* character)
{
	character->SetFrontMove();
	character->SetRightMove();
	// UNDONE: もとに戻ぁE
	character->SetPos(VGet(character->GetPos().x, 0.0f, character->GetPos().z));
}
