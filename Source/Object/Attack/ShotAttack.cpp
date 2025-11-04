#include "Master.h"

#include "ObjectBases.h"
#include "ShotAttack.h"
#include "TimeManager.h"

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
	mpHiCharacter.clear();

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
	mvPosition = VAdd(VGet(1.0f, 0.0f, 1.0f), mvPosition);

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