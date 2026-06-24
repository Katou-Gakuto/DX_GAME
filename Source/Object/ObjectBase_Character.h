#pragma once
#include <map>
#include <vector>

#include "AttackEnum.h"
#include "AnimationData.h"
#include "AttackData.h"
#include "BitFlag.h"
#include "CollisionData.h"
#include "DrawData.h"
#include "Status.h"

#include "DxLib.h"

#include "AnimationBase.h"
#include "ModelsControllerBase.h"
#include "ObjectBase.h"

class AttackBase;
class FSMCharacter;

/*--------------------------------------------------------*/
/*               【キャラクターベース関係】               */
/*--------------------------------------------------------*/

/*------------------------------------------------*/
/*          【キャラクターベース用enum】          */
/*------------------------------------------------*/

// 行動フラグ
enum class ACTION_FLAG
{
    // MAX                  0b0000'0000'0000'0000'0000'0000'0000'0000

    /*上下移動*/
    //UP_OR_DOWN_ACTION =   0b000'000'000'001u,
    /*上移動*/
    UP_ACTION =             0b000'000'000'011u,
    /*下移動*/
    DOWN_ACTION =           0b000'000'000'101u,

    /*右左移動*/
    //LEFT_OR_RIGHT_ACTION= 0b000'000'001'000u,
    /*右移動*/
    RIGHT_ACTION =          0b000'000'011'000u,
    /*左移動*/
    LEFT_ACTION =           0b000'000'101'000u,

    /*前後移動*/
    //FRONT_OR_BACK_ACTION= 0b000'001'000'000u,
    /*前移動*/
    FRONT_ACTION =          0b000'011'000'000u,
    /*後ろ移動*/
    BACK_ACTION =           0b000'101'000'000u,

    /*HPが0以下*/
    HP_ZERO =               0b001'000'000'000u,

    /*ダッシュ*/
    DASH =                  0b010'000'000'000u,

    /*ジャンプ*/
    JUMP =                  0b100'000'000'000u,
};

// 確認用行動フラグ
enum class CHECK_ACTION_FLAG
{
    // MAX 31

    /*上下移動*/
    UP_OR_DOWN_ACTION = 0,
    /*上移動*/
    UP_ACTION,
    /*下移動*/
    DOWN_ACTION,

    /*右左移動*/
    LEFT_OR_RIGHT_ACTION,
    /*右移動*/
    RIGHT_ACTION,
    /*左移動*/
    LEFT_ACTION,

    /*前後移動*/
    FRONT_OR_BACK_ACTION,
    /*前移動*/
    FRONT_ACTION,
    /*後ろ移動*/
    BACK_ACTION,

    /*HPが0以下*/
    HP_ZERO,

    /*ダッシュ*/
    DASH,

    /*ジャンプ*/
    JUMP,
};

/*------------------------------------------*/
/*          【キャラクターベース】          */
/*------------------------------------------*/
;// TODO: 消す
class CharacterBase : public ObjectBase
{
public:
    enum class CHARACTER_OBJECT_BIT_FLAG_NUBER
    {
        INVINCIBLE = ObjectBase::OBJECT_BIT_FLAG_NUBER::OBJECT_BIT_MAX,
        CHARACTER_OBJECT_BIT_MAX
    };

    // 摩擦種類
    enum FRICTION_TYPE
    {
        GROUND = 0,
        SKY,
        MAX
    };

protected:
    // 前のポジション
    VECTOR mvOldPosition;

    // ポジション
    VECTOR mvPosition;

    // 移動方向
    VECTOR mvMoveDir;

    // 移動量
    VECTOR mvVec;

    // モデル向き
    VECTOR mvAngle;

    // ステータス
    STATUS mstStatus;

    // キャラクター有限状態マシン
    FSMCharacter* mpFsm;

    // モデルベース
    ModelsControllerBase* mpModelController;

    // アニメションベース
    AnimationBase* mpAnimation;

    // 行動フラグ
    BIT_FLAG<unsigned int> munActionflags;

    // 攻撃設定情報達
    std::map<ATTACK_METHOD_TYPE, CharacterAttackData> mmCharacterAttackDatas;

    // 攻撃オブジェクト
    AttackBase* mpAttack;

    // ステート用描画情報
    std::vector<DRAW_DATA> mstStateDrawData;

	// 重力 // TODO: マップで掛ける
	static constexpr float CHARACTER_GRAVITY = 0.147f;

    // 摩擦
    static constexpr float CHARACTER_FRICTION[FRICTION_TYPE::MAX] = 
    {
        0.02f,
        0.15f
    };

    // ジャンプ力
    static constexpr float JUMP_POWER = 1.0f;
    
    // 地面フラグ
    bool mbGroundFlag;

    // 運動速度
    VECTOR mvVelocity;
    // 上方向ベクトル保存用
    VECTOR mvUpVec;

public:
    CharacterBase(bool nextSceneDeleteFlag, STATUS status);
    ~CharacterBase();

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

public:
    /*攻撃開始(反動時間を返す)*/
    virtual void StartAttck(ATTACK_METHOD_TYPE attackMethodType);

    /*攻撃停止*/
    virtual void StopAttack(ATTACK_METHOD_TYPE attackMethodType);
    
    /// <summary>指定アニメーション中であるかを取得</summary>
    /// <returns>指定のアニメーションなら「true」を返す</returns>
    bool CheckAnimationType(ANIMATION_TYPE animationType);

    /*ダメージ*/
    virtual void Damage(int damage);

