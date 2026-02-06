#include <string>
#include <vector>

#include "Master.h"

#include "CameraManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "TelopManager.h"
#include "TimeManager.h"

TelopManager::TelopManager()
: mnPreTelopDrawTime(0)
{
    msTelopStrings.clear();
}

TelopManager::~TelopManager()
{
}

// 終了
void TelopManager::Finalize()
{
}

// 更新
void TelopManager::Update()
{
    if ((mnPreTelopDrawTime < Master::mpTimeManager->GetTime()) && (msTelopStrings.size() > 0))
    {
        DeleteTelop();
    }
}

// 描画
void TelopManager::Draw()
{
}

// テロップ描画
void TelopManager::DrawTelop(TELOP_DATA& telopData)
{
    switch (telopData.telopType)
    {
    case TELOP_TYPE::POSITION_3D:
        DrawTelop_Position3D(telopData);
        break;
    }
}

// テロップ追加
void TelopManager::AddTelop(std::string telop)
{
    msTelopStrings.push_back(telop);
    mnPreTelopDrawTime = Master::mpTimeManager->GetTime() + TELOP_TIME;
}

// テロップ削除
void TelopManager::DeleteTelop()
{
    msTelopStrings.clear();
}

/*-------------------------------------------------- テロップ描画 --------------------------------------------------*/
// 3Dポジションテロップ描画
void TelopManager::DrawTelop_Position3D(TELOP_DATA& telopData)
{
    int drawLineCount = 0;
    
    // // 描画先を変更
    // SetDrawScreen(mnStasusDrawScreenHandle);
    // ClearDrawScreen();



    // 1列ずつ下から描画
    // 画像描画
    for (int i = 0; i < 0; i++)
    {
        Master::mpResourceManager->DrawData_Graph(telopData.drawGraphData);

        //SetDrawScreen(DX_SCREEN_BACK);
        //// 3Dカメラ設定
        //Master::mpGameManager->GetCameraManager()->Draw();
        //DrawBillboard3D(VGet(telopData.telopPos.x, telopData.telopPos.y + (telopData.oneSize.y * drawLineCount), telopData.telopPos.z), 0.5f, 0.5f, telopData.oneSize.x, 0.0f, mnStasusDrawScreenHandle, TRUE);
    }

    /*
    // 描画必要データ取得
    VECTOR setCharacterPos = VAdd(mvObjectPosition, VGet(0, msStatus.size * 2.7, 0));

    // 描画先を変更
    SetDrawScreen(mnStasusDrawScreenHandle);
    ClearDrawScreen();

    // 土台
    DrawBoxAA(0, 0, mnScreenSizeX, 40, GetColor(255, 255, 255), TRUE);
    DrawBoxAA(2, 2, mnScreenSizeX - 2, 40 - 2, GetColor(0, 0, 0), TRUE);

    // 名前
    //DrawExtendGraph(0, 0, 100, 50, mnNameHandle, TRUE);
    DrawFormatString(5, 21, GetColor(255, 255, 255), "%s", mstrName.c_str());

    // レベル
    DrawBox(1, 1, 65, 20, GetColor(255, 255, 255), TRUE);
    DrawBox(3, 3, 63, 18, GetColor(0, 0, 0), TRUE);
    DrawFormatString(5, 3, GetColor(255, 255, 255), "Lv.%d", msStatus.level);

    SetDrawScreen(DX_SCREEN_BACK);
    // 3Dカメラ設定
    Master::mpCamera->Initialize3DCameraTemplate();
    DrawBillboard3D(setCharacterPos, 0.5f, 0.5f, 200.0f, 0.0f, mnStasusDrawScreenHandle, TRUE);
    */
}

/*------------------------------------------------------------------------------------------------------------------*/