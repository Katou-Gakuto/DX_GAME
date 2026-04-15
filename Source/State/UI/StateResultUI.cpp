#include <string>
#include <vector>

#include "GameDataEnum.h"
#include "ResourceData.h"
#include "GameDatas.h"
#include "Vector2.h"

#include "Master.h"

#include "DataManager.h"
#include "DrawManager.h"
#include "EndManager.h"
#include "GameManager.h"
#include "ImguiManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "StateResultUI.h"

/*--------------------------------*/
/*     【リザルトUIステート】     */
/*--------------------------------*/

/*----------------------*/
/*【開始画面UIステート】*/
/*----------------------*/


Vector2 numberLeftUp = Vector2(0.200f, 0.156f); // 数字左上
Vector2 numberDistance = Vector2(0.200f, 0.110f);   // 数字同氏の間隔
Vector2 oneNumberSize = Vector2(0.044f, 0.090f);    // 数字一つの大きさ
Vector2_Int oneNumberGraphSize = Vector2_Int(320, 600);   // 数字一つの画像側の大きさ


DisplaySize displaySize;

// データ取得
DataManager* dataManager;
PLAYER_DATA playerData;
std::vector<ONE_DATA> allData;
LEVEL_DATA *levelData = nullptr;

// 変更前ステータス
STATUS preStatus;

