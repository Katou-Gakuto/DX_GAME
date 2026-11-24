#pragma once

#include <atomic>
#include <future>
#include <mutex>

class DataManager;
class TimeManager;

class FadeManager
{
private:
    // フェードフラグ
    std::atomic<bool> mbFadeFlag;

    // フェード描画
    std::atomic<bool> mbFadeDrawFlag;

    // フェードアウトフラグ
    std::atomic<bool> mbFadeOutFlag;

    // フェードインフラグ
    std::atomic<bool> mbFadeInFlag;

    // フェードの濃さ
    float mfFadeAlpha;

    // フェードの速度
    float mfFadeSpeed;

    // フェード値保護用
    mutable std::mutex mMutexFadeAlpha;

    // 非同期処理管理用
    std::future<void> mfuFadeTask;

    // 非同期処理管理用
    std::mutex mMutexFadeTask;

    // データマネージャー
    DataManager* mpDataManager;

    // タイムマネージャー
    TimeManager* mpTimeManager;

private:
    /// <summary>フェード値取得</summary>
    float GetFadeAlpha();

    /// <summary>フェード値設定</summary>
    void SetFadeAlpha(float alpha);

    /// <summary>フェード値加算</summary>
    void AddFadeAlpha(float alpha);

    /// <summary>非同期処理終了待機</summary>
    void WaitFadeTask();

    /// <summary>フェード処理開始</summary>
    bool StartFadeTask(float fadeSpeed);

public:
    FadeManager();
    ~FadeManager();

    /// <summary>初期化</summary>
    void Initilize();

    /// <summary>終了</summary>
    void Finailize();

    /// <summary>描画</summary>
    void Draw();

    /// <summary>フェードアウト開始(入り)</summary>
    void FadeOut();

    /// <summary>フェードイン開始(出)</summary>
    void FadeIn();

    /// <summary>フェード処理</summary>
    void FadeProcess(float fadeSpeed);

    /// <summary>フェード終了</summary>
    void FadeEnd();

    /// <summary>フェードフラグ取得</summary>
    inline bool GetFadeFlag()
    {
        return mbFadeFlag.load();
    }

    /// <summary>フェード率取得</summary>
    inline float GetFadeRatio()
    {
        return GetFadeAlpha() * 0.003921568f;
    }

    /// <summary>フェード速度取得</summary>
    inline float GetFadeSpeed()
    {
        return mfFadeSpeed;
    }

    /// <summary>フェード速度設定</summary>
    inline void SetFadeSpeed(float speed)
    {
        mfFadeSpeed = speed;
    }
};