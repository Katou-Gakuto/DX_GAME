#pragma once
#include "ObjectBases.h"

class Attack_RobotSpceial : public AttackBase
{
public:
    Attack_RobotSpceial();
	~Attack_RobotSpceial();


private:
    /*アタック初期化*/
    void AttackInitilize() override;
    /*アタック終了*/
    void AttackFinalize() override;
    /*アタック更新*/
    void AttackUpdate() override;
    /*アタック最終更新*/
    void AttackLastUpdate() override;
    /*アタック描画*/
    void AttackDraw() override;

    /*当たり判定*/
    void HitCheck(CollisionData& collisionData) override;
};