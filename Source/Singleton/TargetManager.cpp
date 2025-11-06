#include "ObjectBases.h"
#include "TargetManager.h"

TargetManager::TargetManager()
: mpPlayer(nullptr)
{
}

/*----------*/
/*y‰Šú‰»z*/
/*----------*/

/*‘S‰Šú‰»*/
void TargetManager::Init()
{
	mpPlayer = nullptr;
	mpEnemys.clear();
}

/*w’èƒ^[ƒQƒbƒg‰Šú‰»*/
void TargetManager::TargetInit(TARGET_NUMBER targetNumber)
{
	switch (targetNumber)
	{
	case TARGET_NUMBER::PLAYER:
		mpPlayer = nullptr;
		break;

	case TARGET_NUMBER::ENEMY:
		mpEnemys.clear();
		break;
	}
}


/*--------*/
/*yíœz*/
/*--------*/

/*íœ*/
void TargetManager::Delete(CharacterBase* character, TARGET_NUMBER targetNumber)
{
	switch (targetNumber)
	{
	case TARGET_NUMBER::ENEMY:
		for (int i = 0; i < mpEnemys.size(); i++)
		{
			if (mpEnemys[i]->GetID() == character->GetID())
			{
				mpEnemys.erase(mpEnemys.begin() + i);
			}
		}
		break;
	}
}


/*--------*/
/*yİ’èz*/
/*--------*/

// ƒ^[ƒQƒbƒgİ’è
void TargetManager::SetTarget(CharacterBase* target, TARGET_NUMBER targetNumber)
{
	switch (targetNumber)
	{
	case TARGET_NUMBER::PLAYER:
		mpPlayer = target;
		break;

	case TARGET_NUMBER::ENEMY:
		mpEnemys.push_back(target);
		break;
	}
}


/*--------*/
/*yæ“¾z*/
/*--------*/

// ƒ^[ƒQƒbƒgæ“¾
CharacterBase* TargetManager::GetTarget(TARGET_NUMBER targetNumber)
{
	switch (targetNumber)
	{
	case TARGET_NUMBER::PLAYER:
		return mpPlayer;
	case TARGET_NUMBER::ENEMY:
		if (mpEnemys.size() <= 0)
		{
			return nullptr;
		}
		return mpEnemys[0];
	}

	return nullptr;
}

// ƒ^[ƒQƒbƒgæ“¾
std::vector<CharacterBase*> TargetManager::GetTargets(TARGET_NUMBER targetNumber)
{
	switch (targetNumber)
	{
	case TARGET_NUMBER::PLAYER:
	{
		std::vector<CharacterBase*> player = { mpPlayer };

		return player;
	}

	case TARGET_NUMBER::ENEMY:
		return mpEnemys;
	}
}