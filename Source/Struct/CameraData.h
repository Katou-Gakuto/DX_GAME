#pragma once

#include "DxLib.h"

class CharacterBase;

enum class CAMERA_MODE
{
	NONE = -1,// ない

	FIXED = 0,	// 固定視点
	MOVE,	// 移動視点

	CHARACTER,	// キャラクター視点
	PLAYER,	// プレイヤー視点
};

struct CameraData
{
public:
	CameraData();

	inline void SetColor(const FLOAT4& color) { this->red = (int)color.x; this->green = (int)color.y; this->blue = (int)color.z; this->alpha = (int)color.w; }

	CharacterBase* targetCharacter;	// ターゲットキャラクター

	VECTOR targetPosition;	// ターゲットポジション
	
	VECTOR position;		// カメラポジション
	VECTOR plusPosition;	// カメラプラスポジション
	VECTOR angle;	// カメラアングル

	VECTOR twoDPosition;	// 2Dポジション

	CAMERA_MODE cameraMode;	// カメラモード

	int red;	// 赤
	int green;	// 緑
	int blue;	// 青
	int alpha;	// アルファ値

	float cameraDistance;	// カメラの間隔

	int cameraID;	// カメラID

	bool threeDFlag;	// 3D描画フラグ

	/*方向取得*/
	VECTOR GetDirection();
};