StartResultUIState::StartResultUIState()
{
	mStateNumber = (int)RESULT_UI_STATE::START_RESULT_UI_STATE;
    
    displaySize = ResourceManager::mstDisplaySize;

    // データ取得
    dataManager = Master::mpDataManager;
    playerData = dataManager->GetPlayPlayerData();
    allData = dataManager->GetAllData(true);
    levelData = nullptr;
	
    // 変更前ステータス
	preStatus = playerData.status;

    // DisplaySize displaySize = ResourceManager::mstDisplaySize;

    // // データ取得
    // DataManager* dataManager = Master::mpDataManager;
    // PLAYER_DATA playerData = dataManager->GetPlayPlayerData();
    // std::vector<ONE_DATA> allData = dataManager->GetAllData(true);
    // LEVEL_DATA *levelData = nullptr;
	
    // // 変更前ステータス
	// STATUS preStatus = playerData.status;

    for (int i = 0; i < allData.size(); i++)
    {
        if ((allData[i].typeNumber == (int)DATA_TYPE::LEVEL) && (allData[i].datas.levelData.characterType == playerData.typeNumber))
        {
            levelData = &allData[i].datas.levelData;
        }
    }

    if (levelData == nullptr)
    {
        Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::NO_DATA_FLAG);
        return;
    }

    // ステータス変動
    playerData.LevelUpProcess(*levelData, dataManager->GetAcquisitionExpQuantity());

    // ステータス設定
    dataManager->SetPlayPlayerStatus(playerData.status);
    dataManager->ResetAcquisitionExp();

    // 数字
    {
        DRAW_DATA drawData;

        // Vector2 numberLeftUp = Vector2(0.080f, 0.156f); // 数字左上
        // Vector2 numberDistance = Vector2(0.200f, 0.155f);   // 数字同氏の間隔
        // Vector2 oneNumberSize = Vector2(0.050f, 0.050f);    // 数字一つの大きさ
        // Vector2_Int oneNumberGraphSize = Vector2_Int(320, 600);   // 数字一つの画像側の大きさ

        int numberHeightCount = 0;

        // 描画情報数字共通設定
        {
            drawData.drawFlag = true;
            drawData.drawManagerDrawType = DRAW_MANAGER_DRAW_TYPE::GRAPH;
            drawData.drawGraphData.drawType = DRAW_GRAPH_TYPE::RECT_EXTEND_SIZE;
            drawData.drawGraphData.size = displaySize.LeftUp_Ratio(oneNumberSize);
            drawData.drawGraphData.graphSize = oneNumberGraphSize;
            drawData.drawGraphData.transFlag = TRUE;
        }


        // 数字描画個所取得
        {
            int xMaxSize = 5;
            int yMaxSize = 2;

            for (int y = 0; y < yMaxSize; y++)
            {
                for (int x = 0; x < xMaxSize; x++)
                {
                    mstNumberDrawGraphPos[(y * xMaxSize) + x] = Vector2_Int(oneNumberGraphSize.x * x, oneNumberGraphSize.y * y);
                }
            }
        }
/*
Vector2 TestPos[TEST_NUMBER] =  {Vector2(0.0f, 0.0f), 
                                Vector2(0.685f, 0.190f), Vector2(0.685f, 0.550f), Vector2(0.685f, 0.710f), 
                                
                                Vector2(0.080f, 0.156f), Vector2(0.080f, 0.301f), Vector2(0.080f, 0.406f), 
                                Vector2(0.080f, 0.510f), Vector2(0.080f, 0.620f), Vector2(0.080f, 0.730f)};

Vector2 TestSize[TEST_NUMBER] = {Vector2(1.0f, 1.0f),
                                Vector2(0.225f, 0.250f), Vector2(0.225f, 0.150f), Vector2(0.225f, 0.150f), 
                                
                                Vector2(0.520f, 0.140f), Vector2(0.520f, 0.100f), Vector2(0.520f, 0.100f), 
                                Vector2(0.520f, 0.100f), Vector2(0.520f, 0.100f), Vector2(0.520f, 0.100f)};
*/
        // HP
        {
            mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::PRE_HP] = preStatus.hp;
            drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(numberLeftUp.x,                    numberLeftUp.y + (numberDistance.y * numberHeightCount)));
            drawData.drawGraphData.graphPos = mstNumberDrawGraphPos[mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::PRE_HP] % 10];
            mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::PRE_HP] = drawData;

            mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::HP] = playerData.status.hp;
            drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(numberLeftUp.x + numberDistance.x, numberLeftUp.y + (numberDistance.y * numberHeightCount)));
            drawData.drawGraphData.graphPos = mstNumberDrawGraphPos[mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::HP] % 10];
            mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::HP] = drawData;

            numberHeightCount++;
        }
        
        //MAX HP 
        {
            mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::PRE_MAX_HP] = preStatus.maxHp;
            drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(numberLeftUp.x,                    numberLeftUp.y + (numberDistance.y * numberHeightCount)));
            drawData.drawGraphData.graphPos = mstNumberDrawGraphPos[mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::PRE_MAX_HP] % 10];
            mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::PRE_MAX_HP] = drawData;

            mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::MAX_HP] = playerData.status.maxHp;
            drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(numberLeftUp.x + numberDistance.x, numberLeftUp.y + (numberDistance.y * numberHeightCount)));
            drawData.drawGraphData.graphPos = mstNumberDrawGraphPos[mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::MAX_HP] % 10];
            mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::MAX_HP] = drawData;

            numberHeightCount++;
        }
        
        // LEVEL
        {
            mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::PRE_LEVEL] = preStatus.level;
            drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(numberLeftUp.x,                    numberLeftUp.y + (numberDistance.y * numberHeightCount)));
            drawData.drawGraphData.graphPos = mstNumberDrawGraphPos[mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::PRE_LEVEL] % 10];
            mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::PRE_LEVEL] = drawData;

            mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::LEVEL] = playerData.status.level;
            drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(numberLeftUp.x + numberDistance.x, numberLeftUp.y + (numberDistance.y * numberHeightCount)));
            drawData.drawGraphData.graphPos = mstNumberDrawGraphPos[mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::LEVEL] % 10];
            mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::LEVEL] = drawData;

            numberHeightCount++;
        }
        
        // EXP 
        {
            mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::PRE_EXP] = preStatus.exp;
            drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(numberLeftUp.x,                    numberLeftUp.y + (numberDistance.y * numberHeightCount)));
            drawData.drawGraphData.graphPos = mstNumberDrawGraphPos[mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::PRE_EXP] % 10];
            mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::PRE_EXP] = drawData;

            mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::EXP] = playerData.status.exp;
            drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(numberLeftUp.x + numberDistance.x, numberLeftUp.y + (numberDistance.y * numberHeightCount)));
            drawData.drawGraphData.graphPos = mstNumberDrawGraphPos[mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::EXP] % 10];
            mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::EXP] = drawData;

            numberHeightCount++;
        }
        
        // ATTACK 
        {
            mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::PRE_ATTACK] = preStatus.baseAttckPower;
            drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(numberLeftUp.x,                    numberLeftUp.y + (numberDistance.y * numberHeightCount)));
            drawData.drawGraphData.graphPos = mstNumberDrawGraphPos[mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::PRE_ATTACK] % 10];
            mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::PRE_ATTACK] = drawData;

            mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::ATTACK] = playerData.status.baseAttckPower;
            drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(numberLeftUp.x + numberDistance.x, numberLeftUp.y + (numberDistance.y * numberHeightCount)));
            drawData.drawGraphData.graphPos = mstNumberDrawGraphPos[mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::ATTACK] % 10];
            mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::ATTACK] = drawData;

            numberHeightCount++;
        }
        
        // SPEED 
        {
            mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::PRE_SPEED] = preStatus.baseSpeed;
            drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(numberLeftUp.x,                    numberLeftUp.y + (numberDistance.y * numberHeightCount)));
            drawData.drawGraphData.graphPos = mstNumberDrawGraphPos[mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::PRE_SPEED] % 10];
            mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::PRE_SPEED] = drawData;

            mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::SPEED] = playerData.status.baseSpeed;
            drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(numberLeftUp.x + numberDistance.x, numberLeftUp.y + (numberDistance.y * numberHeightCount)));
            drawData.drawGraphData.graphPos = mstNumberDrawGraphPos[mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::SPEED] % 10];
            mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::SPEED] = drawData;

            numberHeightCount++;
        }

        // 描画設定
        for (int i = 0; i < RESULT_DRAW_NUMBER_TYPE::MAX; i++)
        {
            mstNumberDrawData[i].drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/Numbers.png");
            Master::mpDrawManager->AddDrawData(&mstNumberDrawData[i]);
        }
    }

    // 描画情報
    {
        mstDrawDatas.clear();

        // HP
        {
        }

        for (int i = 0; i < mstDrawDatas.size(); i++)
        {
            Master::mpDrawManager->AddDrawData(&mstDrawDatas[i]);
        }
    }
}

