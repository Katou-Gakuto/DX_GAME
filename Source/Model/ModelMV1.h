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
    /*継承モデル終了*/
    void ModelFinalize() override;

	/*継承モデル ゲーム初期化*/
	void ModelGameInit() override;

public:
    /*ポジション更新*/
    void ModelUpdate() override;

    /*モデル描画*/
    void ModelDraw() override;

    /*モデルハンドル設定*/
    inline void SetModelHandle(int handle) { mnModelHandle = handle; }
    /*モデルハンドル設定*/
    void SetModelHandle(const char* filePath);

    /// <summary>ハンドル取得</summary>
    /// <returns>モデルハンドル</returns>
    int GetHandle() const override  { return mnModelHandle; }
};