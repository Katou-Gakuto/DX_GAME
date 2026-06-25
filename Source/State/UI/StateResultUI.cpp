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
#include "ResourceGraph.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "StateResultUI.h"

/*--------------------------------*/
/*     【リザルトUIステート】     */
/*--------------------------------*/

/*----------------------*/
/*【開始画面UIステート】*/
/*----------------------*/


StartResultUIState::StartResultUIState()
{
	mStateNumber = (int)RESULT_UI_STATE::START_RESULT_UI_STATE;
    
    // 描画情報初期化
    mstDrawDatas.clear();

    DisplaySize displaySize = ResourceManager::mstDisplaySize;

    // データ取得
    DataManager* dataManager = Master::mpDataManager;
    PLAYER_DATA playerData = dataManager->GetPlayPlayerData();
    std::vector<ONE_DATA> allData = dataManager->GetAllData(true);
    LEVEL_DATA *levelData = nullptr;
	
    // 変更前ステータス
	STATUS preStatus = playerData.status;

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

        Vector2 numberLeftUp = Vector2(0.312f, 0.156f); // 数字左上
        Vector2 numberDistance = Vector2(0.280f, 0.119048);   // 数字同氏の間隔
        Vector2 oneNumberSize = Vector2(0.044f, 0.090f);    // 数字一つの大きさ
        Vector2_Int oneNumberGraphSize = Vector2_Int(320, 600);   // 数字一つの画像側の大きさ

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
            // drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(numberLeftUp.x,                    numberLeftUp.y + (numberDistance.y * numberHeightCount)));
            // drawData.drawGraphData.graphPos = mstNumberDrawGraphPos[mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::PRE_HP] % 10];
            // mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::PRE_HP] = drawData;

            mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::HP] = playerData.status.hp;
            // drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(numberLeftUp.x + numberDistance.x, numberLeftUp.y + (numberDistance.y * numberHeightCount)));
            // drawData.drawGraphData.graphPos = mstNumberDrawGraphPos[mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::HP] % 10];
            // mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::HP] = drawData;

            numberHeightCount++;
        }
        
        //MAX HP 
        {
            mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::PRE_MAX_HP] = preStatus.maxHp;
            // drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(numberLeftUp.x,                    numberLeftUp.y + (numberDistance.y * numberHeightCount)));
            // drawData.drawGraphData.graphPos = mstNumberDrawGraphPos[mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::PRE_MAX_HP] % 10];
            // mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::PRE_MAX_HP] = drawData;

            mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::MAX_HP] = playerData.status.maxHp;
            // drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(numberLeftUp.x + numberDistance.x, numberLeftUp.y + (numberDistance.y * numberHeightCount)));
            // drawData.drawGraphData.graphPos = mstNumberDrawGraphPos[mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::MAX_HP] % 10];
            // mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::MAX_HP] = drawData;

            numberHeightCount++;
        }
        
        // LEVEL
        {
            mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::PRE_LEVEL] = preStatus.level;
            // drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(numberLeftUp.x,                    numberLeftUp.y + (numberDistance.y * numberHeightCount)));
            // drawData.drawGraphData.graphPos = mstNumberDrawGraphPos[mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::PRE_LEVEL] % 10];
            // mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::PRE_LEVEL] = drawData;

            mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::LEVEL] = playerData.status.level;
            // drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(numberLeftUp.x + numberDistance.x, numberLeftUp.y + (numberDistance.y * numberHeightCount)));
            // drawData.drawGraphData.graphPos = mstNumberDrawGraphPos[mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::LEVEL] % 10];
            // mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::LEVEL] = drawData;

            numberHeightCount++;
        }
        
        // EXP 
        {
            mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::PRE_EXP] = preStatus.exp;
            // drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(numberLeftUp.x,                    numberLeftUp.y + (numberDistance.y * numberHeightCount)));
            // drawData.drawGraphData.graphPos = mstNumberDrawGraphPos[mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::PRE_EXP] % 10];
            // mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::PRE_EXP] = drawData;

            mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::EXP] = playerData.status.exp;
            // drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(numberLeftUp.x + numberDistance.x, numberLeftUp.y + (numberDistance.y * numberHeightCount)));
            // drawData.drawGraphData.graphPos = mstNumberDrawGraphPos[mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::EXP] % 10];
            // mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::EXP] = drawData;

            numberHeightCount++;
        }
        
        // ATTACK 
        {
            mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::PRE_ATTACK] = preStatus.baseAttckPower;
            // drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(numberLeftUp.x,                    numberLeftUp.y + (numberDistance.y * numberHeightCount)));
            // drawData.drawGraphData.graphPos = mstNumberDrawGraphPos[mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::PRE_ATTACK] % 10];
            // mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::PRE_ATTACK] = drawData;

            mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::ATTACK] = playerData.status.baseAttckPower;
            // drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(numberLeftUp.x + numberDistance.x, numberLeftUp.y + (numberDistance.y * numberHeightCount)));
            // drawData.drawGraphData.graphPos = mstNumberDrawGraphPos[mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::ATTACK] % 10];
            // mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::ATTACK] = drawData;

            numberHeightCount++;
        }
        
        // SPEED 
        {
            mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::PRE_SPEED] = preStatus.baseSpeed;
            // drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(numberLeftUp.x,                    numberLeftUp.y + (numberDistance.y * numberHeightCount)));
            // drawData.drawGraphData.graphPos = mstNumberDrawGraphPos[mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::PRE_SPEED] % 10];
            // mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::PRE_SPEED] = drawData;

            mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::SPEED] = playerData.status.baseSpeed;
            // drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(numberLeftUp.x + numberDistance.x, numberLeftUp.y + (numberDistance.y * numberHeightCount)));
            // drawData.drawGraphData.graphPos = mstNumberDrawGraphPos[mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::SPEED] % 10];
            // mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::SPEED] = drawData;

            numberHeightCount++;
        }

        // 描画ポジション設定
        for (int i = 0; i < RESULT_DRAW_NUMBER_TYPE::LEVEL; i++)
        {
            drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(numberLeftUp.x,                    numberLeftUp.y + (numberDistance.y * i)));
            drawData.drawGraphData.graphPos = mstNumberDrawGraphPos[mnDrawNumbers[RESULT_DRAW_NUMBER_TYPE::LEVEL + i] % 10];
            mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::LEVEL + i] = drawData;

            drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(numberLeftUp.x + numberDistance.x, numberLeftUp.y + (numberDistance.y * i)));
            drawData.drawGraphData.graphPos = mstNumberDrawGraphPos[mnDrawNumbers[i] % 10];
            mstNumberDrawData[i] = drawData;
        }

        // 描画情報数字共通設定
        {
            drawData.drawFlag = true;
            drawData.drawManagerDrawType = DRAW_MANAGER_DRAW_TYPE::GRAPH;
            drawData.drawGraphData.drawType = DRAW_GRAPH_TYPE::SIZE;
            drawData.drawGraphData.pos.x = displaySize.Left_RatioWidth(numberLeftUp.x) + displaySize.Left_RatioWidth(oneNumberSize.x * 1.5f);
            drawData.drawGraphData.size = displaySize.LeftUp_Ratio(Vector2(0.1f, 0.1f));
            drawData.drawGraphData.transFlag = TRUE;
        }
        
        // 描画設定
        for (int i = 0; i < RESULT_DRAW_NUMBER_TYPE::MAX; i++)
        {
            if (RESULT_DRAW_NUMBER_TYPE::LEVEL > i)
            {
                if (mnDrawNumbers[i] == mnDrawNumbers[i + RESULT_DRAW_NUMBER_TYPE::LEVEL])
                {
                    mstNumberDrawData[i].drawGraphData.handle = -1;
                    continue;
                }
                drawData.drawGraphData.pos.y = mstNumberDrawData[i].drawGraphData.pos.y;
                drawData.drawGraphData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle(ResourceManager::msResourceFile + "2D/ChangeArrow.png");
                mstDrawDatas.push_back(drawData);
            }
            mstNumberDrawData[i].drawGraphData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle(ResourceManager::msResourceFile + "2D/Numbers.png");
            //Master::mpDrawManager->AddDrawData(&mstNumberDrawData[i]);
        }
    }
    
    // 描画情報
    {
        DRAW_DATA drawData;

        // 共通描画情報
        {
            drawData.drawFlag = true;
            drawData.drawManagerDrawType = DRAW_MANAGER_DRAW_TYPE::GRAPH;
            drawData.drawGraphData.transFlag = TRUE;
        }

        // ステータス
        {
            drawData.drawGraphData.drawType = DRAW_GRAPH_TYPE::RECT_EXTEND_SIZE;
            drawData.drawGraphData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle(ResourceManager::msResourceFile + "2D/ResultStatus.png");
            drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(0.0625f, 0.15625f));
            drawData.drawGraphData.size = displaySize.LeftUp_Ratio(Vector2(0.1859375f, 0.7125f));
            drawData.drawGraphData.graphPos = Vector2_Int(340, 975);
            drawData.drawGraphData.graphSize = Vector2_Int(1362, 3578);
            mstDrawDatas.push_back(drawData);
        }

        // 選択肢
        {
            drawData.drawGraphData.drawType = DRAW_GRAPH_TYPE::RECT_EXTEND_SIZE;
            drawData.drawGraphData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle(ResourceManager::msResourceFile + "2D/Result2.png");
            drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(0.68125f, 0.75f));
            drawData.drawGraphData.size = displaySize.LeftUp_Ratio(Vector2(0.22f, 0.075f));
            drawData.drawGraphData.graphPos = Vector2_Int(4640, 4975);
            drawData.drawGraphData.graphSize = Vector2_Int(1765, 380);
            mstDrawDatas.push_back(drawData);
        }

        // キャラ画像
        {
            drawData.drawGraphData.drawType = DRAW_GRAPH_TYPE::SIZE;
            drawData.drawGraphData.transFlag = FALSE;
            drawData.drawGraphData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle(ResourceManager::msResourceFile + "2D/RobotSphere.png");
            drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(0.68125f, 0.15f));
            int graphSize = displaySize.Left_RatioWidth(0.23125f);
            drawData.drawGraphData.size = Vector2_Int(graphSize, graphSize);
            mstDrawDatas.push_back(drawData);
        }

        for (int i = 0; i < mstDrawDatas.size(); i++)
        {
            Master::mpDrawManager->AddDrawData(&mstDrawDatas[i]);
            
            Master::mpImguiManager->SetIntImgui(IMGUI_INT_DATA::GetImguiData(
                                                                            { &mstDrawDatas[i].drawGraphData.pos.x, &mstDrawDatas[i].drawGraphData.pos.y, &mstDrawDatas[i].drawGraphData.size.x, &mstDrawDatas[i].drawGraphData.size.y },
                                                                            1.0f,
                                                                            1.0f,
                                                                            1.0f,
                                                                            0,
                                                                            1000,
                                                                            "DRAW_DATA_POS_",
                                                                            "%d",
                                                                            0,
                                                                            IMGUI_TYPE::DRAG4
                                                                            )
                                                );
            Master::mpImguiManager->SetIntImgui(IMGUI_INT_DATA::GetImguiData(
                                                                            { &mstDrawDatas[i].drawGraphData.graphPos.x, &mstDrawDatas[i].drawGraphData.graphPos.y, &mstDrawDatas[i].drawGraphData.graphSize.x, &mstDrawDatas[i].drawGraphData.graphSize.y },
                                                                            1.0f,
                                                                            1.0f,
                                                                            1.0f,
                                                                            0,
                                                                            1000,
                                                                            "DRAW_DATA_GRAPH_",
                                                                            "%d",
                                                                            0,
                                                                            IMGUI_TYPE::DRAG4
                                                                            )
                                                );
        }
    }
}

