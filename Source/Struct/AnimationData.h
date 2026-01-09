#pragma once
#include "AnimationEnum.h"

struct AnimationData
{
    ANIMATION_MODEL_TYPE preAnimationModelType = ANIMATION_MODEL_TYPE::NONE;   // アニメーションモデル種類

    ANIMATION_TYPE animationType = ANIMATION_TYPE::NONE;                       // アニメーション種類
};