#include "DxLib.h"

#include "Master.h"

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

// モデル初期化
void ModelPolygonIndexed::ModelInitilize()
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

// モデル描画
void ModelPolygonIndexed::ModelDraw()
{
    if (!mbDrawFlag)
    {
        return;
    }
    
    ModelDraw_Indexed(mstModelVertex);
}