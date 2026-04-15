#include <vector>

#include "DrawData.h"
#include "ResourceData.h"

#include "Master.h"

#include "DataManager.h"
#include "DrawManager.h"
#include "fsrm.h"
#include "KeyState.h"
#include "MapManager.h"
#include "ResourceManager.h"
#include "StateConfigUi.h"
#include "TargetManager.h"
#include "ObjectBases.h"

#include "ImguiManager.h"
bool imguiSetFlag_Config = true;
Vector2 pos_Config = Vector2(0.37f, 0.17f);
float posMove_Config = 0.1f;
//float centerPos_Config = 0.5f;
Vector2 size_Config = Vector2(0.24f, 0.02f);
Vector2 buttonSize_Config = Vector2(0.01f, 0.02f);
DisplaySize graphSize_Config = { Vector2(3221.0f, 218.0f), 0.0f };

/*--------------------------------*/
/*   【コンフィグUIステート】     */
/*--------------------------------*/

/*---------------------------*/
/*【設定変数ポインタ 構造体】*/
/*---------------------------*/
// 設定変数変更
void CONFIG_VARIABLE_POINTER::ChangeVariable(float changeRateAmount)
{
    this->rate += changeRateAmount;
    if (this->rate < 0.0f)
    {
        this->rate = 0.0f;
    }
    else if (this->rate > 1.0f)
    {
        this->rate = 1.0f;
    }

    switch (type)
    {
    case CONFIG_VARIABLE_POINTER_TYPE::INT:
        *this->intPointer = this->intLowestValue + static_cast<int>(this->intRateValue * this->rate);
        break;

    case CONFIG_VARIABLE_POINTER_TYPE::FLOAT:
        *this->floatPointer = this->floatLowestValue + (this->floatRateValue * this->rate);
        break;
    }
}

/*----------*/
/*【コンフィグUI共通処理用】*/
/*----------*/
ConfigUIProcess::ConfigUIProcess(int *statePointer, int defaultStateNumber)
: mnPreSelectNumber(0)  
, mnStatePointer(statePointer)
, mnDefaultStateNumber(defaultStateNumber)
{ 
    mstConfigVariables.clear();
    mstDrawData.clear();
    mstDrawData.resize(CONFIG_SLIDER_TYPE::ALL_CONFIG_SLIDER_MAX);
    if (imguiSetFlag_Config)
    {
        imguiSetFlag_Config = false;
            
        IMGUI_FLOAT_DATA imguiFloatData;
        imguiFloatData.AddVariable(&pos_Config.x);
        imguiFloatData.AddVariable(&pos_Config.y);
        imguiFloatData.AddVariable(&posMove_Config);
        imguiFloatData.SetLabel("CONFIG_POSS_");
        imguiFloatData.SetImguiType(IMGUI_TYPE::DRAG3);
        imguiFloatData.SetMin(0.0f);
        imguiFloatData.SetMax(1.0f);
        imguiFloatData.SetSpeed(0.01f);

        Master::mpImguiManager->SetFloatImgui(imguiFloatData);
        
        imguiFloatData.ReSetVariable();
        imguiFloatData.AddVariable(&size_Config.x);
        imguiFloatData.AddVariable(&size_Config.y);
        imguiFloatData.AddVariable(&buttonSize_Config.x);
        imguiFloatData.AddVariable(&buttonSize_Config.y);
        imguiFloatData.SetLabel("CONFIG_SIZES_");
        imguiFloatData.SetImguiType(IMGUI_TYPE::DRAG4);
        
        Master::mpImguiManager->SetFloatImgui(imguiFloatData);
        
        // imguiFloatData.ReSetVariable();
        // imguiFloatData.AddVariable(&centerPos_Config);
        // imguiFloatData.SetLabel("CONFIG_CENTER_POS_");
        // imguiFloatData.SetImguiType(IMGUI_TYPE::DRAG1);
        //
        // Master::mpImguiManager->SetFloatImgui(imguiFloatData);
    }

    // DisplaySize displaySize = ResourceManager::mstDisplaySize;

    // mstDrawData = DRAW_DATA();
    // mstDrawData.drawFlag = false;
    // mstDrawData.drawManagerDrawType = DRAW_MANAGER_DRAW_TYPE::GRAPH;
    // mstDrawData.drawGraphData.drawType = DRAW_GRAPH_TYPE::SIZE;
    // mstDrawData.drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(0.1f, 0.1f));
    // mstDrawData.drawGraphData.size = displaySize.LeftUp_FloatRatio(0.8f);
    // mstDrawData.drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/TitleSelectBase.png");
    // mstDrawData.drawGraphData.transFlag = TRUE;
    // Master::mpDrawManager->AddDrawData(&mstDrawData);
}

// ステートナンバー取得
int ConfigUIProcess::GetConfigStateNumber(int stateNumber)
{
    return *mnStatePointer + (stateNumber - mnDefaultStateNumber) ;
}

// 値を左右の入力を元に変更する
void ConfigUIProcess::ValueLeftRightInputBasedOnChange(UIBase* ui, int *value, int changeSpeed, int min, int max)
{
    if (changeSpeed < 0)
    {
        changeSpeed = -changeSpeed;
    }

    if (ui->CheckLeft_Frame())
    {
        *value -= changeSpeed;
        if (min > *value)
        {
            *value = min;
        }
    }
    if (ui->CheckRight_Frame())
    {
        *value += changeSpeed;
        if (max < *value)
        {
            *value = max;
        }
    }
}

