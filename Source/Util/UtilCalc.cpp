#include <cmath>

#include "DxLib.h"

#include "UtilCalc.h"


// 方向を2から-2になるように調整する
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

// 方向を2から-2になるように調整する(3方向)
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

// 球面移動した場所
VECTOR UtilCalc::VSphericalMovePos(float size, VECTOR angle)
{
    VECTOR pos = VAngleToVec(angle);
    pos.z = -pos.z;
    // pos.x = size * cosf(NotExceedAngle(angle.x)) * sinf(NotExceedAngle(angle.y));
    // pos.y = size * sinf(NotExceedAngle(angle.x));
    // pos.z = -(size * cosf(NotExceedAngle(angle.x)) * cosf(NotExceedAngle(angle.y)));
    return VScale(pos, size);
}

//　ベクトルをアングルに変換する
VECTOR UtilCalc::VVecToAngle(VECTOR vec)
{
    VECTOR angle;
    angle.x = 0.0f;
    angle.y = atan2f(vec.x, vec.z);
    angle.z = 0.0f;
    return angle;
}

// アングルをベクトルに変換する
VECTOR UtilCalc::VAngleToVec(VECTOR angle)
{
    VECTOR vec;
    vec.x = cosf(NotExceedAngle(angle.x)) * sinf(NotExceedAngle(angle.y));
    vec.y = sinf(NotExceedAngle(angle.x));
    vec.z = cosf(NotExceedAngle(angle.x)) * cosf(NotExceedAngle(angle.y));
    return VNorm(vec);
}

// 移動量をアングルに反映した値を返す
VECTOR UtilCalc::VMoveVecToAngle(VECTOR moveVec, VECTOR angle, float speed)
{
    float targetAngle = VVecToAngle(moveVec).y;
    float diffAngle = targetAngle - angle.y;
    diffAngle = NotExceedAngle(diffAngle);

    // 角度の差を0に近づける
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
/*【当たり判定】*/
/*--------------*/

// 球同士の当たり判定
bool UtilCalc::SphereCollision(VECTOR srcPos, float srcRadius, VECTOR dstPos, float dstRadius)
{
    //円の当たり判定を行う
    VECTOR diff = VSub(dstPos, srcPos);
    float distance = VSize(diff);

    if (distance < (srcRadius + dstRadius))
    {
        return true;
    }
    return false;
}

//// 四角同士の当たり判定
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