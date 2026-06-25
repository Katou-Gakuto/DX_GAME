#pragma once
#include <vector>

#include "StateEnum.h"
#include "DrawData.h"
#include "Vector2.h"

#include "ObjectBases.h"
#include "StateUIBase.h"

class MapManager;
class TargetManager;

/*----------------------*/
/*【コンフィグUIステート】*/
/*----------------------*/

// enum CONFIG_UI_STATE
// {
//     SELECT_CONFIG_STATE = 0,// 選択コンフィグデータ
//     MINIMAP_CONFIG_STATE,   // ミニマップ設定
//     SOUND_CONFIG_STATE,     // サウンド設定
//     CAMERA_CONFIG_STATE,    // カメラ設定
    
//     CONFIG_UI_STATE_MAX,
// };

/*------------------------*/
/*【設定変数ポインタ種類】*/
/*------------------------*/
enum class CONFIG_VARIABLE_POINTER_TYPE
{
    NONE = 0,
    INT,
    FLOAT,
};

/*--------------------*/
/*【設定変数ポインタ】*/
/*--------------------*/
struct CONFIG_VARIABLE_POINTER
{
private:
    CONFIG_VARIABLE_POINTER_TYPE type = CONFIG_VARIABLE_POINTER_TYPE::NONE;

    int* intPointer = nullptr;
    int intRateValue = 0;
    int intLowestValue = 0;

    float* floatPointer = nullptr;
    float floatRateValue = 0.0f;
    float floatLowestValue = 0.0f;

public:
    // 割合
    float rate = 0.0f;

    // 描画情報
    DRAW_DATA drawData;

    /// <summary>int変数設定</summary>
    /// <param name="src">変更変数</param>
    /// <param name="max">最大値</param>
    /// <param name="min">最低値</param>
    void SetInt(int *src, int max, int min)
    {
        this->type = CONFIG_VARIABLE_POINTER_TYPE::INT;
        this->intPointer = src;
        this->intRateValue = max - min;
        this->intLowestValue = min;
        if (this->intRateValue == 0)
        {
            this->rate = 0.0f;
            return;
        }
        this->rate = static_cast<float>(*this->intPointer - this->intLowestValue) / this->intRateValue;
    }

    /// <summary>float変数設定</summary>
    /// <param name="src">変更変数</param>
    /// <param name="max">最大値</param>
    /// <param name="min">最低値</param>
    void SetFloat(float *src, float max, float min)
    {
        this->type = CONFIG_VARIABLE_POINTER_TYPE::FLOAT;
        this->floatPointer = src;
        this->floatRateValue = max - min;
        this->floatLowestValue = min;
        if (this->floatRateValue <= 0.001f)
        {
            this->rate = 0.0f;
            return;
        }
        this->rate = static_cast<float>(*this->floatPointer - this->floatLowestValue) / this->floatRateValue;
    }


    /// <summary>設定変数変更</summary>
    /// <param name="changeRateAmount">変更割合量</param>
    void ChangeVariable(float changeRateAmount);
};

/*----------*/
/*【コンフィグUI共通処理用】*/
/*----------*/
class ConfigUIProcess
{
protected:
    
    // スライダーのまとまりの数
    constexpr static int SLIDER_CHUNK_NUMBER = 2;


    // コンフィグポジション種類
    enum CONFIG_POS_TYPE
    {
        LEFT_UP = 0,
        RIGHT_DOWN,
        CONFIG_POS_TYPE_MAX
    };

    // コンフィグスライダー種類
    enum CONFIG_SLIDER_TYPE
    {
        SLIDER_LEFT,
        SLIDER_RIGHT,
        SLIDER_BUTTON,

        CONFIG_SLIDER_TYPE_MAX,

        ALL_CONFIG_SLIDER_MAX = SLIDER_CHUNK_NUMBER * (int)CONFIG_SLIDER_TYPE_MAX,
    };

    // 前に選択していた項目
    int mnPreSelectNumber;

    // 描画情報
    std::vector<DRAW_DATA> mstDrawData;

    // コンフィグ座標
    const Vector2 CONFIG_POSS[CONFIG_POS_TYPE::CONFIG_POS_TYPE_MAX] = { Vector2(0.1f, 0.1f), Vector2(0.8f, 0.8f) };

    // コンフィグ変数
    std::vector<CONFIG_VARIABLE_POINTER> mstConfigVariables;

    // コンフィグポジション
    const Vector2 CONFIG_POS = Vector2(0.37f, 0.17f);
    // コンフィグポジション間隔
    const float CONFIG_POS_DISTANCE = 0.1f;
    // コンフィグサイズ
    const Vector2 CONFIG_SIZE = Vector2(0.24f, 0.02f);
    // コンフィグボタンサイズ
    const Vector2 CONFIG_BUTTONSIZE = Vector2(0.01f, 0.02f);
    // コンフィグ画像サイズ
    const DisplaySize CONFIG_GRAPHSIZE = { Vector2(3221.0f, 218.0f), 0 };

public:
    ConfigUIProcess();

protected:
    
