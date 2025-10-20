#pragma once

#include <map>

#include "StateBase.h"

class IStateScene;
class SceneManager;

/*------------------------*/
/*【継承用有限状態マシン】*/
/*------------------------*/
class FSMBase
{
protected:
	// 登録した状態リスト
	std::map<int, StateBase*> mmStateMap;
	// 現在実行中のステート
	int mnCurrentState;
	// 次の実行するステート
	int mnNextState;

public:
	FSMBase();
	~FSMBase();

	/*ステート登録*/
	void RegisterState(const int id, StateBase* state);
	void RegisterState(StateBase* state);

	/*初期化*/
	virtual void Init();


	/*実行状態取得*/
	inline int GetCurrentState() const { return mnCurrentState; }

};

/*------------------------*/
/*【シーン有限状態マシン】*/
/*------------------------*/
class FSMScene : public FSMBase
{
public:
	FSMScene();

	/*実行中状態をセットする*/
	void SetCurrentState(int id, SceneManager* sceneManager);

	/*更新*/
	void Update(SceneManager* sceneManager);

	/*次のシーンへ移動する*/
	void NextScene(SceneManager* sceneManager);
private:
	/*ステートを変換する*/
	IStateScene* GetState(StateBase* state);
};

/*--------------------*/
/*【UI有限状態マシン】*/
/*--------------------*/
class FSMUI : public FSMBase
{
private:
	/*ステートを変換する*/
	IStateScene* GetState(StateBase* state);
};