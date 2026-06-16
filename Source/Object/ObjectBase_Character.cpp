#include <map>
#include <vector>

#include "AttackEnum.h"
#include "AnimationData.h"
#include "AttackData.h"
#include "BitFlag.h"
#include "CollisionData.h"
#include "DrawData.h"
#include "Status.h"

#include "DxLib.h"

#include "Master.h"

#include "AnimationBase.h"
#include "AttackManager.h"
#include "DrawManager.h"
#include "FSMAnimation.h"
#include "FSMCharacter.h"
#include "GameManager.h"
#include "ModelsControllerBase.h"
#include "ObjectBase.h"
#include "ObjectBase_Attack.h"
#include "ObjectBase_Character.h"
#include "StopManager.h"


/*------------------------------------------*/
/*          【キャラクターベース】          */
/*------------------------------------------*/

CharacterBase::CharacterBase(bool nextSceneDeleteFlag, STATUS status)
: ObjectBase(OBJECT_TYPE::CHARACTER_BASE, true, nextSceneDeleteFlag)
, mvOldPosition(UtilCalc::VZero)
, mvPosition(UtilCalc::VZero)
, mvMoveDir(UtilCalc::VZero)
, mvVec(UtilCalc::VZero)
, mvAngle(UtilCalc::VZero)
, mstStatus(status)
, munActionflags(BIT_FLAG<unsigned int>())
, mpFsm(nullptr)
, mpModelController(nullptr)
, mpAnimation(nullptr)
, mpAttack(nullptr)
, mfGravity()
{
	mmCharacterAttackDatas.clear();
	mstStateDrawData.clear();
}

CharacterBase::~CharacterBase()
{
}

// 初期化
void CharacterBase::Initilize()
{
	// モデルコントローラー初期化
	mpModelController = new ModelsControllerBase();
	mpModelController->Initilize();

	// アニメーション初期化
	mpAnimation = new AnimationBase();
	mpAnimation->Initilize();
	mpAnimation->SetModelsController(mpModelController);

	// 攻撃初期化
	for (auto attackData : mmCharacterAttackDatas)
	{
		attackData.second.animation->Initilize();

		attackData.second.modelController->Initilize();
	}

	CharacterInitilize();
}

// シーン最終初期化
void CharacterBase::SceneLastInitilize()
{
	// モデル位置・角度設定
	mpModelController->ModelsPositionSetting(mvPosition, mvAngle);

	// アニメーション最終初期化
	mpAnimation->SceneLastInitilize();

	// モデルコントローラー最終初期化
	mpModelController->SceneLastInitilize();

	// 攻撃最終初期化
	for (auto attackData : mmCharacterAttackDatas)
	{
		attackData.second.animation->SceneLastInitilize();

		attackData.second.modelController->SceneLastInitilize();
	}

	CharacterSceneLastInitilize();
}

// 終了
void CharacterBase::Finalize()
{
	CharacterFinalize();

	// モデルコントローラー終了
	mpModelController->Finalize();
	delete mpModelController;
	mpModelController = nullptr;

	// アニメーション終了
	mpAnimation->Finalize();
	delete mpAnimation;// この中でエラー　余計に消してるかも
	mpAnimation = nullptr;

	for (auto& attackDatas : mmCharacterAttackDatas)
	{
		// FIXME: エラーをはくときがある
		attackDatas.second.animation->Finalize();
		delete attackDatas.second.animation;
		attackDatas.second.animation = nullptr;

		attackDatas.second.modelController->Finalize();
		delete attackDatas.second.modelController;
		attackDatas.second.modelController = nullptr;
	}
	mmCharacterAttackDatas.clear();

	if (mpFsm != nullptr)
	{
		mpFsm->Finalize(this);
		delete mpFsm;
	}

	if (mpAttack != nullptr)
	{
		std::vector<AttackBase*> attacks = Master::mpGameManager->GetAttackManager()->GetAllAttack();
		for (int i = 0; i < attacks.size(); i++)
		{
			if ((mpAttack == attacks[i]) && (mpAttack->GetAttackCharacter() == this))
			{
				mpAttack->SetActiveFlag(false);
				break;
			}
		}
	}

	for (int i = 0; i < mstStateDrawData.size(); i++)
	{
		Master::mpResourceManager->ReduceGraphHandle(mstStateDrawData[i].drawGraphData.handle);
	}
}

