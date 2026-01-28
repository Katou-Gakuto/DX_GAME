#pragma once

// アニメーション種類
enum class ANIMATION_TYPE
{
    NONE = 0,   // 無し
    IDLE,       // 待機状態
    WALK,       // 歩く 
    RUN,        // 走る
    JUMP_IN,    // ジャンプ開始
    JUMP,       // ジャンプ
    JUMP_OUT,   // ジャンプ終了
    ATTACK_IN,  // 攻撃開始
    ATTACK,     // 攻撃
    ATTACK_OUT, // 攻撃終了
    DEATH,      // 死亡

    NORMAL_ATTACK_IN,   // ノーマル攻撃開始
    NORMAL_ATTACK,      // ノーマル攻撃
    NORMAL_ATTACK_OUT,  // ノーマル攻撃終了

    DISPLAY_MOVE,// 数字でやる_1, _2,  _3 みたいな感じ
};

// アニメーションモデル種類
enum class MODEL_TYPE
{
    NONE = 0,   // 無し
    MV1_MODEL,  // MV1モデル
    MV1_MODEL_MOVE, // MV1モデル モデル操作
    MV1_MODEL_ONLY, // MV1モデルのみ　アニメーション無しモデル
    POLYGON_INDEXED, // ポリゴンインデックスモデル
    
    EFFECT, // エフェクト

    GRAPH,  // 画像
    MOVIE,  // 映像
};