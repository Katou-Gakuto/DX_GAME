#pragma once
#include <map>
#include <vector>

#include "AttackData.h"

#include "ObjectBases.h"

/*攻撃種類*/
enum class ATTACK_TYPE;

class AttackManager
{
private:
	// 攻撃オブジェクト
	std::map<ATTACK_TYPE, std::vector<AttackBase*>> mmAttacks;

	// 全攻撃オブジェクト
	std::vector<AttackBase*> mstAllAttack;

	// 攻撃情報
	std::vector<AttackData> mstAttackDatas;

public:
	AttackManager();
	~AttackManager();

	/*攻撃作成*/
	void CreateAttack(ATTACK_TYPE attackType);

	/*攻撃情報設定*/
	int SetAttackData(AttackData attackData);

	/*攻撃開始*/
	int StartAttack(int attackDataNumber, ATTACK_METHOD_TYPE attackMethodType);

	/*攻撃停止*/
	void StopAttack(int stopAttackNumber);

	/*削除設定*/
	void SetDelete();
};