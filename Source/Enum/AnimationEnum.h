#pragma once

// アニメーション種類
enum class ANIMATION_TYPE
{
    NONE = 0,  // 無し
    WALK,      // 歩く 
    RUN,       // 走る
    JUMP,      // ジャンプ
    ATTACK,    // 攻撃
};

// アニメーションモデル種類
enum class ANIMATION_MODEL_TYPE
{
    NONE = 0,   // 無し
    MV1_MODEL,  // MV1モデル
};