    /// <summary>移動処理(移動位置確認用にも使う)</summary>
    virtual VECTOR MoveProcess(VECTOR* position = nullptr);

protected:
    /*キャラクター初期化*/
    virtual void CharacterInitilize() = 0;
    /*キャラクターシーン最終初期化*/
    virtual void CharacterSceneLastInitilize() = 0;
    /*キャラクター終了*/
    virtual void CharacterFinalize() = 0;

    /*キャラクター更新*/
    virtual void CharacterUpdate() = 0;
    /*キャラクター最終更新*/
    virtual void CharacterLastUpdate() = 0;

    /*キャラクター描画*/
    virtual void CharacterDraw() = 0;

    /*行動処理*/
    virtual void ActionProcess() { TemplateActionProcess(); }

    /*定型行動処理*/
    void TemplateActionProcess();

    /*死亡処理*/
    virtual void DeathProcess();

    /*提携アニメーション処理*/
    void TemplateAnimationProcess();

public:

    /*--------*/
    /*【取得】*/
    /*--------*/

    /*ステータス取得*/
    inline STATUS* GetStatus() { return &mstStatus; }

    /*ポジション取得*/
    inline VECTOR GetPos() const { return mvPosition; }

    /*移動予定地点*/
    inline VECTOR GetMovePos() const { return VAdd(mvPosition, VScale(mvVec, (float)mstStatus.GetNowSpeed())); }

    /*前のポジション取得*/
    inline VECTOR GetOldPos() const { return mvOldPosition; }

    /*移動方向取得*/
    inline VECTOR GetMoveDir() const { return mvMoveDir; }

    /*移動量取得*/
    inline VECTOR GetVec() const { return mvVec; }

    /*方向取得*/
    inline VECTOR GetAngle() const { return mvAngle; }

    /*サイズ取得*/
    inline VECTOR GetSize() const { return mpModelController->GetModelSize(); }

    /*平均サイズ取得*/
    inline float GetAverageSize() const { return (mpModelController->GetModelSize().x + mpModelController->GetModelSize().y + mpModelController->GetModelSize().z) / 3.0f; }

    /// <summary>モデルコントローラー取得</summary>
    /// <returns>モデルコントローラー</returns>
    inline ModelsControllerBase* GetModelsController() { return mpModelController; }

    /// <summary>アニメションベース取得</summary>
    /// <returns>アニメションベース</returns>
    inline AnimationBase* GetAnimation() { return  mpAnimation; }

    
    /// <summary>攻撃用モデルコントローラー取得</summary>
    /// <returns>モデルコントローラー</returns>
    inline ModelsControllerBase* GetAttackModelsController(ATTACK_METHOD_TYPE attackMethodType) { return mmCharacterAttackDatas[attackMethodType].modelController; }

    /// <summary>攻撃用アニメションベース取得</summary>
    /// <returns>アニメションベース</returns>
    inline AnimationBase* GetAttackAnimation(ATTACK_METHOD_TYPE attackMethodType) { return  mmCharacterAttackDatas[attackMethodType].animation; }

    /// <summary>キャラクターがした攻撃取得</summary>
    /// <returns>攻撃オブジェクト</returns>
    AttackBase* GetAttack();

    /// <summary>ステート用描画情報取得</summary>
    std::vector<DRAW_DATA> GetStateDrawData() { return mstStateDrawData; }

    /*--------*/
    /*【設定】*/
    /*--------*/

    /*fsm設定*/
    void SetFSM(FSMCharacter* fsm);

    /// <summary>アニメーション設定</summary>
    void SetAnimation(ANIMATION_TYPE animationType);

    /*ポジション設定*/
    inline void SetPos(const VECTOR& pos) { mvPosition = pos; }
    /*移動方向設定*/
    inline void SetMoveDir(const VECTOR& moveDir) { mvMoveDir = moveDir; }
    /*移動量設定*/
    inline void SetVec(const VECTOR& vec) { mvVec = vec; }
    /*方向設定*/
    inline void SetAngle(const VECTOR& angle) { mvAngle = angle; }
    
    /// <summary>ステート用描画情報設定</summary>
    inline void SetStateDrawData(std::vector<DRAW_DATA> drawDatas) { mstStateDrawData = drawDatas; }

    /*上移動設定*/
    inline void SetUpMove() { munActionflags.SetXorBit(ACTION_FLAG::UP_ACTION); }
    /*下移動設定*/
    inline void SetDownMove() { munActionflags.SetXorBit(ACTION_FLAG::DOWN_ACTION); }

    /*右移動設定*/
    inline void SetRightMove() { munActionflags.SetXorBit(ACTION_FLAG::RIGHT_ACTION); }
    /*左移動設定*/
    inline void SetLeftMove() { munActionflags.SetXorBit(ACTION_FLAG::LEFT_ACTION); }

    /*前移動設定*/
    inline void SetFrontMove() { munActionflags.SetXorBit(ACTION_FLAG::FRONT_ACTION); }
    /*後ろ移動設定*/
    inline void SetBackMove() { munActionflags.SetXorBit(ACTION_FLAG::BACK_ACTION); }

    /*ジャンプ設定*/
    inline void SetJump() { munActionflags.SetXorBit(ACTION_FLAG::JUMP); }

    /*HPが0以下のフラグを設定*/
    inline void SetHPZero() { munActionflags.SetOrBit(ACTION_FLAG::HP_ZERO); }

    /// <summary>行動フラグ設定</summary>
    inline void SetMoveActionFlag(ACTION_FLAG flagBit) { munActionflags.SetXorBit(flagBit); }

    /// <summary>オブジェクトビットフラグ設定</summary>
    inline void SetObjectBitFlag(bool flag, CHARACTER_OBJECT_BIT_FLAG_NUBER bitNumber) { mullFlags.SetFlag(flag, bitNumber); }
};