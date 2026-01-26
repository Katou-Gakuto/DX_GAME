#include "AttackEnum.h"
#include "CollisionData.h"

#include "DxLib.h"

#include "Master.h"

#include "AttackManager.h"
#include "Character_Shot.h"
#include "GameManager.h"
#include "ObjectBases.h"
#include "UtilCalc.h"

Character_Shot::Character_Shot(bool nextSceneDeleteFlag, STATUS status, SHOT_TYPE shotType, std::map<ATTACK_METHOD_TYPE, CharacterAttackData> characterAttackData, std::map<ATTACK_METHOD_TYPE, AttackData> attackDatas)
: CharacterBase(nextSceneDeleteFlag, status)
{
	mmCharacterAttackDatas = characterAttackData;

	switch (shotType)
	{
	case SHOT_TYPE::DEFAULT:
		for (auto& attackData : attackDatas)
		{
			attackData.second.attackCharacter = this;

			Master::mpGameManager->GetAttackManager()->CreateAttack(attackData.second.attackType);
			mmCharacterAttackDatas[attackData.first].attackDataNumber = Master::mpGameManager->GetAttackManager()->SetAttackData(attackData.second);
		}
		break;
	}
}

Character_Shot::~Character_Shot()
{
}

// 攻撃リセット
void Character_Shot::StopAttack(ATTACK_METHOD_TYPE attackMethodType)
{
}

// キャラクター初期化
void Character_Shot::CharacterInitilize()
{
}

// キャラクター終了
void Character_Shot::CharacterFinalize()
{
}

// キャラクター更新
void Character_Shot::CharacterUpdate()
{
}

// キャラクター最終更新
void Character_Shot::CharacterLastUpdate()
{
}

// キャラクター描画
void Character_Shot::CharacterDraw()
{
	//DrawSphere3D(VAdd(mvPosition, VGet(0.0f, 90.0, 0.0f)), 180.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
}

// 当たり判定用
void Character_Shot::HitCheck(CollisionData& collisionData)
{
	if (UtilCalc::SphereCollision(collisionData.position, collisionData.size, mvPosition, 180.0f))
	{
		collisionData.collisionFlag = true;

		//移動方向を修正
		VECTOR normalWall = VSub(collisionData.position, mvPosition);
		normalWall = VNorm(normalWall); // 正規化して方向を取得
		if (VDot(normalWall, collisionData.vec) < 0.0f)
		{
			VECTOR tempV = VScale(normalWall, VDot(collisionData.vec, normalWall));
			collisionData.vec = VSub(collisionData.vec, tempV); // プレイヤーの方向を修正
		}
	}
}