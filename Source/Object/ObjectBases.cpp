#include <map>

#include "AttackEnum.h"
#include "ResourceData.h"

#include "Master.h"

#include "AnimationBase.h"
#include "AttackManager.h"
#include "DataManager.h"
#include "FSM.h"
#include "GameManager.h"
#include "ModelsControllerBase.h"
#include "ObjectBases.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "StateBase.h"
#include "StopManager.h"
#include "UtilCalc.h"
#include "UtilFactorys.h"

/*------------------------------------------*/
/*          【オブジェクトベース】          */
/*------------------------------------------*/
// コンストラクタ
ObjectBase::ObjectBase(OBJECT_TYPE objectType, bool isActiveFlag, bool nextSceneDeleteFlag)
: mnTag("")
, mnTeam(0)
, mbIsDeleteFlag(false)
, mbIsActiveFlag(isActiveFlag)
, mbNextSceneDeleteFlag(nextSceneDeleteFlag)
, meObjectType(objectType)
{
	mpNextObject = nullptr;
	mpPrevObject = nullptr;
	mpInheritClassNextObject = nullptr;
	mpInheritClassPrevObject = nullptr;

	mllFlags.Init();

	munID = Master::mpGameManager->GetObjectManager()->Add(this, objectType);

	meObjectScene = (SCENE)Master::mpGameManager->GetSceneManager()->GetFSMScene()->GetCurrentState();
}

// デストラクタ
ObjectBase::~ObjectBase()
{
}

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
{
	mmCharacterAttackDatas.clear();
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

	CharacterInitilize();
}

