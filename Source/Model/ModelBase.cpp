#include <vector>

#include "BitFlag.h"
#include "ResourceData.h"

#include "DxLib.h"

#include "Animation.h"
#include "ModelBase.h"
#include "UtilCalc.h"

ModelBase::ModelBase()
: mpAnimation(nullptr)
, mvPosition(UtilCalc::VZero)
, mvAngle(UtilCalc::VZero)
, mvSize(UtilCalc::VOne)
, mbDrawFlag(true)
{
}
ModelBase::~ModelBase()
{
}


// シーン最終初期化
void ModelBase::SceneLastInitilize()
{
    if (mpAnimation != nullptr)
    {
        mpAnimation->SceneLastInitilize();
    }
}

// 終了
void ModelBase::Finalize()
{
    if (mpAnimation != nullptr)
    {
        mpAnimation->Finalize();
        delete mpAnimation;
    }

    ModelFinalize();
}

// 初期化
void ModelBase::ModelGameInit(VECTOR position, VECTOR angle, VECTOR size)
{
    mvPosition = position;
    mvAngle = VGet(angle.x, angle.y - DX_PI_F, angle.z);
    mvSize = size;

    ModelGameInit();
}

// 終了
void ModelBase::Update(VECTOR position, VECTOR angle)
{
    mvPosition = position;
    mvAngle = VGet(angle.x, angle.y - DX_PI_F, angle.z);

    if (mpAnimation != nullptr)
    {
        mpAnimation->Update();
    }

    // 継承モデル更新
    ModelUpdate();
}

/*--------*/
/*【設定】*/
/*--------*/

// このモデルのアニメーションとして設定
Animation* ModelBase::MyAnimationSetting(Animation* animtion)
{
    mpAnimation = animtion;
    if (mpAnimation != nullptr)
    {
        mpAnimation->Initilize(this);
    }
    return mpAnimation; 
}
// // モデル描画(頂点)
// void ModelBase::ModelDraw_Indexed(const std::vector<IndexedData>& modelVertexData)
// {
//     for (int i = 0; i < modelVertexData.size(); i++)
//     {
//         // DrawPolygonIndexed3D(modelVertexData[i].vertex.data(), (int)modelVertexData[i].vertex.size(),
//         //                     &modelVertexData[i].index[0].v1,   (int)modelVertexData[i].index.size(),
//         //     modelVertexData[i].textureHandle,
//         //     modelVertexData[i].transFlag
//         // );
//         Master::mpDrawManager->DrawIndexed(modelVertexData[i].vertex.data(), (int)modelVertexData[i].vertex.size(),
//                                               &modelVertexData[i].index[0].v1,   (int)modelVertexData[i].index.size(),
//             modelVertexData[i].textureHandle,
//             modelVertexData[i].transFlag);
//     }
// }

// // モデル描画(モデルハンドル)
// void ModelBase::ModelDraw_Handle(const int handle)
// {
//     if (handle != -1)
//     {
//         Master::mpDrawManager->DrawModelHandle(handle);
//     }
// }

// // モデル描画(画像)
// void ModelBase::ModelDraw_Graph(const DRAW_GRAPH_DATA drawData)
// {
//     Master::mpDrawManager->DrawData_Graph(drawData);
// }

// // モデル描画(動画)
// void ModelBase::ModelDraw_Movie(const DRAW_GRAPH_DATA drawData)
// {
//     Master::mpDrawManager->DrawData_Graph(drawData);
// }