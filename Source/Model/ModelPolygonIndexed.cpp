#include <vector>

#include "DrawData.h"

#include "DxLib.h"

#include "Master.h"

#include "DrawManager.h"
#include "ModelBase.h"
#include "ModelPolygonIndexed.h"
#include "ResourceGraph.h"
#include "ResourceManager.h"
#include "ResourceMovie.h"

ModelPolygonIndexed::ModelPolygonIndexed()
{
    mstModelVertex.clear();
}
ModelPolygonIndexed::~ModelPolygonIndexed()
{
}

// モデル終了
void ModelPolygonIndexed::ModelFinalize()
{
    for (int i = 0; i < mstModelVertex.size(); i++)
    {
        if (mstModelVertex[i].textureType.GetFlag_BitShift(TEXTURE_TYPE::GRAPH))
        {
            Master::mpResourceManager->GetGraphResource()->ReduceResourceHandle(mstModelVertex[i].textureHandle);
        }
        else if (mstModelVertex[i].textureType.GetFlag_BitShift(TEXTURE_TYPE::MOVIE))
        {
            Master::mpResourceManager->GetMovieResource()->ReduceResourceHandle(mstModelVertex[i].textureHandle);
        }
    }
}

// 継承モデル ゲーム初期化
void ModelPolygonIndexed::ModelGameInit()
{
}

// 継承モデル 更新
void ModelPolygonIndexed::ModelUpdate()
{
}

// モデル描画
void ModelPolygonIndexed::ModelDraw()
{
    if (!mbDrawFlag)
    {
        return;
    }
    
    Master::mpDrawManager->ModelDraw_Indexed(mstModelVertex);
}