#pragma once

// データ種類
enum class DATA_TYPE
{
	FILE_NAME = 0,
	CHARACTER,
	PLAYER,
	INIT_PLAYER,
	LEVEL,
};

// データシーン
enum DATA_SCENE
{
    TOWN = 0,
    DUNGEON,
    BATTLE,
    MAX,
};

// スコア評価
enum class SCORE_RANK
{
    A = 0,
    B,
    C,
    D,
};