#include "../Header/AttackManager.h"


AttackManager::AttackManager(ATTACK_TYPE attackType)
{
	mpAttacks.clear();

	switch (attackType)
	{
	case ATTACK_TYPE::SHOT:
		break;
	}
}

AttackManager::~AttackManager()
{
}

// アクティブ設定
void AttackManager::SetActive(bool activeFlaga)
{
}

// 削除設定
void AttackManager::SetDelete()
{
}