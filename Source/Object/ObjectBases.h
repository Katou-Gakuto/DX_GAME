#pragma once
#include <list>
#include <string>

#include "BitFlag.h"
#include "CollisionData.h"
#include "Status.h"
#include "ResourceData.h"// TODO: 消す

#include "DxLib.h"

#include "AnimationBase.h"
#include "KeyState.h"
#include "ModelsControllerBase.h"
#include "ResourceManager.h"
#include "TimeManager.h"

enum class ATTACK_METHOD_TYPE;
enum class SCENE;

class FSMCharacter;
class FSMUI;

/*--------------------------------------------------------*/
/*               【オブジェクトベース関連】               */
/*--------------------------------------------------------*/

/*------------------------------------------------*/
/*          【オブジェクトベース用enum】          */
/*------------------------------------------------*/

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
    BIT_FLAG<unsigned long long> mllFlags;

public:

    /*コンストラクタ*/
    ObjectBase(OBJECT_TYPE objectType, bool isActiveFlag, bool nextSceneDeleteFlag);
    /*デストラクタ*/
    ~ObjectBase();

    /*初期化*/
    virtual void Initilize() = 0;
    /*終了*/
    virtual void Finalize() = 0;
    /*更新*/
    virtual void Update() = 0;
    /*最終更新*/
    virtual void LastUpdate() = 0;
    /*描画*/
    virtual void Draw() = 0;

    /*前オブジェクトへのポインタ取得*/
    inline ObjectBase* GetPrevObject(bool allBaseFlag = true) { return allBaseFlag ? mpPrevObject : mpInheritClassPrevObject; }
    /*次オブジェクトへのポインタ取得*/
    inline ObjectBase* GetNextObject(bool allBaseFlag = true) { return allBaseFlag ? mpNextObject : mpInheritClassNextObject; }

    /*前オブジェクトのポインタを設定する*/
    inline void SetPrevObject(ObjectBase* object, bool allBaseFlag = true) { if (allBaseFlag) { mpPrevObject = object; } else { mpInheritClassPrevObject = object; } }
    /*次オブジェクトのポインタを設定する*/
    inline void SetNextObject(ObjectBase* object, bool allBaseFlag = true) { if (allBaseFlag) { mpNextObject = object; } else { mpInheritClassNextObject = object; } }

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
    //UP_OR_DOWN_ACTION =  0b0'000'000'001u,
    /*上移動*/
    UP_ACTION =            0b0'000'000'011u,
    /*下移動*/
    DOWN_ACTION =          0b0'000'000'101u,

    /*右左移動*/
    //LEFT_OR_RIGHT_ACTION=0b0'000'001'000u,
    /*右移動*/
    RIGHT_ACTION =         0b0'000'011'000u,
    /*左移動*/
    LEFT_ACTION =          0b0'000'101'000u,

    /*前後移動*/
    //FRONT_OR_BACK_ACTION=0b0'001'000'000u,
    /*前移動*/
    FRONT_ACTION =         0b0'011'000'000u,
    /*後ろ移動*/
    BACK_ACTION =          0b0'101'000'000u,

    /*HPが0以下*/
    HP_ZERO =              0b1'000'000'000u,
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
};

/*------------------------------------------*/
/*          【キャラクターベース】          */
/*------------------------------------------*/

class CharacterBase : public ObjectBase
{

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

    // 移動速度
    float mfSpeed;

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

    // スペシャル攻撃情報ナンバー
    int mnSpecialAttackDataNumber;

    // ノーマル攻撃情報ナンバー
    int mnNormalAttackNumber;

public:
    CharacterBase(bool nextSceneDeleteFlag, STATUS status);
    ~CharacterBase();

    /*初期化*/
    void Initilize() override final;
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
    virtual int StartAttck(ATTACK_METHOD_TYPE attackMethodType);

    /*攻撃停止*/
    virtual void StopAttack(ATTACK_METHOD_TYPE attackMethodType);

    /*ダメージ*/
    virtual void Damage(int damage);

protected:
    /*キャラクター初期化*/
    virtual void CharacterInitilize() = 0;
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
    inline STATUS GetStatus() const { return mstStatus; }

    /*ポジション取得*/
    inline VECTOR GetPos() const { return mvPosition; }

    /*移動予定地点*/
    inline VECTOR GetMovePos() const { return VAdd(mvPosition, VScale(mvVec, (float)mstStatus.speed)); }

    /*前のポジション取得*/
    inline VECTOR GetOldPos() const { return mvOldPosition; }

    /*移動方向取得*/
    inline VECTOR GetMoveDir() const { return mvMoveDir; }

    /*移動量取得*/
    inline VECTOR GetVec() const { return mvVec; }

    /*移動速度取得*/
    inline float GetSpeed() const { return mfSpeed; }

    /*方向取得*/
    inline VECTOR GetAngle() const { return mvAngle; }

    /*サイズ取得*/
    inline VECTOR GetSize() const { return mpModelController->GetModelSize(); }

    /// <summary>モデルコントローラー取得</summary>
    /// <returns>モデルコントローラー</returns>
    inline ModelsControllerBase* GetModelsController() { return mpModelController; }

    /// <summary>アニメションベース取得</summary>
    /// <returns>アニメションベース</returns>
    inline AnimationBase* GetAnimation() { return  mpAnimation; }

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
    /*移動速度設定*/
    inline void SetSpeed(const float& speed) { mfSpeed = speed; }

    /*上移動設定*/
    inline void SetUpMove() { munActionflags ^= (unsigned int)ACTION_FLAG::UP_ACTION; }
    /*下移動設定*/
    inline void SetDownMove() { munActionflags ^= (unsigned int)ACTION_FLAG::DOWN_ACTION; }

