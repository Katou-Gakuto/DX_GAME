#include "Master.h"

#include "ObjectBase.h"
#include "ObjectBase_Building.h"

#include "StopManager.h"

/*------------------------------------------*/
/*          【ビルディングベース】          */
/*------------------------------------------*/

BuildingBase::BuildingBase(bool nextSceneDeleteFlag)
: ObjectBase(OBJECT_TYPE::BUILDING_BASE, true, nextSceneDeleteFlag)
, mvPosition(UtilCalc::VZero)
{
}
BuildingBase::~BuildingBase()
{
}

// 初期化
void BuildingBase::Initilize()
{
	BuildingInitilize();
}

// シーン最終初期化
void BuildingBase::SceneLastInitilize()
{
	BuildingSceneLastInitilize();
}

// 終了
void BuildingBase::Finalize()
{
	BuildingFinalize();
}

// 更新
void BuildingBase::Update()
{
	if (Master::mpStopManager->GetStopFlag(STOP_FLAG_TYPE::GAME_OBJECT))
	{
		return;
	}

	BuildingUpdate();
}

// 最終更新
void BuildingBase::LastUpdate()
{
	if (Master::mpStopManager->GetStopFlag(STOP_FLAG_TYPE::GAME_OBJECT))
	{
		return;
	}

	BuildingLastUpdate();
}

// 描画
void BuildingBase::Draw()
{
	BuildingDraw();
}