#include "CollisionData.h"

#include "DxLib.h"

#include "UtilCalc.h"

CollisionData::CollisionData()
: position(UtilCalc::VZero)
, vec(UtilCalc::VZero)
, speed(0.0f)
, size(0.0f)
, collisionFlag(false)
, objID(-1)
, collisionType(COLLISION_TYPE::NONE)
{
}