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

// モデル初期化
void ModelPolygonIndexed::ModelInitilize()
{
}

// モデル終了
void ModelPolygonIndexed::ModelFinalize()
{
}

// モデル描画
void ModelPolygonIndexed::ModelDraw()
{
    for (int i = 0; i < mstModelVertex.size(); i++)
    {
        DrawPolygonIndexed3D(mstModelVertex[i].vertex.data(), (int)mstModelVertex[i].vertex.size(),
                            &mstModelVertex[i].index[0].v1,   (int)mstModelVertex[i].index.size(),
            mstModelVertex[i].textureHandle,
            mstModelVertex[i].transFlag
        );
    }
}