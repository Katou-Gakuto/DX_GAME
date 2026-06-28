#include <vector>

#include "FSM.h"
#include "ModelBase.h"
#include "ModelsController.h"

ModelsController::ModelsController()
: mvModelPosition{0.0f, 0.0f, 0.0f}
, mvModelAngle{0.0f, 0.0f, 0.0f}
, mvModelSize{1.0f, 1.0f, 1.0f}
, mbModelDrawFlag(true)
{
    mpModelList.clear();
}

ModelsController::~ModelsController()
{
}

// シーン最終初期化
void ModelsController::SceneLastInitilize()
{
    UpdateModels();
}

// 終了
void ModelsController::Finalize()
{
    for (int i = 0; i < mpModelList.size(); i++)
    {
        mpModelList[i]->Finalize();
        delete mpModelList[i];
    }
    mpModelList.clear();
}

// ゲーム中初期化
void ModelsController::ModelGameInit(VECTOR pos, VECTOR angle, VECTOR size)
{
    ModelsPositionSetting(pos, VGet(angle.x, angle.y - DX_PI_F, angle.z), size);

    for (int i = 0; i < mpModelList.size(); i++)
    {
        mpModelList[i]->ModelGameInit(mvModelPosition, mvModelAngle, mvModelSize);
    }
}

// モデル追加
void ModelsController::AddModel(ModelBase* model)
{
    mpModelList.push_back(model);
    //model->SetModelsController(this);
}

// モデル位置設定
void ModelsController::ModelsPositionSetting(VECTOR position, VECTOR angle, VECTOR size)
{
    mvModelPosition = position;
    mvModelAngle = VGet(angle.x, angle.y - DX_PI_F, angle.z);
    mvModelSize = size;
}

// モデル更新
void ModelsController::UpdateModels()
{
    for (int i = 0; i < mpModelList.size(); i++)
    {
        mpModelList[i]->Update(mvModelPosition, mvModelAngle);
    }
}

// モデル描画
void ModelsController::DrawModels()
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