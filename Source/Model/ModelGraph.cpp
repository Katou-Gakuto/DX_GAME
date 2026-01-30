#include "DxLib.h"

#include "Master.h"

#include "ModelBase.h"
#include "ModelGraph.h"
#include "ModelsControllerBase.h"
#include "ResourceManager.h"
#include "UtilCalc.h"

ModelGraph::ModelGraph()
: ModelBase()
, mvPreSize(UtilCalc::VOne)
, mvPreAngle(UtilCalc::VZero)
, mvPrePosition(UtilCalc::VZero)
{
    mstDrawDatas.clear();
}

ModelGraph::~ModelGraph()
{
}

// グラフィック初期化
void ModelGraph::ModelInitilize()
{
}

// グラフィック終了
void ModelGraph::ModelFinalize()
{
    for (auto drawData : mstDrawDatas)
    {
        if (drawData.handle != -1)
        {
            Master::mpResourceManager->ReduceGraphHandle(drawData.handle);
        }
    }
    mstDrawDatas.clear();
}

// ポジション更新
void ModelGraph::PositionUpdate()
{
    VECTOR size     = mvSize;
    VECTOR angle    = mvAngle;
    VECTOR position = mvPosition;

    // モデルコントローラーを反映する   
    if (mpModelsController != nullptr)
    {
        size     = UtilCalc::VMultiply(mvSize,     mpModelsController->GetModelSize());
        angle    = VAdd(mvAngle,    mpModelsController->GetModelAngle());
        position = VAdd(mvPosition, mpModelsController->GetModelPosition());
    }

    SetDrawData(position, angle, size);
}

// グラフィック描画
void ModelGraph::ModelDraw()
{
    if (!mbDrawFlag)
    {
        return;
    }

    for (int i = 0; i < mstDrawDatas.size(); i++)
    {
        ModelDraw_Graph(mstDrawDatas[i]);
    }
}

void ModelGraph::SetDrawData(VECTOR pos, VECTOR angle, VECTOR size)
{
    for (int i = 0; i < mstDrawDatas.size(); i++)
    {
        switch (mstDrawDatas[i].drawType)
        {
	case DRAW_GRAPH_TYPE::NORMAL:
	case DRAW_GRAPH_TYPE::TURN:
        mstDrawDatas[i].pos.x = ResourceManager::mstDisplaySize.Left_RatioWidth(pos.x);
        mstDrawDatas[i].pos.y = ResourceManager::mstDisplaySize.Left_RatioWidth(pos.y);
		break;

	case DRAW_GRAPH_TYPE::EXTEND:
        mstDrawDatas[i].pos.x = ResourceManager::mstDisplaySize.Left_RatioWidth(pos.x);
        mstDrawDatas[i].pos.y = ResourceManager::mstDisplaySize.Left_RatioWidth(pos.y);
        mstDrawDatas[i].extPos.x = ResourceManager::mstDisplaySize.Left_RatioWidth(size.x) + mstDrawDatas[i].pos.x;
        mstDrawDatas[i].extPos.y = ResourceManager::mstDisplaySize.Left_RatioWidth(size.y) + mstDrawDatas[i].pos.y;
		break;

	case DRAW_GRAPH_TYPE::ROTA:
        mstDrawDatas[i].pos.x = ResourceManager::mstDisplaySize.Left_RatioWidth(pos.x);
        mstDrawDatas[i].pos.y = ResourceManager::mstDisplaySize.Left_RatioWidth(pos.y);
        mstDrawDatas[i].extPos.x = ResourceManager::mstDisplaySize.Left_RatioWidth(size.x) + mstDrawDatas[i].pos.x;
        mstDrawDatas[i].extPos.y = ResourceManager::mstDisplaySize.Left_RatioWidth(size.y) + mstDrawDatas[i].pos.y;
        mstDrawDatas[i].angle = angle.z;
		break;

	case DRAW_GRAPH_TYPE::ROTA_CENTER:// centerPosとextRateを設定は外部でやる
	case DRAW_GRAPH_TYPE::ROTA_EXTEND_XY:// centerPosとextRateを設定は外部でやる
        mstDrawDatas[i].pos.x = ResourceManager::mstDisplaySize.Left_RatioWidth(pos.x);
        mstDrawDatas[i].pos.y = ResourceManager::mstDisplaySize.Left_RatioWidth(pos.y);
        mstDrawDatas[i].angle = angle.z;
		break;

	case DRAW_GRAPH_TYPE::RECT:
        mstDrawDatas[i].pos.x = ResourceManager::mstDisplaySize.Left_RatioWidth(pos.x);
        mstDrawDatas[i].pos.y = ResourceManager::mstDisplaySize.Left_RatioWidth(pos.y);
		break;

	case DRAW_GRAPH_TYPE::SIZE:
        mstDrawDatas[i].pos.x += ResourceManager::mstDisplaySize.Left_RatioWidth(pos.x - mvPrePosition.x);
        mstDrawDatas[i].pos.y += ResourceManager::mstDisplaySize.Left_RatioWidth(pos.y - mvPrePosition.y);
        mstDrawDatas[i].size.x += ResourceManager::mstDisplaySize.Left_RatioWidth(size.x - mvPreSize.x);
        mstDrawDatas[i].size.y += ResourceManager::mstDisplaySize.Left_RatioWidth(size.y - mvPreSize.y);
        break;

	case DRAW_GRAPH_TYPE::FREE:
        mstDrawDatas[i].upLeft.x += ResourceManager::mstDisplaySize.Left_RatioWidth(pos.x - mvPrePosition.x);
        mstDrawDatas[i].upLeft.y += ResourceManager::mstDisplaySize.Left_RatioWidth(pos.y - mvPrePosition.y);
        mstDrawDatas[i].upRight.x += ResourceManager::mstDisplaySize.Left_RatioWidth(pos.x - mvPrePosition.x);
        mstDrawDatas[i].upRight.y += ResourceManager::mstDisplaySize.Left_RatioWidth(pos.y - mvPrePosition.y);
        mstDrawDatas[i].downLeft.x += ResourceManager::mstDisplaySize.Left_RatioWidth(pos.x - mvPrePosition.x);
        mstDrawDatas[i].downLeft.y += ResourceManager::mstDisplaySize.Left_RatioWidth(pos.y - mvPrePosition.y);
        mstDrawDatas[i].downRight.x += ResourceManager::mstDisplaySize.Left_RatioWidth(pos.x - mvPrePosition.x);
        mstDrawDatas[i].downRight.y += ResourceManager::mstDisplaySize.Left_RatioWidth(pos.y - mvPrePosition.y);
        break;
        }
    }

    // 前の情報設定
    mvPrePosition = pos;
    mvPreAngle = angle;
    mvPreSize = size;
}