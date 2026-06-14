#include <algorithm>
#include <map>
#include <vector>

#include "AnimationEnum.h"
#include "DotWeenEnum.h"
#include "StateEnum.h"
#include "AnimationData.h"
#include "DotWeenData.h"

#include "Master.h"

#include "AnimationBase.h"
#include "CameraManager.h"
#include "GameManager.h"
#include "FSM.h"
#include "LoadingManager.h"
#include "ModelBase.h"
#include "ModelsControllerBase.h"
#include "ObjectBases.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "StateBase.h"
#include "StateDotWeen.h"
#include "StateScene.h"
#include "UtilChange.h"

/*------------------------*/
/*【継承用有限状態マシン】*/
/*------------------------*/

template<typename subscript, typename state>
FSMBase<subscript, state>::FSMBase()
{
	mmStateMap.clear();
	mCurrentState = (subscript) - 1;
	mnNextState = (subscript)0;
}

/*----------*/
/*【アニメーション有限状態マシン】
/*----------*/
FSMAnimation::FSMAnimation()
: FSMBase()
{
	mCurrentState = ANIMATION_TYPE::NONE;
	mnNextState = ANIMATION_TYPE::IDLE;

	mmAnimationStates.clear();
}

// 初期化
void FSMAnimation::Initilize(AnimationBase* animation)
{
	mCurrentState = ANIMATION_TYPE::IDLE;

	// 新しいStateの開始処理
	for (int i = 0; i < mmAnimationStates.size(); i++)
	{
		NewStateSetting(i, animation, MODEL_TYPE::NONE);
	}
}

// 終了
void FSMAnimation::Finalize(AnimationBase* animation)
{
	for (int i = 0; i < mmAnimationStates.size(); i++)
	{
		for (auto animationState : mmAnimationStates[i])
		{
			animationState.second->Finalize(animation, animation->GetAnimationDatas()[i]);
			delete animationState.second;
		}
	}
	mmAnimationStates.clear();
}

// サブ状態マップのサイズを増やす
void FSMAnimation::IncreaseAnimationStateSize(int size)
{
	mmAnimationStates.resize(size);
}

// アニメーションステート情報設定
void FSMAnimation::SetAnimationStateDatas(int animationStateIndex, std::map<MODEL_TYPE, IStateAnimation*> animationStateMap)
{
	mmAnimationStates[animationStateIndex] = animationStateMap;
}

// 更新
void FSMAnimation::Update(AnimationBase* animation, std::vector<AnimationDatas*> animationDatas)
{
	// 古いアニメーション種類を一時的に保存しておく
	ANIMATION_TYPE oldAnimationState = mCurrentState;

	// アニメーションが変更されたか確認
	mnNextState = mmStateMap[mCurrentState]->CheckState(animation, mnNextState);
	if (mnNextState != mCurrentState)
	{
		mmStateMap[mCurrentState]->OnExit(animation, mnNextState);

		mCurrentState = mnNextState;
		mmStateMap[mCurrentState]->OnEnter(animation, oldAnimationState);
	}
	// TODO: この1行なくせるようにした(UIの方になるになる)
	mnNextState = ANIMATION_TYPE::IDLE;

	// 変更処理
	for (int i = 0; i < mmAnimationStates.size(); i++)
	{
		// モデル取得
//		ModelBase* model = animation->GetModelsController()->GetModelList()[i];

		// ステート変更
		if (mCurrentState != oldAnimationState)
		{
			ChangeState(i, animation, oldAnimationState);
		}

		// 更新
		GetAnimationState(i, animation, mCurrentState)->Update(animation, &animationDatas[i]->animDatas[mCurrentState]);
	}
}

// 新しいステートを設定する
void FSMAnimation::NewStateSetting(int animationIndex, AnimationBase* animation, MODEL_TYPE oldModelType)
{
	GetAnimationState(animationIndex, animation, mCurrentState)->OnEnter(animation, &animation->GetAnimationDatas()[animationIndex]->animDatas[mCurrentState], animation->GetAnimationDatas()[animationIndex], oldModelType);
}

