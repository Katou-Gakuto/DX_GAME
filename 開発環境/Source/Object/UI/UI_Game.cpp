#include "AnimationEnum.h"
#include "SceneEnum.h"
#include "ResourceData.h"
#include "Vector2.h"


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
    std::vector<DRAW_GRAPH_DATA> setDrawDatas;
    DisplaySize displaySize = ResourceManager::mstDisplaySize;


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