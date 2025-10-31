#pragma once
#include "ObjectBases.h"

class ShotAttack : public AttackBase
{
public:
	ShotAttack(bool nextSceneDeleteFlag, CharacterBase* attackCharacter);
	~ShotAttack();


};