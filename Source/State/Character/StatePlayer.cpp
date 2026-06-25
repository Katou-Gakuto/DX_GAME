#include <string>

#include "AttackEnum.h"
#include "StateEnum.h"
#include "CameraData.h"

#include "Master.h"

#include "CameraManager.h"
#include "DrawManager.h"
#include "GameManager.h"
#include "KeyState.h"
#include "MapManager.h"
#include "ObjectBases.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "StatePlayer.h"
#include "StopManager.h"
#include "ResourceGraph.h"
#include "ResourceManager.h"
#include "TargetManager.h"
#include "TimeManager.h"
#include "UtilCalc.h"

#include "UtilStateConditionFunction.h"

/*------------------*/
/*     �y���ʁz     */
/*------------------*/

/*------------------------*/
/*�y�v���C���[���ʏ����p�z*/
/*------------------------*/
int PlayerProcess::mnTargetNumber = -1;
PlayerProcess::PlayerProcess()
: mpKeyState(Master::mpKeyState)
, mpCameraManager(Master::mpGameManager->GetCameraManager())
{
	mnTargetNumber = -1;

	// for (int i = 0; i < PLAYER_DRAW_TYPE::PLAYER_DRAW_MAX; i++)
	// {
	// 	Master::mpDrawManager->AddDrawData(&mstPlayerDataDraw[i]);
	// }

	// // HP
	// {
	// 	DRAW_DATA drawData = DRAW_DATA();
	// 	drawData.drawFlag = true;
	// 	drawData.drawGraphData.drawType = DRAW_GRAPH_TYPE::EXTEND;
	// 	drawData.drawGraphData.graphPos = Vector2_Int(0, 0);
	// 	drawData.drawGraphData.graphSize = HP_GRAPH_SIZE;
	// 	drawData.drawGraphData.transFlag = TRUE;

	// 	mstPlayerDataDraw[PLAYER_DRAW_TYPE::HP_FRAME] = drawData;
	// 	mstPlayerDataDraw[PLAYER_DRAW_TYPE::HP_FRAME].drawGraphData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle(ResourceManager::msResourceFile + "2D/HpBack.png");

	// 	drawData.drawGraphData.drawType = DRAW_GRAPH_TYPE::RECT_EXTEND;

	// 	mstPlayerDataDraw[PLAYER_DRAW_TYPE::HP_LEFT] = drawData;
	// 	mstPlayerDataDraw[PLAYER_DRAW_TYPE::HP_LEFT].drawGraphData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle(ResourceManager::msResourceFile + "2D/HpBar.png");

	// 	drawData.drawGraphData.drawType = DRAW_GRAPH_TYPE::EXTEND;

	// 	mstPlayerDataDraw[PLAYER_DRAW_TYPE::HP_RIGHT] = drawData;
	// 	mstPlayerDataDraw[PLAYER_DRAW_TYPE::HP_RIGHT].drawGraphData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle(ResourceManager::msResourceFile + "2D/HpBarRed.png");
	// }
}

// �ړ����ʏ���
void PlayerProcess::SetPlayerMove(CharacterBase* character)
{
	if (mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::W))
	{
		character->SetFrontMove();
	}
	if (mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::S))
	{
		character->SetBackMove();
	}
	if (mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::A))
	{
		character->SetLeftMove();
	}
	if (mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::D))
	{
		character->SetRightMove();
	}


	 //if (mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::Q))
	 //{
	 //	character->SetUpMove();
	 //}
	 //if (mpKeyState->GetWordKey_Board(KEY_BOARD_WORD::E))
	 //{
	 //	character->SetDownMove();
	 //}
}

// �ړ��L�[������Ă���΁utrue�v
bool PlayerProcess::GetPlayerMoveFlag()
{
	return mpKeyState->GetNowWordKeyFlags_Board() & (((unsigned long long)1 << (int)KEY_BOARD_WORD::W) |
													 ((unsigned long long)1 << (int)KEY_BOARD_WORD::A) |
													 ((unsigned long long)1 << (int)KEY_BOARD_WORD::S) |
													 ((unsigned long long)1 << (int)KEY_BOARD_WORD::D));
}

// �U���L�[������Ă���΁utrue�v
bool PlayerProcess::GetPlayerNormalAttackFlag()
{
	return mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::L);
}

// ����U���L�[������Ă���΁utrue�v
bool PlayerProcess::GetPlayerSpceialAttackFlag()
{
	return mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::R);
}

// �W�����v�U���L�[������Ă���΁utrue�v
bool PlayerProcess::GetPlayerJumpAttackFlag()
{
	return mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::RT);
}

// �^�[�Q�b�g�ύX�L�[������Ă���΁utrue�v
bool PlayerProcess::GetTargetChangeFlag()
{
	return mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::Y);
}

