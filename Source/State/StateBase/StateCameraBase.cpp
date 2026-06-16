#include "CameraData.h"

#include "DxLib.h"

#include "Master.h"

#include "CameraManager.h"
#include "ResourceManager.h"
#include "StateCameraBase.h"

// TODO: ここでZバッファフラグ切っても変わらないか確認
/*------------------------*/
/*【カメラステートベース】*/
/*------------------------*/
int IStateCamera::mnPreThreeDFlag = -1;
// カメラの共通設定をする
void IStateCamera::CommonSetCamera(CameraData *cameraData)
{
	if ((mnPreThreeDFlag == -1) || ((mnPreThreeDFlag == 1) != cameraData->threeDFlag))
	{
		if (cameraData->threeDFlag)
		{
			// カメラのクリッピング距離を設定。(カメラが映せる上限範囲)
			SetCameraNearFar(16.0f, /*/9999999.0f);//*/3800.0f);

			// 背景の色を設定する
			SetBackgroundColor(cameraData->red, cameraData->green, cameraData->blue, cameraData->alpha);

			// Zバファに書き込む準備
			SetUseZBufferFlag(TRUE);
			SetWriteZBufferFlag(TRUE);

			// カメラ位置を反映する
			SetCameraPos(cameraData->position, cameraData->targetPosition);
		}
		else
		{
			// カメラのクリッピング距離を設定。(カメラが映せる上限範囲)
			//SetCameraNearFar(16.f, 3800.0f);

			// 背景の色を設定する
			SetBackgroundColor(cameraData->red, cameraData->green, cameraData->blue, cameraData->alpha);

			// Zバファに書き込む準備
			SetUseZBufferFlag(FALSE);
			SetWriteZBufferFlag(FALSE);
		}
	}
	else if (cameraData->threeDFlag)
	{
		// カメラ位置を反映する
		SetCameraPos(cameraData->position, cameraData->targetPosition);
	}
}

/*カメラポジション設置*/
void IStateCamera::SetCameraPos(VECTOR cameraPos, VECTOR cameraLookPos)
{
	Master::mpResourceManager->Set3DListenerPosition(cameraPos, cameraLookPos);

	// カメラ位置を反映する
	SetCameraPositionAndTarget_UpVecY(cameraPos, cameraLookPos);
}