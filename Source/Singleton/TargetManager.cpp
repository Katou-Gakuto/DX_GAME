#include "ObjectBases.h"
#include "TargetManager.h"

TargetManager::TargetManager()
: mpPlayer(nullptr)
{
}

/*--------*/
/*yİ’èz*/
/*--------*/

/*ƒ^[ƒQƒbƒgİ’è*/
void TargetManager::SetTarget(CharacterBase* target, TARGET_NUMBER targetNumber)
{
	switch (targetNumber)
	{
	case TARGET_NUMBER::PLAYER:
		mpPlayer = target;
		break;
	}
}

/*--------*/
/*yæ“¾z*/
/*--------*/

/*ƒ^[ƒQƒbƒgæ“¾*/
CharacterBase* TargetManager::GetTarget(TARGET_NUMBER targetNumber)
{
	switch (targetNumber)
	{
	case TARGET_NUMBER::PLAYER:
		return mpPlayer;
	}

	return nullptr;
}