// �J�����ɍ��킹�Ĉړ�������ݒ�
void PlayerProcess::SetMoveDir_Camera(CharacterBase* character)
{
	character->SetMoveDir(mpCameraManager->GetCameraData().GetDirection());
}

// �^�[�Q�b�g�ύX
void PlayerProcess::TargetChange()
{
	mnTargetNumber += 1;

	if (Master::mpGameManager->GetTargetManager()->GetTargets(TARGET_TYPE::ENEMY).size() <= mnTargetNumber)
	{
		mnTargetNumber = -1;
	}
}

// �^�[�Q�b�g�ɃJ�����������
void PlayerProcess::SetTargetCamera(CharacterBase* character)
{
	if (Master::mpGameManager->GetTargetManager()->GetTargets(TARGET_TYPE::ENEMY).size() <= mnTargetNumber)
	{
		if (Master::mpGameManager->GetTargetManager()->GetTargets(TARGET_TYPE::ENEMY).size() <= 0)
		{
			mnTargetNumber = -1;
			return;
		}

		mnTargetNumber = Master::mpGameManager->GetTargetManager()->GetTargets(TARGET_TYPE::ENEMY).size() - 1;
	}

	CharacterBase* targetEnemy = Master::mpGameManager->GetTargetManager()->GetTargets(TARGET_TYPE::ENEMY)[mnTargetNumber];

	CameraData cameraData = mpCameraManager->GetCameraData();
	cameraData.angle.y = -UtilCalc::VDegChange(UtilCalc::VMoveVecToAngle(VSub(character->GetPos(), targetEnemy->GetPos()), UtilCalc::VZero, UtilCalc::PiTwo)).y + UtilCalc::RadPi;
	mpCameraManager->SetCameraData(cameraData);
}

// �^�[�Q�b�g�A���̃J��������
void PlayerProcess::TargetCameraProcess(CharacterBase* character)
{
	if (GetTargetChangeFlag())
	{
		TargetChange();
	}

	if (mnTargetNumber != -1)
	{
		SetTargetCamera(character);
	}

	SetMoveDir_Camera(character);
}

// HP�`����ݒ�
void PlayerProcess::HpDrawInfoSetup(CharacterBase* character)
{
	std::vector<DRAW_DATA> drawDatas = character->GetStateDrawData();

	Vector2_Int frameSize = ResourceManager::mstDisplaySize.LeftUp_Ratio(HP_FRAME_SIZE);
	Vector2_Int leftUp = ResourceManager::mstDisplaySize.LeftUp_Ratio(HP_LEFT_UP);
	Vector2_Int rightDown = ResourceManager::mstDisplaySize.LeftUp_Ratio(HP_RIGHT_DOWN);

	drawDatas[PLAYER_DRAW_TYPE::HP_FRAME].drawGraphData.pos = Vector2_Int(leftUp.x - frameSize.x, leftUp.y - frameSize.y);
	drawDatas[PLAYER_DRAW_TYPE::HP_FRAME].drawGraphData.extPos = Vector2_Int(rightDown.x + frameSize.x, rightDown.y + frameSize.y);

	float hpRate = ((float)character->GetStatus()->hp / (float)character->GetStatus()->maxHp);

	drawDatas[PLAYER_DRAW_TYPE::HP_LEFT].drawGraphData.pos = Vector2_Int(leftUp.x, leftUp.y);
	drawDatas[PLAYER_DRAW_TYPE::HP_LEFT].drawGraphData.extPos = Vector2_Int((int)(leftUp.x + ((rightDown.x - leftUp.x) * hpRate)), rightDown.y);
	drawDatas[PLAYER_DRAW_TYPE::HP_LEFT].drawGraphData.graphSize.x = HP_GRAPH_SIZE.x * hpRate;

	drawDatas[PLAYER_DRAW_TYPE::HP_RIGHT].drawGraphData.pos = Vector2_Int(leftUp.x, leftUp.y);
	drawDatas[PLAYER_DRAW_TYPE::HP_RIGHT].drawGraphData.extPos = Vector2_Int(rightDown.x, rightDown.y);

	character->SetStateDrawData(drawDatas);
}

