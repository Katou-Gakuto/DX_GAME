#pragma once
#include <list>
#include <string>
#include <map>
#include <vector>

#include "AttackData.h"
#include "BitFlag.h"
#include "CollisionData.h"
#include "DrawData.h"
#include "Status.h"
#include "TimeData.h"
#include "ResourceData.h"// TODO: 消す

#include "DxLib.h"

#include "AnimationBase.h"
#include "KeyState.h"
#include "ModelsControllerBase.h"
#include "ResourceManager.h"
#include "TimeManager.h"

enum class ATTACK_METHOD_TYPE;
enum class LOAD_ANIMATION_DATA_FACTORY_NUMBER;
enum class MODEL_TYPE;
enum class SCENE;

class AttackBase;
class FSMAnimation;
class FSMCharacter;
class FSMUI;

class ObjectBase;
#ifdef _DEBUG
bool DEBUG_OBJECT_POINT_CHECK(void* p, bool check = false);
#endif

/*--------------------------------------------------------*/
/*               【オブジェクトベース関連】               */
/*--------------------------------------------------------*/

/*------------------------------------------------*/
/*          【オブジェクトベース用enum】          */
/*------------------------------------------------*/
;
// オブジェクトタイプ
enum class OBJECT_TYPE
{
    BASE = 0,
    CHARACTER_BASE,
    BUILDING_BASE,
    ATTACK_BASE,
    UI_BASE
};

/*------------------------------------------*/
/*          【オブジェクトベース】          */
/*------------------------------------------*/

class ObjectBase
{
public:
    enum class OBJECT_BIT_FLAG_NUBER
    {
        OBJECT_BIT_MAX = 0
    };

private:
    // 前オブジェクトへのポインタ
    ObjectBase* mpPrevObject;
    // 次オブジェクトへのポインタ
    ObjectBase* mpNextObject;

    // 継承したクラスと同タイプの前オブジェクトへのポインタ
    ObjectBase* mpInheritClassPrevObject;
    // 継承したクラスと同タイプの次オブジェクトへのポインタ
    ObjectBase* mpInheritClassNextObject;

    // 削除フラグ
    bool mbIsDeleteFlag;
    // 有効フラグ
    bool mbIsActiveFlag;

    // 次のシーン削除するフラグ
    bool mbNextSceneDeleteFlag;

    // 識別タグ
    std::string mnTag;
    // チーム
    int mnTeam;
    // 個別ナンバー
    unsigned int munID;

    // オブジェクトの種類
    OBJECT_TYPE meObjectType;

protected:
    // 生成されたシーン
    SCENE meObjectScene;

    // フラグ
    BIT_FLAG<unsigned long long> mullFlags;

public:

    /*コンストラクタ*/
    ObjectBase(OBJECT_TYPE objectType, bool isActiveFlag, bool nextSceneDeleteFlag);
    /*デストラクタ*/
    ~ObjectBase();

    /*初期化*/
    virtual void Initilize() = 0;
    /// <summary>シーン最終初期化</summary>
    virtual void SceneLastInitilize() = 0;
    /*終了*/
    virtual void Finalize() = 0;
    /*更新*/
    virtual void Update() = 0;
    /*最終更新*/
    virtual void LastUpdate() = 0;
    /*描画*/

