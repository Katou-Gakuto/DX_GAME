#pragma once
#include "ModelsControllerBase.h"

class AnimationBase
{
private:
    // モデルコントローラー
    ModelsControllerBase* mpModelsController;

public:
    AnimationBase();
    ~AnimationBase() = default;

    /// <summary>初期化</summary>
    void Initilize();
    /// <summary>終了</summary>
    void Finalize();

    /*----------*/
    /*【設定・取得】
    /*----------*/

    // モデルコントローラー取得
    inline ModelsControllerBase* GetModelsController() const { return mpModelsController; }
    // モデルコントローラー設定
    inline void SetModelsController(ModelsControllerBase* modelsController) { mpModelsController = modelsController; }
};