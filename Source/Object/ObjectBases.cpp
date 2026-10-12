#include <map>

#include "AttackEnum.h"
#include "DrawData.h"
#include "ResourceData.h"

#include "Master.h"

#include "Animation.h"
#include "AttackManager.h"
#include "DataManager.h"
#include "DrawManager.h"
#include "FSMAnimation.h"
#include "FSMCharacter.h"
#include "FSMUI.h"
#include "GameManager.h"
#include "ModelBase.h"
#include "ModelsController.h"
#include "ObjectBases.h"
#include "ObjectManager.h"
#include "ResourceGraph.h"
#include "ResourceManager.h"
#include "ResourceMovie.h"
#include "SceneManager.h"
#include "StateBase.h"
#include "StopManager.h"
#include "UtilCalc.h"
#include "UtilFactorys.h"

/*------------------------------------------*/
/*          �y�I�u�W�F�N�g�x�[�X�z          */
/*------------------------------------------*/
// �R���X�g���N�^
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

	mullFlags.Init();

	munID = Master::mpGameManager->GetObjectManager()->Add(this, objectType);

	meObjectScene = (SCENE)Master::mpGameManager->GetSceneManager()->GetFSMScene()->GetCurrentState();
}

// �f�X�g���N�^
ObjectBase::~ObjectBase()
{
}

/*------------------------------------------*/
/*          �y�L�����N�^�[�x�[�X�z          */
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
, mpModelBase(nullptr)
, mpAttack(nullptr)
{
	mmCharacterAttackDatas.clear();
	mstStateDrawData.clear();
}

CharacterBase::~CharacterBase()
{
}

// ������
void CharacterBase::Initilize()
{
	// // ���f��������
	// mpModelBase = new ModelBase();
	// mpModelBase->Initilize();

	// // �A�j���[�V����������
	// mpAnimation = new Animation();
	// mpAnimation->Initilize();
	// mpAnimation->SetModelsController(mpModelBase);

	// // �U��������
	// for (auto attackData : mmCharacterAttackDatas)
	// {
	// 	attackData.second.animation->Initilize();

	// 	attackData.second.->Initilize();
	// }

	CharacterInitilize();
}

// �V�[���ŏI������
void CharacterBase::SceneLastInitilize()
{
	// ���f���ʒu�E�p�x�ݒ�
	// mpModelBase->ModelGameInit(mvPosition, mvAngle, );

	// // �A�j���[�V�����ŏI������
	// mpAnimation->SceneLastInitilize();

	// ���f���ŏI������
	mpModelBase->SceneLastInitilize();

	// �U���ŏI������
	for (auto attackData : mmCharacterAttackDatas)
	{
		// attackData.second.animation->SceneLastInitilize();

		attackData.second.modelBase->SceneLastInitilize();
	}

	CharacterSceneLastInitilize();
}

// �I��
void CharacterBase::Finalize()
{
	CharacterFinalize();

	// ���f���I��
	mpModelBase->Finalize();
	delete mpModelBase;
	mpModelBase = nullptr;

	for (auto& attackDatas : mmCharacterAttackDatas)
	{
		attackDatas.second.modelBase->Finalize();
		delete attackDatas.second.modelBase;
		attackDatas.second.modelBase = nullptr;
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
		Master::mpResourceManager->GetGraphResource()->ReduceResourceHandle(mstStateDrawData[i].drawGraphData.handle);
	}
}

// �X�V
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

// �ŏI�X�V
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

	// �X�V
	mpModelBase->Update(mvPosition, mvAngle);
}

