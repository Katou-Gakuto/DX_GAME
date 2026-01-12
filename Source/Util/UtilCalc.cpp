#include <cmath>

#include "DxLib.h"

#include "UtilCalc.h"


// •ûŒü‚ğ2‚©‚ç-2‚É‚È‚é‚æ‚¤‚É’²®‚·‚é
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

// •ûŒü‚ğ2‚©‚ç-2‚É‚È‚é‚æ‚¤‚É’²®‚·‚é(3•ûŒü)
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

// ˆÚ“®—Ê‚ğƒAƒ“ƒOƒ‹‚É”½‰f‚µ‚½’l‚ğ•Ô‚·
VECTOR UtilCalc::VMoveVecToAngle(VECTOR moveVec, VECTOR angle, float speed)
{
    float targetAngle = atan2f(moveVec.x, moveVec.z);
    float diffAngle = targetAngle - angle.y;
    diffAngle = NotExceedAngle(diffAngle);

    // Šp“x‚Ì·‚ğ0‚É‹ß‚Ã‚¯‚é
    if (diffAngle > 0.0f)
    {
        diffAngle -= speed;
        if (diffAngle < 0.0f)
        {
            diffAngle = 0.0f;
        }
    }
    else
    {
        diffAngle += speed;
        if (diffAngle > 0.0f)
        {
            diffAngle = 0.0f;
        }
    }

    return VGet(angle.x, targetAngle - diffAngle, angle.z);
}

/*--------------*/
/*y“–‚½‚è”»’èz*/
/*--------------*/

// ‹…“¯m‚Ì“–‚½‚è”»’è
bool UtilCalc::SphereCollision(VECTOR srcPos, float srcRadius, VECTOR dstPos, float dstRadius)
{
    //‰~‚Ì“–‚½‚è”»’è‚ğs‚¤
    VECTOR diff = VSub(dstPos, srcPos);
    float distance = VSize(diff);

    if (distance < (srcRadius + dstRadius))
    {
        return true;
    }
    return false;
}

//// lŠp“¯m‚Ì“–‚½‚è”»’è
//bool UtilCalc::BoxCollision(VECTOR srcTopRight, VECTOR srcBottomLeft, VECTOR dstTopRight, VECTOR dstBottomLeft)
//{
//    if ()
//    {
//
//    }
//    ele
//    {
//
//    }
//}