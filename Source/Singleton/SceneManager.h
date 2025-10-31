#pragma once

#include "SceneEnum.h"

#include "FSM.h"
#include "StateScene.h"

class SceneManager
{
private:
	// 有限状態マシン
	FSMScene* mpFSMScene;
	// 次のシーン
	SCENE meNextScene;

public:
	SceneManager();
	~SceneManager();

	/*初期化*/
	void Initilize();
	/*更新*/
	void Update();
	/*次のシーンへ移動する*/
	void NextScene();

	/*--------------------------------------------------
	* 【設定】
	*/
	/*次のシーンを設定*/
	void SetNextScene(SCENE nextScene) { meNextScene = nextScene; }
	
	/*--------------------------------------------------
	* 【取得】
	*/
	SCENE GetNowScene() const { return (SCENE)mpFSMScene->GetCurrentState(); }
	/*次のシーンを取得*/
	SCENE GetNextScene() const { return meNextScene; }

	/*有限状態マシン取得*/
	FSMScene* GetFSMScene() const { return mpFSMScene; }
};