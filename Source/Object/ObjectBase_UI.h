#pragma once
#include <map>
#include <vector>

#include "AnimationEnum.h"
#include "TimeData.h"
#include "BitFlag.h"
#include "ResourceData.h"

#include "DxLib.h"

#include "AnimationBase.h"
#include "FSMUI.h"
#include "KeyState.h"
#include "ModelsControllerBase.h"
#include "ObjectBase.h"
#include "UtilFactorys.h"

class ResourceManager;
class TimeManager;

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