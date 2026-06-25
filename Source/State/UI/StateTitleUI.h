#pragma once
#include <string>

#include "Status.h"

#include "ObjectBases.h"
#include "StateUIBase.h"

enum class CHARACTER_TYPE;
enum class SCENE;

struct DisplaySize;
struct Vector2;
struct Vector2_Int;

/*----------------------*/
/*【タイトルUIステート】*/
/*----------------------*/

// enum class TITLE_UI_STATE
// {
// 	START_TITLE_UI_STATE = 0,			// 開始画面
// 	SELECT_TITLE_UI_STATE,				// 選択

// 	NEW_DATA_CHECK_TITLE_UI_STATE,		// 新しいデータの入る場所があるか確認する
// 	DATA_SELECT_TITLE_UI_STATE,			// データ選択
// 	TUTORIAL_TITLE_UI_STATE,			// チュートリアル開始
// 	SETTING_TITLE_UI_STATE,				// セッティング

// 	/*新データ関係*/
// 	CHARACTER_SELECT_TITLE_UI_STATE,	// キャラクター種類選択
// 	PLAYER_NAME_TITLE_UI_STATE,			// プレイヤー名設定
// 	INPUT_CHECK_TITLE_UI_STATE,			// 入力情報の最終確認

// 	/*セッティング関係*/
// 	SCREEN_SIZE_TITLE_UI_STATE,			// 画面サイズ
// 	VOLUME_TITLE_UI_STATE,				// 音量

// 	MAX									// 最大
// };

/*----------*/
/*【タイトルUIステート共通処理用】
/*----------*/
class TitleUIStateProcess
{
protected:
	// 前段階のステート
	STATE_TYPE_UI mePreviousSteptate;

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
	TitleUIStateProcess(STATE_TYPE_UI preUiState);

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
	inline STATE_TYPE_UI GetPreUiState() { return mePreviousSteptate; }

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
	// FIXME: コンストラクタでステート変更条件を渡せます
	StartTitleUIState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>> stateChangeCriterias);
	~StartTitleUIState() = default;

	/*終了*/
	void Finalize() override;

	/*この状態に入った時の処理*/
	void OnEnter(UIBase* ui, STATE_TYPE_UI preState) override;
	/*この状態を出る時の処理*/
	void OnExit(UIBase* ui, STATE_TYPE_UI nextState) override;

	/*更新*/
	void Update(UIBase* ui) override;
	/*決定*/
	void Decision(UIBase* ui) override;
	/*描画*/
	void Draw(UIBase* ui) override;
};



/*----------------------*/
/*【選択画面UIステート】*/
/*----------------------*/
class SelectTitleUIState : public IStateUI, public TitleUIStateProcess
{
public:
	// FIXME: コンストラクタでステート変更条件を渡せます
	SelectTitleUIState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>> stateChangeCriterias);
	~SelectTitleUIState() = default;

	/*終了*/
	void Finalize() override;

	/*この状態に入った時の処理*/
	void OnEnter(UIBase* ui, STATE_TYPE_UI preState) override;
	/*この状態を出る時の処理*/
	void OnExit(UIBase* ui, STATE_TYPE_UI nextState) override;

	/*更新*/
	void Update(UIBase* ui) override;
	/*決定*/
	void Decision(UIBase* ui) override;
	/*戻る*/
	void Close(UIBase* ui) override;
	/*描画*/
	void Draw(UIBase* ui) override;
};



/*------------------------------------------------*/
/*【新しいデータの入る場所があるか確認UIステート】*/
/*------------------------------------------------*/
class NewDataCheckTitleUIState : public IStateUI, public TitleUIStateProcess
{
public:
	// FIXME: コンストラクタでステート変更条件を渡せます
	NewDataCheckTitleUIState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>> stateChangeCriterias);
	~NewDataCheckTitleUIState() = default;

	/*終了*/
	void Finalize() override;

	/*この状態に入った時の処理*/
	void OnEnter(UIBase* ui, STATE_TYPE_UI preState) override;
	/*この状態を出る時の処理*/
	void OnExit(UIBase* ui, STATE_TYPE_UI nextState) override;

	/*更新*/
	void Update(UIBase* ui) override;
	/*決定*/
	void Decision(UIBase* ui) override;
	/*戻る*/
	void Close(UIBase* ui) override;
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
	// FIXME: コンストラクタでステート変更条件を渡せます
	DataSelectTitleUIState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>> stateChangeCriterias);
	~DataSelectTitleUIState() = default;

	/*終了*/
	void Finalize() override;

	/*この状態に入った時の処理*/
	void OnEnter(UIBase* ui, STATE_TYPE_UI preState) override;
	/*この状態を出る時の処理*/
	void OnExit(UIBase* ui, STATE_TYPE_UI nextState) override;

	/*更新*/
	void Update(UIBase* ui) override;
	/*決定*/
	void Decision(UIBase* ui) override;
	/*戻る*/
	void Close(UIBase* ui) override;
	/*描画*/
	void Draw(UIBase* ui) override;
};



/*----------------------------*/
/*【チュートリアルUIステート】*/
/*----------------------------*/
class TutorialTitleUIState : public IStateUI, public TitleUIStateProcess
{
public:
	// FIXME: コンストラクタでステート変更条件を渡せます
	TutorialTitleUIState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>> stateChangeCriterias);
	~TutorialTitleUIState() = default;

	/*終了*/
	void Finalize() override;

	/*この状態に入った時の処理*/
	void OnEnter(UIBase* ui, STATE_TYPE_UI preState) override;
	/*この状態を出る時の処理*/
	void OnExit(UIBase* ui, STATE_TYPE_UI nextState) override;

	/*更新*/
	void Update(UIBase* ui) override;
	/*決定*/
	void Decision(UIBase* ui) override;
	/*戻る*/
	void Close(UIBase* ui) override;
	/*描画*/
	void Draw(UIBase* ui) override;
};



