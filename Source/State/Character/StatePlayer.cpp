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
/*     ・ｽE・ｽy・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾊ】     */
/*------------------*/

/*------------------------*/
/*・ｽE・ｽy・ｽE・ｽv・ｽE・ｽ・ｽE・ｽ・ｽE・ｽC・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ[・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾊ擾ｿｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽp・ｽE・ｽz*/
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

// ・ｽE・ｽﾚ難ｿｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾊ擾ｿｽ・ｽE・ｽ・ｽE・ｽ
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

// ・ｽE・ｽﾚ難ｿｽ・ｽE・ｽL・ｽE・ｽ[・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾄゑｿｽ・ｽE・ｽ・ｽE・ｽﾎ「true・ｽE・ｽv
bool PlayerProcess::GetPlayerMoveFlag()
{
	return mpKeyState->GetNowWordKeyFlags_Board() & (((unsigned long long)1 << (int)KEY_BOARD_WORD::W) |
													 ((unsigned long long)1 << (int)KEY_BOARD_WORD::A) |
													 ((unsigned long long)1 << (int)KEY_BOARD_WORD::S) |
													 ((unsigned long long)1 << (int)KEY_BOARD_WORD::D));
}

// ・ｽE・ｽU・ｽE・ｽ・ｽE・ｽ・ｽE・ｽL・ｽE・ｽ[・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾄゑｿｽ・ｽE・ｽ・ｽE・ｽﾎ「true・ｽE・ｽv
bool PlayerProcess::GetPlayerNormalAttackFlag()
{
	return mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::L);
}

// ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽU・ｽE・ｽ・ｽE・ｽ・ｽE・ｽL・ｽE・ｽ[・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾄゑｿｽ・ｽE・ｽ・ｽE・ｽﾎ「true・ｽE・ｽv
bool PlayerProcess::GetPlayerSpceialAttackFlag()
{
	return mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::R);
}

// ・ｽE・ｽW・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽv・ｽE・ｽU・ｽE・ｽ・ｽE・ｽ・ｽE・ｽL・ｽE・ｽ[・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾄゑｿｽ・ｽE・ｽ・ｽE・ｽﾎ「true・ｽE・ｽv
bool PlayerProcess::GetPlayerJumpAttackFlag()
{
	return mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::RT);
}

// ・ｽE・ｽ^・ｽE・ｽ[・ｽE・ｽQ・ｽE・ｽb・ｽE・ｽg・ｽE・ｽﾏ更・ｽE・ｽL・ｽE・ｽ[・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾄゑｿｽ・ｽE・ｽ・ｽE・ｽﾎ「true・ｽE・ｽv
bool PlayerProcess::GetTargetChangeFlag()
{
	return mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::Y);
}

// ・ｽE・ｽJ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾉ搾ｿｽ・ｽE・ｽ・ｽ・ｽ・ｽ・ｽE・ｽﾄ移難ｿｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾝ抵ｿｽ
void PlayerProcess::SetMoveDir_Camera(CharacterBase* character)
{
	character->SetMoveDir(mpCameraManager->GetCameraData().GetDirection());
}

// ・ｽE・ｽ^・ｽE・ｽ[・ｽE・ｽQ・ｽE・ｽb・ｽE・ｽg・ｽE・ｽﾏ更
void PlayerProcess::TargetChange()
{
	mnTargetNumber += 1;

	if (Master::mpGameManager->GetTargetManager()->GetTargets(TARGET_TYPE::ENEMY).size() <= mnTargetNumber)
	{
		mnTargetNumber = -1;
	}
}

// ・ｽE・ｽ^・ｽE・ｽ[・ｽE・ｽQ・ｽE・ｽb・ｽE・ｽg・ｽE・ｽﾉカ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ
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

// ・ｽE・ｽ^・ｽE・ｽ[・ｽE・ｽQ・ｽE・ｽb・ｽE・ｽg・ｽE・ｽA・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾌカ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ
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

// HP・ｽE・ｽ`・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾝ抵ｿｽ
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

