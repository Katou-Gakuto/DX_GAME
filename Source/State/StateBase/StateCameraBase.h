#pragma once
#include <vector>

#include "CameraData.h"

#include "StateBase.h"

enum class CAMERA_MODE;

class CameraManager;

/*------------------------*/
/*【カメラステートベース】*/
/*------------------------*/
class IStateCamera : public StateBase<CAMERA_MODE, CameraData>
{
protected:
	// カメラ1フレーム移動量
	const float CAMERA_ONE_FRAME_AMOUNT = 3.0f;

	// 前の3Dフラグ(-1:初期値、0:2D、1:3D)
	static int mnPreThreeDFlag;

public:
	IStateCamera(std::vector<STATE_CHANGE_CRITERIA_DATA<CAMERA_MODE, CameraData>> stateChangeCriterias, CAMERA_MODE stateNumber)
	: StateBase(stateChangeCriterias, stateNumber)
	{
	}
	~IStateCamera() = default;

	// /*この状態に入った時の処理*/
	// virtual void OnEnter(CameraManager* cameraManager, CameraData cameraData, int& preThreeDFlag) = 0;
	// /*この状態を出る時の処理*/
	// virtual void OnExit(CameraManager* cameraManager, CameraData cameraData) = 0;

	/// <summary>初期化</summary>
	//virtual void Initilize(STATE_CAMERA_DATA* cameraManager) = 0;
	/*初期化*/
	//virtual void Initilize(CameraManager* cameraManager, CameraData cameraData) = 0;

	/*更新*/
	virtual void Update(CameraData* cameraManager) = 0;

	/*描画*/
	virtual void Draw(CameraData* cameraManager) = 0;

protected:
	/*カメラの共通設定をする*/
	void CommonSetCamera(CameraData *cameraData);

	/*カメラポジション設置*/
	void SetCameraPos(VECTOR cameraPos, VECTOR cameraLookPos);
};