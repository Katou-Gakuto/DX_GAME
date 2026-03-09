#include "ImguiEnum.h"
#include "ImguiData.h"

#include "DxLib.h"

#include "Master.h"

#include "ImguiManager.h"
#include "ModelBase.h"
#include "ModelGraph.h"
#include "ModelsControllerBase.h"
#include "ResourceManager.h"
#include "StopManager.h"
#include "UtilCalc.h"
#include "UtilChange.h"

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
	IMGUI_FLOAT_DATA imguiFloatData;
	imguiFloatData.AddVariable(&mvPosition.x);
	imguiFloatData.AddVariable(&mvPosition.y);
	imguiFloatData.AddVariable(&mvSize.x);
	imguiFloatData.AddVariable(&mvSize.y);
	imguiFloatData.SetLabel("GRAPH_");
	imguiFloatData.SetImguiType(IMGUI_TYPE::DRAG4);
	imguiFloatData.SetMin(-100.0f);
	imguiFloatData.SetMax(100.0f);
    imguiFloatData.SetStep(0.1f);
	imguiFloatData.SetSpeed(0.01f);
    imguiFloatData.SetStepFast(0.1f);

	Master::mpImguiManager->SetFloatImgui(imguiFloatData);
}

// グラフィック終了
void ModelGraph::ModelFinalize()
{
    Master::mpImguiManager->DeleteImguiData("GRAPH_");

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
    if (!mbDrawFlag || Master::mpStopManager->GetStopFlag(STOP_FLAG_TYPE::UI_MODEL))
    {
        return;
    }

    SetDrawBlendMode(mstDrawConfigData.blendMode, mstDrawConfigData.blendParameter);

    for (int i = 0; i < mstDrawDatas.size(); i++)
    {
#if _DEBUG

        IMGUI_INT_DATA imguiIntData;
        imguiIntData.AddVariable(&mstDrawDatas[i].pos.x);
        imguiIntData.AddVariable(&mstDrawDatas[i].pos.y);
        imguiIntData.AddVariable(&mstDrawDatas[i].size.x);
        imguiIntData.AddVariable(&mstDrawDatas[i].size.y);
        imguiIntData.SetLabel("DRAW_GRAPH_" + std::to_string(i));
        imguiIntData.SetImguiType(IMGUI_TYPE::DRAG4);
        imguiIntData.SetFormat("%d");
        imguiIntData.SetMin(-5000);
        imguiIntData.SetMax(5000);
        imguiIntData.SetStep(10);
        imguiIntData.SetSpeed(5.0f);
        imguiIntData.SetStepFast(5.0f);

        Master::mpImguiManager->AddDrawImgui(imguiIntData);
#endif

        ModelDraw_Graph(mstDrawDatas[i]);
    }

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void ModelGraph::SetDrawData(VECTOR pos, VECTOR angle, VECTOR size)
{
    DisplaySize displaySize = ResourceManager::mstDisplaySize;
    for (int i = 0; i < mstDrawDatas.size(); i++)
    {
        switch (mstDrawDatas[i].drawType)
        {
	case DRAW_GRAPH_TYPE::NORMAL:
	case DRAW_GRAPH_TYPE::TURN:
        mstDrawDatas[i].pos.x = displaySize.Left_RatioWidth(pos.x);
        mstDrawDatas[i].pos.y = displaySize.Left_RatioWidth(pos.y);
		break;

	case DRAW_GRAPH_TYPE::EXTEND:
        mstDrawDatas[i].pos.x = displaySize.Left_RatioWidth(pos.x);
        mstDrawDatas[i].pos.y = displaySize.Left_RatioWidth(pos.y);
        mstDrawDatas[i].extPos.x = displaySize.Left_RatioWidth(size.x) + mstDrawDatas[i].pos.x;
        mstDrawDatas[i].extPos.y = displaySize.Left_RatioWidth(size.y) + mstDrawDatas[i].pos.y;
		break;

	case DRAW_GRAPH_TYPE::ROTA:
        mstDrawDatas[i].pos.x = displaySize.Left_RatioWidth(pos.x);
        mstDrawDatas[i].pos.y = displaySize.Left_RatioWidth(pos.y);
        mstDrawDatas[i].extPos.x = displaySize.Left_RatioWidth(size.x) + mstDrawDatas[i].pos.x;
        mstDrawDatas[i].extPos.y = displaySize.Left_RatioWidth(size.y) + mstDrawDatas[i].pos.y;
        mstDrawDatas[i].angle = angle.z;
		break;

	case DRAW_GRAPH_TYPE::ROTA_CENTER:// centerPosとextRateを設定は外部でやる
	case DRAW_GRAPH_TYPE::ROTA_EXTEND_XY:// centerPosとextRateを設定は外部でやる
        mstDrawDatas[i].pos.x = displaySize.Left_RatioWidth(pos.x);
        mstDrawDatas[i].pos.y = displaySize.Left_RatioWidth(pos.y);
        mstDrawDatas[i].angle = angle.z;
		break;

	case DRAW_GRAPH_TYPE::RECT:
        mstDrawDatas[i].pos.x = displaySize.Left_RatioWidth(pos.x);
        mstDrawDatas[i].pos.y = displaySize.Left_RatioWidth(pos.y);
		break;

	case DRAW_GRAPH_TYPE::SIZE:
        mstDrawDatas[i].pos += displaySize.LeftUp_SeparateRatio(UtilChange::ChangeVector_XY(mvPrePosition), UtilChange::ChangeVector_XY(pos));
        mstDrawDatas[i].size += displaySize.LeftUp_SeparateRatio(UtilChange::ChangeVector_XY(mvPreSize), UtilChange::ChangeVector_XY(size));
        break;

	case DRAW_GRAPH_TYPE::FREE:
    {
        Vector2_Int plusPos = displaySize.LeftUp_SeparateRatio(UtilChange::ChangeVector_XY(mvPrePosition), UtilChange::ChangeVector_XY(pos));
        mstDrawDatas[i].upLeft += plusPos;
        mstDrawDatas[i].upRight += plusPos;
        mstDrawDatas[i].downLeft += plusPos;
        mstDrawDatas[i].downRight += plusPos;
    }
        break;
        }
    }

    // 前の情報設定
    mvPrePosition = pos;
    mvPreAngle = angle;
    mvPreSize = size;
}