// この状態に入った時の処理
void StartResultUIState::OnEnter(UIBase* ui)
{
    for (int i  = RESULT_DRAW_NUMBER_TYPE::HP - 1; i < RESULT_DRAW_NUMBER_TYPE::HP; i++)
    {
            Master::mpImguiManager->SetIntImgui(IMGUI_INT_DATA::GetImguiData(
                                                                            { &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::PRE_HP].drawGraphData.pos.x, &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::PRE_HP].drawGraphData.pos.y, &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::PRE_HP].drawGraphData.size.x, &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::PRE_HP].drawGraphData.size.y },
                                                                            1.0f,
                                                                            1.0f,
                                                                            1.0f,
                                                                            0,
                                                                            1000,
                                                                            "PRE_HP_",
                                                                            "%d",
                                                                            0,
                                                                            IMGUI_TYPE::SLIDER4
                                                                            )
                                                );
                                                
            Master::mpImguiManager->SetIntImgui(IMGUI_INT_DATA::GetImguiData(
                                                                            { &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::PRE_HP].drawGraphData.graphPos.x, &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::PRE_HP].drawGraphData.graphPos.y, &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::PRE_HP].drawGraphData.graphSize.x, &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::PRE_HP].drawGraphData.graphSize.y },
                                                                            1.0f,
                                                                            1.0f,
                                                                            1.0f,
                                                                            0,
                                                                            1000,
                                                                            "PRE_HP_GRAPH_",
                                                                            "%d",
                                                                            0,
                                                                            IMGUI_TYPE::SLIDER4
                                                                            )
                                                );

            Master::mpImguiManager->SetIntImgui(IMGUI_INT_DATA::GetImguiData(
                                                                            { &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::HP].drawGraphData.pos.x, &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::HP].drawGraphData.pos.y, &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::HP].drawGraphData.size.x, &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::HP].drawGraphData.size.y },
                                                                            1.0f,
                                                                            1.0f,
                                                                            1.0f,
                                                                            0,
                                                                            1000,
                                                                            "HP_",
                                                                            "%d",
                                                                            0,
                                                                            IMGUI_TYPE::SLIDER4
                                                                            )
                                                );
                                                
            Master::mpImguiManager->SetIntImgui(IMGUI_INT_DATA::GetImguiData(
                                                                            { &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::HP].drawGraphData.graphPos.x, &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::HP].drawGraphData.graphPos.y, &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::HP].drawGraphData.graphSize.x, &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::HP].drawGraphData.graphSize.y },
                                                                            1.0f,
                                                                            1.0f,
                                                                            1.0f,
                                                                            0,
                                                                            1000,
                                                                            "HP_GRAPH_",
                                                                            "%d",
                                                                            0,
                                                                            IMGUI_TYPE::SLIDER4
                                                                            )
                                                );
                                            }
                                                
                                                
            Master::mpImguiManager->SetIntImgui(IMGUI_INT_DATA::GetImguiData(
                                                                            { &oneNumberGraphSize.x, &oneNumberGraphSize.y},
                                                                            1.0f,
                                                                            1.0f,
                                                                            1.0f,
                                                                            0,
                                                                            1000,
                                                                            "oneNumberGraphSize_",
                                                                            "%d",
                                                                            0,
                                                                            IMGUI_TYPE::SLIDER2
                                                                            )
                                                );

                                                
    Master::mpImguiManager->SetFloatImgui(IMGUI_FLOAT_DATA::GetImguiData(
        { &numberLeftUp.x, &numberLeftUp.y },
        0.001f,
        0.001f,
        0.001f,
        0.0f,
        1.0f,
        "numberLeftUp_",
        "%f",
        0,
        IMGUI_TYPE::SLIDER2
    )
    );                        
    Master::mpImguiManager->SetFloatImgui(IMGUI_FLOAT_DATA::GetImguiData(
        { &numberDistance.x, &numberDistance.y },
        0.001f,
        0.001f,
        0.001f,
        0.0f,
        1.0f,
        "numberDistance_",
        "%f",
        0,
        IMGUI_TYPE::SLIDER2
    )
    );
    Master::mpImguiManager->SetFloatImgui(IMGUI_FLOAT_DATA::GetImguiData(
        { &oneNumberSize.x, &oneNumberSize.y },
        0.001f,
        0.001f,
        0.001f,
        0.0f,
        1.0f,
        "oneNumberSize_",
        "%f",
        0,
        IMGUI_TYPE::SLIDER2
    )
    );
    //for (int i = 0; i < NUMBERS_ENUM::NUMBERS_ENUM_MAX; i++)
    {
        Master::mpImguiManager->SetIntImgui(IMGUI_INT_DATA::GetImguiData(
            { &mstNumberDrawGraphPos[0].x, &mstNumberDrawGraphPos[0].y },
            1.0f,
            1.0f,
            1.0f,
            0,
            1000,
            "mstNumberDrawGraphPos_",
            "%d",
            0,
            IMGUI_TYPE::SLIDER2
        )
        );
    }
}

