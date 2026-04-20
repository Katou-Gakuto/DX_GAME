#include "CameraData.h"

#include "Master.h"

#include "CameraManager.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "UI_StageStart.h"

UI_StageStart::UI_StageStart()
: UIBase(true, 1, true)
, mnCameraID(-1)
{
}

UI_StageStart::~UI_StageStart()
{
}

// UI初期化
void UI_StageStart::UIInitilize()
{

}

// UIシーン最終初期化
void UI_StageStart::UISceneLastInitilize()
{
	CameraData cmeraData = CameraData();
	cmeraData.cameraMode = CAMERA_MODE::FIXED;


	mnCameraID = Master::mpGameManager->GetCameraManager()->NewCamera(cmeraData);
	Master::mpGameManager->GetCameraManager()->SetCameraMode(mnCameraID);
}

// UI終了
void UI_StageStart::UIFinalize()
{
	Master::mpGameManager->GetCameraManager()->SetCameraMode(Master::mpGameManager->GetSceneManager()->GetSceneCameraID());
	Master::mpGameManager->GetCameraManager()->DeleteCameraData(mnCameraID);
}

// UI更新
void UI_StageStart::UIUpdate()
{
}

// UI最終更新
void UI_StageStart::UILastUpdate()
{
}

// UI描画
void UI_StageStart::UIDraw()
{

}

// 選択決定時処理
void UI_StageStart::DecisionProcess()
{
}