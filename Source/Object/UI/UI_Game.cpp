#include "AnimationEnum.h"
#include "ResourceData.h"

#include "Master.h"

#include "FSM.h"
#include "ResourceManager.h"
#include "UI_Game.h"
#include "UtilFactorys.h"

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
    std::vector<DRAW_GRAPH_DATA> setDrawDatas;
    DisplaySize displaySize = ResourceManager::mstDisplaySize;

    {
        setDrawDatas.clear();
        DRAW_GRAPH_DATA drawData;
        drawData.drawType = DRAW_GRAPH_TYPE::SIZE;
        drawData.pos = displaySize.LeftUp_Ratio(Vector2(0.1f, 0.1f));
        drawData.size = displaySize.LeftUp_FloatRatio(0.8f);
        drawData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/TitleSelectBase.png");
        drawData.transFlag = TRUE;
        setDrawDatas.push_back(drawData);
    }

    // モデル追加
    AddModelData(setDrawDatas, MODEL_TYPE::GRAPH);

    // アニメーション設定
    AnimationSetting(LOAD_ANIMATION_DATA_FACTORY_NUMBER::UI_RESULT);
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