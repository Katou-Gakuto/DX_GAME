#include <future>
#include <iostream>

#include "BitFlag.h"
#include "ResourceData.h"
#include "TimeData.h"
#include "Vector2.h"

#include "DxLib.h"

#include "Master.h"

#include "DataManager.h"
#include "FadeManager.h"
#include "LoadingManager.h"
#include "ResourceManager.h"
#include "ThreadManager.h"
#include "TimeManager.h"

#ifdef _DEBUG
#include "DebugLogs/DebugLog.h"
#endif


/*----------------------*/
/*【フェードマネージャー】*/
/*----------------------*/

FadeManager::FadeManager()
: mfFadeAlpha(255)
, mbFadeFlag(false)
, mbFadeDrawFlag(true)
, mbFadeOutFlag(false)
, mbFadeInFlag(false)
, mpDataManager(nullptr)
, mpTimeManager(nullptr)
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
void FadeManager::Finalize()
{
    mbFadeFlag = false;
}

// 描画
void FadeManager::Draw()
{
    if (mbFadeDrawFlag)
    {
        Vector2_Int displaySize = ResourceManager::mstDisplaySize.GetVecInt();

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
    if (mbFadeFlag || mbFadeInFlag)
    {
        return;
    }

    mbFadeFlag = true;
    mbFadeOutFlag = true;

#ifdef _DEBUG
    DEBUG::SaveText("FadeOut\n", DEBUG::DEBUG_MAP_TYPE::DEBUG_FADE);
#endif

    /*フェードアウト開始*/
    Master::mpThreadManager->AddThread(std::async(std::launch::async, &FadeManager::FadeProcess, this, mfFadeSpeed));
}

// フェードイン開始
void FadeManager::FadeIn()
{
    if (mbFadeFlag || mbFadeOutFlag)
    {
        return;
    }
    mbFadeFlag = true;
    mbFadeInFlag = true;

#ifdef _DEBUG
    DEBUG::SaveText("FadeIn\n", DEBUG::DEBUG_MAP_TYPE::DEBUG_FADE);
#endif
    
    /*フェードイン開始*/
    Master::mpThreadManager->AddThread(std::async(std::launch::async, &FadeManager::FadeProcess, this, -mfFadeSpeed));
}

void FadeManager::FadeProcess(float fadeSpeed)
{
    if (mbFadeOutFlag)
    {
        mbFadeDrawFlag = true;
    }
    TIME_DATA preTime = mpTimeManager->GetElapsedTime();

    while (mbFadeFlag && ((0.0f <= mfFadeAlpha) && (mfFadeAlpha <= 255.1f)))
    {
        if ((preTime + 17u) < Master::mpTimeManager->GetElapsedTime())
        {
            preTime = mpTimeManager->GetElapsedTime();
            mfFadeAlpha += fadeSpeed;
        }
    }

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
}