// �`��
void PlayerProcess::PlayerProcessDraw(CharacterBase* character)
{
	// // HACK: ������
	// if ((UtilChange::SceneState(Master::mpGameManager->GetSceneManager()->GetNowScene()) == SCENE::BATTLE) ||
	// 	(UtilChange::SceneState(Master::mpGameManager->GetSceneManager()->GetNowScene()) == SCENE::BATTLE_LOOP))
	// {
	// 	// HACK: �����X�V�̃��f���`��O�Ɉړ�������
	// 	Vector2_Int frameSize = ResourceManager::mstDisplaySize.LeftUp_Ratio(HP_FRAME_SIZE);
	// 	Vector2_Int leftUp = ResourceManager::mstDisplaySize.LeftUp_Ratio(HP_LEFT_UP);
	// 	Vector2_Int rightDown = ResourceManager::mstDisplaySize.LeftUp_Ratio(HP_RIGHT_DOWN);

	// 	mstPlayerDataDraw[PLAYER_DRAW_TYPE::HP_FRAME].drawGraphData.pos = Vector2_Int(leftUp.x - frameSize.x, leftUp.y - frameSize.y);
	// 	mstPlayerDataDraw[PLAYER_DRAW_TYPE::HP_FRAME].drawGraphData.extPos = Vector2_Int(rightDown.x + frameSize.x, rightDown.y + frameSize.y);
	// 	//DrawBox(leftUp.x - frameSize.x, leftUp.y - frameSize.y, rightDown.x + frameSize.x, rightDown.y + frameSize.y, GetColor(0, 0, 0), TRUE);

	// 	float hpRate = ((float)character->GetStatus()->hp / (float)character->GetStatus()->maxHp);

	// 	mstPlayerDataDraw[PLAYER_DRAW_TYPE::HP_LEFT].drawGraphData.pos = Vector2_Int(leftUp.x, leftUp.y);
	// 	mstPlayerDataDraw[PLAYER_DRAW_TYPE::HP_LEFT].drawGraphData.extPos = Vector2_Int((int)(leftUp.x + ((rightDown.x - leftUp.x) * hpRate)), rightDown.y);
	// 	mstPlayerDataDraw[PLAYER_DRAW_TYPE::HP_LEFT].drawGraphData.graphSize.x = HP_GRAPH_SIZE.x * hpRate;

	// 	mstPlayerDataDraw[PLAYER_DRAW_TYPE::HP_RIGHT].drawGraphData.pos = Vector2_Int(leftUp.x, leftUp.y);
	// 	mstPlayerDataDraw[PLAYER_DRAW_TYPE::HP_RIGHT].drawGraphData.extPos = Vector2_Int(rightDown.x, rightDown.y);
	// 	//DrawBox(leftUp.x, leftUp.y, rightDown.x, rightDown.y, GetColor(100, 100, 100), TRUE);
	// 	//DrawBox(leftUp.x, leftUp.y, leftUp.x + ((rightDown.x - leftUp.x) * ((float)character->GetStatus()->hp / (float)character->GetStatus()->maxHp)), rightDown.y, GetColor(255, 255, 255), TRUE);	
	// }

	// VECTOR pos1;
	// VECTOR pos2;

	// SetUseZBufferFlag(true);

	// float size = /*/1000000.0f;//*/ 10000.0f;
	// int number = /*/5000; //*/ 50;
	// pos1 = VGet(-size / 2.0f, 0.0f, -size / 2.0f);
	// pos2 = VGet(-size / 2.0f, 0.0f, size / 2.0f);
	// for (int i = 0; i < number; i++)
	// {
	// 	DrawLine3D(pos1, pos2, GetColor(0, 255, 0));
	// 	pos1.x += size / number;
	// 	pos2.x += size / number;
	// }

	// pos1 = VGet(-size / 2.0f, 0.0f, -size / 2.0f);
	// pos2 = VGet(size / 2.0f, 0.0f, -size / 2.0f);
	// for (int i = 0; i < number; i++)
	// {
	// 	DrawLine3D(pos1, pos2, GetColor(255, 0, 0));
	// 	pos1.z += size / number;
	// 	pos2.z += size / number;
	// }

	//DrawString(500 , 10 , (std::to_string(character->GetPos().x) + "\n" + std::to_string(character->GetPos().y) + "\n" + std::to_string(character->GetPos().z)).c_str(), GetColor(255, 255, 0));

	if (Master::mpStopManager->GetStopFlag(STOP_FLAG_TYPE::UI_MODEL))
	{
		return;
	}
	Master::mpGameManager->GetMapManager()->DrawMiniMap();
}

// ���S
void PlayerProcess::PlayerDeath(CharacterBase* character)
{
	Master::mpGameManager->GetTargetManager()->Delete(character, TARGET_TYPE::PLAYER);
	Master::mpGameManager->GetSceneManager()->SetNextScene(SCENE::GAME_OVER);
}

