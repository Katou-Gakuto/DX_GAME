#include <windows.h>

#ifdef _DEBUG
#include <map>
#endif

#include "DxLib.h"

#include "TimeManager.h"

// コンストラクタ
TimeManager::TimeManager(int oneFrameTime)
: munLowestOneFrameSeconds(oneFrameTime)
, munNextProcessingSeconds(0)
, mstStartTime(TIME_DATA())
, mstPreviousTime(TIME_DATA())
, mstStopTime(TIME_DATA())
, mfTimeScale(1.0f)
, mstDeltaTime(TIME_DATA())
, mstElapsedTime(TIME_DATA())
, mstFrameCount(FRAME_DATA())
, mstGameElapsedTime(TIME_DATA())
, mstGameFrameNumber(FRAME_DATA())
, mstSceneElapsedFrame(FRAME_DATA())
, mstBackgroundTime(TIME_DATA())
, mbStopFlag(false)
, mbNewSceneTimeFlag(false)
, mnTimeResetFlag(0)
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
    munNextProcessingSeconds = mstStartTime.Time + munLowestOneFrameSeconds;
}

// 更新
bool TimeManager::GetNextUpdateFlag()
{
    unsigned long nowTime = timeGetTime();
 
    // 0になった場合の処理
    if (munPreviousTime > nowTime)
    {
        munPreviousTime = 0;
        mnTimeResetFlag += 1;
    }

    // 時間経過処理
    if ((munPreviousTime + munOneFrame) <= nowTime)
    {
        munFrameCount += 1;

        if (mbStopFlag) {
            munStopTime += (nowTime - munPreviousTime);
            if (mbNewSceneTimeFlag) {
                mbNewSceneTimeFlag = false;
            }
        }
        else if (mbNewSceneTimeFlag) {
            munStopTime += ((nowTime - munPreviousTime) - munOneFrame);
            mbNewSceneTimeFlag = false;
        }

        munPreviousTime = nowTime;

#ifdef _DEBUG
        mmForPastFrameSecondsSave[mstPreviousTime.Time - nowTime];
#endif

        return true;

    }

    return false;
}