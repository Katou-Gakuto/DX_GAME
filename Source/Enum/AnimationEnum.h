#pragma once

// アニメーション種類
enum class ANIMATION_TYPE
{
    NONE = 0,   // 無し
    WALK,       // 歩く 
    RUN,        // 走る
    JUMP_IN,    // ジャンプ開始
    JUMP,       // ジャンプ
    JUMP_OUT,   // ジャンプ終了
    ATTACK,     // 攻撃
};

// アニメーションモデル種類
enum class MODEL_TYPE
{
    NONE = 0,   // 無し
    MV1_MODEL,  // MV1モデル
    MV1_MODEL_ONLY, // MV1モデルのみ
    POLYGON_INDEXED, // ポリゴンインデックスモデル
};