// LR�L�[�`����ݒ�
void PlayerProcess::L_R_KeyDrawDataSetUp(PLAYER_DRAW_KEY_TYPE keyStatusNumber)
{
	std::string lGraphString;
	std::string rGraphString;
	// �摜�t�@�C���擾
	switch (keyStatusNumber)
	{
	case PLAYER_DRAW_KEY_TYPE::PLAYER_DRAW_KEY_INVALID:
		lGraphString = ResourceManager::msResourceFile + "2D/Button_L_2.png";
		rGraphString = ResourceManager::msResourceFile + "2D/Button_R_2.png";
		break;
		
	case PLAYER_DRAW_KEY_TYPE::PLAYER_DRAW_KEY_VALID:
		lGraphString = ResourceManager::msResourceFile + "2D/Button_L_3.png";
		rGraphString = ResourceManager::msResourceFile + "2D/Button_R_3.png";
		break;
	}

	DRAW_DATA drawData = DRAW_DATA();
	DisplaySize displaySize = ResourceManager::mstDisplaySize;
	
	// ���ʕ`��ݒ�
	{
        drawData.drawFlag = false;
        drawData.drawManagerDrawType = DRAW_MANAGER_DRAW_TYPE::GRAPH;
        drawData.drawGraphData.drawType = DRAW_GRAPH_TYPE::SIZE;
        drawData.drawGraphData.transFlag = TRUE;
        drawData.drawGraphData.pos = displaySize.RightDown_Ratio(Vector2(0.21f, 0.1f));
        drawData.drawGraphData.size = displaySize.LeftUp_Ratio(Vector2(0.105f, 0.07f));
        drawData.drawGraphData.transFlag = TRUE;
	}

	// L�摜�ݒ�
	{
		drawData.drawGraphData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle(lGraphString);
		mstLKeyDraw = drawData;
	}

	// R�摜�ݒ�
	{
        drawData.drawGraphData.pos.x += drawData.drawGraphData.size.x;
		drawData.drawGraphData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle(rGraphString);
		mstRKeyDraw = drawData;
	}

	Master::mpDrawManager->AddDrawData(&mstLKeyDraw);
	Master::mpDrawManager->AddDrawData(&mstRKeyDraw);
}

// �v���C���[���ʏ��� ���̏�Ԃɓ�������
void PlayerProcess::PlayerProcessOnEnter(CharacterBase* character)
{
	mstLKeyDraw.drawFlag = true;
	mstRKeyDraw.drawFlag = true;
}

// �v���C���[���ʏ��� ���̏�Ԃɏo�鎞
void PlayerProcess::PlayerProcessOnExit(CharacterBase* character)
{
	mstLKeyDraw.drawFlag = false;
	mstRKeyDraw.drawFlag = false;
}

/*--------------------------*/
/*     �y��{�X�e�[�g�z     */
/*--------------------------*/

/*--------------------------*/
/*�yIdle�v���C���[�X�e�[�g�z*/
/*--------------------------*/
IdlePlayerState::IdlePlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, void>> stateChangeCriterias)
: PlayerProcess()
, IStateCharacter(PLAYER_STATE::IDLE_PLAYER_STATE, stateChangeCriterias)
{
}

// ���̏�Ԃɓ��������̏���
void IdlePlayerState::OnEnter(CharacterBase* character)
{
	PlayerProcessOnEnter(character);

	if (character->GetStateDrawData().size() <= 0)
	{
		std::vector<DRAW_DATA> drawDatas;
		drawDatas.resize(PLAYER_DRAW_TYPE::PLAYER_DRAW_MAX);
			
		// HP
		{
			DRAW_DATA drawData = DRAW_DATA();
			drawData.drawFlag = true;
			drawData.drawGraphData.drawType = DRAW_GRAPH_TYPE::EXTEND;
			drawData.drawGraphData.graphPos = Vector2_Int(0, 0);
			drawData.drawGraphData.graphSize = HP_GRAPH_SIZE;
			drawData.drawGraphData.transFlag = TRUE;

			drawDatas[PLAYER_DRAW_TYPE::HP_FRAME] = drawData;
			drawDatas[PLAYER_DRAW_TYPE::HP_FRAME].drawGraphData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle(ResourceManager::msResourceFile + "2D/HpBack.png");

			drawData.drawGraphData.drawType = DRAW_GRAPH_TYPE::RECT_EXTEND;

			drawDatas[PLAYER_DRAW_TYPE::HP_LEFT] = drawData;
			drawDatas[PLAYER_DRAW_TYPE::HP_LEFT].drawGraphData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle(ResourceManager::msResourceFile + "2D/HpBar.png");

			drawData.drawGraphData.drawType = DRAW_GRAPH_TYPE::EXTEND;

			drawDatas[PLAYER_DRAW_TYPE::HP_RIGHT] = drawData;
			drawDatas[PLAYER_DRAW_TYPE::HP_RIGHT].drawGraphData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle(ResourceManager::msResourceFile + "2D/HpBarRed.png");
		}

		character->SetStateDrawData(drawDatas);
		
		HpDrawInfoSetup(character);
	}
}

// ���̏�Ԃ�o�鎞�̏���
void IdlePlayerState::OnExit(CharacterBase* character)
{
	PlayerProcessOnExit(character);
}

// �X�e�[�g�ύX�m�F
STATE_TYPE_CHARACTER IdlePlayerState::StateCheck(CharacterBase* character)
{
	if (UtilStateConditionFunction::ShouldTransitionToMove(character))
	{
		return STATE_TYPE_CHARACTER::MOVE_PLAYER_STATE;
	}

	return mStateNumber;
}

