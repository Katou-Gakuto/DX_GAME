#pragma once
class FadeManager;
class ResourceManager;
class StageDataManager;
class TimeManager;

enum class STOP_FLAG_TYPE
{
    NODE = 0,
    GAME_OBJECT,
    GAME_OBJECT_UI_DRAW,
    UI_OBJECT,
    UI_MODEL,
    BACK_GROUND,
};

class StopManager
{
private:
    // フェードマネージャー
    FadeManager* mpFadeManager;

    // リソースマネージャー
    ResourceManager* mpResourceManager;

    // ステージデータマネージャー
    StageDataManager* mpStageDataManager;

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