// 値を左右の入力を元に変更する
void ConfigUIProcess::ValueLeftRightInputBasedOnChange(UIBase* ui, float *value, float changeSpeed, float min, float max)
{
    if (changeSpeed < 0.0000f)
    {
        changeSpeed = -changeSpeed;
    }

    if (ui->CheckLeft_Frame())
    {
        *value -= changeSpeed;
        if (min > *value)
        {
            *value = min;
        }
    }
    if (ui->CheckRight_Frame())
    {
        *value += changeSpeed;
        if (max < *value)
        {
            *value = max;
        }
    }
}

// ステートに入った時の処理
void ConfigUIProcess::ConfigOnEnter(UIBase* ui)
{
    for (int i = 0; i < mstDrawData.size(); i++)
    {
        mstDrawData[i].drawFlag = true;
    }
    for (int i = 0; i < mstConfigVariables.size(); i++)
    {
        mstConfigVariables[i].drawData.drawFlag = true;
    }
    ui->SetSelectNumber(mnPreSelectNumber);
}

// ステートを出た時の処理
void ConfigUIProcess::ConfigOnExit(UIBase* ui)
{
    for (int i = 0; i < mstDrawData.size(); i++)
    {
        mstDrawData[i].drawFlag = false;
    }
    for (int i = 0; i < mstConfigVariables.size(); i++)
    {
        mstConfigVariables[i].drawData.drawFlag = false;
    }
   mnPreSelectNumber = ui->GetSelectNumber();
}

// Sliderワンセット初期設定
void ConfigUIProcess::InitSetSlider(int index)
{
    DisplaySize displaySize = ResourceManager::mstDisplaySize;

    mstDrawData[index + 0].drawFlag = false;
    mstDrawData[index + 0].drawManagerDrawType = DRAW_MANAGER_DRAW_TYPE::GRAPH;
    mstDrawData[index + 0].drawGraphData.drawType = DRAW_GRAPH_TYPE::RECT_EXTEND_SIZE;
    mstDrawData[index + 0].drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(pos_Config.x, pos_Config.y + (posMove_Config * index)) + CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP]);
    mstDrawData[index + 0].drawGraphData.size = displaySize.LeftUp_SeparateRatio(Vector2(pos_Config.x, pos_Config.y + (posMove_Config * index)) + CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP], Vector2(size_Config.x * /*centerPos_Config*/mstConfigVariables[index].rate, size_Config.y), true);
    mstDrawData[index + 0].drawGraphData.graphSize = graphSize_Config.LeftUp_Ratio(Vector2(/*centerPos_Config*/mstConfigVariables[index].rate, 1.0f));
    mstDrawData[index + 0].drawGraphData.transFlag = TRUE;
    mstDrawData[index + 0].drawGraphData.turnFlag.x = 0;
    mstDrawData[index + 0].drawGraphData.turnFlag.y = 0;
    mstDrawData[index + 0].drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/ConfigUISliderLeft.png");

    mstDrawData[index + 1].drawFlag = false;
    mstDrawData[index + 1].drawManagerDrawType = DRAW_MANAGER_DRAW_TYPE::GRAPH;
    mstDrawData[index + 1].drawGraphData.drawType = DRAW_GRAPH_TYPE::RECT_EXTEND_SIZE;
    mstDrawData[index + 1].drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(pos_Config.x + (size_Config.x * /*centerPos_Config*/mstConfigVariables[index].rate), pos_Config.y + (posMove_Config * index)) + CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP]);
    mstDrawData[index + 1].drawGraphData.size = displaySize.LeftUp_SeparateRatio(Vector2(pos_Config.x + (size_Config.x * /*centerPos_Config*/mstConfigVariables[index].rate), pos_Config.y + (posMove_Config * index)) + CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP], Vector2(size_Config.x - (size_Config.x * /*centerPos_Config*/mstConfigVariables[index].rate), size_Config.y), true);
    mstDrawData[index + 1].drawGraphData.graphPos = graphSize_Config.LeftUp_Ratio(Vector2(/*centerPos_Config*/mstConfigVariables[index].rate, 0.0f));
    mstDrawData[index + 1].drawGraphData.graphSize = graphSize_Config.LeftUp_SeparateRatio(Vector2(/*centerPos_Config*/mstConfigVariables[index].rate, 0.0f), Vector2(1.0f - /*centerPos_Config*/mstConfigVariables[index].rate, 1.0f));
    mstDrawData[index + 1].drawGraphData.transFlag = TRUE;
    mstDrawData[index + 1].drawGraphData.turnFlag.x = 0;
    mstDrawData[index + 1].drawGraphData.turnFlag.y = 0;
    mstDrawData[index + 1].drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/ConfigUISliderRight.png");

    
    mstDrawData[index + 2].drawFlag = false;
    mstDrawData[index + 2].drawManagerDrawType = DRAW_MANAGER_DRAW_TYPE::GRAPH;
    mstDrawData[index + 2].drawGraphData.drawType = DRAW_GRAPH_TYPE::SIZE;
    mstDrawData[index + 2].drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(pos_Config.x + (size_Config.x * /*centerPos_Config*/mstConfigVariables[index].rate) - (buttonSize_Config.x * 0.5f), pos_Config.y + (posMove_Config * index)) + CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP]);
    mstDrawData[index + 2].drawGraphData.size = displaySize.LeftUp_SeparateRatio(Vector2(pos_Config.x + (size_Config.x * /*centerPos_Config*/mstConfigVariables[index].rate), pos_Config.y + (posMove_Config * index)) + CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP], buttonSize_Config, true);
    mstDrawData[index + 2].drawGraphData.transFlag = TRUE;
    mstDrawData[index + 2].drawGraphData.turnFlag.x = 0;
    mstDrawData[index + 2].drawGraphData.turnFlag.y = 0;
    mstDrawData[index + 2].drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/ConfigUISliderButton.png");
}

