#include "Master.h"

#include "Attack_RobotSpceial.h"
#include "ObjectBases.h"
#include "TimeManager.h"
#include "UtilCalc.h"

Attack_RobotSpceial::Attack_RobotSpceial()
: AttackBase()
{
	munPreCharacterHitTime.clear();
}

Attack_RobotSpceial::~Attack_RobotSpceial()
{
}

// アタック初期化
void Attack_RobotSpceial::AttackInitilize()
{
	mnHiObjID.clear();

	mvPosition = mpAttackCharacter->GetPos();

    mpAttackCharacter->GetStatus()->AddSpeed(mpAttackCharacter->GetStatus()->baseSpeed * 2);

	SetActiveFlag(true);
}

// アタックシーン最終初期化
void Attack_RobotSpceial::AttackSceneLastInitilize()
{
}

// アタック終了
void Attack_RobotSpceial::AttackFinalize()
{
}

// アタック更新
void Attack_RobotSpceial::AttackUpdate()
{
	mvPosition = mpAttackCharacter->GetPos();
    if (!mpAttackCharacter->CheckAnimationMoveType(ANIMATION_MOVE_TYPE::ATTACK_IN) &&
        !mpAttackCharacter->CheckAnimationMoveType(ANIMATION_MOVE_TYPE::ATTACK_OUT) &&
        mpAttackCharacter->CheckAnimationMoveType(ANIMATION_MOVE_TYPE::ATTACK))
    {
        mpAttackCharacter->SetMoveActionFlag(ACTION_FLAG::DASH);
    }

	if (mstAttackTime <= Master::mpTimeManager->GetGameElapsedTime())
	{
        mpAttackCharacter->GetStatus()->SubSpeed(mpAttackCharacter->GetStatus()->baseSpeed * 2);
		SetActiveFlag(false);
	}
}

// アタック最終更新
void Attack_RobotSpceial::AttackLastUpdate()
{
}

// アタック描画
void Attack_RobotSpceial::AttackDraw()
{
	//DrawSphere3D(VAdd(mvPosition, VGet(0.0f, 50.0, 0.0f)), 200.0f, 32, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
}

// 当たり判定
void Attack_RobotSpceial::HitCheck(CollisionData& collisionData)
{
	if (mpAttackCharacter->GetID() == collisionData.objID)
	{
		return;
	}

	for (int i = 0; i < mnHiObjID.size(); i++)
	{
		if (mnHiObjID[i] == collisionData.objID)
		{
			if (munPreCharacterHitTime[i] > (Master::mpTimeManager->GetGameElapsedTime().Full + 1000u/*一秒*/))
			{
				if (UtilCalc::SphereCollision(collisionData.position, collisionData.size, mvPosition, 200.0f))
				{
					munPreCharacterHitTime[i] = Master::mpTimeManager->GetGameElapsedTime();
					collisionData.collisionFlag = true;
				}
			}
			return;
		}
	}

	if (UtilCalc::SphereCollision(collisionData.position, collisionData.size, mvPosition, 200.0f))
	{
		mnHiObjID.push_back(collisionData.objID);
		munPreCharacterHitTime.push_back(Master::mpTimeManager->GetGameElapsedTime());
		collisionData.collisionFlag = true;
	}
}