#pragma once
#include <iostream>
#include <map>
#include <type_traits>
#include <vector>

#include "StateEnum.h"
#include "StateData.h"

#include "StateBase.h"

enum class CAMERA_MODE;
enum class DOT_WEEN_TYPE;
enum class SCENE;

struct DOT_WEEN_DATA;

class AnimationBase;
class CameraManager;
class CharacterBase;
class SceneManager;
class UIBase;

/*----------*/
/*【継承用有限状態マシン】*/
/*----------*/
template<typename state, typename subscript, typename stateData, typename = typename std::enable_if<std::is_base_of<StateBase<subscript, stateData>, state>::value>::type>
class FSMBase
{
protected:
	// 登録した状態リスト
	std::map<subscript, state*> mmStateMap;
	// 現在実行中ステート
	subscript mCurrentState;
	// 次の実行ステート
	subscript mNextState;
	// 前の実行ステート
	subscript mPreState;

public:
	FSMBase()
	: mCurrentState((subscript) - 1)
	, mNextState((subscript)0)
	, mPreState((subscript) - 1)
	{
		mmStateMap.clear();
	}
	
	~FSMBase()
	{
		//mapコンテナの解放
		for (const auto& pair : mmStateMap)
			delete (pair.second);//登録されたStateのインスタンスを削除する

		mmStateMap.clear();
	}

    /// <summary>初期化</summary>
    virtual void Initilize(stateData* stateData) {}// = 0;

	/*ステート登録(ステートナンバー変更される)*/
	inline void RegisterState(const subscript id, state* state)
	{
		state->SetStatenumber(id);
		mmStateMap[id] = state;
	}

	/*ステート登録*/
	inline void RegisterState(state* state)
	{
		mmStateMap[state->GetStateNumber()] = state;
	}

	/*ステート変更確認*/
	void CheckChangeState(stateData* checkStateData)
	{
		// 変更確認
		subscript changeState = mmStateMap[mCurrentState]->GetNextState(checkStateData);
		if (changeState != mCurrentState)
		{
			mPreState = mCurrentState;
			mCurrentState = changeState;

			// 変更処理	
			mmStateMap[mPreState]->OnExit(checkStateData, mCurrentState);
			mmStateMap[mCurrentState]->OnEnter(checkStateData, mPreState);
		}
	}

	/// <summary>現在の実行状態取得</summary>
	inline subscript GetCurrentState() const { return mCurrentState; }
	/// <summary>前の実行状態取得</summary>
	inline subscript GetPreState() const { return mPreState; }
	/// <summary>次の実行状態設定</summary>
	inline void SetNextState(subscript nextState) { mNextState = nextState; }
};

// TODO: 1つのモデルに対して複数のアニメーションを後から適用できるようにする
/*----------*/
/*【アニメーション有限状態マシン】
/*----------*/
class FSMAnimation : public FSMBase<IStateAnimation, ANIMATION_TYPE, STATE_ANEMATION_DATA>
{
private:
	// // アニメーションステート達
	// std::vector<std::map<MODEL_TYPE, IStateAnimation*>> mmAnimationStates;
public:
	FSMAnimation();

    /// <summary>初期化</summary>
    void Initilize(AnimationBase* animation);
	/// <summary>終了</summary>
	void Finalize(AnimationBase* animation);

	/*アニメーション状態達のサイズを増やす*/
	void IncreaseAnimationStateSize(int size);

	/// <summary>アニメーションステート情報設定</summary>
	void SetAnimationStateDatas(int animationStateIndex, std::map<MODEL_TYPE, IStateAnimation*> animationStateMap);

	/// <summary>更新</summary>
	void Update(AnimationBase* animation, std::vector<AnimationDatas*> animationDatas);

	/// <summary>次のステート設定</summary>
	// TODO: 構造体でアニメーションを設定出来るように変更する
	//inline void SetNextState(ANIMATION_TYPE animationType) { mnNextState = animationType; }

	/// <summary>現在のステートと同じ種類かを確認する</summary>
	//bool CheckNowStateSameType(ANIMATION_TYPE animationType) { return mmStateMap[mCurrentState]->CheckSameType(animationType); }
	
private:
	/*新しいステートを設定する*/
	void NewStateSetting(int animationIndex, AnimationBase* animation, MODEL_TYPE oldModelType);

