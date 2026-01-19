#include "DxLib.h"

#include "Master.h"

#include "AttackManager.h"
#include "CameraManager.h"
#include "CollisionManager.h"
#include "DataManager.h"
#include "FadeManager.h"
#include "GameManager.h"
#include "KeyState.h"
#include "MapManager.h"
#include "ObjectManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "StopManager.h"
#include "TargetManager.h"
#include "TimeManager.h"

// コンストラクタ
GameManager::GameManager()
: mpAttackManager(nullptr)
, mpCameraManager(nullptr)
, mpCollisionManager(nullptr)
, mpMapManager(nullptr)
, mpObjectManager(nullptr)
, mpSceneManager(nullptr)
, mpTargetManager(nullptr)
, mnUINumber(0)
{
}
// デストラクタ
GameManager::~GameManager()
{
}

// 初期化
void GameManager::Initilize()
{
    Master::mpDataManager->Initilize();

    mpCameraManager = new CameraManager();

    Master::mpResourceManager->Initilize();

    Master::mpFadeManager->Initilize();
    Master::mpStopManager->Initilize();

    mpSceneManager = new SceneManager();
	mpSceneManager->Initilize();

    mpObjectManager = new ObjectManager();
    mpObjectManager->Initilize();

    mpAttackManager = new AttackManager();
    mpCollisionManager = new CollisionManager();
    mpMapManager = new MapManager();
    mpTargetManager = new TargetManager();

    SetDrawScreen(DX_SCREEN_BACK);
}

// 終了処理
void GameManager::Finailize()
{
    mpObjectManager->Finalize();

    delete mpCameraManager;
    delete mpObjectManager;
    delete mpSceneManager;
    delete mpAttackManager;
    delete mpCollisionManager;
    delete mpMapManager;
    delete mpTargetManager;
}

// 更新
void GameManager::Update()
{
    Master::mpKeyState->Update();

    mpCameraManager->Update();

    mpObjectManager->Update();

    mpCollisionManager->CollisionProcess();

    mpObjectManager->LastUpdate();

	mpSceneManager->Update();
}

// 必要であれば削除する
void GameManager::DeleteAllIfNeeded()
{
    mpObjectManager->DeleteAllIfNeeded();
}

// 描画
void GameManager::Draw()
{
    ClearDrawScreen();

    mpCameraManager->Draw();

    Master::mpResourceManager->StartDraw();
    mpObjectManager->Draw();
    mpMapManager->Draw();
    Master::mpResourceManager->MiddleDraw();

    mpObjectManager->Draw();

    mpMapManager->Draw();

    Master::mpResourceManager->LastDraw();

    Master::mpFadeManager->Draw();

    Master::mpResourceManager->DrawDataRelease();

    ScreenFlip();
}

/*----------*/
/*【UI処理】*/
/*----------*/

// UIナンバー増加
int GameManager::IncreaseUINumber()
{
    mnUINumber += 1;
    if (mnUINumber == 1) {
        // 時間を止める
        Master::mpTimeManager->SetStopFlag(true);
    }
    return mnUINumber;
}

// UIナンバー減少
void GameManager::DecreaseUINumber()
{
    mnUINumber -= 1;
    if (mnUINumber <= 0) {
        mnUINumber = 0;

        // 時間を動かす
        Master::mpTimeManager->SetStopFlag(false);
    }
}
