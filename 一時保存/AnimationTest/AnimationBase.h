#pragma once
#include <map>
#include <vector>

#include "AnimationData.h"
#include "ModelsControllerBase.h"

class FSMAnimation;

/*----------*/
/*【アニメーションベース】*/
/*----------*/
class AnimationBase
{
private:
    // モデルコントローラー
    ModelsControllerBase* mpModelsController;

    // アニメーション有限状態マシン
    FSMAnimation* mpFsm;

    // アニメーションデータ
    std::vector<AnimationDatas*> mstAnimationDatas;

    // アニメーション時間
    std::map<ANIMATION_TYPE, int> mmAnimationTime;

public:
    AnimationBase();
    ~AnimationBase() = default;

    /// <summary>初期化</summary>
    virtual void Initilize();

    /// <summary>シーン最終初期化</summary>
    virtual void SceneLastInitilize();

    /// <summary>終了</summary>
    virtual void Finalize();

    /// <summary>更新</summary>
    virtual void Update();

    /// <summary>アニメーションデータ追加</summary>
    inline void AddAnimationData(
        AnimationDatas* animationData)
    {
        mstAnimationDatas.push_back(animationData);
    }

    /// <summary>アニメーション種類探索</summary>
    inline bool SearchAnimationType(
        ANIMATION_TYPE animationType) const
    {
        return
            mmAnimationTime.find(animationType)
            != mmAnimationTime.end();
    }

    /*----------*/
    /*【取得・設定】*/
    /*----------*/
public:
    /// <summary>モデルコントローラー取得</summary>
    inline ModelsControllerBase*
        GetModelsController() const
    {
        return mpModelsController;
    }

    /// <summary>モデルコントローラー設定</summary>
    inline void SetModelsController(
        ModelsControllerBase* modelsController)
    {
        mpModelsController = modelsController;
    }

    /// <summary>FSM取得</summary>
    inline FSMAnimation* GetFsm() const
    {
        return mpFsm;
    }

    /// <summary>FSM設定</summary>
    inline void SetFsm(FSMAnimation* fsm)
    {
        mpFsm = fsm;
    }

    /// <summary>アニメーションデータ取得</summary>
    inline std::vector<AnimationDatas*>&
        GetAnimationDatas()
    {
        return mstAnimationDatas;
    }

    /// <summary>アニメーションデータ設定</summary>
    inline void SetAnimationDatas(
        const std::vector<AnimationDatas*>&
            animationDatas)
    {
        mstAnimationDatas = animationDatas;
    }

    /// <summary>現在ステート取得</summary>
    inline int GetCurrentAnimationState() const;

    /// <summary>次ステート設定</summary>
    inline void SetNextAnimationState(
        int state);
};