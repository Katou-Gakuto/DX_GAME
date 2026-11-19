#pragma once
#include <map>

#include "AttackEnum.h"

#include "ObjectBases.h"

enum class ATTACK_METHOD_TYPE;

enum class SHOT_TYPE
{
    DEFAULT = 0,
};

class Character_Shot : public CharacterBase
{
public:
    Character_Shot(bool nextSceneDeleteFlag, STATUS status, SHOT_TYPE shotType, std::map<ATTACK_METHOD_TYPE, CharacterAttackData> characterAttackData, std::map<ATTACK_METHOD_TYPE, AttackData> attackDatas);
    ~Character_Shot();

    /*攻撃リセット*/
    void StopAttack(ATTACK_METHOD_TYPE attackMethodType) override;

private:
    /*キャラクター初期化*/
    void CharacterInitilize() override;
    /*キャラクターシーン最終初期化*/
    void CharacterSceneLastInitilize() override;
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