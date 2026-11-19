#pragma once
#include <vector>
#include "TimeData.h"

#include "ObjectBases.h"

class Attack_RobotSpceial : public AttackBase
{
public:
    Attack_RobotSpceial();
	~Attack_RobotSpceial();

    // 前回攻撃ヒット時間
    std::vector<TIME_DATA> munPreCharacterHitTime;

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