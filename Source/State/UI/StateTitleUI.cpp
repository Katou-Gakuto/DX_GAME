#include <vector>

#include "DxLib.h"

#include "Master.h"

#include "DataManager.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "StateTitleUI.h"

// TODO: このファイルの文字描画消して画面作成

/*--------------------------------*/
/*     【タイトルUIステート】     */
/*--------------------------------*/

/*----------*/
/*【タイトルUIステート共通処理用】
/*----------*/

// 土台描画
void TitleUIStateProcess::BaseDraw()
{
}

/*----------------------*/
/*【開始画面UIステート】*/
/*----------------------*/

StartTitleUIState::StartTitleUIState()
{
	mStateNumber = (int)TITLE_UI_STATE::START_TITLE_UI_STATE;
}

// この状態に入った時の処理
void StartTitleUIState::OnEnter(UIBase* ui)
{
	printfDx("テロップ：開始　Enter\n");
}

// この状態を出る時の処理
void StartTitleUIState::OnExit(UIBase* ui)
{
}

// 更新
int StartTitleUIState::Update(UIBase* ui)
{
	ui->DefaultDecision();

	return mStateNumber;
}

// 決定
int StartTitleUIState::Decision(UIBase* ui)
{
	return (int)TITLE_UI_STATE::SELECT_TITLE_UI_STATE;
}

// 描画
void StartTitleUIState::Draw(UIBase* ui)
{
}

/*----------------------*/
/*【選択画面UIステート】*/
/*----------------------*/

SelectTitleUIState::SelectTitleUIState()
{
	mStateNumber = (int)TITLE_UI_STATE::SELECT_TITLE_UI_STATE;
}

// この状態に入った時の処理
void SelectTitleUIState::OnEnter(UIBase* ui)
{
	ui->SetSelectNumber(0);
	ui->SetSelectMaxNumber(4);

	printfDx("テロップ：選択　Enter\n");
}

// この状態を出る時の処理
void SelectTitleUIState::OnExit(UIBase* ui)
{
}

// 更新
int SelectTitleUIState::Update(UIBase* ui)
{
	ui->DefaultSelectProcess();

	return mStateNumber;
}

// 決定
int SelectTitleUIState::Decision(UIBase* ui)
{
	switch (ui->GetSelectNumber())
	{
	case 0:
	case 1:
	case 2:
	case 3:
		return (int)TITLE_UI_STATE::DATA_SELECT_TITLE_UI_STATE;
	}
	/*
	switch (ui->GetSelectNumber())
	{
	case 0:
		return (int)TITLE_UI_STATE::NEW_DATA_CHECK_TITLE_UI_STATE;
									
	case 1:							
		return (int)TITLE_UI_STATE::DATA_SELECT_TITLE_UI_STATE;
		
	case 2:
		return (int)TITLE_UI_STATE::TUTORIAL_TITLE_UI_STATE;
		
	case 3:
		return (int)TITLE_UI_STATE::SETTING_TITLE_UI_STATE;
	}*/

	return mStateNumber;
}

// 描画
void SelectTitleUIState::Draw(UIBase* ui)
{
}

/*------------------------------------------------*/
/*【新しいデータの入る場所があるか確認UIステート】*/
/*------------------------------------------------*/

NewDataCheckTitleUIState::NewDataCheckTitleUIState()
{
	mStateNumber = (int)TITLE_UI_STATE::NEW_DATA_CHECK_TITLE_UI_STATE;
}

// この状態に入った時の処理
void NewDataCheckTitleUIState::OnEnter(UIBase* ui)
{
}

// この状態を出る時の処理
void NewDataCheckTitleUIState::OnExit(UIBase* ui)
{
}

// 更新
int NewDataCheckTitleUIState::Update(UIBase* ui)
{
	ui->DefaultDecision();
	return mStateNumber;
}

// 決定
int NewDataCheckTitleUIState::Decision(UIBase* ui)
{
	return (int)TITLE_UI_STATE::SELECT_TITLE_UI_STATE;
}

// 描画
void NewDataCheckTitleUIState::Draw(UIBase* ui)
{
}

/*----------------------------*/
/*【データ選択画面UIステート】*/
/*----------------------------*/

DataSelectTitleUIState::DataSelectTitleUIState()
{
	mStateNumber = (int)TITLE_UI_STATE::DATA_SELECT_TITLE_UI_STATE;
}

// この状態に入った時の処理
void DataSelectTitleUIState::OnEnter(UIBase* ui)
{
	ui->SetSelectNumber(0);
	ui->SetSelectMaxNumber((const int)Master::mpDataManager->GetPlayerData().size());

	printfDx("テロップ：情報選択　Enter\n");
}

// この状態を出る時の処理
void DataSelectTitleUIState::OnExit(UIBase* ui)
{
}

// 更新
int DataSelectTitleUIState::Update(UIBase* ui)
{
	ui->DefaultSelectProcess();
	return mStateNumber;
}

// 決定
int DataSelectTitleUIState::Decision(UIBase* ui)
{
	Master::mpDataManager->SetPlayPlayer(ui->GetSelectNumber());
	Master::mpGameManager->GetSceneManager()->SetNextScene(Master::mpDataManager->GetPlayPlayerData().mapType);

	return mStateNumber;
}

// 描画
void DataSelectTitleUIState::Draw(UIBase* ui)
{
}

/*----------------------------*/
/*【チュートリアルUIステート】*/
/*----------------------------*/

TutorialTitleUIState::TutorialTitleUIState()
{
	mStateNumber = (int)TITLE_UI_STATE::TUTORIAL_TITLE_UI_STATE;
}

// この状態に入った時の処理
void TutorialTitleUIState::OnEnter(UIBase* ui)
{
}

// この状態を出る時の処理
void TutorialTitleUIState::OnExit(UIBase* ui)
{
}

// 更新
int TutorialTitleUIState::Update(UIBase* ui)
{
	ui->DefaultDecision();
	return mStateNumber;
}

// 決定
int TutorialTitleUIState::Decision(UIBase* ui)
{
	return (int)TITLE_UI_STATE::SELECT_TITLE_UI_STATE;
}

// 描画
void TutorialTitleUIState::Draw(UIBase* ui)
{
}

/*--------------------------*/
/*【セッティングUIステート】*/
/*--------------------------*/

SettingTitleUIState::SettingTitleUIState()
{
	mStateNumber = (int)TITLE_UI_STATE::SETTING_TITLE_UI_STATE;
}

// この状態に入った時の処理
void SettingTitleUIState::OnEnter(UIBase* ui)
{
}

// この状態を出る時の処理
void SettingTitleUIState::OnExit(UIBase* ui)
{
}

// 更新
int SettingTitleUIState::Update(UIBase* ui)
{
	ui->DefaultDecision();
	return mStateNumber;
}

// 決定
int SettingTitleUIState::Decision(UIBase* ui)
{
	return (int)TITLE_UI_STATE::SELECT_TITLE_UI_STATE;
}

// 描画
void SettingTitleUIState::Draw(UIBase* ui)
{
}
