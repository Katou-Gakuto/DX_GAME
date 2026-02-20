#pragma once

#include "ResourceEnum.h"
#include "Vector2.h"

#include "DxLib.h"

// DIV画像データ
struct DIV_GRAPH_DATA
{
public:
	int* handle;

	int allNum;
	
	int xNum;
	int yNum;

	int xSize;
	int ySize;

	int number;
	int count;

	DIV_GRAPH_DATA()
	{
		handle = nullptr;
		allNum = 0;
		xNum = 0;
		yNum = 0;
		xSize = 0;
		ySize = 0;
		number = -1;
		count = 0;
	}

	/*初期化用(ハンドルの配列と全画像の枚数のみ設定)*/
	DIV_GRAPH_DATA(int allNumber)
	{
		handle = (int *)malloc(sizeof(int) * allNumber);
		allNum = allNumber;
		xNum = 0;
		yNum = 0;
		xSize = 0;
		ySize = 0;
		number = -1;
		count = 0;
	}
};


struct DRAW_GRAPH_DATA
{
	Vector2_Int pos = Vector2_Int(0, 0);	// 座標
    int handle = -1;	// ハンドル

    int transFlag = TRUE;	// 透過フラグ
	Vector2_Int turnFlag = Vector2_Int(0, 0);  // 反転フラグ

	Vector2_Int size = Vector2_Int(0, 0);   // サイズ

	Vector2_Int extPos = Vector2_Int(0, 0); // 拡大座標

	Vector2_Int graphPos = Vector2_Int(0, 0);  // 画像座標


	Vector2_Int upLeft = Vector2_Int(0, 0);     // 左上座標
	Vector2_Int upRight = Vector2_Int(0, 0);    // 右上座標
	Vector2_Int downRight = Vector2_Int(0, 0);  // 右下座標
	Vector2_Int downLeft = Vector2_Int(0, 0);   // 左下座標

    double angle = 0.0;   // 回転角度

	Vector2_Int centerPos = Vector2_Int(0, 0);  // 中心座標
    VECTOR_D extRate = VGetD(0.0, 0.0, 0.0);	// 回転拡大率

    DRAW_GRAPH_TYPE drawType = DRAW_GRAPH_TYPE::NORMAL;  // 描画種類
};


typedef struct DisplaySize : Vector2
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


} DISPLAY_SIZE;

typedef struct DrawConfigData
{
	int blendMode;	// ブレンドモード
	int blendParameter;	// ブレンドパラメーター
	DrawConfigData()
	: blendMode(DX_BLENDMODE_NOBLEND)
	, blendParameter(255)
	{
	}

}DRAW_CONFIG_DATA;