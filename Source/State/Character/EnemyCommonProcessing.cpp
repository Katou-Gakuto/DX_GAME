#include "ResourceData.h"

#include "DxLib.h"

#include "Master.h"

#include "CameraManager.h"
#include "EnemyCommonProcessing.h"
#include "GameManager.h"
#include "ObjectBases.h"

EnemyCommonProcessing::EnemyCommonProcessing(STATE_ENEMY_TYPE enemyType)
{
    meEnemyType = enemyType;

    mnScreenHandle = MakeScreen(SCREEN_SIZES[(int)enemyType].x, SCREEN_SIZES[(int)enemyType].y);
}

// 削除処理
void EnemyCommonProcessing::EnemyCommonProcessingData_Delete()
{
    if (mnScreenHandle != -1)
    {
        DeleteGraph(mnScreenHandle);
    }
}

// エネミー情報描画
void EnemyCommonProcessing::EnemyDataDraw(CharacterBase *enemy)
{
    if (mnScreenHandle == -1)
    {
        return;
    }

    // 描画必要データ取得
    VECTOR setCharacterPos = VAdd(enemy->GetPos(), VGet(0, enemy->GetSize().y * 250.0f, 0));

    // 描画先を変更
    SetDrawScreen(mnScreenHandle);
    ClearDrawScreen();

    switch (meEnemyType)
    {
    case STATE_ENEMY_TYPE::MAP_ENEMY:

        // // 土台
        // DrawBoxAA(0, 0, mnScreenSizeX, 40, GetColor(255, 255, 255), TRUE);
        // DrawBoxAA(2, 2, mnScreenSizeX - 2, 40 - 2, GetColor(0, 0, 0), TRUE);

        // 名前
        //DrawExtendGraph(0, 0, 100, 50, mnNameHandle, TRUE);
        DrawFormatString(5, 21, GetColor(255, 255, 255), "%s", "mstrName.c_str()");

        // レベル
        DrawBox(1, 1, 65, 20, GetColor(255, 255, 255), TRUE);
        DrawBox(3, 3, 63, 18, GetColor(0, 0, 0), TRUE);
        DrawFormatString(5, 3, GetColor(255, 255, 255), "Lv.%d", enemy->GetStatus()->level);
        break;

    case STATE_ENEMY_TYPE::BATTLE_ENEMY:
        // 描画必要データ取得
        VECTOR setCharacterPos = VAdd(enemy->GetPos(), VGet(0, enemy->GetSize().y * 250.0f, 0));

        // 描画先を変更
        SetDrawScreen(mnScreenHandle);
        ClearDrawScreen();

        // // 土台
        // DrawBoxAA(0, 0, mnScreenSizeX, 40, GetColor(255, 255, 255), TRUE);
        // DrawBoxAA(2, 2, mnScreenSizeX - 2, 40 - 2, GetColor(0, 0, 0), TRUE);

        // 名前
        //DrawExtendGraph(0, 0, 100, 50, mnNameHandle, TRUE);
        DrawFormatString(5, 21, GetColor(255, 255, 255), "%s", "mstrName.c_str()");

        // レベル
        DrawBox(1, 1, 65, 20, GetColor(255, 255, 255), TRUE);
        DrawBox(3, 3, 63, 18, GetColor(0, 0, 0), TRUE);
        DrawFormatString(5, 3, GetColor(255, 255, 255), "Lv.%d", enemy->GetStatus()->level);

        // 土台
        DrawBoxAA(0, 40, SCREEN_SIZES[(int)meEnemyType].x, 80, GetColor(255, 255, 255), TRUE);
        DrawBoxAA(2, 42, SCREEN_SIZES[(int)meEnemyType].x - 2, 80 - 2, GetColor(0, 0, 0), TRUE);

        // HP文字
        DrawFormatString(5, 43, GetColor(255, 255, 255), "HP:%d", enemy->GetStatus()->hp);

        // HPバー
        DrawBox(5, 60, SCREEN_SIZES[(int)meEnemyType].x - 5, 75, GetColor(255, 255, 255), TRUE);
        DrawBox(8, 63, SCREEN_SIZES[(int)meEnemyType].x - 8, 72, GetColor(0, 0, 0), TRUE);
        DrawBox(8, 63, ((SCREEN_SIZES[(int)meEnemyType].x - 16) * (static_cast<float>(enemy->GetStatus()->hp) / static_cast<float>(enemy->GetStatus()->maxHp))) + 8, 72, GetColor(255, 0, 0), TRUE);
        break;
    }

    SetDrawScreen(DX_SCREEN_BACK);
    // 3Dカメラ設定
    Master::mpGameManager->GetCameraManager()->Draw();
    DrawBillboard3D(setCharacterPos, 0.5f, 0.0f, 200.0f, 0.0f, mnScreenHandle, TRUE);
}