#include <stdlib.h>
#include <map>
#include <vector>

#include "CameraData.h"
#include "ResourceData.h"
#include "Vector2.h"

#include "Master.h"

#include "FSMUI.h"
#include "ResourceGraph.h"
#include "ResourceManager.h"
#include "ResourceMovie.h"
#include "StateTitleUI.h"
#include "UI_Title.h"
#include "UtilCalc.h"
#include "UtilFactorys.h"

UI_Title::UI_Title()
: UIBase(true, 1)
, mnLineAeraSize(10000.0f)
, mnLineNum(50)
{
}

UI_Title::~UI_Title()
{
}

// UI初期化
void UI_Title::UIInitilize()
{
    std::vector<DRAW_GRAPH_DATA> setDrawDatas;
    DRAW_GRAPH_DATA drawData;
    
    std::vector<std::map<int, VECTOR>> setUIPosData;    // UI座標情報設定用変数

    DisplaySize displaySize = ResourceManager::mstDisplaySize;
    
    // 映像設定
    {
        setDrawDatas.clear();
        
        drawData.drawType = DRAW_GRAPH_TYPE::SIZE;
        drawData.pos = Vector2_Int(0, 0);
        drawData.size = displaySize.LeftUp_FloatRatio(1.0f);
        drawData.handle = Master::mpResourceManager->GetMovieResource()->GetResourceHandle(ResourceManager::msResourceFile + "Movie/TitleBack_1.mp4");// TODO: 時間帯で色変更
        drawData.transFlag = TRUE;
        setDrawDatas.push_back(drawData);

        // モデル追加
        AddModelData(setDrawDatas, ANIMATION_TYPE::MOVIE);
        // アニメーション設定
        AnimationSetting(LOAD_ANIMATION_DATA_FACTORY_NUMBER::UI_BASE_MOVIE, {});
    }


    // 固定画像設定
    {
        setDrawDatas.clear();
        
        // タイトル文字
        {
            drawData.pos = displaySize.LeftUp_Ratio(Vector2(0.1f, 0.1f));
            drawData.size = displaySize.LeftUp_Ratio(Vector2(0.8f, 0.2f));
            drawData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle(ResourceManager::msResourceFile + "2D/TitleString.png");
            setDrawDatas.push_back(drawData);
            // モデル追加
            AddModelData(setDrawDatas, ANIMATION_TYPE::GRAPH);
            // アニメーション設定
            AnimationSetting(LOAD_ANIMATION_DATA_FACTORY_NUMBER::UI_BASE, { (int)STATE_TYPE_UI::START_TITLE_UI_STATE, (int)STATE_TYPE_UI::SELECT_TITLE_UI_STATE });
            
            setDrawDatas.clear();
        }

        drawData.pos = displaySize.LeftUp_Ratio(Vector2(0.1f, 0.4f));
        drawData.size = displaySize.LeftUp_Ratio(Vector2(0.8f, 0.5f));
        drawData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle(ResourceManager::msResourceFile + "2D/TitleSelectBase.png");
        setDrawDatas.push_back(drawData);

        // 文字背景
        {
            drawData.pos = displaySize.LeftUp_Ratio(Vector2(0.16f, 0.5f));
            drawData.size = displaySize.LeftUp_Ratio(Vector2(0.31f, 0.1f));
            drawData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle(ResourceManager::msResourceFile + "2D/StringBack_Close.png");
            setDrawDatas.push_back(drawData);
            drawData.pos = displaySize.LeftUp_Ratio(Vector2(0.16f, 0.7f));
            drawData.size = displaySize.LeftUp_Ratio(Vector2(0.31f, 0.1f));
            drawData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle(ResourceManager::msResourceFile + "2D/StringBack.png");
            setDrawDatas.push_back(drawData);
            
            drawData.pos = displaySize.LeftUp_Ratio(Vector2(0.53f, 0.5f));
            drawData.size = displaySize.LeftUp_Ratio(Vector2(0.31f, 0.1f));
            drawData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle(ResourceManager::msResourceFile + "2D/StringBack_Close.png");
            setDrawDatas.push_back(drawData);
            drawData.pos = displaySize.LeftUp_Ratio(Vector2(0.53f, 0.7f));
            drawData.size = displaySize.LeftUp_Ratio(Vector2(0.31f, 0.1f));
            drawData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle(ResourceManager::msResourceFile + "2D/StringBack_Close.png");
            setDrawDatas.push_back(drawData);
        }

        // 文字
        {
            drawData.pos = displaySize.LeftUp_Ratio(Vector2(0.185f, 0.52f));
            drawData.size = displaySize.LeftUp_Ratio(Vector2(0.26f, 0.06f));
            drawData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle(ResourceManager::msResourceFile + "2D/NewData_String.png");
            setDrawDatas.push_back(drawData);
            drawData.pos = displaySize.LeftUp_Ratio(Vector2(0.185f, 0.72f));
            drawData.size = displaySize.LeftUp_Ratio(Vector2(0.26f, 0.06f));
            drawData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle(ResourceManager::msResourceFile + "2D/DataSelect_String.png");
            setDrawDatas.push_back(drawData);
            
            drawData.pos = displaySize.LeftUp_Ratio(Vector2(0.555f, 0.52f));
            drawData.size = displaySize.LeftUp_Ratio(Vector2(0.26f, 0.06f));
            drawData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle(ResourceManager::msResourceFile + "2D/Tutorial_String.png");
            setDrawDatas.push_back(drawData);
            drawData.pos = displaySize.LeftUp_Ratio(Vector2(0.555f, 0.72f));
            drawData.size = displaySize.LeftUp_Ratio(Vector2(0.26f, 0.06f));
            drawData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle(ResourceManager::msResourceFile + "2D/Setting_String.png");
            setDrawDatas.push_back(drawData);
        }

        // モデル追加
        AddModelData(setDrawDatas, ANIMATION_TYPE::GRAPH);
        // アニメーション設定
        AnimationSetting(LOAD_ANIMATION_DATA_FACTORY_NUMBER::UI_FADE, { (int)STATE_TYPE_UI::SELECT_TITLE_UI_STATE });
        setDrawDatas.clear();
    }

    // 移動画像設定
    {
        drawData.pos = displaySize.LeftUp_Ratio(Vector2(0.135f, 0.48f));
        drawData.size = displaySize.LeftUp_Ratio(Vector2(0.36f, 0.15f));
        drawData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle(ResourceManager::msResourceFile + "2D/SelectString_1.png");
        setDrawDatas.push_back(drawData);

        // モデル追加
        AddModelData(setDrawDatas, ANIMATION_TYPE::GRAPH);
        // アニメーション設定
        AnimationSetting(LOAD_ANIMATION_DATA_FACTORY_NUMBER::UI_BASE, { (int)STATE_TYPE_UI::SELECT_TITLE_UI_STATE });
        setDrawDatas.clear();

        setUIPosData.resize(mstUIDrawModels.size()/*mpUIModelController->GetModelList().size()*/);   // モデル数分確保
        // setUIPosData[mpUIModelController->GetModelList().size() - 1][0] = VGet(0.135f, 0.48f, 0.0f);
        // setUIPosData[mpUIModelController->GetModelList().size() - 1][1] = VGet(0.135f, 0.68f, 0.0f);
        // setUIPosData[mpUIModelController->GetModelList().size() - 1][2] = VGet(0.505f, 0.48f, 0.0f);
        // setUIPosData[mpUIModelController->GetModelList().size() - 1][3] = VGet(0.505f, 0.68f, 0.0f);
        setUIPosData[mstUIDrawModels.size() - 1][0] = VGet(0.0f, 0.0f, 0.0f);
        setUIPosData[mstUIDrawModels.size() - 1][1] = VGet(0.0f, 0.196f, 0.0f);
        setUIPosData[mstUIDrawModels.size() - 1][2] = VGet(0.37f, 0.0f, 0.0f);
        setUIPosData[mstUIDrawModels.size() - 1][3] = VGet(0.37f, 0.196f, 0.0f);
        std::vector<std::map<int, VECTOR>> nullUIPosData;
        nullUIPosData.clear();
        for (int i = 0; i < UI_Title::TITLE_STATE_MAX; i++)
        {
            switch (static_cast<STATE_TYPE_UI>(i + static_cast<int>(STATE_TYPE_UI::START_TITLE_UI_STATE)))
            {
            case STATE_TYPE_UI::SELECT_TITLE_UI_STATE:
            case STATE_TYPE_UI::DATA_SELECT_TITLE_UI_STATE:
            case STATE_TYPE_UI::SETTING_TITLE_UI_STATE:
            case STATE_TYPE_UI::CHARACTER_SELECT_TITLE_UI_STATE:
            case STATE_TYPE_UI::PLAYER_NAME_TITLE_UI_STATE:
            case STATE_TYPE_UI::INPUT_CHECK_TITLE_UI_STATE:
            case STATE_TYPE_UI::SCREEN_SIZE_TITLE_UI_STATE:
            case STATE_TYPE_UI::VOLUME_TITLE_UI_STATE:
                mmUIPositionData[i] = setUIPosData;
                break;
            default:
                mmUIPositionData[i] = nullUIPosData;
                break;
            }
        }
    }

	// // モデル設定
    // mpUIModelController->AddModel(UtilFactorys::ModelFactory(ANIMATION_TYPE::MOVIE, "", UtilCalc::VZero, UtilCalc::VZero, UtilCalc::VOne, &setDrawDatas));
	// // アニメション設定
	//  {
	//  	std::vector<std::vector<LoadAnimationData>> setcharacterLoadAnimationData;
	//  	// 読み込み用アニメーションデータ設定
	//  	setcharacterLoadAnimationData.push_back(UtilFactorys::LoadAnimationDataFactory(mpAnimation, LOAD_ANIMATION_DATA_FACTORY_NUMBER::UI_TITLE));
	//  	// アニメーション有限状態マシン設定
	//  	mpAnimation->SetFsm(UtilFactorys::FSMAnimationFactory(mpAnimation, ANIMATION_FACTORY_NUMBER::UI, LOAD_ANIMATION_DATA_FACTORY_NUMBER::UI_TITLE, setcharacterLoadAnimationData));
	//  }

    // プレイヤー画像設定
    {
        SetGraphCount(1);
        SetGraphHandle(0, mpResourceManager->GetGraphResource()->GetResourceHandle(ResourceManager::msResourceFile + "2D/RobotSphere.png"));
    }
}

