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
};

/*----------*/
/*【アニメーションの情報】
/*----------*/
struct AnimationDatas
{
    int number = 0;   // モデル種類

    bool loopFlag = false;  // ループフラグ

    MODEL_TYPE modelType = MODEL_TYPE::NONE;    // モデル種類

    operator int&()
    {
        return this->number;
    }
};