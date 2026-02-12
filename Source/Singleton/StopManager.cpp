#include "Master.h"

#include "FadeManager.h"
#include "StopManager.h"
#include "TimeManager.h"

/*----------------------*/
/*【ストップマネージャー】*/
/*----------------------*/

StopManager::StopManager()
: mpFadeManager(nullptr)
, mpTimeManager(nullptr)
{
}

StopManager::~StopManager()
{
}

// 初期化
void StopManager::Initilize()
{
    mpFadeManager = Master::mpFadeManager;

    mpTimeManager = Master::mpTimeManager;
}

// ストップフラグ取得
bool StopManager::GetStopFlag(STOP_FLAG_TYPE stopType)
{
    bool stopflag = false;

    switch (stopType)
    {
    case STOP_FLAG_TYPE::NODE:
        stopflag |= mpFadeManager->GetFadeFlag();
        break;

    case STOP_FLAG_TYPE::GAME_OBJECT:
        stopflag |= mpTimeManager->GetStopFlag();
        stopflag |= mpFadeManager->GetFadeFlag();
        break;
    }

    return stopflag;
}