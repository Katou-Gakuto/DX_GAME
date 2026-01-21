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

// èâä˙âª
void ModelBase::Initilize()
{
	ModelInitilize();
}

// èIóπ
void ModelBase::Finalize()
{
	ModelFinalize();
}

void ModelBase::SetModelsController(ModelsControllerBase* modelsController)
{
    mpModelsController = modelsController;
}

// ÉÇÉfÉãï`âÊ
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

// ÉÇÉfÉãï`âÊ
void ModelBase::ModelDraw_Handle(const int handle)
{
    if (handle != -1)
    {
        //MV1DrawModel(handle);
        Master::mpResourceManager->DrawModelHandle(handle);
    }
}