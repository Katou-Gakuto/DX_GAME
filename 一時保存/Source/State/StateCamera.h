#pragma once
#include "CameraData.h"

#include "StateBase.h"

/*--------------------*/
/*【固定視点ステート】*/
/*--------------------*/
class StateFixedCamera : public IStateCamera
{
public:
	StateFixedCamera();

	/*この状態に入った時の処理*/
	void OnEnter(CameraManager* cameraManager, CameraData cameraData, int& preThreeDFlag) override;
	/*この状態を出る時の処理*/
	void OnExit(CameraManager* cameraManager, CameraData cameraData) override;

	/*初期化*/
	void Initilize(CameraManager* cameraManager, CameraData cameraData) override;

	/*更新*/
	void Update(CameraManager* cameraManager, CameraData cameraData) override;

	/*描画*/
	void Draw(CameraManager* cameraManager, CameraData cameraData) override;
};

/*--------------------*/
/*【移動視点ステート】*/
/*--------------------*/
class StateMoveCamera : public IStateCamera
{
public:
	StateMoveCamera();

	/*この状態に入った時の処理*/
	void OnEnter(CameraManager* cameraManager, CameraData cameraData, int& preThreeDFlag) override;
	/*この状態を出る時の処理*/
	void OnExit(CameraManager* cameraManager, CameraData cameraData) override;

	/*初期化*/
	void Initilize(CameraManager* cameraManager, CameraData cameraData) override;

	/*更新*/
	void Update(CameraManager* cameraManager, CameraData cameraData) override;

	/*描画*/
	void Draw(CameraManager* cameraManager, CameraData cameraData) override;
};

/*----------------------------*/
/*【キャラクター視点ステート】*/
/*----------------------------*/
class StateCharacterCamera : public IStateCamera
{
public:
	StateCharacterCamera();

	/*この状態に入った時の処理*/
	void OnEnter(CameraManager* cameraManager, CameraData cameraData, int& preThreeDFlag) override;
	/*この状態を出る時の処理*/
	void OnExit(CameraManager* cameraManager, CameraData cameraData) override;

	/*初期化*/
	void Initilize(CameraManager* cameraManager, CameraData cameraData) override;

	/*更新*/
	void Update(CameraManager* cameraManager, CameraData cameraData) override;

	/*描画*/
	void Draw(CameraManager* cameraManager, CameraData cameraData) override;
};

/*--------------------------*/
/*【プレイヤー視点ステート】*/
/*--------------------------*/
class StatePlayerCamera : public IStateCamera
{
private:
	// 上方向最大アングル
	const float UP_MAX_ANGLE = 70.0f;
	// 下方向最大アングル
	const float DOWN_MAX_ANGLE = 0.0f;

public:
	StatePlayerCamera();

	/*この状態に入った時の処理*/
	void OnEnter(CameraManager* cameraManager, CameraData cameraData, int& preThreeDFlag) override;
	/*この状態を出る時の処理*/
	void OnExit(CameraManager* cameraManager, CameraData cameraData) override;

	/*初期化*/
	void Initilize(CameraManager* cameraManager, CameraData cameraData) override;

	/*更新*/
	void Update(CameraManager* cameraManager, CameraData cameraData) override;

	/*描画*/
	void Draw(CameraManager* cameraManager, CameraData cameraData) override;
};