// コンフィグ描画をセッティングする
void ConfigUIProcess::ConfigDrawSetting(UIBase* ui)
{
    DisplaySize displaySize = ResourceManager::mstDisplaySize;
    int sliderNumber = 0;

    for (int i = 0; i < mstConfigVariables.size(); i++)
    {
        mstDrawData[sliderNumber].drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(pos_Config.x, pos_Config.y + (posMove_Config * i)) + CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP]);
        mstDrawData[sliderNumber].drawGraphData.size = displaySize.LeftUp_SeparateRatio(Vector2(pos_Config.x, pos_Config.y + (posMove_Config * i)) + CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP], Vector2(size_Config.x * /*centerPos_Config*/mstConfigVariables[i].rate, size_Config.y), true);
        mstDrawData[sliderNumber].drawGraphData.graphSize = graphSize_Config.LeftUp_Ratio(Vector2(/*centerPos_Config*/mstConfigVariables[i].rate, 1.0f));
        sliderNumber++;

        mstDrawData[sliderNumber].drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(pos_Config.x + (size_Config.x * /*centerPos_Config*/mstConfigVariables[i].rate), pos_Config.y + (posMove_Config * i)) + CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP]);
        mstDrawData[sliderNumber].drawGraphData.size = displaySize.LeftUp_SeparateRatio(Vector2(pos_Config.x + (size_Config.x * /*centerPos_Config*/mstConfigVariables[i].rate), pos_Config.y + (posMove_Config * i)) + CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP], Vector2(size_Config.x - (size_Config.x * /*centerPos_Config*/mstConfigVariables[i].rate), size_Config.y), true);
        mstDrawData[sliderNumber].drawGraphData.graphPos = graphSize_Config.LeftUp_Ratio(Vector2(/*centerPos_Config*/mstConfigVariables[i].rate, 0.0f));
        mstDrawData[sliderNumber].drawGraphData.graphSize = graphSize_Config.LeftUp_SeparateRatio(Vector2(/*centerPos_Config*/mstConfigVariables[i].rate, 0.0f), Vector2(1.0f - /*centerPos_Config*/mstConfigVariables[i].rate, 1.0f));
        sliderNumber++;

        mstDrawData[sliderNumber].drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(pos_Config.x + (size_Config.x * /*centerPos_Config*/mstConfigVariables[i].rate) - (buttonSize_Config.x * 0.5f), pos_Config.y + (posMove_Config * i)) + CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP]);
        mstDrawData[sliderNumber].drawGraphData.size = displaySize.LeftUp_SeparateRatio(Vector2(pos_Config.x + (size_Config.x * /*centerPos_Config*/mstConfigVariables[i].rate), pos_Config.y + (posMove_Config * i)) + CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP], buttonSize_Config, true);
        sliderNumber++;
    }
}

// コンフィグ別スライダー設定
void ConfigUIProcess::SetConfigSlider(CONFIG_UI_STATE configType)
{
    CONFIG_VARIABLE_POINTER setConfigVariable;
    DRAW_DATA drawData;
    mstConfigVariables.clear();
    DisplaySize displaySize = ResourceManager::mstDisplaySize;
    
    // 描画情報デフォルト設定
    {
        drawData.drawFlag = false;
        drawData.drawManagerDrawType = DRAW_MANAGER_DRAW_TYPE::GRAPH;
        drawData.drawGraphData.drawType = DRAW_GRAPH_TYPE::SIZE;
        drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP]);
        drawData.drawGraphData.size = displaySize.LeftUp_SeparateRatio(CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP], CONFIG_POSS[CONFIG_POS_TYPE::RIGHT_DOWN]);
        drawData.drawGraphData.transFlag = TRUE;
    }


    switch (configType)
    {
    // 戻る
    case CONFIG_UI_STATE::SELECT_CONFIG_STATE:
        {
        }
        break;
        
    // ミニマップ
    case CONFIG_UI_STATE::MINIMAP_CONFIG_STATE:
        {
            //drawData.drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/ConfigUIMinMap.png");
            drawData.drawGraphData.handle = -1;
            setConfigVariable.drawData = drawData;
            setConfigVariable.SetFloat(Master::mpDataManager->GetMiniMapSensedRangePointer(), 0.0f, 0.0f);
            mstConfigVariables.push_back(setConfigVariable);

            drawData.drawGraphData.handle = -1;
            setConfigVariable.drawData = drawData;
            setConfigVariable.SetFloat(Master::mpDataManager->GetMiniMapScreenDrawSizePointer(), 0.0f, 0.0f);
            mstConfigVariables.push_back(setConfigVariable);
        }
        break;
        
    // サウンド
    case CONFIG_UI_STATE::SOUND_CONFIG_STATE:
        {
            //drawData.drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/ConfigUISound.png");
            drawData.drawGraphData.handle = -1;
            setConfigVariable.drawData = drawData;
            setConfigVariable.SetInt(Master::mpDataManager->GetSeVolumePointer(), 0, 0);
            mstConfigVariables.push_back(setConfigVariable);

            drawData.drawGraphData.handle = -1;
            setConfigVariable.drawData = drawData;
            setConfigVariable.SetInt(Master::mpDataManager->GetBgmVolumePointer(), 0, 0);
            mstConfigVariables.push_back(setConfigVariable);
        }
        break;
        
    // カメラ
    case CONFIG_UI_STATE::CAMERA_CONFIG_STATE:
        {
            //drawData.drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/ConfigUICamera.png");
            drawData.drawGraphData.handle = -1;
            setConfigVariable.drawData = drawData;
            setConfigVariable.SetInt(&Master::mpDataManager->GetScreenSizePointer()->x, 0, 0);
            mstConfigVariables.push_back(setConfigVariable);

            drawData.drawGraphData.handle = -1;
            setConfigVariable.drawData = drawData;
            setConfigVariable.SetInt(&Master::mpDataManager->GetScreenSizePointer()->y, 0, 0);
            mstConfigVariables.push_back(setConfigVariable);
        }
        break;
    }
}

