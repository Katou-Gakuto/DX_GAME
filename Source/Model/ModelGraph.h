#pragma once
#include <vector>

#include "ResourceData.h"

#include "ModelBase.h"

class ModelGraph : public ModelBase
{
protected:
    // 描画情報
    std::vector<DRAW_GRAPH_DATA> mstDrawDatas;

    // 前のポジション
    VECTOR mvPrePosition;

    // 前のアングル
    VECTOR mvPreAngle;

    // 前のサイズ
    VECTOR mvPreSize;

    // モデル描画情報
    DrawConfigData mstDrawConfigData;

public:
    ModelGraph();
    ~ModelGraph();

protected:
    /*継承モデル初期化*/
    virtual void ModelInitilize() override;
    /*継承モデル終了*/
    virtual void ModelFinalize() override;

public:
    /*ポジション更新*/
    virtual void PositionUpdate() override;

    /*画像描画*/
    virtual void ModelDraw() override;

    /// <summary>描画情報追加</summary>
    inline void AddDrawData(DRAW_GRAPH_DATA drawData) { mstDrawDatas.push_back(drawData); }

    /// <summary>描画情報設定</summary>
    inline void SetDrawDatas(std::vector<DRAW_GRAPH_DATA> drawData) { mstDrawDatas = drawData; }

    /// <summary>描画情報取得</summary>
    /// <returns>描画情報(複数)</returns>
    std::vector<DRAW_GRAPH_DATA>* GetDrawData() override { return &mstDrawDatas; }

	/// <summary>モデル描画情報の取得</summary>
    inline DrawConfigData GetDrawConfigData() override { return mstDrawConfigData; }
	/// <summary>モデル描画情報の設定</summary>
    inline void SetDrawConfigData(DrawConfigData drawConfigData) override { mstDrawConfigData = drawConfigData; }

protected:
    void SetDrawData(VECTOR pos, VECTOR angle, VECTOR size);
};