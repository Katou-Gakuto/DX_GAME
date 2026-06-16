#include <vector>

#include "CollisionData.h"
#include "TimeData.h"

#include "DxLib.h"

#include "Master.h"

#include "AnimationBase.h"
#include "ModelsControllerBase.h"
#include "ObjectBase.h"
#include "ObjectBase_Attack.h"
#include "ObjectBase_Character.h"
#include "StopManager.h"

/*--------------------------------------*/
/*          【アタックベース】          */
/*--------------------------------------*/

AttackBase::AttackBase()
: ObjectBase(OBJECT_TYPE::ATTACK_BASE, false, false)
, mvPosition(UtilCalc::VZero)
, mnPower(0)
, mpAttackCharacter(nullptr)
, mnAttackNumber(-1)
//, mnAttackRecoilTime(0)
, mstAttackTime(TIME_DATA())
, mvMoveDir(UtilCalc::VZero)
, mpModelController(nullptr)
, mpAnimation(nullptr)
, mvAngle(UtilCalc::VZero)
{
	mnHiObjID.clear();
}

AttackBase::~AttackBase()
{
}

// 初期化
void AttackBase::Initilize()
{
	AttackInitilize();
}

// シーン最終初期化
void AttackBase::SceneLastInitilize()
{
	AttackSceneLastInitilize();
}

// 終了
void AttackBase::Finalize()
{
	AttackFinalize();
}

// 更新
void AttackBase::Update()
{
	if (Master::mpStopManager->GetStopFlag(STOP_FLAG_TYPE::GAME_OBJECT))
	{
		return;
	}

	AttackUpdate();
}


// 最終更新
void AttackBase::LastUpdate()
{
	if (Master::mpStopManager->GetStopFlag(STOP_FLAG_TYPE::GAME_OBJECT))
	{
		return;
	}

	AttackLastUpdate();

	if (mpModelController != nullptr)
	{
		// モデル位置・角度更新
		mvAngle = UtilCalc::VMoveVecToAngle(mvMoveDir, mvAngle);
		mpModelController->ModelsPositionSetting(mvPosition, mvAngle);

		// アニメーション更新
		mpAnimation->Update();

		// モデルに反映
		mpModelController->UpdateModels();
	}
}

// 描画
void AttackBase::Draw()
{	
	AttackDraw();

	if (mpModelController != nullptr)
	{
		// モデル描画
		mpModelController->DrawModels();
	}
}
