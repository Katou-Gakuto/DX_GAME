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

	// TODO: 所持しているオブジェクトでシーン変更後この関数を呼び出すようにする
    /// <summary>ステート初期化</summary>
    virtual void StateInitilize(stateData* initilizeStateData)
	{
		for (auto& initilizeState : mmStateMap)
		{
			initilizeState.second->Initilize(initilizeStateData);
		}
	}

	/*ステート登録(ステートナンバー変更される)*/
	inline void RegisterState(const subscript id, state* state)
	{
		state->SetStatenumber(id);
		mmStateMap[id] = state;
	}

	/*ステート登録*/
	virtual void RegisterState(state* state)
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