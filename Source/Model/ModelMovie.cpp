#include "ImguiEnum.h"
#include "ImguiData.h"

#include "DxLib.h"

#include "Master.h"

#include "DrawManager.h"
#include "ImguiManager.h"
#include "ModelGraph.h"
#include "ModelMovie.h"
#include "ModelBase.h"
#include "ResourceManager.h"
#include "ResourceMovie.h"
#include "StopManager.h"
#include "UtilCalc.h"

ModelMovie::ModelMovie()
: ModelGraph()
{
    mnSinglePlayFlag.clear();
}

ModelMovie::~ModelMovie()
{
}

// // ムービー初期化
// void ModelMovie::ModelInitilize()
// {
// 	IMGUI_FLOAT_DATA imguiFloatData;
// 	imguiFloatData.AddVariable(&mvPosition.x);
// 	imguiFloatData.AddVariable(&mvPosition.y);
// 	imguiFloatData.AddVariable(&mvSize.x);
// 	imguiFloatData.AddVariable(&mvSize.y);
// 	imguiFloatData.SetLabel("MOVIE_");
// 	imguiFloatData.SetImguiType(IMGUI_TYPE::DRAG4);
// 	imguiFloatData.SetMin(-100.0f);
// 	imguiFloatData.SetMax(100.0f);
// 	imguiFloatData.SetSpeed(0.01f);

// #ifdef _DEBUG
//     msDebugName = Master::mpImguiManager->SetFloatImgui(imguiFloatData);
// #endif
// }

// 終了
void ModelMovie::ModelFinalize()
{
#ifdef _DEBUG
    Master::mpImguiManager->DeleteImguiData(msDebugName);
#endif

    for (auto drawData : mstDrawDatas)
    {
        if (drawData.handle != -1)
        {
            Master::mpResourceManager->GetMovieResource()->ReduceResourceHandle(drawData.handle);
        }
    }
    mstDrawDatas.clear();
}

// ポジション更新
void ModelMovie::ModelUpdate()
{
    VECTOR size     = mvSize;
    VECTOR angle    = mvAngle;
    VECTOR position = mvPosition;

    // モデルコントローラーを反映する   
    // if (mpModelsController != nullptr)
    // {
    //     size     = UtilCalc::VMultiply(mvSize,     mpModelsController->GetModelSize());
    //     angle    = VAdd(mvAngle,    mpModelsController->GetModelAngle());
    //     position = VAdd(mvPosition, mpModelsController->GetModelPosition());
    // }

    SetDrawData(position, angle, size);

    for (int i = 0; i < mstDrawDatas.size(); i++)
    {
        // ループするかを確認
        int  j = 0;
        while (j < mnSinglePlayFlag.size())
        {
            if (mnSinglePlayFlag[j] == i)
            {
                break;
            }
            j++;
        }
        if (j < mnSinglePlayFlag.size())
        {
            continue;
        }

        // 動画ループ再生
        Master::mpResourceManager->GetMovieResource()->MovieLoop(mstDrawDatas[i].handle);
    }
}

// ムービー描画
void ModelMovie::ModelDraw()
{
    if (!mbDrawFlag || Master::mpStopManager->GetStopFlag(STOP_FLAG_TYPE::UI_MODEL))
    {
        return;
    }
    
    for (int i = 0; i < mstDrawDatas.size(); i++)
    {
        Master::mpDrawManager->DrawData_Graph(mstDrawDatas[i]);
    }
}