// 最終初期化
void CharacterBase::LastInitilize()
{
	// アニメーション初期化
	mpAnimation->Initilize();

	// モデルコントローラー初期化
	mpModelController->Initilize();


	CharacterLastInitilize();
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
	delete mpAnimation;
	mpAnimation = nullptr;
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
		if (munActionflags.GetFlag((int)CHECK_ACTION_FLAG::DASH))
		{
			mvVec = VAdd(mvVec, frontVec);
			moveFlag = true;
		}
		// 前後
		else if (munActionflags.GetFlag((int)CHECK_ACTION_FLAG::FRONT_OR_BACK_ACTION))
		{
			if (munActionflags.GetFlag((int)CHECK_ACTION_FLAG::FRONT_ACTION))
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
		if (munActionflags.GetFlag((int)CHECK_ACTION_FLAG::LEFT_OR_RIGHT_ACTION))
		{
			if (munActionflags.GetFlag((int)CHECK_ACTION_FLAG::RIGHT_ACTION))
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
		if (munActionflags.GetFlag((int)CHECK_ACTION_FLAG::UP_OR_DOWN_ACTION))
		{
			if (munActionflags.GetFlag((int)CHECK_ACTION_FLAG::UP_ACTION))
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

		if (munActionflags.GetFlag((int)CHECK_ACTION_FLAG::HP_ZERO))
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

// 最終初期化
void BuildingBase::LastInitilize()
{
	BuildingLastInitilize();
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
, mnAttackTime(0)
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

// 最終初期化
void AttackBase::LastInitilize()
{
	AttackLastInitilize();
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

/*--------------------------------*/
/*          【UIベース】          */
/*--------------------------------*/

UIBase::UIBase(bool nextSceneDeleteFlag, int maxMenuSelect, bool timeStopFlag, bool decreaseFlag)
: ObjectBase(OBJECT_TYPE::UI_BASE, true, nextSceneDeleteFlag)
, mpKeyState(nullptr)
, mpResourceManager(nullptr)
, mnSelectNumber(0)
, mnSelectMaxNumber(maxMenuSelect)
, mnSelectBoundaryValue(-1)
, mnSelectChangeFrame(0)
, mnSetChangeIntervalFrame(30)
, mnUINumber(0)
, mpTimeManager(nullptr)
, mnGraphHandles(nullptr)
, mnGraphCount(0)
, mnMovieHandles(nullptr)
, mnMovieCount(0)
, mpFsm(nullptr)
, mnUIModelControllerCount(0)
{
	mmUIPositionData.clear();

	mbTimeStopFlag = timeStopFlag;

	if (mbTimeStopFlag)
	{
		mbDeleteDecreaseFlag = decreaseFlag;
	}
	else
	{
		mbDeleteDecreaseFlag = false;
	}
}

UIBase::~UIBase()
{
}

// 初期化
void UIBase::Initilize()
{
	if (mbTimeStopFlag)
	{
		SetUINumber();
	}

	mpKeyState = Master::mpKeyState;
	mpResourceManager = Master::mpResourceManager;
	mpTimeManager = Master::mpTimeManager;

	UIInitilize();
}

// 最終初期化
void UIBase::LastInitilize()
{
	UILastInitilize();
}

// 終了
void UIBase::Finalize()
{
	if (mbDeleteDecreaseFlag) {
		DeleteUINumber();
	}

	if (mpFsm != nullptr)
	{
		mpFsm->Finalize();
		delete mpFsm;
	}

	// 画像削除
	if (mnGraphCount != 0)
	{
		for (int i = 0; i < mnGraphCount; i++)
		{
			mpResourceManager->ReduceGraphHandle(mnGraphHandles[i]);
		}
		free(mnGraphHandles);
	}

	if (mnMovieCount != 0)
	{
		// 動画削除
		for (int i = 0; i < mnMovieCount; i++)
		{
			mpResourceManager->ReduceGraphHandle(mnMovieHandles[i]);
		}
		free(mnMovieHandles);
	}

	for (int i = 0; i < mstUIDrawModels.size(); i++)
	{	
		// モデルコントローラー終了
		mstUIDrawModels[i].mpUIModelController->Finalize();
		delete mstUIDrawModels[i].mpUIModelController;
		mstUIDrawModels[i].mpUIModelController = nullptr;

		// アニメーション終了
		mstUIDrawModels[i].mpAnimation->Finalize();
		delete mstUIDrawModels[i].mpAnimation;
		mstUIDrawModels[i].mpAnimation = nullptr;
	}
	mstUIDrawModels.clear();

	UIFinalize();
}

// 更新
void UIBase::Update()
{
	if (mnUINumber == Master::mpGameManager->GetNowUINumber()) {
		UIUpdate();
		if (mpFsm != nullptr)
		{
			mpFsm->Update(this);
		}
	}
}

// 最終更新
void UIBase::LastUpdate()
{
	if (mnUINumber == Master::mpGameManager->GetNowUINumber()) {
		UILastUpdate();
	}

	for (int i = 0; i < mstUIDrawModels.size(); i++)
	{	
		// モデル位置・角度更新
		mstUIDrawModels[i].mpUIModelController->ModelsPositionSetting();

		// アニメーション更新
		mstUIDrawModels[i].mpAnimation->Update();
		
		// モデルに反映
		mstUIDrawModels[i].mpUIModelController->UpdateModels();
	}

}

// 描画
void UIBase::Draw()
{
	UIDraw();
	

	for (int i = 0; i < mstUIDrawModels.size(); i++)
	{
		// モデル描画
		mstUIDrawModels[i].mpUIModelController->DrawModels();
	}

	if (mpFsm != nullptr)
	{
		mpFsm->Draw(this);
	}
}


/*----------------------*/
/*     【独自処理】     */
/*----------------------*/

/*--------*/
/*【設定】*/
/*--------*/

// fsm設定
void UIBase::SetFsm(FSMUI* fsm)
{
	mpFsm = fsm;
}

// 画像ハンドル設定
void UIBase::SetGraphHandle(int index, int handle)
{
	if (index < mnGraphCount)
	{
		mnGraphHandles[index] = handle;
	}
}

// 画像ハンドル数変更
void UIBase::SetGraphCount(int count)
{
	// if (mnGraphHandles != nullptr)
	// {
	// 	for (int i = 0; i < mnGraphCount; i++)
	// 	{
	// 		if (mnGraphHandles[i] != -1)
	// 		{
	// 			Master::mpResourceManager->ReduceGraphHandle(mnGraphHandles[i]);
	// 		}
	// 	}

	// 	free(mnGraphHandles);
	// }

	// mnGraphCount = count;

	// mnGraphHandles = (int*)malloc(sizeof(int) * mnGraphCount);

	// for (int i = 0; i < mnGraphCount; i++)
	// {
	// 	mnGraphHandles[i] = -1;
	// }
	SetHandleCount(count, &mnGraphCount, &mnGraphHandles);
}

// 動画ハンドル設定
void UIBase::SetMovieHandle(int index, int handle)
{
	if (index < mnMovieCount)
	{
		mnMovieHandles[index] = handle;
	}
}

// 画像ハンドル数変更
void UIBase::SetMovieCount(int count)
{
	// if (mnGraphHandles != nullptr)
	// {
	// 	for (int i = 0; i < mnGraphCount; i++)
	// 	{
	// 		if (mnGraphHandles[i] != -1)
	// 		{
	// 			Master::mpResourceManager->ReduceGraphHandle(mnGraphHandles[i]);
	// 		}
	// 	}

	// 	free(mnGraphHandles);
	// }

	// mnGraphCount = count;

	// mnGraphHandles = (int*)malloc(sizeof(int) * mnGraphCount);

	// for (int i = 0; i < mnGraphCount; i++)
	// {
	// 	mnGraphHandles[i] = -1;
	// }
	SetHandleCount(count, &mnMovieCount, &mnMovieHandles);
}
// アニメーション設定
void UIBase::SetAnimationType(ANIMATION_TYPE aniamtionType)
{
	for (int i = 0; i < mstUIDrawModels.size(); i++)
	{
		mstUIDrawModels[i].mpAnimation->SetAnimationType(aniamtionType);
	}
}

// ハンドル数変更
void UIBase::SetHandleCount(int count, int *handleCount, int**handle)
{
	if (*handle != nullptr)
	{
		for (int i = 0; i < (*handleCount); i++)
		{
			if ((*handle)[i] != -1)
			{
				Master::mpResourceManager->ReduceGraphHandle((*handle)[i]);
			}
		}

		free((*handle));
	}

	(*handleCount) = count;

	(*handle) = (int*)malloc(sizeof(int) * (*handleCount));

	for (int i = 0; i < (*handleCount); i++)
	{
		(*handle)[i] = -1;
	}
}

/*------------------------*/
/*【継承オブジェクト処理】*/
/*------------------------*/

// UIナンバー設定
void UIBase::SetUINumber()
{
	mnUINumber = Master::mpGameManager->IncreaseUINumber();
}

// UIナンバー削除
void UIBase::DeleteUINumber()
{
	Master::mpGameManager->DecreaseUINumber();

	// TODO: ここら辺の処理見直し
	if (!IsDeleteFlag())
	{
		mnUINumber -= 1;
	}
}

// モデル追加
void UIBase::AddModelData(std::vector<DRAW_GRAPH_DATA> drawData, MODEL_TYPE modelType)
{
	if (mstUIDrawModels.size() <= mnUIModelControllerCount)
	{
		UIDrawModel uiDrawModel = UIDrawModel();

		uiDrawModel.mpUIModelController = new ModelsControllerBase();
		uiDrawModel.mpUIModelController->Initilize();

		uiDrawModel.mpAnimation = new AnimationBase();
		uiDrawModel.mpAnimation->Initilize();
		uiDrawModel.mpAnimation->SetModelsController(uiDrawModel.mpUIModelController);

		uiDrawModel.mnDrawNumber.clear();
		
		mstUIDrawModels.push_back(uiDrawModel);
	}

    mstUIDrawModels[mnUIModelControllerCount].mpUIModelController->AddModel(UtilFactorys::ModelFactory(modelType, "", UtilCalc::VZero, UtilCalc::VZero, UtilCalc::VOne, &drawData));
}

// アニメーション設定
void UIBase::AnimationSetting(LOAD_ANIMATION_DATA_FACTORY_NUMBER ladoAnimationDataFactorynumber, std::vector<int> drawNumber)
{
	std::vector<std::vector<LoadAnimationData>> setcharacterLoadAnimationData;
	for (int i = 0; i < mstUIDrawModels[mnUIModelControllerCount].mpUIModelController->GetModelList().size(); i++)
	{
		// 読み込み用アニメーションデータ設定
		setcharacterLoadAnimationData.push_back(UtilFactorys::LoadAnimationDataFactory(mstUIDrawModels[mnUIModelControllerCount].mpAnimation, ladoAnimationDataFactorynumber));
	}
	// アニメーション有限状態マシン設定
	mstUIDrawModels[mnUIModelControllerCount].mpAnimation->SetFsm(UtilFactorys::FSMAnimationFactory(mstUIDrawModels[mnUIModelControllerCount].mpAnimation, ANIMATION_FACTORY_NUMBER::UI, ladoAnimationDataFactorynumber, setcharacterLoadAnimationData));

	// 描画するステート設定
	if (drawNumber.size() == 0)
	{
		// TODO: 全ステートのステートで追加するから後でちょうどいい数字を変数で取得できるようにする
		for (int i = 0; i < 10; i++)
		{
			mstUIDrawModels[mnUIModelControllerCount].mnDrawNumber.push_back(i);
		}
	}
	else
	{
		mstUIDrawModels[mnUIModelControllerCount].mnDrawNumber = drawNumber;
	}

	// アニメーション数を加算する
	mnUIModelControllerCount++;
}

/*----------------------*/
/*【入力キー種類別処理】*/
/*----------------------*/

// マウスが反応したら関数を実行させる
void UIBase::CheckMouse()
{
	if ((mpKeyState->GetMouseFlags() & 0x1ffu) != 0)
	{
		MouseProcess();
	}
}

// キーボードが反応したら関数を実行させる
void UIBase::CheckKeyboard()
{
	if (mpKeyState->GetDownWordKeyFlags_Board().Bool() || mpKeyState->GetDownSpecialKeyFlags_Board().Bool() || mpKeyState->GetDownNumpadKeyFlags_Board().Bool() ||
		mpKeyState->GetUpWordKeyFlags_Board().Bool() || mpKeyState->GetUpSpecialKeyFlags_Board().Bool() || mpKeyState->GetUpNumpadKeyFlags_Board().Bool())
	{
		KeyboardProcess();
	}
}

// コントローラーが反応したら関数を実行させる
void UIBase::CheckController()
{
	if (mpKeyState->GetAllNowKeyFlags_Controller(false) != 0)
	{
		ControllerProcess();
	}
}

// キーボードかコントローラーが反応したら関数を実行させる
void UIBase::CheckKeyboard_Controller()
{
	if (mpKeyState->GetDownWordKeyFlags_Board().Bool() || mpKeyState->GetDownSpecialKeyFlags_Board().Bool() || mpKeyState->GetDownNumpadKeyFlags_Board().Bool() ||
		mpKeyState->GetUpWordKeyFlags_Board().Bool() || mpKeyState->GetUpSpecialKeyFlags_Board().Bool() || mpKeyState->GetUpNumpadKeyFlags_Board().Bool() ||
		(mpKeyState->GetAllNowKeyFlags_Controller(false) != 0))
	{
		Keyboard_ControllerProcess();
	}
}

// マウスが反応した時に実行する
void UIBase::MouseProcess()
{
	if (mpFsm != nullptr)
	{
		mpFsm->Mouse(this);
	}
}
// キーボードが反応した時に実行する
void UIBase::KeyboardProcess()
{
	if (mpFsm != nullptr)
	{
		mpFsm->Keyboard(this);
	}
}
// コントローラーが反応した時に実行する
void UIBase::ControllerProcess()
{
	if (mpFsm != nullptr)
	{
		mpFsm->Controller(this);
	}
}
// キーボードかコントローラーが反応した時に実行する
void UIBase::Keyboard_ControllerProcess()
{
	if (mpFsm != nullptr)
	{
		mpFsm->Keyboard_Controller(this);
	}
}

/*----------------*/
/*【テンプレート】*/
/*----------------*/

// デフォルト選択処理
void UIBase::DefaultSelectProcess()
{
	DefaultDecrease();

	DefaultIncrease();

	DefaultDecision();
}

// デフォルト選択ナンバー減少処理
void UIBase::DefaultDecrease()
{
	if (CheckUp_Frame())
	{
		SelectNumberDecrease();
	}
}

// デフォルト選択ナンバー増加処理
void UIBase::DefaultIncrease()
{
	if (CheckDown_Frame())
	{
		SelectNumberIncrease();
	}
}

// 左右選択処理
void UIBase::LeftRightSelectProcess()
{
	if (mnSelectBoundaryValue == (-1))
	{
		mnSelectBoundaryValue = 1;
	}

	LeftDecrease();

	RightIncrease();
}

// 左選択ナンバー減少処理
void UIBase::LeftDecrease()
{
	if (CheckLeft_Frame())
	{
		SelectBoundaryValueDecrease();
	}
}

// 右選択ナンバー増加処理
void UIBase::RightIncrease()
{
	if (CheckRight_Frame())
	{
		SelectBoundaryValueIncrease();
	}
}

// 選択ナンバー減少処理
void UIBase::SelectNumberDecrease()
{
	--mnSelectNumber;
	if (mnSelectNumber < 0)
	{
		if (mnSelectMaxNumber != 0)
		{
			mnSelectNumber = mnSelectMaxNumber - 1;
		}
		else
		{
			mnSelectNumber = 0;
		}
	}
}

// 選択ナンバー増加処理
void UIBase::SelectNumberIncrease()
{
	++mnSelectNumber;
	if (mnSelectNumber >= mnSelectMaxNumber)
	{
		mnSelectNumber = 0;
	}
}

// 選択ナンバー境界値を跨いだ減少処理
void UIBase::SelectBoundaryValueDecrease()
{
	if (mnSelectBoundaryValue == (-1))
	{
		return;
	}

	mnSelectNumber -= mnSelectBoundaryValue;
	if (mnSelectNumber < 0)
	{
		if (mnSelectMaxNumber != 0)
		{
			mnSelectNumber += mnSelectMaxNumber;
		}
		else
		{
			mnSelectNumber = 0;
		}
	}
}

// 選択ナンバー境界値を跨いだ増加処理
void UIBase::SelectBoundaryValueIncrease()
{
	if (mnSelectBoundaryValue == (-1))
	{
		return;
	}

	mnSelectNumber += mnSelectBoundaryValue;
	if (mnSelectNumber >= mnSelectMaxNumber)
	{
		mnSelectNumber -= mnSelectMaxNumber;
	}
}

// デフォルト選択決定処理
void UIBase::DefaultDecision()
{
	if (CheckDecision())
	{
		DecisionProcess();
	}
}

// デフォルト終了確認処理
void UIBase::DefaultCloce()
{
	if (mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::B, true)// TODO: ここ修正すべき
		// ||
		// ((mpKeyState->GetSpecialKeyDown_Board(KEY_BOARD_SPECIAL::CTRL_LEFT_AND_RIGHT) || mpKeyState->GetWordKeyDown_Board(KEY_BOARD_WORD::Z)) && 
		// (mpKeyState->GetSpecialKey_Board(KEY_BOARD_SPECIAL::CTRL_LEFT_AND_RIGHT) && mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::Z)))
		)
	{
		CloceProcess();
	}
}

// デフォルト終了処理
void UIBase::CloceProcess()
{
	SetDeleteFlag(true);
	if (mpFsm != nullptr)
	{
		mpFsm->Cloce(this);
	}
}

// 上が押されていて、なおかつ前回の選択変更から一定フレーム経っているなら「true」を返す
bool UIBase::CheckUp_Frame()
{
	if (((mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::UP, false) ||
		mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::LEFT_STICK_UP, false) ||
		mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::ARROW_UP)) &&
		(CheckFrame(0) || (mnSelectChangeFrame == mpTimeManager->GetFrame() + mnSetChangeIntervalFrame))) ||
		mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::UP, false) || mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::LEFT_STICK_UP, false) || mpKeyState->GetWordKeyDown_Board(KEY_BOARD_WORD::ARROW_UP))
	{
		mnSelectChangeFrame = mpTimeManager->GetFrame() + mnSetChangeIntervalFrame;
		return true;
	}
	return false;
}

