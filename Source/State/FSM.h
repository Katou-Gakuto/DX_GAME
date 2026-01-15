#pragma once

#include <map>
#include <vector>

#include "StateBase.h"

enum class CAMERA_MODE;
enum class SCENE;

class AnimationBase;
class CameraManager;
class CharacterBase;
class SceneManager;
class UIBase;

/*----------*/
/*【継承用有限状態マシン】*/
/*----------*/
template<typename subscript, typename state>
class FSMBase
{
protected:
	// 登録した状態リスト
	std::map<subscript, state*> mmStateMap;
	// 現在実行中のステート
	subscript mnCurrentState;
	// 次の実行するステート
	subscript mnNextState;

public:
	FSMBase();
	~FSMBase()
	{
		//mapコンテナの解放
		for (const auto& pair : mmStateMap)
			delete (pair.second);//登録されたStateのインスタンスを削除する

		mmStateMap.clear();
	}

	/*ステート登録*/
	inline void RegisterState(const subscript id, state* state)
	{
		mmStateMap[id] = state;
	}

	/*ステート登録*/
	inline void RegisterState(state* state)
	{
		mmStateMap[state->GetStateNumber()] = state;
	}

	/*初期化*/
	virtual void Init()
	{
		mnCurrentState = mnNextState;
	}

	/*実行状態取得*/
	inline subscript GetCurrentState() const { return mnCurrentState; }
};

/*----------*/
/*【アニメーション有限状態マシン】
/*----------*/
class FSMAnimation : public FSMBase<ANIMATION_TYPE, IStateAnimationController>
{
private:
	// アニメーションステート達
	std::vector<std::map<MODEL_TYPE, IStateAnimation*>> mmAnimationStates;
public:
	FSMAnimation();

    /// <summary>初期化</summary>
    void Initilize(AnimationBase* animation);
	/// <summary>終了</summary>
	void Finalize();

	/*アニメーション状態達のサイズを増やす*/
	void IncreaseAnimationStateSize(int size);

	/// <summary>アニメーションステート情報設定</summary>
	void SetAnimationStateDatas(int animationStateIndex, std::map<MODEL_TYPE, IStateAnimation*> animationStateMap);

	/// <summary>更新</summary>
	void Update(AnimationBase* animation, std::vector<std::map<ANIMATION_TYPE, AnimationDatas>>& animationDatas);

	/// <summary>次のステート設定</summary>
	inline void SetNextState(ANIMATION_TYPE animationType) { mnNextState = animationType; }

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
class FSMCamera : public FSMBase<CAMERA_MODE, IStateCamera>
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
class FSMCharacter : public FSMBase<int, IStateCharacter>
{
public:
	FSMCharacter();

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

/*----------*/
/*【シーン有限状態マシン】*/
/*----------*/
class FSMScene : public FSMBase<SCENE, IStateScene>
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
};

/*----------*/
/*【UI有限状態マシン】*/
/*----------*/
class FSMUI : public FSMBase<int, IStateUI>
{
public:
	FSMUI();

	/*実行中状態をセットする*/
	void SetCurrentState(int id, UIBase* ui);

	/*更新*/
	void Update(UIBase* ui);

	/*決定 ※UIBaseに設置してない*/
	void Decision(UIBase* ui);
	/*終了 ※この処理の前にUIBaseでuiを削除する仕組みになっている*/
	void Cloce(UIBase* ui);

	/*マウス*/
	void Mouse(UIBase* ui);
	/*キーボード*/
	void Keyboard(UIBase* ui);
	/*コントローラー*/
	void Controller(UIBase* ui);
	/*キーボードとコントローラー*/
	void Keyboard_Controller(UIBase* ui);

	/*描画*/
	void Draw(UIBase* ui);

private:
	/*次のステートが現在のステートと違うならステート変更処理をする*/
	void SetState(int nextState, UIBase* ui);
};
