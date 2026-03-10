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
#include "UtilChange.h"
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
    // INPROGRESS: 操作キーおよびHPを作成中 量表示用尾モデル(maxと現在地をポインタで持つモデル)作成
    std::vector<DRAW_GRAPH_DATA> setDrawDatas;
    DisplaySize displaySize = ResourceManager::mstDisplaySize;

    // ゲーム画面、HP
    {
        setDrawDatas.clear();
        DRAW_GRAPH_DATA drawData;
        // 操作キー
        {
            drawData.drawType = DRAW_GRAPH_TYPE::SIZE;
            drawData.transFlag = TRUE;
            // drawData.pos = displaySize.LeftUp_Ratio(Vector2(0.8f, 0.1f));
            // drawData.size = displaySize.LeftUp_Ratio(Vector2(1.0f, 0.2f));
            // drawData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/Button_A.png");
            // setDrawDatas.push_back(drawData);
            
            // drawData.pos = displaySize.LeftUp_Ratio(Vector2(0.8f, 0.1f));
            // drawData.size = displaySize.LeftUp_Ratio(Vector2(1.0f, 0.2f));
            // drawData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/Button_B.png");
            // setDrawDatas.push_back(drawData);
            
            // drawData.pos = displaySize.LeftUp_Ratio(Vector2(0.8f, 0.1f));
            // drawData.size = displaySize.LeftUp_Ratio(Vector2(1.0f, 0.2f));
            // drawData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/Button_X.png");
            // setDrawDatas.push_back(drawData);
            
            // drawData.pos = displaySize.LeftUp_Ratio(Vector2(0.8f, 0.1f));
            // drawData.size = displaySize.LeftUp_Ratio(Vector2(1.0f, 0.2f));
            // drawData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/Button_Y.png");
            // setDrawDatas.push_back(drawData);
            
            if (UtilChange::SceneState(Master::mpGameManager->GetSceneManager()->GetNowScene()) == SCENE::BATTLE)
            {
                drawData.pos = displaySize.RightDown_Ratio(Vector2(0.26f, 0.1f));
                drawData.size = Vector2_Int(displaySize.Left_RatioWidth(0.1f) * 0.4f, displaySize.Left_RatioWidth(0.1f) * 0.4f);
                drawData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/Button_R.png");
                setDrawDatas.push_back(drawData);
                
                drawData.pos = displaySize.RightDown_Ratio(Vector2(0.31f, 0.1f));
                drawData.size = Vector2_Int(displaySize.Left_RatioWidth(0.1f) * 0.4f, displaySize.Left_RatioWidth(0.1f) * 0.4f);
                drawData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/Button_L.png");
                setDrawDatas.push_back(drawData);
            }

            drawData.pos = displaySize.RightDown_Ratio(Vector2(0.135f, 0.175f));
            drawData.size = Vector2_Int(displaySize.Left_RatioWidth(0.1f) * 1.5f, displaySize.Left_RatioWidth(0.1f) * 1.5f);
            drawData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/Enter.png");
            setDrawDatas.push_back(drawData);
            
            drawData.pos = displaySize.RightDown_Ratio(Vector2(0.21f, 0.1f));
            drawData.size = displaySize.LeftUp_Ratio(Vector2(0.105f, 0.07f));
            drawData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/Button_WASD.png");
            setDrawDatas.push_back(drawData);
            
            drawData.pos = displaySize.RightDown_Ratio(Vector2(0.21f, 0.18f));
            drawData.size = displaySize.LeftUp_Ratio(Vector2(0.105f, 0.07f));
            drawData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/Button_Arrow.png");
            setDrawDatas.push_back(drawData);
        }
        
        // モデル追加
        AddModelData(setDrawDatas, MODEL_TYPE::GRAPH);

        DrawConfigData drawConfigData;
        drawConfigData.blendMode = DX_BLENDMODE_ALPHA;
        drawConfigData.blendParameter = 100;
        for (int i  = 0; i < mstUIDrawModels[mnUIModelControllerCount].mpUIModelController->GetModelList().size(); i++)
        {
            mstUIDrawModels[mnUIModelControllerCount].mpUIModelController->GetModelList()[i]->SetDrawConfigData(drawConfigData);
        }

        // アニメーション設定
        AnimationSetting(LOAD_ANIMATION_DATA_FACTORY_NUMBER::UI_BASE, {});
    }

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

        case SCENE::BATTLE_LOOP:
            stringNumber = -3;
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

    int testNumber = 10;
    // メニュー背景
    for (int i = 0; i < testNumber/*テスト*/; i++)
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

        if (i != (testNumber - 1))
        {
            continue;
        }

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

// UI最終初期化
void UI_Game::UISceneLastInitilize()
{
}

// UI終了
void UI_Game::UIFinalize()
{
}

// UI更新
void UI_Game::UIUpdate()
{
    //printfDx("%d\n", mnSelectNumber);

    //SetDrawBright(0.0f, 0.0f, 0.0f);
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
    if (mnSelectNumber < 0)
    {
        if (mnSelectNumber == -1)
        {
            SetUINumber();
            mpResourceManager->StopAllEfect();
        }
        else if (mnSelectNumber == -2)
        {
            DeleteUINumber();
            mpResourceManager->PlayAllEfect();
        }

        return;
    }

    mpFsm->Decision(this);
}

// 削除処理
void UI_Game::CloceProcess()
{
	if (mpFsm != nullptr)
	{
		mpFsm->Cloce(this);
	}
}