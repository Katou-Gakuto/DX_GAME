#pragma once
#include <vector>

#include "FSM.h"
#include "ModelBase.h"

class ModelsControllerBase
{
private:
    // モデルリスト
    std::vector<ModelBase*> mpModelList;

    // 有限状態マシン
    FSMModelsController* mpFsm;

public:
    ModelsControllerBase();
    ~ModelsControllerBase();

    /// <summary>初期化</summary>
    void Initilize();

    /// <summary>モデル追加</summary>
    /// <param name = model>追加するモデル</param>
    void AddModel(ModelBase* model);

    /// <summary>モデル配置変更</summary>
};