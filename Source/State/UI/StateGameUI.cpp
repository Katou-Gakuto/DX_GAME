#include "ResourceData.h"
#include "Vector2.h"

#include "DxLib.h"

#include "Master.h"

#include "GameManager.h"
#include "KeyState.h"
#include "MapManager.h"
#include "ObjectBases.h"
#include "StateGameUI.h"
#include "TargetManager.h"
#include "UtilCalc.h"

/*--------------------------------*/
/*     【ゲームUIステート】     */
/*--------------------------------*/

/*----------*/
/*【ゲームUI共通処理用】
/*----------*/
GameUIProcess::GameUIProcess()
{
    mpMapManager = Master::mpGameManager->GetMapManager();
    mpTargetManager = Master::mpGameManager->GetTargetManager();
}

// メニューキーを押したか返す
bool GameUIProcess::IsMenuKeyPressed()
{
    // TODO: キー仮設定
    return Master::mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::X);
}

// メニューの背景描画
void GameUIProcess::DrawMenuBackground(UIBase* ui)
{
    // TODO: 画像ハンドルに変更
    DisplaySize displaySize = ui->GetDisplaySize();
    Vector2_Int leftUp = displaySize.LeftUp_FloatRatio(0.1f);
    Vector2_Int rightDown = displaySize.RightDown_FloatRatio(0.1f);
    DrawBox(leftUp.x, leftUp.y, rightDown.x, rightDown.y, GetColor(255, 255, 255), TRUE);

    Vector2_Int stringDrawPos = displaySize.LeftUp_Ratio(Vector2(0.5f, 0.11f));
    DrawString(stringDrawPos.x - 50, stringDrawPos.y, "メニュー", GetColor(0, 0, 0));
}

// ミニマップ表示
void GameUIProcess::DrawMinMap()
{
    // INPROGRESS: 実装　あとエフェクトのエラー削除ファイルごとにやればいいらしい 2Dは影がいらないからstopマネージャーで描画処理自体を一回で済むようにする

    // 範囲外計算
    {
        mvPlayerPos = mpTargetManager->GetTarget(TARGET_TYPE::PLAYER).target->GetPos();
        mvPlayerAngle = mpTargetManager->GetTarget(TARGET_TYPE::PLAYER).target->GetAngle();

    }


    // 描画

}

// ミニマップポジションに変換する
VECTOR GameUIProcess::PosToMinMapPos(VECTOR pos)
{
    VECTOR minMapPos;


    return minMapPos;
}

/*----------------------*/
/*【通常ゲームUIステート】*/
/*----------------------*/

NormalGameUIState::NormalGameUIState()
{
    mStateNumber = (int)GAME_UI_STATE::NORMAL_GAME_UI_STATE;
}

// この状態に入った時の処理
void NormalGameUIState::OnEnter(UIBase* ui)
{
    printfDx("テロップ：通常ゲームUI\n");
}

// この状態を出る時の処理
void NormalGameUIState::OnExit(UIBase* ui)
{
}

// 更新
int NormalGameUIState::Update(UIBase* ui)
{
    if (IsMenuKeyPressed())
    {
        ui->SetSelectNumber(2);
        ui->Decision();
    }

    return mStateNumber;
}

// 決定
int NormalGameUIState::Decision(UIBase* ui)
{
    return (int)GAME_UI_STATE::PAUSE_GAME_UI_STATE;
}

// 描画
void NormalGameUIState::Draw(UIBase* ui)
{
    DrawMinMap();
}

/*----------------------*/
/*【ポーズUIステート】*/
/*----------------------*/

PauseGameUIState::PauseGameUIState()
{
    mStateNumber = (int)GAME_UI_STATE::PAUSE_GAME_UI_STATE;
}

// この状態に入った時の処理
void PauseGameUIState::OnEnter(UIBase* ui)
{
    ui->SetSelectNumber(0);
    ui->Decision();
    printfDx("テロップ：ポーズUI\n");
}

// この状態を出る時の処理
void PauseGameUIState::OnExit(UIBase* ui)
{
    ui->SetSelectNumber(1);
    ui->Decision();
}

// 更新
int PauseGameUIState::Update(UIBase* ui)
{
    if (IsMenuKeyPressed())
    {
        ui->SetSelectNumber(2);
        ui->Decision();
    }

    return mStateNumber;
}

// 決定
int PauseGameUIState::Decision(UIBase* ui)
{
    return (int)GAME_UI_STATE::NORMAL_GAME_UI_STATE;
}

// 描画
void PauseGameUIState::Draw(UIBase* ui)
{
    DrawMinMap();

    DrawMenuBackground(ui);
}