#include "AnimationEnum.h"
#include "SceneEnum.h"
#include "ResourceData.h"

#include "Master.h"

#include "FSM.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "StateGameUI.h"
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
{// INPROGRESS: 操作キーおよびHPを作成中
    std::vector<DRAW_GRAPH_DATA> setDrawDatas;
    DisplaySize displaySize = ResourceManager::mstDisplaySize;

    // ゲーム開始時字幕
    {
        setDrawDatas.clear();
        DRAW_GRAPH_DATA drawData;
        drawData.drawType = DRAW_GRAPH_TYPE::SIZE;
        drawData.pos = displaySize.LeftUp_Ratio(Vector2(0.0f, 0.1f));
        drawData.size = displaySize.LeftUp_Ratio(Vector2(1.0f, 0.2f));
        drawData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/White.png");
        drawData.transFlag = TRUE;
        setDrawDatas.push_back(drawData);


        int stringNumber = 0;
        switch (Master::mpGameManager->GetSceneManager()->GetNowScene())
        {
        case SCENE::TOWN_1:
            stringNumber++;
        case SCENE::TOWN_2:
            stringNumber++;
        case SCENE::TOWN_3:
            stringNumber++;
            drawData.drawType = DRAW_GRAPH_TYPE::SIZE;
            drawData.pos = displaySize.LeftUp_Ratio(Vector2(0.4f, 0.15f));
            drawData.size = displaySize.LeftUp_Ratio(Vector2(0.2f, 0.1f));
            drawData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/TownString_" + std::to_string(stringNumber) + ".png");
            drawData.transFlag = TRUE;
            setDrawDatas.push_back(drawData);
            break;

        case SCENE::DUNGEON_1:
            stringNumber++;
        case SCENE::DUNGEON_2:
            stringNumber++;
        case SCENE::DUNGEON_3:
            stringNumber++;
            drawData.drawType = DRAW_GRAPH_TYPE::SIZE;
            drawData.pos = displaySize.LeftUp_Ratio(Vector2(0.3f, 0.15f));
            drawData.size = displaySize.LeftUp_Ratio(Vector2(0.4f, 0.1f));
            drawData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/DungeonString_" + std::to_string(stringNumber) + ".png");
            drawData.transFlag = TRUE;
            setDrawDatas.push_back(drawData);
            break;

        case SCENE::BATTLE_1:
            stringNumber++;
        case SCENE::BATTLE_2:
            stringNumber++;
        case SCENE::BATTLE_3:
            stringNumber++;
            drawData.drawType = DRAW_GRAPH_TYPE::SIZE;
            drawData.pos = displaySize.LeftUp_Ratio(Vector2(0.325f, 0.15f));
            drawData.size = displaySize.LeftUp_Ratio(Vector2(0.35f, 0.1f));
            drawData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/BattleString_" + std::to_string(stringNumber) + ".png");
            drawData.transFlag = TRUE;
            setDrawDatas.push_back(drawData);
            break;
        }

        // モデル追加
        AddModelData(setDrawDatas, MODEL_TYPE::GRAPH);


        // アニメーション設定
        AnimationSetting(LOAD_ANIMATION_DATA_FACTORY_NUMBER::UI_FADE, { (int)GAME_UI_STATE::START_GAME_UI_STAE });
    }

    // メニュー背景
    {
        setDrawDatas.clear();
        DRAW_GRAPH_DATA drawData;
        drawData.drawType = DRAW_GRAPH_TYPE::SIZE;
        drawData.pos = displaySize.LeftUp_Ratio(Vector2(0.1f, 0.1f));
        drawData.size = displaySize.LeftUp_FloatRatio(0.8f);
        drawData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/TitleSelectBase.png");
        drawData.transFlag = TRUE;
        setDrawDatas.push_back(drawData);

        // モデル追加
        AddModelData(setDrawDatas, MODEL_TYPE::GRAPH);
        // 最初に見えなくする
        DrawConfigData drawConfigData;
        drawConfigData.blendMode = DX_BLENDMODE_ALPHA;
        drawConfigData.blendParameter = 0;
        for (int i = 0; i < mstUIDrawModels[mnUIModelControllerCount].mpUIModelController->GetModelList().size(); i++)
        {
            mstUIDrawModels[mnUIModelControllerCount].mpUIModelController->GetModelList()[i]->SetDrawConfigData(drawConfigData);
        }
        // アニメーション設定
        AnimationSetting(LOAD_ANIMATION_DATA_FACTORY_NUMBER::UI_FADE, {});
    }

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