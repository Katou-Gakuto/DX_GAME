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

    int blendMode;      // ブレンドモード（画像用）
    int blendParameter; // ブレンドパラメーター（画像用)
};

/*----------*/
/*【アニメーション一つ分の情報】
/*----------*/

struct OneAnimationData
{
    /*-------------------------------------------------- 3Dモデルアニメーション情報 --------------------------------------------------*/
    ANIMATION_TYPE preAnimationType = ANIMATION_TYPE::NONE;    // 一つ前のアニメーション種類

    int number = 0;   // モデルナンバー

    bool loopFlag = false;  // ループフラグ

    MODEL_TYPE modelType = MODEL_TYPE::NONE;    // モデル種類

    float animationCount = 0.0f;   // アニメーションカウント

    int animationHandle = 0;    // アニメションハンドル
    /*--------------------------------------------------------------------------------------------------------------------------------*/

    
    /*-------------------------------------------------- 画像アニメーション情報 --------------------------------------------------*/
    int blendMode = 0;      // ブレンドモード
    int blendParameter = 0; // ブレンドパラメーター

    /*----------------------------------------------------------------------------------------------------------------------------*/
};

/*----------*/
/*【アニメーションの情報】
/*----------*/
struct AnimationDatas
{
    std::map<ANIMATION_TYPE, OneAnimationData> animDatas;
};