// �`��
void CharacterBase::Draw()
{
	CharacterDraw();
	if (mpFsm != nullptr)
	{
		mpFsm->Draw(this);
	}
	
	// ���f���`��
	mpModelBase->ModelDraw();



	// ���f���͕`�悵�������߂���ȊO�𖳌�������
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
/*     �y�Ǝ������z     */
/*----------------------*/

// �U���J�n
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

// �U�����Z�b�g
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

// �w��A�j���[�V�������ł��邩���擾
bool CharacterBase::CheckAnimationType(ANIMATION_TYPE animationType)
{
	if ((mpModelBase != nullptr) && (mpModelBase->GetAnimation() != nullptr))
	{
		return mpModelBase->GetAnimation()->GetFsm()->CheckNowStateSameType(animationType);
	}

	return false;
}

// �w��A�j���[�V�������[�u���ł��邩���擾
bool CharacterBase::CheckAnimationMoveType(ANIMATION_MOVE_TYPE animationType)
{
	if ((mpModelBase != nullptr) && (mpModelBase->GetAnimation() != nullptr))
	{
		// static_cast<int>(animationType)���P�������������A�j���[�V�����f�[�^�Ɣ�r�������Ǝv��
		return mpModelBase->GetAnimation()->GetFsm()->GetCurrentState() == static_cast<int>(animationType);
	}

	return false;
}

// �_���[�W
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

// ��^�s������
void CharacterBase::TemplateActionProcess()
{
	/*�A���O������O�ƉE�̈ړ��ʂ��擾*/
    float denominator = std::fabs(mvMoveDir.x) + std::fabs(mvMoveDir.z);
	VECTOR frontVec = VGet(mvMoveDir.x / denominator, 0.0f, mvMoveDir.z / denominator);

	VECTOR rightVec = VGet(frontVec.z, 0.0f, -frontVec.x);

	/**********************************/

	mvVec = UtilCalc::VZero;
	if (munActionflags.Bool())
	{
		bool moveFlag = false;
		
		// ����
		if (munActionflags.GetFlag_BitShift((int)CHECK_ACTION_FLAG::DASH))
		{
			mvVec = VAdd(mvVec, frontVec);
			moveFlag = true;
		}
		// �O��
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

		// ���E
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

		// �㉺
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

			SetAnimation(ANIMATION_MOVE_TYPE::WALK);
		}

		if (munActionflags.GetFlag_BitShift((int)CHECK_ACTION_FLAG::HP_ZERO))
		{
			DeathProcess();
		}

		munActionflags.Init();
	}
}

// �ړ�����
void CharacterBase::MoveProcess()
{
	mvPosition = VAdd(mvPosition, VScale(mvVec, (float)mstStatus.GetNowSpeed()));
}

// ���S����
void CharacterBase::DeathProcess()
{
	SetDeleteFlag(true);
}


/*--------*/
/*�y�擾�z*/
/*--------*/

// �L�����N�^�[�������U���擾
AttackBase* CharacterBase::GetAttack()
{
	return mpAttack;
}


/*--------*/
/*�y�ݒ�z*/
/*--------*/

// fsm�ݒ�
void CharacterBase::SetFSM(FSMCharacter* fsm)
{
	mpFsm = fsm;
}

// �A�j���[�V�����ݒ�
void CharacterBase::SetAnimation(ANIMATION_MOVE_TYPE animationType)
{
	if ((mpModelBase != nullptr) &&
		(mpModelBase->GetAnimation() != nullptr))
	{
		mpModelBase->GetAnimation()->NextAnimationMoveSetting(animationType);
	}
}

/*------------------------------------------*/
/*          �y�r���f�B���O�x�[�X�z          */
/*------------------------------------------*/

BuildingBase::BuildingBase(bool nextSceneDeleteFlag)
: ObjectBase(OBJECT_TYPE::BUILDING_BASE, true, nextSceneDeleteFlag)
, mvPosition(UtilCalc::VZero)
{
}
BuildingBase::~BuildingBase()
{
}

// ������
void BuildingBase::Initilize()
{
	BuildingInitilize();
}

// �V�[���ŏI������
void BuildingBase::SceneLastInitilize()
{
	BuildingSceneLastInitilize();
}

// �I��
void BuildingBase::Finalize()
{
	BuildingFinalize();
}

// �X�V
void BuildingBase::Update()
{
	if (Master::mpStopManager->GetStopFlag(STOP_FLAG_TYPE::GAME_OBJECT))
	{
		return;
	}

	BuildingUpdate();
}

// �ŏI�X�V
void BuildingBase::LastUpdate()
{
	if (Master::mpStopManager->GetStopFlag(STOP_FLAG_TYPE::GAME_OBJECT))
	{
		return;
	}

	BuildingLastUpdate();
}

// �`��
void BuildingBase::Draw()
{
	BuildingDraw();
}

/*--------------------------------------*/
/*          �y�A�^�b�N�x�[�X�z          */
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
, mpModelBase(nullptr)
, mvAngle(UtilCalc::VZero)
{
	mnHiObjID.clear();
}

