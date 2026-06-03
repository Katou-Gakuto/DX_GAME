#pragma once
#include <string>

#include "Status.h"

#include "ObjectBases.h"
#include "StateBase.h"

enum class CHARACTER_TYPE;
enum class SCENE;

struct DisplaySize;
struct Vector2;
struct Vector2_Int;

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

	// TODO: UIを利用する方式に変える
	// セーブデータ背景画像ハンドル
	int mnSaveDataDrawBackHandle;
	// セーブデータ選択背景画像ハンドル
	int mnSaveDataDrawDelectBackHandle;
	
	// TODO: 文字ハンドルのリソースマネージャーとUIベースにハンドルを持たせれるようにする
	// セーブデータ文字列描画時設定ハンドル(セーブデータ)
	int mnSaveDataDrawFontHandle_SaveData;
	// セーブデータ文字列描画時設定ハンドル(プレイヤーネーム)
	int mnSaveDataDrawFontHandle_PlayerName;
	// セーブデータ文字列描画時設定ハンドル(その他)
	int mnSaveDataDrawFontHandle_Other;

public:
	TitleUIStateProcess(TITLE_UI_STATE preUiState);

protected:
	/*終了処理*/
	void StateProcessFinalize();

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

	/*セーブデータを描画*/
	void DrawSaveData(UIBase* ui, int displayPos, int playerGraphNumber, std::string name, int dataNumber, STATUS status, SCENE mapType);

	/*文字描画*/
	void UIStringDraw(Vector2_Int pos, DisplaySize displaySize, Vector2 ratio, std::string drawString, int fontHndle);
};



/*----------------------*/
/*【開始画面UIステート】*/
/*----------------------*/
class StartTitleUIState : public IStateUI, public TitleUIStateProcess
{
public:
	StartTitleUIState();
	~StartTitleUIState() = default;

	/*終了*/
	void Finalize() override;

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

	/*終了*/
	void Finalize() override;

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

	/*終了*/
	void Finalize() override;

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
private:
	int mnDrawDataPos;

public:
	DataSelectTitleUIState();
	~DataSelectTitleUIState() = default;

	/*終了*/
	void Finalize() override;

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

	/*終了*/
	void Finalize() override;

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

	/*終了*/
	void Finalize() override;

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

	/*終了*/
	void Finalize() override;

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

	/*終了*/
	void Finalize() override;

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

	/*終了*/
	void Finalize() override;

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

	/*終了*/
	void Finalize() override;

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

	/*終了*/
	void Finalize() override;

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