#include <map>

#include "../Header/Master.h"

#include "../Header/EndManager.h"
#include "../Header/FSM.h"
#include "../Header/LoadingManager.h"
#include "../Header/SceneManager.h"
#include "../Header/StateBase.h"
#include "../Header/StateScene.h"

/*------------------------*/
/*【継承用有限状態マシン】*/
/*------------------------*/

FSMBase::FSMBase()
{
	mmStateMap.clear();
	mnCurrentState = 0;
	mnNextState = 0;
}
FSMBase::~FSMBase()
{
	//mapコンテナの解放
	for (const auto& pair : mmStateMap)
		delete (pair.second);//登録されたStateのインスタンスを削除する

	mmStateMap.clear();
}

// ステート登録
void FSMBase::RegisterState(const int id, StateBase* state)
{
	mmStateMap[id] = state;
}
// ステート登録
void FSMBase::RegisterState(StateBase* state)
{
	mmStateMap[state->GetStateNumber()] = state;
}

// 初期化
void FSMBase::Init()
{
	mnCurrentState = mnNextState;
}

/*------------------------*/
/*【シーン有限状態マシン】*/
/*------------------------*/

FSMScene::FSMScene()
{
}

// 実行中状態をセットする
void FSMScene::SetCurrentState(int id, SceneManager* sceneManager)
{
	mnCurrentState = id;
	GetState(mmStateMap[mnCurrentState])->OnEnter(sceneManager);
}

// 更新
void FSMScene::Update(SceneManager* sceneManager)
{
	IStateScene* stateScene = GetState(mmStateMap[mnCurrentState]);
	int ret = stateScene->Update(sceneManager);
	if (mnCurrentState != ret)
	{
		Master::mpLoadingManager->SetLoadingFlag(LOADING_NUMBER::SCENE);
		stateScene->OnExit(sceneManager);
		mnCurrentState = ret;
	}
}

// 次のシーンへ移動する
void FSMScene::NextScene(SceneManager* sceneManager)
{
	GetState(mmStateMap[mnCurrentState])->OnEnter(sceneManager);
}

// ステートを変換する
IStateScene* FSMScene::GetState(StateBase* state)
{
	IStateScene* sceneState = dynamic_cast<IStateScene*>(state);
	if (sceneState != nullptr)
	{
		return sceneState;
	}

	sceneState = new DeleteStateScene();
	Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::FSM_FLAG);
	Master::mpEndManager->SetDeleteObject((void*)sceneState);
	return sceneState;
}