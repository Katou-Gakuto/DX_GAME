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

// ÉÇÉfÉãèIóπ
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

// ÉÇÉfÉãï`âÊ
void ModelPolygonIndexed::ModelDraw()
{
    if (!mbDrawFlag)
    {
        return;
    }
    
    Master::mpDrawManager->ModelDraw_Indexed(mstModelVertex);
}