AttackBase::~AttackBase()
{
}

// ������
void AttackBase::Initilize()
{
	// if (mpModelBase != nullptr)
	// {
	// 	mpModelBase->ModelGameInit(mvPosition, mvAngle,);
	// }

	AttackInitilize();
}

// �V�[���ŏI������
void AttackBase::SceneLastInitilize()
{
	AttackSceneLastInitilize();
}

// �I��
void AttackBase::Finalize()
{
	AttackFinalize();
}

// �X�V
void AttackBase::Update()
{
	if (Master::mpStopManager->GetStopFlag(STOP_FLAG_TYPE::GAME_OBJECT))
	{
		return;
	}

	AttackUpdate();
}


// �ŏI�X�V
void AttackBase::LastUpdate()
{
	if (Master::mpStopManager->GetStopFlag(STOP_FLAG_TYPE::GAME_OBJECT))
	{
		return;
	}

	AttackLastUpdate();

	if (mpModelBase != nullptr)
	{

		// ���f���ʒu�E�p�x�X�V
		mvAngle = UtilCalc::VMoveVecToAngle(mvMoveDir, mvAngle);
		mpModelBase->Update(mvPosition, mvAngle);
	}
}

// �`��
void AttackBase::Draw()
{	
	AttackDraw();

	if (mpModelBase != nullptr)
	{
		// ���f���`��
		mpModelBase->ModelDraw();
	}
}

/*--------------------------------*/
/*          �yUI�x�[�X�z          */
/*--------------------------------*/

UIBase::UIBase(bool nextSceneDeleteFlag, int maxMenuSelect, bool timeStopFlag, bool decreaseFlag)
: ObjectBase(OBJECT_TYPE::UI_BASE, true, nextSceneDeleteFlag)
, mpModelsController(nullptr)
, mpKeyState(nullptr)
, mpResourceManager(nullptr)
, mnSelectNumber(0)
, mnPreSelectNumber(0)
, mnSelectMaxNumber(maxMenuSelect)
, mnSelectBoundaryValue(-1)
, mstSelectChangeFrame(0)
, mnSetChangeIntervalFrame(30)
, mnUINumber(0)
, mpTimeManager(nullptr)
, mnGraphHandles(nullptr)
, mnGraphCount(0)
, mnMovieHandles(nullptr)
, mnMovieCount(0)
, mpFsm(nullptr)
, mnUIModelControllerCount(0)
, mstSelectNumberFlag(0)
, mnSelectStepNumber(0)
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

// ������
void UIBase::Initilize()
{
	mstSelectNumberFlag.SetNumber(SELECT_NUMBER_FLAG_ENUM::CHANGE_NORMAL, SELECT_NUMBER_FLAG_ENUM::CHANGE_BIT_ZONE, SELECT_NUMBER_FLAG_ENUM::CHANGE_BIT_MOVING_DISTANCE);

	if (mbTimeStopFlag)
	{
		SetUINumber();
	}

	mpKeyState = Master::mpKeyState;
	mpResourceManager = Master::mpResourceManager;
	mpTimeManager = Master::mpTimeManager;

	UIInitilize();
}

// �V�[���ŏI������
void UIBase::SceneLastInitilize()
{
	UISceneLastInitilize();
}

// �I��
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

	// �摜�폜
	if (mnGraphCount != 0)
	{
		for (int i = 0; i < mnGraphCount; i++)
		{
			mpResourceManager->GetGraphResource()->ReduceResourceHandle(mnGraphHandles[i]);
		}
		free(mnGraphHandles);
	}

	if (mnMovieCount != 0)
	{
		// ����폜
		for (int i = 0; i < mnMovieCount; i++)
		{
			mpResourceManager->GetMovieResource()->ReduceResourceHandle(mnMovieHandles[i]);
		}
		free(mnMovieHandles);
	}

	for (int i = 0; i < mstUIDrawModels.size(); i++)
	{	
		// ���f���I��
		mstUIDrawModels[i].mpUIModel->Finalize();
		delete mstUIDrawModels[i].mpUIModel;
		mstUIDrawModels[i].mpUIModel = nullptr;
	}
	mstUIDrawModels.clear();

	UIFinalize();
}