/*----------------------*/
/*【コンフィグ選択ステート】*/
/*----------------------*/
ConfigSelectState::ConfigSelectState()
: ConfigUIProcess(&mStateNumber, CONFIG_UI_STATE::SELECT_CONFIG_STATE)
{
    mStateNumber = CONFIG_UI_STATE::SELECT_CONFIG_STATE;

    DisplaySize displaySize = ResourceManager::mstDisplaySize;

    mstDrawData.reserve(CONFIG_SELECT_DRAW_DATA_TYPE::MAX - CONFIG_SELECT_DRAW_DATA_TYPE::SLIDER_MAX);
    // // 固定表示物
    // {
    //     mstDrawData.push_back(DRAW_DATA());
    //     mstDrawData[0].drawFlag = false;
    //     mstDrawData[0].drawManagerDrawType = DRAW_MANAGER_DRAW_TYPE::GRAPH;
    //     mstDrawData[0].drawGraphData.drawType = DRAW_GRAPH_TYPE::SIZE;
    //     mstDrawData[0].drawGraphData.pos = displaySize.LeftUp_Ratio(CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP]);
    //     mstDrawData[0].drawGraphData.size = displaySize.LeftUp_SeparateRatio(CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP], CONFIG_POSS[CONFIG_POS_TYPE::RIGHT_DOWN]);
    //     mstDrawData[0].drawGraphData.transFlag = TRUE;
    //     for (int i = 0; i < (CONFIG_UI_STATE::CONFIG_UI_STATE_MAX - 1); i++)
    //     {
    //         mstDrawData.push_back(mstDrawData[0]);
    //     }
    //     mstDrawData[0].drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/ConfigUIReturn.png");
    //     mstDrawData[1].drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/ConfigUIMinMap.png");
    //     mstDrawData[2].drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/ConfigUISound.png");
    //     mstDrawData[3].drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/ConfigUICamera.png");
    // }

    {
        CONFIG_VARIABLE_POINTER setConfigVariable;
        DRAW_DATA drawData;

        // 描画情報デフォルト設定
        {
            drawData.drawFlag = false;
            drawData.drawManagerDrawType = DRAW_MANAGER_DRAW_TYPE::GRAPH;
            drawData.drawGraphData.drawType = DRAW_GRAPH_TYPE::SIZE;
            drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP]);
            drawData.drawGraphData.size = displaySize.LeftUp_SeparateRatio(CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP], CONFIG_POSS[CONFIG_POS_TYPE::RIGHT_DOWN]);
            drawData.drawGraphData.transFlag = TRUE;
        }

        for (int i = 0; i < (int)CONFIG_UI_STATE::CONFIG_UI_STATE_MAX; i++)
        {
            SetConfigSlider((CONFIG_UI_STATE)i);
            mstAllConfigVariables.push_back(mstConfigVariables);
        }

        //　描画自動化
        for (int i = 0; i < mstAllConfigVariables.size(); i++)
        {
            for (int j = 0; j < mstAllConfigVariables[i].size(); j++)
            {
                Master::mpDrawManager->AddDrawData(&mstAllConfigVariables[i][j].drawData);
            }
        }

        mstConfigVariables = mstAllConfigVariables[0];
        /*
        // 戻る
        {
            //drawData.drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/ConfigUIReturn.png");
            drawData.drawGraphData.handle = -1;
            setConfigVariable.drawData = drawData;
            setConfigVariable.SetFloat(Master::mpDataManager->GetMiniMapSensedRangePointer(), 0.0f, 0.0f);
            //mstConfigVariables.push_back(setConfigVariable);

            mstAllConfigVariables.push_back(mstConfigVariables);
            mstConfigVariables.clear();
        }
        
        // ミニマップ
        {
            //drawData.drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/ConfigUIMinMap.png");
            drawData.drawGraphData.handle = -1;
            setConfigVariable.drawData = drawData;
            setConfigVariable.SetFloat(Master::mpDataManager->GetMiniMapSensedRangePointer(), 0.0f, 0.0f);
            mstConfigVariables.push_back(setConfigVariable);

            drawData.drawGraphData.handle = -1;
            setConfigVariable.drawData = drawData;
            setConfigVariable.SetFloat(Master::mpDataManager->GetMiniMapScreenDrawSizePointer(), 0.0f, 0.0f);
            mstConfigVariables.push_back(setConfigVariable);

            mstAllConfigVariables.push_back(mstConfigVariables);
            mstConfigVariables.clear();
        }
        
        // サウンド
        {
            //drawData.drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/ConfigUISound.png");
            drawData.drawGraphData.handle = -1;
            setConfigVariable.drawData = drawData;
            setConfigVariable.SetInt(Master::mpDataManager->GetSeVolumePointer(), 0, 0);
            mstConfigVariables.push_back(setConfigVariable);

            drawData.drawGraphData.handle = -1;
            setConfigVariable.drawData = drawData;
            setConfigVariable.SetInt(Master::mpDataManager->GetBgmVolumePointer(), 0, 0);
            mstConfigVariables.push_back(setConfigVariable);

            mstAllConfigVariables.push_back(mstConfigVariables);
            mstConfigVariables.clear();
        }
        
        // カメラ
        {
            //drawData.drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/ConfigUICamera.png");
            drawData.drawGraphData.handle = -1;
            setConfigVariable.drawData = drawData;
            setConfigVariable.SetInt(&Master::mpDataManager->GetScreenSizePointer()->x, 0, 0);
            mstConfigVariables.push_back(setConfigVariable);

            drawData.drawGraphData.handle = -1;
            setConfigVariable.drawData = drawData;
            setConfigVariable.SetInt(&Master::mpDataManager->GetScreenSizePointer()->y, 0, 0);
            mstConfigVariables.push_back(setConfigVariable);

            mstAllConfigVariables.push_back(mstConfigVariables);
            mstConfigVariables.clear();
        }

        //　描画自動化
        for (int i = 0; i < mstAllConfigVariables.size(); i++)
        {
            for (int j = 0; j < mstAllConfigVariables[i].size(); j++)
            {
                Master::mpDrawManager->AddDrawData(&mstAllConfigVariables[i][j].drawData);
            }
        }

        mstConfigVariables = mstAllConfigVariables[0];
        //mstAllConfigVariables[mn]*/
    }

    // スライダー 
    for (int i = 0; i < SLIDER_CHUNK_NUMBER; i++)
    {
        InitSetSlider(i);
        // mstDrawData[i + 0].drawFlag = false;
        // mstDrawData[i + 0].drawManagerDrawType = DRAW_MANAGER_DRAW_TYPE::GRAPH;
        // mstDrawData[i + 0].drawGraphData.drawType = DRAW_GRAPH_TYPE::RECT_EXTEND_SIZE;
        // mstDrawData[i + 0].drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(pos_Config.x, pos_Config.y + (posMove_Config * i)) + CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP]);
        // mstDrawData[i + 0].drawGraphData.size = displaySize.LeftUp_SeparateRatio(Vector2(pos_Config.x, pos_Config.y + (posMove_Config * i)) + CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP], Vector2(size_Config.x * /*centerPos_Config*/0.5f, size_Config.y), true);
        // mstDrawData[i + 0].drawGraphData.graphSize = graphSize_Config.LeftUp_Ratio(Vector2(/*centerPos_Config*/0.5f, 1.0f));
        // mstDrawData[i + 0].drawGraphData.transFlag = TRUE;
        // mstDrawData[i + 0].drawGraphData.turnFlag.x = 0;
        // mstDrawData[i + 0].drawGraphData.turnFlag.y = 0;
        // mstDrawData[i + 0].drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/ConfigUISliderLeft.png");

        // mstDrawData[i + 1].drawFlag = false;
        // mstDrawData[i + 1].drawManagerDrawType = DRAW_MANAGER_DRAW_TYPE::GRAPH;
        // mstDrawData[i + 1].drawGraphData.drawType = DRAW_GRAPH_TYPE::RECT_EXTEND_SIZE;
        // mstDrawData[i + 1].drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(pos_Config.x + (size_Config.x * /*centerPos_Config*/0.5f), pos_Config.y + (posMove_Config * i)) + CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP]);
        // mstDrawData[i + 1].drawGraphData.size = displaySize.LeftUp_SeparateRatio(Vector2(pos_Config.x + (size_Config.x * /*centerPos_Config*/0.5f), pos_Config.y + (posMove_Config * i)) + CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP], Vector2(size_Config.x - (size_Config.x * /*centerPos_Config*/0.5f), size_Config.y), true);
        // mstDrawData[i + 1].drawGraphData.graphPos = graphSize_Config.LeftUp_Ratio(Vector2(/*centerPos_Config*/0.5f, 0.0f));
        // mstDrawData[i + 1].drawGraphData.graphSize = graphSize_Config.LeftUp_FloatRatio(1.0f);
        // mstDrawData[i + 1].drawGraphData.transFlag = TRUE;
        // mstDrawData[i + 1].drawGraphData.turnFlag.x = 0;
        // mstDrawData[i + 1].drawGraphData.turnFlag.y = 0;
        // mstDrawData[i + 1].drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/ConfigUISliderRight.png");

        
        // mstDrawData[i + 2].drawFlag = false;
        // mstDrawData[i + 2].drawManagerDrawType = DRAW_MANAGER_DRAW_TYPE::GRAPH;
        // mstDrawData[i + 2].drawGraphData.drawType = DRAW_GRAPH_TYPE::SIZE;
        // mstDrawData[i + 2].drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(pos_Config.x + (size_Config.x * /*centerPos_Config*/0.5f), pos_Config.y + (posMove_Config * i)) + CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP]);
        // mstDrawData[i + 2].drawGraphData.size = displaySize.LeftUp_SeparateRatio(Vector2(pos_Config.x + (size_Config.x * /**/0.5f), pos_Config.y + (posMove_Config * i)) + CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP], buttonSize_Config, true);
        // mstDrawData[i + 2].drawGraphData.transFlag = TRUE;
        // mstDrawData[i + 2].drawGraphData.turnFlag.x = 0;
        // mstDrawData[i + 2].drawGraphData.turnFlag.y = 0;
        // mstDrawData[i + 2].drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/ConfigUISliderButton.png");
    }

    for (int i = 0; i < mstDrawData.size(); i++)
    {
        Master::mpDrawManager->AddDrawData(&mstDrawData[i]);
    }

    // 背景作成
    {
        DRAW_DATA drawData;

        // 描画情報デフォルト設定
        {
            drawData.drawFlag = false;
            drawData.drawManagerDrawType = DRAW_MANAGER_DRAW_TYPE::GRAPH;
            drawData.drawGraphData.drawType = DRAW_GRAPH_TYPE::SIZE;
            drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP]);
            drawData.drawGraphData.size = displaySize.LeftUp_SeparateRatio(CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP], CONFIG_POSS[CONFIG_POS_TYPE::RIGHT_DOWN]);
            drawData.drawGraphData.transFlag = TRUE;
        }

        // 戻る
        {
            drawData.drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/ConfigUIReturn.png");
            mstDrawData.push_back(drawData);
            Master::mpDrawManager->AddDrawData(&mstDrawData[mstDrawData.size() - 1], 0);
        }

        // ミニマップ
        {
            drawData.drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/ConfigUIMinMap.png");
            mstDrawData.push_back(drawData);
            Master::mpDrawManager->AddDrawData(&mstDrawData[mstDrawData.size() - 1], 0);
        }

        // サウンド
        {
            drawData.drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/ConfigUISound.png");
            mstDrawData.push_back(drawData);
            Master::mpDrawManager->AddDrawData(&mstDrawData[mstDrawData.size() - 1], 0);
        }

        // カメラ
        {
            drawData.drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/ConfigUICamera.png");
            mstDrawData.push_back(drawData);
            Master::mpDrawManager->AddDrawData(&mstDrawData[mstDrawData.size() - 1], 0);
        }
    }
}

