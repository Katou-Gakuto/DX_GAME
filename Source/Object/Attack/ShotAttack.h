#pragma once
#include "ObjectBases.h"

class ShotAttack : public AttackBase
{
public:
	ShotAttack();
	~ShotAttack();


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