// �X�V
void IdlePlayerState::Update(CharacterBase* character)
{
	if (GetTargetChangeFlag())
	{
		TargetChange();
	}

	if (mnTargetNumber != -1)
	{
		SetTargetCamera(character);
	}

#if _DEBUG || true
	if (mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::LEFT_STICK_PUSH))
	{
		CharacterBase* characterWorkObject = dynamic_cast<CharacterBase*>(Master::mpGameManager->GetObjectManager()->GetTypeObject(OBJECT_TYPE::CHARACTER_BASE));
		do
		{
			if (!characterWorkObject->IsDeleteFlag() && characterWorkObject->IsActiveFlag() && (character != characterWorkObject))
			{
				characterWorkObject->Damage(10000);
			}
			characterWorkObject = dynamic_cast<CharacterBase*>(characterWorkObject->GetNextObject(false));
		} while (characterWorkObject != nullptr);
	}
#endif
}

// �ŏI�X�V
void IdlePlayerState::LastUpdate(CharacterBase* character)
{
	HpDrawInfoSetup(character);
}

// �`��
void IdlePlayerState::Draw(CharacterBase* character)
{
	PlayerProcessDraw(character);
}

// ���S
void IdlePlayerState::Death(CharacterBase* character)
{
	PlayerDeath(character);
}

/*--------------------------*/
/*�y�ړ��v���C���[�X�e�[�g�z*/
/*--------------------------*/
MovePlayerState::MovePlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, void>> stateChangeCriterias)
: PlayerProcess()
, IStateCharacter(PLAYER_STATE::MOVE_PLAYER_STATE, stateChangeCriterias)
{
}

// ���̏�Ԃɓ��������̏���
void MovePlayerState::OnEnter(CharacterBase* character)
{
	PlayerProcessOnEnter(character);
}

// ���̏�Ԃ�o�鎞�̏���
void MovePlayerState::OnExit(CharacterBase* character)
{
	PlayerProcessOnExit(character);
}

// �X�e�[�g�ύX�m�F
STATE_TYPE_CHARACTER MovePlayerState::StateCheck(CharacterBase* character)
{
	if (UtilStateConditionFunction::ShouldTransitionToIdle(character))
	{
		return STATE_TYPE_CHARACTER::IDLE_PLAYER_STATE;
	}

	return mStateNumber;
}

// �X�V
void MovePlayerState::Update(CharacterBase* character)
{
	TargetCameraProcess(character);

	SetPlayerMove(character);
}

// �ŏI�X�V
void MovePlayerState::LastUpdate(CharacterBase* character)
{
	HpDrawInfoSetup(character);
}

// �`��
void MovePlayerState::Draw(CharacterBase* character)
{
	PlayerProcessDraw(character);
}

// ���S
void MovePlayerState::Death(CharacterBase* character)
{
	PlayerDeath(character);
}

/*--------------------------*/
/*�y�m�[�}���U���v���C���[�X�e�[�g�z*/
/*--------------------------*/
NormalAttackPlayerState::NormalAttackPlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, void>> stateChangeCriterias)
: PlayerProcess()
, IStateCharacter(PLAYER_STATE::NORMAL_ATTACK_PLAYER_STATE, stateChangeCriterias)
{
	L_R_KeyDrawDataSetUp(PLAYER_DRAW_KEY_TYPE::PLAYER_DRAW_KEY_INVALID);
}

// ���̏�Ԃɓ��������̏���
void NormalAttackPlayerState::OnEnter(CharacterBase* character)
{
	PlayerProcessOnEnter(character);
	character->StartAttck(ATTACK_METHOD_TYPE::NORMAL);
	character->SetAnimation(ANIMATION_TYPE::NORMAL_ATTACK_IN);
}

// ���̏�Ԃ�o�鎞�̏���
void NormalAttackPlayerState::OnExit(CharacterBase* character)
{
	PlayerProcessOnExit(character);
}

// �X�e�[�g�ύX�m�F
STATE_TYPE_CHARACTER NormalAttackPlayerState::StateCheck(CharacterBase* character)
{
	if (UtilStateConditionFunction::IsAttackAnimationFinished(character))
	{
		if (UtilStateConditionFunction::ShouldTransitionToMove(character))
		{
			return STATE_TYPE_CHARACTER::MOVE_PLAYER_STATE;
		}

		return STATE_TYPE_CHARACTER::IDLE_PLAYER_STATE;
	}

	return mStateNumber;
}

// �X�V
void NormalAttackPlayerState::Update(CharacterBase* character)
{
}

// �ŏI�X�V
void NormalAttackPlayerState::LastUpdate(CharacterBase* character)
{
	HpDrawInfoSetup(character);
}

// �`��
void NormalAttackPlayerState::Draw(CharacterBase* character)
{
	PlayerProcessDraw(character);
}

