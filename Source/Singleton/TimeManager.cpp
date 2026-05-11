#include <windows.h>

#ifdef _DEBUG
#include <map>
#endif

#include "DxLib.h"

#include "TimeManager.h"

// コンストラクタ
TimeManager::TimeManager(int oneFrameTime)
: munLowestOneFrameSeconds(oneFrameTime)
, mstStartTime(TIME_DATA())
, mstPreviousTime(TIME_DATA())
, mstGameStopTime(TIME_DATA())
, mfTimeScale(1.0f)
, mfDeltaTime(0.0f)
, mstElapsedTime(TIME_DATA())
, mstFrameCount(FRAME_DATA())
, mstGameElapsedTime(TIME_DATA())
, mstGameFrameCount(FRAME_DATA())
, mstSceneElapsedFrame(FRAME_DATA())
, mstBackgroundTime(TIME_DATA())
, mstUnprocessedBackgroundTime(TIME_DATA())
, mulBackgroundStartTime(0ul)
, mbGameStopFlag(false)
, mbNewSceneTimeFlag(false)
{
#ifdef _DEBUG
    mmForPastFrameSecondsSave.clear();
#endif
}
// デストラクタ
TimeManager::~TimeManager()
{
}
// 初期化
void TimeManager::Initilize()
{
    timeBeginPeriod(1); // タイマーの分解量の設定を1msにする (1ミリ秒/1000秒)にする
    mstStartTime.Time = timeGetTime();
}

// 更新
bool TimeManager::GetNextUpdateFlag()
{
    unsigned long nowTime = timeGetTime();

    // 経過時間差分
    unsigned long timeDiff = nowTime - mstElapsedTime.Time;    

    // 時間経過処理
    if (timeDiff >= munLowestOneFrameSeconds)
    {
        mstPreviousTime = mstElapsedTime;
#ifdef _DEBUG
        // 試験運用家でデバッグ時
        mstElapsedTime += munLowestOneFrameSeconds;
        mfDeltaTime = static_cast<float>(munLowestOneFrameSeconds) * 0.001f * mfTimeScale;
#else
        mstElapsedTime += timeDiff;
        mfDeltaTime = static_cast<float>(timeDiff) * 0.001f * mfTimeScale;
#endif

        mstFrameCount.Frame++;

        if (mbGameStopFlag) {
            mstGameStopTime += timeDiff;

            // シーン時間フラグ無効化
            mbNewSceneTimeFlag = false;
        }
        else if (mbNewSceneTimeFlag) {
            mstGameStopTime += ((timeDiff) - munLowestOneFrameSeconds);
            mbNewSceneTimeFlag = false;
        }
        else
        {
            mstGameFrameCount.Frame++;
#ifdef _DEBUG
            mstGameElapsedTime += munLowestOneFrameSeconds;
#else
            mstGameElapsedTime += timeDiff;
#endif
        }

#ifdef _DEBUG
        if (mmForPastFrameSecondsSave.find(timeDiff) == mmForPastFrameSecondsSave.end())
        {
            mmForPastFrameSecondsSave[timeDiff] = 0u;
        }
        mmForPastFrameSecondsSave[timeDiff]++;
#endif

        return true;
    }

    return false;
}

// バックグラウンドに出た時の処理
void TimeManager::OnEnterBackground()
{
    mulBackgroundStartTime = timeGetTime();
}

// バックグラウンドから戻った処理
void TimeManager::OnReturnForeground()
{
    unsigned long backgroundTime = timeGetTime() - mulBackgroundStartTime;
    mstUnprocessedBackgroundTime = TIME_DATA();
    mstUnprocessedBackgroundTime += backgroundTime;
    mstBackgroundTime += backgroundTime;
}

// 時間比較
bool TimeManager::IsOverTime(TIME_DATA comparisonTime, TIME_PROCESSING_TYPE timeProcessingType)
{
    TIME_DATA targetTime;

    switch (timeProcessingType)
    {
    case TIME_PROCESSING_TYPE::ELAPSED:
        targetTime = mstElapsedTime;
        break;
    case TIME_PROCESSING_TYPE::GAME_ELAPSED:
        targetTime = mstGameElapsedTime;
        break;
    case TIME_PROCESSING_TYPE::STOP:
        targetTime = mstGameStopTime;
        break;
    case TIME_PROCESSING_TYPE::BACKGROUND:
        targetTime = mstBackgroundTime;
        break;
    default:
        return false;
    }

    // 現在の時間が比較対象の時間を超えているか
    return targetTime > comparisonTime;
}

// フレーム数比較
bool TimeManager::IsOverFrame(FRAME_DATA comparisonFrame, FRAME_PROCESSING_TYPE frameProcessingType)
{
    unsigned int targetFrame = 0;

    switch (frameProcessingType)
    {
    case FRAME_PROCESSING_TYPE::TOTAL:
        targetFrame = mstFrameCount.Frame;
        break;
    case FRAME_PROCESSING_TYPE::GAME:
        targetFrame = mstGameFrameCount.Frame;
        break;
    default:
        return false;
    }

    // 現在のフレーム数が比較対象を超えているか
    return targetFrame > comparisonFrame.Frame;
}