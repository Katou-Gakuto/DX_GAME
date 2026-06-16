#include <vector>

#include "BitFlag.h"
#include "DrawData.h"
#include "MiniMapData.h"
#include "ResourceData.h"
#include "Vector2.h"

#include "DxLib.h"

#include "Master.h"

#include "DataManager.h"
#include "DrawManager.h"
#include "EndManager.h"
#include "GameManager.h"
#include "KeyState.h"
#include "MapManager.h"
#include "ObjectBase.h"
#include "ObjectManager.h"
#include "ResourceManager.h"
#include "StateConfigUi.h"
#include "StateGameUI.h"
#include "TargetManager.h"
#include "UI_Check.h"
#include "UtilCalc.h"

/*--------------------------------*/
/*     【ゲームUIステート】     */
/*--------------------------------*/

/*----------*/
/*【ゲームUI共通処理用】
/*----------*/
GameUIProcess::GameUIProcess()
: mnPreSelectNumber(0)
, mpMapManager(Master::mpGameManager->GetMapManager())
, mpTargetManager(Master::mpGameManager->GetTargetManager())
{
//     // 画面サイズ取得
//     COORDINATE_X_Y_INT set = XYGet_Int(0, 0);
//     int colorBit = 0;
//     GetScreenState(&set.x, &set.y, &colorBit);
//     /*
//     msMapUpperLeft = XYGet((set.x / 10) * 0.2, set.y / 24); // 左上
//     msMapLowerRight = XYGet((set.x / 10) * 1.67, set.y / 4);  // 右下*/
// //    /*
//     msMapUpperLeft = XYGet((set.x / 10) * 8.33 , set.y / 24); // 左上
//     msMapLowerRight = XYGet((set.x / 10) *  9.8, set.y / 4);  // 右下*/
//     msMapSide = XYGet((msMapLowerRight.x - msMapUpperLeft.x), (msMapLowerRight.y - msMapUpperLeft.y));  // 一辺
//     mnMapFrameDreadth = 5;
//     msMapMiddle = XYGet((msMapSide.x / 2) + mnMapFrameDreadth, (msMapSide.y / 2) + mnMapFrameDreadth);

//     mnMapDrawHandle = MakeScreen(msMapSide.x + (mnMapFrameDreadth * 2), msMapSide.y + (mnMapFrameDreadth * 2), TRUE);
//     mnDrawMiniMapScreenHandle = MakeScreen();
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
    // // TODO: 画像ハンドルに変更
    // DisplaySize displaySize = ResourceManager::mstDisplaySize;
    // Vector2_Int leftUp = displaySize.LeftUp_FloatRatio(0.1f);
    // Vector2_Int rightDown = displaySize.RightDown_FloatRatio(0.1f);
    // DrawBox(leftUp.x, leftUp.y, rightDown.x, rightDown.y, GetColor(255, 255, 255), TRUE);

    // Vector2_Int stringDrawPos = displaySize.LeftUp_Ratio(Vector2(0.5f, 0.11f));
    // DrawString(stringDrawPos.x - 50, stringDrawPos.y, "メニュー", GetColor(0, 0, 0));
}

// ミニマップポジションに変換する
VECTOR GameUIProcess::PosToMiniMapPos(VECTOR pos)
{
    VECTOR minMapPos;


    return minMapPos;
}

// /*------------------------*/
// /*【ゲーム開始UIステート】*/
// /*------------------------*/
// StartGameUIState::StartGameUIState()
// : GameUIProcess()
// , mnElapsedTime(0)
// , mbFadeInFlag(false)
// , mbMenuFlag(false)
// {
//     mStateNumber = (int)GAME_UI_STATE::START_GAME_UI_STAE;
// }

// // この状態に入った時の処理
// void StartGameUIState::OnEnter(UIBase* ui)
// {
//     mbFadeInFlag = false;
//     mnElapsedTime = Master::mpTimeManager->GetGameTime() + SUBTITLE_TIME;
    
//     ui->SetAnimationType(ANIMATION_TYPE::FADE_IN);

//     ui->GetAnimation(MODEL_CONTROLLER_INDEX)->SetAnimationType(ANIMATION_TYPE::FADE_OUT);
// }

// // この状態を出る時の処理
// void StartGameUIState::OnExit(UIBase* ui)
// {
// }

