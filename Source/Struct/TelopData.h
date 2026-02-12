#pragma once
#include "TelopEnum.h"
#include "ResourceData.h"

#include "DxLib.h"

struct TELOP_DATA
{
    TELOP_TYPE telopType;   // テロップ種類

    VECTOR telopPos;    // テロップ座標

    VECTOR oneSize; // 1つ分のサイズ

    DRAW_GRAPH_DATA drawGraphData;  // 描画画像情報
};