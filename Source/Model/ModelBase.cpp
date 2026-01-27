#include "Master.h"

#include "ModelBase.h"
#include "ModelsControllerBase.h"
#include "ResourceManager.h"
#include "UtilCalc.h"

ModelBase::ModelBase()
: mvSize(UtilCalc::VZero)
, mpModelsController(nullptr)
{
}
ModelBase::~ModelBase()
{
}

// 初期化
void ModelBase::Initilize()
{
	ModelInitilize();
}

// 終了
void ModelBase::Finalize()
{
	ModelFinalize();
}

void ModelBase::SetModelsController(ModelsControllerBase* modelsController)
{
    mpModelsController = modelsController;
}

// モデル描画(頂点)
void ModelBase::ModelDraw_Indexed(const std::vector<IndexedData>& modelVertexData)
{
    for (int i = 0; i < modelVertexData.size(); i++)
    {
        // DrawPolygonIndexed3D(modelVertexData[i].vertex.data(), (int)modelVertexData[i].vertex.size(),
        //                     &modelVertexData[i].index[0].v1,   (int)modelVertexData[i].index.size(),
        //     modelVertexData[i].textureHandle,
        //     modelVertexData[i].transFlag
        // );
        Master::mpResourceManager->DrawIndexed(modelVertexData[i].vertex.data(), (int)modelVertexData[i].vertex.size(),
                                              &modelVertexData[i].index[0].v1,   (int)modelVertexData[i].index.size(),
            modelVertexData[i].textureHandle,
            modelVertexData[i].transFlag);
    }
}

// モデル描画(モデルハンドル)
void ModelBase::ModelDraw_Handle(const int handle)
{
    if (handle != -1)
    {
        Master::mpResourceManager->DrawModelHandle(handle);
    }
}

// モデル描画(画像)
void ModelBase::ModelDraw_Graph(const DRAW_GRAPH_DATA drawData)
{
    Master::mpResourceManager->DrawData_Graph(drawData);
}

// モデル描画(動画)
void ModelBase::ModelDraw_Movie(const DRAW_GRAPH_DATA drawData)
{
    Master::mpResourceManager->DrawData_Graph(drawData);
}