#include <stdlib.h>
#include <vector>

#include "CameraData.h"
#include "ResourceData.h"
#include "Vector2.h"

#include "Master.h"

#include "FSM.h"
#include "ResourceManager.h"
#include "UI_Title.h"
#include "UtilCalc.h"
#include "UtilFactorys.h"

UI_Title::UI_Title()
: UIBase(true, 1)
, mnLineAeraSize(10000.0f)
, mnLineNum(50)
{
}

UI_Title::~UI_Title()
{
}

// UI初期化
void UI_Title::UIInitilize()
{
    std::vector<DRAW_GRAPH_DATA> setDrawDatas;
    setDrawDatas.clear();
    {
        DRAW_GRAPH_DATA drawData;
        drawData.drawType = DRAW_GRAPH_TYPE::SIZE;
        drawData.pos = Vector2_Int(0, 0);
        drawData.size = ResourceManager::mstDisplaySize.LeftUp_FloatRatio(1.0f);
        drawData.handle = Master::mpResourceManager->GetMovieHandle(ResourceManager::msResourceFile + "Movie/TitleBack.mp4");
        drawData.transFlag = TRUE;
        setDrawDatas.push_back(drawData);
    }

    // モデル追加
    AddModelData(setDrawDatas);

    // アニメーション設定
    AnimationSetting(LOAD_ANIMATION_DATA_FACTORY_NUMBER::UI_TITLE);

	// // モデル設定
    // mpUIModelController->AddModel(UtilFactorys::ModelFactory(MODEL_TYPE::MOVIE, "", UtilCalc::VZero, UtilCalc::VZero, UtilCalc::VOne, &setDrawDatas));
	// // アニメション設定
	//  {
	//  	std::vector<std::vector<LoadAnimationData>> setcharacterLoadAnimationData;
	//  	// 読み込み用アニメーションデータ設定
	//  	setcharacterLoadAnimationData.push_back(UtilFactorys::LoadAnimationDataFactory(mpAnimation, LOAD_ANIMATION_DATA_FACTORY_NUMBER::UI_TITLE));
	//  	// アニメーション有限状態マシン設定
	//  	mpAnimation->SetFsm(UtilFactorys::FSMAnimationFactory(mpAnimation, ANIMATION_FACTORY_NUMBER::UI, LOAD_ANIMATION_DATA_FACTORY_NUMBER::UI_TITLE, setcharacterLoadAnimationData));
	//  }
}

// UI終了
void UI_Title::UIFinalize()
{
}

// UI更新
void UI_Title::UIUpdate()
{
}

// UI最終更新
void UI_Title::UILastUpdate()
{
}

// UI描画
void UI_Title::UIDraw()
{

    // VECTOR pos1;
    // VECTOR pos2;

    // SetUseZBufferFlag(true);

    // pos1 = VGet(-mnLineAeraSize / 2.0f, 0.0f, -mnLineAeraSize / 2.0f);
    // pos2 = VGet(-mnLineAeraSize / 2.0f, 0.0f, mnLineAeraSize / 2.0f);
    // for (int i = 0; i < mnLineNum; i++)
    // {
    //     DrawLine3D(pos1, pos2, GetColor(0, 255, 0));
    //     pos1.x += mnLineAeraSize / mnLineNum;
    //     pos2.x += mnLineAeraSize / mnLineNum;
    // }

    // pos1 = VGet(-mnLineAeraSize / 2.0f, 0.0f, -mnLineAeraSize / 2.0f);
    // pos2 = VGet(mnLineAeraSize / 2.0f, 0.0f, -mnLineAeraSize / 2.0f);
    // for (int i = 0; i < mnLineNum; i++)
    // {
    //     DrawLine3D(pos1, pos2, GetColor(255, 0, 0));
    //     pos1.z += mnLineAeraSize / mnLineNum;
    //     pos2.z += mnLineAeraSize / mnLineNum;
    // }
}


// 選択決定時処理
void UI_Title::DecisionProcess()
{
	mpFsm->Decision(this);
}

// 削除処理
void UI_Title::CloceProcess()
{
	if (mpFsm != nullptr)
	{
		mpFsm->Cloce(this);
	}
}