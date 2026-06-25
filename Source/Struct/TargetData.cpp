#include "TargetData.h"

#include "Master.h"

#include "GameManager.h"
#include "MapManager.h"
#include "ObjectBases.h"

CharacterTargetData::CharacterTargetData()
{
	target = nullptr;
	mapPosX = 0;
	mapPosZ = 0;
}

CharacterTargetData::CharacterTargetData(CharacterBase* src)
{
	target = src;
	Master::mpGameManager->GetMapManager()->GetMapPos(mapPosX, mapPosZ, src->GetPos());
	
}