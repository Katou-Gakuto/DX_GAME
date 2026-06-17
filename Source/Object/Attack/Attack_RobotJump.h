#pragma once
#include "ObjectBase_Attack.h"

class Attack_RobotJump : public AttackBase
{
public:
    Attack_RobotJump();
	~Attack_RobotJump();


private:
    /*アタック初期化*/
    void AttackInitilize() override;
    /*アタックシーン最終初期化*/
    void AttackSceneLastInitilize() override;
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