// 次のステートが現在のステートと違うならステート変更処理をする
void FSMAnimation::ChangeState(int animationStateIndex, AnimationBase* animation, ANIMATION_TYPE oldAnimationType)
{
	AnimationDatas* animationDatas = animation->GetAnimationDatas()[animationStateIndex];

	// 現在のState終了処理
	GetAnimationState(animationStateIndex, animation, oldAnimationType)->OnExit(animation, &animationDatas->animDatas[oldAnimationType], animationDatas, animationDatas->animDatas[mCurrentState].modelType);

	// 新しいState設定
	NewStateSetting(animationStateIndex, animation, animationDatas->animDatas[oldAnimationType].modelType);
}

// 現在のステート取得
IStateAnimation* FSMAnimation::GetAnimationState(int index, AnimationBase* animation, ANIMATION_TYPE animationType)
{
	return mmAnimationStates[index][animation->GetAnimationDatas()[index]->animDatas[animationType].modelType];
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
	if (mCurrentState != CAMERA_MODE::NONE)
	{
		mmStateMap[mCurrentState]->OnExit(cameraManager, cameraManager->GetCameraData());
	}

	mCurrentState = cameraManager->GetCameraData().cameraMode;
	mmStateMap[mCurrentState]->OnEnter(cameraManager, cameraManager->GetCameraData(), preThreeDFlag);
}

// 初期化
void FSMCamera::Initilize(CameraManager* cameraManager, int id)
{
	mmStateMap[cameraManager->GetCameraData(id).cameraMode]->Initilize(cameraManager, cameraManager->GetCameraData());
}

// 更新
void FSMCamera::Update(CameraManager* cameraManager)
{
	mmStateMap[mCurrentState]->Update(cameraManager, cameraManager->GetCameraData());
}

// 描画
void FSMCamera::Draw(CameraManager* cameraManager)
{
	mmStateMap[mCurrentState]->Draw(cameraManager, cameraManager->GetCameraData());
}

/*------------------------------*/
/*【キャラクター有限状態マシン】*/
/*------------------------------*/

FSMCharacter::FSMCharacter()
: FSMBase()
{
}

// 終了
void FSMCharacter::Finalize(CharacterBase* character)
{
	mmStateMap[mCurrentState]->Finalize(character);
}

// 実行中状態をセットする
void FSMCharacter::SetCurrentState(int id, CharacterBase* character)
{
	mCurrentState = id;
	mmStateMap[mCurrentState]->OnEnter(character);
}

// 更新
void FSMCharacter::Update(CharacterBase* character)
{
	int nextState = mmStateMap[mCurrentState]->StateCheck(character);
	if (mCurrentState != nextState)
	{
		mmStateMap[mCurrentState]->OnExit(character);//現在のStateの終了処理
		mmStateMap[nextState]->OnEnter(character);//新しいStateの開始処理
		mCurrentState = nextState;//新しいStateを設定
	}

	mmStateMap[mCurrentState]->Update(character);
}

// 最終更新
void FSMCharacter::LastUpdate(CharacterBase* character)
{
	mmStateMap[mCurrentState]->LastUpdate(character);
}

// 描画
void FSMCharacter::Draw(CharacterBase* character)
{
	mmStateMap[mCurrentState]->Draw(character);
}

// 死亡
void FSMCharacter::Death(CharacterBase* character)
{
	mmStateMap[mCurrentState]->Death(character);
}


/*-------------------------*/
/*【DotWeen有限状態マシン】*/
/*-------------------------*/
FSMDotWeen::FSMDotWeen()
: FSMBase()
{
}

// 初期化
void FSMDotWeen::Initilize()
{
	RegisterState(DOT_WEEN_TYPE::OUT_BOUNCE, new StateOutBounce());
}

// 更新
void FSMDotWeen::Update(std::vector<DOT_WEEN_DATA>& dotWeenData)
{
	for (int i  = 0; i < dotWeenData.size(); i++)
	{
		dotWeenData[i].DotWeenElapsedTime += Master::mpTimeManager->GetDeltaTime();
		if (dotWeenData[i].DotWeenElapsedTime >= dotWeenData[i].DotWeenTotalTime)
		{
			*dotWeenData[i].ChangeData = dotWeenData[i].EndData;
			dotWeenData.erase(dotWeenData.begin() + i);
			i -= 1;
			continue;
		}

		mmStateMap[dotWeenData[i].DotWeenType]->Update(dotWeenData[i]);

	}
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
	mCurrentState = id;
	mmStateMap[UtilChange::SceneState(mCurrentState)]->OnEnter(sceneManager);
}

