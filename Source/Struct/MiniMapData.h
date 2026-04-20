#pragma once
#include <vector>

#include "Vector2.h"

struct MINI_MAP_DATA
{
    Vector2 vectorData;
};

struct ALL_MINI_MAP_DRAW_DATA
{
    // 範囲内にいるキャラクターのポジション情報
    std::vector<MINI_MAP_DATA> minMapWithinRangePos;

    // 範囲外のキャラクターの方向情報
    std::vector<MINI_MAP_DATA> minMapOutsideRangeDir;
};