// 下が押されていて、なおかつ前回の選択変更から一定フレーム経っているなら「true」を返す
bool UIBase::CheckDown_Frame()
{
	if (((mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::DOWN, false) ||
		mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::LEFT_STICK_DOWN, false) ||
		mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::ARROW_DOWN)) &&
		(CheckFrame(0) || (mnSelectChangeFrame == mpTimeManager->GetFrame() + mnSetChangeIntervalFrame))) ||
		mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::DOWN, false) || mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::LEFT_STICK_DOWN, false) || mpKeyState->GetWordKeyDown_Board(KEY_BOARD_WORD::ARROW_DOWN))
	{
		mnSelectChangeFrame = mpTimeManager->GetFrame() + mnSetChangeIntervalFrame;
		return true;
	}
	return false;
}

// 右が押されていて、なおかつ前回の選択変更から一定フレーム経っているなら「true」を返す
bool UIBase::CheckRight_Frame()
{
	if (((mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::RIGHT, false) ||
		mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::LEFT_STICK_RIGHT, false) ||
		mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::ARROW_RIGHT)) &&
		(CheckFrame(0) || (mnSelectChangeFrame == mpTimeManager->GetFrame() + mnSetChangeIntervalFrame))) ||
		mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::RIGHT, false) || mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::LEFT_STICK_RIGHT, false) || mpKeyState->GetWordKeyDown_Board(KEY_BOARD_WORD::ARROW_RIGHT))
	{
		mnSelectChangeFrame = mpTimeManager->GetFrame() + mnSetChangeIntervalFrame;
		return true;
	}
	return false;
}