    /*値を上下の入力を元に変更する*/
    void ValueLeftRightInputBasedOnChange(UIBase* ui, int *value, int changeSpeed = 1, int min = 0, int max = 10000);
    /*値を上下の入力を元に変更する*/
    void ValueLeftRightInputBasedOnChange(UIBase* ui, float *value, float changeSpeed = 1.0f, float min = 0.0f, float max = 10000.0f);
    
    /*ステートに入った時の処理*/
    void ConfigOnEnter(UIBase* ui);
    /*ステートを出た時の処理*/
    void ConfigOnExit(UIBase* ui);

    /*Sliderワンセット初期設定*/
    void InitSetSlider(int index);

    /*コンフィグ描画をセッティングする*/
    void ConfigDrawSetting(UIBase* ui);

    /*コンフィグ別スライダー設定*/// TODO:ここintじゃね?
    void SetConfigSlider(STATE_TYPE_UI configType);
};

/*----------------------*/
/*【コンフィグ選択ステート】*/
/*----------------------*/
class ConfigSelectState : public IStateUI, public ConfigUIProcess
{
private:
    // 描画情報種類
    enum CONFIG_SELECT_DRAW_DATA_TYPE
    {

        SLIDER_1_LEFT = 0,
        SLIDER_1_RIGHT,
        SLIDER_1_BUTTON,
        
        SLIDER_2_LEFT,
        SLIDER_2_RIGHT,
        SLIDER_2_BUTTON,

        SLIDER_MAX = CONFIG_SLIDER_TYPE::ALL_CONFIG_SLIDER_MAX,

        RETURN = static_cast<int>(SLIDER_MAX),
        MINIMAP,
        SOUND,
        CAMERA,

        TYPE_MAX,

        MAX = static_cast<int>(TYPE_MAX)
    };

    static constexpr int CONFIG_UI_STATE_MAX = 4;

    // 前のConfig以外のステートナンバー
    int mnPreConfigExceptStateNumber;
    
    // 全コンフィグ変数
    std::vector<std::vector<CONFIG_VARIABLE_POINTER>> mstAllConfigVariables;

public:
    ConfigSelectState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>> stateChangeCriterias);
    ~ConfigSelectState() = default;

    void OnEnter(UIBase* ui, STATE_TYPE_UI preState) override;
    void OnExit(UIBase* ui, STATE_TYPE_UI nextState) override;

    void Update(UIBase* ui) override;
    void Decision(UIBase* ui) override;
    void Draw(UIBase* ui) override;
    void Close(UIBase* ui) override;

private:

    /*全コンフィグ描画をセッティングする*/
    void AllConfigDrawSetting(UIBase* ui, bool setFlag = false);
};

/*----------------------*/
/*【ミニマップ設定ステート】*/
/*----------------------*/
class MinimapConfigState : public IStateUI, public ConfigUIProcess
{
private:
    // ミニマップ設定種類
    enum MINI_MAP_CONFIG_TYPE
    {
        MINI_MAP_SIZE = 0,   // マップサイズ
        MAX
    };
public:
    MinimapConfigState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>> stateChangeCriterias);
    ~MinimapConfigState() = default;

    void OnEnter(UIBase* ui, STATE_TYPE_UI preState) override;
    void OnExit(UIBase* ui, STATE_TYPE_UI nextState) override;

    void Update(UIBase* ui) override;
    void Decision(UIBase* ui) override;
    void Draw(UIBase* ui) override;
    void Close(UIBase* ui) override;
};

/*----------------------*/
/*【サウンド設定ステート】*/
/*----------------------*/
class SoundConfigState : public IStateUI, public ConfigUIProcess
{
private:
    // サウンド設定種類
    enum SOUND_CONFIG_TYPE
    {
        VOLUME = 0, // 音量
        MAX
    };
public:
    SoundConfigState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>> stateChangeCriterias);
    ~SoundConfigState() = default;

    void OnEnter(UIBase* ui, STATE_TYPE_UI preState) override;
    void OnExit(UIBase* ui, STATE_TYPE_UI nextState) override;

    void Update(UIBase* ui) override;
    void Decision(UIBase* ui) override;
    void Draw(UIBase* ui) override;
    void Close(UIBase* ui) override;
};

/*----------------------*/
/*【カメラ設定ステート】*/
/*----------------------*/
class CameraConfigState : public IStateUI, public ConfigUIProcess
{
private:
    // カメラ設定種類
    enum CAMERA_CONFIG_TYPE
    {
        DISTANCE = 0,   // 距離
        MAX
    };
public:
    CameraConfigState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, UIBase>> stateChangeCriterias);
    ~CameraConfigState() = default;

    void OnEnter(UIBase* ui, STATE_TYPE_UI preState) override;
    void OnExit(UIBase* ui, STATE_TYPE_UI nextState) override;

    void Update(UIBase* ui) override;
    void Decision(UIBase* ui) override;
    void Draw(UIBase* ui) override;
    void Close(UIBase* ui) override;
};