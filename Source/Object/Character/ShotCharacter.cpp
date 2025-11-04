#include "CollisionData.h"

#include "DxLib.h"

#include "Master.h"

#include "AttackManager.h"
#include "GameManager.h"
#include "ObjectBases.h"
#include "ShotCharacter.h"

ShotCharacter::ShotCharacter(bool nextSceneDeleteFlag, STATUS status, SHOT_TYPE shotType)
: CharacterBase(nextSceneDeleteFlag, status)
{
	AttackData setData;
	setData.attackType = ATTACK_TYPE::SHOT;
	setData.attackCharacter = this;
	setData.attackTime = 5000;

	switch (shotType)
	{
	case SHOT_TYPE::DEFAULT:
		Master::mpGameManager->GetAttackManager()->CreateAttack(setData.attackType);
		mnAttackDataNumber = Master::mpGameManager->GetAttackManager()->SetAttackData(setData);
		break;
	}
}

ShotCharacter::~ShotCharacter()
{
}

// 攻撃リセット
void ShotCharacter::StopAttack()
{
}

// キャラクター初期化
void ShotCharacter::CharacterInitilize()
{
}

// キャラクター終了
void ShotCharacter::CharacterFinalize()
{
}

// キャラクター更新
void ShotCharacter::CharacterUpdate()
{
}

// キャラクター最終更新
void ShotCharacter::CharacterLastUpdate()
{
}

// キャラクター描画
void ShotCharacter::CharacterDraw()
{
	DrawSphere3D(VAdd(mvPosition, VGet(0.0f, 90.0, 0.0f)), 180.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
}

// 当たり判定用
CollisionData ShotCharacter::CharacterCheck(const CollisionData& collisionData)
{

	return collisionData;
}