// 左が押されていて、なおかつ前回の選択変更から一定フレーム経っているなら「true」を返す
bool UIBase::CheckLeft_Frame()
{
	if (((mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::LEFT, false) ||
		mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::LEFT_STICK_LEFT, false) ||
		mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::ARROW_LEFT)) &&
		(CheckFrame(0) || (mnSelectChangeFrame == mpTimeManager->GetFrame() + mnSetChangeIntervalFrame))) ||
		mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::LEFT, false) || mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::LEFT_STICK_LEFT, false) || mpKeyState->GetWordKeyDown_Board(KEY_BOARD_WORD::ARROW_LEFT))
	{
		mnSelectChangeFrame = mpTimeManager->GetFrame() + mnSetChangeIntervalFrame;
		return true;
	}
	return false;
}

// A/Enterが押されているなら「true」を返す
bool UIBase::CheckDecision()
{
	return (mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::A, false) || mpKeyState->GetSpecialKeyDown_Board(KEY_BOARD_SPECIAL::ENTER));
}

// フレームが一定時間経っているかどうか
bool UIBase::CheckFrame(int frameNumber)
{
	switch (frameNumber)
	{
	case 0:
		return mnSelectChangeFrame < mpTimeManager->GetFrame();
		break;
	}

	return false;
}