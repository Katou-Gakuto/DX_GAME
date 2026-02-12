#include <map>
#include <vector>

#include "CollisionData.h"

#include "Master.h"

#include "AttackManager.h"
#include "Attack_RobotSpceial.h"
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

// 攻撃作成
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
	}
}

// 攻撃情報設定
int AttackManager::SetAttackData(AttackData attackData)
{
	mstAttackDatas.push_back(attackData);

	return (int)mstAttackDatas.size() - 1;
}

// 攻撃開始
AttackBase* AttackManager::StartAttack(int attackDataNumber, ATTACK_METHOD_TYPE attackMethodType)
{
	if (mstAttackDatas.size() > attackDataNumber)
	{
		for (AttackBase* attack : mmAttacks[mstAttackDatas[attackDataNumber].attackType])
		{
			if (!attack->IsActiveFlag())
			{
				// 攻撃情報設定
				attack->SetAttackCharacter(mstAttackDatas[attackDataNumber].attackCharacter);
				attack->SetAttackTime(mstAttackDatas[attackDataNumber].attackTime + Master::mpTimeManager->GetGameTime()/*+ (17 * 300)*/);
				attack->SetMoveDir(UtilCalc::VAngleToVec(mstAttackDatas[attackDataNumber].attackCharacter->GetAngle()));
				attack->SetAttackPower(mstAttackDatas[attackDataNumber].attackPower);
				attack->SetAttackNumber(attackDataNumber);

				// モデル設定
				attack->SetModelController(mstAttackDatas[attackDataNumber].attackCharacter->GetAttackModelsController(attackMethodType));
				attack->SetAnimation(mstAttackDatas[attackDataNumber].attackCharacter->GetAttackAnimation(attackMethodType));
				attack->GetModelsController()->GameInit(mstAttackDatas[attackDataNumber].attackCharacter->GetPos(), mstAttackDatas[attackDataNumber].attackCharacter->GetAngle(), mstAttackDatas[attackDataNumber].attackCharacter->GetSize());
				attack->GetAnimation()->Initilize();

				// FIXME: なぜかヌルポインターが出た　作って試していた時に出たけど最近は出てない作ってない物がある想定で作られた結果だと予測される
				// 初期化
				attack->Initilize();
				attack->SetActiveFlag(true);

				// 反動時間を返す
				return attack;
			}
		}
	}

	return 0;
}

// 攻撃停止
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

// 削除設定
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