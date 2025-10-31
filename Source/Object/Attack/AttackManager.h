#pragma once
#include <vector>

#include "ObjectBases.h"

/*攻撃種類*/
enum class ATTACK_TYPE
{
	SHOT = 0,
};

class AttackManager
{
private:
	std::vector<AttackBase*> mpAttacks;

public:
	AttackManager(ATTACK_TYPE attackType);
	~AttackManager();

	/*アクティブ設定*/
	void SetActive(bool activeFlaga);

	/*削除設定*/
	void SetDelete();
};