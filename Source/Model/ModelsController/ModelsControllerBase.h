#pragma once
#include <vector>

#include "AnimationData.h"

#include "DxLib.h"

#include "FSM.h"
#include "ModelBase.h"

class ModelsControllerBase
{
private:
    // モデルリスト
    std::vector<ModelBase*> mpModelList;

    // 有限状態マシン
    FSMModelsController* mpFsm;

    // モデルポジション
    VECTOR mvModelPosition;

    // モデル角度
    VECTOR mvModelAngle;

    // モデルサイズ
    VECTOR mvModelSize;

public:
    ModelsControllerBase();
    ~ModelsControllerBase();

    /// <summary>初期化</summary>
    void Initilize();

    /// <summary>終了</summary>
    void Finalize();

    /// <summary>モデル追加</summary>
    /// <param name="model">追加するモデル</param>
    void AddModel(ModelBase* model);

    // TODO: アニメーションに移動

    /// <summary>アニメーションをモデルに反映</summary>
    /// <param name="animationDatas">アニメーション情報</param>
    inline void AnimationToModel(std::vector<AnimationData>& animationDatas) { mpFsm->Update(this, animationDatas); }

    /// <summary>モデル位置設定</summary>
    /// <param name="useSetting">設定を使うかどうか</param>
    /// <param name="position">ポジション</param>
    /// <param name="angle">角度</param>
    /// <param name="size">大きさ</param>
    void ModelsPositionSetting(bool useSetting = false, VECTOR position = VGet(0.0f, 0.0f, 0.0f), VECTOR angle = VGet(0.0f, 0.0f, 0.0f), VECTOR size = VGet(1.0f, 1.0f, 1.0f));

    /// <summary>モデル更新</summary>
    void UpdateModels();
    
    // TODO: 関数書く
    
    /// <summary>モデル描画</summary>
    inline void DrawModels() { mpFsm->Draw(this); }

    /*----------*/
    /*【取得・設定】
    /*----------*/

    /// <summary>モデルポジション取得</summary>
    inline VECTOR GetModelPosition() const { return mvModelPosition; }
    /// <summary>モデルポジション設定</summary>
    inline void SetModelPosition(VECTOR position) { mvModelPosition = position; }

    /// <summary>モデル角度取得</summary>
    inline VECTOR GetModelAngle() const { return mvModelAngle; }
    /// <summary>モデル角度設定</summary>
    inline void SetModelAngle(VECTOR angle) { mvModelAngle = angle; }

    /// <summary>モデルサイズ取得</summary>
    inline VECTOR GetModelSize() const { return mvModelSize; }
    /// <summary>モデルサイズ設定</summary>
    inline void SetModelSize(VECTOR size) { mvModelSize = size; }

    /// <summary>モデルリスト取得</summary>
    inline std::vector<ModelBase*> GetModelList() const { return mpModelList; }

    /// <summary>有限状態マシン取得</summary>
    inline FSMModelsController* GetFsm() const { return mpFsm; }
};