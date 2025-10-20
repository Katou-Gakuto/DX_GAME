#include "../Header/StateTitleUI.h"

/*--------------------------------*/
/*     【タイトルUIステート】     */
/*--------------------------------*/

/*----------------------*/
/*【開始画面UIステート】*/
/*----------------------*/

StartTitleUIState::StartTitleUIState()
{
	mnStateNumber = (int)TITLE_UI_STATE::START_TITLE_UI_STATE;
}

// 更新
int StartTitleUIState::Update(UIBase* ui)
{
	ui->DefaultDecision();

	return mnStateNumber;
}

// 決定
int StartTitleUIState::Decision(UIBase* ui)
{
	return (int)TITLE_UI_STATE::SELECT_TITLE_UI_STATE;
}

/*----------------------*/
/*【選択画面UIステート】*/
/*----------------------*/

SelectTitleUIState::SelectTitleUIState()
{
	mnStateNumber = (int)TITLE_UI_STATE::SELECT_TITLE_UI_STATE;
}

// 更新
int SelectTitleUIState::Update(UIBase* ui)
{
	ui->DefaultDecision();

	return mnStateNumber;
}

// 決定
int SelectTitleUIState::Decision(UIBase* ui)
{
	return (int)TITLE_UI_STATE::DATA_SELECT_TITLE_UI_STATE;
}

/*----------------------------*/
/*【データ選択画面UIステート】*/
/*----------------------------*/

DataSelectTitleUIState::DataSelectTitleUIState()
{
	mnStateNumber = (int)TITLE_UI_STATE::DATA_SELECT_TITLE_UI_STATE;
}

// 更新
int DataSelectTitleUIState::Update(UIBase* ui)
{
	ui->DefaultDecision();

	return mnStateNumber;
}

// 決定
int DataSelectTitleUIState::Decision(UIBase* ui)
{
	return mnStateNumber + 1;
}
