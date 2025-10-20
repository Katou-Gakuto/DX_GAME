#pragma once

#include "StateBase.h"

class SceneManager;

/*------------------------*/
/*【継承用シーンステート】*/
/*------------------------*/
class IStateScene : public StateBase
{
public:
	IStateScene() = default;
	virtual ~IStateScene() = default;

	/*この状態に入った時の処理*/
	virtual void OnEnter(SceneManager* sceneManager) = 0;
	/*この状態を出る時の処理*/
	virtual void OnExit(SceneManager* sceneManager) = 0;

	/*更新*/
	int Update(SceneManager* sceneManager);
};

/*------------------------*/
/*【削除用シーンステート】*/
/*------------------------*/
class DeleteStateScene : public IStateScene { public: DeleteStateScene() = default; ~DeleteStateScene() = default; void OnEnter(SceneManager* sceneManager) override {} void OnExit(SceneManager* sceneManager) override {} };

/*--------------------------*/
/*【スタートシーンステート】*/
/*--------------------------*/
class StartScene : public IStateScene
{
public:
	StartScene();
	~StartScene() = default;
	
	/*この状態に入った時の処理*/
	void OnEnter(SceneManager* sceneManager) override;
	/*この状態を出る時の処理*/
	void OnExit(SceneManager* sceneManager) override;
};