void ConfigSelectState::OnEnter(UIBase* ui)
{
    ConfigOnEnter(ui);

    ui->SetSelectMaxNumber(CONFIG_UI_STATE::CONFIG_UI_STATE_MAX);
    ui->SetSelectNumber(mnPreSelectNumber);
    ui->SetSelectBoundaryValue(1);
 
    int preStateNumber = ui->GetFsm()->GetCurrentState();
    if (preStateNumber < mStateNumber)
    {
        mnPreConfigExceptStateNumber = preStateNumber;
        ui->SetSelectNumber(0);
    }

    AllConfigDrawSetting(ui, true);

    for (int i = 0; i < CONFIG_UI_STATE::CONFIG_UI_STATE_MAX; i++)
    {
        if (i == ui->GetSelectNumber())
        {
            for (int j = 0; j < mstAllConfigVariables[i].size(); j++)
            {
                mstAllConfigVariables[i][j].drawData.drawFlag = true;
            }
        }
        else
        {
            for (int j = 0; j < mstAllConfigVariables[i].size(); j++)
            {
                mstAllConfigVariables[i][j].drawData.drawFlag = false;
            }
        }
    }
}

void ConfigSelectState::OnExit(UIBase* ui)
{
    for (int i = 0; i < mstAllConfigVariables.size(); i++)
    {
        for (int j = 0; j < mstAllConfigVariables[i].size(); j++)
        {
            mstAllConfigVariables[i][j].drawData.drawFlag = false;
        }
    }

    ConfigOnExit(ui);
}

