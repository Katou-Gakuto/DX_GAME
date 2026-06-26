#pragma once
#include <map>
#include <string>
#include <vector>

#include "AnimationEnum.h"
#include "DotWeenData.h"

class IStateAnimation;

// TODO: あとでデータマネージャーに移動
/*----------*/
/*【読み込み用アニメーションデータ】
/*----------*/
struct LoadAnimationData
{
    std::string animationPath;  // アニメーションファイル座標

    ANIMATION_MOVE_TYPE animationType;   // アニメーション種類

    int animationIndex; // アニメーション添え字

    bool animationLoopFlag;  // アニメーションループフラグ

    ANIMATION_TYPE modelType;   // モデル種類

    int blendMode;      // ブレンドモード（画像用）
    int blendParameter; // ブレンドパラメーター（画像用)

    float size = 1.0f;
};

/*----------*/
/*【アニメーション一つ分の情報】
/*----------*/
struct OneAnimationData
{
    /*-------------------------------------------------- 3Dモデルアニメーション情報 --------------------------------------------------*/
    ANIMATION_MOVE_TYPE preAnimationType = ANIMATION_MOVE_TYPE::NONE;    // 一つ前のアニメーション種類

    int number = 0;   // モデルナンバー

    bool loopFlag = false;  // ループフラグ

    ANIMATION_TYPE modelType = ANIMATION_TYPE::NONE;    // モデル種類

    float animationCount = 0.0f;   // アニメーションカウント

    int animationHandle = 0;    // アニメションハンドル
    /*--------------------------------------------------------------------------------------------------------------------------------*/

    
    /*-------------------------------------------------- 画像アニメーション情報 --------------------------------------------------*/
    int blendMode = 0;      // ブレンドモード
    int blendParameter = 0; // ブレンドパラメーター
    /*----------------------------------------------------------------------------------------------------------------------------*/

    DOT_WEEN_DATA dotWeenData;  // DotWeen情報
};

// /*----------*/
// /*【アニメーションの情報】
// /*----------*/
// struct AnimationDatas
// {
//     std::map<ANIMATION_MOVE_TYPE, OneAnimationData> animDatas;
// };

// /*----------*/
// /*【アニメーションステート生成情報】
// /*----------*/
// struct ANIMATION_STATE_INFO
// {
//     int MyKey;    // 自身のキーを返す
//     ANIMATION_MOVE_TYPE AnimationType;   // アニメーションの種類

//     IStateAnimation* AnimationState;    // アニメーションステート

//     int ReferenceNumber;    // 参照数

//     // アニメーション変更条件をenumclass化したものを保持
//     //std::vector<>

//     bool operator== (ANIMATION_STATE_INFO& src)
//     {
//         if (this->AnimationType == src.AnimationType)
//         {
//             return true;
//         }

//         return false;
//     }
// };