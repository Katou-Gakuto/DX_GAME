#include "FSM.h"
#include "UI_Game.h"

UI_Game::UI_Game()
: UIBase(true, 1, false)
{
}

UI_Game::~UI_Game()
{
}

// UI初期化
void UI_Game::UIInitilize()
{
}

// UI終了
void UI_Game::UIFinalize()
{
}

// UI更新
void UI_Game::UIUpdate()
{
}

// UI最終更新
void UI_Game::UILastUpdate()
{
}

// UI描画
void UI_Game::UIDraw()
{
}

// 選択決定時処理
void UI_Game::DecisionProcess()
{
    switch (mnSelectNumber)
    {
    case 0:
        SetUINumber();
        mpResourceManager->StopAllEfect();
        break;

    case 1:
        DeleteUINumber();
        mpResourceManager->PlayAllEfect();
        break;

    default:
        mpFsm->Decision(this);
        break;
    }
}