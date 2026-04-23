#include "Master.h"

#include "FadeManager.h"
#include "ResourceManager.h"
#include "StageDataManager.h"
#include "StopManager.h"
#include "TimeManager.h"

/*----------------------*/
/*【ストップマネージャー】*/
/*----------------------*/

StopManager::StopManager()
: mpFadeManager(nullptr)
, mpResourceManager(nullptr)
, mpStageDataManager(nullptr)
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

    mpResourceManager = Master::mpResourceManager;

    mpStageDataManager = Master::mpStageDataManager;

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

    case STOP_FLAG_TYPE::GAME_OBJECT_UI_DRAW:
        stopflag |= mpStageDataManager->GetStageStartPeriodFlag();
        break;

    case STOP_FLAG_TYPE::UI_OBJECT:
        stopflag |= mpFadeManager->GetFadeFlag();
        break;
    
    case STOP_FLAG_TYPE::UI_MODEL:
        stopflag |= mpResourceManager->GetShadowMapDrawFlag();
        break;

    case STOP_FLAG_TYPE::BACK_GROUND:
        stopflag |= mpResourceManager->GetShadowMapDrawFlag();
        break;
    }

    return stopflag;
}