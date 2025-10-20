#pragma once
#include <list>

#include "BitFlag.h"
#include "CollisionData.h"
#include "Status.h"

#include "DxLib.h"

#include "KeyState.h"
#include "ResourceManager.h"
#include "TimeManager.h"

enum class SCENE;

class AttackBase;

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
    int mnTag;
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

    /*削除フラグ設定*/
    inline void SetDeleteFlag(bool flag) { mbIsDeleteFlag = flag; }
    /*削除フラグ取得*/
    inline bool IsDeleteFlag() const { return mbIsDeleteFlag; }

    /*有効フラグ設定*/
    inline void SetActiveFlag(bool flag) { mbIsActiveFlag = flag; }
    /*有効フラグ取得*/
    inline bool IsActiveFlag() const { return mbIsActiveFlag; }

    /*タグ設定*/
    inline void SetTag(int tag) { mnTag = tag; }
    /*タグ取得*/
    inline int GetTag() const { return mnTag; }

    /*チーム設定*/
    inline void SetTeam(int team) { mnTeam = team; }
    /*チーム取得*/
    inline int GetTeam() const { return mnTeam; }

    /*個別ナンバー取得*/
    inline unsigned int GetID() const { return munID; }

    /*次のシーン削除するフラグを設定*/
    inline void SetNextSceneDeleteFlag(bool nextSceneDeleteFlag) { mbNextSceneDeleteFlag = nextSceneDeleteFlag; }
    /*次のシーン削除するフラグを取得*/
    inline bool GetNextSceneDeleteFlag() const { return mbNextSceneDeleteFlag; }

    /*オブジェクト種類(ナンバー)取得*/
    inline int GetObjectTypeNumber() const { return (int)meObjectType; }

    /*オブジェクトのシーンを取得*/
    inline SCENE GetObjectScene() const { return meObjectScene; }
    /*オブジェクトのシーン設定*/
    inline void SetObjectScene(SCENE objectScene) { meObjectScene = objectScene; }

    /*--------------------------*/
    /*【継承処理キャスト省略用】*/
    /*--------------------------*/
    /*当たり判定*/
    virtual CollisionData HitCheck(CollisionData collisionData) { return collisionData; };
};

/*--------------------------------------------------------*/
/*               【キャラクターベース関係】               */
/*--------------------------------------------------------*/

/*------------------------------------------------*/
/*          【キャラクターベース用enum】          */
/*------------------------------------------------*/
// 行動フラグ
enum class MOVE_FLAG
{
    // MAX 0b0000'0000'0000'0000'0000'0000'0000'0000

    /*上下移動*/
    UP_OR_DOWN_MOVE    = 0b0'000'000'001u,
    /*上移動*/
    UP_MOVE            = 0b0'000'000'011u,
    /*下移動*/
    DOWN_MOVE          = 0b0'000'000'101u,

    /*右左移動*/
    LEFT_OR_RIGHT_MOVE = 0b0'000'001'000u,
    /*右移動*/
    RIGHT_MOVE         = 0b0'000'011'000u,
    /*左移動*/
    LEFT_MOVE          = 0b0'000'101'000u,

    /*前後移動*/
    FRONT_OR_BACK_MOVE = 0b0'001'000'000u,
    /*前移動*/
    FRONT_MOVE         = 0b0'011'000'000u,
    /*後ろ移動*/
    BACK_MOVE          = 0b0'101'000'000u,

    /*攻撃*/
    ATTACK_MOVE        = 0b1'000'000'000u,
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
    VECTOR mvVec;

    // モデル向き
    VECTOR mvAngle;

    // ステータス
    STATUS mstStatus;

    //fsm

    // モデルベース

    // アニメションベース

    // 攻撃オブジェクト
    AttackBase* mpAttack;

    // 移動フラグ
    BIT_FLAG<unsigned int> munMoveflags;

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

public:
    /*----------------------*/
    /*     【独自処理】     */
    /*----------------------*/

    /*当たり判定用(継承用)*/
    virtual CollisionData CharacterCheck(CollisionData collisionData) = 0;

    /*攻撃リセット*/
    virtual void StopAttack();

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

    ///*移動処理*/
    //virtual void MoveProcess() { TemplateMoveProcess(); }

    ///*定型移動処理*/
    //void TemplateMoveProcess();

public:

    /*--------*/
    /*【取得】*/
    /*--------*/

    /*ステータス取得*/
    inline STATUS& GetStatus() { return mstStatus; }

    /*--------*/
    /*【設定】*/
    /*--------*/

    /*上移動設定*/
    inline void SetUpMove() { munMoveflags ^= (unsigned int)MOVE_FLAG::UP_MOVE; }
    /*下移動設定*/
    inline void SetDownMove() { munMoveflags ^= (unsigned int)MOVE_FLAG::DOWN_MOVE; }

    /*右移動設定*/
    inline void SetRightMove() { munMoveflags ^= (unsigned int)MOVE_FLAG::RIGHT_MOVE; }
    /*左移動設定*/
    inline void SetLeftMove() { munMoveflags ^= (unsigned int)MOVE_FLAG::LEFT_MOVE; }

    /*攻撃設定*/
    inline void SetAttack() { munMoveflags ^= (unsigned int)MOVE_FLAG::ATTACK_MOVE; }
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
    std::list<CharacterBase*> mpHiCharacter;

    // モデルベース

    //fsm

public:
    AttackBase(bool nextSceneDeleteFlag, CharacterBase* attackCharacter);
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
};

/*----------------------------------------------*/
/*               【UIベース関係】               */
/*----------------------------------------------*/

/*--------------------------------*/
/*          【UIベース】          */
/*--------------------------------*/
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
    virtual void MouseProcess() {}
    /*キーボードが反応した時に実行する*/
    virtual void KeyboardProcess() {}
    /*コントローラーが反応した時に実行する*/
    virtual void ControllerProcess() {}
    /*キーボードかコントローラーが反応した時に実行する*/
    virtual void Keyboard_ControllerProcess() {}

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