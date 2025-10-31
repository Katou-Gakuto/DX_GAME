#include "../Header/ObjectBases.h"
#include "../Header/ShotAttack.h"

ShotAttack::ShotAttack(bool nextSceneDeleteFlag, CharacterBase* attackCharacter)
: AttackBase(nextSceneDeleteFlag, attackCharacter)
{
}

ShotAttack::~ShotAttack()
{
}