int ConfigSelectState::Update(UIBase* ui)
{
    ui->LeftRightSelectProcess();

    ConfigDrawSetting(ui);
    AllConfigDrawSetting(ui);

    ui->DefaultDecision();
    ui->DefaultCloce();
    if (ui->CheckDown_Frame())
    {
        ui->Decision();
    }
    // DisplaySize displaySize = ResourceManager::mstDisplaySize;
    // int j = CONFIG_DRAW_DATA_TYPE::SLIDER_1_LEFT;
    // //int j = CONFIG_DRAW_DATA_TYPE::MAX;
    // for (int i = 0; j < CONFIG_DRAW_DATA_TYPE::MAX; i++)
    // {
    //     mstDrawData[j].drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(pos_Config.x, pos_Config.y + (posMove_Config * i)) + CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP]);
    //     mstDrawData[j].drawGraphData.size = displaySize.LeftUp_SeparateRatio(Vector2(pos_Config.x, pos_Config.y + (posMove_Config * i)) + CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP], Vector2(size_Config.x * /*centerPos_Config*/mstConfigVariables[i].rate, size_Config.y), true);
    //     mstDrawData[j].drawGraphData.graphSize = graphSize_Config.LeftUp_Ratio(Vector2(/*centerPos_Config*/mstConfigVariables[i].rate, 1.0f));
    //     j++;

    //     mstDrawData[j].drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(pos_Config.x + (size_Config.x * /*centerPos_Config*/mstConfigVariables[i].rate), pos_Config.y + (posMove_Config * i)) + CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP]);
    //     mstDrawData[j].drawGraphData.size = displaySize.LeftUp_SeparateRatio(Vector2(pos_Config.x + (size_Config.x * /*centerPos_Config*/mstConfigVariables[i].rate), pos_Config.y + (posMove_Config * i)) + CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP], Vector2(size_Config.x - (size_Config.x * /*centerPos_Config*/mstConfigVariables[i].rate), size_Config.y), true);
    //     mstDrawData[j].drawGraphData.graphPos = graphSize_Config.LeftUp_Ratio(Vector2(/*centerPos_Config*/mstConfigVariables[i].rate, 0.0f));
    //     mstDrawData[j].drawGraphData.graphSize = graphSize_Config.LeftUp_SeparateRatio(Vector2(/*centerPos_Config*/mstConfigVariables[i].rate, 0.0f), Vector2(1.0f - /*centerPos_Config*/mstConfigVariables[i].rate, 1.0f));
    //     j++;

    //     mstDrawData[j].drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(pos_Config.x + (size_Config.x * /*centerPos_Config*/mstConfigVariables[i].rate) - (buttonSize_Config.x * 0.5f), pos_Config.y + (posMove_Config * i)) + CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP]);
    //     mstDrawData[j].drawGraphData.size = displaySize.LeftUp_SeparateRatio(Vector2(pos_Config.x + (size_Config.x * /*centerPos_Config*/mstConfigVariables[i].rate), pos_Config.y + (posMove_Config * i)) + CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP], buttonSize_Config, true);
    //     j++;
    // }

    return mStateNumber;
}

