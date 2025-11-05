#pragma once
#include "DxLib.h"

namespace UtilCalc
{
	/*ゼロ*/
	inline const VECTOR VZero() { return VGet(0.0f, 0.0f, 0.0f); }

	/*符号反転*/
	inline const VECTOR VSignInversion(VECTOR src) { return VGet(src.x, src.y, src.z); }

	/*ラジアン変換(PI / 180.0f)*/
	inline const VECTOR VRadChange(VECTOR src) { return VScale(src, 0.0174532924f/*PI / 180.0f*/); }
	/*デグリー変換(180.0f / PI)*/
	inline const VECTOR VDegChange(VECTOR src) { return VScale(src, 57.29578f/*180.0f / PI*/); }

    /*方向を2から-2になるように調整する(ラジアン)*/
	float NotExceedAngle(float angle);

    /*方向を2から-2になるように調整する(3方向)(ラジアン)*/
	VECTOR VNotExceedAngle(VECTOR angle);

	/*球面移動した場所(ラジアン)*/
	VECTOR VSphericalMovePos(float size, VECTOR angle);

	/*--------------*/
	/*【当たり判定】*/
	/*--------------*/

	/*球同士の当たり判定*/
	bool SphereCollision(VECTOR srcPos, float srcRadius, VECTOR dstPos, float dstRadius);
};