#pragma once
#include <vector>

#include "StateEnum.h"

#include "StateBase.h"

class UIBase;

/*--------------------*/
/*【UIステートベース】*/
/*--------------------*/
class IStateUI : public StateBase<STATE_TYPE_UI, UIBase>
{
public:
	IStateUI(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>> stateChangeCriterias, STATE_TYPE_UI stateNumber)
	: StateBase(stateChangeCriterias, stateNumber)
	{
	}
	~IStateUI() = default;

	/// <summary>初期化</summary>
	virtual void Initilize(UIBase* ui){}

	/// <summary>終了</summary>
	virtual void Finalize() {}

	// /*この状態に入った時の処理*/
	// virtual void OnEnter(UIBase* ui) = 0;
	// /*この状態を出る時の処理*/
	// virtual void OnExit(UIBase* ui) = 0;

	/*更新*/
	virtual void Update(UIBase* ui) { }

	/*決定*/
	virtual void Decision(UIBase* ui) { }
	/*終了*/
	virtual void Close(UIBase* ui) { }

	/*マウス*/
	virtual void Mouse(UIBase* ui) { }
	/*キーボード*/
	virtual void Keyboard(UIBase* ui) { }
	/*コントローラー*/
	virtual void Controller(UIBase* ui) { }
	/*キーボードとコントローラー*/
	virtual void Keyboard_Controller(UIBase* ui) { }

	/*描画*/
	virtual void Draw(UIBase* ui) = 0;
};