// 更新
void FSMScene::Update(SceneManager* sceneManager)
{
	IStateScene* stateScene = mmStateMap[UtilChange::SceneState(mCurrentState)];
	SCENE ret = stateScene->Update(sceneManager);
	if (mCurrentState != ret)
	{
		Master::mpLoadingManager->SetLoadingFlag(LOADING_NUMBER::SCENE);
		sceneManager->SetPreScene((SCENE)mCurrentState);
		mCurrentState = ret;
	}
}

// 次のシーンへ移動する
void FSMScene::NextScene(SceneManager* sceneManager)
{
	mmStateMap[UtilChange::SceneState(mCurrentState)]->OnEnter(sceneManager);
}

// カメラID取得
int FSMScene::GetSceneCameraID()
{
	return mmStateMap[UtilChange::SceneState(mCurrentState)]->GetSceneCameraID();
}

/*--------------------*/
/*【UI有限状態マシン】*/
/*--------------------*/

FSMUI::FSMUI()
: FSMBase()
{
}

// 終了
void FSMUI::Finalize()
{
	for (auto state : mmStateMap)
	{
		state.second->Finalize();
	}
}

// 実行中状態をセットする
void FSMUI::SetCurrentState(STATE_TYPE_UI id, UIBase* ui)
{
	mCurrentState = id;
	StartNextState(mCurrentState, ui);
}

// 更新
void FSMUI::Update(UIBase* ui)
{
	Init();

	if (mCurrentState == mnNextState)
	{
		SetState(mmStateMap[mCurrentState]->Update(ui), ui);
	}

	ui->CheckMouse();
	ui->CheckKeyboard();
	ui->CheckController();
	ui->CheckKeyboard_Controller();
}

// 決定
void FSMUI::Decision(UIBase* ui)
{
	if (mCurrentState == mnNextState)
	{
		SetState(mmStateMap[mCurrentState]->Decision(ui), ui);
	}
}

// 終了
void FSMUI::Cloce(UIBase* ui)
{
	if (mCurrentState == mnNextState)
	{
		SetState(mmStateMap[mCurrentState]->Cloce(ui), ui);
	}
}

// マウス
void FSMUI::Mouse(UIBase* ui)
{
	if (mCurrentState == mnNextState)
	{
		SetState(mmStateMap[mCurrentState]->Mouse(ui), ui);
	}
}

// キーボード
void FSMUI::Keyboard(UIBase* ui)
{
	if (mCurrentState == mnNextState)
	{
		SetState(mmStateMap[mCurrentState]->Keyboard(ui), ui);
	}
}

// コントローラー
void FSMUI::Controller(UIBase* ui)
{
	if (mCurrentState == mnNextState)
	{
		SetState(mmStateMap[mCurrentState]->Controller(ui), ui);
	}
}

// キーボードとコントローラー
void FSMUI::Keyboard_Controller(UIBase* ui)
{
	if (mCurrentState == mnNextState)
	{
		SetState(mmStateMap[mCurrentState]->Keyboard_Controller(ui), ui);
	}
}

// 描画
void FSMUI::Draw(UIBase* ui)
{
	mmStateMap[mCurrentState]->Draw(ui);
}

// 次のステートが現在のステートと違うならステート変更処理をする
void FSMUI::SetState(STATE_TYPE_UI nextState, UIBase* ui)
{
	if (mCurrentState != nextState)
	{
		mmStateMap[mCurrentState]->OnExit(ui);//現在のStateの終了処理

		StartNextState(nextState, ui);    // 新しいStateの開始処理
		mnNextState = nextState;//新しいStateを設定
	}
}

// 次のステートを設定する
void FSMUI::StartNextState(STATE_TYPE_UI nextState, UIBase* ui)
{
	// モデルを描画フラグを設定
	for (int i = 0; i < ui->GetModelCount(); i++)
	{
	std::vector<int> drawNumber = ui->GetDrawModels()[i].mnDrawNumber;
	ui->GetModelsController(i)->SetModelDrawFlag(std::find(drawNumber.begin(), drawNumber.end(), static_cast<int>(nextState)) != drawNumber.end());
	}

	mmStateMap[nextState]->OnEnter(ui);//新しいStateの開始処理
}