#include "CameraData.h"

#include "Master.h"

#include "FSM.h"
#include "UI_Result.h"

UI_Result::UI_Result()
: UIBase(true, 1)
, mnLineAeraSize(10000.0f)
, mnLineNum(50)
{
}

UI_Result::~UI_Result()
{
}

// UI初期化
void UI_Result::UIInitilize()
{
}

// UI終了
void UI_Result::UIFinalize()
{
}

// UI更新
void UI_Result::UIUpdate()
{
}

// UI最終更新
void UI_Result::UILastUpdate()
{
}

// UI描画
void UI_Result::UIDraw()
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
void UI_Result::DecisionProcess()
{
    mpFsm->Decision(this);
}