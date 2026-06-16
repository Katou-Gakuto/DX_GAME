#pragma once
#include <vector>

#include "CollisionData.h"
#include "TimeData.h"

#include "DxLib.h"

#include "AnimationBase.h"
#include "ModelsControllerBase.h"
#include "ObjectBase.h"
#include "ObjectBase_Character.h"

/*----------------------------------------------------*/
/*               【アタックベース関係】               */
/*----------------------------------------------------*/

/*--------------------------------------*/
/*          【アタックベース】          */
/*--------------------------------------*/

class AttackBase : public ObjectBase
{
public:
    enum class ATTACK_OBJECT_BIT_FLAG_NUBER
    {
        ATTACK_OBJECT_BIT_MAX = ObjectBase::OBJECT_BIT_FLAG_NUBER::OBJECT_BIT_MAX
    };

protected:
    // ポジション
    VECTOR mvPosition;

    // パワー
    int mnPower;

    // 攻撃キャラクター
    CharacterBase* mpAttackCharacter;

    // 当たったキャラクター
    std::vector<int> mnHiObjID;

    // 移動方向
    VECTOR mvMoveDir;

    // 向き
    VECTOR mvAngle;

    //fsm

    // モデルベース
    ModelsControllerBase* mpModelController;

    // アニメションベース
    AnimationBase* mpAnimation;

    // 攻撃ナンバー
    int mnAttackNumber;

    //// 攻撃反動時間
    //int mnAttackRecoilTime;

    // 攻撃時間
    TIME_DATA mstAttackTime;

public:
    AttackBase();
    ~AttackBase();

    /*初期化*/
    void Initilize() override final;
    /// <summary>シーン最終初期化</summary>
    void SceneLastInitilize() override final;
    /*終了*/
    void Finalize() override final;
    /*更新*/
    void Update() override final;
    /*最終更新*/
    void LastUpdate() override final;
    /*描画*/
    void Draw() override final;

    /*当たり判定*/
    void HitCheck(CollisionData& collisionData) override = 0;

    /*----------------------*/
    /*     【独自処理】     */
    /*----------------------*/

protected:
    /*アタック初期化*/
    virtual void AttackInitilize() = 0;
    /*アタックシーン最終初期化*/
    virtual void AttackSceneLastInitilize() = 0;
    /*アタック終了*/
    virtual void AttackFinalize() = 0;
    /*アタック更新*/
    virtual void AttackUpdate() = 0;
    /*アタック最終更新*/
    virtual void AttackLastUpdate() = 0;
    /*アタック描画*/
    virtual void AttackDraw() = 0;

    /*--------*/
    /*【設定】*/
    /*--------*/

public:
    /*攻撃キャラクター設定*/
    inline void SetAttackCharacter(CharacterBase* character) { mpAttackCharacter = character; }
    
    /*攻撃ナンバー設定*/
    inline void SetAttackNumber(int number) { mnAttackNumber = number; }

    /*攻撃時間設定*/
    inline void SetAttackTime(TIME_DATA time) { mstAttackTime = time; }

    /*移動方向設定*/
    inline void SetMoveDir(VECTOR moveDir) { mvMoveDir = moveDir; }

    /*攻撃力設定*/
    inline void SetAttackPower(int power) { mnPower = power; }

    /// <summary>モデルコントローラー設定</summary>
    inline void SetModelController(ModelsControllerBase* modelsController) { mpModelController = modelsController; }

    /// <summary>アニメション設定</summary>
    inline void SetAnimation(AnimationBase* animation) { mpAnimation = animation; }

    /*--------*/
    /*【取得】*/
    /*--------*/

public:
    /// <summary>攻撃キャラクター取得</summary>
    /// <returns>キャラクター</returns>
    inline CharacterBase* GetAttackCharacter() { return mpAttackCharacter; }

    /*攻撃ナンバー取得*/
    inline int GetAttackNumber() const { return mnAttackNumber; }

    ///*攻撃反動時間取得*/
    //inline int GetAttackRecoilTime() const { return mnAttackRecoilTime; }

    /*パワー取得*/
    inline int GetAttackPower()const { return mnPower; }

    /// <summary>モデルコントローラー取得</summary>
    inline ModelsControllerBase* GetModelsController() { return mpModelController; }

    /// <summary>アニメーション取得</summary>
    inline AnimationBase* GetAnimation() { return mpAnimation; }
};