// �X�V
void UIBase::Update()
{
	if (Master::mpStopManager->GetStopFlag(STOP_FLAG_TYPE::UI_MODEL))
	{
		return;
	}

	mnPreSelectNumber = mnSelectNumber;
	if (mnUINumber == Master::mpGameManager->GetNowUINumber()) {
		UIUpdate();
		if (mpFsm != nullptr)
		{
			mpFsm->Update(this);
		}
	}
}

// �ŏI�X�V
void UIBase::LastUpdate()
{
	if (Master::mpStopManager->GetStopFlag(STOP_FLAG_TYPE::UI_MODEL))
	{
		return;
	}

	if (mnUINumber == Master::mpGameManager->GetNowUINumber()) {
		UILastUpdate();
	}

	for (int i = 0; i < mstUIDrawModels.size(); i++)
	{	
		// �X�V
		mstUIDrawModels[i].mpUIModel->Update(mstUIDrawModels[i].mpUIModel->GetPosition(), mstUIDrawModels[i].mpUIModel->GetAngle());
	}

	mstSelectNumberFlag.Init(SELECT_NUMBER_FLAG_ENUM::INIT_BIT);
}

// �`��
void UIBase::Draw()
{
	UIDraw();
	

	for (int i = 0; i < mstUIDrawModels.size(); i++)
	{
		// ���f���`��
		mstUIDrawModels[i].mpUIModel->ModelDraw();
	}

	if (mpFsm != nullptr)
	{
		mpFsm->Draw(this);
	}
}


/*----------------------*/
/*     �y�Ǝ������z     */
/*----------------------*/

/*--------*/
/*�y�ݒ�z*/
/*--------*/

// fsm�ݒ�
void UIBase::SetFsm(FSMUI* fsm)
{
	mpFsm = fsm;
}

// �摜�n���h���ݒ�
void UIBase::SetGraphHandle(int index, int handle)
{
	if (index < mnGraphCount)
	{
		mnGraphHandles[index] = handle;
	}
}

// �摜�n���h�����ύX
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

// ����n���h���ݒ�
void UIBase::SetMovieHandle(int index, int handle)
{
	if (index < mnMovieCount)
	{
		mnMovieHandles[index] = handle;
	}
}

// �摜�n���h�����ύX
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
// �A�j���[�V�����ݒ�
void UIBase::SetAnimationType(ANIMATION_MOVE_TYPE aniamtionType)
{
	for (int i = 0; i < mstUIDrawModels.size(); i++)
	{
		if ((mstUIDrawModels[i].mpUIModel != nullptr) &&
			(mstUIDrawModels[i].mpUIModel->GetAnimation() != nullptr))
		{
			mstUIDrawModels[i].mpUIModel->GetAnimation()->NextAnimationMoveSetting(aniamtionType);
		}
	}
}