int ConfigSelectState::Decision(UIBase* ui)
{
    switch (ui->GetSelectNumber())
    {
    case CONFIG_UI_STATE::SELECT_CONFIG_STATE:
        return mnPreConfigExceptStateNumber;
    }
    return GetConfigStateNumber(ui->GetSelectNumber());
}

void ConfigSelectState::Draw(UIBase* ui)
{
    clsDx();
    printfDx("選択\n");
    printfDx("%d", ui->GetSelectNumber());
}

int ConfigSelectState::Cloce(UIBase* ui)
{
    return mnPreConfigExceptStateNumber;
}

// 全コンフィグ描画設定
void ConfigSelectState::AllConfigDrawSetting(UIBase* ui, bool setFlag)
{
    if ((ui->GetPreSelectnumber() != ui->GetSelectNumber()) || setFlag)
    {
        mstConfigVariables = mstAllConfigVariables[ui->GetSelectNumber()];
    }
    else
    {
        return;
    }

    int configSelectStartIndex = CONFIG_SELECT_DRAW_DATA_TYPE::SLIDER_1_LEFT;
    int configSelectDrawDataNumber = CONFIG_SLIDER_TYPE::CONFIG_SLIDER_TYPE_MAX;
    // 描画情報全削除
    for (int i = configSelectStartIndex; i < CONFIG_SELECT_DRAW_DATA_TYPE::MAX; i++)
    {
        mstDrawData[i].drawFlag = false;
    }

    // 選択している設定情報のみ見れるようにする
    for (int i = 0; i < mstAllConfigVariables.size(); i++)
    {
        for (int j = 0; j < mstAllConfigVariables[i].size(); j++)
        {
            mstAllConfigVariables[i][j].drawData.drawFlag = false;
        }

        if (i == ui->GetSelectNumber())
        {
            for (int j = 0; j < mstAllConfigVariables[i].size(); j++)
            {
                mstAllConfigVariables[i][j].drawData.drawFlag = true;
                mstDrawData[configSelectStartIndex + (configSelectDrawDataNumber * j) + 0].drawFlag = true;
                mstDrawData[configSelectStartIndex + (configSelectDrawDataNumber * j) + 1].drawFlag = true;
                mstDrawData[configSelectStartIndex + (configSelectDrawDataNumber * j) + 2].drawFlag = true;
            }
        }
        else
        {
            for (int j = 0; j < mstAllConfigVariables[i].size(); j++)
            {
                mstAllConfigVariables[i][j].drawData.drawFlag = false;
            }
        }
    }

    // 背景
    for (int i = CONFIG_SELECT_DRAW_DATA_TYPE::RETURN; i < CONFIG_SELECT_DRAW_DATA_TYPE::TYPE_MAX; i++)
    {
        if ((i - CONFIG_SELECT_DRAW_DATA_TYPE::RETURN) == ui->GetSelectNumber())
        {
            mstDrawData[i].drawFlag = true;
        }
        else
        {
            mstDrawData[i].drawFlag = false;
        }
    }
}

/*----------------------*/
/*【ミニマップ設定ステート】*/
/*----------------------*/
MinimapConfigState::MinimapConfigState()
: ConfigUIProcess(&mStateNumber, CONFIG_UI_STATE::MINIMAP_CONFIG_STATE)
{
    mStateNumber = CONFIG_UI_STATE::MINIMAP_CONFIG_STATE;
    SetConfigSlider(CONFIG_UI_STATE::MINIMAP_CONFIG_STATE);
    
    DisplaySize displaySize = ResourceManager::mstDisplaySize;
    
    // スライダー 
    for (int i = 0; i < SLIDER_CHUNK_NUMBER; i++)
    {
        InitSetSlider(i);
    }

    for (int i = 0; i < mstDrawData.size(); i++)
    {
        Master::mpDrawManager->AddDrawData(&mstDrawData[i]);
    }

    // 背景作成
    {
        DRAW_DATA drawData;

        // 描画情報デフォルト設定
        {
            drawData.drawFlag = false;
            drawData.drawManagerDrawType = DRAW_MANAGER_DRAW_TYPE::GRAPH;
            drawData.drawGraphData.drawType = DRAW_GRAPH_TYPE::SIZE;
            drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP]);
            drawData.drawGraphData.size = displaySize.LeftUp_SeparateRatio(CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP], CONFIG_POSS[CONFIG_POS_TYPE::RIGHT_DOWN]);
            drawData.drawGraphData.transFlag = TRUE;
        }

        // ミニマップ
        {
            drawData.drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/ConfigUIMinMap.png");
            mstDrawData.push_back(drawData);
            Master::mpDrawManager->AddDrawData(&mstDrawData[mstDrawData.size() - 1], 0);
        }
    }
}

void MinimapConfigState::OnEnter(UIBase* ui)
{
    ConfigOnEnter(ui);

    ui->SetSelectNumberChangeType(SELECT_NUMBER_FLAG_ENUM::CHANGE_BOUNDARY_STOP);
    ui->SetSelectMaxNumber(MIN_MAP_CONFIG_TYPE::MAX);
    ui->SetSelectNumber(mnPreSelectNumber);
}

void MinimapConfigState::OnExit(UIBase* ui)
{
    ConfigOnExit(ui);
}

int MinimapConfigState::Update(UIBase* ui)
{
    ConfigDrawSetting(ui);

    ui->DefaultSelectProcess();
    ui->DefaultCloce();

    return mStateNumber;
}

int MinimapConfigState::Decision(UIBase* ui)
{
    return mStateNumber;
}

void MinimapConfigState::Draw(UIBase* ui)
{
    clsDx();
    printfDx("ミニマップ");
}

int MinimapConfigState::Cloce(UIBase* ui)
{
    return GetConfigStateNumber(CONFIG_UI_STATE::SELECT_CONFIG_STATE);
}

