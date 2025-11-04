#pragma once
#include <map>
#include <vector>

#include "AttackData.h"

#include "ObjectBases.h"

/*UŒ‚í—Ş*/
enum class ATTACK_TYPE;

class AttackManager
{
private:
	// UŒ‚ƒIƒuƒWƒFƒNƒg
	std::map<ATTACK_TYPE, std::vector<AttackBase*>> mmAttacks;

	// UŒ‚î•ñ
	std::vector<AttackData> mstAttackDatas;

public:
	AttackManager();
	~AttackManager();

	/*UŒ‚ì¬*/
	void CreateAttack(ATTACK_TYPE attackType);

	/*UŒ‚î•ñİ’è*/
	int SetAttackData(AttackData attackData);

	/*UŒ‚ŠJn*/
	int StartAttack(int attackDataNumber);

	/*UŒ‚’â~*/
	void StopAttack(int stopAttackNumber);

	/*íœİ’è*/
	void SetDelete();
};