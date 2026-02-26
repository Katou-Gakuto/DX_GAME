#pragma once
#include <vector>

#include "ObjectBases.h"
#include "StateBase.h"
#include "UI_Check.h"

class MapManager;
class TargetManager;

/*----------------------*/
/*【ゲームUIステート】*/
/*----------------------*/

enum class GAME_UI_STATE
{
    START_GAME_UI_STAE = 0, // ゲーム開始
    NORMAL_GAME_UI_STATE,   // 通常
    PAUSE_GAME_UI_STATE,	// ポーズ

    DRAW_PLAYER_DATA_UI_STATE,  // プレイヤー情報描画
    CONFIG_CHANGE_UI_STATE, // 設定変更

    GAME_END_UI_STATE,  // ゲーム終了
};

/*----------------------------*/
/*【ゲームUI選択ナンバーEnum】*/
/*----------------------------*/
enum GAME_UI_SELECT_NUKMBER
{
    PLAY_GAME = -2,
    STOP_GAME,

    /*---------- PAUSE選択用 ----------*/
    UI_CLOSE = 0,           // 閉じる
    UI_DRAW_PLAYER_DATA,    // プレイヤー情報
    UI_CONFIG_CHANGE,       // 設定変更
    UI_GAME_END,            // ゲーム終了
    PAUSE_SELECT_MAX,       // ポーズ選択最大数
};

/*----------*/
/*【ゲームUI共通処理用】
/*----------*/
class GameUIProcess
{
protected:
    // 前の選択数
    int mnPreSelectNumber;

private:
    // マップマネージャー
    MapManager* mpMapManager;

    // ターゲットマネージャー
    TargetManager* mpTargetManager;

    // プレイヤーポジション
    VECTOR mvPlayerPos;

    // プレイヤーアングル
    VECTOR mvPlayerAngle;

public:
    GameUIProcess();

protected:
    /*メニューキーを押したか返す*/
    bool IsMenuKeyPressed();

    // TODO: 後々モデルコントローラーで表示が理想

    /*メニューの背景描画*/
    void DrawMenuBackground(UIBase* ui);

    /*ミニマップ表示*/
    void DrawMinMap();

    /*ミニマップ座標に変換する*/
    VECTOR PosToMinMapPos(VECTOR pos);
};

/*------------------------*/
/*【ゲーム開始UIステート】*/
/*------------------------*/
class StartGameUIState : public IStateUI, public GameUIProcess
{
private:
    // 経過時間
    int mnElapsedTime;

    // フェードインフラグ
    bool mbFadeInFlag;

    // モデルコントローラの添え字
    const int MODEL_CONTROLLER_INDEX = 1;

    // 字幕表示時間
    const int SUBTITLE_TIME = 17 * 230;

public:
    StartGameUIState();
    ~StartGameUIState() = default;

    /// <summary>この状態に入った時の処理</summary>
    void OnEnter(UIBase* ui) override;
    /// <summary>この状態を出る時の処理</summary>
    void OnExit(UIBase* ui) override;

    /// <summary>更新</summary>
    int Update(UIBase* ui) override;

    /// <summary>決定</summary>
    int Decision(UIBase* ui) override;

    /// <summary>描画</summary>
    void Draw(UIBase* ui) override;

	/// <summary>終了</summary>
	int Cloce(UIBase* ui) override;
};

/*----------------------*/
/*【通常ゲームUIステート】*/
/*----------------------*/
class NormalGameUIState : public IStateUI, public GameUIProcess
{
public:
    NormalGameUIState();
    ~NormalGameUIState() = default;

    /// <summary>この状態に入った時の処理</summary>
    void OnEnter(UIBase* ui) override;
    /// <summary>この状態を出る時の処理</summary>
    void OnExit(UIBase* ui) override;

    /// <summary>更新</summary>
    int Update(UIBase* ui) override;

    /// <summary>決定</summary>
    int Decision(UIBase* ui) override;

    /// <summary>描画</summary>
    void Draw(UIBase* ui) override;

	/// <summary>終了</summary>
	int Cloce(UIBase* ui) override;
};

/*----------------------*/
/*【ポーズUIステート】*/
/*----------------------*/
class PauseGameUIState : public IStateUI, public GameUIProcess
{
private:
public:
    PauseGameUIState();
    ~PauseGameUIState() = default;

    /// <summary>この状態に入った時の処理</summary>
    void OnEnter(UIBase* ui) override;
    /// <summary>この状態を出る時の処理</summary>
    void OnExit(UIBase* ui) override;

    /// <summary>更新</summary>
    int Update(UIBase* ui) override;

    /// <summary>決定</summary>
    int Decision(UIBase* ui) override;

    /// <summary>描画</summary>
    void Draw(UIBase* ui) override;

	/// <summary>終了</summary>
	int Cloce(UIBase* ui) override;
};


/*------------------------------*/
/*【プレイヤー情報表示ステート】*/
/*------------------------------*/
class DrawPlayerDataState : public IStateUI, public GameUIProcess
{
public:
    DrawPlayerDataState();
    ~DrawPlayerDataState() = default;

    /// <summary>この状態に入った時の処理</summary>
    void OnEnter(UIBase* ui) override;
    /// <summary>この状態を出る時の処理</summary>
    void OnExit(UIBase* ui) override;

    /// <summary>更新</summary>
    int Update(UIBase* ui) override;

    /// <summary>決定</summary>
    int Decision(UIBase* ui) override;

    /// <summary>描画</summary>
    void Draw(UIBase* ui) override;

	/// <summary>終了</summary>
	int Cloce(UIBase* ui) override;
};

/*--------------------*/
/*【設定変更ステート】*/
/*--------------------*/
class ConfigChangeState : public IStateUI, public GameUIProcess
{
private:
public:
    ConfigChangeState();
    ~ConfigChangeState() = default;

    /// <summary>この状態に入った時の処理</summary>
    void OnEnter(UIBase* ui) override;
    /// <summary>この状態を出る時の処理</summary>
    void OnExit(UIBase* ui) override;

    /// <summary>更新</summary>
    int Update(UIBase* ui) override;

    /// <summary>決定</summary>
    int Decision(UIBase* ui) override;

    /// <summary>描画</summary>
    void Draw(UIBase* ui) override;

	/// <summary>終了</summary>
	int Cloce(UIBase* ui) override;
};

/*----------------------*/
/*【ゲーム終了ステート】*/
/*----------------------*/
class GameEndState : public IStateUI, public GameUIProcess
{
private:
    // 戻るフラグ
    bool mbReturnFlag;
public:
    GameEndState();
    ~GameEndState() = default;

    /// <summary>この状態に入った時の処理</summary>
    void OnEnter(UIBase* ui) override;
    /// <summary>この状態を出る時の処理</summary>
    void OnExit(UIBase* ui) override;

    /// <summary>更新</summary>
    int Update(UIBase* ui) override;

    /// <summary>決定</summary>
    int Decision(UIBase* ui) override;

    /// <summary>描画</summary>
    void Draw(UIBase* ui) override;

    /*ステートを戻る*/
    void StateReturn(void *null);

    /*終了する*/
    void GameEnd(void *null);

	/// <summary>終了</summary>
	int Cloce(UIBase* ui) override;
};