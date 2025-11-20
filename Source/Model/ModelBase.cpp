#include "ModelBase.h"
#include "UtilCalc.h"

ModelBase::ModelBase()
: mvSize(UtilCalc::VZero)
{
}
ModelBase::~ModelBase()
{
}

// ‰Šú‰»
void ModelBase::Initilize()
{
	ModelInitilize();
}

// I—¹
void ModelBase::Finalize()
{
	ModelFinalize();
}

// ƒ‚ƒfƒ‹•`‰æ
void ModelBase::ModelDraw_Indexed(const std::vector<IndexedData>& modelVertexData)
{
    for (int i = 0; i < modelVertexData.size(); i++)
    {
        DrawPolygonIndexed3D(modelVertexData[i].vertex.data(), (int)modelVertexData[i].vertex.size(),
                            &modelVertexData[i].index[0].v1,   (int)modelVertexData[i].index.size(),
            modelVertexData[i].textureHandle,
            modelVertexData[i].transFlag
        );
    }
}

// ƒ‚ƒfƒ‹•`‰æ
void ModelBase::ModelDraw_Handle(const int handle)
{
    if (handle != -1)
    {
        MV1DrawModel(handle);
    }
}