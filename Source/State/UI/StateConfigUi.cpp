#include "StateConfigUi.h"
#include "Master.h"
#include "KeyState.h"
#include "MapManager.h"
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
}

// ステートナンバー取得
int ConfigUIProcess::GetConfigStateNumber(int stateNumber)
{
    return *mnStatePointer + (stateNumber - mnDefaultStateNumber) ;
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
    ui->SetSelectMaxNumber(CONFIG_UI_STATE::CONFIG_UI_STATE_MAX);
    ui->SetSelectNumber(mnPreSelectNumber);
 
    int preStateNumber = ui->GetFsm()->GetCurrentState();
    if (preStateNumber < mStateNumber)
    {
        mnPreConfigExceptStateNumber = preStateNumber;
        ui->SetSelectNumber(0);
    }
}

void ConfigSelectState::OnExit(UIBase* ui)
{
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
    ui->SetSelectMaxNumber(MIN_MAP_CONFIG_TYPE::MAX);
    ui->SetSelectNumber(mnPreSelectNumber);
}

void MinimapConfigState::OnExit(UIBase* ui)
{
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
    ui->SetSelectMaxNumber(SOUND_CONFIG_TYPE::MAX);
    ui->SetSelectNumber(mnPreSelectNumber);
}

void SoundConfigState::OnExit(UIBase* ui)
{
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
    ui->SetSelectMaxNumber(CAMERA_CONFIG_TYPE::MAX);
    ui->SetSelectNumber(mnPreSelectNumber);
}

void CameraConfigState::OnExit(UIBase* ui)
{
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
}

int CameraConfigState::Cloce(UIBase* ui)
{
    return GetConfigStateNumber(CONFIG_UI_STATE::SELECT_CONFIG_STATE);
}