#pragma once
#include <map>
#include <string>
#include <vector>

#include "AnimationEnum.h"

// TODO: あとでデータマネージャーに移動
/*----------*/
/*【読み込み用アニメーションデータ】
/*----------*/
struct LoadAnimationData
{
    std::string animationPath;  // アニメーションファイル座標

    ANIMATION_TYPE animationType;   // アニメーション種類

    int animationIndex; // アニメーション添え字

    bool animationLoopFlag;  // アニメーションループフラグ

    MODEL_TYPE modelType;   // モデル種類
};

/*----------*/
/*【アニメーションの情報】
/*----------*/
struct AnimationDatas
{
    ANIMATION_TYPE preAnimationType;    // 一つ前のアニメーション種類

    int number = 0;   // モデルナンバー

    bool loopFlag = false;  // ループフラグ

    MODEL_TYPE modelType = MODEL_TYPE::NONE;    // モデル種類

    float animationCount = 0.0f;   // アニメーションカウント

    int animationHandle = 0.0f;    // アニメションハンドル

    operator int&()
    {
        return this->number;
    }
};