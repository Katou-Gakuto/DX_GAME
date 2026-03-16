#include "DrawData.h"

#include "Master.h"

#include "DrawManager.h"
#include "KeyState.h"
#include "MapManager.h"
#include "ResourceManager.h"
#include "StateConfigUi.h"
#include "TargetManager.h"
#include "ObjectBases.h"

/*--------------------------------*/
/*   【コンフィグUIステート】     */
/*--------------------------------*/

/*----------*/
/*【コンフィグUI共通処理用】*/
/*----------*/
ConfigUIProcess::ConfigUIProcess(int *statePointer, int defaultStateNumber)
: mnPreSelectNumber(0)  
, mnStatePointer(statePointer)
, mnDefaultStateNumber(defaultStateNumber)
{
    DisplaySize displaySize = ResourceManager::mstDisplaySize;

    mstDrawData = DRAW_DATA();
    mstDrawData.drawFlag = false;
    mstDrawData.drawManagerDrawType = DRAW_MANAGER_DRAW_TYPE::GRAPH;
    mstDrawData.drawGraphData.drawType = DRAW_GRAPH_TYPE::SIZE;
    mstDrawData.drawGraphData.pos = displaySize.LeftUp_Ratio(Vector2(0.1f, 0.1f));
    mstDrawData.drawGraphData.size = displaySize.LeftUp_FloatRatio(0.8f);
    mstDrawData.drawGraphData.handle = Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/TitleSelectBase.png");
    mstDrawData.drawGraphData.transFlag = TRUE;
    Master::mpDrawManager->AddDrawData(&mstDrawData);
}

// ステートナンバー取得
int ConfigUIProcess::GetConfigStateNumber(int stateNumber)
{
    return *mnStatePointer + (stateNumber - mnDefaultStateNumber) ;
}

// 値を左右の入力を元に変更する
void ConfigUIProcess::ValueLeftRightInputBasedOnChange(UIBase* ui, int *value, int changeSpeed, int min, int max)
{
    if (changeSpeed < 0)
    {
        changeSpeed = -changeSpeed;
    }

    if (ui->CheckLeft_Frame())
    {
        *value -= changeSpeed;
        if (min > *value)
        {
            *value = min;
        }
    }
    if (ui->CheckRight_Frame())
    {
        *value += changeSpeed;
        if (max < *value)
        {
            *value = max;
        }
    }
}

// ステートに入った時の処理
void ConfigUIProcess::ConfigOnEnter(UIBase* ui)
{
    mstDrawData.drawFlag = true;
    ui->SetSelectNumber(mnPreSelectNumber);
}

// ステートを出た時の処理
void ConfigUIProcess::ConfigOnExit(UIBase* ui)
{
    mstDrawData.drawFlag = false;
    mnPreSelectNumber = ui->GetSelectNumber();
}

/*----------------------*/
/*【コンフィグ選択ステート】*/
/*----------------------*/
ConfigSelectState::ConfigSelectState()
: ConfigUIProcess(&mStateNumber, CONFIG_UI_STATE::SELECT_CONFIG_STATE)
{
    mStateNumber = CONFIG_UI_STATE::SELECT_CONFIG_STATE;
}

void ConfigSelectState::OnEnter(UIBase* ui)
{
    ConfigOnEnter(ui);

    ui->SetSelectMaxNumber(CONFIG_UI_STATE::CONFIG_UI_STATE_MAX);
    ui->SetSelectNumber(mnPreSelectNumber);
    ui->SetSelectBoundaryValue(1);
 
    int preStateNumber = ui->GetFsm()->GetCurrentState();
    if (preStateNumber < mStateNumber)
    {
        mnPreConfigExceptStateNumber = preStateNumber;
        ui->SetSelectNumber(0);
    }
}

void ConfigSelectState::OnExit(UIBase* ui)
{
    ConfigOnExit(ui);

    mnPreSelectNumber = ui->GetSelectNumber();
}

int ConfigSelectState::Update(UIBase* ui)
{
    ui->LeftRightSelectProcess();
    ui->DefaultDecision();
    ui->DefaultCloce();

    if (ui->CheckDown_Frame())
    {
        ui->Decision();
    }

    return mStateNumber;
}

int ConfigSelectState::Decision(UIBase* ui)
{
    switch (ui->GetSelectNumber())
    {
    case CONFIG_UI_STATE::SELECT_CONFIG_STATE:
        return mnPreConfigExceptStateNumber;
    }
    return GetConfigStateNumber(ui->GetSelectNumber());
}

