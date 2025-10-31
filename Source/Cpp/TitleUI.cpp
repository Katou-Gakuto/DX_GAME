#include "../Header/CameraData.h"

#include "../Header/Master.h"

#include "../Header/CameraManager.h"
#include "../Header/DataManager.h"
#include "../Header/GameManager.h"
#include "../Header/SceneManager.h"
#include "../Header/TitleUI.h"

TitleUI::TitleUI()
: UIBase(true, 1)
, mnLineAeraSize(10000.0f)
, mnLineNum(50)
, mnCameraID(-1)
{
}

TitleUI::~TitleUI()
{
}

// UI初期化
void TitleUI::UIInitilize()
{
    CameraData cameraData = CameraData();
    cameraData.cameraMode = CAMERA_MODE::FIXED;
    cameraData.position = VGet(0.0f, 180.0f, -180.0f);
    cameraData.targetPosition = VGet(0.0f, 180.0f, 0.0f);
    cameraData.threeDFlag = true;
    cameraData.SetColor(F4Get(128, 128, 128, 0));
    mnCameraID = Master::mpGameManager->GetCameraManager()->NewCamera(cameraData);
    Master::mpGameManager->GetCameraManager()->SetCameraMode(mnCameraID);
}

// UI終了
void TitleUI::UIFinalize()
{
    Master::mpGameManager->GetCameraManager()->DeleteCameraData(mnCameraID);
}

// UI更新
void TitleUI::UIUpdate()
{
}

// UI最終更新
void TitleUI::UILastUpdate()
{
}

// UI描画
void TitleUI::UIDraw()
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
void TitleUI::DecisionProcess()
{
	mpFsm->Decision(this);
}