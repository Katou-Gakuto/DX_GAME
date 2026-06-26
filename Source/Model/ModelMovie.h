#pragma once

#include <vector>

#include "ModelGraph.h"

class ModelMovie : public ModelGraph
{
private:
    std::vector<int> mnSinglePlayFlag;
#ifdef _DEBUG
    std::string msDebugName;
#endif

public:
    ModelMovie();
    ~ModelMovie();

public:
    /*継承モデル終了*/
    virtual void ModelFinalize() override;
    /*ポジション更新*/
    virtual void ModelUpdate() override;

    /*動画描画*/
    virtual void ModelDraw() override;
};