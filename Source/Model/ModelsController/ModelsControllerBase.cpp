#include <vector>

#include "ModelBase.h"
#include "ModelsControllerBase.h"

ModelsControllerBase::ModelsControllerBase()
: mvModelPosition{0.0f, 0.0f, 0.0f}
, mvModelAngle{0.0f, 0.0f, 0.0f}
,mvModelSize{1.0f, 1.0f, 1.0f}
, mbModelDrawFlag(true)
{
    mpModelList.clear();
}

ModelsControllerBase::~ModelsControllerBase()
{
}

// 初期化
void ModelsControllerBase::Initilize()
{
}

// シーン最終初期化
void ModelsControllerBase::SceneLastInitilize()
{
    UpdateModels();
}

// 終了
void ModelsControllerBase::Finalize()
{
    for (int i = 0; i < mpModelList.size(); i++)
    {
        mpModelList[i]->Finalize();
        delete mpModelList[i];
    }
    mpModelList.clear();
}

// ゲーム中初期化
void ModelsControllerBase::GameInit(VECTOR pos, VECTOR angle, VECTOR size)
{
    ModelsPositionSetting(pos, VGet(angle.x, angle.y - DX_PI_F, angle.z), size);

    for (int i = 0; i < mpModelList.size(); i++)
    {
        mpModelList[i]->GameInit();
    }
}

// モデル追加
void ModelsControllerBase::AddModel(ModelBase* model)
{
    mpModelList.push_back(model);
    model->SetModelsController(this);
}

// モデル位置設定
void ModelsControllerBase::ModelsPositionSetting(VECTOR position, VECTOR angle, VECTOR size)
{
    mvModelPosition = position;
    mvModelAngle = VGet(angle.x, angle.y - DX_PI_F, angle.z);
    mvModelSize = size;
}

// モデル更新
void ModelsControllerBase::UpdateModels()
{
    for (int i = 0; i < mpModelList.size(); i++)
    {
        mpModelList[i]->PositionUpdate();
    }
}

// モデル描画
void ModelsControllerBase::DrawModels()
{
    if (!mbModelDrawFlag)
    {
        return;
    }

	for (int i = 0; i < mpModelList.size(); i++)
	{
		mpModelList[i]->ModelDraw();
	}
}