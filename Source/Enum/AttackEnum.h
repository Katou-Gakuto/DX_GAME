#pragma once

// 攻撃手段種類
enum class ATTACK_METHOD_TYPE
{
    NORMAL = 0, // ノーマル攻撃
    SPCEIAL,    // スペシャル攻撃
    JUMP,       // ジャンプ攻撃
};

// 攻撃種類
enum class ATTACK_TYPE
{
	SHOT = 0,
    UNIQUE_ROBOT,
    JUMP_ATTACK,
};