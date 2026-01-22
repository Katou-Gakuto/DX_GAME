#pragma once
#include "AttackEnum.h"

class CharacterBase;

// UŒ‚î•ñİ’è—pî•ñ
struct AttackData
{
	CharacterBase* attackCharacter;	// UŒ‚ƒLƒƒƒ‰ƒNƒ^[

	ATTACK_TYPE attackType;	// UŒ‚í—Ş

	int attackTime;	// UŒ‚ŠÔ

	int attackPower; // UŒ‚—Í
};