	/*次のステートが現在のステートと違うならステート変更処理をする*/
	void ChangeState(int animationStateIndex, AnimationBase* animation, ANIMATION_TYPE oldAnimationType);

	/*現在のステート取得*/
	IStateAnimation* GetAnimationState(int index, AnimationBase* animation, ANIMATION_TYPE animationType);
};

/*----------*/
/*【カメラ有限状態マシン】*/
/*----------*/
class FSMCamera : public FSMBase<IStateCamera, CAMERA_MODE, CameraData>
{
public:
	FSMCamera();

	/*実行中状態をセットする*/
	void SetCurrentState(CameraManager* cameraManager, int& preThreeDFlag);

	/*初期化*/
	void Initilize(CameraManager* cameraManager, int id);

	/*更新*/
	void Update(CameraManager* cameraManager);

	/*描画*/
	void Draw(CameraManager* cameraManager);
};

/*----------*/
/*【キャラクター有限状態マシン】*/
/*----------*/
class FSMCharacter : public FSMBase<IStateCharacter, STATE_TYPE_CHARACTER, CharacterBase>
{
public:
	FSMCharacter();

	/// <summary>終了</summary>
	void Finalize(CharacterBase* character);

	/*実行中状態をセットする*/
	void SetCurrentState(int id, CharacterBase* character);

	/*更新*/
	void Update(CharacterBase* character);
	/*最終更新*/
	void LastUpdate(CharacterBase* character);

	/*描画*/
	void Draw(CharacterBase* character);

	/*死亡*/
	void Death(CharacterBase* character);
};

/*-------------------------*/
/*【DotWeen有限状態マシン】*/
/*-------------------------*/
class FSMDotWeen : public FSMBase<IStateDotWeen, DOT_WEEN_TYPE, std::vector<DOT_WEEN_DATA>>
{
public:
	FSMDotWeen();

	/// <summary>初期化</summary>
	void Initilize();

	/// <summary>更新</summary>
	void Update(std::vector<DOT_WEEN_DATA>& dotWeenData);
};

/*----------*/
/*【シーン有限状態マシン】*/
/*----------*/
class FSMScene : public FSMBase<IStateScene, SCENE, SceneManager>
{
public:
	FSMScene();

	/*実行中状態をセットする*/
	void SetCurrentState(SCENE id, SceneManager* sceneManager);

	/*更新*/
	void Update(SceneManager* sceneManager);

	/*次のシーンへ移動する*/
	void NextScene(SceneManager* sceneManager);

	/*カメラID取得*/
	int GetSceneCameraID();

	/*ステートマップ取得*/
	inline std::map<SCENE, IStateScene*> GetStateMap() { return mmStateMap; }
};

/*----------*/
/*【UI有限状態マシン】*/
/*----------*/
class FSMUI : public FSMBase<IStateUI, STATE_TYPE_UI, UIBase>
{
public:
	FSMUI();

	/// <summary>終了</summary>
	void Finalize();

	/*実行中状態をセットする*/
	void SetCurrentState(STATE_TYPE_UI id, UIBase* ui);

	/*更新*/
	void Update(UIBase* ui);

	/*決定 ※UIBaseに設置してない*/
	void Decision(UIBase* ui);
	/*終了 ※この処理の前にUIBaseでuiを削除する仕組みになっている*/
	void Cloce(UIBase* ui);

	// /*マウス*/
	// void Mouse(UIBase* ui);
	// /*キーボード*/
	// void Keyboard(UIBase* ui);
	// /*コントローラー*/
	// void Controller(UIBase* ui);
	// /*キーボードとコントローラー*/
	// void Keyboard_Controller(UIBase* ui);

	/*描画*/
	void Draw(UIBase* ui);

private:
	/*次のステートが現在のステートと違うならステート変更処理をする*/
	void SetState(STATE_TYPE_UI nextState, UIBase* ui);

	/*次のステートを開始する*/
	void StartNextState(STATE_TYPE_UI nextState, UIBase* ui);
};