    virtual void Draw() = 0;
#ifdef _DEBUG
    /*前オブジェクトへのポインタ取得*/
    inline ObjectBase* GetPrevObject(bool allBaseFlag = true) {

        if (DEBUG_OBJECT_POINT_CHECK(allBaseFlag ? mpPrevObject : mpInheritClassPrevObject))
        {
            if (allBaseFlag)
            {
                mpPrevObject = reinterpret_cast<ObjectBase*>(reinterpret_cast<uintptr_t>(mpPrevObject) | (reinterpret_cast<uintptr_t>(mpInheritClassPrevObject) & 0xffff'ffff'0000'0000u));
            }
            else
            {
                mpInheritClassPrevObject = reinterpret_cast<ObjectBase*>(reinterpret_cast<uintptr_t>(mpInheritClassPrevObject) | (reinterpret_cast<uintptr_t>(mpPrevObject) & 0xffff'ffff'0000'0000u));
            }
        }

   

        return allBaseFlag ? mpPrevObject : mpInheritClassPrevObject;
    }
    /*次オブジェクトへのポインタ取得*/
    inline ObjectBase* GetNextObject(bool allBaseFlag = true) {

        if (DEBUG_OBJECT_POINT_CHECK(allBaseFlag ? mpNextObject : mpInheritClassNextObject))
        {
            if (allBaseFlag)
            {
                mpNextObject = reinterpret_cast<ObjectBase*>(reinterpret_cast<uintptr_t>(mpNextObject) | (reinterpret_cast<uintptr_t>(mpInheritClassNextObject) & 0xffff'ffff'0000'0000u));
            }
            else
            {
                mpInheritClassNextObject = reinterpret_cast<ObjectBase*>(reinterpret_cast<uintptr_t>(mpInheritClassNextObject) | (reinterpret_cast<uintptr_t>(mpNextObject) & 0xffff'ffff'0000'0000u));
            }
        }


        return allBaseFlag ? mpNextObject : mpInheritClassNextObject;
    }
    /*前オブジェクトのポインタを設定する*/
    inline void SetPrevObject(ObjectBase* object, bool allBaseFlag = true) { DEBUG_OBJECT_POINT_CHECK(object, true); if (allBaseFlag) { mpPrevObject = object; } else { mpInheritClassPrevObject = object; } }
    /*次オブジェクトのポインタを設定する*/
    inline void SetNextObject(ObjectBase* object, bool allBaseFlag = true) { DEBUG_OBJECT_POINT_CHECK(object, true); if (allBaseFlag) { mpNextObject = object; } else { mpInheritClassNextObject = object; } }

#else
    /*前オブジェクトへのポインタ取得*/
    inline ObjectBase* GetPrevObject(bool allBaseFlag = true) { return allBaseFlag ? mpPrevObject : mpInheritClassPrevObject; }
    /*次オブジェクトへのポインタ取得*/
    inline ObjectBase* GetNextObject(bool allBaseFlag = true) { return allBaseFlag ? mpNextObject : mpInheritClassNextObject; }

    /*前オブジェクトのポインタを設定する*/
    inline void SetPrevObject(ObjectBase* object, bool allBaseFlag = true) { if (allBaseFlag) { mpPrevObject = object; } else { mpInheritClassPrevObject = object; } }
    /*次オブジェクトのポインタを設定する*/
    inline void SetNextObject(ObjectBase* object, bool allBaseFlag = true) { if (allBaseFlag) { mpNextObject = object; } else { mpInheritClassNextObject = object; } }

#endif
    /*削除フラグ設定(true = 削除)*/
    inline void SetDeleteFlag(const bool flag) { mbIsDeleteFlag = flag; }
    /*削除フラグ取得*/
    inline bool IsDeleteFlag() const { return mbIsDeleteFlag; }

    /*有効フラグ設定*/
    inline void SetActiveFlag(const bool flag) { mbIsActiveFlag = flag; }
    /*有効フラグ取得*/
    inline bool IsActiveFlag() const { return mbIsActiveFlag; }

    /*タグ設定*/
    inline void SetTag(const std::string& tag) { mnTag = tag; }
    /*タグ取得*/
    inline std::string GetTag() const { return mnTag; }

    /*チーム設定*/
    inline void SetTeam(const int team) { mnTeam = team; }
    /*チーム取得*/
    inline int GetTeam() const { return mnTeam; }

    /*個別ナンバー取得*/
    inline unsigned int GetID() const { return munID; }

    /*次のシーン削除するフラグを設定*/
    inline void SetNextSceneDeleteFlag(bool nextSceneDeleteFlag) { mbNextSceneDeleteFlag = nextSceneDeleteFlag; }
    /*次のシーン削除するフラグを取得*/
    inline bool GetNextSceneDeleteFlag() const { return mbNextSceneDeleteFlag; }

    /*オブジェクト種類(ナンバー)取得*/
    inline OBJECT_TYPE GetObjectTypeNumber() const { return meObjectType; }

    /*オブジェクトのシーンを取得*/
    inline SCENE GetObjectScene() const { return meObjectScene; }
    /*オブジェクトのシーン設定*/
    inline void SetObjectScene(SCENE objectScene) { meObjectScene = objectScene; }

    inline BIT_FLAG<unsigned long long> GetObjectBitFlag() const { return mullFlags; }

    /*--------------------------*/
    /*【継承処理キャスト省略用】*/
    /*--------------------------*/
    /*当たり判定*/
    virtual void HitCheck(CollisionData& collisionData) {};
};

/*--------------------------------------------------------*/
/*               【キャラクターベース関係】               */
/*--------------------------------------------------------*/

/*------------------------------------------------*/
/*          【キャラクターベース用enum】          */
/*------------------------------------------------*/

// 行動フラグ
enum class ACTION_FLAG
{
    // MAX 0b0000'0000'0000'0000'0000'0000'0000'0000

    /*上下移動*/
    //UP_OR_DOWN_ACTION =   0b00'000'000'001u,
    /*上移動*/
    UP_ACTION =             0b00'000'000'011u,
    /*下移動*/
    DOWN_ACTION =           0b00'000'000'101u,

    /*右左移動*/
    //LEFT_OR_RIGHT_ACTION= 0b00'000'001'000u,
    /*右移動*/
    RIGHT_ACTION =          0b00'000'011'000u,
    /*左移動*/
    LEFT_ACTION =           0b00'000'101'000u,

    /*前後移動*/
    //FRONT_OR_BACK_ACTION= 0b00'001'000'000u,
    /*前移動*/
    FRONT_ACTION =          0b00'011'000'000u,
    /*後ろ移動*/
    BACK_ACTION =           0b00'101'000'000u,

    /*HPが0以下*/
    HP_ZERO =               0b01'000'000'000u,

    /*ダッシュ*/
    DASH =                  0b10'000'000'000u,
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
    DASH
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

	// 重力
	static constexpr float MAP_GRAVITY = 0.147f;

    // 重量
    float mfGravity;

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

    /*移動処理*/
    virtual void MoveProcess();

    /*死亡処理*/
    virtual void DeathProcess();

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

    /*HPが0以下のフラグを設定*/
    inline void SetHPZero() { munActionflags.SetOrBit(ACTION_FLAG::HP_ZERO); }

    /// <summary>行動フラグ設定</summary>
    inline void SetMoveActionFlag(ACTION_FLAG flagBit) { munActionflags.SetXorBit(flagBit); }

    /// <summary>オブジェクトビットフラグ設定</summary>
    inline void SetObjectBitFlag(bool flag, CHARACTER_OBJECT_BIT_FLAG_NUBER bitNumber) { mullFlags.SetFlag(flag, bitNumber); }
};

/*--------------------------------------------------------*/
/*               【ビルディングベース関係】               */
/*--------------------------------------------------------*/

/*------------------------------------------*/
/*          【ビルディングベース】          */
/*------------------------------------------*/
class BuildingBase : public ObjectBase
{
public:
    enum class BUILDING_OBJECT_BIT_FLAG_NUBER
    {
        BUILDING_OBJECT_BIT_MAX = ObjectBase::OBJECT_BIT_FLAG_NUBER::OBJECT_BIT_MAX
    };

protected:
    // ポジション
    VECTOR mvPosition;

    // モデルベース

    //fsm

    /*当たり判定用 多分モデルでいける*/
//    CollisionData HitCheck(CollisionData collisionData) override { return CollisionCheck(collisionData); }

public:
    BuildingBase(bool nextSceneDeleteFlag);
    ~BuildingBase();

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

    /*----------------------*/
    /*     【独自処理】     */
    /*----------------------*/

protected:
    /*ビルディング初期化*/
    virtual void BuildingInitilize() = 0;
    /*ビルディングシーン最終初期化*/
    virtual void BuildingSceneLastInitilize() = 0;
    /*ビルディング終了*/
    virtual void BuildingFinalize() = 0;
    /*ビルディング更新*/
    virtual void BuildingUpdate() = 0;
    /*ビルディング最終更新*/
    virtual void BuildingLastUpdate() = 0;
    /*ビルディング描画*/
    virtual void BuildingDraw() = 0;
};

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

/*----------------------------------------------*/
/*               【UIベース関係】               */
/*----------------------------------------------*/

/*--------------------------------------*/
/*          【UIベース用enum】          */
/*--------------------------------------*/
// 選択ナンバーフラグ関連用 enum
enum class SELECT_NUMBER_FLAG_ENUM
{
    // MAX 0b0000'0000'0000'0000
    /*---------- bit ----------*/
    /*超えた*/
    EXCEEDED                                 =  0b0001'0000u,
    /*数字減少 超えた*/
    NUMBER_DECREASE_EXCEEDED                 =  0b0000'0001u,
    /*数字増加 超えた*/
    NUMBER_INCREASE_EXCEEDED                 =  0b0000'0010u,
    /*境界値分減少 超えた*/
    BOUNDARY_VALUE_NUMBER_DECREASE_EXCEEDED  =  0b0000'0100u,
    /*境界値分増加 超えた*/
    BOUNDARY_VALUE_NUMBER_INCREASE_EXCEEDED  =  0b0000'1000u,

    /*変更　ビット範囲*/
    CHANGE_BIT_ZONE                          =/*0b1110'0000u*/0b111u,

    /*初期化用ビット*/
    INIT_BIT                                 =  0b1110'0000u,
    /*-------------------------*/

    /*---------- 数字 ----------*/
    /*0*/
    ZERO = 0,

    /*変更　通常*/
    CHANGE_NORMAL                  = 1,
    /*変更　境界停止*/
    CHANGE_BOUNDARY_STOP           = 2,
    // /*変更　境界移動反転*/
    // CHANGE_BOUNDARY_MOVE_INVERSION = 3,
    // /*変更 境界内移動*/
    // CHANGE_MOVING_IN_BOUNDARY = 4,
    /*変更　ビット移動量*/
    CHANGE_BIT_MOVING_DISTANCE     = 5,
    /*--------------------------*/
};

/*------------------------------*/
/*          【UIモデル構造体】
/*------------------------------*/
struct UIDrawModel// TODO: 一旦UIを表示させた後にこれに置き換える
{
    // モデル
    ModelsControllerBase* mpUIModelController;

    // アニメション
    AnimationBase* mpAnimation;

    // 描画するステート
    std::vector<int> mnDrawNumber;
};

/*--------------------------------*/
/*          【UIベース】          */
/*--------------------------------*/
// TODO: Downでの変更間隔をフレーム1つにするのと長押しの間隔を調整する
class UIBase : public ObjectBase
{
public:
    enum class UI_OBJECT_BIT_FLAG_NUBER
    {
        UI_OBJECT_BIT_MAX = ObjectBase::OBJECT_BIT_FLAG_NUBER::OBJECT_BIT_MAX
    };

private:
    // 自分のUIナンバー
    int mnUINumber;

    // 時間停止フラグ
    bool mbTimeStopFlag;

    // 削除時減少させるフラグ
    bool mbDeleteDecreaseFlag;

    // 選択ナンバー関連フラグ
    BIT_FLAG<unsigned short> mstSelectNumberFlag;

protected:
    // キー状態
    KeyState* mpKeyState;

    // リソースマネージャー
    ResourceManager* mpResourceManager;

    // タイムマネジャー
    TimeManager* mpTimeManager;

    // 選択ナンバー
    int mnSelectNumber;
    int mnPreSelectNumber;
    // 選択ステップ数
    int mnSelectStepNumber;

    // 最大選択ナンバー
    int mnSelectMaxNumber;

    // 選択境界値
    int mnSelectBoundaryValue;

    // 前回選択変更フレーム
    FRAME_DATA mstSelectChangeFrame;

    // 選択変更の間隔
    int mnSetChangeIntervalFrame;

    // 画像ハンドル達
    int* mnGraphHandles;
    // 画像ハンドル数
    int mnGraphCount;

    // 動画ハンドル達
    int* mnMovieHandles;
    // 動画ハンドル数
    int mnMovieCount;

    // 有限状態マシン
    FSMUI* mpFsm;

    // UI描画モデルたち
    std::vector<UIDrawModel> mstUIDrawModels;

    // モデルコントローラーの数
    int mnUIModelControllerCount;

    
	// UI座標情報
	std::map<int, std::vector<std::map<int, VECTOR>>> mmUIPositionData;

public:
    UIBase(bool nextSceneDeleteFlag, int maxMenuSelect, bool timeStopFlag = false, bool decreaseFlag = true);
    ~UIBase();

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

    /*----------------------*/
    /*     【独自処理】     */
    /*----------------------*/

    /*--------*/
    /*【設定】*/
    /*--------*/
public:
    /*fsm設定*/
    void SetFsm(FSMUI* fsm);

    /*選択数設定*/
    inline void SetSelectNumber(const int number) { mnSelectNumber = number; ResetSelectStepNumber(); }
    /*選択最大数設定*/
    inline void SetSelectMaxNumber(const int maxNumber) { mnSelectMaxNumber = maxNumber; }
    /// <summary>選択境界値設定</summary>
    inline void SetSelectBoundaryValue(int selectBoundaryValue) { mnSelectBoundaryValue = selectBoundaryValue; ResetSelectStepNumber(); }

    /// <summary>画像ハンドル設定</summary>
    void SetGraphHandle(int index, int handle);

    /// <summary>画像ハンドル数変更</summary>
    void SetGraphCount(int count);

    /// <summary>画像ハンドル設定</summary>
    void SetMovieHandle(int index, int handle);

    /// <summary>画像ハンドル数変更</summary>
    void SetMovieCount(int count);

    /// <summary>UI座標情報設定</summary>
    void SetUIPositionData(int state, std::vector<std::map<int, VECTOR>> uiPositionData) { mmUIPositionData[state]= uiPositionData; }

    /// <summary>アニメーション設定</summary>
    void SetAnimationType(ANIMATION_TYPE aniamtionType);

    /// <summary>選択ナンバー変更種類設定</summary>
    inline void SetSelectNumberChangeType(SELECT_NUMBER_FLAG_ENUM type) {mstSelectNumberFlag.SetNumber(type, SELECT_NUMBER_FLAG_ENUM::CHANGE_BIT_ZONE, SELECT_NUMBER_FLAG_ENUM::CHANGE_BIT_MOVING_DISTANCE);}

private:
    /// <summary></summary>
    inline void ResetSelectStepNumber() { mnSelectStepNumber = mnSelectNumber / mnSelectBoundaryValue; }

    /// <summary>ハンドル数変更</summary>
    void SetHandleCount(int count, int *handleCount, int**handle);

    /*--------*/
    /*【取得】*/
    /*--------*/
public:
    /// <summary>fms取得</summary>
    inline FSMUI* GetFsm() { return mpFsm; }

    /*選択数取得*/
    inline int GetSelectNumber() const { return mnSelectNumber; }
    /// <summary>前の選択数取得</summary>
    inline int GetPreSelectnumber() const { return mnPreSelectNumber; }

    /// <summary>キー取得</summary>
    /// <returns>キーステート</returns>
    inline KeyState* GetKey() { return mpKeyState; }

    /// <summary>画像ハンドル達を取得</summary>
    inline int* GetGraphHandles() { return mnGraphHandles; }

    /// <summary>画像ハンドル数を取得</summary>
    inline int GetGraphHandleCount() const { return mnGraphCount; }

    /// <summary>動画ハンドル達を取得</summary>
    inline int* GetMovieHandles() { return mnMovieHandles; }

    /// <summary>動画ハンドル数を取得</summary>
    inline int GetMovieHandleCount() const { return mnMovieCount; }

    /// <summary>描画モデル情報全取得</summary>
    inline std::vector<UIDrawModel> GetDrawModels() { return mstUIDrawModels; }

    /// <summary>モデル数取得</summary>
    inline int GetModelCount() { return static_cast<int>(mstUIDrawModels.size()); }

    /// <summary>モデルコントローラー取得</summary>
    /// <returns>モデルコントローラー</returns>
    inline ModelsControllerBase* GetModelsController(int index) { return mstUIDrawModels[index].mpUIModelController; }

    /// <summary>アニメションベース取得</summary>
    /// <returns>アニメションベース</returns>
    inline AnimationBase* GetAnimation(int index) {
        return  mstUIDrawModels[index].mpAnimation;
    }

    /// <summary>UI座標情報設定</summary>
    inline std::vector<std::map<int, VECTOR>> GetUIPositionData(int state) { return mmUIPositionData[state]; }

    /// <summary>選択ナンバー超過フラグ取得</summary>
    inline bool GetSelectExceededFlag(SELECT_NUMBER_FLAG_ENUM enumBit) { return mstSelectNumberFlag.GetFlag_Bit(enumBit); }

    /// <summary>選択ナンバー関連フラグ取得</summary>
    inline BIT_FLAG<unsigned short> GetSelectNumberFlag() const { return mstSelectNumberFlag; }

    /*------------------------*/
    /*【継承オブジェクト処理】*/
    /*------------------------*/

protected:
    /*UI初期化*/
    virtual void UIInitilize() = 0;
    /*UIシーン最終初期化*/
    virtual void UISceneLastInitilize() = 0;
    /*UI終了*/
    virtual void UIFinalize() = 0;
    /*UI更新*/
    virtual void UIUpdate() = 0;
    /*UI最終更新*/
    virtual void UILastUpdate() = 0;
    /*UI描画*/
    virtual void UIDraw() = 0;

    /*UIナンバー設定*/
    void SetUINumber();
    /*UIナンバー削除*/
    void DeleteUINumber();

    /*モデル追加*/
    void AddModelData(std::vector<DRAW_GRAPH_DATA> drawData, MODEL_TYPE modelType);
    /*アニメーション設定*/
    void AnimationSetting(LOAD_ANIMATION_DATA_FACTORY_NUMBER ladoAnimationDataFactorynumber, std::vector<int> drawNumber);

    /*----------------------*/
    /*【入力キー種類別処理】*/
    /*----------------------*/

public:
    /*マウスが反応したら関数を実行させる*/
    void CheckMouse();

    /*キーボードが反応したら関数を実行させる*/
    void CheckKeyboard();

    /*コントローラーが反応したら関数を実行させる*/
    void CheckController();

    /*キーボードかコントローラーが反応したら関数を実行させる*/
    void CheckKeyboard_Controller();

protected:
    /*マウスが反応した時に実行する*/
    virtual void MouseProcess();
    /*キーボードが反応した時に実行する*/
    virtual void KeyboardProcess();
    /*コントローラーが反応した時に実行する*/
    virtual void ControllerProcess();
    /*キーボードかコントローラーが反応した時に実行する*/
    virtual void Keyboard_ControllerProcess();

    /*----------------*/
    /*【テンプレート】*/
    /*----------------*/

public:
    /*デフォルト選択処理*/
    void DefaultSelectProcess();
    /*デフォルト選択ナンバー減少処理*/
    void DefaultDecrease();
    /*デフォルト選択ナンバー増加処理*/
    void DefaultIncrease();

    /*左右選択処理*/
    void LeftRightSelectProcess();
    /*左選択ナンバー減少処理*/
    void LeftDecrease();
    /*右選択ナンバー増加処理*/
    void RightIncrease();

    /*選択ナンバー減少処理*/
    void SelectNumberDecrease();
    /*選択ナンバー増加処理*/
    void SelectNumberIncrease();

    /// <summary>選択ナンバー境界値を跨いだ減少処理</summary>
    void SelectBoundaryValueDecrease();
    /// <summary>選択ナンバー境界値を跨いだ増加処理</summary>
    void SelectBoundaryValueIncrease();

    /*デフォルト選択決定処理*/
    void DefaultDecision();
    /*選択決定時処理*/
    virtual void DecisionProcess() = 0;

    /*デフォルト終了確認処理*/
    void DefaultCloce();
    /*デフォルト終了処理*/
    virtual void CloceProcess();

    /*上が押されていて、なおかつ前回の選択変更から一定フレーム経っているなら「true」を返す*/
    bool CheckUp_Frame();
    /*下が押されていて、なおかつ前回の選択変更から一定フレーム経っているなら「true」を返す*/
    bool CheckDown_Frame();
    /*右が押されていて、なおかつ前回の選択変更から一定フレーム経っているなら「true」を返す*/
    bool CheckRight_Frame();
    /*左が押されていて、なおかつ前回の選択変更から一定フレーム経っているなら「true」を返す*/
    bool CheckLeft_Frame();

    /*A/Enterが押されているなら「true」を返す*/
    bool CheckDecision();

    /*フレームが一定時間経っているかどうか*/
    bool CheckFrame(int frameNumber);

    /*選択肢上変更(マイナス)*/
    virtual void Up() { DefaultDecrease(); }
    /*選択肢下変更(プラス)*/
    virtual void Down() { DefaultIncrease(); }
    /*決定時処理*/
    virtual void Decision() { DecisionProcess(); }
};