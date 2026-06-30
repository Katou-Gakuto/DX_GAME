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
    void ModelFinalize() override;

	/*継承モデル ゲーム初期化*/
	void ModelGameInit() override;
    /*ポジション更新*/
    void ModelUpdate() override;

    /*動画描画*/
    void ModelDraw() override;
};