// 更新
void CharacterBase::Update()
{
	if (Master::mpStopManager->GetStopFlag(STOP_FLAG_TYPE::GAME_OBJECT))
	{
		return;
	}

	CharacterUpdate();
	if (mpFsm != nullptr)
	{
		mpFsm->Update(this);
	}
	ActionProcess();
}

// 最終更新
void CharacterBase::LastUpdate()
{
	 if (Master::mpStopManager->GetStopFlag(STOP_FLAG_TYPE::GAME_OBJECT))
	 {
	 	return;
	 }

	CharacterLastUpdate();
	if (mpFsm != nullptr)
	{
		mpFsm->LastUpdate(this);
	}
	MoveProcess();

	// モデル位置・角度更新
	mpModelController->ModelsPositionSetting(mvPosition, mvAngle);

	// アニメーション更新
	mpAnimation->Update();
	
	// モデルに反映
	mpModelController->UpdateModels();
}

// 描画
void CharacterBase::Draw()
{
	CharacterDraw();
	if (mpFsm != nullptr)
	{
		mpFsm->Draw(this);
	}
	
	// モデル描画
	mpModelController->DrawModels();



	// モデルは描画したいためそれ以外を無効化する
	if (Master::mpStopManager->GetStopFlag(STOP_FLAG_TYPE::GAME_OBJECT_UI_DRAW))
	{
		return;
	}

	for (auto drawData : mstStateDrawData)
	{
		Master::mpDrawManager->DrawData_Draw(&drawData);
	}
}

/*----------------------*/
/*     【独自処理】     */
/*----------------------*/

// 攻撃開始
void CharacterBase::StartAttck(ATTACK_METHOD_TYPE attackMethodType)
{
	if (mmCharacterAttackDatas.find(attackMethodType) != mmCharacterAttackDatas.end())
	{
		mpAttack =  Master::mpGameManager->GetAttackManager()->StartAttack(mmCharacterAttackDatas[attackMethodType].attackDataNumber, attackMethodType);
	}
	// switch (attackMethodType)
	// {
	// case ATTACK_METHOD_TYPE::NORMAL:
	// 	if (mnNormalAttackNumber != -1)
	// 	{
			
	// 	}
	// 	break;

	// case ATTACK_METHOD_TYPE::SPCEIAL:
	// 	if (mnSpecialAttackDataNumber != -1)
	// 	{
	// 		return Master::mpGameManager->GetAttackManager()->StartAttack(mnSpecialAttackDataNumber, attackMethodType);
	// 	}
	// 	break;
	// }

	//return nullptr;
}

// 攻撃リセット
void CharacterBase::StopAttack(ATTACK_METHOD_TYPE attackMethodType)
{
	if (mmCharacterAttackDatas.find(attackMethodType) != mmCharacterAttackDatas.end())
	{
		Master::mpGameManager->GetAttackManager()->StopAttack(mmCharacterAttackDatas[attackMethodType].attackDataNumber);
		mpAttack = nullptr;
	}

	// switch (attackMethodType)
	// {
	// case ATTACK_METHOD_TYPE::NORMAL:
	// 	if (mnNormalAttackNumber != -1)
	// 	{
	// 		return Master::mpGameManager->GetAttackManager()->StopAttack(mnNormalAttackNumber);
	// 	}
	// 	break;

	// case ATTACK_METHOD_TYPE::SPCEIAL:
	// 	if (mnSpecialAttackDataNumber != -1)
	// 	{
	// 		return Master::mpGameManager->GetAttackManager()->StopAttack(mnSpecialAttackDataNumber);
	// 	}
	// 	break;
	// }
}

// 指定アニメーション中であるかを取得
bool CharacterBase::CheckAnimationType(ANIMATION_TYPE animationType)
{
	if (mpAnimation != nullptr)
	{
		return mpAnimation->GetFsm()->CheckNowStateSameType(animationType);
	}

	return false;
}

