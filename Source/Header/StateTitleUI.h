#pragma once

#include "ObjectBases.h"
#include "StateBase.h"

/*--------------------------------*/
/*     【タイトルUIステート】     */
/*--------------------------------*/

enum class TITLE_UI_STATE
{
	START_TITLE_UI_STATE = 0,			// 開始画面
	SELECT_TITLE_UI_STATE,				// 選択

	NEW_DATA_SELECT_TITLE_UI_STATE,		// 新しいデータの保存場所を選択(仮)
	DATA_SELECT_TITLE_UI_STATE,			// データ選択
	TUTORIAL_TITLE_UI_STATE,			// チュートリアル開始
	SETTING_TITLE_UI_STATE,				// セッティング

	CHARACTER_SELECT_TITLE_UI_STATE,	// キャラクター種類選択

};

/*----------------------*/
/*【開始画面UIステート】*/
/*----------------------*/
class StartTitleUIState : public IStateUI
{
public:
	StartTitleUIState();
	~StartTitleUIState() = default;

	/*更新*/
	int Update(UIBase* ui) override;

	/*決定*/
	int Decision(UIBase* ui) override;
};

/*----------------------*/
/*【選択画面UIステート】*/
/*----------------------*/
class SelectTitleUIState : public IStateUI
{
public:
	SelectTitleUIState();
	~SelectTitleUIState() = default;

	/*更新*/
	int Update(UIBase* ui) override;

	/*決定*/
	int Decision(UIBase* ui) override;
};

/*----------------------------*/
/*【データ選択画面UIステート】*/
/*----------------------------*/
class DataSelectTitleUIState : public IStateUI
{
public:
	DataSelectTitleUIState();
	~DataSelectTitleUIState() = default;

	/*更新*/
	int Update(UIBase* ui) override;

	/*決定*/
	int Decision(UIBase* ui) override;
};