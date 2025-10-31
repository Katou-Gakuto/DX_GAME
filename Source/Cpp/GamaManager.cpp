#include "DxLib.h"

#include "../Header/Master.h"

#include "../Header/CameraManager.h"
#include "../Header/GameManager.h"
#include "../Header/KeyState.h"
#include "../Header/ObjectManager.h"
#include "../Header/SceneManager.h"
#include "../Header/TimeManager.h"

// コンストラクタ
GameManager::GameManager()
: mpCameraManager(nullptr)
, mpObjectManager(nullptr)
, mpSceneManager(nullptr)
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
    mpCameraManager = new CameraManager();

    mpSceneManager = new SceneManager();
	mpSceneManager->Initilize();

    mpObjectManager = new ObjectManager();
    mpObjectManager->Initilize();

    SetDrawScreen(DX_SCREEN_BACK);
}

// 終了処理
void GameManager::Finailize()
{
    mpObjectManager->Finalize();

    delete mpCameraManager;
    delete mpObjectManager;
    delete mpSceneManager;
}

// 更新
void GameManager::Update()
{
    Master::mpKeyState->Update();

    mpCameraManager->Update();

    mpObjectManager->Update();

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

    mpObjectManager->Draw();

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
