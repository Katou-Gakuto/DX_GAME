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

	/*新データ関係*/
	CHARACTER_SELECT_TITLE_UI_STATE,	// キャラクター種類選択
	PLAYER_NAME_TITLE_UI_STATE,			// プレイヤー名設定
	INPUT_CHECK_TITLE_UI_STATE,			// 入力情報の最終確認

	/*セッティング関係*/
	SCREEN_SIZE_TITLE_UI_STATE,			// 画面サイズ
	VOLUME_TITLE_UI_STATE,				// 音量

	MAX									// 最大
};
// INPROGRESS: セーブデータ描画作成中
/*----------*/
/*【タイトルUIステート共通処理用】
/*----------*/
class TitleUIStateProcess
{
protected:
	// 前のステート
	TITLE_UI_STATE mePreUiState;

	// 前の選択数
	int mnPreSelectNumber;

public:
	TitleUIStateProcess(TITLE_UI_STATE preUiState);

protected:
	/*背景描画*/
	void DrawBackground(UIBase* ui, std::vector<std::string> str);

	/*この状態に入った時の処理*/
	void ProcessOnEnter(UIBase* ui);

	/*この状態を出る時の処理*/
	void ProcessOnExit(UIBase* ui);

	/*更新*/
	void ProcessUpadate(UIBase* ui);

	/*ゲームを開始する*/
	void StartGame(UIBase* ui);

	/*構造上一つ前のステートを取得する*/
	inline int GetPreUiState() { return (int)mePreUiState; }
};



/*----------------------*/
/*【開始画面UIステート】*/
/*----------------------*/
class StartTitleUIState : public IStateUI, public TitleUIStateProcess
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
class SelectTitleUIState : public IStateUI, public TitleUIStateProcess
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
	/*戻る*/
	int Cloce(UIBase* ui) override;
	/*描画*/
	void Draw(UIBase* ui) override;
};



/*------------------------------------------------*/
/*【新しいデータの入る場所があるか確認UIステート】*/
/*------------------------------------------------*/
class NewDataCheckTitleUIState : public IStateUI, public TitleUIStateProcess
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
	/*戻る*/
	int Cloce(UIBase* ui) override;
	/*描画*/
	void Draw(UIBase* ui) override;
};



/*----------------------------*/
/*【データ選択画面UIステート】*/
/*----------------------------*/
class DataSelectTitleUIState : public IStateUI, public TitleUIStateProcess
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
	/*戻る*/
	int Cloce(UIBase* ui) override;
	/*描画*/
	void Draw(UIBase* ui) override;
};



/*----------------------------*/
/*【チュートリアルUIステート】*/
/*----------------------------*/
class TutorialTitleUIState : public IStateUI, public TitleUIStateProcess
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
	/*戻る*/
	int Cloce(UIBase* ui) override;
	/*描画*/
	void Draw(UIBase* ui) override;
};



/*--------------------------*/
/*【セッティングUIステート】*/
/*--------------------------*/
class SettingTitleUIState : public IStateUI, public TitleUIStateProcess
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
	/*戻る*/
	int Cloce(UIBase* ui) override;
	/*描画*/
	void Draw(UIBase* ui) override;
};



/*----------------------*/
/*【キャラクター種類選択UIステート】*/
/*----------------------*/
class CharacterSelectTitleUIState : public IStateUI, public TitleUIStateProcess
{
public:
	CharacterSelectTitleUIState();
	~CharacterSelectTitleUIState() = default;

	/*この状態に入った時の処理*/
	void OnEnter(UIBase* ui) override;
	/*この状態を出る時の処理*/
	void OnExit(UIBase* ui) override;

	/*更新*/
	int Update(UIBase* ui) override;
	/*決定*/
	int Decision(UIBase* ui) override;
	/*戻る*/
	int Cloce(UIBase* ui) override;
	/*描画*/
	void Draw(UIBase* ui) override;
};



/*----------------------*/
/*【プレイヤー名設定UIステート】*/
/*----------------------*/
class PlayerNameTitleUIState : public IStateUI, public TitleUIStateProcess
{
public:
	PlayerNameTitleUIState();
	~PlayerNameTitleUIState() = default;

	/*この状態に入った時の処理*/
	void OnEnter(UIBase* ui) override;
	/*この状態を出る時の処理*/
	void OnExit(UIBase* ui) override;

	/*更新*/
	int Update(UIBase* ui) override;
	/*決定*/
	int Decision(UIBase* ui) override;
	/*戻る*/
	int Cloce(UIBase* ui) override;
	/*描画*/
	void Draw(UIBase* ui) override;
};



/*----------------------*/
/*【入力情報の最終確認UIステート】*/
/*----------------------*/
class InputCheckTitleUIState : public IStateUI, public TitleUIStateProcess
{
public:
	InputCheckTitleUIState();
	~InputCheckTitleUIState() = default;

	/*この状態に入った時の処理*/
	void OnEnter(UIBase* ui) override;
	/*この状態を出る時の処理*/
	void OnExit(UIBase* ui) override;

	/*更新*/
	int Update(UIBase* ui) override;
	/*決定*/
	int Decision(UIBase* ui) override;
	/*戻る*/
	int Cloce(UIBase* ui) override;
	/*描画*/
	void Draw(UIBase* ui) override;
};



/*----------------------*/
/*【画面サイズ調整UIステート】*/
/*----------------------*/
class ScreenSizeTitleUIState : public IStateUI, public TitleUIStateProcess
{
public:
	ScreenSizeTitleUIState();
	~ScreenSizeTitleUIState() = default;

	/*この状態に入った時の処理*/
	void OnEnter(UIBase* ui) override;
	/*この状態を出る時の処理*/
	void OnExit(UIBase* ui) override;

	/*更新*/
	int Update(UIBase* ui) override;
	/*決定*/
	int Decision(UIBase* ui) override;
	/*戻る*/
	int Cloce(UIBase* ui) override;
	/*描画*/
	void Draw(UIBase* ui) override;
};



/*----------------------*/
/*【音量調整UIステート】*/
/*----------------------*/
class VolumeTitleUIState : public IStateUI, public TitleUIStateProcess
{
public:
	VolumeTitleUIState();
	~VolumeTitleUIState() = default;

	/*この状態に入った時の処理*/
	void OnEnter(UIBase* ui) override;
	/*この状態を出る時の処理*/
	void OnExit(UIBase* ui) override;

	/*更新*/
	int Update(UIBase* ui) override;
	/*決定*/
	int Decision(UIBase* ui) override;
	/*戻る*/
	int Cloce(UIBase* ui) override;
	/*描画*/
	void Draw(UIBase* ui) override;
};