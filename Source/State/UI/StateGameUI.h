#pragma once
#include <vector>

#include "ObjectBases.h"
#include "StateBase.h"

class MapManager;
class TargetManager;

/*----------------------*/
/*【ゲームUIステート】*/
/*----------------------*/

enum GAME_UI_STATE
{
    START_GAME_UI_STAE = 0, // ゲーム開始
    NORMAL_GAME_UI_STATE,   // 通常
    PAUSE_GAME_UI_STATE,	// ポーズ
};

/*----------*/
/*【ゲームUI共通処理用】
/*----------*/
class GameUIProcess
{
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
};

/*----------------------*/
/*【ポーズUIステート】*/
/*----------------------*/
class PauseGameUIState : public IStateUI, public GameUIProcess
{
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
};