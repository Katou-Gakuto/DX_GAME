#pragma once
#include "DxLib.h"

struct CollisionData
{
	CollisionData();

	VECTOR position;	// ポジション
	VECTOR vec;			// 向き
	float speed;		// 速度
	float size;			// 大きさ

	bool collisionFlag;	// 衝突フラグ
};