#include <map>

#include "Master.h"

#include "CameraManager.h"
#include "GameManager.h"
#include "FSM.h"
#include "LoadingManager.h"
#include "ObjectBases.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "StateBase.h"
#include "StateScene.h"
#include "UtilChange.h"

/*------------------------*/
/*【継承用有限状態マシン】*/
/*------------------------*/

template<typename subscript, typename state>
FSMBase<subscript, state>::FSMBase()
{
	mmStateMap.clear();
	mnCurrentState = (subscript) - 1;
	mnNextState = (subscript)0;
}

/*------------------------*/
/*【カメラ有限状態マシン】*/
/*------------------------*/

FSMCamera::FSMCamera()
: FSMBase()
{
}

// 実行中状態をセットする
void FSMCamera::SetCurrentState(CameraManager* cameraManager, int& preThreeDFlag)
{
	if (mnCurrentState != CAMERA_MODE::NONE)
	{
		mmStateMap[mnCurrentState]->OnExit(cameraManager, cameraManager->GetCameraData());
	}

	mnCurrentState = cameraManager->GetCameraData().cameraMode;
	mmStateMap[mnCurrentState]->OnEnter(cameraManager, cameraManager->GetCameraData(), preThreeDFlag);
}

// 初期化
void FSMCamera::Initilize(CameraManager* cameraManager, int id)
{
	mmStateMap[cameraManager->GetCameraData(id).cameraMode]->Initilize(cameraManager, cameraManager->GetCameraData());
}

// 更新
void FSMCamera::Update(CameraManager* cameraManager)
{
	mmStateMap[mnCurrentState]->Update(cameraManager, cameraManager->GetCameraData());
}

// 描画
void FSMCamera::Draw(CameraManager* cameraManager)
{
	mmStateMap[mnCurrentState]->Draw(cameraManager, cameraManager->GetCameraData());
}

/*------------------------------*/
/*【キャラクター有限状態マシン】*/
/*------------------------------*/

FSMCharacter::FSMCharacter()
: FSMBase()
{
}

// 実行中状態をセットする
void FSMCharacter::SetCurrentState(int id, CharacterBase* character)
{
	mnCurrentState = id;
	mmStateMap[mnCurrentState]->OnEnter(character);
}

// 更新
void FSMCharacter::Update(CharacterBase* character)
{
	int nextState = mmStateMap[mnCurrentState]->StateCheck(character);
	if (mnCurrentState != nextState)
	{
		mmStateMap[mnCurrentState]->OnExit(character);//現在のStateの終了処理
		mmStateMap[nextState]->OnEnter(character);//新しいStateの開始処理
		mnCurrentState = nextState;//新しいStateを設定
	}

	mmStateMap[mnCurrentState]->Update(character);
}

// 最終更新
void FSMCharacter::LastUpdate(CharacterBase* character)
{
	mmStateMap[mnCurrentState]->LastUpdate(character);
}

// 描画
void FSMCharacter::Draw(CharacterBase* character)
{
	mmStateMap[mnCurrentState]->Draw(character);
}

// 死亡
void FSMCharacter::Death(CharacterBase* character)
{
	mmStateMap[mnCurrentState]->Death(character);
}

// INPROGRESS: 作業中
/*----------*/
/*【モデルコントローラー有限状態マシン】
/*----------*/
FSMModelsController::FSMModelsController()
: FSMBase()
{
	mmSubStateMap.clear();
}

// 実行中状態をセットする
void FSMModelsController::SetCurrentState(ANIMATION_MODEL_TYPE id, ModelsControllerBase* modelsController)
{
//	mnCurrentState = modelsController->GetSubStateIndex();
//	mmStateMap[mnCurrentState][id]->OnEnter(modelsController, modelsController->GetAnimationData());	
}

// サブ状態マップのサイズを増やす
void FSMModelsController::IncreaseSubStateMapSize(int size)
{
	mmSubStateMap.resize(size);
}

// サブ状態マップに情報を設定
void FSMModelsController::SetSubStateMap(int subStateIndex, ANIMATION_MODEL_TYPE stateType, IStateModelsController* state)
{
	mmSubStateMap[subStateIndex][stateType] = state;
}

// サブ状態マップに情報を設定
void FSMModelsController::SetSubStateMap(int subStateIndex, std::map<ANIMATION_MODEL_TYPE, IStateModelsController*> subStateMap)
{
	mmSubStateMap[subStateIndex] = subStateMap;
}

