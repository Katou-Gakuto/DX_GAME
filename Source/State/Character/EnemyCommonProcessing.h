#pragma once
#include "ResourceData.h"

class CharacterBase;

enum class STATE_ENEMY_TYPE
{
    MAP_ENEMY = 0,
    BATTLE_ENEMY,

    MAX
};

class EnemyCommonProcessing
{
private:
    // エネミーステート種類
    STATE_ENEMY_TYPE meEnemyType;

    // TODO: 描画マネージャー作りそこに情報渡しハンドルを設定する　それの参照を切ることで削除したことにするs
    // 描画用スクリーンハンドル
    int mnScreenHandle;

    const DisplaySize SCREEN_SIZES[(int)STATE_ENEMY_TYPE::MAX] = { {Vector2(70.0f, 40.0f), 0 }, {Vector2(70.0f, 80.0f), 0,}};

protected:
    EnemyCommonProcessing(STATE_ENEMY_TYPE enemyType);

    /// <summary>削除処理</summary>
    void EnemyCommonProcessingData_Delete();

    /// <summary>エネミー情報描画</summary>
    void EnemyDataDraw(CharacterBase *enemy);
};