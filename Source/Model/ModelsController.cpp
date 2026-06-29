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
    ModelUpdate();
}

// モデル終了
void ModelsController::ModelFinalize()
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

// 描画
void ModelsController::ModelDraw()
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

// モデル描画情報の設定
void ModelsController::SetDrawConfigData(DrawConfigData drawConfigData)
{
    for (int i = 0; mpModelList.size(); i++)
    {
        mpModelList[i]->SetDrawConfigData(drawConfigData);
    }
}

// 継承モデル ゲーム初期化
void ModelsController::ModelGameInit()
{
    ModelGameInit(mvModelPosition, mvModelAngle, mvModelSize);
}

// 継承モデル 更新
void ModelsController::ModelUpdate()
{
    for (int i = 0; i < mpModelList.size(); i++)
    {
        mpModelList[i]->Update(mvModelPosition, mvModelAngle);
    }
}