    /*右移動設定*/
    inline void SetRightMove() { munActionflags ^= (unsigned int)ACTION_FLAG::RIGHT_ACTION; }
    /*左移動設定*/
    inline void SetLeftMove() { munActionflags ^= (unsigned int)ACTION_FLAG::LEFT_ACTION; }

    /*前移動設定*/
    inline void SetFrontMove() { munActionflags ^= (unsigned int)ACTION_FLAG::FRONT_ACTION; }
    /*後ろ移動設定*/
    inline void SetBackMove() { munActionflags ^= (unsigned int)ACTION_FLAG::BACK_ACTION; }

    /*HPが0以下のフラグを設定*/
    inline void SetHPZero() { munActionflags ^= (unsigned int)ACTION_FLAG::HP_ZERO; }
};

/*--------------------------------------------------------*/
/*               【ビルディングベース関係】               */
/*--------------------------------------------------------*/

/*------------------------------------------*/
/*          【ビルディングベース】          */
/*------------------------------------------*/

class BuildingBase : public ObjectBase
{
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
    /*コリジョン初期化*/
    virtual void CollisionInitilize() = 0;
    /*コリジョン終了*/
    virtual void CollisionFinalize() = 0;
    /*コリジョン更新*/
    virtual void CollisionUpdate() = 0;
    /*コリジョン最終更新*/
    virtual void CollisionLastUpdate() = 0;
    /*コリジョン描画*/
    virtual void CollisionDraw() = 0;
};

/*----------------------------------------------------*/
/*               【アタックベース関係】               */
/*----------------------------------------------------*/

/*--------------------------------------*/
/*          【アタックベース】          */
/*--------------------------------------*/

class AttackBase : public ObjectBase
{
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

    // モデルベース

    //fsm

    // 攻撃ナンバー
    int mnAttackNumber;

    // 攻撃反動時間
    int mnAttackRecoilTime;

    // 攻撃時間
    int mnAttackTime;

public:
    AttackBase();
    ~AttackBase();

    /*初期化*/
    void Initilize() override final;
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
    inline void SetAttackTime(int time) { mnAttackTime = time; }

    /*移動方向設定*/
    inline void SetMoveDir(VECTOR moveDir) { mvMoveDir = moveDir; }

    /*攻撃力設定*/
    inline void SetAttackPower(int power) { mnPower = power; }

    /*--------*/
    /*【取得】*/
    /*--------*/

public:
    /*攻撃ナンバー取得*/
    inline int GetAttackNumber() const { return mnAttackNumber; }

    /*攻撃反動時間取得*/
    inline int GetAttackRecoilTime() const { return mnAttackRecoilTime; }

    /*パワー取得*/
    inline int GetAttackPower()const { return mnPower; }
};

/*----------------------------------------------*/
/*               【UIベース関係】               */
/*----------------------------------------------*/

/*--------------------------------*/
/*          【UIベース】          */
/*--------------------------------*/
// TODO: Downでの変更間隔をフレーム1つにするのと長押しの間隔を調整する
class UIBase : public ObjectBase
{
private:
    // 自分のUIナンバー
    int mnUINumber;

    // 時間停止フラグ
    bool mbTimeStopFlag;

    // 削除時減少させるフラグ
    bool mbDeleteDecreaseFlag;

protected:
    // キー状態
    KeyState* mpKeyState;

    // リソースマネージャー
    ResourceManager* mpResourceManager;

    // タイムマネジャー
    TimeManager* mpTimeManager;

    // 選択ナンバー
    int mnSelectNumber;

    // 最大選択ナンバー
    int mnSelectMaxNumber;

    // 前回選択変更フレーム
    int mnSelectChangeFrame;

    // 選択変更の間隔
    int mnSetChangeIntervalFrame;

    // 画像ハンドル達
    int* mnGraphHandles;
    // 画像ハンドル数
    int mnGraphCount;

    // 有限状態マシン
    FSMUI* mpFsm;

    // ディスプレイサイズ
    DisplaySize mstDisplaySize;

public:
    UIBase(bool nextSceneDeleteFlag, int maxMenuSelect, bool timeStopFlag = false, bool decreaseFlag = true);
    ~UIBase();

    /*初期化*/
    void Initilize() override final;
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
    inline void SetSelectNumber(const int number) { mnSelectNumber = number; }
    /*選択最大数設定*/
    inline void SetSelectMaxNumber(const int maxNumber) { mnSelectMaxNumber = maxNumber; }

    /// <summary>画面サイズ設定</summary>
    /// <param name="displaySize">ディスプレイサイズ</param>
    inline void SetDisplaySize(const DisplaySize displaySize) { mstDisplaySize = displaySize; }

    /// <summary>画像ハンドル設定</summary>
    void SetGraphHandle(int index, int handle);

    /// <summary>画像ハンドル数変更</summary>
    void SetGraphCount(int count);

    /*--------*/
    /*【取得】*/
    /*--------*/
public:
    /*選択数取得*/
    inline int GetSelectNumber() const { return mnSelectNumber; }

    /// <summary>画面サイズ取得</summary>
    /// <returns>画面サイズ</returns>
    inline DisplaySize GetDisplaySize() const { return mstDisplaySize; }

    /// <summary>キー取得</summary>
    /// <returns>キーステート</returns>
    inline KeyState* GetKey() { return mpKeyState; }

    /// <summary>画像ハンドル達を取得</summary>
    inline int* GetGraphHandles() { return mnGraphHandles; }

    /// <summary>画像ハンドル数を取得</summary>
    inline int GetGraphHandleCount() { return mnGraphCount; }

    /*------------------------*/
    /*【継承オブジェクト処理】*/
    /*------------------------*/

protected:
    /*UI初期化*/
    virtual void UIInitilize() = 0;
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