// �n���h�����ύX
void UIBase::SetHandleCount(int count, int *handleCount, int**handle)
{
	if (*handle != nullptr)
	{
		for (int i = 0; i < (*handleCount); i++)
		{
			if ((*handle)[i] != -1)
			{
				Master::mpResourceManager->GetGraphResource()->ReduceResourceHandle((*handle)[i]);
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
/*�y�p���I�u�W�F�N�g�����z*/
/*------------------------*/

// UI�i���o�[�ݒ�
void UIBase::SetUINumber()
{
	mnUINumber = Master::mpGameManager->IncreaseUINumber();
}

// UI�i���o�[�폜
void UIBase::DeleteUINumber()
{
	Master::mpGameManager->DecreaseUINumber();

	// TODO: ������ӂ̏���������
	if (!IsDeleteFlag())
	{
		mnUINumber = Master::mpGameManager->GetNowUINumber();
	}
}

// ���f���ǉ�
void UIBase::AddModelData(std::vector<DRAW_GRAPH_DATA> drawData, ANIMATION_TYPE modelType)
{
    if (mpModelsController == nullptr)
    {
        mpModelsController = new ModelsController();
    }

    mpModelsController->AddModel(UtilFactorys::ModelFactory(modelType, "", UtilCalc::VZero, UtilCalc::VZero, UtilCalc::VOne, &drawData));
}

// �A�j���[�V�����ݒ�
void UIBase::AnimationSetting(LOAD_ANIMATION_DATA_FACTORY_NUMBER ladoAnimationDataFactorynumber, std::vector<int> drawNumber)
{
    UIDrawModel uiDrawModel = UIDrawModel();

	for (int i = 0; i < mpModelsController->GetModelList().size(); i++)
	{
		ModelBase* model = mpModelsController->GetModelList()[i];
		Animation* animation = model->GetAnimation();
		if (animation == nullptr)
		{
			Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::ANIMATION_MISSING_FLAG);
			continue;
		}

		const std::vector<LoadAnimationData> loadAnimationData = UtilFactorys::LoadAnimationDataFactory(ladoAnimationDataFactorynumber);
		animation->SetFsm(UtilFactorys::FSMAnimationFactory(animation, ANIMATION_FACTORY_NUMBER::UI, loadAnimationData));
	}

	// �`�悷��X�e�[�g�ݒ�
	if (drawNumber.size() == 0)
	{
		// TODO: �S�X�e�[�g�̃X�e�[�g�Œǉ����邩���ł��傤�ǂ���������ϐ��Ŏ擾�ł���悤�ɂ���
		for (int i = 0; i < 10; i++)
		{
			uiDrawModel.mnDrawNumber.push_back(i);
		}
	}
	else
	{
		uiDrawModel.mnDrawNumber = drawNumber;
	}

    // mstUIDrawModels�̖�����mpModelsController��ǉ�
    uiDrawModel.mpUIModel = mpModelsController;
    mstUIDrawModels.push_back(uiDrawModel);
	mpModelsController = nullptr;

	// �A�j���[�V�����������Z����
	mnUIModelControllerCount++;
}

/*----------------------*/
/*�y���̓L�[��ޕʏ����z*/
/*----------------------*/

// �}�E�X������������֐������s������
void UIBase::CheckMouse()
{
	if ((mpKeyState->GetMouseFlags() & 0x1ffu) != 0)
	{
		MouseProcess();
	}
}

// �L�[�{�[�h������������֐������s������
void UIBase::CheckKeyboard()
{
	if (mpKeyState->GetDownWordKeyFlags_Board().Bool() || mpKeyState->GetDownSpecialKeyFlags_Board().Bool() || mpKeyState->GetDownNumpadKeyFlags_Board().Bool() ||
		mpKeyState->GetUpWordKeyFlags_Board().Bool() || mpKeyState->GetUpSpecialKeyFlags_Board().Bool() || mpKeyState->GetUpNumpadKeyFlags_Board().Bool())
	{
		KeyboardProcess();
	}
}

// �R���g���[���[������������֐������s������
void UIBase::CheckController()
{
	if (mpKeyState->GetAllNowKeyFlags_Controller(false) != 0)
	{
		ControllerProcess();
	}
}

// �L�[�{�[�h���R���g���[���[������������֐������s������
void UIBase::CheckKeyboard_Controller()
{
	if (mpKeyState->GetDownWordKeyFlags_Board().Bool() || mpKeyState->GetDownSpecialKeyFlags_Board().Bool() || mpKeyState->GetDownNumpadKeyFlags_Board().Bool() ||
		mpKeyState->GetUpWordKeyFlags_Board().Bool() || mpKeyState->GetUpSpecialKeyFlags_Board().Bool() || mpKeyState->GetUpNumpadKeyFlags_Board().Bool() ||
		(mpKeyState->GetAllNowKeyFlags_Controller(false) != 0))
	{
		Keyboard_ControllerProcess();
	}
}

// �}�E�X�������������Ɏ��s����
void UIBase::MouseProcess()
{
	if (mpFsm != nullptr)
	{
		mpFsm->Mouse(this);
	}
}
// �L�[�{�[�h�������������Ɏ��s����
void UIBase::KeyboardProcess()
{
	if (mpFsm != nullptr)
	{
		mpFsm->Keyboard(this);
	}
}
// �R���g���[���[�������������Ɏ��s����
void UIBase::ControllerProcess()
{
	if (mpFsm != nullptr)
	{
		mpFsm->Controller(this);
	}
}
// �L�[�{�[�h���R���g���[���[�������������Ɏ��s����
void UIBase::Keyboard_ControllerProcess()
{
	if (mpFsm != nullptr)
	{
		mpFsm->Keyboard_Controller(this);
	}
}

/*----------------*/
/*�y�e���v���[�g�z*/
/*----------------*/

// �f�t�H���g�I������
void UIBase::DefaultSelectProcess()
{
	DefaultDecrease();

	DefaultIncrease();

	DefaultDecision();
}

// �f�t�H���g�I���i���o�[��������
void UIBase::DefaultDecrease()
{
	if (CheckUp_Frame())
	{
		SelectNumberDecrease();
	}
}

// �f�t�H���g�I���i���o�[��������
void UIBase::DefaultIncrease()
{
	if (CheckDown_Frame())
	{
		SelectNumberIncrease();
	}
}

// ���E�I������
void UIBase::LeftRightSelectProcess()
{
	if (mnSelectBoundaryValue == (-1))
	{
		mnSelectBoundaryValue = 1;
	}

	LeftDecrease();

	RightIncrease();
}

// ���I���i���o�[��������
void UIBase::LeftDecrease()
{
	if (CheckLeft_Frame())
	{
		SelectBoundaryValueDecrease();
	}
}

// �E�I���i���o�[��������
void UIBase::RightIncrease()
{
	if (CheckRight_Frame())
	{
		SelectBoundaryValueIncrease();
	}
}

// �I���i���o�[��������
void UIBase::SelectNumberDecrease()
{
	--mnSelectNumber;
	if ((mnSelectStepNumber * mnSelectBoundaryValue) > mnSelectNumber)
	{
		if (mstSelectNumberFlag.GetNumber(SELECT_NUMBER_FLAG_ENUM::CHANGE_BIT_ZONE, SELECT_NUMBER_FLAG_ENUM::CHANGE_BIT_MOVING_DISTANCE)
			== static_cast<unsigned short>(SELECT_NUMBER_FLAG_ENUM::CHANGE_BOUNDARY_STOP))
		{
			++mnSelectNumber;
			return;	
		}
		--mnSelectStepNumber;
	}

	if (mnSelectNumber < 0)
	{
		mstSelectNumberFlag.SetOrBit((unsigned short)SELECT_NUMBER_FLAG_ENUM::NUMBER_DECREASE_EXCEEDED | (unsigned short)SELECT_NUMBER_FLAG_ENUM::EXCEEDED);

		if (mstSelectNumberFlag.GetNumber(SELECT_NUMBER_FLAG_ENUM::CHANGE_BIT_ZONE, SELECT_NUMBER_FLAG_ENUM::CHANGE_BIT_MOVING_DISTANCE)
			== static_cast<unsigned short>(SELECT_NUMBER_FLAG_ENUM::CHANGE_BOUNDARY_STOP))
		{
			mnSelectNumber = 0;
		}
		else if (mnSelectMaxNumber != 0)
		{
			mnSelectNumber = mnSelectMaxNumber - 1;
			ResetSelectStepNumber();
		}
		else
		{
			mnSelectNumber = 0;
		}
	}
}

// �I���i���o�[��������
void UIBase::SelectNumberIncrease()
{
	++mnSelectNumber;
	if (((mnSelectStepNumber + 1) * mnSelectBoundaryValue) <= mnSelectNumber)
	{
		if (mstSelectNumberFlag.GetNumber(SELECT_NUMBER_FLAG_ENUM::CHANGE_BIT_ZONE, SELECT_NUMBER_FLAG_ENUM::CHANGE_BIT_MOVING_DISTANCE)
			== static_cast<unsigned short>(SELECT_NUMBER_FLAG_ENUM::CHANGE_BOUNDARY_STOP))
		{
			--mnSelectNumber;
			return;	
		}
		++mnSelectStepNumber;
	}
	
	if (mnSelectNumber >= mnSelectMaxNumber)
	{
		mstSelectNumberFlag.SetOrBit((unsigned short)SELECT_NUMBER_FLAG_ENUM::BOUNDARY_VALUE_NUMBER_INCREASE_EXCEEDED | (unsigned short)SELECT_NUMBER_FLAG_ENUM::EXCEEDED);

		if (mstSelectNumberFlag.GetNumber(SELECT_NUMBER_FLAG_ENUM::CHANGE_BIT_ZONE, SELECT_NUMBER_FLAG_ENUM::CHANGE_BIT_MOVING_DISTANCE)
			== static_cast<unsigned short>(SELECT_NUMBER_FLAG_ENUM::CHANGE_BOUNDARY_STOP))
		{
			mnSelectNumber = mnSelectMaxNumber - 1;
		}
		else
		{
			mnSelectNumber = 0;
		}
		ResetSelectStepNumber();
	}
}

// �I���i���o�[���E�l���ׂ�����������
void UIBase::SelectBoundaryValueDecrease()
{
	if (mnSelectBoundaryValue == (-1))
	{
		return;
	}

	mnSelectNumber -= mnSelectBoundaryValue;
	--mnSelectStepNumber;
	if (mnSelectNumber < 0)
	{
		mstSelectNumberFlag.SetOrBit((unsigned short)SELECT_NUMBER_FLAG_ENUM::BOUNDARY_VALUE_NUMBER_DECREASE_EXCEEDED | (unsigned short)SELECT_NUMBER_FLAG_ENUM::EXCEEDED);

		if (mstSelectNumberFlag.GetNumber(SELECT_NUMBER_FLAG_ENUM::CHANGE_BIT_ZONE, SELECT_NUMBER_FLAG_ENUM::CHANGE_BIT_MOVING_DISTANCE)
			== static_cast<unsigned short>(SELECT_NUMBER_FLAG_ENUM::CHANGE_BOUNDARY_STOP))
		{
			mnSelectNumber += mnSelectBoundaryValue;
		}
		else if (mnSelectMaxNumber != 0)
		{
			mnSelectNumber += mnSelectMaxNumber;
		}
		else
		{
			mnSelectNumber = 0;
		}
		ResetSelectStepNumber();
	}
}

// �I���i���o�[���E�l���ׂ�����������
void UIBase::SelectBoundaryValueIncrease()
{
	if (mnSelectBoundaryValue == (-1))
	{
		return;
	}

	mnSelectNumber += mnSelectBoundaryValue;
	++mnSelectStepNumber;
	if (mnSelectNumber >= mnSelectMaxNumber)
	{
		mstSelectNumberFlag.SetOrBit((unsigned short)SELECT_NUMBER_FLAG_ENUM::BOUNDARY_VALUE_NUMBER_INCREASE_EXCEEDED | (unsigned short)SELECT_NUMBER_FLAG_ENUM::EXCEEDED);

		if (mstSelectNumberFlag.GetNumber(SELECT_NUMBER_FLAG_ENUM::CHANGE_BIT_ZONE, SELECT_NUMBER_FLAG_ENUM::CHANGE_BIT_MOVING_DISTANCE)
			== static_cast<unsigned short>(SELECT_NUMBER_FLAG_ENUM::CHANGE_BOUNDARY_STOP))
		{
			mnSelectNumber -= mnSelectBoundaryValue;
		}
		else
		{
			mnSelectNumber -= mnSelectMaxNumber;
		}
		ResetSelectStepNumber();
	}
}

// �f�t�H���g�I�����菈��
void UIBase::DefaultDecision()
{
	if (CheckDecision())
	{
		DecisionProcess();
	}
}

// �f�t�H���g�I���m�F����
void UIBase::DefaultClose()
{
	if (mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::B, true)// TODO: �����C�����ׂ�
		// ||
		// ((mpKeyState->GetSpecialKeyDown_Board(KEY_BOARD_SPECIAL::CTRL_LEFT_AND_RIGHT) || mpKeyState->GetWordKeyDown_Board(KEY_BOARD_WORD::Z)) && 
		// (mpKeyState->GetSpecialKey_Board(KEY_BOARD_SPECIAL::CTRL_LEFT_AND_RIGHT) && mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::Z)))
		)
	{
		CloseProcess();
	}
}

// �f�t�H���g�I������
void UIBase::CloseProcess()
{
	SetDeleteFlag(true);
	if (mpFsm != nullptr)
	{
		mpFsm->Close(this);
	}
}

// �オ������Ă��āA�Ȃ����O��̑I��ύX������t���[���o���Ă���Ȃ�utrue�v��Ԃ�
bool UIBase::CheckUp_Frame()
{
	if (((mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::UP, false) ||
		mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::LEFT_STICK_UP, false) ||
		mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::ARROW_UP)) &&
		(CheckFrame(0) || (mstSelectChangeFrame == mpTimeManager->GetFrame() + mnSetChangeIntervalFrame))) ||
		mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::UP, false) || mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::LEFT_STICK_UP, false) || mpKeyState->GetWordKeyDown_Board(KEY_BOARD_WORD::ARROW_UP))
	{
		mstSelectChangeFrame = mpTimeManager->GetFrame() + mnSetChangeIntervalFrame;
		return true;
	}
	return false;
}

