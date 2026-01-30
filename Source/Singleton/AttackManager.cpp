#include <map>
#include <vector>

#include "CollisionData.h"

#include "Master.h"

#include "AttackManager.h"
#include "Attack_Shot.h"
#include "GameManager.h"
#include "ObjectBases.h"
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

// UŒ‚ì¬
void AttackManager::CreateAttack(ATTACK_TYPE attackType)
{
	switch (attackType)
	{
	case ATTACK_TYPE::SHOT:
		const int setSize = 10;
		mmAttacks[attackType].reserve(setSize);
		mstAllAttack.reserve(setSize);
		for (int i = 0; i < setSize; i++)
		{
			mstAllAttack.push_back(new Attack_Shot());
			mmAttacks[attackType].push_back(mstAllAttack.back());
		}
		break;
	}
}

// UŒ‚î•ñİ’è
int AttackManager::SetAttackData(AttackData attackData)
{
	mstAttackDatas.push_back(attackData);

	return (int)mstAttackDatas.size() - 1;
}

// UŒ‚ŠJn
AttackBase* AttackManager::StartAttack(int attackDataNumber, ATTACK_METHOD_TYPE attackMethodType)
{
	if (mstAttackDatas.size() > attackDataNumber)
	{
		for (AttackBase* attack : mmAttacks[mstAttackDatas[attackDataNumber].attackType])
		{
			if (!attack->IsActiveFlag())
			{
				// UŒ‚î•ñİ’è
				attack->SetAttackCharacter(mstAttackDatas[attackDataNumber].attackCharacter);
				attack->SetAttackTime(mstAttackDatas[attackDataNumber].attackTime + Master::mpTimeManager->GetGameTime() + (17 * 300));
				attack->SetMoveDir(UtilCalc::VAngleToVec(mstAttackDatas[attackDataNumber].attackCharacter->GetAngle()));
				attack->SetAttackPower(mstAttackDatas[attackDataNumber].attackPower);
				attack->SetAttackNumber(attackDataNumber);

				// ƒ‚ƒfƒ‹İ’è
				attack->SetModelController(mstAttackDatas[attackDataNumber].attackCharacter->GetAttackModelsController(attackMethodType));
				attack->SetAnimation(mstAttackDatas[attackDataNumber].attackCharacter->GetAttackAnimation(attackMethodType));
				attack->GetModelsController()->GameInit(mstAttackDatas[attackDataNumber].attackCharacter->GetPos(), mstAttackDatas[attackDataNumber].attackCharacter->GetAngle(), mstAttackDatas[attackDataNumber].attackCharacter->GetSize());
				attack->GetAnimation()->Initilize();

				// FIXME: ‚È‚º‚©ƒkƒ‹ƒ|ƒCƒ“ƒ^[‚ªo‚½@ì‚Á‚Ä‚µ‚Ä‚¢‚½‚Éo‚½‚¯‚ÇÅ‹ß‚Ío‚Ä‚È‚¢ì‚Á‚Ä‚È‚¢•¨‚ª‚ ‚é‘z’è‚Åì‚ç‚ê‚½Œ‹‰Ê‚¾‚Æ—\‘ª‚³‚ê‚é
				// ‰Šú‰»
				attack->Initilize();
				attack->SetActiveFlag(true);

				// ”½“®ŠÔ‚ğ•Ô‚·
				return attack;
			}
		}
	}

	return 0;
}

// UŒ‚’â~
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

// íœİ’è
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