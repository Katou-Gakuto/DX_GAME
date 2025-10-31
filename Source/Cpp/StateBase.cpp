#include "../Header/CameraData.h"

#include "../Header/CameraManager.h"
#include "../Header/SceneManager.h"
#include "../Header/StateBase.h"
#include "../Header/UtilCalc.h"

/*------------------------*/
/*【カメラステートベース】*/
/*------------------------*/
// カメラの共通設定をする
void IStateCamera::CommonSetCamera(CameraData cameraData, int& preThreeDFlag)
{
	if ((preThreeDFlag == -1) || ((preThreeDFlag == 1) != cameraData.threeDFlag))
	{
		if (cameraData.threeDFlag)
		{
			// カメラのクリッピング距離を設定。(カメラが映せる上限範囲)
			SetCameraNearFar(16.f, 3800.0f);

			// 背景の色を設定する
			SetBackgroundColor(cameraData.red, cameraData.green, cameraData.blue, cameraData.alpha);

			// Zバファに書き込む準備
			SetUseZBufferFlag(TRUE);
			SetWriteZBufferFlag(TRUE);

			// カメラ位置を反映する
			SetCameraPositionAndTarget_UpVecY(cameraData.position, cameraData.targetPosition);
		}
		else
		{
			// カメラのクリッピング距離を設定。(カメラが映せる上限範囲)
			//SetCameraNearFar(16.f, 3800.0f);

			// 背景の色を設定する
			SetBackgroundColor(cameraData.red, cameraData.green, cameraData.blue, cameraData.alpha);

			// Zバファに書き込む準備
			SetUseZBufferFlag(FALSE);
			SetWriteZBufferFlag(FALSE);
		}
	}
	else if (cameraData.threeDFlag)
	{
		// カメラ位置を反映する
		SetCameraPositionAndTarget_UpVecY(cameraData.position, cameraData.targetPosition);
	}
}

/*------------------------*/
/*【シーンステートベース】*/
/*------------------------*/

// 更新
SCENE IStateScene::Update(SceneManager* sceneManager)
{
	if (sceneManager->GetNextScene() != sceneManager->GetFSMScene()->GetCurrentState())
	{
		return sceneManager->GetNextScene();
	}

	return sceneManager->GetFSMScene()->GetCurrentState();
}