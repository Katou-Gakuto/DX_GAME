#pragma once
#include <vector>

#include "SceneEnum.h"

#include "StateBase.h"

class MapManager;
class SceneManager;
class TargetManager;

/*------------------------*/
/*【シーンステートベース】*/
/*------------------------*/
class IStateScene : public StateBase<SCENE, SceneManager>
{
protected:
	// ターゲットマネージャー
	TargetManager* mpTargetManager;
	
	// マップマネージャー
	MapManager* mpMapManager;

	// シーンカメラID
	int mnSceneCameraID;

public:
	IStateScene(std::vector<STATE_CHANGE_CRITERIA_DATA<SCENE, SceneManager>> stateChangeCriterias, SCENE stateNumber);
	virtual ~IStateScene() = default;

	// /*この状態に入った時の処理*/
	// virtual void OnEnter(SceneManager* sceneManager) = 0;
	// /*この状態を出る時の処理*/
	// virtual void OnExit(SceneManager* sceneManager) = 0;
	/// <summary>初期化</summary>
	virtual void Initilize(SceneManager* sceneManager){}

	/*ステージ状態に入った時の共通処理*/
	void StageOnEnter(SceneManager* sceneManager);

	// /*更新*/
	// SCENE Update(SceneManager* sceneManager);

	/*シーンカメラID*/
	inline int GetSceneCameraID() const { return mnSceneCameraID; }
};