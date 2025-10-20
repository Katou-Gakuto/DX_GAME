#pragma once

class SceneManager;
class UIBase;

/*----------------------------*/
/*     【ステートベース】     */
/*----------------------------*/
class StateBase
{
protected:
	int mnStateNumber = -1;
public:
	StateBase() = default;
	virtual ~StateBase() = default;

	int GetStateNumber() const { return mnStateNumber; }
};


/*----------------------------------*/
/*     【シーンステートベース】     */
/*----------------------------------*/

/*------------------------*/
/*【継承用シーンステート】*/
/*------------------------*/
class IStateScene : public StateBase
{
public:
	IStateScene() = default;
	virtual ~IStateScene() = default;

	/*この状態に入った時の処理*/
	virtual void OnEnter(SceneManager* sceneManager) = 0;
	/*この状態を出る時の処理*/
	virtual void OnExit(SceneManager* sceneManager) = 0;

	/*更新*/
	int Update(SceneManager* sceneManager);
};
/*------------------------*/
/*【削除用シーンステート】*/
/*------------------------*/
class DeleteSceneState : public IStateScene { public: DeleteSceneState() = default; ~DeleteSceneState() = default; void OnEnter(SceneManager* sceneManager) override {} void OnExit(SceneManager* sceneManager) override {} };


/*----------------------------*/
/*     【UIステートベース】     */
/*----------------------------*/

/*--------------------*/
/*【継承用UIステート】*/
/*--------------------*/
class IStateUI : public StateBase
{
public:
	IStateUI() = default;
	virtual ~IStateUI() = default;

	/*この状態に入った時の処理*/
	virtual void OnEnter(UIBase* ui) = 0;
	/*この状態を出る時の処理*/
	virtual void OnExit(UIBase* ui) = 0;

	/*更新*/
	virtual int Update(UIBase* ui) { return mnStateNumber; }

	/*決定*/
	virtual int Decision(UIBase* ui) { return mnStateNumber; }
	/*終了*/
	virtual void Cloce(UIBase* ui) {}

	/*マウス*/
	virtual int Mouse() { return mnStateNumber; }
	/*キーボード*/
	virtual int Keyboard() { return mnStateNumber; }
	/*コントローラー*/
	virtual int Controller() { return mnStateNumber; }
	/*キーボードとコントローラー*/
	virtual int Keyboard_Controller() { return mnStateNumber; }
};
/*--------------------*/
/*【削除用UIステート】*/
/*--------------------*/
class DeleteUIState : public IStateUI { public: DeleteUIState() = default; ~DeleteUIState() = default; void OnEnter(UIBase* ui) override {} void OnExit(UIBase* ui) override {} };
