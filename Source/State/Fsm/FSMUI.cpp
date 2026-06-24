#include <map>
#include <vector>

#include "StateEnum.h"

#include "FSM.h"
#include "FSMUI.h"
#include "ObjectBase_UI.h"
#include "StateUIBase.h"

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

// 更新
void FSMUI::Update(UIBase* ui)
{
	CheckChangeState(ui);

	mmStateMap[mCurrentState]->Update(ui);

	ui->CheckMouse();
	ui->CheckKeyboard();
	ui->CheckController();
	ui->CheckKeyboard_Controller();
}

// 決定
void FSMUI::Decision(UIBase* ui)
{
	mmStateMap[mCurrentState]->Decision(ui);
}

// 終了
void FSMUI::Close(UIBase* ui)
{
	mmStateMap[mCurrentState]->Close(ui);
}

// マウス
void FSMUI::Mouse(UIBase* ui)
{
	mmStateMap[mCurrentState]->Mouse(ui);
}

// キーボード
void FSMUI::Keyboard(UIBase* ui)
{
	mmStateMap[mCurrentState]->Keyboard(ui);
}

// コントローラー
void FSMUI::Controller(UIBase* ui)
{
	mmStateMap[mCurrentState]->Controller(ui);
}

// キーボードとコントローラー
void FSMUI::Keyboard_Controller(UIBase* ui)
{
	mmStateMap[mCurrentState]->Keyboard_Controller(ui);
}

// 描画
void FSMUI::Draw(UIBase* ui)
{
	mmStateMap[mCurrentState]->Draw(ui);
}