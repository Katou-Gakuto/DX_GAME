#include "CameraData.h"

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