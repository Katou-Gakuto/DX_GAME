#pragma once

#include "GameDataEnum.h"
#include "GameDatas.h"

#include "StateSceneBase.h"

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

	/*プレイヤーポジションデータ設定*/
	void SetPlayerPosData(PLAYER_DATA* playerData, DATA_SCENE dataScene, SCENE scene);
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
	void OnEnter(SceneManager* sceneManager, SCENE preScene) override;
	/*この状態を出る時の処理*/
	void OnExit(SceneManager* sceneManager, SCENE newScene) override;
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
	void OnEnter(SceneManager* sceneManager, SCENE preScene) override;
	/*この状態を出る時の処理*/
	void OnExit(SceneManager* sceneManager, SCENE newScene) override;
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
	void OnEnter(SceneManager* sceneManager, SCENE preScene) override;
	/*この状態を出る時の処理*/
	void OnExit(SceneManager* sceneManager, SCENE newScene) override;
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
	void OnEnter(SceneManager* sceneManager, SCENE preScene) override;
	/*この状態を出る時の処理*/
	void OnExit(SceneManager* sceneManager, SCENE newScene) override;
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
	void OnEnter(SceneManager* sceneManager, SCENE preScene) override;
	/*この状態を出る時の処理*/
	void OnExit(SceneManager* sceneManager, SCENE newScene) override;
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
	void OnEnter(SceneManager* sceneManager, SCENE preScene) override;
	/*この状態を出る時の処理*/
	void OnExit(SceneManager* sceneManager, SCENE newScene) override;
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
	void OnEnter(SceneManager* sceneManager, SCENE preScene) override;
	/*この状態を出る時の処理*/
	void OnExit(SceneManager* sceneManager, SCENE newScene) override;
};

/*------------------------------*/
/*【ゲームループシーンステート】*/
/*------------------------------*/
class GameLoopScene : public IStateScene, public SceneStateProcess
{
public:
	GameLoopScene();
	~GameLoopScene() = default;
	
	/*この状態に入った時の処理*/
	void OnEnter(SceneManager* sceneManager, SCENE preScene) override;
	/*この状態を出る時の処理*/
	void OnExit(SceneManager* sceneManager, SCENE newScene) override;
};

/*------------------------------*/
/*【バトルループシーンステート】*/
/*------------------------------*/
class BattleLoopScene : public IStateScene, public SceneStateProcess
{
public:
	BattleLoopScene();
	~BattleLoopScene() = default;
	
	/*この状態に入った時の処理*/
	void OnEnter(SceneManager* sceneManager, SCENE preScene) override;
	/*この状態を出る時の処理*/
	void OnExit(SceneManager* sceneManager, SCENE newScene) override;
};

/*------------------------------*/
/*【ゲームクリアシーンステート】*/
/*------------------------------*/
class GameClearScene : public IStateScene, public SceneStateProcess
{
public:
	GameClearScene();
	~GameClearScene() = default;

	/*この状態に入った時の処理*/
	void OnEnter(SceneManager* sceneManager, SCENE preScene) override;
	/*この状態を出る時の処理*/
	void OnExit(SceneManager* sceneManager, SCENE newScene) override;
};