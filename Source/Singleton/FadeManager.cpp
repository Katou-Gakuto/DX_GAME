#include <future>
#include <iostream>

#include "BitFlag.h"
#include "ResourceData.h"
#include "Vector2.h"

#include "DxLib.h"

#include "Master.h"

#include "DataManager.h"
#include "FadeManager.h"
#include "LoadingManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"

/*----------------------*/
/*【フェードマネージャー】*/
/*----------------------*/

FadeManager::FadeManager()
: mfFadeAlpha(0)
, mbFadeFlag(false)
, mbFadeDrawFlag(false)
, mbFadeOutFlag(false)
, mbFadeInFlag(false)
, mpDataManager(nullptr)
, mpTimeManager(nullptr)
, mfuFadeTask()
, mfFadeSpeed(5.0f)
{
}

FadeManager::~FadeManager()
{
}

// 初期化
void FadeManager::Initilize()
{
    mpDataManager = Master::mpDataManager;
    mpTimeManager = Master::mpTimeManager;
}

// 終了
void FadeManager::Finailize()
{
    mbFadeFlag = false;
}

// 描画
void FadeManager::Draw()
{
    if (mbFadeDrawFlag && false)
    {
        Vector2_Int displaySize = ResourceManager::mstDisplaySize;

        SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)mfFadeAlpha);
        /*boxから画像ハンドルでフェードしたい
        */
        DrawBox(0, 0, displaySize.x, displaySize.y, GetColor(0, 0, 0), TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
    }
}

// フェードアウト開始
void FadeManager::FadeOut()
{
    if (mbFadeFlag || mbFadeInFlag || true)
    {
        return;
    }

    mbFadeFlag = true;
    mbFadeOutFlag = true;

    /*フェードアウト開始*/
    mfuFadeTask = std::async(std::launch::async, &FadeManager::FadeProcess, this, mfFadeSpeed);
}

// フェードイン開始
void FadeManager::FadeIn()
{
    if (mbFadeFlag || mbFadeOutFlag || true)
    {
        return;
    }
    mbFadeFlag = true;
    mbFadeInFlag = true;
    
    /*フェードイン開始*/
   mfuFadeTask = std::async(std::launch::async, &FadeManager::FadeProcess, this, -mfFadeSpeed);
}

void FadeManager::FadeProcess(float fadeSpeed)
{
    if (mbFadeOutFlag)
    {
        mbFadeDrawFlag = true;
    }
    int preTime = mpTimeManager->GetTime();

    while (mbFadeFlag && ((0.0f <= mfFadeAlpha) && (mfFadeAlpha <= 255.1f)))
    {
        if ((preTime + 17) < mpTimeManager->GetTime())
        {
            preTime = mpTimeManager->GetTime();
            mfFadeAlpha += fadeSpeed;
        }
        // ユーザー定義メッセージをログに追加
        ErrorLogAdd("フェード\n");
    }

    // ユーザー定義メッセージをログに追加
    ErrorLogAdd("フェード終了\n");
    mfFadeAlpha -= fadeSpeed;
    
    if (mbFadeInFlag)
    {
        mbFadeDrawFlag = false;
    }

    Master::mpLoadingManager->SetLoadingFlag(LOADING_NUMBER::FADE);

    mbFadeFlag = false;
}

// フェード終了
void FadeManager::FadeEnd()
{
    mbFadeOutFlag = false;
    mbFadeInFlag = false;

    mfuFadeTask.get();
}