#include "Master.h"

#include "ObjectBases.h"
#include "ShotAttack.h"
#include "TimeManager.h"
#include "UtilCalc.h"

ShotAttack::ShotAttack()
: AttackBase()
{
	mnAttackRecoilTime = 500;
}

ShotAttack::~ShotAttack()
{
}

// アタック初期化
void ShotAttack::AttackInitilize()
{
	mnHiObjID.clear();

	mvPosition = mpAttackCharacter->GetPos();

	SetActiveFlag(true);
}

// アタック終了
void ShotAttack::AttackFinalize()
{
}

// アタック更新
void ShotAttack::AttackUpdate()
{
	mvPosition = VAdd(VScale(mvMoveDir, 10.0f), mvPosition);

	if (mnAttackTime <= Master::mpTimeManager->GetGameTime())
	{
		SetActiveFlag(false);
	}
}

// アタック最終更新
void ShotAttack::AttackLastUpdate()
{
}

// アタック描画
void ShotAttack::AttackDraw()
{
	DrawSphere3D(VAdd(mvPosition, VGet(0.0f, 50.0, 0.0f)), 100.0f, 32, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
}

// 当たり判定
void ShotAttack::HitCheck(CollisionData& collisionData)
{
	if (mpAttackCharacter->GetID() == collisionData.objID)
	{
		return;
	}
	for (int i = 0; mnHiObjID.size(); i++)
	{
		if (mnHiObjID[i] == collisionData.objID)
		{
			return;
		}
	}

	if (UtilCalc::SphereCollision(collisionData.position, collisionData.size, mvPosition, 100.0f))
	{
		mnHiObjID.push_back(collisionData.objID);
		collisionData.collisionFlag = true;
	}
}