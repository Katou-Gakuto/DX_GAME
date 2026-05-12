#include "CameraData.h"
#include "TimeData.h"

#include "Master.h"

#include "Attack_RobotJump.h"
#include "CameraManager.h"
#include "GameManager.h"
#include "ObjectBases.h"
#include "TimeManager.h"
#include "UtilCalc.h"

Attack_RobotJump::Attack_RobotJump()
: AttackBase()
{
}

Attack_RobotJump::~Attack_RobotJump()
{
}

// アタック初期化
void Attack_RobotJump::AttackInitilize()
{
	mnHiObjID.clear();

	mvPosition = mpAttackCharacter->GetPos();

    mpAttackCharacter->GetStatus()->AddSpeed(mpAttackCharacter->GetStatus()->baseSpeed * 2);

	SetActiveFlag(true);
}

// アタックシーン最終初期化
void Attack_RobotJump::AttackSceneLastInitilize()
{
}

// アタック終了
void Attack_RobotJump::AttackFinalize()
{
}

// アタック更新
void Attack_RobotJump::AttackUpdate()
{
	mvPosition = mpAttackCharacter->GetPos();

	if (mstAttackTime <= Master::mpTimeManager->GetGameElapsedTime())
	{
        mpAttackCharacter->GetStatus()->SubSpeed(mpAttackCharacter->GetStatus()->baseSpeed * 2);
        mpAttackCharacter->SetPos(VGet(mvPosition.x, 0.0f, mvPosition.z));
		SetActiveFlag(false);
	}
}

// アタック最終更新
void Attack_RobotJump::AttackLastUpdate()
{
	mvPosition = mpAttackCharacter->GetPos();
	if (mstAttackTime <= Master::mpTimeManager->GetGameElapsedTime())
	{
        mpAttackCharacter->SetPos(VGet(mvPosition.x, 0.0f, mvPosition.z));
	}
}

// アタック描画
void Attack_RobotJump::AttackDraw()
{
	//DrawSphere3D(VAdd(mvPosition, VGet(0.0f, 50.0, 0.0f)), 200.0f, 32, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
}

// 当たり判定
void Attack_RobotJump::HitCheck(CollisionData& collisionData)
{
	if (!mpAttackCharacter->CheckAnimationType(ANIMATION_TYPE::ATTACK_OUT))
	{
		return;
	}

	if (mpAttackCharacter->GetID() == collisionData.objID)
	{
		return;
	}

	for (int i = 0; i < mnHiObjID.size(); i++)
	{
		if (mnHiObjID[i] == collisionData.objID)
		{
			return;
		}
	}

	if (UtilCalc::SphereCollision(collisionData.position, collisionData.size, mvPosition, 200.0f * 1.5f))
	{
		mnHiObjID.push_back(collisionData.objID);
		collisionData.collisionFlag = true;
	}
}