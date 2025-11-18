#pragma once

#include "DxLib.h"

#include "ModelBase.h"

class ModelMV1 : public ModelBase
{
private:
    int mModelHandle; // モデルハンドル
public:
    ModelMV1();
    ~ModelMV1();

protected:
    /*継承モデル初期化*/
    virtual void ModelInitilize() override;
    /*継承モデル終了*/
    virtual void ModelFinalize() override;

public:
    /*モデル描画*/
    virtual void ModelDraw() override;

    /*モデルハンドル設定*/
    inline void SetModelHandle(int handle) { mModelHandle = handle; }
    /*モデルハンドル設定*/
    void SetModelHandle(const char* filePath);
};