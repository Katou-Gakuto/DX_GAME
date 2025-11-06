#include "CameraData.h"

#include "Master.h"

#include "FSM.h"
#include "ResultUI.h"

ResultUI::ResultUI()
: UIBase(true, 1)
, mnLineAeraSize(10000.0f)
, mnLineNum(50)
{
}

ResultUI::~ResultUI()
{
}

// UI初期化
void ResultUI::UIInitilize()
{
}

// UI終了
void ResultUI::UIFinalize()
{
}

// UI更新
void ResultUI::UIUpdate()
{
}

// UI最終更新
void ResultUI::UILastUpdate()
{
}

// UI描画
void ResultUI::UIDraw()
{

    VECTOR pos1;
    VECTOR pos2;

    SetUseZBufferFlag(true);

    pos1 = VGet(-mnLineAeraSize / 2.0f, 0.0f, -mnLineAeraSize / 2.0f);
    pos2 = VGet(-mnLineAeraSize / 2.0f, 0.0f, mnLineAeraSize / 2.0f);
    for (int i = 0; i < mnLineNum; i++)
    {
        DrawLine3D(pos1, pos2, GetColor(0, 255, 0));
        pos1.x += mnLineAeraSize / mnLineNum;
        pos2.x += mnLineAeraSize / mnLineNum;
    }

    pos1 = VGet(-mnLineAeraSize / 2.0f, 0.0f, -mnLineAeraSize / 2.0f);
    pos2 = VGet(mnLineAeraSize / 2.0f, 0.0f, -mnLineAeraSize / 2.0f);
    for (int i = 0; i < mnLineNum; i++)
    {
        DrawLine3D(pos1, pos2, GetColor(255, 0, 0));
        pos1.z += mnLineAeraSize / mnLineNum;
        pos2.z += mnLineAeraSize / mnLineNum;
    }
}


// 選択決定時処理
void ResultUI::DecisionProcess()
{
    mpFsm->Decision(this);
}