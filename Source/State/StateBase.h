#pragma once
#include "AnimationData.h"
#include "CameraData.h"

enum class MODEL_TYPE;
enum class CAMERA_MODE;
enum class SCENE;

struct AnimationStateData;

class AnimationBase;
class CameraManager;
class CharacterBase;
class MapManager;
class ModelBase;
class SceneManager;
class TargetManager;
class UIBase;

/*------------------*/
/*【ステートベース】*/
/*------------------*/
template<typename number>
class StateBase
{
protected:
	// ステートナンバー
	number mStateNumber = (number) - 1;
public:
	StateBase() = default;
	virtual ~StateBase() = default;

	inline number GetStateNumber() const { return mStateNumber; }
};

/*------------------------*/
/*【カメラステートベース】*/
/*------------------------*/
class IStateCamera : public StateBase<CAMERA_MODE>
{
public:
	IStateCamera() = default;
	virtual ~IStateCamera() = default;

	/*この状態に入った時の処理*/
	virtual void OnEnter(CameraManager* cameraManager, CameraData cameraData, int& preThreeDFlag) = 0;
	/*この状態を出る時の処理*/
	virtual void OnExit(CameraManager* cameraManager, CameraData cameraData) = 0;

	/*初期化*/
	virtual void Initilize(CameraManager* cameraManager, CameraData cameraData) = 0;

	/*更新*/
	virtual void Update(CameraManager* cameraManager, CameraData cameraData) = 0;

	/*描画*/
	virtual void Draw(CameraManager* cameraManager, CameraData cameraData) = 0;

protected:
	/*カメラの共通設定をする*/
	void CommonSetCamera(CameraData cameraData, int& preThreeDFlag);
};

/*------------------------------*/
/*【キャラクターステートベース】*/
/*------------------------------*/
class IStateCharacter : public StateBase<int>
{
public:
	IStateCharacter() = default;
	virtual ~IStateCharacter() = default;

	/*この状態に入った時の処理*/
	virtual void OnEnter(CharacterBase* character) = 0;
	/*この状態を出る時の処理*/
	virtual void OnExit(CharacterBase* character) = 0;

	/*ステート変更確認*/
	virtual int StateCheck(CharacterBase* character) = 0;
	/*更新*/
	virtual void Update(CharacterBase* character) = 0;
	/*最終更新*/
	virtual void LastUpdate(CharacterBase* character) = 0;

	/*描画*/
	virtual void Draw(CharacterBase* character) = 0;

	/*死亡*/
	virtual void Death(CharacterBase* character) = 0;
};

/*----------*/
/*【アニメーションステートベース】
/*----------*/
class IStateAnimation : public StateBase<MODEL_TYPE>
{
public:
	IStateAnimation() = default;
	virtual ~IStateAnimation() = default;
	/// <summary>この状態に入った時の処理</summary>
	virtual void OnEnter(AnimationBase* animation, AnimationDatas animationDatas, MODEL_TYPE oldModelType) = 0;
	/// <summary>この状態を出る時の処理</summary>
	virtual void OnExit(AnimationBase* animation, AnimationDatas animationDatas, MODEL_TYPE newModelType) = 0;
	
	/// <summary>更新</summary>
	virtual void Update(AnimationBase* animation, AnimationDatas animationDatas) = 0;
};

/*----------*/
/*【アニメション操作ステートベース】
/*----------*/
class IStateAnimationController : public StateBase<ANIMATION_TYPE>
{
public:
	IStateAnimationController() = default;
	virtual ~IStateAnimationController() = default;
	
	/// <summary>この状態に入った時の処理</summary>
	virtual void OnEnter(AnimationBase* animation, ANIMATION_TYPE oldState) = 0;
	/// <summary>この状態を出る時の処理</summary>
	virtual void OnExit(AnimationBase* animation, ANIMATION_TYPE newState) = 0;

	/// <summary>ステート変更確認</summary>
	virtual ANIMATION_TYPE CheckState(AnimationBase* animation, ANIMATION_TYPE nextState) = 0;
};

/*------------------------*/
/*【シーンステートベース】*/
/*------------------------*/
class IStateScene : public StateBase<SCENE>
{
protected:
	// ターゲットマネージャー
	TargetManager* mpTargetManager;
	
	// マップマネージャー
	MapManager* mpMapManager;

	// シーンカメラID
	int mnSceneCameraID;

public:
	IStateScene();
	virtual ~IStateScene() = default;

	/*この状態に入った時の処理*/
	virtual void OnEnter(SceneManager* sceneManager) = 0;
	/*この状態を出る時の処理*/
	virtual void OnExit(SceneManager* sceneManager) = 0;

	/*ステージ状態に入った時の共通処理*/
	void StageOnEnter(SceneManager* sceneManager);

	/*更新*/
	SCENE Update(SceneManager* sceneManager);

	/*シーンカメラID*/
	inline int GetSceneCameraID() const { return mnSceneCameraID; }
};

/*--------------------*/
/*【UIステートベース】*/
/*--------------------*/
class IStateUI : public StateBase<int>
{
public:
	IStateUI() = default;
	virtual ~IStateUI() = default;

	/// <summary>終了</summary>
	virtual void Finalize() {}

	/*この状態に入った時の処理*/
	virtual void OnEnter(UIBase* ui) = 0;
	/*この状態を出る時の処理*/
	virtual void OnExit(UIBase* ui) = 0;

	/*更新*/
	virtual int Update(UIBase* ui) { return mStateNumber; }

	/*決定*/
	virtual int Decision(UIBase* ui) { return mStateNumber; }
	/*終了*/
	virtual int Cloce(UIBase* ui) { return mStateNumber; }

	/*マウス*/
	virtual int Mouse(UIBase* ui) { return mStateNumber; }
	/*キーボード*/
	virtual int Keyboard(UIBase* ui) { return mStateNumber; }
	/*コントローラー*/
	virtual int Controller(UIBase* ui) { return mStateNumber; }
	/*キーボードとコントローラー*/
	virtual int Keyboard_Controller(UIBase* ui) { return mStateNumber; }

	/*描画*/
	virtual void Draw(UIBase* ui) = 0;
};