/*----------------------*/
/*【サウンド設定ステート】*/
/*----------------------*/
SoundConfigState::SoundConfigState()
: ConfigUIProcess(&mStateNumber, CONFIG_UI_STATE::SOUND_CONFIG_STATE)
{
    mStateNumber = (int)CONFIG_UI_STATE::SOUND_CONFIG_STATE;
    SetConfigSlider(CONFIG_UI_STATE::SOUND_CONFIG_STATE);

    
    DisplaySize displaySize = ResourceManager::mstDisplaySize;
    
    // スライダー 
    for (int i = 0; i < SLIDER_CHUNK_NUMBER; i++)
    {
        InitSetSlider(i);
    }

    for (int i = 0; i < mstDrawData.size(); i++)
    {
        Master::mpDrawManager->AddDrawData(&mstDrawData[i]);
    }

    // 背景作成
    {
        DRAW_DATA drawData;

        // 描画情報デフォルト設定
        {
            drawData.drawFlag = false;
            drawData.drawManagerDrawType = DRAW_MANAGER_DRAW_TYPE::GRAPH;
            drawData.drawGraphData.drawType = DRAW_GRAPH_TYPE::SIZE;
            drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP]);
            drawData.drawGraphData.size = displaySize.LeftUp_SeparateRatio(CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP], CONFIG_POSS[CONFIG_POS_TYPE::RIGHT_DOWN]);
            drawData.drawGraphData.transFlag = TRUE;
        }

        // サウンド
        {
            drawData.drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/ConfigUISound.png");
            mstDrawData.push_back(drawData);
            Master::mpDrawManager->AddDrawData(&mstDrawData[mstDrawData.size() - 1], 0);
        }
    }
}

void SoundConfigState::OnEnter(UIBase* ui)
{
    ConfigOnEnter(ui);

    ui->SetSelectNumberChangeType(SELECT_NUMBER_FLAG_ENUM::CHANGE_BOUNDARY_STOP);
    ui->SetSelectMaxNumber(SOUND_CONFIG_TYPE::MAX);
    ui->SetSelectNumber(mnPreSelectNumber);
}

void SoundConfigState::OnExit(UIBase* ui)
{
    ConfigOnExit(ui);
}

int SoundConfigState::Update(UIBase* ui)
{
    ConfigDrawSetting(ui);

    ui->DefaultSelectProcess();
    ui->DefaultCloce();

    return mStateNumber;
}

int SoundConfigState::Decision(UIBase* ui)
{
    return mStateNumber;
}

void SoundConfigState::Draw(UIBase* ui)
{
    clsDx();
    printfDx("サウンド");
}

int SoundConfigState::Cloce(UIBase* ui)
{
    return GetConfigStateNumber(CONFIG_UI_STATE::SELECT_CONFIG_STATE);
}

/*----------------------*/
/*【カメラ設定ステート】*/
/*----------------------*/
CameraConfigState::CameraConfigState()
: ConfigUIProcess(&mStateNumber, CONFIG_UI_STATE::CAMERA_CONFIG_STATE)
{
    mStateNumber = (int)CONFIG_UI_STATE::CAMERA_CONFIG_STATE;
    SetConfigSlider(CONFIG_UI_STATE::CAMERA_CONFIG_STATE);

    
    DisplaySize displaySize = ResourceManager::mstDisplaySize;
    
    // スライダー 
    for (int i = 0; i < SLIDER_CHUNK_NUMBER; i++)
    {
        InitSetSlider(i);
    }

    for (int i = 0; i < mstDrawData.size(); i++)
    {
        Master::mpDrawManager->AddDrawData(&mstDrawData[i]);
    }

    // 背景作成
    {
        DRAW_DATA drawData;

        // 描画情報デフォルト設定
        {
            drawData.drawFlag = false;
            drawData.drawManagerDrawType = DRAW_MANAGER_DRAW_TYPE::GRAPH;
            drawData.drawGraphData.drawType = DRAW_GRAPH_TYPE::SIZE;
            drawData.drawGraphData.pos = displaySize.LeftUp_Ratio(CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP]);
            drawData.drawGraphData.size = displaySize.LeftUp_SeparateRatio(CONFIG_POSS[CONFIG_POS_TYPE::LEFT_UP], CONFIG_POSS[CONFIG_POS_TYPE::RIGHT_DOWN]);
            drawData.drawGraphData.transFlag = TRUE;
        }

        // カメラ
        {
            drawData.drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/ConfigUICamera.png");
            mstDrawData.push_back(drawData);
            Master::mpDrawManager->AddDrawData(&mstDrawData[mstDrawData.size() - 1], 0);
        }
    }
}

void CameraConfigState::OnEnter(UIBase* ui)
{
    ConfigOnEnter(ui);

    ui->SetSelectNumberChangeType(SELECT_NUMBER_FLAG_ENUM::CHANGE_BOUNDARY_STOP);
    ui->SetSelectMaxNumber(CAMERA_CONFIG_TYPE::MAX);
    ui->SetSelectNumber(mnPreSelectNumber);
}

void CameraConfigState::OnExit(UIBase* ui)
{
    ConfigOnExit(ui);
}

int CameraConfigState::Update(UIBase* ui)
{
    ConfigDrawSetting(ui);
    
    ui->DefaultSelectProcess();
    ui->DefaultCloce();
    
    return mStateNumber;
}

int CameraConfigState::Decision(UIBase* ui)
{
    return mStateNumber;
}

void CameraConfigState::Draw(UIBase* ui)
{
    clsDx();
    printfDx("カメラ");
}

int CameraConfigState::Cloce(UIBase* ui)
{
    return GetConfigStateNumber(CONFIG_UI_STATE::SELECT_CONFIG_STATE);
}