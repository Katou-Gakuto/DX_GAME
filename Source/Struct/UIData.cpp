#include "UIData.h"

// 左を起点にした割合(0～1)から縦軸の座標を取得
float DisplaySize::DidplayLeft_RatioHeightPos(float ratio)
{
    return displaySize.y * ratio;
}

// 上を起点にした割合(0～1)から縦軸の座標を取得
float DisplaySize::DidplayUp_RatioWidthPos(float ratio)
{
    return displaySize.x * ratio;
}

// 左上を起点にした割合(0～1)から座標を取得
Vector2_Int DisplaySize::DidplayLeftUp_RatioPos(Vector2 ratio)
{
    Vector2_Int pos;
    pos.x = static_cast<int>(DidplayLeft_RatioHeightPos(ratio.x));
    pos.y = static_cast<int>(DidplayLeft_RatioHeightPos(ratio.y));
    return pos;
}

// 右上を起点にした割合(0～1)から座標を取得
Vector2_Int DisplaySize::DidplayRightUp_RatioPos(Vector2 ratio)
{
    Vector2_Int pos;
    pos.x = static_cast<int>(DidplayLeft_RatioHeightPos(1.0f - ratio.x));
    pos.y = static_cast<int>(DidplayLeft_RatioHeightPos(ratio.y));
    return pos;
}

// 左下を起点にした割合(0～1)から座標を取得
Vector2_Int DisplaySize::DidplayLeftDown_RatioPos(Vector2 ratio)
{
    Vector2_Int pos;
    pos.x = static_cast<int>(DidplayLeft_RatioHeightPos(ratio.x));
    pos.y = static_cast<int>(DidplayLeft_RatioHeightPos(1.0f - ratio.y));
    return pos;
}

// 右下を起点にした割合(0～1)から座標を取得
Vector2_Int DisplaySize::DidplayRightDown_RatioPos(Vector2 ratio)
{
    Vector2_Int pos;
    pos.x = static_cast<int>(DidplayLeft_RatioHeightPos(1.0f - ratio.x));
    pos.y = static_cast<int>(DidplayLeft_RatioHeightPos(1.0f - ratio.y));
    return pos;
}