// ����������Ă��āA�Ȃ����O��̑I��ύX������t���[���o���Ă���Ȃ�utrue�v��Ԃ�
bool UIBase::CheckDown_Frame()
{
	if (((mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::DOWN, false) ||
		mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::LEFT_STICK_DOWN, false) ||
		mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::ARROW_DOWN)) &&
		(CheckFrame(0) || (mstSelectChangeFrame == mpTimeManager->GetFrame() + mnSetChangeIntervalFrame))) ||
		mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::DOWN, false) || mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::LEFT_STICK_DOWN, false) || mpKeyState->GetWordKeyDown_Board(KEY_BOARD_WORD::ARROW_DOWN))
	{
		mstSelectChangeFrame = mpTimeManager->GetFrame() + mnSetChangeIntervalFrame;
		return true;
	}
	return false;
}

// �E��������Ă��āA�Ȃ����O��̑I��ύX������t���[���o���Ă���Ȃ�utrue�v��Ԃ�
bool UIBase::CheckRight_Frame()
{
	if (((mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::RIGHT, false) ||
		mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::LEFT_STICK_RIGHT, false) ||
		mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::ARROW_RIGHT)) &&
		(CheckFrame(0) || (mstSelectChangeFrame == mpTimeManager->GetFrame() + mnSetChangeIntervalFrame))) ||
		mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::RIGHT, false) || mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::LEFT_STICK_RIGHT, false) || mpKeyState->GetWordKeyDown_Board(KEY_BOARD_WORD::ARROW_RIGHT))
	{
		mstSelectChangeFrame = mpTimeManager->GetFrame() + mnSetChangeIntervalFrame;
		return true;
	}
	return false;
}

