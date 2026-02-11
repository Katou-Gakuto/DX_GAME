#pragma once
#include "DxLib.h"

#include "ObjectBases.h"

class Attack_Shot : public AttackBase
{
private:
    // HACK: 攻撃情報にこれらを持たせる
    // 攻撃開始時間
    int mnAttackStartTime;

    // 設定用攻撃開始時間
    const int ATTACK_START_TIME = 1088;

    // 攻撃サイズ
    VECTOR mvAttackSize;

public:
    Attack_Shot();
	~Attack_Shot();


private:
    /*アタック初期化*/
    void AttackInitilize() override;
    /*アタック最終初期化*/
    void AttackLastInitilize() override;
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