void ConfigSelectState::Draw(UIBase* ui)
{
    clsDx();
    printfDx("選択\n");
    printfDx("%d", ui->GetSelectNumber());
}

int ConfigSelectState::Cloce(UIBase* ui)
{
    return mnPreConfigExceptStateNumber;
}

/*----------------------*/
/*【ミニマップ設定ステート】*/
/*----------------------*/
MinimapConfigState::MinimapConfigState()
: ConfigUIProcess(&mStateNumber, CONFIG_UI_STATE::MINIMAP_CONFIG_STATE)
{
    mStateNumber = CONFIG_UI_STATE::MINIMAP_CONFIG_STATE;
}

void MinimapConfigState::OnEnter(UIBase* ui)
{
    ConfigOnEnter(ui);

    ui->SetSelectNumberChangeType(SELECT_NUMBER_FLAG_ENUM::CHANGE_BOUNDARY_STOP);
    ui->SetSelectMaxNumber(MIN_MAP_CONFIG_TYPE::MAX);
    ui->SetSelectNumber(mnPreSelectNumber);
}

void MinimapConfigState::OnExit(UIBase* ui)
{
    ConfigOnExit(ui);

    mnPreSelectNumber = ui->GetSelectNumber();
}

int MinimapConfigState::Update(UIBase* ui)
{
    ui->DefaultSelectProcess();
    ui->DefaultCloce();

    return mStateNumber;
}

int MinimapConfigState::Decision(UIBase* ui)
{
    return mStateNumber;
}

void MinimapConfigState::Draw(UIBase* ui)
{
    clsDx();
    printfDx("ミニマップ");
}

int MinimapConfigState::Cloce(UIBase* ui)
{
    return GetConfigStateNumber(CONFIG_UI_STATE::SELECT_CONFIG_STATE);
}

/*----------------------*/
/*【サウンド設定ステート】*/
/*----------------------*/
SoundConfigState::SoundConfigState()
: ConfigUIProcess(&mStateNumber, CONFIG_UI_STATE::SOUND_CONFIG_STATE)
{
    mStateNumber = (int)CONFIG_UI_STATE::SOUND_CONFIG_STATE;
}

void SoundConfigState::OnEnter(UIBase* ui)
{
    ConfigOnEnter(ui);

    ui->SetSelectMaxNumber(SOUND_CONFIG_TYPE::MAX);
    ui->SetSelectNumber(mnPreSelectNumber);
}

void SoundConfigState::OnExit(UIBase* ui)
{
    ConfigOnExit(ui);

    mnPreSelectNumber = ui->GetSelectNumber();
}

int SoundConfigState::Update(UIBase* ui)
{
    ui->DefaultSelectProcess();
    ui->DefaultCloce();

    return mStateNumber;
}

int SoundConfigState::Decision(UIBase* ui)
{
    return mStateNumber;
}

void SoundConfigState::Draw(UIBase* ui)
{
    clsDx();
    printfDx("サウンド");
}

int SoundConfigState::Cloce(UIBase* ui)
{
    return GetConfigStateNumber(CONFIG_UI_STATE::SELECT_CONFIG_STATE);
}

/*----------------------*/
/*【カメラ設定ステート】*/
/*----------------------*/
CameraConfigState::CameraConfigState()
: ConfigUIProcess(&mStateNumber, CONFIG_UI_STATE::CAMERA_CONFIG_STATE)
{
    mStateNumber = (int)CONFIG_UI_STATE::CAMERA_CONFIG_STATE;
}

void CameraConfigState::OnEnter(UIBase* ui)
{
    ConfigOnEnter(ui);

    ui->SetSelectMaxNumber(CAMERA_CONFIG_TYPE::MAX);
    ui->SetSelectNumber(mnPreSelectNumber);
}

void CameraConfigState::OnExit(UIBase* ui)
{
    ConfigOnExit(ui);

    mnPreSelectNumber = ui->GetSelectNumber();
}

int CameraConfigState::Update(UIBase* ui)
{
    ui->DefaultSelectProcess();
    ui->DefaultCloce();
    
    return mStateNumber;
}

int CameraConfigState::Decision(UIBase* ui)
{
    return mStateNumber;
}

void CameraConfigState::Draw(UIBase* ui)
{
    clsDx();
    printfDx("カメラ");
}

int CameraConfigState::Cloce(UIBase* ui)
{
    return GetConfigStateNumber(CONFIG_UI_STATE::SELECT_CONFIG_STATE);
}