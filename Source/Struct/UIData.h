#pragma once

#include "Vector2.h"

struct DisplaySize : Vector2
{
public:
	int colorBit;

	DisplaySize& operator =(Vector2 src)
	{
		this->x = src.x;
		this->y = src.y;
		return *this;
	}
	DisplaySize& operator =(Vector2_Int src)
	{
		this->x = static_cast<float>(src.x);
		this->y = static_cast<float>(src.y);
		return *this;
	}
	
	// TODO: 画面の座標取得(割合)と別の座標から居て値割合変更した座標

	/// <summary>左を起点にした割合(0～1)から縦軸の座標を取得</summary>
	int Left_RatioWidth(float ratio);
	/// <summary>上を起点にした割合(0～1)から縦軸の座標を取得</summary>
	int Up_RatioHeight(float ratio);
	/// <summary>右を起点にした割合(0～1)から縦軸の座標を取得</summary>
	int Right_RatioWidth(float ratio);
	/// <summary>下を起点にした割合(0～1)から縦軸の座標を取得</summary>
	int Down_RatioHeight(float ratio);

	/// <summary>左上を起点にした割合(0～1)から座標を取得</summary>
	Vector2_Int LeftUp_Ratio(Vector2 ratio);
	/// <summary>左上を起点にした割合(0～1)から座標を取得</summary>
	Vector2_Int LeftUp_FloatRatio(float ratio) { return LeftUp_Ratio(Vector2(ratio, ratio)); }

	/// <summary>右上を起点にした割合(0～1)から座標を取得</summary>
	Vector2_Int RightUp_Ratio(Vector2 ratio);
	/// <summary>右上を起点にした割合(0～1)から座標を取得</summary>
	Vector2_Int RightUp_FloatRatio(float ratio) { return RightUp_Ratio(Vector2(ratio, ratio)); }

	/// <summary>左下を起点にした割合(0～1)から座標を取得</summary>
	Vector2_Int LeftDown_Ratio(Vector2 ratio);
	/// <summary>左下を起点にした割合(0～1)から座標を取得</summary>
	Vector2_Int LeftDown_FloatRatio(float ratio) { return LeftDown_Ratio(Vector2(ratio, ratio)); }
	
	/// <summary>右下を起点にした割合(0～1)から座標を取得</summary>
	Vector2_Int RightDown_Ratio(Vector2 ratio);
	/// <summary>右下を起点にした割合(0～1)から座標を取得</summary>
	Vector2_Int RightDown_FloatRatio(float ratio) { return RightDown_Ratio(Vector2(ratio, ratio)); }
};