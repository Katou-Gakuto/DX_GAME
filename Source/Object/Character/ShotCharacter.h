#pragma once
#include "ObjectBases.h"

enum class SHOT_TYPE
{
    DEFAULT = 0,
};

class ShotCharacter : public CharacterBase
{
public:
    ShotCharacter(bool nextSceneDeleteFlag, STATUS status, SHOT_TYPE shotType);
    ~ShotCharacter();

    /*攻撃リセット*/
    void StopAttack() override;

private:
    /*キャラクター初期化*/
    void CharacterInitilize() override;
    /*キャラクター終了*/
    void CharacterFinalize() override;

    /*キャラクター更新*/
    void CharacterUpdate() override;
    /*キャラクター最終更新*/
    void CharacterLastUpdate() override;

    /*キャラクター描画*/
    void CharacterDraw() override;

    /*当たり判定用*/
    void HitCheck(CollisionData& collisionData) override;
};