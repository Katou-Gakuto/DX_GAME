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
/*【アニメーションデータ】
/*----------*/
struct AnimationData
{// TODO: 変数名後で修正
    MODEL_TYPE preAnimationModelType = MODEL_TYPE::NONE;    // アニメーションモデル種類

    ANIMATION_TYPE animationType = ANIMATION_TYPE::NONE;                        // アニメーション種類

    std::map<ANIMATION_TYPE, int> animationNumber;           // アニメションの数字(添え字やハンドルナンバーなど)
};

/*----------*/
/*【シングルアニメーションタイプデータ】
/*----------*/
// INPROGRESS: アニメーション作成中

/*----------*/
/*【アニメーションステートデータ構造体】
/*----------*/
struct AnimationStateData
{
	std::map<MODEL_TYPE, IStateAnimation*> animationState;	// アニメーション状態達
	std::map<ANIMATION_TYPE, MODEL_TYPE> animationModelType;	// アニメーションのモデル種類
	ANIMATION_TYPE animationType;	// 現在のアニメーション種類
	
};