#pragma once
#include "DxLib.h"

namespace UtilCalc
{
	/*ゼロ*/
	const VECTOR VZero = VGet(0.0f, 0.0f, 0.0f);
	/*ゼロ*/
	const VECTOR VOne = VGet(1.0f, 1.0f, 1.0f);

	/*符号反転*/
	inline const VECTOR VSignInversion(VECTOR src) { return VGet(src.x, src.y, src.z); }

	/*ラジアン変換(PI / 180.0f)*/
	inline const VECTOR VRadChange(VECTOR src) { return VScale(src, 0.0174532924f/*PI / 180.0f*/); }
	/*デグリー変換(180.0f / PI)*/
	inline const VECTOR VDegChange(VECTOR src) { return VScale(src, 57.29578f/*180.0f / PI*/); }

    /*方向を3.14から-3.14になるように調整する(ラジアン)*/
	float NotExceedAngle(float angle);

    /*方向を3.14から-3.14になるように調整する(3方向)(ラジアン)*/
	VECTOR VNotExceedAngle(VECTOR angle);

	/*球面移動した場所(ラジアン)*/
	VECTOR VSphericalMovePos(float size, VECTOR angle);

	/// <summary>移動量をアングルに反映した値を返す(ラジアン)</summary>
	VECTOR VMoveVecToAngle(VECTOR moveVec, VECTOR angle = UtilCalc::VZero, float speed = 0.2f);

	/*--------------*/
	/*【当たり判定】*/
	/*--------------*/

	/*球同士の当たり判定*/
	bool SphereCollision(VECTOR srcPos, float srcRadius, VECTOR dstPos, float dstRadius);

	///*四角同士の当たり判定*/
	//bool BoxCollision(VECTOR srcTopLeft, VECTOR srcBottomRight, VECTOR dstTopLeft, VECTOR dstBottomRight);
};