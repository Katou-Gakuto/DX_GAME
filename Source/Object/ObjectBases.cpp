#include "Master.h"

#include "AnimationBase.h"
#include "AttackManager.h"
#include "FSM.h"
#include "GameManager.h"
#include "ModelsControllerBase.h"
#include "ObjectBases.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "StateBase.h"
#include "UtilCalc.h"

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
, mfSpeed(0.0f)
, mstStatus(status)
, munActionflags(BIT_FLAG<unsigned int>())
, mpFsm(nullptr)
, mnAttackDataNumber(-1)
, mpModelController(nullptr)
, mpAnimation(nullptr)
{
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
	if (!Master::mpTimeManager->GetStopFlag())
	{
		CharacterUpdate();
		if (mpFsm != nullptr)
		{
			mpFsm->Update(this);
		}
		ActionProcess();
	}
}

// 最終更新
void CharacterBase::LastUpdate()
{
	if (!Master::mpTimeManager->GetStopFlag())
	{
		CharacterLastUpdate();
		if (mpFsm != nullptr)
		{
			mpFsm->LastUpdate(this);
		}
		MoveProcess();

		// モデル位置・角度更新
		mpModelController->SetModelPosition(mvPosition);
		mpModelController->SetModelAngle(mvAngle);
		mpModelController->ModelsPositionSetting();
		
		// TODO: アニメーション出来たら
		// アニメーション更新

		// モデルに反映
		mpModelController->UpdateModels();
	}
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
int CharacterBase::StartAttck()
{
	if (mnAttackDataNumber != -1)
	{
		return Master::mpGameManager->GetAttackManager()->StartAttack(mnAttackDataNumber);
	}

	return 0;
}

// 攻撃リセット
void CharacterBase::StopAttack()
{
	if (mnAttackDataNumber != -1)
	{
		Master::mpGameManager->GetAttackManager()->StopAttack(mnAttackDataNumber);
	}
}

// ダメージ
void CharacterBase::Damage(int damage)
{
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
		// 前後
		if (munActionflags.GetFlag((int)CHECK_ACTION_FLAG::FRONT_OR_BACK_ACTION))
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
	mvPosition = VAdd(mvPosition, VScale(mvVec, (float)mstStatus.speed));
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
/*【設定】*/
/*--------*/

// fsm設定
void CharacterBase::SetFSM(FSMCharacter* fsm)
{
	mpFsm = fsm;
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
	CollisionInitilize();
}

// 終了
void BuildingBase::Finalize()
{
	CollisionFinalize();
}

// 更新
void BuildingBase::Update()
{
	if (!Master::mpTimeManager->GetStopFlag())
	{
		CollisionUpdate();
	}
}

// 最終更新
void BuildingBase::LastUpdate()
{
	if (!Master::mpTimeManager->GetStopFlag())
	{
		CollisionLastUpdate();
	}
}

// 描画
void BuildingBase::Draw()
{
	CollisionDraw();
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
, mnAttackRecoilTime(0)
, mnAttackTime(0)
, mvMoveDir(UtilCalc::VZero)
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

// 終了
void AttackBase::Finalize()
{
	AttackFinalize();
}

// 更新
void AttackBase::Update()
{
	if (!Master::mpTimeManager->GetStopFlag())
	{
		AttackUpdate();
	}
}

// 最終更新
void AttackBase::LastUpdate()
{
	if (!Master::mpTimeManager->GetStopFlag())
	{
		AttackLastUpdate();
	}
}

// 描画
void AttackBase::Draw()
{
	AttackDraw();
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
, mnSelectChangeFrame(0)
, mnSetChangeIntervalFrame(30)
, mnUINumber(0)
, mpTimeManager(nullptr)
, mnGraphHandles(nullptr)
, mnGraphCount(0)
, mpFsm(nullptr)
{
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

// 終了
void UIBase::Finalize()
{
	if (mbDeleteDecreaseFlag) {
		DeleteUINumber();
	}

	if (mpFsm != nullptr)
	{
		delete mpFsm;
	}

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
}

// 描画
void UIBase::Draw()
{
	UIDraw();
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
	LeftDecrease();

	RightIncrease();

	DefaultDecision();
}

// 左選択ナンバー減少処理
void UIBase::LeftDecrease()
{
	if (CheckLeft_Frame())
	{
		SelectNumberDecrease();
	}
}

// 右選択ナンバー増加処理
void UIBase::RightIncrease()
{
	if (CheckRight_Frame())
	{
		SelectNumberIncrease();
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
	if ((mpKeyState->GetSpecialKeyDown_Board(KEY_BOARD_SPECIAL::CTRL_LEFT_AND_RIGHT) && mpKeyState->GetWordKeyDown_Board(KEY_BOARD_WORD::Z)) ||
		mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::B, false))
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
	if ((mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::UP, false) ||
		mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::LEFT_STICK_UP, false) ||
		mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::ARROW_UP)) &&
		(CheckFrame(0) || (mnSelectChangeFrame == mpTimeManager->GetFrame() + mnSetChangeIntervalFrame)))
	{
		mnSelectChangeFrame = mpTimeManager->GetFrame() + mnSetChangeIntervalFrame;
		return true;
	}
	return false;
}

// 下が押されていて、なおかつ前回の選択変更から一定フレーム経っているなら「true」を返す
bool UIBase::CheckDown_Frame()
{
	if ((mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::DOWN, false) ||
		mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::LEFT_STICK_DOWN, false) ||
		mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::ARROW_DOWN)) &&
		(CheckFrame(0) || (mnSelectChangeFrame == mpTimeManager->GetFrame() + mnSetChangeIntervalFrame)))
	{
		mnSelectChangeFrame = mpTimeManager->GetFrame() + mnSetChangeIntervalFrame;
		return true;
	}
	return false;
}

// 右が押されていて、なおかつ前回の選択変更から一定フレーム経っているなら「true」を返す
bool UIBase::CheckRight_Frame()
{
	if ((mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::RIGHT, false) ||
		mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::LEFT_STICK_RIGHT, false) ||
		mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::ARROW_RIGHT)) &&
		(CheckFrame(0) || (mnSelectChangeFrame == mpTimeManager->GetFrame() + mnSetChangeIntervalFrame)))
	{
		mnSelectChangeFrame = mpTimeManager->GetFrame() + mnSetChangeIntervalFrame;
		return true;
	}
	return false;
}

// 左が押されていて、なおかつ前回の選択変更から一定フレーム経っているなら「true」を返す
bool UIBase::CheckLeft_Frame()
{
	if ((mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::LEFT, false) ||
		mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::LEFT_STICK_LEFT, false) ||
		mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::ARROW_LEFT)) &&
		(CheckFrame(0) || (mnSelectChangeFrame == mpTimeManager->GetFrame() + mnSetChangeIntervalFrame)))
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