#pragma once

#include "ResourceData.h"

enum class DRAW_MANAGER_DRAW_TYPE
{
    GRAPH = 0,
};

struct DRAW_DATA
{
    int drawID; // 描画ID

    bool drawFlag = true;

    DRAW_MANAGER_DRAW_TYPE drawManagerDrawType; // 描画マネージャー描画種類

    DRAW_GRAPH_DATA drawGraphData;  // 画像描画情報

    DRAW_CONFIG_DATA drawConfigData;    // 描画設定情報
};