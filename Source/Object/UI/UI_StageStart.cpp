#include "CameraData.h"
#include "DrawData.h"

#include "Master.h"

#include "CameraManager.h"
#include "DataManager.h"
#include "DrawManager.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "StageDataManager.h"
#include "TimeManager.h"
#include "UI_StageStart.h"
#include "UtilFactorys.h"

UI_StageStart::UI_StageStart()
: UIBase(true, 1, true)
, mnCameraID(-1)
, mstSurvivalTime(0)
, mbFadeInFlag(false)
{
}

UI_StageStart::~UI_StageStart()
{
}

// UI初期化
void UI_StageStart::UIInitilize()
{
    Master::mpStageDataManager->SetStageStartPeriodFlag(true);

    mstSurvivalTime = Master::mpTimeManager->GetElapsedTime() + SURVIVAL_TIME;

    // ゲーム開始時字幕
    {
		std::vector<DRAW_GRAPH_DATA> setDrawDatas;
		DisplaySize displaySize = ResourceManager::mstDisplaySize;

        setDrawDatas.clear();
        DRAW_GRAPH_DATA drawData;
        drawData.drawType = DRAW_GRAPH_TYPE::SIZE;
        drawData.pos = displaySize.LeftUp_Ratio(Vector2(0.0f, 0.1f));
        drawData.size = displaySize.LeftUp_Ratio(Vector2(1.0f, 0.2f));
        drawData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle((ResourceManager::msResourceFile + "2D/White.png");
        drawData.transFlag = TRUE;
        setDrawDatas.push_back(drawData);


        int stringNumber = 0;
        switch (Master::mpGameManager->GetSceneManager()->GetNowScene())
        {
        case SCENE::TOWN_1:
            stringNumber++;
        case SCENE::TOWN_2:
            stringNumber++;
        case SCENE::TOWN_3:
            stringNumber++;
            drawData.drawType = DRAW_GRAPH_TYPE::SIZE;
            drawData.pos = displaySize.LeftUp_Ratio(Vector2(0.4f, 0.15f));
            drawData.size = displaySize.LeftUp_Ratio(Vector2(0.2f, 0.1f));
            drawData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle((ResourceManager::msResourceFile + "2D/TownString_" + std::to_string(stringNumber) + ".png");
            drawData.transFlag = TRUE;
            setDrawDatas.push_back(drawData);
            break;

        case SCENE::DUNGEON_1:
            stringNumber++;
        case SCENE::DUNGEON_2:
            stringNumber++;
        case SCENE::DUNGEON_3:
            stringNumber++;
            drawData.drawType = DRAW_GRAPH_TYPE::SIZE;
            drawData.pos = displaySize.LeftUp_Ratio(Vector2(0.3f, 0.15f));
            drawData.size = displaySize.LeftUp_Ratio(Vector2(0.4f, 0.1f));
            drawData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle((ResourceManager::msResourceFile + "2D/DungeonString_" + std::to_string(stringNumber) + ".png");
            drawData.transFlag = TRUE;
            setDrawDatas.push_back(drawData);
            break;

        case SCENE::BATTLE_1:
            stringNumber++;
        case SCENE::BATTLE_2:
            stringNumber++;
        case SCENE::BATTLE_3:
            stringNumber++;
            drawData.drawType = DRAW_GRAPH_TYPE::SIZE;
            drawData.pos = displaySize.LeftUp_Ratio(Vector2(0.325f, 0.15f));
            drawData.size = displaySize.LeftUp_Ratio(Vector2(0.35f, 0.1f));
            drawData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle((ResourceManager::msResourceFile + "2D/BattleString_" + std::to_string(stringNumber) + ".png");
            drawData.transFlag = TRUE;
            setDrawDatas.push_back(drawData);
            break;

        case SCENE::BATTLE_LOOP:
            drawData.drawType = DRAW_GRAPH_TYPE::SIZE;
            drawData.pos = displaySize.LeftUp_Ratio(Vector2(0.325f, 0.15f));
            drawData.size = displaySize.LeftUp_Ratio(Vector2(0.35f, 0.1f));
            drawData.handle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle((ResourceManager::msResourceFile + "2D/WaveString_" + std::to_string(Master::mpDataManager->GetWaveNumber() + 1) + ".png");
            drawData.transFlag = TRUE;
            setDrawDatas.push_back(drawData);
            break;
        }

        // モデル追加
        AddModelData(setDrawDatas, MODEL_TYPE::GRAPH);

        // アニメーション設定
        AnimationSetting(LOAD_ANIMATION_DATA_FACTORY_NUMBER::UI_FADE, { });
    }
	GetAnimation(0)->SetAnimationType(ANIMATION_TYPE::FADE_OUT);
}

// UIシーン最終初期化
void UI_StageStart::UISceneLastInitilize()
{
}

// UI終了
void UI_StageStart::UIFinalize()
{
    Master::mpStageDataManager->SetStageStartPeriodFlag(false);
}

// UI更新
void UI_StageStart::UIUpdate()
{
	// 初期化でやると切り替え時に一瞬白飛びする
	if (mnCameraID == -1)
	{
		CameraData cameraData = CameraData();
		cameraData.cameraMode = CAMERA_MODE::MOVE;

        {// R_F
            cameraData.position =       VGet(    0.0f,  350.0f,    0.0f);   // ポジション
            cameraData.moveDistance =   VGet(   20.0f,    0.0f,    0.0f);   // 移動量
            cameraData.plusPosition =   VGet(    0.0f,   -1.0f,   10.0f);   // 向く地点
            cameraData.targetPosition = VGet( 4400.0f,  350.0f,    0.0f);   // 目標越智店
        }
        // {// F_F
        //     cameraData.position =       VGet( 2000.0f,  350.0f,    0.0f);   // ポジション
        //     cameraData.moveDistance =   VGet(    0.0f,    0.0f,   20.0f);   // 移動量
        //     cameraData.plusPosition =   VGet(    0.0f,   -1.0f,   10.0f);   // 向く地点
        //     cameraData.targetPosition = VGet( 2000.0f,  350.0f, 4400.0f);   // 目標越智店
        // }
        // {// F_B
        //     cameraData.position =       VGet( 2000.0f,  350.0f,    0.0f);   // ポジション
        //     cameraData.moveDistance =   VGet(    0.0f,    0.0f,   20.0f);   // 移動量
        //     cameraData.plusPosition =   VGet(    0.0f,   -1.0f,  -10.0f);   // 向く地点
        //     cameraData.targetPosition = VGet( 2000.0f,  350.0f, 4400.0f);   // 目標越智店
        // }        
        // {// B_B
        //     cameraData.position =       VGet( 2000.0f,  350.0f, 4400.0f);   // ポジション
        //     cameraData.moveDistance =   VGet(    0.0f,    0.0f,  -20.0f);   // 移動量
        //     cameraData.plusPosition =   VGet(    0.0f,   -1.0f,  -10.0f);   // 向く地点
        //     cameraData.targetPosition = VGet( 2000.0f,  350.0f,    0.0f);   // 目標越智店
        // }
        // {// B_F
        //     cameraData.position =       VGet( 2000.0f,  350.0f, 4400.0f);   // ポジション
        //     cameraData.moveDistance =   VGet(    0.0f,    0.0f,  -20.0f);   // 移動量
        //     cameraData.plusPosition =   VGet(    0.0f,   -1.0f,   10.0f);   // 向く地点
        //     cameraData.targetPosition = VGet( 2000.0f,  350.0f,    0.0f);   // 目標越智店
        // }


		mnCameraID = Master::mpGameManager->GetCameraManager()->NewCamera(cameraData);
		Master::mpGameManager->GetCameraManager()->SetCameraMode(mnCameraID);
	}

	if (!mbFadeInFlag && 
			(
				(Master::mpTimeManager->GetElapsedTime() > (mstSurvivalTime.Full - FADE_IN_TIME))
			)
		)
	{
		DecisionProcess();
	}
	else if (!mbFadeInFlag &&
			(
				(CheckDecision()) ||
				(Master::mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::X))
			)
		)
	{
        mstSurvivalTime = Master::mpTimeManager->GetElapsedTime() + FADE_IN_TIME;
		DecisionProcess();
	}
	else if (mstSurvivalTime < Master::mpTimeManager->GetElapsedTime())
	{
		CloseProcess();
	}

}

// UI最終更新
void UI_StageStart::UILastUpdate()
{
}

// UI描画
void UI_StageStart::UIDraw()
{
}

// 選択決定時処理
void UI_StageStart::DecisionProcess()
{
	GetAnimation(0)->SetAnimationType(ANIMATION_TYPE::FADE_IN);
	mbFadeInFlag = true;
}

// 削除処理
void UI_StageStart::CloseProcess()
{
	SetDeleteFlag(true);
	Master::mpGameManager->GetCameraManager()->SetCameraMode(Master::mpGameManager->GetSceneManager()->GetSceneCameraID());
	Master::mpGameManager->GetCameraManager()->DeleteCameraData(mnCameraID);
}