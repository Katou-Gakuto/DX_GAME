#pragma once
#include "DxLib.h"

namespace UtilCalc
{
	/*ゼロ*/
	const VECTOR VZero = VGet(0.0f, 0.0f, 0.0f);
	/*イチ*/
	const VECTOR VOne = VGet(1.0f, 1.0f, 1.0f);
	/*xのみ1*/
	const VECTOR VXOne = VGet(1.0f, 0.0f, 0.0f);
	/*三分の一*/
	const float One_Third = 0.3333333f;
	/*3,14*/
	const float Pi = DX_PI_F;
	/*3,14 * 2.0f*/
	const float PiTwo = DX_PI_F * 2.0f;

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

	// TODO: 未完 Yのみ完成
	/// <summary>ベクトルをアングルに変換する</summary>
	VECTOR VVecToAngle(VECTOR vec);

	// TODO: 未完
	/// <summary>アングルをベクトルに変換する</summary>
	VECTOR VAngleToVec(VECTOR angle);

	/// <summary>移動量をアングルに反映した値を返す(ラジアン)</summary>
	VECTOR VMoveVecToAngle(VECTOR moveVec, VECTOR angle, float speed = 0.2f);

	/// <summary>VECTORの平均を出す(正の数)</summary>
	float PutVectorAverage(VECTOR vector);

	/// <summary>VECTORの掛け算</summary>
	VECTOR VMultiply(VECTOR src, VECTOR dst);

	/// <summary>差を出す</summary>
	float VDiff(VECTOR src, VECTOR dst);

	/// <summary>アングル同士の差を返す</summary>
	float AngleDiff(float srcAngle, float dstAngle);

	/*--------------*/
	/*【当たり判定】*/
	/*--------------*/

	/*球同士の当たり判定*/
	bool SphereCollision(VECTOR srcPos, float srcRadius, VECTOR dstPos, float dstRadius);

	///*四角同士の当たり判定*/
	//bool BoxCollision(VECTOR srcTopLeft, VECTOR srcBottomRight, VECTOR dstTopLeft, VECTOR dstBottomRight);
};