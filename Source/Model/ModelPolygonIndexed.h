#pragma once
#include <vector>

#include "BitFlag.h"
#include "DrawData.h"

#include "DxLib.h"

#include "ModelBase.h"

// ポリゴンインデックスモデルクラス
class ModelPolygonIndexed : public ModelBase
{
private:
    std::vector<IndexedData> mstModelVertex; // モデルデータ
public:
    ModelPolygonIndexed();
    ~ModelPolygonIndexed();

protected:
	/*継承モデル終了*/
	void ModelFinalize() override;

	/*継承モデル ゲーム初期化*/
	void ModelGameInit() override;
	/*継承モデル 更新*/
	void ModelUpdate() override;

public:
	/*モデル描画*/
	void ModelDraw() override;
    
    /*モデルデータ追加*/
    inline void AddModelData(const IndexedData& data) { mstModelVertex.push_back(data); }
};