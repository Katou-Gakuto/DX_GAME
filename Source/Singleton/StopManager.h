#pragma once
class FadeManager;
class TimeManager;

enum class STOP_FLAG_TYPE
{
    NODE = 0,
    GAME_OBJECT,
};

class StopManager
{
private:
    // フェードマネージャー
    FadeManager* mpFadeManager;

    // タイムマネジャー
    TimeManager *mpTimeManager;

public:
    StopManager();
    ~StopManager();

    /// <summary>初期化</summary>
    void Initilize();

    /// <summary>ストップフラグ取得</summary>
    bool GetStopFlag(STOP_FLAG_TYPE stopType);
};