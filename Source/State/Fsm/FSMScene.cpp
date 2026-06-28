#include <map>

#include "Master.h"

#include "FSM.h"
#include "FSMScene.h"
#include "LoadingManager.h"
#include "SceneManager.h"
#include "StateSceneBase.h"
#include "UtilChange.h"

// TODO: シーン関連シーン周辺を見ながら再考
/*------------------------*/
/*【シーン有限状態マシン】*/
/*------------------------*/

FSMScene::FSMScene()
: FSMBase()
{
}

// 実行中状態をセットする
void FSMScene::SetCurrentState(SCENE id, SceneManager* sceneManager, SceneManager* preSceneManager)
{
	mPreState = mCurrentState;
	mCurrentState = id;
	mmStateMap[UtilChange::SceneState(mCurrentState)]->OnEnter(sceneManager, mPreState);
}

// 更新
void FSMScene::Update(SceneManager* sceneManager)
{
	IStateScene* stateScene = mmStateMap[UtilChange::SceneState(mCurrentState)];
	SCENE ret = sceneManager->GetNextScene();
	if (mCurrentState != ret)
	{
		Master::mpLoadingManager->SetLoadingFlag(LOADING_NUMBER::SCENE);
		sceneManager->SetPreScene((SCENE)mCurrentState);
		mCurrentState = ret;
	}
}

// // 次のシーンへ移動する
// void FSMScene::NextScene(SceneManager* sceneManager)
// {
// 	mmStateMap[UtilChange::SceneState(mCurrentState)]->OnEnter(sceneManager);
// }

// カメラID取得
int FSMScene::GetSceneCameraID()
{
	return mmStateMap[UtilChange::SceneState(mCurrentState)]->GetSceneCameraID();
}