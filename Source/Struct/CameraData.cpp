#include "CameraData.h"

#include "ObjectBases.h"
#include "UtilCalc.h"

CameraData::CameraData()
{

	targetCharacter = nullptr;

	targetPosition = UtilCalc::VZero();
	position = UtilCalc::VZero();
	plusPosition = UtilCalc::VZero();
	angle = UtilCalc::VZero();

	twoDPosition = UtilCalc::VZero();

	cameraMode = CAMERA_MODE::NONE;

	red = 0;
	green = 0;
	blue = 0;
	alpha = 0;

	threeDFlag = true;

	cameraDistance = 250.0f;

	cameraID = -1;
}

// •ûŒüŽæ“¾
VECTOR CameraData::GetDirection()
{
	VECTOR direction = UtilCalc::VZero();

	switch (cameraMode)
	{
	case CAMERA_MODE::FIXED:
		direction = VSub(targetPosition, position);
		break;

	case CAMERA_MODE::CHARACTER:
		direction = VSub(targetCharacter->GetPos(), VAdd(VScale(UtilCalc::VSignInversion(targetCharacter->GetVec()), cameraDistance), targetCharacter->GetPos()));
		break;

	case CAMERA_MODE::PLAYER:
		direction = VSub(targetCharacter->GetPos(), VAdd(position, targetCharacter->GetPos()));
		break;
	}

	return direction;
}