// // 更新
// int StartGameUIState::Update(UIBase* ui)
// {
//     if (IsMenuKeyPressed())
//     {
//         mbMenuFlag = true;
//     }
//     else if (!mbMenuFlag && !(mnElapsedTime < Master::mpTimeManager->GetGameTime()))
//     {
//         return mStateNumber;
//     }

//     if (!mbFadeInFlag &&
//         !ui->GetAnimation(MODEL_CONTROLLER_INDEX)->GetFsm()->CheckNowStateSameType(ANIMATION_TYPE::FADE_IN))
//     {
//         ui->GetAnimation(MODEL_CONTROLLER_INDEX)->SetAnimationType(ANIMATION_TYPE::FADE_IN);
//     }
//     else if (ui->GetAnimation(MODEL_CONTROLLER_INDEX)->GetFsm()->CheckNowStateSameType(ANIMATION_TYPE::FADE_IN))
//     {
//         mbFadeInFlag = true;
//     }
//     else if (!ui->GetAnimation(MODEL_CONTROLLER_INDEX)->GetFsm()->CheckNowStateSameType(ANIMATION_TYPE::FADE_IN))
//     {
//         if (mbMenuFlag)
//         {
//             ui->SetSelectNumber(GAME_UI_SELECT_NUKMBER::STOP_GAME);
//             ui->Decision();
//             return (int)GAME_UI_STATE::PAUSE_GAME_UI_STATE;
//         }
//         else
//         {
//             return (int)GAME_UI_STATE::NORMAL_GAME_UI_STATE;
//         }
//     }

//     return mStateNumber;
// }

// // 決定
// int StartGameUIState::Decision(UIBase* ui)
// {
//     return mStateNumber;
// }

// // 描画
// void StartGameUIState::Draw(UIBase* ui)
// {
// }

// // 終了
// int StartGameUIState::Cloce(UIBase* ui)
// {
//     return mStateNumber;
// }

/*----------------------*/
/*【通常ゲームUIステート】*/
/*----------------------*/
NormalGameUIState::NormalGameUIState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, void>> stateChangeCriterias)
: IStateUI(STATE_TYPE_UI::NORMAL_GAME_UI_STATE, stateChangeCriterias)
, GameUIProcess()
{
    mStateNumber = (int)GAME_UI_STATE::NORMAL_GAME_UI_STATE;
}

// この状態に入った時の処理
void NormalGameUIState::OnEnter(UIBase* ui)
{
    //printfDx("テロップ：通常ゲームUI\n");
    ui->SetAnimationType(ANIMATION_TYPE::FADE_IN);

    // for (int i = 0; i < ui->GetModelCount(); i++)
    // {
    //     ui->GetModelsController(i)->SetModelDrawFlag(false);
    // }
    
    ui->SetSelectNumber(GAME_UI_SELECT_NUKMBER::PLAY_GAME);
    ui->Decision();
}

// この状態を出る時の処理
void NormalGameUIState::OnExit(UIBase* ui)
{
    ui->SetSelectNumber(GAME_UI_SELECT_NUKMBER::STOP_GAME);
    ui->Decision();
}

// 更新
STATE_TYPE_UI NormalGameUIState::Update(UIBase* ui)
{
    if (IsMenuKeyPressed())
    {
        return STATE_TYPE_UI::PAUSE_GAME_UI_STATE;
    }

    return mStateNumber;
}

// 決定
STATE_TYPE_UI NormalGameUIState::Decision(UIBase* ui)
{
    return STATE_TYPE_UI::PAUSE_GAME_UI_STATE;
}

// 描画
void NormalGameUIState::Draw(UIBase* ui)
{
}

// 終了
STATE_TYPE_UI NormalGameUIState::Cloce(UIBase* ui)
{
    return mStateNumber;
}

