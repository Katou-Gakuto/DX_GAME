#include "ObjectBases.h"
#include "ShotAttack.h"

ShotAttack::ShotAttack(bool nextSceneDeleteFlag, CharacterBase* attackCharacter)
: AttackBase(nextSceneDeleteFlag, attackCharacter)
{
}

ShotAttack::~ShotAttack()
{
}