#include <chrono>
#include <thread>
#include <algorithm>
#include <cmath>

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
#include "TimeManager.h"

/*----------------------*/
/*【フェードマネージャー】*/
/*----------------------*/

FadeManager::FadeManager()
    : mfFadeAlpha(255.0f)
    , mbFadeFlag(false)
    , mbFadeDrawFlag(true)
    , mbFadeOutFlag(false)
    , mbFadeInFlag(false)
    , mfFadeSpeed(5.0f)
    , mpDataManager(nullptr)
    , mpTimeManager(nullptr)
    , mfuFadeTask()
{
}

FadeManager::~FadeManager()
{
    Finailize();
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
    // 非同期処理を停止
    mbFadeFlag.store(false);

    // 非同期処理終了待機
    WaitFadeTask();

    // フェード状態初期化
    mbFadeOutFlag.store(false);
    mbFadeInFlag.store(false);
}

// 描画
void FadeManager::Draw()
{
    if (!mbFadeDrawFlag.load())
    {
        return;
    }

    // フェード値取得
    float fadeAlpha = GetFadeAlpha();

    // フェード値が0の場合描画しない
    if (fadeAlpha <= 0.0f)
    {
        return;
    }

    Vector2_Int displaySize = ResourceManager::mstDisplaySize.GetVecInt();

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(fadeAlpha));

    DrawBox(
        0,
        0,
        displaySize.x,
        displaySize.y,
        GetColor(0, 0, 0),
        TRUE
    );

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

// フェードアウト開始
void FadeManager::FadeOut()
{
    std::lock_guard<std::mutex> lock(mMutexFadeTask);

    // フェード中なら開始しない
    if (mbFadeFlag.load())
    {
        return;
    }

    // フェードアウト開始状態設定
    mbFadeFlag.store(true);
    mbFadeOutFlag.store(true);
    mbFadeInFlag.store(false);

    // フェード描画有効
    mbFadeDrawFlag.store(true);

    // フェード値初期化
    SetFadeAlpha(0.0f);

    // 非同期処理開始
    mfuFadeTask = std::async(
        std::launch::async,
        &FadeManager::FadeProcess,
        this,
        std::abs(mfFadeSpeed)
    );
}

// フェードイン開始
void FadeManager::FadeIn()
{
    std::lock_guard<std::mutex> lock(mMutexFadeTask);

    // フェード中なら開始しない
    if (mbFadeFlag.load())
    {
        return;
    }

    // フェードイン開始状態設定
    mbFadeFlag.store(true);
    mbFadeOutFlag.store(false);
    mbFadeInFlag.store(true);

    // フェード描画有効
    mbFadeDrawFlag.store(true);

    // フェード値初期化
    SetFadeAlpha(255.0f);

    // 非同期処理開始
    mfuFadeTask = std::async(
        std::launch::async,
        &FadeManager::FadeProcess,
        this,
        -std::abs(mfFadeSpeed)
    );
}

// フェード処理
void FadeManager::FadeProcess(float fadeSpeed)
{
    using namespace std::chrono;

    // 更新間隔
    constexpr float FADE_INTERVAL = 17.0f;

    // 前回更新時間
    TIME_DATA preTime = mpTimeManager->GetElapsedTime();

    while (mbFadeFlag.load())
    {
        TIME_DATA currentTime = mpTimeManager->GetElapsedTime();

        // 更新間隔経過確認
        if ((preTime + FADE_INTERVAL) < currentTime)
        {
            preTime = currentTime;

            // フェード値更新
            AddFadeAlpha(fadeSpeed);

            float fadeAlpha = GetFadeAlpha();

            // フェード終了確認
            if ((fadeSpeed > 0.0f && fadeAlpha >= 255.0f) ||
                (fadeSpeed < 0.0f && fadeAlpha <= 0.0f))
            {
                break;
            }
        }

        // CPU負荷軽減
        std::this_thread::sleep_for(milliseconds(1));
    }

    // 最終値設定
    if (fadeSpeed > 0.0f)
    {
        SetFadeAlpha(255.0f);
    }
    else
    {
        SetFadeAlpha(0.0f);
    }

    // フェードイン終了時は描画無効
    if (mbFadeInFlag.load())
    {
        mbFadeDrawFlag.store(false);
    }

    // ロード管理にフェード終了を通知
    Master::mpLoadingManager->SetLoadingFlag(LOADING_NUMBER::FADE);

    // フェード状態解除
    mbFadeFlag.store(false);
}

// フェード終了
void FadeManager::FadeEnd()
{
    // 非同期処理終了待機
    WaitFadeTask();

    // フェード状態初期化
    mbFadeFlag.store(false);
    mbFadeOutFlag.store(false);
    mbFadeInFlag.store(false);
}

// フェード値取得
float FadeManager::GetFadeAlpha()
{
    std::lock_guard<std::mutex> lock(mMutexFadeAlpha);

    return mfFadeAlpha;
}

// フェード値設定
void FadeManager::SetFadeAlpha(float alpha)
{
    std::lock_guard<std::mutex> lock(mMutexFadeAlpha);

    mfFadeAlpha = std::clamp(alpha, 0.0f, 255.0f);
}

// フェード値加算
void FadeManager::AddFadeAlpha(float alpha)
{
    std::lock_guard<std::mutex> lock(mMutexFadeAlpha);

    mfFadeAlpha = std::clamp(
        mfFadeAlpha + alpha,
        0.0f,
        255.0f
    );
}

// 非同期処理終了待機
void FadeManager::WaitFadeTask()
{
    std::lock_guard<std::mutex> lock(mMutexFadeTask);

    if (!mfuFadeTask.valid())
    {
        return;
    }

    // 非同期処理終了待機
    mfuFadeTask.get();
}