// ダメージ
void CharacterBase::Damage(int damage)
{
	//printfDx("Hit\n");
	if (mullFlags.GetFlag_BitShift(CHARACTER_OBJECT_BIT_FLAG_NUBER::INVINCIBLE))
	{
		return;
	}

	mstStatus.hp -= damage;
	if (mstStatus.hp <= 0)
	{
		SetHPZero();
	}
}

// 定型行動処理
void CharacterBase::TemplateActionProcess()
{
	/*アングルから前と右の移動量を取得*/
    float denominator = std::fabs(mvMoveDir.x) + std::fabs(mvMoveDir.z);
	VECTOR frontVec = VGet(mvMoveDir.x / denominator, 0.0f, mvMoveDir.z / denominator);

	VECTOR rightVec = VGet(frontVec.z, 0.0f, -frontVec.x);

	/**********************************/

	mvVec = UtilCalc::VZero;
	if (munActionflags.Bool())
	{
		bool moveFlag = false;
		
		// 走る
		if (munActionflags.GetFlag_BitShift((int)CHECK_ACTION_FLAG::DASH))
		{
			mvVec = VAdd(mvVec, frontVec);
			moveFlag = true;
		}
		// 前後
		else if (munActionflags.GetFlag_BitShift((int)CHECK_ACTION_FLAG::FRONT_OR_BACK_ACTION))
		{
			if (munActionflags.GetFlag_BitShift((int)CHECK_ACTION_FLAG::FRONT_ACTION))
			{
				mvVec = VAdd(mvVec, frontVec);
			}
			else
			{
				mvVec = VSub(mvVec, frontVec);
			}
			moveFlag = true;
		}

		// 左右
		if (munActionflags.GetFlag_BitShift((int)CHECK_ACTION_FLAG::LEFT_OR_RIGHT_ACTION))
		{
			if (munActionflags.GetFlag_BitShift((int)CHECK_ACTION_FLAG::RIGHT_ACTION))
			{
				mvVec = VAdd(mvVec, rightVec);
			}
			else
			{
				mvVec = VSub(mvVec, rightVec);
			}
			moveFlag = true;
		}

		// 上下
		if (munActionflags.GetFlag_BitShift((int)CHECK_ACTION_FLAG::UP_OR_DOWN_ACTION))
		{
			if (munActionflags.GetFlag_BitShift((int)CHECK_ACTION_FLAG::UP_ACTION))
			{
				mvVec.y += 1.0f;
			}
			else
			{
				mvVec.y -= 1.0f;
			}
			moveFlag = true;
		}


		if (moveFlag)
		{
			mvVec = VNorm(mvVec);

			mvAngle = UtilCalc::VMoveVecToAngle(mvVec, mvAngle);

			SetAnimation(ANIMATION_TYPE::WALK);
		}

		if (munActionflags.GetFlag_BitShift((int)CHECK_ACTION_FLAG::HP_ZERO))
		{
			DeathProcess();
		}

		munActionflags.Init();
	}
}

// 移動処理
void CharacterBase::MoveProcess()
{
	mvPosition = VAdd(mvPosition, VScale(mvVec, (float)mstStatus.GetNowSpeed()));
	mfGravity -= MAP_GRAVITY;
	mvPosition.y += mfGravity;
	if (0.0f > mvPosition.y)
	{
		mfGravity = 0.0f;
		mvPosition.y = 0.0f;
	}
}

// 死亡処理
void CharacterBase::DeathProcess()
{
	if (mpFsm != nullptr)
	{
		mpFsm->Death(this);
	}

	SetDeleteFlag(true);
}


/*--------*/
/*【取得】*/
/*--------*/

// キャラクターがした攻撃取得
AttackBase* CharacterBase::GetAttack()
{
	return mpAttack;
}


/*--------*/
/*【設定】*/
/*--------*/

// fsm設定
void CharacterBase::SetFSM(FSMCharacter* fsm)
{
	mpFsm = fsm;
}

// アニメーション設定
void CharacterBase::SetAnimation(ANIMATION_TYPE animationType)
{
	mpAnimation->SetAnimationType(animationType);
}