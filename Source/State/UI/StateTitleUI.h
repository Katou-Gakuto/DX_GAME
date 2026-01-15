#pragma once

#include "ObjectBases.h"
#include "StateBase.h"

/*----------------------*/
/*【タイトルUIステート】*/
/*----------------------*/

enum class TITLE_UI_STATE
{
	START_TITLE_UI_STATE = 0,			// 開始画面
	SELECT_TITLE_UI_STATE,				// 選択

	NEW_DATA_CHECK_TITLE_UI_STATE,		// 新しいデータの入る場所があるか確認する
	DATA_SELECT_TITLE_UI_STATE,			// データ選択
	TUTORIAL_TITLE_UI_STATE,			// チュートリアル開始
	SETTING_TITLE_UI_STATE,				// セッティング

	CHARACTER_SELECT_TITLE_UI_STATE,	// キャラクター種類選択
	PLAYER_NAME_TITLE_UI_STATE			// プレイヤー名設定
};

/*----------*/
/*【タイトルUIステート共通処理用】
/*----------*/
class TitleUIStateProcess
{
public:
	TitleUIStateProcess();

protected:
	/// <summary>土台描画</summary>
	void BaseDraw();
};

/*----------------------*/
/*【開始画面UIステート】*/
/*----------------------*/
class StartTitleUIState : public IStateUI
{
public:
	StartTitleUIState();
	~StartTitleUIState() = default;

	/*この状態に入った時の処理*/
	void OnEnter(UIBase* ui) override;
	/*この状態を出る時の処理*/
	void OnExit(UIBase* ui) override;

	/*更新*/
	int Update(UIBase* ui) override;

	/*決定*/
	int Decision(UIBase* ui) override;

	/*描画*/
	void Draw(UIBase* ui) override;
};

/*----------------------*/
/*【選択画面UIステート】*/
/*----------------------*/
class SelectTitleUIState : public IStateUI
{
public:
	SelectTitleUIState();
	~SelectTitleUIState() = default;

	/*この状態に入った時の処理*/
	void OnEnter(UIBase* ui) override;
	/*この状態を出る時の処理*/
	void OnExit(UIBase* ui) override;

	/*更新*/
	int Update(UIBase* ui) override;

	/*決定*/
	int Decision(UIBase* ui) override;

	/*描画*/
	void Draw(UIBase* ui) override;
};

/*------------------------------------------------*/
/*【新しいデータの入る場所があるか確認UIステート】*/
/*------------------------------------------------*/
class NewDataCheckTitleUIState : public IStateUI
{
public:
	NewDataCheckTitleUIState();
	~NewDataCheckTitleUIState() = default;

	/*この状態に入った時の処理*/
	void OnEnter(UIBase* ui) override;
	/*この状態を出る時の処理*/
	void OnExit(UIBase* ui) override;

	/*更新*/
	int Update(UIBase* ui) override;

	/*決定*/
	int Decision(UIBase* ui) override;

	/*描画*/
	void Draw(UIBase* ui) override;
};

/*----------------------------*/
/*【データ選択画面UIステート】*/
/*----------------------------*/
class DataSelectTitleUIState : public IStateUI
{
public:
	DataSelectTitleUIState();
	~DataSelectTitleUIState() = default;

	/*この状態に入った時の処理*/
	void OnEnter(UIBase* ui) override;
	/*この状態を出る時の処理*/
	void OnExit(UIBase* ui) override;

	/*更新*/
	int Update(UIBase* ui) override;

	/*決定*/
	int Decision(UIBase* ui) override;

	/*描画*/
	void Draw(UIBase* ui) override;
};

/*----------------------------*/
/*【チュートリアルUIステート】*/
/*----------------------------*/
class TutorialTitleUIState : public IStateUI
{
public:
	TutorialTitleUIState();
	~TutorialTitleUIState() = default;

	/*この状態に入った時の処理*/
	void OnEnter(UIBase* ui) override;
	/*この状態を出る時の処理*/
	void OnExit(UIBase* ui) override;

	/*更新*/
	int Update(UIBase* ui) override;

	/*決定*/
	int Decision(UIBase* ui) override;

	/*描画*/
	void Draw(UIBase* ui) override;
};

/*--------------------------*/
/*【セッティングUIステート】*/
/*--------------------------*/
class SettingTitleUIState : public IStateUI
{
public:
	SettingTitleUIState();
	~SettingTitleUIState() = default;

	/*この状態に入った時の処理*/
	void OnEnter(UIBase* ui) override;
	/*この状態を出る時の処理*/
	void OnExit(UIBase* ui) override;

	/*更新*/
	int Update(UIBase* ui) override;

	/*決定*/
	int Decision(UIBase* ui) override;

	/*描画*/
	void Draw(UIBase* ui) override;
};