// ���S
void NormalAttackPlayerState::Death(CharacterBase* character)
{
	PlayerDeath(character);
}

/*------------------------------------*/
/*�y�X�y�V�����U���v���C���[�X�e�[�g�z*/
/*------------------------------------*/
SpceialAttackPlayerState::SpceialAttackPlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, void>> stateChangeCriterias)
: PlayerProcess()
, IStateCharacter(PLAYER_STATE::SPCEIAL_ATTACK_PLAYER_STATE, stateChangeCriterias)
{
	L_R_KeyDrawDataSetUp(PLAYER_DRAW_KEY_TYPE::PLAYER_DRAW_KEY_INVALID);
}

// ���̏�Ԃɓ��������̏���
void SpceialAttackPlayerState::OnEnter(CharacterBase* character)
{
	PlayerProcessOnEnter(character);

	character->SetMoveDir(UtilCalc::VAngleToVec(character->GetAngle()));

	character->StartAttck(ATTACK_METHOD_TYPE::SPCEIAL);
	character->SetAnimation(ANIMATION_TYPE::SPCEIAL_ATTACK_IN);
}

// ���̏�Ԃ�o�鎞�̏���
void SpceialAttackPlayerState::OnExit(CharacterBase* character)
{
	PlayerProcessOnExit(character);
}

// �X�e�[�g�ύX�m�F
STATE_TYPE_CHARACTER SpceialAttackPlayerState::StateCheck(CharacterBase* character)
{
	if (UtilStateConditionFunction::IsAttackAnimationFinished(character))
	{
		if (UtilStateConditionFunction::ShouldTransitionToMove(character))
		{
			return STATE_TYPE_CHARACTER::MOVE_PLAYER_STATE;
		}

		return STATE_TYPE_CHARACTER::IDLE_PLAYER_STATE;
	}

	return mStateNumber;
}

// �X�V
void SpceialAttackPlayerState::Update(CharacterBase* character)
{
}

// �ŏI�X�V
void SpceialAttackPlayerState::LastUpdate(CharacterBase* character)
{
	HpDrawInfoSetup(character);
}

// �`��
void SpceialAttackPlayerState::Draw(CharacterBase* character)
{
	PlayerProcessDraw(character);
}

// ���S
void SpceialAttackPlayerState::Death(CharacterBase* character)
{
	PlayerDeath(character);
}

/*--------------------------*/
/*�y���݃v���C���[�X�e�[�g�z*/
/*--------------------------*/
FlinchPlayerState::FlinchPlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, void>> stateChangeCriterias)
: PlayerProcess()
, IStateCharacter(PLAYER_STATE::FLINCH_PLAYER_STATE, stateChangeCriterias)
{
}

// ���̏�Ԃɓ��������̏���
void FlinchPlayerState::OnEnter(CharacterBase* character)
{
	PlayerProcessOnEnter(character);
	//character->SetAnimation(ANIMATION_TYPE::FLINCH);
}

// ���̏�Ԃ�o�鎞�̏���
void FlinchPlayerState::OnExit(CharacterBase* character)
{
	PlayerProcessOnExit(character);
}

// �X�e�[�g�ύX�m�F
STATE_TYPE_CHARACTER FlinchPlayerState::StateCheck(CharacterBase* character)
{
	//if (!character->CheckAnimationType(ANIMATION_TYPE::FLINCH))
	{
		return STATE_TYPE_CHARACTER::IDLE_PLAYER_STATE;
	}

	return mStateNumber;
}

// �X�V
void FlinchPlayerState::Update(CharacterBase* character)
{
}

// �ŏI�X�V
void FlinchPlayerState::LastUpdate(CharacterBase* character)
{
	HpDrawInfoSetup(character);
}

// �`��
void FlinchPlayerState::Draw(CharacterBase* character)
{
	PlayerProcessDraw(character);
}

// ���S
void FlinchPlayerState::Death(CharacterBase* character)
{
	PlayerDeath(character);
}

/*--------------------------*/
/*�y����v���C���[�X�e�[�g�z*/
/*--------------------------*/
AvoidPlayerState::AvoidPlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, void>> stateChangeCriterias)
: PlayerProcess()
, IStateCharacter(PLAYER_STATE::AVOID_PLAYER_STATE, stateChangeCriterias)
{
}

// ���̏�Ԃɓ��������̏���
void AvoidPlayerState::OnEnter(CharacterBase* character)
{
	PlayerProcessOnEnter(character);
	//character->SetAnimation(ANIMATION_TYPE::AVOID);
}

// ���̏�Ԃ�o�鎞�̏���
void AvoidPlayerState::OnExit(CharacterBase* character)
{
	PlayerProcessOnExit(character);
}

// �X�e�[�g�ύX�m�F
STATE_TYPE_CHARACTER AvoidPlayerState::StateCheck(CharacterBase* character)
{
	//if (!character->CheckAnimationType(ANIMATION_TYPE::AVOID))
	{
		return STATE_TYPE_CHARACTER::IDLE_PLAYER_STATE;
	}

	return mStateNumber;
}

