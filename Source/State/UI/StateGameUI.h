#pragma once
#include "ObjectBases.h"
#include "StateBase.h"

/*----------------------*/
/*【ゲームUIステート】*/
/*----------------------*/

enum class GAME_UI_STATE
{
    NORMAL_GAME_UI_STATE = 0,		// 通常
    PAUSE_GAME_UI_STATE,			// ポーズ
};

/*----------*/
/*【ゲームUI共通処理用】
/*----------*/
class GameUIProcess
{
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