#include "Master.h"

#include "FadeManager.h"
#include "SceneManager.h"
#include "UtilFactorys.h"

SceneManager::SceneManager()
: mpFSMScene(nullptr)
, meNextScene(SCENE::START)
{

}
SceneManager::~SceneManager()
{
	delete mpFSMScene;
}

// 初期化
void SceneManager::Initilize()
{
	mpFSMScene = UtilFactorys::FSMSceneFactory(this);
}

// 更新
void SceneManager::Update()
{
	mpFSMScene->Update(this);
}

// 次のシーンへ移動する
void SceneManager::NextScene()
{
	mpFSMScene->NextScene(this);
}

// 次のシーンを設定
void SceneManager::SetNextScene(SCENE nextScene)
{
	Master::mpFadeManager->FadeOut();
	meNextScene = nextScene;
}