// ����������Ă��āA�Ȃ����O��̑I��ύX������t���[���o���Ă���Ȃ�utrue�v��Ԃ�
bool UIBase::CheckLeft_Frame()
{
	if (((mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::LEFT, false) ||
		mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::LEFT_STICK_LEFT, false) ||
		mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::ARROW_LEFT)) &&
		(CheckFrame(0) || (mstSelectChangeFrame == mpTimeManager->GetFrame() + mnSetChangeIntervalFrame))) ||
		mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::LEFT, false) || mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::LEFT_STICK_LEFT, false) || mpKeyState->GetWordKeyDown_Board(KEY_BOARD_WORD::ARROW_LEFT))
	{
		// TODO: ����������ꏊ�Ɉړ�(���̂�)
		mstSelectChangeFrame = mpTimeManager->GetFrame() + mnSetChangeIntervalFrame;
		return true;
	}
	return false;
}

// A/Enter��������Ă���Ȃ�utrue�v��Ԃ�
bool UIBase::CheckDecision()
{
	return (mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::A, false) || mpKeyState->GetSpecialKeyDown_Board(KEY_BOARD_SPECIAL::ENTER));
}

// �t���[������莞�Ԍo���Ă��邩�ǂ���
bool UIBase::CheckFrame(int frameNumber)
{
	switch (frameNumber)
	{
	case 0:
		return mstSelectChangeFrame < mpTimeManager->GetFrame();
		break;
	}

	return false;
}




#ifdef _DEBUG
#include <cassert>
bool DEBUG_OBJECT_POINT_CHECK(void* p, bool check)
{
	if (p != nullptr)
	{
		// �|�C���^�𐮐��ɕϊ�
		uintptr_t addr = reinterpret_cast<uintptr_t>(p);

		// ���32�r�b�g�����o��
		uint32_t upper = static_cast<uint32_t>(addr >> 32);

		// 0���ǂ����m�F
		if (check)
		{
			assert(upper != 0 && "���32�r�b�g��0�ł�\n");
		}
		if (upper == 0)
		{
			return true;
		}
		return false;
	}

	return false;
}
#endif