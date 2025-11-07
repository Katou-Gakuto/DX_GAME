#include "BitFlag.h"

#include "ObjectBases.h"
#include "TargetManager.h"

TargetManager::TargetManager()
: mpPlayer(nullptr)
{
}

/*----------*/
/*【初期化】*/
/*----------*/

// 全初期化
void TargetManager::Init()
{
	mpPlayer = nullptr;
	mpEnemys.clear();
}

// 指定ターゲット初期化
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

// 指定ターゲット初期化
void TargetManager::TargetInit(BIT_FLAG<unsigned int> targetNumber)
{
	if (targetNumber.BIT_GET((int)TARGET_NUMBER::PLAYER))
	{
		mpPlayer = nullptr;
	}
	if (targetNumber.BIT_GET((int)TARGET_NUMBER::ENEMY))
	{
		mpEnemys.clear();
	}
}


/*--------*/
/*【削除】*/
/*--------*/

// 削除
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
/*【設定】*/
/*--------*/

// ターゲット設定
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
/*【取得】*/
/*--------*/

// ターゲット取得
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

// ターゲット取得
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