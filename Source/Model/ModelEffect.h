#pragma once
#include <string>

#include "ModelBase.h"
#include "ModelsControllerBase.h"

class ModelEffect : public ModelBase
{
protected:
    // エフェクトハンドル
    int mnEffectHandle;

    // 描画設定用ポジション
    VECTOR mvDrawPosition;
    // 描画設定用アングル
    VECTOR mvDrawAngle;
    // 描画設定用サイズ
    VECTOR mvDrawSize;

public:
    ModelEffect();
    ~ModelEffect();

    /// <summary>継承モデル初期化</summary>
	virtual void ModelInitilize() override;
    /// <summary>継承モデル終了</summary>
	virtual void ModelFinalize() override;

    /// <summary>ゲーム中初期化</summary>
    virtual void GameInit() override;
    
    /// <summary>ポジション更新</summary>
    virtual void PositionUpdate() override;

	/// <summary>モデル描画</summary>
	virtual void ModelDraw() override;

    /// <summary>エフェクトハンドル取得</summary>
    int *GetHandlePointer() override { return &mnEffectHandle; }
};