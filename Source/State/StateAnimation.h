#pragma once
#include <map>

#include "AnimationEnum.h"
#include "AnimationData.h"

#include "AnimationBase.h"
#include "ModelBase.h"
#include "StateBase.h"

// TODO: アニメーションのステートにする
class StateMVOneModel : public IStateAnimation
{
protected:
    // 前のアニメーション再生タイム
    int mnPreAnimNumber = -1;

    // 現在の全アニメーションのループ再生フラグ
    std::map<ANIMATION_TYPE, bool> mmLoopAnimationFlags;

    // 再生速度
    float mfAnimationSpeed = 0.5f;

public:
    StateMVOneModel();
    ~StateMVOneModel() = default;

    // この状態に入った時の処理
    void OnEnter(ModelsControllerBase* modelsController, AnimationData& animationDatas, ModelBase* model) override;
    // この状態を出る時の処理
    void OnExit(ModelsControllerBase* modelsController, AnimationData& animationDatas, ModelBase* model) override;

    // 更新
    void Update(ModelsControllerBase* modelsController, AnimationData& animationDatas, ModelBase* model) override;

protected:
    // アニメーションモデル切り替え
    virtual void ChangeAnimationModel();

    // アニメーション更新
    virtual void UpdateAnimation();

    
};