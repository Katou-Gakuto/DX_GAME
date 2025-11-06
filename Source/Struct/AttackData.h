#pragma once
class CharacterBase;

// UŒ‚í—Ş
enum class ATTACK_TYPE
{
	SHOT = 0,
};

// UŒ‚î•ñİ’è—pî•ñ
struct AttackData
{
	CharacterBase* attackCharacter;	// UŒ‚ƒLƒƒƒ‰ƒNƒ^[

	ATTACK_TYPE attackType;	// UŒ‚í—Ş

	int attackTime;	// UŒ‚ŠÔ

	int attackPower; // UŒ‚—Í
};