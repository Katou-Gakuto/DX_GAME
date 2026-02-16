#pragma once

#include "StateBase.h"

enum class ANIMATION_FACTORY_NUMBER;

class CharacterBase;

/*----------*/
/*【シーンステート共通処理用】
/*----------*/
class SceneStateProcess
{
protected:
	/*キャラクターモデル設定*/
	void CharacterModelSetting(CharacterBase* character, ANIMATION_FACTORY_NUMBER animationFactoryNumber);
};

/*--------------------------*/
/*【スタートシーンステート】*/
/*--------------------------*/
class StartScene : public IStateScene, public SceneStateProcess
{
private:
	bool mbStartFlag;

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
class TitleScene : public IStateScene, public SceneStateProcess
{
public:
	TitleScene();
	~TitleScene() = default;
	
	/*この状態に入った時の処理*/
	void OnEnter(SceneManager* sceneManager) override;
	/*この状態を出る時の処理*/
	void OnExit(SceneManager* sceneManager) override;
};

/*--------------------*/
/*【町シーンステート】*/
/*--------------------*/
class TownScene : public IStateScene, public SceneStateProcess
{
public:
	TownScene();
	~TownScene() = default;
	
	/*この状態に入った時の処理*/
	void OnEnter(SceneManager* sceneManager) override;
	/*この状態を出る時の処理*/
	void OnExit(SceneManager* sceneManager) override;
};

/*----------------------------*/
/*【ダンジョンシーンステート】*/
/*----------------------------*/
class DungeonScene : public IStateScene, public SceneStateProcess
{
public:
	DungeonScene();
	~DungeonScene() = default;
	
	/*この状態に入った時の処理*/
	void OnEnter(SceneManager* sceneManager) override;
	/*この状態を出る時の処理*/
	void OnExit(SceneManager* sceneManager) override;
};

/*------------------------*/
/*【バトルシーンステート】*/
/*------------------------*/
class BattleScene : public IStateScene, public SceneStateProcess
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
class ResultScene : public IStateScene, public SceneStateProcess
{
public:
	ResultScene();
	~ResultScene() = default;
	
	/*この状態に入った時の処理*/
	void OnEnter(SceneManager* sceneManager) override;
	/*この状態を出る時の処理*/
	void OnExit(SceneManager* sceneManager) override;
};

/*--------------------------------*/
/*【ゲームオーバーシーンステート】*/
/*--------------------------------*/
class GameOverScene : public IStateScene, public SceneStateProcess
{
public:
	GameOverScene();
	~GameOverScene() = default;
	
	/*この状態に入った時の処理*/
	void OnEnter(SceneManager* sceneManager) override;
	/*この状態を出る時の処理*/
	void OnExit(SceneManager* sceneManager) override;
};