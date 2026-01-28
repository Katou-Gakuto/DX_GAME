// filepath: c:\Users\student3\source\repos\DX_GAME\Source\Model\ModelMovie.cpp
#include "DxLib.h"

#include "Master.h"

#include "ModelGraph.h"
#include "ModelMovie.h"
#include "ModelsControllerBase.h"
#include "ResourceManager.h"
#include "UtilCalc.h"

ModelMovie::ModelMovie()
: ModelGraph()
{
    mnSinglePlayFlag.clear();
}

ModelMovie::~ModelMovie()
{
}

// グラフィック初期化
void ModelMovie::ModelInitilize()
{
}

// グラフィック終了
void ModelMovie::ModelFinalize()
{
    for (auto drawData : mstDrawDatas)
    {
        if (drawData.handle != -1)
        {
            Master::mpResourceManager->ReduceMovie(drawData.handle);
        }
    }
    mstDrawDatas.clear();
}

// ポジション更新
void ModelMovie::PositionUpdate()
{
    VECTOR size     = mvSize;
    VECTOR angle    = mvAngle;
    VECTOR position = mvPosition;

    // モデルコントローラーを反映する   
    if (mpModelsController != nullptr)
    {
        size     = UtilCalc::VMultiply(mvSize,     mpModelsController->GetModelSize());
        angle    = VAdd(mvAngle,    mpModelsController->GetModelAngle());
        position = VAdd(mvPosition, mpModelsController->GetModelPosition());
    }

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
        Master::mpResourceManager->MovieLoop(mstDrawDatas[i].handle);
    }
}

// ムービー描画
void ModelMovie::ModelDraw()
{
    for (int i = 0; i < mstDrawDatas.size(); i++)
    {
        ModelDraw_Movie(mstDrawDatas[i]);
    }
}