// この状態を出る時の処理
void StartResultUIState::OnExit(UIBase* ui)
{
}

// 更新
int StartResultUIState::Update(UIBase* ui)
{
	ui->DefaultDecision();

	return mStateNumber;
}

// 決定
int StartResultUIState::Decision(UIBase* ui)
{
    /*// UNDONE: 元に戻す
    // シーン移動
	Master::mpGameManager->GetSceneManager()->SetNextScene(Master::mpDataManager->GetPlayPlayerData().sceneData[DATA_SCENE::DUNGEON].sceneType);

    // エネミー削除
    Master::mpDataManager->DeleteEnemyData(Master::mpDataManager->GetPlayPlayerData().sceneData[DATA_SCENE::DUNGEON].sceneType);
    */

    // HACK: 仮実装
    // シーン移動
	Master::mpGameManager->GetSceneManager()->SetNextScene(SCENE::GAME_LOOP);


	return mStateNumber;
}

// 描画
void StartResultUIState::Draw(UIBase* ui)
{
    // 数字描画
    DrawNumber();
	// // TODO: 画面全体に描画
    // // TODO: 画像ハンドルに変更
    // DisplaySize displaySize = ResourceManager::mstDisplaySize;
    // Vector2_Int leftUp = displaySize.LeftUp_FloatRatio(0.1f);
    // Vector2_Int rightDown = displaySize.RightDown_FloatRatio(0.1f);
    // DrawBox(leftUp.x, leftUp.y, rightDown.x, rightDown.y, GetColor(255, 255, 255), TRUE);

    // Vector2_Int stringDrawPos = displaySize.LeftUp_Ratio(Vector2(0.5f, 0.11f));
    // DrawString(stringDrawPos.x - 50, stringDrawPos.y, "リザルト", GetColor(0, 0, 0));
}

// 数字描画
void StartResultUIState::DrawNumber()
{
    for (int i = 0; i < RESULT_DRAW_NUMBER_TYPE::MAX; i++)
    {
        DrawNumberAddDraw(mstNumberDrawData[i], mnDrawNumbers[i]);
    }
}

// 二桁以上の数字を渡したら左に追加描画する
void StartResultUIState::DrawNumberAddDraw(DRAW_DATA numberDrawData, int number)
{
    // 2桁以上なら
    while (number >= 10)
    {
        number /= 10;

        int test = number % 10;

        numberDrawData.drawGraphData.graphPos = mstNumberDrawGraphPos[number % 10];
        numberDrawData.drawGraphData.pos.x -= numberDrawData.drawGraphData.size.x;
        Master::mpResourceManager->DrawData_Graph(numberDrawData.drawGraphData);
    }
}