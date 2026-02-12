#pragma once

#include <vector>

#include "ModelGraph.h"

class ModelMovie : public ModelGraph
{
private:
    std::vector<int> mnSinglePlayFlag;

public:
    ModelMovie();
    ~ModelMovie();

public:
    /*継承モデル初期化*/
    virtual void ModelInitilize() override;
    /*継承モデル終了*/
    virtual void ModelFinalize() override;
    /*ポジション更新*/
    virtual void PositionUpdate() override;

    /*動画描画*/
    virtual void ModelDraw() override;
};