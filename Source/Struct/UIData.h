#pragma once

#include "Vector2.h"

struct DisplaySize
{
public:
	// ディスプレイ大きさ
	Vector2 displaySize;

	// TODO: 画面の座標取得(割合)と別の座標から居て値割合変更した座標

	/// <summary>左を起点にした割合(0～1)から縦軸の座標を取得</summary>
	float DidplayLeft_RatioHeightPos(float ratio);
	
	/// <summary>上を起点にした割合(0～1)から縦軸の座標を取得</summary>
	float DidplayUp_RatioWidthPos(float ratio);

	/// <summary>左上を起点にした割合(0～1)から座標を取得</summary>
	Vector2_Int DidplayLeftUp_RatioPos(Vector2 ratio);

	/// <summary>右上を起点にした割合(0～1)から座標を取得</summary>
	Vector2_Int DidplayRightUp_RatioPos(Vector2 ratio);

	/// <summary>左下を起点にした割合(0～1)から座標を取得</summary>
	Vector2_Int DidplayLeftDown_RatioPos(Vector2 ratio);
	
	/// <summary>右下を起点にした割合(0～1)から座標を取得</summary>
	Vector2_Int DidplayRightDown_RatioPos(Vector2 ratio);
};