// ・ｽE・ｽ`・ｽE・ｽ・ｽE・ｽ
void PlayerProcess::PlayerProcessDraw(CharacterBase* character)
{
	// // HACK: ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ
	// if ((UtilChange::SceneState(Master::mpGameManager->GetSceneManager()->GetNowScene()) == SCENE::BATTLE) ||
	// 	(UtilChange::SceneState(Master::mpGameManager->GetSceneManager()->GetNowScene()) == SCENE::BATTLE_LOOP))
	// {
	// 	// HACK: ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽX・ｽE・ｽV・ｽE・ｽﾌ・・ｽ・ｽ・ｽE・ｽf・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ`・ｽE・ｽ・ｽE・ｽO・ｽE・ｽﾉ移難ｿｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ
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

// ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽS
void PlayerProcess::PlayerDeath(CharacterBase* character)
{
	Master::mpGameManager->GetTargetManager()->Delete(character, TARGET_TYPE::PLAYER);
	Master::mpGameManager->GetSceneManager()->SetNextScene(SCENE::GAME_OVER);
}

// LR・ｽE・ｽL・ｽE・ｽ[・ｽE・ｽ`・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾝ抵ｿｽ
void PlayerProcess::L_R_KeyDrawDataSetUp(PLAYER_DRAW_KEY_TYPE keyStatusNumber)
{
	std::string lGraphString;
	std::string rGraphString;
	// ・ｽE・ｽ鞫懶ｿｽt・ｽE・ｽ@・ｽE・ｽC・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ謫ｾ
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
	
	// ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾊ描・ｽE・ｽ・ｽE・ｽﾝ抵ｿｽ
	{
        drawData.drawFlag = false;
        drawData.drawManagerDrawType = DRAW_MANAGER_DRAW_TYPE::GRAPH;
        drawData.drawGraphData.drawType = DRAW_GRAPH_TYPE::SIZE;
        drawData.drawGraphData.transFlag = TRUE;
        drawData.drawGraphData.pos = displaySize.RightDown_Ratio(Vector2(0.21f, 0.1f));
        drawData.drawGraphData.size = displaySize.LeftUp_Ratio(Vector2(0.105f, 0.07f));
        drawData.drawGraphData.transFlag = TRUE;
	}

	// L・ｽE・ｽ鞫懶ｿｽﾝ抵ｿｽ
	{
		drawData.drawGraphData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle(lGraphString);
		mstLKeyDraw = drawData;
	}

	// R・ｽE・ｽ鞫懶ｿｽﾝ抵ｿｽ
	{
        drawData.drawGraphData.pos.x += drawData.drawGraphData.size.x;
		drawData.drawGraphData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle(rGraphString);
		mstRKeyDraw = drawData;
	}

	Master::mpDrawManager->AddDrawData(&mstLKeyDraw);
	Master::mpDrawManager->AddDrawData(&mstRKeyDraw);
}

// ・ｽE・ｽv・ｽE・ｽ・ｽE・ｽ・ｽE・ｽC・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ[・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾊ擾ｿｽ・ｽE・ｽ・ｽE・ｽ ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾌ擾ｿｽﾔに難ｿｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ
void PlayerProcess::PlayerProcessOnEnter(CharacterBase* character)
{
	mstLKeyDraw.drawFlag = true;
	mstRKeyDraw.drawFlag = true;
}

// ・ｽE・ｽv・ｽE・ｽ・ｽE・ｽ・ｽE・ｽC・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ[・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾊ擾ｿｽ・ｽE・ｽ・ｽE・ｽ ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾌ擾ｿｽﾔに出・ｽE・ｽ骼・
void PlayerProcess::PlayerProcessOnExit(CharacterBase* character)
{
	mstLKeyDraw.drawFlag = false;
	mstRKeyDraw.drawFlag = false;
}

/*--------------------------*/
/*     ・ｽE・ｽy・ｽE・ｽ・ｽE・ｽ{・ｽE・ｽX・ｽE・ｽe・ｽE・ｽ[・ｽE・ｽg・ｽE・ｽz     */
/*--------------------------*/

/*--------------------------*/
/*・ｽE・ｽyIdle・ｽE・ｽv・ｽE・ｽ・ｽE・ｽ・ｽE・ｽC・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ[・ｽE・ｽX・ｽE・ｽe・ｽE・ｽ[・ｽE・ｽg・ｽE・ｽz*/
/*--------------------------*/
IdlePlayerState::IdlePlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias)
: PlayerProcess()
, IStateCharacter(stateChangeCriterias, STATE_TYPE_CHARACTER::IDLE_PLAYER_STATE, STATE_TYPE_CHARACTER::IDLE_PLAYER_STATE)
{
}

// ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾌ擾ｿｽﾔに難ｿｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾌ擾ｿｽ・ｽE・ｽ・ｽE・ｽ
void IdlePlayerState::OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState)
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

// ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾌ擾ｿｽﾔゑｿｽo・ｽE・ｽ骼橸ｿｽﾌ擾ｿｽ・ｽE・ｽ・ｽE・ｽ
void IdlePlayerState::OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState)
{
	PlayerProcessOnExit(character);
}

// ・ｽE・ｽX・ｽE・ｽe・ｽE・ｽ[・ｽE・ｽg・ｽE・ｽﾏ更・ｽE・ｽm・ｽE・ｽF
STATE_TYPE_CHARACTER IdlePlayerState::StateCheck(CharacterBase* character)
{
	if (UtilStateConditionFunction::ShouldTransitionToMove(character))
	{
		return STATE_TYPE_CHARACTER::MOVE_PLAYER_STATE;
	}

	return mStateNumber;
}

// ・ｽE・ｽX・ｽE・ｽV
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

// ・ｽE・ｽﾅ終・ｽE・ｽX・ｽE・ｽV
void IdlePlayerState::LastUpdate(CharacterBase* character)
{
	HpDrawInfoSetup(character);
}

// ・ｽE・ｽ`・ｽE・ｽ・ｽE・ｽ
void IdlePlayerState::Draw(CharacterBase* character)
{
	PlayerProcessDraw(character);
}

// ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽS
void IdlePlayerState::Death(CharacterBase* character)
{
	PlayerDeath(character);
}

/*--------------------------*/
/*・ｽE・ｽy・ｽE・ｽﾚ難ｿｽ・ｽE・ｽv・ｽE・ｽ・ｽE・ｽ・ｽE・ｽC・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ[・ｽE・ｽX・ｽE・ｽe・ｽE・ｽ[・ｽE・ｽg・ｽE・ｽz*/
/*--------------------------*/
MovePlayerState::MovePlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias)
: PlayerProcess()
, IStateCharacter(stateChangeCriterias, STATE_TYPE_CHARACTER::MOVE_PLAYER_STATE, STATE_TYPE_CHARACTER::MOVE_PLAYER_STATE)
{
}

// ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾌ擾ｿｽﾔに難ｿｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾌ擾ｿｽ・ｽE・ｽ・ｽE・ｽ
void MovePlayerState::OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState)
{
	PlayerProcessOnEnter(character);
}

// ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾌ擾ｿｽﾔゑｿｽo・ｽE・ｽ骼橸ｿｽﾌ擾ｿｽ・ｽE・ｽ・ｽE・ｽ
void MovePlayerState::OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState)
{
	PlayerProcessOnExit(character);
}

// ・ｽE・ｽX・ｽE・ｽe・ｽE・ｽ[・ｽE・ｽg・ｽE・ｽﾏ更・ｽE・ｽm・ｽE・ｽF
STATE_TYPE_CHARACTER MovePlayerState::StateCheck(CharacterBase* character)
{
	if (UtilStateConditionFunction::ShouldTransitionToIdle(character))
	{
		return STATE_TYPE_CHARACTER::IDLE_PLAYER_STATE;
	}

	return mStateNumber;
}

// ・ｽE・ｽX・ｽE・ｽV
void MovePlayerState::Update(CharacterBase* character)
{
	TargetCameraProcess(character);

	SetPlayerMove(character);
}

// ・ｽE・ｽﾅ終・ｽE・ｽX・ｽE・ｽV
void MovePlayerState::LastUpdate(CharacterBase* character)
{
	HpDrawInfoSetup(character);
}

// ・ｽE・ｽ`・ｽE・ｽ・ｽE・ｽ
void MovePlayerState::Draw(CharacterBase* character)
{
	PlayerProcessDraw(character);
}

// ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽS
void MovePlayerState::Death(CharacterBase* character)
{
	PlayerDeath(character);
}

/*--------------------------*/
/*・ｽE・ｽy・ｽE・ｽm・ｽE・ｽ[・ｽE・ｽ}・ｽE・ｽ・ｽE・ｽ・ｽE・ｽU・ｽE・ｽ・ｽE・ｽ・ｽE・ｽv・ｽE・ｽ・ｽE・ｽ・ｽE・ｽC・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ[・ｽE・ｽX・ｽE・ｽe・ｽE・ｽ[・ｽE・ｽg・ｽE・ｽz*/
/*--------------------------*/
NormalAttackPlayerState::NormalAttackPlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias)
: PlayerProcess()
, IStateCharacter(stateChangeCriterias, STATE_TYPE_CHARACTER::NORMAL_ATTACK_PLAYER_STATE, STATE_TYPE_CHARACTER::NORMAL_ATTACK_PLAYER_STATE)
{
	L_R_KeyDrawDataSetUp(PLAYER_DRAW_KEY_TYPE::PLAYER_DRAW_KEY_INVALID);
}

// ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾌ擾ｿｽﾔに難ｿｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾌ擾ｿｽ・ｽE・ｽ・ｽE・ｽ
void NormalAttackPlayerState::OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState)
{
	PlayerProcessOnEnter(character);
	character->StartAttck(ATTACK_METHOD_TYPE::NORMAL);
	character->SetAnimation(ANIMATION_MOVE_TYPE::NORMAL_ATTACK_IN);
}

// ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾌ擾ｿｽﾔゑｿｽo・ｽE・ｽ骼橸ｿｽﾌ擾ｿｽ・ｽE・ｽ・ｽE・ｽ
void NormalAttackPlayerState::OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState)
{
	PlayerProcessOnExit(character);
}

// ・ｽE・ｽX・ｽE・ｽe・ｽE・ｽ[・ｽE・ｽg・ｽE・ｽﾏ更・ｽE・ｽm・ｽE・ｽF
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

// ・ｽE・ｽX・ｽE・ｽV
void NormalAttackPlayerState::Update(CharacterBase* character)
{
}

// ・ｽE・ｽﾅ終・ｽE・ｽX・ｽE・ｽV
void NormalAttackPlayerState::LastUpdate(CharacterBase* character)
{
	HpDrawInfoSetup(character);
}

// ・ｽE・ｽ`・ｽE・ｽ・ｽE・ｽ
void NormalAttackPlayerState::Draw(CharacterBase* character)
{
	PlayerProcessDraw(character);
}

// ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽS
void NormalAttackPlayerState::Death(CharacterBase* character)
{
	PlayerDeath(character);
}

/*------------------------------------*/
/*・ｽE・ｽy・ｽE・ｽX・ｽE・ｽy・ｽE・ｽV・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽU・ｽE・ｽ・ｽE・ｽ・ｽE・ｽv・ｽE・ｽ・ｽE・ｽ・ｽE・ｽC・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ[・ｽE・ｽX・ｽE・ｽe・ｽE・ｽ[・ｽE・ｽg・ｽE・ｽz*/
/*------------------------------------*/
SpceialAttackPlayerState::SpceialAttackPlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias)
: PlayerProcess()
, IStateCharacter(stateChangeCriterias, STATE_TYPE_CHARACTER::SPCEIAL_ATTACK_PLAYER_STATE, STATE_TYPE_CHARACTER::SPCEIAL_ATTACK_PLAYER_STATE)
{
	L_R_KeyDrawDataSetUp(PLAYER_DRAW_KEY_TYPE::PLAYER_DRAW_KEY_INVALID);
}

// ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾌ擾ｿｽﾔに難ｿｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾌ擾ｿｽ・ｽE・ｽ・ｽE・ｽ
void SpceialAttackPlayerState::OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState)
{
	PlayerProcessOnEnter(character);

	character->SetMoveDir(UtilCalc::VAngleToVec(character->GetAngle()));

	character->StartAttck(ATTACK_METHOD_TYPE::SPCEIAL);
	character->SetAnimation(ANIMATION_MOVE_TYPE::SPCEIAL_ATTACK_IN);
}

// ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾌ擾ｿｽﾔゑｿｽo・ｽE・ｽ骼橸ｿｽﾌ擾ｿｽ・ｽE・ｽ・ｽE・ｽ
void SpceialAttackPlayerState::OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState)
{
	PlayerProcessOnExit(character);
}

// ・ｽE・ｽX・ｽE・ｽe・ｽE・ｽ[・ｽE・ｽg・ｽE・ｽﾏ更・ｽE・ｽm・ｽE・ｽF
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

// ・ｽE・ｽX・ｽE・ｽV
void SpceialAttackPlayerState::Update(CharacterBase* character)
{
}

// ・ｽE・ｽﾅ終・ｽE・ｽX・ｽE・ｽV
void SpceialAttackPlayerState::LastUpdate(CharacterBase* character)
{
	HpDrawInfoSetup(character);
}

// ・ｽE・ｽ`・ｽE・ｽ・ｽE・ｽ
void SpceialAttackPlayerState::Draw(CharacterBase* character)
{
	PlayerProcessDraw(character);
}

// ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽS
void SpceialAttackPlayerState::Death(CharacterBase* character)
{
	PlayerDeath(character);
}

/*--------------------------*/
/*・ｽE・ｽy・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾝプ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽC・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ[・ｽE・ｽX・ｽE・ｽe・ｽE・ｽ[・ｽE・ｽg・ｽE・ｽz*/
/*--------------------------*/
FlinchPlayerState::FlinchPlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias)
: PlayerProcess()
, IStateCharacter(stateChangeCriterias, STATE_TYPE_CHARACTER::FLINCH_PLAYER_STATE, STATE_TYPE_CHARACTER::FLINCH_PLAYER_STATE)
{
}

// ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾌ擾ｿｽﾔに難ｿｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾌ擾ｿｽ・ｽE・ｽ・ｽE・ｽ
void FlinchPlayerState::OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState)
{
	PlayerProcessOnEnter(character);
	//character->SetAnimation(ANIMATION_MOVE_TYPE::FLINCH);
}

// ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾌ擾ｿｽﾔゑｿｽo・ｽE・ｽ骼橸ｿｽﾌ擾ｿｽ・ｽE・ｽ・ｽE・ｽ
void FlinchPlayerState::OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState)
{
	PlayerProcessOnExit(character);
}

// ・ｽE・ｽX・ｽE・ｽe・ｽE・ｽ[・ｽE・ｽg・ｽE・ｽﾏ更・ｽE・ｽm・ｽE・ｽF
STATE_TYPE_CHARACTER FlinchPlayerState::StateCheck(CharacterBase* character)
{
	//if (!character->CheckAnimationType(ANIMATION_MOVE_TYPE::FLINCH))
	{
		return STATE_TYPE_CHARACTER::IDLE_PLAYER_STATE;
	}

	return mStateNumber;
}

// ・ｽE・ｽX・ｽE・ｽV
void FlinchPlayerState::Update(CharacterBase* character)
{
}

// ・ｽE・ｽﾅ終・ｽE・ｽX・ｽE・ｽV
void FlinchPlayerState::LastUpdate(CharacterBase* character)
{
	HpDrawInfoSetup(character);
}

// ・ｽE・ｽ`・ｽE・ｽ・ｽE・ｽ
void FlinchPlayerState::Draw(CharacterBase* character)
{
	PlayerProcessDraw(character);
}

// ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽS
void FlinchPlayerState::Death(CharacterBase* character)
{
	PlayerDeath(character);
}

/*--------------------------*/
/*・ｽE・ｽy・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽv・ｽE・ｽ・ｽE・ｽ・ｽE・ｽC・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ[・ｽE・ｽX・ｽE・ｽe・ｽE・ｽ[・ｽE・ｽg・ｽE・ｽz*/
/*--------------------------*/
AvoidPlayerState::AvoidPlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias)
: PlayerProcess()
, IStateCharacter(stateChangeCriterias, STATE_TYPE_CHARACTER::AVOID_PLAYER_STATE, STATE_TYPE_CHARACTER::AVOID_PLAYER_STATE)
{
}

// ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾌ擾ｿｽﾔに難ｿｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾌ擾ｿｽ・ｽE・ｽ・ｽE・ｽ
void AvoidPlayerState::OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState)
{
	PlayerProcessOnEnter(character);
	//character->SetAnimation(ANIMATION_MOVE_TYPE::AVOID);
}

// ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾌ擾ｿｽﾔゑｿｽo・ｽE・ｽ骼橸ｿｽﾌ擾ｿｽ・ｽE・ｽ・ｽE・ｽ
void AvoidPlayerState::OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState)
{
	PlayerProcessOnExit(character);
}

// ・ｽE・ｽX・ｽE・ｽe・ｽE・ｽ[・ｽE・ｽg・ｽE・ｽﾏ更・ｽE・ｽm・ｽE・ｽF
STATE_TYPE_CHARACTER AvoidPlayerState::StateCheck(CharacterBase* character)
{
	//if (!character->CheckAnimationType(ANIMATION_MOVE_TYPE::AVOID))
	{
		return STATE_TYPE_CHARACTER::IDLE_PLAYER_STATE;
	}

	return mStateNumber;
}

// ・ｽE・ｽX・ｽE・ｽV
void AvoidPlayerState::Update(CharacterBase* character)
{
}

// ・ｽE・ｽﾅ終・ｽE・ｽX・ｽE・ｽV
void AvoidPlayerState::LastUpdate(CharacterBase* character)
{
	HpDrawInfoSetup(character);
}

// ・ｽE・ｽ`・ｽE・ｽ・ｽE・ｽ
void AvoidPlayerState::Draw(CharacterBase* character)
{
	PlayerProcessDraw(character);
}

// ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽS
void AvoidPlayerState::Death(CharacterBase* character)
{
	PlayerDeath(character);
}

/*--------------------------*/
/*・ｽE・ｽy・ｽE・ｽK・ｽE・ｽ[・ｽE・ｽh・ｽE・ｽv・ｽE・ｽ・ｽE・ｽ・ｽE・ｽC・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ[・ｽE・ｽX・ｽE・ｽe・ｽE・ｽ[・ｽE・ｽg・ｽE・ｽz*/
/*--------------------------*/
GuardPlayerState::GuardPlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias)
: PlayerProcess()
, IStateCharacter(stateChangeCriterias, STATE_TYPE_CHARACTER::GUARD_PLAYER_STATE, STATE_TYPE_CHARACTER::GUARD_PLAYER_STATE)
{
}

// ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾌ擾ｿｽﾔに難ｿｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾌ擾ｿｽ・ｽE・ｽ・ｽE・ｽ
void GuardPlayerState::OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState)
{
	PlayerProcessOnEnter(character);
	//character->SetAnimation(ANIMATION_MOVE_TYPE::GUARD);
}

// ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾌ擾ｿｽﾔゑｿｽo・ｽE・ｽ骼橸ｿｽﾌ擾ｿｽ・ｽE・ｽ・ｽE・ｽ
void GuardPlayerState::OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState)
{
	PlayerProcessOnExit(character);
}

// ・ｽE・ｽX・ｽE・ｽe・ｽE・ｽ[・ｽE・ｽg・ｽE・ｽﾏ更・ｽE・ｽm・ｽE・ｽF
STATE_TYPE_CHARACTER GuardPlayerState::StateCheck(CharacterBase* character)
{
	//if (!character->CheckAnimationType(ANIMATION_MOVE_TYPE::GUARD))
	{
		return STATE_TYPE_CHARACTER::IDLE_PLAYER_STATE;
	}

	return mStateNumber;
}

// ・ｽE・ｽX・ｽE・ｽV
void GuardPlayerState::Update(CharacterBase* character)
{
}

// ・ｽE・ｽﾅ終・ｽE・ｽX・ｽE・ｽV
void GuardPlayerState::LastUpdate(CharacterBase* character)
{
	HpDrawInfoSetup(character);
}

// ・ｽE・ｽ`・ｽE・ｽ・ｽE・ｽ
void GuardPlayerState::Draw(CharacterBase* character)
{
	PlayerProcessDraw(character);
}

// ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽS
void GuardPlayerState::Death(CharacterBase* character)
{
	PlayerDeath(character);
}

/*--------------------------*/
/*・ｽE・ｽy・ｽE・ｽ|・ｽE・ｽ・ｽE・ｽv・ｽE・ｽ・ｽE・ｽ・ｽE・ｽC・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ[・ｽE・ｽX・ｽE・ｽe・ｽE・ｽ[・ｽE・ｽg・ｽE・ｽz*/
/*--------------------------*/
FallDownPlayerState::FallDownPlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias)
: PlayerProcess()
, IStateCharacter(stateChangeCriterias, STATE_TYPE_CHARACTER::FALL_DOWN_PLAYER_STATE, STATE_TYPE_CHARACTER::FALL_DOWN_PLAYER_STATE)
{
}

// ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾌ擾ｿｽﾔに難ｿｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾌ擾ｿｽ・ｽE・ｽ・ｽE・ｽ
void FallDownPlayerState::OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState)
{
	PlayerProcessOnEnter(character);
	//character->SetAnimation(ANIMATION_MOVE_TYPE::DOWN);
}

// ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾌ擾ｿｽﾔゑｿｽo・ｽE・ｽ骼橸ｿｽﾌ擾ｿｽ・ｽE・ｽ・ｽE・ｽ
void FallDownPlayerState::OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState)
{
	//PlayerProcessOnExit(character);
}

// ・ｽE・ｽX・ｽE・ｽe・ｽE・ｽ[・ｽE・ｽg・ｽE・ｽﾏ更・ｽE・ｽm・ｽE・ｽF
STATE_TYPE_CHARACTER FallDownPlayerState::StateCheck(CharacterBase* character)
{
	//if (!character->CheckAnimationType(ANIMATION_MOVE_TYPE::DOWN))
	{
		//return STATE_TYPE_CHARACTER::IDLE_PLAYER_STATE;
	}

	return mStateNumber;
}

// ・ｽE・ｽX・ｽE・ｽV
void FallDownPlayerState::Update(CharacterBase* character)
{
}

// ・ｽE・ｽﾅ終・ｽE・ｽX・ｽE・ｽV
void FallDownPlayerState::LastUpdate(CharacterBase* character)
{
	HpDrawInfoSetup(character);
}

// ・ｽE・ｽ`・ｽE・ｽ・ｽE・ｽ
void FallDownPlayerState::Draw(CharacterBase* character)
{
	PlayerProcessDraw(character);
}

// ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽS
void FallDownPlayerState::Death(CharacterBase* character)
{
	//PlayerDeath(character);
}

/*--------------------------------*/
/*・ｽE・ｽy・ｽE・ｽW・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽv・ｽE・ｽU・ｽE・ｽ・ｽE・ｽ・ｽE・ｽv・ｽE・ｽ・ｽE・ｽ・ｽE・ｽC・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ[・ｽE・ｽX・ｽE・ｽe・ｽE・ｽ[・ｽE・ｽg・ｽE・ｽz*/
/*--------------------------------*/
JumpAttackPlayerState::JumpAttackPlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias)
: PlayerProcess()
, IStateCharacter(stateChangeCriterias, STATE_TYPE_CHARACTER::JUMP_ATTACK_PLAYER_STATE, STATE_TYPE_CHARACTER::JUMP_ATTACK_PLAYER_STATE)
, mfUpDownSpeed(10.0f)
{
}

// ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾌ擾ｿｽﾔに難ｿｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾌ擾ｿｽ・ｽE・ｽ・ｽE・ｽ
void JumpAttackPlayerState::OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState)
{
	PlayerProcessOnEnter(character);
	character->StartAttck(ATTACK_METHOD_TYPE::JUMP);
	character->SetAnimation(ANIMATION_MOVE_TYPE::JUMP_ATTACK_IN);
}

// ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽﾌ擾ｿｽﾔゑｿｽo・ｽE・ｽ骼橸ｿｽﾌ擾ｿｽ・ｽE・ｽ・ｽE・ｽ
void JumpAttackPlayerState::OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState)
{
	PlayerProcessOnExit(character);
	character->SetPos(VGet(character->GetPos().x, 0.0f, character->GetPos().z));
}

