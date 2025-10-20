#include "../Header/Master.h"

#include "../Header/GameManager.h"
#include "../Header/ObjectBases.h"
#include "../Header/ObjectManager.h"
#include "../Header/SceneManager.h"
#include "../Header/UtilCalc.h"

/*------------------------------------------*/
/*          【オブジェクトベース】          */
/*------------------------------------------*/
// コンストラクタ
ObjectBase::ObjectBase(OBJECT_TYPE objectType, bool isActiveFlag, bool nextSceneDeleteFlag)
: mnTag(0)
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

	munID = Master::mpGameManager->GetObjectManager()->Add(this, (int)objectType);

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
, mvOldPosition(UtilCalc::VZero())
, mvPosition(UtilCalc::VZero())
, mvVec(UtilCalc::VZero())
, mvAngle(UtilCalc::VZero())
, mstStatus(status)
, munMoveflags(BIT_FLAG<unsigned int>())
, mpAttack(nullptr)
{
}
CharacterBase::~CharacterBase()
{
}

// 初期化
void CharacterBase::Initilize()
{
	CharacterInitilize();
}

// 終了
void CharacterBase::Finalize()
{
	if (mpAttack != nullptr)
	{
		mpAttack->SetDeleteFlag(true);
	}
	CharacterFinalize();
}

// 更新
void CharacterBase::Update()
{
	if (!Master::mpTimeManager->GetStopFlag())
	{
		CharacterUpdate();
	}
}

// 最終更新
void CharacterBase::LastUpdate()
{
	CharacterLastUpdate();
}

// 描画
void CharacterBase::Draw()
{
	CharacterDraw();
}

/*----------------------*/
/*     【独自処理】     */
/*----------------------*/

// 攻撃リセット
void CharacterBase::StopAttack()
{
	mpAttack->SetActiveFlag(false);
}

/*------------------------------------------*/
/*          【ビルディングベース】          */
/*------------------------------------------*/

BuildingBase::BuildingBase(bool nextSceneDeleteFlag)
: ObjectBase(OBJECT_TYPE::BUILDING_BASE, true, nextSceneDeleteFlag)
, mvPosition(UtilCalc::VZero())
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
	CollisionUpdate();
}

// 最終更新
void BuildingBase::LastUpdate()
{
	CollisionLastUpdate();
}

// 描画
void BuildingBase::Draw()
{
	CollisionDraw();
}

/*--------------------------------------*/
/*          【アタックベース】          */
/*--------------------------------------*/

AttackBase::AttackBase(bool nextSceneDeleteFlag, CharacterBase* attackCharacter)
: ObjectBase(OBJECT_TYPE::ATTACK_BASE, false, nextSceneDeleteFlag)
, mvPosition(UtilCalc::VZero())
, mnPower(0)
, mpAttackCharacter(attackCharacter)
{
	mpHiCharacter.clear();
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
	AttackUpdate();
}

// 最終更新
void AttackBase::LastUpdate()
{
	AttackLastUpdate();
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
, mnSetChangeIntervalFrame(15)
, mnUINumber(0)
, mpTimeManager(nullptr)
, mnGraphHandles(nullptr)
, mnGraphCount(0)
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

	UIFinalize();
}

// 更新
void UIBase::Update()
{
	if (mnUINumber == Master::mpGameManager->GetNowUINumber()) {
		UIUpdate();
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
}

/*----------------------*/
/*     【独自処理】     */
/*----------------------*/

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
		--mnSelectNumber;
		if (mnSelectNumber < 0)
		{
			mnSelectNumber = mnSelectMaxNumber - 1;
		}
	}
}

// デフォルト選択ナンバー増加処理
void UIBase::DefaultIncrease()
{
	if (CheckDown_Frame())
	{
		++mnSelectNumber;
		if (mnSelectNumber >= mnSelectMaxNumber)
		{
			mnSelectNumber = 0;
		}
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
		mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::B, false))
	{
		CloceProcess();
	}
}

// デフォルト終了処理
void UIBase::CloceProcess()
{
	SetDeleteFlag(true);
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
		mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::ARROW_DOEN)) &&
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
	return (mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::A, false) || mpKeyState->GetSpecialKeyDown_Board(KEY_BOARD_SPECIAL::ENTER));
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