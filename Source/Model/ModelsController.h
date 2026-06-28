#pragma once
#include <vector>

#include "AnimationData.h"

#include "DxLib.h"

#include "ModelBase.h"

class ModelsController : public ModelBase
{
private:
    // モデルリスト
    std::vector<ModelBase*> mpModelList;

    // モデルポジション
    VECTOR mvModelPosition;

    // モデル角度
    VECTOR mvModelAngle;

    // モデルサイズ
    VECTOR mvModelSize;

    // モデル描画フラグ
    bool mbModelDrawFlag;

public:
    ModelsController();
    ~ModelsController();

    /// <summary>シーン最終初期化</summary>
    void SceneLastInitilize();

    /// <summary>終了</summary>
    void Finalize();

    /// <summary>ゲーム中初期化</summary>
    void ModelGameInit(VECTOR pos, VECTOR angle, VECTOR size);

    /// <summary>モデル追加</summary>
    /// <param name="model">追加するモデル</param>
    void AddModel(ModelBase* model);

    /// <summary>モデル位置設定</summary>
    /// <param name="useSetting">設定を使うかどうか</param>
    /// <param name="position">ポジション</param>
    /// <param name="angle">角度</param>
    /// <param name="size">大きさ</param>
    void ModelsPositionSetting(VECTOR position, VECTOR angle, VECTOR size);
    void ModelsPositionSetting(VECTOR position, VECTOR angle) { ModelsPositionSetting(position, angle, mvModelSize); }
    void ModelsPositionSetting(VECTOR position){ ModelsPositionSetting(position, mvModelAngle, mvModelSize); }
    void ModelsPositionSetting(){ ModelsPositionSetting(mvModelPosition, mvModelAngle, mvModelSize); }

    /// <summary>モデル更新</summary>
    void UpdateModels();
    
    /// <summary>モデル描画</summary>
    void DrawModels();

    /*----------*/
    /*【取得・設定】
    /*----------*/

    /// <summary>モデルポジション取得</summary>
    inline VECTOR GetModelPosition() const { return mvModelPosition; }
    /// <summary>モデルポジション設定</summary>
    inline void SetModelPosition(VECTOR position) { mvModelPosition = position; }
    /// <summary>モデルポジションポインタ</summary>
    inline VECTOR* GetModelPositionPointer() { return &mvModelPosition; }

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
    /// <summary>モデルリスト設定</summary>
    inline void SetModelsList(std::vector<ModelBase*> models) { mpModelList = models; }

    /// <summary>UIモデル描画フラグ設定</summary>
    inline void SetModelDrawFlag(bool flag) { mbModelDrawFlag = flag; }
};