/*----------------------*/
/*【ポーズUIステート】*/
/*----------------------*/
PauseGameUIState::PauseGameUIState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, void>> stateChangeCriterias)
: IStateUI(STATE_TYPE_UI::PAUSE_GAME_UI_STATE, stateChangeCriterias)
, GameUIProcess()
{
    mStateNumber = (int)GAME_UI_STATE::PAUSE_GAME_UI_STATE;
 
 
    DRAW_DATA drawData = DRAW_DATA();
    DisplaySize displaySize = ResourceManager::mstDisplaySize;
    Vector2_Int menuLeftUpPos = displaySize.LeftUp_Ratio(Vector2(0.15625f, 0.2125f));
    Vector2_Int menuRightDown = displaySize.LeftUp_Ratio(Vector2(0.53125f, 0.5375f));
    // 共通描画情報設定
    {
        drawData.drawFlag = false;
        drawData.drawManagerDrawType = DRAW_MANAGER_DRAW_TYPE::GRAPH;
        drawData.drawGraphData.drawType = DRAW_GRAPH_TYPE::SIZE;
        drawData.drawGraphData.transFlag = TRUE;
        drawData.drawGraphData.size = displaySize.LeftUp_Ratio(Vector2(0.30625f, 0.2625f));
        drawData.drawGraphData.transFlag = TRUE;
    }

    {
        // 戻る
        {
            drawData.drawGraphData.pos = Vector2_Int(menuLeftUpPos.x, menuLeftUpPos.y);
            drawData.drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/MenuString_Back.png");
            mstMenuStringDrawData[MENU_STRING_TYPE::RETURN_GAME] = drawData;
            drawData.drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/MenuString_BackPush.png");
            mstMenuStringDrawData[MENU_STRING_TYPE::PUSH_RETURN_GAME] = drawData;
        }

        // コンフィグ
        {
            drawData.drawGraphData.pos = Vector2_Int(menuRightDown.x, menuLeftUpPos.y);
            drawData.drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/MenuString_Config.png");
            mstMenuStringDrawData[MENU_STRING_TYPE::CONFIG_SET] = drawData;
            drawData.drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/MenuString_ConfigPush.png");
            mstMenuStringDrawData[MENU_STRING_TYPE::PUSH_CONFIG_SET] = drawData;
        }
        
        // ステータス
        {
            drawData.drawGraphData.pos = Vector2_Int(menuLeftUpPos.x, menuRightDown.y);
            drawData.drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/MenuString_Status.png");
            mstMenuStringDrawData[MENU_STRING_TYPE::STATUS_DRAW] = drawData;
            drawData.drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/MenuString_StatusPush.png");
            mstMenuStringDrawData[MENU_STRING_TYPE::PUSH_STATUS_DRAW] = drawData;
        }
        
        // ゲーム終了
        {
            drawData.drawGraphData.pos = Vector2_Int(menuRightDown.x, menuRightDown.y);
            drawData.drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/MenuString_GameEnd.png");
            mstMenuStringDrawData[MENU_STRING_TYPE::GAME_END] = drawData;
            drawData.drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/MenuString_GameEndPush.png");
            mstMenuStringDrawData[MENU_STRING_TYPE::PUSH_GAME_END] = drawData;
        }
    }

    for (int i = 0; i < MENU_STRING_TYPE::MENU_STRING_MAX; i++)
    {
        Master::mpDrawManager->AddDrawData(&mstMenuStringDrawData[i]);
        
            Master::mpImguiManager->SetIntImgui(IMGUI_INT_DATA::GetImguiData(
                                                                            { &mstMenuStringDrawData[i].drawGraphData.pos.x, &mstMenuStringDrawData[i].drawGraphData.pos.y, &mstMenuStringDrawData[i].drawGraphData.size.x, &mstMenuStringDrawData[i].drawGraphData.size.y },
                                                                            1.0f,
                                                                            1.0f,
                                                                            1.0f,
                                                                            0,
                                                                            1000,
                                                                            "CONFIG_SELECT_STRING_DRAW_",
                                                                            "%d",
                                                                            0,
                                                                            IMGUI_TYPE::DRAG4,
                                                                            false
                                                                            )
                                                );
            Master::mpImguiManager->SetIntImgui(IMGUI_INT_DATA::GetImguiData(
                                                                            { &mstMenuStringDrawData[i].drawGraphData.pos.x, &mstMenuStringDrawData[i].drawGraphData.pos.y, &mstMenuStringDrawData[i].drawGraphData.size.x, &mstMenuStringDrawData[i].drawGraphData.size.y },
                                                                            1.0f,
                                                                            1.0f,
                                                                            1.0f,
                                                                            0,
                                                                            1000,
                                                                            "CONFIG_SELECT_STRING_DRAW_",
                                                                            "%d",
                                                                            0,
                                                                            IMGUI_TYPE::DRAG4
                                                                            )
                                                );
    }
}

