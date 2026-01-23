#pragma once
#include <string>

#include "ModelBase.h"

class ModelEffect : public ModelBase
{
protected:
    // エフェクトハンドル
    int mnEffectHandle;

public:
    ModelEffect();
    ~ModelEffect();

    /// <summary>継承モデル初期化</summary>
	virtual void ModelInitilize() override;
    /// <summary>継承モデル終了</summary>
	virtual void ModelFinalize() override;
    /// <summary>ポジション更新</summary>
    virtual void PositionUpdate() override;

	/// <summary>モデル描画</summary>
	virtual void ModelDraw() override;

    /// <summary>エフェクトハンドル取得</summary>
    int *GetHandlePointer() override { return &mnEffectHandle; }
};