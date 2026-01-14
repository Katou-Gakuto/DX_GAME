#pragma once
#include <vector>

#include "ModelsControllerBase.h"

#include "FSM.h"

class AnimationBase
{
private:
    // モデルコントローラー
    ModelsControllerBase* mpModelsController;

    // アニメーション有限状態マシン
    FSMAnimation* mpFsm;    

    // アニメーションデータ
    std::vector<std::map<ANIMATION_TYPE, AnimationDatas>> mstAnimationDatas;

public:
    AnimationBase();
    ~AnimationBase() = default;

    /// <summary>初期化</summary>
    void Initilize();
    /// <summary>終了</summary>
    void Finalize();

    /// <summary>アニメーション更新</summary>
    void Update();

    /// <summary>アニメーションデータ追加</summary>
    void AddAnimationData(const std::map<ANIMATION_TYPE, AnimationDatas> animationData) { mstAnimationDatas.push_back(animationData); }

    /*----------*/
    /*【設定・取得】
    /*----------*/
public:
    /// <summary>モデルコントローラー取得</summary>
    inline ModelsControllerBase* GetModelsController() const { return mpModelsController; }
    /// <summary>モデルコントローラー設定</summary>
    inline void SetModelsController(ModelsControllerBase* modelsController) { mpModelsController = modelsController; }

    /// <summary>アニメーション有限状態マシン取得</summary>
    inline FSMAnimation* GetFsm() const { return mpFsm; }
    /// <summary>アニメーション有限状態マシン設定</summary>
    inline void SetFsm(FSMAnimation* fsm) { mpFsm = fsm; }

    /// <summary>アニメーションデータ取得</summary>
    inline std::vector<std::map<ANIMATION_TYPE, AnimationDatas>>& GetAnimationDatas() { return mstAnimationDatas; }
    /// <summary>アニメーションデータ設定</summary>
    inline void SetAnimationDatas(const std::vector<std::map<ANIMATION_TYPE, AnimationDatas>>& animationDatas) { mstAnimationDatas = animationDatas; }

    /// <summary>アニメーション種類設定</summary>
    inline void SetAnimationType(ANIMATION_TYPE animationType) { mpFsm->SetNextState(animationType); }
};