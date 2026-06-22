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
void FSMUI::Close(UIBase* ui)
{
	if (mCurrentState == mnNextState)
	{
		SetState(mmStateMap[mCurrentState]->Close(ui), ui);
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