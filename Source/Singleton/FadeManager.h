#pragma once
#include <future>
#include <iostream>

class DataManager;
class TimeManager;

class FadeManager
{
private:
    // フェードフラグ
    bool mbFadeFlag;

    // フェード描画
    bool mbFadeDrawFlag;

    // フェードアウトフラグ
    bool mbFadeOutFlag;

    // フェードインフラグ
    bool mbFadeInFlag;

    // フェードの濃さ
    float mfFadeAlpha;

    // データマネージャー
    DataManager* mpDataManager;

    // タイムマネジャー
    TimeManager* mpTimeManager;

    // 非同期返り値
    std::future<void> mfuFadeTask;

public:
    FadeManager();
    ~FadeManager();

    /// <summary>初期化</summary>
    void Initilize();

    /// <summary>終了</summary>
    void Finailize();

    /// <summary>描画</summary>
    void Draw();

    /// <summary>フェードアウト開始</summary>
    void FadeOut();

    /// <summary>フェードイン開始</summary>
    void FadeIn();

    /// <summary>フェード処理</summary>
    void FadeProcess(float fadeSpeed);

    /// <summary>フェード終了</summary>
    void FadeEnd();

    /// <summary>フェードフラグ取得</summary>
    bool GetFadeFlag() { return mbFadeFlag; }

    /// <summary>フェード率取得</summary>
    float GetFadeRatio() { return mfFadeAlpha * 0.003921568f; }
};