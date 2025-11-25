#include "DxLib.h"

#include "Master.h"

#include "ModelBase.h"
#include "ModelPolygonIndexed.h"
#include "ResourceManager.h"

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
        if (mstModelVertex[i].textureType.GetFlag(TEXTURE_TYPE::GRAPH))
        {
            Master::mpResourceManager->ReduceGraphHandle(mstModelVertex[i].textureHandle);
        }
        else if (mstModelVertex[i].textureType.GetFlag(TEXTURE_TYPE::MOVIE))
        {
            Master::mpResourceManager->ReduceMovie(mstModelVertex[i].textureHandle);
        }
    }
}

// モデル描画
void ModelPolygonIndexed::ModelDraw()
{
    ModelDraw_Indexed(mstModelVertex);
}