// 更新
void FSMModelsController::Update(ModelsControllerBase* modelsController, std::vector<AnimationData>& animationDatas)
{
	//mmSubStateMap[mnCurrentState][modelsController->GetAnimationModelType()]->Update(modelsController, animationDatas);
}

// 描画
void FSMModelsController::Draw(ModelsControllerBase* modelsController)
{
}

/*------------------------*/
/*【シーン有限状態マシン】*/
/*------------------------*/

FSMScene::FSMScene()
: FSMBase()
{
}

// 実行中状態をセットする
void FSMScene::SetCurrentState(SCENE id, SceneManager* sceneManager)
{
	mnCurrentState = id;
	mmStateMap[UtilChange::SceneState(mnCurrentState)]->OnEnter(sceneManager);
}

// 更新
void FSMScene::Update(SceneManager* sceneManager)
{
	IStateScene* stateScene = mmStateMap[UtilChange::SceneState(mnCurrentState)];
	SCENE ret = stateScene->Update(sceneManager);
	if (mnCurrentState != ret)
	{
		Master::mpLoadingManager->SetLoadingFlag(LOADING_NUMBER::SCENE);
		stateScene->OnExit(sceneManager);
		Master::mpGameManager->GetObjectManager()->DeleteSetScene((SCENE)mnCurrentState);
		mnCurrentState = ret;
	}
}

// 次のシーンへ移動する
void FSMScene::NextScene(SceneManager* sceneManager)
{
	mmStateMap[UtilChange::SceneState(mnCurrentState)]->OnEnter(sceneManager);
}

// カメラID取得
int FSMScene::GetSceneCameraID()
{
	return mmStateMap[UtilChange::SceneState(mnCurrentState)]->GetSceneCameraID();
}

/*--------------------*/
/*【UI有限状態マシン】*/
/*--------------------*/

FSMUI::FSMUI()
: FSMBase()
{
}

// 実行中状態をセットする
void FSMUI::SetCurrentState(int id, UIBase* ui)
{
	mnCurrentState = id;
	mmStateMap[mnCurrentState]->OnEnter(ui);
}

// 更新
void FSMUI::Update(UIBase* ui)
{
	Init();

	if (mnCurrentState == mnNextState)
	{
		SetState(mmStateMap[mnCurrentState]->Update(ui), ui);
	}

	ui->CheckMouse();
	ui->CheckKeyboard();
	ui->CheckController();
	ui->CheckKeyboard_Controller();
}

// 決定
void FSMUI::Decision(UIBase* ui)
{
	if (mnCurrentState == mnNextState)
	{
		SetState(mmStateMap[mnCurrentState]->Decision(ui), ui);
	}
}

// 終了
void FSMUI::Cloce(UIBase* ui)
{
	mmStateMap[mnCurrentState]->Cloce(ui);
}

// マウス
void FSMUI::Mouse(UIBase* ui)
{
	if (mnCurrentState == mnNextState)
	{
		SetState(mmStateMap[mnCurrentState]->Mouse(ui), ui);
	}
}

// キーボード
void FSMUI::Keyboard(UIBase* ui)
{
	if (mnCurrentState == mnNextState)
	{
		SetState(mmStateMap[mnCurrentState]->Keyboard(ui), ui);
	}
}

// コントローラー
void FSMUI::Controller(UIBase* ui)
{
	if (mnCurrentState == mnNextState)
	{
		SetState(mmStateMap[mnCurrentState]->Controller(ui), ui);
	}
}

// キーボードとコントローラー
void FSMUI::Keyboard_Controller(UIBase* ui)
{
	if (mnCurrentState == mnNextState)
	{
		SetState(mmStateMap[mnCurrentState]->Keyboard_Controller(ui), ui);
	}
}

// 描画
void FSMUI::Draw(UIBase* ui)
{
	mmStateMap[mnCurrentState]->Draw(ui);
}

// 次のステートが現在のステートと違うならステート変更処理をする
void FSMUI::SetState(int nextState, UIBase* ui)
{
	if (mnCurrentState != nextState)
	{
		mmStateMap[mnCurrentState]->OnExit(ui);//現在のStateの終了処理
		mmStateMap[nextState]->OnEnter(ui);//新しいStateの開始処理
		mnNextState = nextState;//新しいStateを設定
	}
}