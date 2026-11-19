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

	// ‘SUŒ‚ƒIƒuƒWƒFƒNƒg
	std::vector<AttackBase*> mstAllAttack;

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
	AttackBase* StartAttack(int attackDataNumber, ATTACK_METHOD_TYPE attackMethodType);

	/*UŒ‚’â~*/
	void StopAttack(int stopAttackNumber);

	/*íœİ’è*/
	void SetDelete();

	/// <summary>UŒ‚î•ñæ“¾</summary>
	inline AttackData GetAttacData(int attackNumber) { return mstAttackDatas[attackNumber]; }

	/// <summary>UŒ‚‘Sæ“¾</summary>
	std::vector<AttackBase*> GetAllAttack() { return mstAllAttack; }
};