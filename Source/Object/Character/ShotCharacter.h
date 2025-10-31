#pragma once
#include "ObjectBases.h"

class ShotCharacter : public CharacterBase
{
private:
    // カメラID
    int mnCameraID;

public:
    ShotCharacter(bool nextSceneDeleteFlag, STATUS status);
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
    CollisionData CharacterCheck(const CollisionData& collisionData) override;
};