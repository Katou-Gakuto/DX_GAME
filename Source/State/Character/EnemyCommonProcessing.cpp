#include "ResourceData.h"

#include "DxLib.h"

#include "Master.h"

#include "CameraManager.h"
#include "DrawManager.h"
#include "EnemyCommonProcessing.h"
#include "GameManager.h"
#include "ObjectBases.h"
#include "ResourceGraph.h"
#include "ResourceManager.h"
#include "ObjectBases.h"
#include "StopManager.h"

EnemyCommonProcessing::EnemyCommonProcessing(STATE_ENEMY_TYPE enemyType)
{
    meEnemyType = enemyType;

    mnScreenHandle = MakeScreen(SCREEN_SIZES[(int)enemyType].x, SCREEN_SIZES[(int)enemyType].y, TRUE);
}

// �폜����
EnemyCommonProcessing::~EnemyCommonProcessing()
{
    EnemyCommonProcessingData_Delete();
}

void EnemyCommonProcessing::EnemyCommonProcessingData_Delete()
{
    if (mnScreenHandle != -1)
    {
        DeleteGraph(mnScreenHandle);
        mnScreenHandle = -1;
    }
}

// �G�l�~�[���`��
void EnemyCommonProcessing::EnemyDataDraw(CharacterBase *enemy)
{
    if (mnScreenHandle == -1)
    {
        return;
    }

    // �`��K�v�f�[�^�擾
    VECTOR setCharacterPos = VAdd(enemy->GetPos(), VGet(0, enemy->GetSize().y * 250.0f, 0));
    DrawManager* drawManager = Master::mpDrawManager;

    // �`����ύX
    SetDrawScreen(mnScreenHandle);
    ClearDrawScreen();

    // switch (/*meEnemyType*/STATE_ENEMY_TYPE::NONE)
    // {
    // case STATE_ENEMY_TYPE::MAP_ENEMY:

    //     // // �y��
    //     // DrawBoxAA(0, 0, mnScreenSizeX, 40, GetColor(255, 255, 255), TRUE);
    //     // DrawBoxAA(2, 2, mnScreenSizeX - 2, 40 - 2, GetColor(0, 0, 0), TRUE);

    //     // ���O
    //     //DrawExtendGraph(0, 0, 100, 50, mnNameHandle, TRUE);
    //     DrawFormatString(5, 21, GetColor(255, 255, 255), "%s", "mstrName.c_str()");

    //     // ���x��
    //     DrawBox(1, 1, 65, 20, GetColor(255, 255, 255), TRUE);
    //     DrawBox(3, 3, 63, 18, GetColor(0, 0, 0), TRUE);
    //     DrawFormatString(5, 3, GetColor(255, 255, 255), "Lv.%d", enemy->GetStatus()->level);
    //     break;

    // case STATE_ENEMY_TYPE::BATTLE_ENEMY:
    //     // �`��K�v�f�[�^�擾
    //     VECTOR setCharacterPos = VAdd(enemy->GetPos(), VGet(0, enemy->GetSize().y * 250.0f, 0));

    //     // �`����ύX
    //     SetDrawScreen(mnScreenHandle);
    //     ClearDrawScreen();

    //     // // �y��
    //     // DrawBoxAA(0, 0, mnScreenSizeX, 40, GetColor(255, 255, 255), TRUE);
    //     // DrawBoxAA(2, 2, mnScreenSizeX - 2, 40 - 2, GetColor(0, 0, 0), TRUE);

    //     // ���O
    //     //DrawExtendGraph(0, 0, 100, 50, mnNameHandle, TRUE);
    //     DrawFormatString(5, 21, GetColor(255, 255, 255), "%s", "mstrName.c_str()");

    //     // ���x��
    //     DrawBox(1, 1, 65, 20, GetColor(255, 255, 255), TRUE);
    //     DrawBox(3, 3, 63, 18, GetColor(0, 0, 0), TRUE);
    //     DrawFormatString(5, 3, GetColor(255, 255, 255), "Lv.%d", enemy->GetStatus()->level);

    //     // �y��
    //     DrawBoxAA(0, 40, SCREEN_SIZES[(int)meEnemyType].x, 80, GetColor(255, 255, 255), TRUE);
    //     DrawBoxAA(2, 42, SCREEN_SIZES[(int)meEnemyType].x - 2, 80 - 2, GetColor(0, 0, 0), TRUE);

    //     // HP����
    //     DrawFormatString(5, 43, GetColor(255, 255, 255), "HP:%d", enemy->GetStatus()->hp);

    //     // HP�o�[
    //     DrawBox(5, 60, SCREEN_SIZES[(int)meEnemyType].x - 5, 75, GetColor(255, 255, 255), TRUE);
    //     DrawBox(8, 63, SCREEN_SIZES[(int)meEnemyType].x - 8, 72, GetColor(0, 0, 0), TRUE);
    //     DrawBox(8, 63, ((SCREEN_SIZES[(int)meEnemyType].x - 16) * (static_cast<float>(enemy->GetStatus()->hp) / static_cast<float>(enemy->GetStatus()->maxHp))) + 8, 72, GetColor(255, 0, 0), TRUE);
    //     break;
    // }
    std::vector<DRAW_DATA> drawData = enemy->GetStateDrawData();
    for (int i = 0; i < drawData.size(); i++)
    {
        drawManager->DrawData_Draw(&drawData[i], true);
    }

    SetDrawScreen(DX_SCREEN_BACK);
    // 3D�J�����ݒ�
    Master::mpGameManager->GetCameraManager()->Draw();
    SetDrawBlendMode(DX_BLENDMODE_PMA_ALPHA, 128);
    DrawBillboard3D(setCharacterPos, 0.5f, 0.0f, 200.0f, 0.0f, mnScreenHandle, TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

// �G�l�~�[�摜�f�[�^������
void EnemyCommonProcessing::EnemyGraphDataInitialize(CharacterBase *enemy)
{
	if (enemy->GetStateDrawData().size() <= 0)
	{
		std::vector<DRAW_DATA> drawDatas;
		drawDatas.resize(ENEMY_DRAW_TYPE::ENEMY_DRAW_MAX);
			
		// HP
		{
			DRAW_DATA drawData = DRAW_DATA();
			drawData.drawFlag = false;
			drawData.drawGraphData.drawType = DRAW_GRAPH_TYPE::EXTEND;
			drawData.drawGraphData.graphPos = Vector2_Int(0, 0);
			drawData.drawGraphData.graphSize = HP_GRAPH_SIZE;
			drawData.drawGraphData.transFlag = TRUE;

			drawDatas[ENEMY_DRAW_TYPE::HP_FRAME] = drawData;
			drawDatas[ENEMY_DRAW_TYPE::HP_FRAME].drawGraphData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle(ResourceManager::msResourceFile + "2D/HpBack.png");

			drawData.drawGraphData.drawType = DRAW_GRAPH_TYPE::RECT_EXTEND;

			drawDatas[ENEMY_DRAW_TYPE::HP_LEFT] = drawData;
			drawDatas[ENEMY_DRAW_TYPE::HP_LEFT].drawGraphData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle(ResourceManager::msResourceFile + "2D/HpBar.png");

			drawData.drawGraphData.drawType = DRAW_GRAPH_TYPE::EXTEND;

			drawDatas[ENEMY_DRAW_TYPE::HP_RIGHT] = drawData;
			drawDatas[ENEMY_DRAW_TYPE::HP_RIGHT].drawGraphData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle(ResourceManager::msResourceFile + "2D/HpBarRed.png");
		}

        // �O�g
        {
			DRAW_DATA drawData = DRAW_DATA();
			drawData.drawFlag = false;
			drawData.drawGraphData.drawType = DRAW_GRAPH_TYPE::EXTEND;
			drawData.drawGraphData.pos = Vector2_Int(0, 0);
			drawData.drawGraphData.extPos = Vector2_Int(SCREEN_SIZES[(int)meEnemyType].x, SCREEN_SIZES[(int)meEnemyType].y);
			drawData.drawGraphData.transFlag = TRUE;

			//drawDatas[ENEMY_DRAW_TYPE::FRAME] = drawData;
			//drawDatas[ENEMY_DRAW_TYPE::FRAME].drawGraphData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle(ResourceManager::msResourceFile + "2D/HpBack.png");
        }

		enemy->SetStateDrawData(drawDatas);
		
		HpDrawInfoSetup(enemy);
	}
}

// HP�`����ݒ�
void EnemyCommonProcessing::HpDrawInfoSetup(CharacterBase *enemy)
{
	// ���f���͕`�悵�������߂���ȊO�𖳌�������
	if (Master::mpStopManager->GetStopFlag(STOP_FLAG_TYPE::GAME_OBJECT_UI_DRAW))
	{
		return;
	}

	std::vector<DRAW_DATA> drawDatas = enemy->GetStateDrawData();

	Vector2_Int frameSize = HP_FRAME_SIZE;
	Vector2_Int leftUp = mstHpLeftUp;
	Vector2_Int rightDown = mstHpRightDown;

	drawDatas[ENEMY_DRAW_TYPE::HP_FRAME].drawGraphData.pos = Vector2_Int(leftUp.x - frameSize.x, leftUp.y - frameSize.y);
	drawDatas[ENEMY_DRAW_TYPE::HP_FRAME].drawGraphData.extPos = Vector2_Int(rightDown.x + frameSize.x, rightDown.y + frameSize.y);

	float hpRate = ((float)enemy->GetStatus()->hp / (float)enemy->GetStatus()->maxHp);

	drawDatas[ENEMY_DRAW_TYPE::HP_LEFT].drawGraphData.pos = Vector2_Int(leftUp.x, leftUp.y);
	drawDatas[ENEMY_DRAW_TYPE::HP_LEFT].drawGraphData.extPos = Vector2_Int((int)(leftUp.x + ((rightDown.x - leftUp.x) * hpRate)), rightDown.y);
	drawDatas[ENEMY_DRAW_TYPE::HP_LEFT].drawGraphData.graphSize.x = HP_GRAPH_SIZE.x * hpRate;

	drawDatas[ENEMY_DRAW_TYPE::HP_RIGHT].drawGraphData.pos = Vector2_Int(leftUp.x, leftUp.y);
	drawDatas[ENEMY_DRAW_TYPE::HP_RIGHT].drawGraphData.extPos = Vector2_Int(rightDown.x, rightDown.y);

	enemy->SetStateDrawData(drawDatas);
}
