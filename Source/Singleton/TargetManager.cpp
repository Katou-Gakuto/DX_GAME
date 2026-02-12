#include "BitFlag.h"

#include "ObjectBases.h"
#include "TargetData.h"
#include "TargetManager.h"


TargetManager::TargetManager()
: mstPlayer()
{
}

/*----------*/
/*【初期化】*/
/*----------*/

// 全初期化
void TargetManager::Init()
{
	mstPlayer = nullptr;
	mstEnemys.clear();
}

// 指定ターゲット初期化
void TargetManager::TargetInit(TARGET_TYPE targetNumber)
{
	switch (targetNumber)
	{
	case TARGET_TYPE::PLAYER:
		mstPlayer = nullptr;
		break;

	case TARGET_TYPE::ENEMY:
		mstEnemys.clear();
		break;
	}
}

// 指定ターゲット初期化
void TargetManager::TargetInit(BIT_FLAG<unsigned int> targetNumber)
{
	if (targetNumber.BIT_GET((int)TARGET_TYPE::PLAYER))
	{
		mstPlayer = CharacterTargetData();
	}
	if (targetNumber.BIT_GET((int)TARGET_TYPE::ENEMY))
	{
		mstEnemys.clear();
	}
}


/*--------*/
/*【削除】*/
/*--------*/

// 削除
void TargetManager::Delete(CharacterBase* character, TARGET_TYPE targetNumber)
{
	switch (targetNumber)
	{
	case TARGET_TYPE::ENEMY:
		for (int i = 0; i < mstEnemys.size(); i++)
		{
			if (mstEnemys[i].target->GetID() == character->GetID())
			{
				mstEnemys.erase(mstEnemys.begin() + i);
			}
		}
		break;
	}
}


/*--------*/
/*【設定】*/
/*--------*/

// ターゲット設定
void TargetManager::SetTarget(CharacterBase* target, TARGET_TYPE targetNumber)
{
	switch (targetNumber)
	{
	case TARGET_TYPE::PLAYER:
		mstPlayer = target;
		break;

	case TARGET_TYPE::ENEMY:
		mstEnemys.push_back(target);
		break;
	}
}

// ターゲット設定
void TargetManager::SetTarget(std::vector<CharacterTargetData> target, TARGET_TYPE targetNumber)
{
	switch (targetNumber)
	{
	case TARGET_TYPE::PLAYER:
		if (target.size() > 0)
		{
			mstPlayer = target[0];
		}
		break;

	case TARGET_TYPE::ENEMY:
		mstEnemys = target;
		break;
	}
}


/*--------*/
/*【取得】*/
/*--------*/

// ターゲット取得
CharacterTargetData TargetManager::GetTarget(TARGET_TYPE targetNumber)
{
	switch (targetNumber)
	{
	case TARGET_TYPE::PLAYER:
		return mstPlayer;
	case TARGET_TYPE::ENEMY:
		if (mstEnemys.size() <= 0)
		{
			return nullptr;
		}
		return mstEnemys[0];
	}

	return nullptr;
}

// ターゲット取得
std::vector<CharacterTargetData> TargetManager::GetTargets(TARGET_TYPE targetNumber)
{
	switch (targetNumber)
	{
	case TARGET_TYPE::PLAYER:
	{
		std::vector<CharacterTargetData> player = { mstPlayer };

		return player;
	}

	case TARGET_TYPE::ENEMY:
		return mstEnemys;
	}
	std::vector<CharacterTargetData> nullData;
	return nullData;
}