#pragma once

#include "ModelBase.h"

class ModelMV1 : public ModelBase
{
private:
    int mnModelHandle; // モデルハンドル
public:
    ModelMV1();
    ~ModelMV1();

protected:
    /*継承モデル初期化*/
    virtual void ModelInitilize() override;
    /*継承モデル終了*/
    virtual void ModelFinalize() override;

public:
    /*ポジション更新*/
    void PositionUpdate() override;

    /*モデル描画*/
    virtual void ModelDraw() override;

    /*モデルハンドル設定*/
    inline void SetModelHandle(int handle) { mnModelHandle = handle; }
    /*モデルハンドル設定*/
    void SetModelHandle(const char* filePath);

    /// <summary>ハンドル取得</summary>
    /// <returns>モデルハンドル</returns>
    int GetHandle() const override  { return mnModelHandle; }
};