// �X�V
void AvoidPlayerState::Update(CharacterBase* character)
{
}

// �ŏI�X�V
void AvoidPlayerState::LastUpdate(CharacterBase* character)
{
	HpDrawInfoSetup(character);
}

// �`��
void AvoidPlayerState::Draw(CharacterBase* character)
{
	PlayerProcessDraw(character);
}

// ���S
void AvoidPlayerState::Death(CharacterBase* character)
{
	PlayerDeath(character);
}

/*--------------------------*/
/*�y�K�[�h�v���C���[�X�e�[�g�z*/
/*--------------------------*/
GuardPlayerState::GuardPlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, void>> stateChangeCriterias)
: PlayerProcess()
 IStateCharacter(PLAYER_STATE::GUARD_PLAYER_STATE, stateChangeCriterias)
{
}

// ���̏�Ԃɓ��������̏���
void GuardPlayerState::OnEnter(CharacterBase* character)
{
	PlayerProcessOnEnter(character);
	//character->SetAnimation(ANIMATION_TYPE::GUARD);
}

// ���̏�Ԃ�o�鎞�̏���
void GuardPlayerState::OnExit(CharacterBase* character)
{
	PlayerProcessOnExit(character);
}

// �X�e�[�g�ύX�m�F
STATE_TYPE_CHARACTER GuardPlayerState::StateCheck(CharacterBase* character)
{
	//if (!character->CheckAnimationType(ANIMATION_TYPE::GUARD))
	{
		return STATE_TYPE_CHARACTER::IDLE_PLAYER_STATE;
	}

	return mStateNumber;
}

// �X�V
void GuardPlayerState::Update(CharacterBase* character)
{
}

// �ŏI�X�V
void GuardPlayerState::LastUpdate(CharacterBase* character)
{
	HpDrawInfoSetup(character);
}

// �`��
void GuardPlayerState::Draw(CharacterBase* character)
{
	PlayerProcessDraw(character);
}

// ���S
void GuardPlayerState::Death(CharacterBase* character)
{
	PlayerDeath(character);
}

/*--------------------------*/
/*�y�|��v���C���[�X�e�[�g�z*/
/*--------------------------*/
FallDownPlayerState::FallDownPlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, void>> stateChangeCriterias)
: PlayerProcess()
, IStateCharacter(PLAYER_STATE::FALL_DOWN_PLAYER_STATE, stateChangeCriterias)
{
}

// ���̏�Ԃɓ��������̏���
void FallDownPlayerState::OnEnter(CharacterBase* character)
{
	PlayerProcessOnEnter(character);
	//character->SetAnimation(ANIMATION_TYPE::DOWN);
}

// ���̏�Ԃ�o�鎞�̏���
void FallDownPlayerState::OnExit(CharacterBase* character)
{
	//PlayerProcessOnExit(character);
}

// �X�e�[�g�ύX�m�F
STATE_TYPE_CHARACTER FallDownPlayerState::StateCheck(CharacterBase* character)
{
	//if (!character->CheckAnimationType(ANIMATION_TYPE::DOWN))
	{
		//return STATE_TYPE_CHARACTER::IDLE_PLAYER_STATE;
	}

	return mStateNumber;
}

// �X�V
void FallDownPlayerState::Update(CharacterBase* character)
{
}

// �ŏI�X�V
void FallDownPlayerState::LastUpdate(CharacterBase* character)
{
	HpDrawInfoSetup(character);
}

// �`��
void FallDownPlayerState::Draw(CharacterBase* character)
{
	PlayerProcessDraw(character);
}

// ���S
void FallDownPlayerState::Death(CharacterBase* character)
{
	//PlayerDeath(character);
}

/*--------------------------------*/
/*�y�W�����v�U���v���C���[�X�e�[�g�z*/
/*--------------------------------*/
JumpAttackPlayerState::JumpAttackPlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, void>> stateChangeCriterias)
: PlayerProcess()
, IStateCharacter(PLAYER_STATE::JUMP_ATTACK_PLAYER_STATE, stateChangeCriterias)
, mfUpDownSpeed(10.0f)
{
}

// ���̏�Ԃɓ��������̏���
void JumpAttackPlayerState::OnEnter(CharacterBase* character)
{
	PlayerProcessOnEnter(character);
	character->StartAttck(ATTACK_METHOD_TYPE::JUMP);
	character->SetAnimation(ANIMATION_TYPE::JUMP_ATTACK_IN);
}

// ���̏�Ԃ�o�鎞�̏���
void JumpAttackPlayerState::OnExit(CharacterBase* character)
{
	PlayerProcessOnExit(character);
	character->SetPos(VGet(character->GetPos().x, 0.0f, character->GetPos().z));
}

