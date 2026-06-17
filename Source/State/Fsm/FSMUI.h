#pragma once
#include "StateEnum.h"

#include "FSM.h"
#include "ObjectBase_UI.h"

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
	void Close(UIBase* ui);

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