// UIシーン最終初期化
void UI_Title::UISceneLastInitilize()
{
}

// UI終了
void UI_Title::UIFinalize()
{
}

// UI更新
void UI_Title::UIUpdate()
{
}

// UI最終更新
void UI_Title::UILastUpdate()
{
}

// UI描画
void UI_Title::UIDraw()
{

    // VECTOR pos1;
    // VECTOR pos2;

    // SetUseZBufferFlag(true);

    // pos1 = VGet(-mnLineAeraSize / 2.0f, 0.0f, -mnLineAeraSize / 2.0f);
    // pos2 = VGet(-mnLineAeraSize / 2.0f, 0.0f, mnLineAeraSize / 2.0f);
    // for (int i = 0; i < mnLineNum; i++)
    // {
    //     DrawLine3D(pos1, pos2, GetColor(0, 255, 0));
    //     pos1.x += mnLineAeraSize / mnLineNum;
    //     pos2.x += mnLineAeraSize / mnLineNum;
    // }

    // pos1 = VGet(-mnLineAeraSize / 2.0f, 0.0f, -mnLineAeraSize / 2.0f);
    // pos2 = VGet(mnLineAeraSize / 2.0f, 0.0f, -mnLineAeraSize / 2.0f);
    // for (int i = 0; i < mnLineNum; i++)
    // {
    //     DrawLine3D(pos1, pos2, GetColor(255, 0, 0));
    //     pos1.z += mnLineAeraSize / mnLineNum;
    //     pos2.z += mnLineAeraSize / mnLineNum;
    // }
}


// 選択決定時処理
void UI_Title::DecisionProcess()
{
	mpFsm->Decision(this);
}

// 削除処理
void UI_Title::CloseProcess()
{
	if (mpFsm != nullptr)
	{
		mpFsm->Close(this);
	}
}