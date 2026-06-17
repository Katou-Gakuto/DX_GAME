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
	IStateUI(STATE_TYPE_UI stateNumber, std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>> stateChangeCriterias)
	: StateBase(stateNumber, stateChangeCriterias)
	{
	}
	virtual ~IStateUI() = default;

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

	// /*マウス*/
	// virtual STATE_TYPE_UI Mouse(UIBase* ui) { return mStateNumber; }
	// /*キーボード*/
	// virtual STATE_TYPE_UI Keyboard(UIBase* ui) { return mStateNumber; }
	// /*コントローラー*/
	// virtual STATE_TYPE_UI Controller(UIBase* ui) { return mStateNumber; }
	// /*キーボードとコントローラー*/
	// virtual STATE_TYPE_UI Keyboard_Controller(UIBase* ui) { return mStateNumber; }

	/*描画*/
	virtual void Draw(UIBase* ui) = 0;
};