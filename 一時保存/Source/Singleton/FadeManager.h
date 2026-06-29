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

    // フェードの速度
    float mfFadeSpeed;

    // データマネージャー
    DataManager* mpDataManager;

    // タイムマネジャー
    TimeManager* mpTimeManager;

public:
    FadeManager();
    ~FadeManager();

    /// <summary>初期化</summary>
    void Initilize();

    /// <summary>終了</summary>
    void Finalize();

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
    inline bool GetFadeFlag() { return mbFadeFlag; }

    /// <summary>フェード率取得</summary>
    inline float GetFadeRatio() { return mfFadeAlpha * 0.003921568f; }

    /// <summary>フェード速度取得</summary>
    inline float GetFadeSpeed() { return mfFadeSpeed; }

    /// <summary>フェード速度設定</summary>
    inline void SetFadeSpeed(float speed) { mfFadeSpeed = speed; }
};