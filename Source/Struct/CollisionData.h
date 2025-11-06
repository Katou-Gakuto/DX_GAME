#pragma once
#include "DxLib.h"

enum class COLLISION_TYPE
{
	NONE = -1,
	SPHERE = 0,	// 球
	CUBOID,		// 直方体
};

struct CollisionData
{
	CollisionData();

	VECTOR position;	// ポジション
	VECTOR vec;			// 向き
	float speed;		// 速度
	float size;			// 大きさ

	bool collisionFlag;	// 衝突フラグ

	int objID;			// オブジェクトID

	COLLISION_TYPE collisionType;	// 当たり判定種類(今は設定できない　モデルができてから)
};