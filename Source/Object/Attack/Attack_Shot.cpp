#include "Master.h"

#include "Attack_Shot.h"
#include "ObjectBases.h"
#include "TimeManager.h"
#include "UtilCalc.h"

Attack_Shot::Attack_Shot()
: AttackBase()
{
	mnAttackRecoilTime = 500;
}

Attack_Shot::~Attack_Shot()
{
}

// アタック初期化
void Attack_Shot::AttackInitilize()
{
	mnHiObjID.clear();

	mvPosition = mpAttackCharacter->GetPos();

	SetActiveFlag(true);
}

// アタック終了
void Attack_Shot::AttackFinalize()
{
}

// アタック更新
void Attack_Shot::AttackUpdate()
{
	mvPosition = VAdd(VScale(mvMoveDir, 10.0f), mvPosition);

	if (mnAttackTime <= Master::mpTimeManager->GetGameTime())
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
	DrawSphere3D(VAdd(mvPosition, VGet(0.0f, 50.0, 0.0f)), 100.0f, 32, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
}

// 当たり判定
void Attack_Shot::HitCheck(CollisionData& collisionData)
{
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

	if (UtilCalc::SphereCollision(collisionData.position, collisionData.size, mvPosition, 100.0f))
	{
		mnHiObjID.push_back(collisionData.objID);
		collisionData.collisionFlag = true;
	}
}