#include "../Header/FSM.h"
#include "../Header/SceneManager.h"
#include "../Header/StateBase.h"
#include "../Header/StateScene.h"
#include "../Header/TitleUI.h"

/*--------------------------*/
/*【スタートシーンステート】*/
/*--------------------------*/
StartScene::StartScene()
{
	mnStateNumber = (int)SCENE::START;
}

void StartScene::OnEnter(SceneManager* sceneManager)
{
	sceneManager->SetNextScene(SCENE::TITLE);
}
void StartScene::OnExit(SceneManager* sceneManager)
{
}


/*--------------------------*/
/*【タイトルシーンステート】*/
/*--------------------------*/
TitleScene::TitleScene()
{
	mnStateNumber = (int)SCENE::TITLE;
}

void TitleScene::OnEnter(SceneManager* sceneManager)
{
	TitleUI* title = new TitleUI();
	title->Initilize();
}
void TitleScene::OnExit(SceneManager* sceneManager)
{
}


/*--------------------------*/
/*【町シーンステート】*/
/*--------------------------*/
TownScene::TownScene()
{
	mnStateNumber = (int)SCENE::TOWN;
}

void TownScene::OnEnter(SceneManager* sceneManager)
{
}
void TownScene::OnExit(SceneManager* sceneManager)
{
}


/*----------------------------*/
/*【ダンジョンシーンステート】*/
/*----------------------------*/
DungeonScene::DungeonScene()
{
	mnStateNumber = (int)SCENE::DUNGEON;
}

void DungeonScene::OnEnter(SceneManager* sceneManager)
{
}
void DungeonScene::OnExit(SceneManager* sceneManager)
{
}


/*--------------------------*/
/*【バトルシーンステート】*/
/*--------------------------*/
BattleScene::BattleScene()
{
	mnStateNumber = (int)SCENE::BATTLE;
}

void BattleScene::OnEnter(SceneManager* sceneManager)
{
}
void BattleScene::OnExit(SceneManager* sceneManager)
{
}


/*--------------------------*/
/*【リザルトシーンステート】*/
/*--------------------------*/
ResultScene::ResultScene()
{
	mnStateNumber = (int)SCENE::RESULT;
}

void ResultScene::OnEnter(SceneManager* sceneManager)
{
}
void ResultScene::OnExit(SceneManager* sceneManager)
{
}