#pragma once

#include "StateBase.h"

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

/*--------------------------*/
/*【タイトルシーンステート】*/
/*--------------------------*/
class TitleScene : public IStateScene
{
public:
	TitleScene();
	~TitleScene() = default;
	
	/*この状態に入った時の処理*/
	void OnEnter(SceneManager* sceneManager) override;
	/*この状態を出る時の処理*/
	void OnExit(SceneManager* sceneManager) override;
};

/*--------------------------*/
/*【町シーンステート】*/
/*--------------------------*/
class TownScene : public IStateScene
{
public:
	TownScene();
	~TownScene() = default;
	
	/*この状態に入った時の処理*/
	void OnEnter(SceneManager* sceneManager) override;
	/*この状態を出る時の処理*/
	void OnExit(SceneManager* sceneManager) override;
};

/*--------------------------*/
/*【ダンジョンシーンステート】*/
/*--------------------------*/
class DungeonScene : public IStateScene
{
public:
	DungeonScene();
	~DungeonScene() = default;
	
	/*この状態に入った時の処理*/
	void OnEnter(SceneManager* sceneManager) override;
	/*この状態を出る時の処理*/
	void OnExit(SceneManager* sceneManager) override;
};

/*--------------------------*/
/*【バトルシーンステート】*/
/*--------------------------*/
class BattleScene : public IStateScene
{
public:
	BattleScene();
	~BattleScene() = default;
	
	/*この状態に入った時の処理*/
	void OnEnter(SceneManager* sceneManager) override;
	/*この状態を出る時の処理*/
	void OnExit(SceneManager* sceneManager) override;
};

/*--------------------------*/
/*【リザルトシーンステート】*/
/*--------------------------*/
class ResultScene : public IStateScene
{
public:
	ResultScene();
	~ResultScene() = default;
	
	/*この状態に入った時の処理*/
	void OnEnter(SceneManager* sceneManager) override;
	/*この状態を出る時の処理*/
	void OnExit(SceneManager* sceneManager) override;
};