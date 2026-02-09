#include <windows.h>

#include "DxLib.h"

#include "TimeManager.h"

// コンストラクタ
TimeManager::TimeManager(int oneFrameTime)
: munFrameCount(0)
, munStartTime(0)
, munPreviousTime(0)
, munStopTime(0)
, mbStopFlag(false)
, munOneFrame(oneFrameTime)
, mbNewSceneTimeFlag(false)
{
}
// デストラクタ
TimeManager::~TimeManager()
{
}
// 初期化
void TimeManager::Initilize()
{
    timeBeginPeriod(1); // タイマーの分解量の設定を1msにする (1ミリ秒/1000秒)にする
    munStartTime = timeGetTime();
}

// 更新
bool TimeManager::GetNextUpdateFlag()
{

    ErrorLogFmtAdd("時間: %ld", timeGetTime());
    int nowTime = timeGetTime();
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

        return true;

    }

    return false;
}