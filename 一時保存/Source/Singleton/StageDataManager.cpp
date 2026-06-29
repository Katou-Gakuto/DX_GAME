#include "StageDataManager.h"


StageDataManager::StageDataManager()
: mbStageStartPeriodFlag(false)
{
}

StageDataManager::~StageDataManager()
{
}

void StageDataManager::Init()
{
	mbStageStartPeriodFlag = false;
}