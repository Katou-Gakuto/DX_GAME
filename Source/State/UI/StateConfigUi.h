#pragma once
#include <vector>

#include "DrawData.h"
#include "Vector2.h"

#include "ObjectBases.h"
#include "StateBase.h"

class MapManager;
class TargetManager;

/*----------------------*/
/*【コンフィグUIステート】*/
/*----------------------*/

enum CONFIG_UI_STATE
{
    SELECT_CONFIG_STATE = 0,// 選択コンフィグデータ
    MINIMAP_CONFIG_STATE,   // ミニマップ設定
    SOUND_CONFIG_STATE,     // サウンド設定
    CAMERA_CONFIG_STATE,    // カメラ設定
    
    CONFIG_UI_STATE_MAX,
};

/*----------*/
/*【コンフィグUI共通処理用】*/
/*----------*/
class ConfigUIProcess
{
protected:
    enum CONFIG_POS_TYPE
    {
        LEFT_UP = 0,
        RIGHT_DOWN,
        MAX
    };

    // 前に選択していた項目
    int mnPreSelectNumber;

    std::vector<DRAW_DATA> mstDrawData;

    const Vector2 CONFIG_POSS[CONFIG_POS_TYPE::MAX] = { Vector2(0.1f, 0.1f), Vector2(0.8f, 0.8f) };

private:
    int* mnStatePointer;
    int mnDefaultStateNumber;

public:
    ConfigUIProcess(int *statePointer, int defaultStateNumber);

protected:
    /*ステートナンバー取得*/
    int GetConfigStateNumber(int stateNumber);
    
    /*値を上下の入力を元に変更する*/
    void ValueLeftRightInputBasedOnChange(UIBase* ui, int *value, int changeSpeed = 1, int min = 0, int max = 10000);
    /*値を上下の入力を元に変更する*/
    void ValueLeftRightInputBasedOnChange(UIBase* ui, float *value, float changeSpeed = 1.0f, float min = 0.0f, float max = 10000.0f);
    
    /*ステートに入った時の処理*/
    void ConfigOnEnter(UIBase* ui);
    /*ステートを出た時の処理*/
    void ConfigOnExit(UIBase* ui);
};

/*----------------------*/
/*【コンフィグ選択ステート】*/
/*----------------------*/
class ConfigSelectState : public IStateUI, public ConfigUIProcess
{
private:
    // 前のConfig以外のステートナンバー
    int mnPreConfigExceptStateNumber;

public:
    ConfigSelectState();
    ~ConfigSelectState() = default;

    void OnEnter(UIBase* ui) override;
    void OnExit(UIBase* ui) override;
    int Update(UIBase* ui) override;
    int Decision(UIBase* ui) override;
    void Draw(UIBase* ui) override;
    int Cloce(UIBase* ui) override;
};

/*----------------------*/
/*【ミニマップ設定ステート】*/
/*----------------------*/
class MinimapConfigState : public IStateUI, public ConfigUIProcess
{
private:
    // ミニマップ設定種類
    enum MIN_MAP_CONFIG_TYPE
    {
        MIN_MAP_SIZE = 0,   // マップサイズ
        MAX
    };
public:
    MinimapConfigState();
    ~MinimapConfigState() = default;

    void OnEnter(UIBase* ui) override;
    void OnExit(UIBase* ui) override;
    int Update(UIBase* ui) override;
    int Decision(UIBase* ui) override;
    void Draw(UIBase* ui) override;
    int Cloce(UIBase* ui) override;
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
    SoundConfigState();
    ~SoundConfigState() = default;

    void OnEnter(UIBase* ui) override;
    void OnExit(UIBase* ui) override;
    int Update(UIBase* ui) override;
    int Decision(UIBase* ui) override;
    void Draw(UIBase* ui) override;
    int Cloce(UIBase* ui) override;
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
    CameraConfigState();
    ~CameraConfigState() = default;

    void OnEnter(UIBase* ui) override;
    void OnExit(UIBase* ui) override;
    int Update(UIBase* ui) override;
    int Decision(UIBase* ui) override;
    void Draw(UIBase* ui) override;
    int Cloce(UIBase* ui) override;
};