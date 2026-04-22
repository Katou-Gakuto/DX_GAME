#pragma once

// アニメーション種類
enum class ANIMATION_TYPE
{
    // アニメーションがどう動くかを定義する

    NONE = 0,   // 無し
    START,      // 開始
    END,        // 終了

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

    SPCEIAL_ATTACK_IN,   // スペシャル攻撃開始
    SPCEIAL_ATTACK,      // スペシャル攻撃
    SPCEIAL_ATTACK_OUT,  // スペシャル攻撃終了

    JUMP_ATTACK_IN,   // ジャンプ攻撃開始
    JUMP_ATTACK,      // ジャンプ攻撃
    JUMP_ATTACK_OUT,  // ジャンプ攻撃終了

    DISPLAY_MOVE,   // 画面移動

    FADE_OUT,   // フェードアウト
    FADE_IN,    // フェードイン
};

// アニメーションモデル種類
enum class MODEL_TYPE // TODO: モデル種類ではなくアニメーション処理種類にする
{
    NONE = 0,   // 無し
    // TODO: IDLE作る
    MV1_MODEL,  // MV1モデル
    MV1_MODEL_MOVE, // MV1モデル モデル操作
    MV1_MODEL_ONLY, // MV1モデルのみ　アニメーション無しモデル
    POLYGON_INDEXED, // ポリゴンインデックスモデル
    
    EFFECT, // エフェクト

    GRAPH,  // 画像
    MOVIE,  // 映像

    FADE,   // フェード

    TOD_WEEN,
};