// �X�e�[�g�ύX�m�F
STATE_TYPE_CHARACTER JumpAttackPlayerState::StateCheck(CharacterBase* character)
{
	if (UtilStateConditionFunction::IsAttackAnimationFinished(character))
	{
		if (UtilStateConditionFunction::ShouldTransitionToMove(character))
		{
			//return STATE_TYPE_CHARACTER::MOVE_PLAYER_STATE;
		}

		return STATE_TYPE_CHARACTER::IDLE_PLAYER_STATE;
	}

	return mStateNumber;
}

// �X�V
void JumpAttackPlayerState::Update(CharacterBase* character)
{
	// �U����������������
	VECTOR position = character ->GetPos();
	CameraData cameraData = Master::mpGameManager->GetCameraManager()->GetCameraData();
	cameraData.angle.y = -UtilCalc::VDegChange(UtilCalc::VMoveVecToAngle(VSub(position, VAdd(position, UtilCalc::VAngleToVec(character->GetAngle()))), UtilCalc::VZero, UtilCalc::PiTwo)).y + UtilCalc::RadPi;
	cameraData.angle.x = 45.0f;
	Master::mpGameManager->GetCameraManager()->SetCameraData(cameraData);

	SetPlayerMove(character);

    if (character->CheckAnimationType(ANIMATION_TYPE::ATTACK_IN))
	{
		character->SetUpMove();
	}
	else if (character->CheckAnimationType(ANIMATION_TYPE::ATTACK_OUT))
    {
		character->SetDownMove();
    }
    

}

// �ŏI�X�V
void JumpAttackPlayerState::LastUpdate(CharacterBase* character)
{
	HpDrawInfoSetup(character);
}

// �`��
void JumpAttackPlayerState::Draw(CharacterBase* character)
{
	PlayerProcessDraw(character);
}

// ���S
void JumpAttackPlayerState::Death(CharacterBase* character)
{
	PlayerDeath(character);
}

/*----------------------------*/
/*     �y�o�g���X�e�[�g�z     */
/*----------------------------*/

/*--------------------------------*/
/*�yIdle�o�g���v���C���[�X�e�[�g�z*/
/*--------------------------------*/
IdleBattlePlayerState::IdleBattlePlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, void>> stateChangeCriterias)
: IdlePlayerState(stateChangeCriterias)
{
	L_R_KeyDrawDataSetUp(PLAYER_DRAW_KEY_TYPE::PLAYER_DRAW_KEY_VALID);
}

// �X�e�[�g�ύX�m�F
STATE_TYPE_CHARACTER IdleBattlePlayerState::StateCheck(CharacterBase* character)
{
	if (UtilStateConditionFunction::ShouldTransitionToNormalAttack(character))
	{
		return STATE_TYPE_CHARACTER::NORMAL_ATTACK_PLAYER_STATE;
	}

	if (UtilStateConditionFunction::ShouldTransitionToSpecialAttack(character))
	{
		return STATE_TYPE_CHARACTER::SPCEIAL_ATTACK_PLAYER_STATE;
	}

	if (UtilStateConditionFunction::ShouldTransitionToJumpAttack(character))
	{
		return STATE_TYPE_CHARACTER::JUMP_ATTACK_PLAYER_STATE;
	}

	if (UtilStateConditionFunction::ShouldTransitionToMove(character))
	{
		return STATE_TYPE_CHARACTER::MOVE_PLAYER_STATE;
	}

	return mStateNumber;
}

/*--------------------------------*/
/*�y�ړ��o�g���v���C���[�X�e�[�g�z*/
/*--------------------------------*/
MoveBattlePlayerState::MoveBattlePlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, void>> stateChangeCriterias)
: MovePlayerState(stateChangeCriterias)
{
	L_R_KeyDrawDataSetUp(PLAYER_DRAW_KEY_TYPE::PLAYER_DRAW_KEY_VALID);
}

// �X�e�[�g�ύX�m�F
STATE_TYPE_CHARACTER MoveBattlePlayerState::StateCheck(CharacterBase* character)
{
	if (UtilStateConditionFunction::ShouldTransitionToNormalAttack(character))
	{
		return STATE_TYPE_CHARACTER::NORMAL_ATTACK_PLAYER_STATE;
	}

	if (UtilStateConditionFunction::ShouldTransitionToSpecialAttack(character))
	{
		return STATE_TYPE_CHARACTER::SPCEIAL_ATTACK_PLAYER_STATE;
	}

	if (UtilStateConditionFunction::ShouldTransitionToJumpAttack(character))
	{
		return STATE_TYPE_CHARACTER::JUMP_ATTACK_PLAYER_STATE;
	}

	if (UtilStateConditionFunction::ShouldTransitionToIdle(character))
	{
		return STATE_TYPE_CHARACTER::IDLE_PLAYER_STATE;
	}

	return mStateNumber;
}