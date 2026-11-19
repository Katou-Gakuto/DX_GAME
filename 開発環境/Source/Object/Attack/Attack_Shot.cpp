#include "Master.h"

#include "Attack_Shot.h"
#include "ObjectBases.h"
#include "TimeManager.h"
#include "UtilCalc.h"

#include "SoundManager.h"

Attack_Shot::Attack_Shot()
: AttackBase()
, mnAttackStartTime(0)
{
	mvAttackSize = VGet(3000.0f, 1.0f, 3000.0f);
}

Attack_Shot::~Attack_Shot()
{
}

// アタック初期化
void Attack_Shot::AttackInitilize()
{
	mnHiObjID.clear();

	mvPosition = mpAttackCharacter->GetPos();

	mnAttackStartTime = Master::mpTimeManager->GetGameElapsedTime().Full + ATTACK_START_TIME;

	SetActiveFlag(true);

	
	Master::mpSoundManager->Set3DSound(SOUND_3D::BEAM_CANNON_CHARGE, mvPosition);
}

// アタックシーン最終初期化
void Attack_Shot::AttackSceneLastInitilize()
{
}

// アタック終了
void Attack_Shot::AttackFinalize()
{
}

// アタック更新
void Attack_Shot::AttackUpdate()
{
	//mvPosition = VAdd(VScale(mvMoveDir, 10.0f), mvPosition);

	if (mstAttackTime <= Master::mpTimeManager->GetGameElapsedTime())
	{
		SetActiveFlag(false);
	}
}

// アタック最終更新
void Attack_Shot::AttackLastUpdate()
{
}

// アタック描画
void Attack_Shot::AttackDraw()
{
}

// 当たり判定
void Attack_Shot::HitCheck(CollisionData& collisionData)
{
	if (Master::mpTimeManager->GetGameElapsedTime() <= mnAttackStartTime)
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

	if (HitCheck_Sphere_Capsule(collisionData.position, collisionData.size, mvPosition, VAdd(mvPosition, VGet(mvMoveDir.x * mvAttackSize.x, mvMoveDir.y * mvAttackSize.y, mvMoveDir.z * mvAttackSize.z)), 100.0f))
	{
	 	mnHiObjID.push_back(collisionData.objID);
		collisionData.collisionFlag = true;
	}
}