// この状態に入った時の処理
void PauseGameUIState::OnEnter(UIBase* ui)
{
    //printfDx("テロップ：ポーズUI\n");

    ui->SetAnimationType(ANIMATION_TYPE::FADE_OUT);

    ui->SetSelectMaxNumber(GAME_UI_SELECT_NUKMBER::PAUSE_SELECT_MAX);
    ui->SetSelectBoundaryValue(2);

    if (ui->GetSelectNumber() < 0)
    {
        ui->SetSelectNumber(0);
    }
    else
    {
        ui->SetSelectNumber(mnPreSelectNumber);
    }

    for (int i = MENU_STRING_TYPE::RETURN_GAME; i < MENU_STRING_TYPE::PUSH_RETURN_GAME; i++)
    {
        mstMenuStringDrawData[i].drawFlag = true;
    }
    // セーブテスト
    //Master::mpDataManager->Save(Master::mpGameManager->GetTargetManager()->GetTarget(TARGET_TYPE::PLAYER));

    // for (int i = 0; i < ui->GetModelCount(); i++)
    // {
    //     ui->GetModelsController(i)->SetModelDrawFlag(true);
    // }
}

// この状態を出る時の処理
void PauseGameUIState::OnExit(UIBase* ui)
{
    mnPreSelectNumber = ui->GetSelectNumber();

    for (int i = 0; i < MENU_STRING_TYPE::MENU_STRING_MAX; i++)
    {
        mstMenuStringDrawData[i].drawFlag = false;
    }
}

// 更新
STATE_TYPE_UI PauseGameUIState::Update(UIBase* ui)
{
    if (IsMenuKeyPressed())
    {
        return STATE_TYPE_UI::NORMAL_GAME_UI_STATE;
    }

    ui->DefaultSelectProcess();
    ui->LeftRightSelectProcess();

    if (ui->GetSelectNumberFlag().Bool())
    {
        for (int i = 0; i < GAME_UI_SELECT_NUKMBER::PAUSE_SELECT_MAX; i++)
        {
            if (i == ui->GetSelectNumber())
            {
                mstMenuStringDrawData[MENU_STRING_TYPE::PUSH_RETURN_GAME + i].drawFlag = true;
            }
            else
            {
                mstMenuStringDrawData[MENU_STRING_TYPE::PUSH_RETURN_GAME + i].drawFlag = false;
            }
        }
    }

    return mStateNumber;
}

// 決定
STATE_TYPE_UI PauseGameUIState::Decision(UIBase* ui)
{
    switch (ui->GetSelectNumber())
    {
    case GAME_UI_SELECT_NUKMBER::UI_CLOSE:
        return STATE_TYPE_UI::NORMAL_GAME_UI_STATE;
        
    case GAME_UI_SELECT_NUKMBER::UI_DRAW_PLAYER_DATA:
        return STATE_TYPE_UI::DRAW_PLAYER_DATA_UI_STATE;
        
    case GAME_UI_SELECT_NUKMBER::UI_CONFIG_CHANGE:
        // return (int)GAME_UI_STATE::CONFIG_CHANGE_UI_STATE;
        return STATE_TYPE_UI::CONFIG_CHANGE_UI_STATE; // FIXME: map complex config mapping if needed
        
    case GAME_UI_SELECT_NUKMBER::UI_GAME_END:
        return STATE_TYPE_UI::GAME_END_UI_STATE;
    }

    return mStateNumber;
}

// 描画
void PauseGameUIState::Draw(UIBase* ui)
{
    clsDx();
    printfDx("%d : UInannba\n", ui->GetSelectNumber());

    DrawMenuBackground(ui);
}

// 終了
STATE_TYPE_UI PauseGameUIState::Cloce(UIBase* ui)
{
    return mStateNumber;
}

/*------------------------------*/
/*【プレイヤー情報表示ステート】*/
/*------------------------------*/
DrawPlayerDataState::DrawPlayerDataState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, void>> stateChangeCriterias)
: IStateUI(STATE_TYPE_UI::DRAW_PLAYER_DATA_UI_STATE, stateChangeCriterias)
, GameUIProcess()
{
    mStateNumber = (int)GAME_UI_STATE::DRAW_PLAYER_DATA_UI_STATE;
}

// この状態に入った時の処理
void DrawPlayerDataState::OnEnter(UIBase* ui)
{
}

// この状態を出る時の処理
void DrawPlayerDataState::OnExit(UIBase* ui)
{
}

