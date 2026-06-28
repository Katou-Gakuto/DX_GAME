#pragma once

#include "FSM.h"
#include "StateSceneBase.h"

/*----------*/
/*【シーン有限状態マシン】*/
/*----------*/
class FSMScene : public FSMBase<IStateScene, SCENE, SceneManager>
{
public:
	FSMScene();

	/*実行中状態をセットする*/
	void SetCurrentState(SCENE id, SceneManager* sceneManager, SceneManager* preSceneManager = nullptr) override;

	/*更新*/
	void Update(SceneManager* sceneManager);

	/*次のシーンへ移動する*/
	void NextScene(SceneManager* sceneManager);

	/*カメラID取得*/
	int GetSceneCameraID();

	/*ステートマップ取得*/
	inline std::map<SCENE, IStateScene*> GetStateMap() { return mmStateMap; }
};