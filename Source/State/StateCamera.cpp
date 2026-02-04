#include "CameraData.h"

#include "Master.h"

#include "CameraManager.h"
#include "GameManager.h"
#include "KeyState.h"
#include "ObjectBases.h"
#include "StateBase.h"
#include "StateCamera.h"
#include "StopManager.h"
#include "UtilCalc.h"


/*--------------------*/
/*【固定視点ステート】*/
/*--------------------*/
StateFixedCamera::StateFixedCamera()
{
	mStateNumber = CAMERA_MODE::FIXED;
}

// この状態に入った時の処理
void StateFixedCamera::OnEnter(CameraManager* cameraManager, CameraData cameraData, int& preThreeDFlag)
{
	CommonSetCamera(cameraData, preThreeDFlag);
}

// この状態を出る時の処理
void StateFixedCamera::OnExit(CameraManager* cameraManager, CameraData cameraData)
{
}

// 初期化
void StateFixedCamera::Initilize(CameraManager* cameraManager, CameraData cameraData)
{
}

// 更新
void StateFixedCamera::Update(CameraManager* cameraManager, CameraData cameraData)
{
}

// 描画
void StateFixedCamera::Draw(CameraManager* cameraManager, CameraData cameraData)
{
}


/*----------------------------*/
/*【キャラクター視点ステート】*/
/*----------------------------*/
StateCharacterCamera::StateCharacterCamera()
{
	mStateNumber = CAMERA_MODE::CHARACTER;
}

// この状態に入った時の処理
void StateCharacterCamera::OnEnter(CameraManager* cameraManager, CameraData cameraData, int& preThreeDFlag)
{
	CommonSetCamera(cameraData, preThreeDFlag);
}

// この状態を出る時の処理
void StateCharacterCamera::OnExit(CameraManager* cameraManager, CameraData cameraData)
{
}

// 初期化
void StateCharacterCamera::Initilize(CameraManager* cameraManager, CameraData cameraData)
{

}

// 更新
void StateCharacterCamera::Update(CameraManager* cameraManager, CameraData cameraData)
{
}

// 描画
void StateCharacterCamera::Draw(CameraManager* cameraManager, CameraData cameraData)
{
	// カメラ位置を反映する
	SetCameraPositionAndTarget_UpVecY(
		VAdd(VAdd(VScale(UtilCalc::VSignInversion(cameraData.targetCharacter->GetVec()), cameraData.cameraDistance), cameraData.targetCharacter->GetPos()), cameraData.plusPosition),
		VAdd(cameraData.targetCharacter->GetPos(), cameraData.plusPosition)
	);
}


/*--------------------------*/
/*【プレイヤー視点ステート】*/
/*--------------------------*/
StatePlayerCamera::StatePlayerCamera()
{
	mStateNumber = CAMERA_MODE::PLAYER;
}

// この状態に入った時の処理
void StatePlayerCamera::OnEnter(CameraManager* cameraManager, CameraData cameraData, int& preThreeDFlag)
{
	CommonSetCamera(cameraData, preThreeDFlag);
}

// この状態を出る時の処理
void StatePlayerCamera::OnExit(CameraManager* cameraManager, CameraData cameraData)
{
}

// 初期化
void StatePlayerCamera::Initilize(CameraManager* cameraManager, CameraData cameraData)
{
}

// 更新
void StatePlayerCamera::Update(CameraManager* cameraManager, CameraData cameraData)
{
	if (Master::mpStopManager->GetStopFlag(STOP_FLAG_TYPE::GAME_OBJECT))
	{
		// カメラの設置だけやる
		if (Master::mpStopManager->GetStopFlag(STOP_FLAG_TYPE::NODE))
		{
			cameraData.position = UtilCalc::VSphericalMovePos(cameraData.cameraDistance, UtilCalc::VRadChange(cameraData.angle));
			cameraManager->SetCameraData(cameraData);
		}

		return;
	}

	KeyState* keyState = Master::mpKeyState;

	if (keyState->GetWordKey_Board(KEY_BOARD_WORD::ARROW_LEFT))
	{
		cameraData.angle.y += 3.0f;
		if (cameraData.angle.y >= 180.0f)
		{
			cameraData.angle.y -= 360.0f;
		}

	}
	if (keyState->GetWordKey_Board(KEY_BOARD_WORD::ARROW_RIGHT))
	{
		cameraData.angle.y -= 3.0f;
		if (cameraData.angle.y <= (-180.0f))
		{
			cameraData.angle.y += 360.0f;
		}
	}

	if (keyState->GetWordKey_Board(KEY_BOARD_WORD::ARROW_UP))
	{
		cameraData.angle.x += 3.0f;
		if (cameraData.angle.x >= 70.0f)
		{
			cameraData.angle.x = 70.0f;
		}
	}
	if (keyState->GetWordKey_Board(KEY_BOARD_WORD::ARROW_DOWN))
	{
		cameraData.angle.x -= 3.0f;
		if (cameraData.angle.x <= 0.0f)
		{
			cameraData.angle.x = 0.0f;
		}
	}

	cameraData.position = UtilCalc::VSphericalMovePos(cameraData.cameraDistance, UtilCalc::VRadChange(cameraData.angle));

	cameraManager->SetCameraData(cameraData);
}

// 描画
void StatePlayerCamera::Draw(CameraManager* cameraManager, CameraData cameraData)
{
	// カメラ位置を反映する
	SetCameraPositionAndTarget_UpVecY(
		VAdd(VAdd(cameraData.position, cameraData.targetCharacter->GetPos()), cameraData.plusPosition),
		VAdd(cameraData.targetCharacter->GetPos(), cameraData.plusPosition)
	);
}