// この状態に入った時の処理
void StartResultUIState::OnEnter(UIBase* ui)
{
    //for (int i  = RESULT_DRAW_NUMBER_TYPE::HP - 1; i < RESULT_DRAW_NUMBER_TYPE::HP; i++)
    //{
    //        Master::mpImguiManager->SetIntImgui(IMGUI_INT_DATA::GetImguiData(
    //                                                                        { &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::PRE_HP].drawGraphData.pos.x, &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::PRE_HP].drawGraphData.pos.y, &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::PRE_HP].drawGraphData.size.x, &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::PRE_HP].drawGraphData.size.y },
    //                                                                        1.0f,
    //                                                                        1.0f,
    //                                                                        1.0f,
    //                                                                        0,
    //                                                                        1000,
    //                                                                        "PRE_HP_",
    //                                                                        "%d",
    //                                                                        0,
    //                                                                        IMGUI_TYPE::SLIDER4
    //                                                                        )
    //                                            );
    //                                            
    //        Master::mpImguiManager->SetIntImgui(IMGUI_INT_DATA::GetImguiData(
    //                                                                        { &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::PRE_HP].drawGraphData.graphPos.x, &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::PRE_HP].drawGraphData.graphPos.y, &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::PRE_HP].drawGraphData.graphSize.x, &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::PRE_HP].drawGraphData.graphSize.y },
    //                                                                        1.0f,
    //                                                                        1.0f,
    //                                                                        1.0f,
    //                                                                        0,
    //                                                                        1000,
    //                                                                        "PRE_HP_GRAPH_",
    //                                                                        "%d",
    //                                                                        0,
    //                                                                        IMGUI_TYPE::SLIDER4
    //                                                                        )
    //                                            );

    //        Master::mpImguiManager->SetIntImgui(IMGUI_INT_DATA::GetImguiData(
    //                                                                        { &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::HP].drawGraphData.pos.x, &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::HP].drawGraphData.pos.y, &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::HP].drawGraphData.size.x, &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::HP].drawGraphData.size.y },
    //                                                                        1.0f,
    //                                                                        1.0f,
    //                                                                        1.0f,
    //                                                                        0,
    //                                                                        1000,
    //                                                                        "HP_",
    //                                                                        "%d",
    //                                                                        0,
    //                                                                        IMGUI_TYPE::SLIDER4
    //                                                                        )
    //                                            );
    //                                            
    //        Master::mpImguiManager->SetIntImgui(IMGUI_INT_DATA::GetImguiData(
    //                                                                        { &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::HP].drawGraphData.graphPos.x, &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::HP].drawGraphData.graphPos.y, &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::HP].drawGraphData.graphSize.x, &mstNumberDrawData[RESULT_DRAW_NUMBER_TYPE::HP].drawGraphData.graphSize.y },
    //                                                                        1.0f,
    //                                                                        1.0f,
    //                                                                        1.0f,
    //                                                                        0,
    //                                                                        1000,
    //                                                                        "HP_GRAPH_",
    //                                                                        "%d",
    //                                                                        0,
    //                                                                        IMGUI_TYPE::SLIDER4
    //                                                                        )
    //                                            );
    //                                        }
    //                                            
    //                                            
    //        Master::mpImguiManager->SetIntImgui(IMGUI_INT_DATA::GetImguiData(
    //                                                                        { &oneNumberGraphSize.x, &oneNumberGraphSize.y},
    //                                                                        1.0f,
    //                                                                        1.0f,
    //                                                                        1.0f,
    //                                                                        0,
    //                                                                        1000,
    //                                                                        "oneNumberGraphSize_",
    //                                                                        "%d",
    //                                                                        0,
    //                                                                        IMGUI_TYPE::SLIDER2
    //                                                                        )
    //                                            );

    //                                            
    //Master::mpImguiManager->SetFloatImgui(IMGUI_FLOAT_DATA::GetImguiData(
    //    { &numberLeftUp.x, &numberLeftUp.y },
    //    0.001f,
    //    0.001f,
    //    0.001f,
    //    0.0f,
    //    1.0f,
    //    "numberLeftUp_",
    //    "%f",
    //    0,
    //    IMGUI_TYPE::SLIDER2
    //)
    //);                        
    //Master::mpImguiManager->SetFloatImgui(IMGUI_FLOAT_DATA::GetImguiData(
    //    { &numberDistance.x, &numberDistance.y },
    //    0.001f,
    //    0.001f,
    //    0.001f,
    //    0.0f,
    //    1.0f,
    //    "numberDistance_",
    //    "%f",
    //    0,
    //    IMGUI_TYPE::SLIDER2
    //)
    //);
    //Master::mpImguiManager->SetFloatImgui(IMGUI_FLOAT_DATA::GetImguiData(
    //    { &oneNumberSize.x, &oneNumberSize.y },
    //    0.001f,
    //    0.001f,
    //    0.001f,
    //    0.0f,
    //    1.0f,
    //    "oneNumberSize_",
    //    "%f",
    //    0,
    //    IMGUI_TYPE::SLIDER2
    //)
    //);
    ////for (int i = 0; i < NUMBERS_ENUM::NUMBERS_ENUM_MAX; i++)
    //{
    //    Master::mpImguiManager->SetIntImgui(IMGUI_INT_DATA::GetImguiData(
    //        { &mstNumberDrawGraphPos[0].x, &mstNumberDrawGraphPos[0].y },
    //        1.0f,
    //        1.0f,
    //        1.0f,
    //        0,
    //        1000,
    //        "mstNumberDrawGraphPos_",
    //        "%d",
    //        0,
    //        IMGUI_TYPE::SLIDER2
    //    )
    //    );
    //}
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
        if ((RESULT_DRAW_NUMBER_TYPE::LEVEL > i) && (mnDrawNumbers[i] == mnDrawNumbers[i + RESULT_DRAW_NUMBER_TYPE::LEVEL]))
        {
            continue;
        }
        NumberDataDraw(mstNumberDrawData[i], mnDrawNumbers[i]);
    }
}

// 数字情報を描画する
void StartResultUIState::NumberDataDraw(DRAW_DATA numberDrawData, int number)
{
    // 一桁目描画
    Master::mpDrawManager->DrawData_Graph(numberDrawData.drawGraphData);

    // 2桁以上なら
    while (number >= 10)
    {
        number /= 10;

        int test = number % 10;

        numberDrawData.drawGraphData.graphPos = mstNumberDrawGraphPos[number % 10];
        numberDrawData.drawGraphData.pos.x -= numberDrawData.drawGraphData.size.x;
        Master::mpDrawManager->DrawData_Graph(numberDrawData.drawGraphData);
    }
}