// ・ｽE・ｽX・ｽE・ｽe・ｽE・ｽ[・ｽE・ｽg・ｽE・ｽﾏ更・ｽE・ｽm・ｽE・ｽF
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

// ・ｽE・ｽX・ｽE・ｽV
void JumpAttackPlayerState::Update(CharacterBase* character)
{
	// ・ｽE・ｽU・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ
	VECTOR position = character ->GetPos();
	CameraData cameraData = Master::mpGameManager->GetCameraManager()->GetCameraData();
	cameraData.angle.y = -UtilCalc::VDegChange(UtilCalc::VMoveVecToAngle(VSub(position, VAdd(position, UtilCalc::VAngleToVec(character->GetAngle()))), UtilCalc::VZero, UtilCalc::PiTwo)).y + UtilCalc::RadPi;
	cameraData.angle.x = 45.0f;
	Master::mpGameManager->GetCameraManager()->SetCameraData(cameraData);

	SetPlayerMove(character);

    if (character->CheckAnimationMoveType(ANIMATION_MOVE_TYPE::ATTACK_IN))
	{
		character->SetUpMove();
	}
	else if (character->CheckAnimationMoveType(ANIMATION_MOVE_TYPE::ATTACK_OUT))
    {
		character->SetDownMove();
    }
    

}

// ・ｽE・ｽﾅ終・ｽE・ｽX・ｽE・ｽV
void JumpAttackPlayerState::LastUpdate(CharacterBase* character)
{
	HpDrawInfoSetup(character);
}

// ・ｽE・ｽ`・ｽE・ｽ・ｽE・ｽ
void JumpAttackPlayerState::Draw(CharacterBase* character)
{
	PlayerProcessDraw(character);
}

// ・ｽE・ｽ・ｽE・ｽ・ｽE・ｽS
void JumpAttackPlayerState::Death(CharacterBase* character)
{
	PlayerDeath(character);
}

/*----------------------------*/
/*     ・ｽE・ｽy・ｽE・ｽo・ｽE・ｽg・ｽE・ｽ・ｽE・ｽ・ｽE・ｽX・ｽE・ｽe・ｽE・ｽ[・ｽE・ｽg・ｽE・ｽz     */
/*----------------------------*/

/*--------------------------------*/
/*・ｽE・ｽyIdle・ｽE・ｽo・ｽE・ｽg・ｽE・ｽ・ｽE・ｽ・ｽE・ｽv・ｽE・ｽ・ｽE・ｽ・ｽE・ｽC・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ[・ｽE・ｽX・ｽE・ｽe・ｽE・ｽ[・ｽE・ｽg・ｽE・ｽz*/
/*--------------------------------*/
IdleBattlePlayerState::IdleBattlePlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias)
: IdlePlayerState(stateChangeCriterias)
{
	L_R_KeyDrawDataSetUp(PLAYER_DRAW_KEY_TYPE::PLAYER_DRAW_KEY_VALID);
}

// ・ｽE・ｽX・ｽE・ｽe・ｽE・ｽ[・ｽE・ｽg・ｽE・ｽﾏ更・ｽE・ｽm・ｽE・ｽF
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
/*・ｽE・ｽy・ｽE・ｽﾚ難ｿｽ・ｽE・ｽo・ｽE・ｽg・ｽE・ｽ・ｽE・ｽ・ｽE・ｽv・ｽE・ｽ・ｽE・ｽ・ｽE・ｽC・ｽE・ｽ・ｽE・ｽ・ｽE・ｽ[・ｽE・ｽX・ｽE・ｽe・ｽE・ｽ[・ｽE・ｽg・ｽE・ｽz*/
/*--------------------------------*/
MoveBattlePlayerState::MoveBattlePlayerState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias)
: MovePlayerState(stateChangeCriterias)
{
	L_R_KeyDrawDataSetUp(PLAYER_DRAW_KEY_TYPE::PLAYER_DRAW_KEY_VALID);
}

// ・ｽE・ｽX・ｽE・ｽe・ｽE・ｽ[・ｽE・ｽg・ｽE・ｽﾏ更・ｽE・ｽm・ｽE・ｽF
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
