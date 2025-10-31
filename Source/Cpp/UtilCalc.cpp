#include <cmath>

#include "DxLib.h"

#include "../Header/UtilCalc.h"


// •ûŒü‚ð2‚©‚ç-2‚É‚È‚é‚æ‚¤‚É’²®‚·‚é
float UtilCalc::NotExceedAngle(float angle)
{
    if (angle > DX_PI_F) {
        angle -= DX_TWO_PI_F;
    }
    else if (angle < -DX_PI_F) {
        angle += DX_TWO_PI_F;
    }

    return angle;
}

// •ûŒü‚ð2‚©‚ç-2‚É‚È‚é‚æ‚¤‚É’²®‚·‚é(3•ûŒü)
VECTOR UtilCalc::VNotExceedAngle(VECTOR angle)
{
    if (angle.x > DX_PI_F) {
        angle.x -= DX_TWO_PI_F;
    }
    else if (angle.x < -DX_PI_F) {
        angle.x += DX_TWO_PI_F;
    }

    if (angle.y > DX_PI_F) {
        angle.y -= DX_TWO_PI_F;
    }
    else if (angle.y < -DX_PI_F) {
        angle.y += DX_TWO_PI_F;
    }

    if (angle.z > DX_PI_F) {
        angle.z -= DX_TWO_PI_F;
    }
    else if (angle.z < -DX_PI_F) {
        angle.z += DX_TWO_PI_F;
    }

    return angle;
}

// ‹…–ÊˆÚ“®‚µ‚½êŠ
VECTOR UtilCalc::VSphericalMovePos(float size, VECTOR angle)
{
    VECTOR pos = VGet(0.0f, 0.0f, 0.0f);

    pos.x = size * cosf(NotExceedAngle(angle.x)) * sinf(NotExceedAngle(angle.y));
    pos.y = size * sinf(NotExceedAngle(angle.x));
    pos.z = -(size * cosf(NotExceedAngle(angle.x)) * cosf(NotExceedAngle(angle.y)));

    return pos;
}