// 更新
STATE_TYPE_UI DrawPlayerDataState::Update(UIBase* ui)
{
    if (IsMenuKeyPressed())
    {
        return STATE_TYPE_UI::NORMAL_GAME_UI_STATE;
    }

    ui->DefaultDecision();

    ui->DefaultCloce();

    return mStateNumber;
}

// 決定
STATE_TYPE_UI DrawPlayerDataState::Decision(UIBase* ui)
{
    return STATE_TYPE_UI::PAUSE_GAME_UI_STATE;
}

// 描画
void DrawPlayerDataState::Draw(UIBase* ui)
{
}

// 終了
STATE_TYPE_UI DrawPlayerDataState::Cloce(UIBase* ui)
{
    return STATE_TYPE_UI::PAUSE_GAME_UI_STATE;
}

/*--------------------*/
/*【設定変更ステート】*/
/*--------------------*/
ConfigChangeState::ConfigChangeState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, void>> stateChangeCriterias)
: IStateUI(STATE_TYPE_UI::CONFIG_CHANGE_UI_STATE, stateChangeCriterias)
, GameUIProcess()
{
    mStateNumber = (int)GAME_UI_STATE::CONFIG_CHANGE_UI_STATE;
}

// この状態に入った時の処理
void ConfigChangeState::OnEnter(UIBase* ui)
{
    ui->SetSelectNumber(mnPreSelectNumber);
    ui->SetSelectMaxNumber(CONFIG_SELECT_TYPE::MAX);
    ui->SetSelectBoundaryValue(1);
}

// この状態を出る時の処理
void ConfigChangeState::OnExit(UIBase* ui)
{
}

// 更新
STATE_TYPE_UI ConfigChangeState::Update(UIBase* ui)
{
    if (IsMenuKeyPressed())
    {
        return STATE_TYPE_UI::NORMAL_GAME_UI_STATE;
    }

    ui->LeftRightSelectProcess();
    ui->DefaultDecision();
    ui->DefaultCloce();

    printfDx("%d\n", ui->GetSelectNumber());

    return mStateNumber;
}

// 決定
STATE_TYPE_UI ConfigChangeState::Decision(UIBase* ui)
{
    switch (ui->GetSelectNumber())
    {
    case CONFIG_SELECT_TYPE::BACK_TO_MENU:
        return STATE_TYPE_UI::PAUSE_GAME_UI_STATE;

    case CONFIG_SELECT_TYPE::MINI_MAP:
        break;
    }

    return mStateNumber;
}

// 描画
void ConfigChangeState::Draw(UIBase* ui)
{
}

// 終了
STATE_TYPE_UI ConfigChangeState::Cloce(UIBase* ui)
{
    return STATE_TYPE_UI::PAUSE_GAME_UI_STATE;
}

/*----------------------*/
/*【ゲーム終了ステート】*/
/*----------------------*/
GameEndState::GameEndState()
: GameUIProcess()
, mbReturnFlag(false)
{
    mStateNumber = (int)GAME_UI_STATE::GAME_END_UI_STATE;
}

// この状態に入った時の処理
void GameEndState::OnEnter(UIBase* ui)
{
    mbReturnFlag = false;

    printfDx("TEST\n");

    // 確認UI
    UI_Check<GameEndState>* uiCheck = new UI_Check<GameEndState>(nullptr, nullptr, &GameEndState::GameEnd, &GameEndState::StateReturn, this, this, "終了しますか?");
    uiCheck->Initilize();
}

// この状態を出る時の処理
void GameEndState::OnExit(UIBase* ui)
{
}

// 更新
STATE_TYPE_UI GameEndState::Update(UIBase* ui)
{
    if (mbReturnFlag)
    {
        return STATE_TYPE_UI::PAUSE_GAME_UI_STATE;
    }

    return mStateNumber;
}

// 決定
STATE_TYPE_UI GameEndState::Decision(UIBase* ui)
{
    return mStateNumber;
}

// 描画
void GameEndState::Draw(UIBase* ui)
{
}

// ステートを戻る
void GameEndState::StateReturn(void *null)
{
    mbReturnFlag = true;
}

// 終了する
void GameEndState::GameEnd(void *null)
{
    Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::WITHIN_EXPECTATION_FLAG);
}

// 終了
STATE_TYPE_UI GameEndState::Cloce(UIBase* ui)
{
    return mStateNumber;
}