#include "../Header/Master.h"

#include "../Header/GamaManager.h"
#include "../Header/ObjectManager.h"
#include "../Header/SceneManager.h"
#include "../Header/TimeManager.h"

// コンストラクタ
GameManager::GameManager()
: mnUINumber(0)
, mpSceneManager(nullptr)
, mpObjectManager(nullptr)
{
}
// デストラクタ
GameManager::~GameManager()
{
}

// 初期化
void GameManager::Initilize()
{
    mpSceneManager = new SceneManager();
	mpSceneManager->Initilize();

    mpObjectManager = new ObjectManager();
    mpObjectManager->Initilize();
}

// 終了処理
void GameManager::Finailize()
{
    mpObjectManager->Finalize();

    delete mpObjectManager;
    delete mpSceneManager;
}

// 更新
void GameManager::Update()
{
    mpObjectManager->Update();

    mpObjectManager->Update();

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
    mpObjectManager->Draw();
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
