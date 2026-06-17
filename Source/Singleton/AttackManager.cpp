#include <map>
#include <vector>

#include "CollisionData.h"

#include "Master.h"

#include "AttackManager.h"
#include "Attack_RobotJump.h"
#include "Attack_RobotSpceial.h"
#include "Attack_Shot.h"
#include "GameManager.h"
#include "ObjectBase_Attack.h"
#include "ObjectManager.h"
#include "TimeManager.h"
#include "UtilCalc.h"

AttackManager::AttackManager()
{
	mmAttacks.clear();
	mstAllAttack.clear();
	mstAttackDatas.clear();
}

AttackManager::~AttackManager()
{
}

// çUåÇçÏê¨
void AttackManager::CreateAttack(ATTACK_TYPE attackType)
{
	switch (attackType)
	{
	case ATTACK_TYPE::SHOT:
	{
		int setSize = 10;
		mmAttacks[attackType].reserve(setSize);
		mstAllAttack.reserve(setSize);
		for (int i = 0; i < setSize; i++)
		{
			mstAllAttack.push_back(new Attack_Shot());
			mmAttacks[attackType].push_back(mstAllAttack.back());
		}
	}
		break;

	case ATTACK_TYPE::UNIQUE_ROBOT:
		mstAllAttack.push_back(new Attack_RobotSpceial());
		mmAttacks[attackType].push_back(mstAllAttack.back());
		break;

	case ATTACK_TYPE::JUMP_ATTACK:
		mstAllAttack.push_back(new Attack_RobotJump());
		mmAttacks[attackType].push_back(mstAllAttack.back());
		break;
	}
}

// çUåÇèÓïÒê›íË
int AttackManager::SetAttackData(AttackData attackData)
{
	mstAttackDatas.push_back(attackData);

	return (int)mstAttackDatas.size() - 1;
}

// çUåÇäJén
AttackBase* AttackManager::StartAttack(int attackDataNumber, ATTACK_METHOD_TYPE attackMethodType)
{
	if (mstAttackDatas.size() > attackDataNumber)
	{
		for (AttackBase* attack : mmAttacks[mstAttackDatas[attackDataNumber].attackType])
		{
			if (!attack->IsActiveFlag())
			{
				// çUåÇèÓïÒê›íË
				attack->SetAttackCharacter(mstAttackDatas[attackDataNumber].attackCharacter);
				attack->SetAttackTime(Master::mpTimeManager->GetGameElapsedTime() + mstAttackDatas[attackDataNumber].attackTime /*+ (17 * 300)*/);
				attack->SetMoveDir(UtilCalc::VAngleToVec(mstAttackDatas[attackDataNumber].attackCharacter->GetAngle()));
				attack->SetAttackPower(mstAttackDatas[attackDataNumber].attackPower);
				attack->SetAttackNumber(attackDataNumber);

				// ÉÇÉfÉãê›íË
				attack->SetModelController(mstAttackDatas[attackDataNumber].attackCharacter->GetAttackModelsController(attackMethodType));
				attack->SetAnimation(mstAttackDatas[attackDataNumber].attackCharacter->GetAttackAnimation(attackMethodType));
				attack->GetModelsController()->GameInit(mstAttackDatas[attackDataNumber].attackCharacter->GetPos(), mstAttackDatas[attackDataNumber].attackCharacter->GetAngle(), mstAttackDatas[attackDataNumber].attackCharacter->GetSize());
				attack->GetAnimation()->Initilize();

				// FIXME: Ç»Ç∫Ç©ÉkÉãÉ|ÉCÉìÉ^Å[Ç™èoÇΩÅ@çÏÇ¡ÇƒééÇµÇƒÇ¢ÇΩéûÇ…èoÇΩÇØÇ«ç≈ãﬂÇÕèoÇƒÇ»Ç¢çÏÇ¡ÇƒÇ»Ç¢ï®Ç™Ç†ÇÈëzíËÇ≈çÏÇÁÇÍÇΩåãâ ÇæÇ∆ó\ë™Ç≥ÇÍÇÈ
				// èâä˙âª
				attack->Initilize();
				attack->SetActiveFlag(true);

				// îΩìÆéûä‘Çï‘Ç∑
				return attack;
			}
		}
	}

	return 0;
}

// çUåÇí‚é~
void AttackManager::StopAttack(int stopAttackNumber)
{
	if (mstAttackDatas.size() > stopAttackNumber)
	{
		for (AttackBase* attack : mmAttacks[mstAttackDatas[stopAttackNumber].attackType])
		{
			if (attack->IsActiveFlag())
			{
				if (attack->GetAttackNumber() == stopAttackNumber)
				{
					attack->SetActiveFlag(false);
					return;
				}
			}
		}
	}
}

// çÌèúê›íË
void AttackManager::SetDelete()
{
	for (int i = 0; i < mstAllAttack.size(); i++)
	{
		mstAllAttack[i]->SetDeleteFlag(true);
	}

	mstAllAttack.clear();
	mmAttacks.clear();
	mstAttackDatas.clear();
}