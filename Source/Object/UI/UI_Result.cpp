#include "GameDataEnum.h"
#include "CameraData.h"
#include "GameDatas.h"
#include "ResourceData.h"
#include "Status.h"

#include "Master.h"

#include "DataManager.h"
#include "FSMUI.h"
#include "ImguiManager.h"
#include "ResourceManager.h"
#include "Resourcemovie.h"
#include "UI_Result.h"
#include "UtilFactorys.h"

UI_Result::UI_Result()
: UIBase(true, 1)
, mnLineAeraSize(10000.0f)
, mnLineNum(50)
{
}

UI_Result::~UI_Result()
{
}

// HACK: テスト用　削除する
#define TEST_NUMBER 10

Vector2 TestPos[TEST_NUMBER] =  {Vector2(0.0f, 0.0f), 
                                Vector2(0.685f, 0.190f), Vector2(0.685f, 0.550f), Vector2(0.685f, 0.710f), 
                                
                                Vector2(0.080f, 0.156f), Vector2(0.080f, 0.301f), Vector2(0.080f, 0.406f), 
                                Vector2(0.080f, 0.510f), Vector2(0.080f, 0.620f), Vector2(0.080f, 0.730f)};

Vector2 TestSize[TEST_NUMBER] = {Vector2(1.0f, 1.0f),
                                Vector2(0.225f, 0.250f), Vector2(0.225f, 0.150f), Vector2(0.225f, 0.150f), 
                                
                                Vector2(0.520f, 0.140f), Vector2(0.520f, 0.100f), Vector2(0.520f, 0.100f), 
                                Vector2(0.520f, 0.100f), Vector2(0.520f, 0.100f), Vector2(0.520f, 0.100f)};

// UI初期化
void UI_Result::UIInitilize()
{
    std::vector<DRAW_GRAPH_DATA> setDrawDatas;

    {
        setDrawDatas.clear();
        DRAW_GRAPH_DATA drawData;
        drawData.drawType = DRAW_GRAPH_TYPE::SIZE;
        drawData.pos = Vector2_Int(0, 0);
        drawData.size = ResourceManager::mstDisplaySize.LeftUp_FloatRatio(1.0f);
        drawData.handle = Master::mpResourceManager->GetMovieResource()->GetResourceHandle(ResourceManager::msResourceFile + "Movie/ResultBack.mp4");
        drawData.transFlag = TRUE;
        setDrawDatas.push_back(drawData);
    }

    for (int i = 0; i < /*TEST_NUMBER*/1; i++)
    {
        setDrawDatas[0].pos = ResourceManager::mstDisplaySize.LeftUp_Ratio(TestPos[i]);
        setDrawDatas[0].size = ResourceManager::mstDisplaySize.LeftUp_Ratio(TestSize[i]);

        // モデル追加
        AddModelData(setDrawDatas, MODEL_TYPE::MOVIE);

        // アニメーション設定
        AnimationSetting(LOAD_ANIMATION_DATA_FACTORY_NUMBER::UI_BASE_MOVIE, {});
    }
}

// UIシーン最終初期化
void UI_Result::UISceneLastInitilize()
{
}

// UI終了
void UI_Result::UIFinalize()
{
}

// UI更新
void UI_Result::UIUpdate()
{
}

// UI最終更新
void UI_Result::UILastUpdate()
{
}

// UI描画
void UI_Result::UIDraw()
{

    //VECTOR pos1;
    //VECTOR pos2;

    //SetUseZBufferFlag(true);

    //pos1 = VGet(-mnLineAeraSize / 2.0f, 0.0f, -mnLineAeraSize / 2.0f);
    //pos2 = VGet(-mnLineAeraSize / 2.0f, 0.0f, mnLineAeraSize / 2.0f);
    //for (int i = 0; i < mnLineNum; i++)
    //{
    //    DrawLine3D(pos1, pos2, GetColor(0, 255, 0));
    //    pos1.x += mnLineAeraSize / mnLineNum;
    //    pos2.x += mnLineAeraSize / mnLineNum;
    //}

    //pos1 = VGet(-mnLineAeraSize / 2.0f, 0.0f, -mnLineAeraSize / 2.0f);
    //pos2 = VGet(mnLineAeraSize / 2.0f, 0.0f, -mnLineAeraSize / 2.0f);
    //for (int i = 0; i < mnLineNum; i++)
    //{
    //    DrawLine3D(pos1, pos2, GetColor(255, 0, 0));
    //    pos1.z += mnLineAeraSize / mnLineNum;
    //    pos2.z += mnLineAeraSize / mnLineNum;
    //}
}


// 選択決定時処理
void UI_Result::DecisionProcess()
{
    mpFsm->Decision(this);
}