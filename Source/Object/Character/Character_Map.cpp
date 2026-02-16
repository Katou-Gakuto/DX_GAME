#include "AttackEnum.h"
#include "CollisionData.h"

#include "DxLib.h"

#include "Master.h"

#include "Character_Map.h"
#include "ObjectBases.h"
#include "UtilCalc.h"

Character_Map::Character_Map(STATUS status)
: CharacterBase(true, status)
{
}

Character_Map::~Character_Map()
{
}

/*攻撃開始(反動時間を返す)*/
void Character_Map::StartAttck(ATTACK_METHOD_TYPE attackMethodType)
{
}

/*攻撃停止*/
void Character_Map::StopAttack(ATTACK_METHOD_TYPE attackMethodType)
{
}

// キャラクター初期化
void Character_Map::CharacterInitilize()
{
}

// キャラクターシーン最終初期化
void Character_Map::CharacterSceneLastInitilize()
{
}

// キャラクター終了
void Character_Map::CharacterFinalize()
{
}

// キャラクター更新
void Character_Map::CharacterUpdate()
{
}

// キャラクター最終更新
void Character_Map::CharacterLastUpdate()
{
}

// キャラクター描画
void Character_Map::CharacterDraw()
{
	//if (mvPosition.z > 3400.0f)
	//{
	//	DrawSphere3D(VAdd(mvPosition, VGet(0.0f, 90.0, 0.0f)), 180.0f, 32, GetColor(0, 0, 255), GetColor(255, 255, 255), TRUE);
	//	return;
	//}
	//DrawSphere3D(VAdd(mvPosition, VGet(0.0f, 90.0, 0.0f)), 180.0f, 32, GetColor(255, 0, 255), GetColor(255, 255, 255), TRUE);
}

// 当たり判定用
void Character_Map::HitCheck(CollisionData& collisionData)
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