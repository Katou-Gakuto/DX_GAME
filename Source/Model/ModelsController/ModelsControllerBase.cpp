#include <vector>

#include "FSM.h"
#include "ModelBase.h"
#include "ModelsControllerBase.h"

ModelsControllerBase::ModelsControllerBase()
: mvModelPosition{0.0f, 0.0f, 0.0f}
, mvModelAngle{0.0f, 0.0f, 0.0f}
,mvModelSize{1.0f, 1.0f, 1.0f}
{
    mpFsm = nullptr;

    mpModelList.clear();
}

ModelsControllerBase::~ModelsControllerBase()
{
}

// 初期化
void ModelsControllerBase::Initilize()
{
    // FSM生成
    mpFsm = new FSMModelsController();
}

void ModelsControllerBase::Finalize()
{
    for (int i = 0; i < mpModelList.size(); i++)
    {
        mpModelList[i]->Finalize();
        delete mpModelList[i];
    }
    mpModelList.clear();

    delete mpFsm;
}

// モデル追加
void ModelsControllerBase::AddModel(ModelBase* model)
{
    mpModelList.push_back(model);
}

// モデル位置設定
void ModelsControllerBase::ModelsPositionSetting(bool useSetting, VECTOR position, VECTOR angle, VECTOR size)
{
    if (useSetting)
    {
        mvModelPosition = position;
        mvModelAngle = angle;
        mvModelSize = size;
    }

    // モデルに設定
    for (int i = 0; i < mpModelList.size(); i++)
    {
        mpModelList[i]->SetPosition(mvModelPosition);
        mpModelList[i]->SetAngle(mvModelAngle);
        mpModelList[i]->SetSize(mvModelSize);
        // INPROGRESS: 作業中回転させる
    }
}

// モデル更新
void ModelsControllerBase::UpdateModels()
{
    for (int i = 0; i < mpModelList.size(); i++)
    {
        mpModelList[i]->PositionUpdate();
    }
}