/*--------------------------*/
/*【セッティングUIステート】*/
/*--------------------------*/
class SettingTitleUIState : public IStateUI, public TitleUIStateProcess
{
public:
	// FIXME: コンストラクタでステート変更条件を渡せます
	SettingTitleUIState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>> stateChangeCriterias);
	~SettingTitleUIState() = default;

	/*終了*/
	void Finalize() override;

	/*この状態に入った時の処理*/
	void OnEnter(UIBase* ui, STATE_TYPE_UI preState) override;
	/*この状態を出る時の処理*/
	void OnExit(UIBase* ui, STATE_TYPE_UI nextState) override;

	/*更新*/
	void Update(UIBase* ui) override;
	/*決定*/
	void Decision(UIBase* ui) override;
	/*戻る*/
	void Close(UIBase* ui) override;
	/*描画*/
	void Draw(UIBase* ui) override;
};



/*----------------------*/
/*【キャラクター種類選択UIステート】*/
/*----------------------*/
class CharacterSelectTitleUIState : public IStateUI, public TitleUIStateProcess
{
public:
	// FIXME: コンストラクタでステート変更条件を渡せます
	CharacterSelectTitleUIState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>> stateChangeCriterias);
	~CharacterSelectTitleUIState() = default;

	/*終了*/
	void Finalize() override;

	/*この状態に入った時の処理*/
	void OnEnter(UIBase* ui, STATE_TYPE_UI preState) override;
	/*この状態を出る時の処理*/
	void OnExit(UIBase* ui, STATE_TYPE_UI nextState) override;

	/*更新*/
	void Update(UIBase* ui) override;
	/*決定*/
	void Decision(UIBase* ui) override;
	/*戻る*/
	void Close(UIBase* ui) override;
	/*描画*/
	void Draw(UIBase* ui) override;
};



/*----------------------*/
/*【プレイヤー名設定UIステート】*/
/*----------------------*/
class PlayerNameTitleUIState : public IStateUI, public TitleUIStateProcess
{
public:
	// FIXME: コンストラクタでステート変更条件を渡せます
	PlayerNameTitleUIState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>> stateChangeCriterias);
	~PlayerNameTitleUIState() = default;

	/*終了*/
	void Finalize() override;

	/*この状態に入った時の処理*/
	void OnEnter(UIBase* ui, STATE_TYPE_UI preState) override;
	/*この状態を出る時の処理*/
	void OnExit(UIBase* ui, STATE_TYPE_UI nextState) override;

	/*更新*/
	void Update(UIBase* ui) override;
	/*決定*/
	void Decision(UIBase* ui) override;
	/*戻る*/
	void Close(UIBase* ui) override;
	/*描画*/
	void Draw(UIBase* ui) override;
};



/*----------------------*/
/*【入力情報の最終確認UIステート】*/
/*----------------------*/
class InputCheckTitleUIState : public IStateUI, public TitleUIStateProcess
{
public:
	// FIXME: コンストラクタでステート変更条件を渡せます
	InputCheckTitleUIState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>> stateChangeCriterias);
	~InputCheckTitleUIState() = default;

	/*終了*/
	void Finalize() override;

	/*この状態に入った時の処理*/
	void OnEnter(UIBase* ui, STATE_TYPE_UI preState) override;
	/*この状態を出る時の処理*/
	void OnExit(UIBase* ui, STATE_TYPE_UI nextState) override;

	/*更新*/
	void Update(UIBase* ui) override;
	/*決定*/
	void Decision(UIBase* ui) override;
	/*戻る*/
	void Close(UIBase* ui) override;
	/*描画*/
	void Draw(UIBase* ui) override;
};



/*----------------------*/
/*【画面サイズ調整UIステート】*/
/*----------------------*/
class ScreenSizeTitleUIState : public IStateUI, public TitleUIStateProcess
{
public:
	// FIXME: コンストラクタでステート変更条件を渡せます
	ScreenSizeTitleUIState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>> stateChangeCriterias);
	~ScreenSizeTitleUIState() = default;

	/*終了*/
	void Finalize() override;

	/*この状態に入った時の処理*/
	void OnEnter(UIBase* ui, STATE_TYPE_UI preState) override;
	/*この状態を出る時の処理*/
	void OnExit(UIBase* ui, STATE_TYPE_UI nextState) override;

	/*更新*/
	void Update(UIBase* ui) override;
	/*決定*/
	void Decision(UIBase* ui) override;
	/*戻る*/
	void Close(UIBase* ui) override;
	/*描画*/
	void Draw(UIBase* ui) override;
};



/*----------------------*/
/*【音量調整UIステート】*/
/*----------------------*/
class VolumeTitleUIState : public IStateUI, public TitleUIStateProcess
{
public:
	// FIXME: コンストラクタでステート変更条件を渡せます
	VolumeTitleUIState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>> stateChangeCriterias);
	~VolumeTitleUIState() = default;

	/*終了*/
	void Finalize() override;

	/*この状態に入った時の処理*/
	void OnEnter(UIBase* ui, STATE_TYPE_UI preState) override;
	/*この状態を出る時の処理*/
	void OnExit(UIBase* ui, STATE_TYPE_UI nextState) override;

	/*更新*/
	void Update(UIBase* ui) override;
	/*決定*/
	void Decision(UIBase* ui) override;
	/*戻る*/
	void Close(UIBase* ui) override;
	/*描画*/
	void Draw(UIBase* ui) override;
};