#include <map>
#include <vector>

#invlude "ResourceData.h"
#include "Vector2.h"

#include "DxLib.h"

#include "Master.h"

#include "DataManager.h"
#include "FadeManager.h"
#include "FSM.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "StateTitleUI.h"

// TODO: このファイルの文字描画消して画面作成

/*--------------------------------*/
/*     【タイトルUIステート】     */
/*--------------------------------*/

/*----------*/
/*【タイトルUIステート共通処理用】
/*----------*/
TitleUIStateProcess::TitleUIStateProcess(TITLE_UI_STATE preUiState)
: mePreUiState(preUiState)
, mnPreSelectNumber(-1)
{
}

// 背景描画
void TitleUIStateProcess::DrawBackground(UIBase* ui, std::vector<std::string> str)
{

	// 背景
	if (ui->GetMovieHandleCount() >= 1)
	{
	// 	int handle = ui->GetMovieHandles()[0];

	// 	DisplaySize displaySize = ResourceManager::mstDisplaySize;
	// 	Vector2_Int leftUp = Vector2(displaySize.Left_RatioWidth(-(BackSize - 1.0f)) + mfBackGraphTime, displaySize.Up_RatioHeight(-((BackSize - 1.0f) * 0.5f)));
	// 	Vector2_Int leftDown = Vector2(displaySize.Left_RatioWidth(-(BackSize - 1.0f)) + mfBackGraphTime, displaySize.Up_RatioHeight(((BackSize - 1.0f) * 0.5f) + 1.0f));
	// 	Vector2_Int rightUp = Vector2(displaySize.Left_RatioWidth(1.0f) + mfBackGraphTime, displaySize.Up_RatioHeight(-((BackSize - 1.0f) * 0.5f)));
	// 	Vector2_Int rightDown = Vector2(displaySize.Left_RatioWidth(1.0f) + mfBackGraphTime, displaySize.Up_RatioHeight(((BackSize - 1.0f) * 0.5f) + 1.0f));

	// 	Master::mpResourceManager->DrawData_Graph(Master::mpResourceManager->GetDrawGraphData(handle, leftUp, rightUp, leftDown, rightDown));
		
	// 	leftUp = Vector2(displaySize.Left_RatioWidth(-(BackSize - 1.0f)) + mfBackGraphTime, displaySize.Up_RatioHeight(-((BackSize - 1.0f) * 0.5f)));
	// 	leftDown = Vector2(displaySize.Left_RatioWidth(-(BackSize - 1.0f)) + mfBackGraphTime, displaySize.Up_RatioHeight(((BackSize - 1.0f) * 0.5f) + 1.0f));
	// 	rightUp = Vector2(displaySize.Left_RatioWidth(-((BackSize * 2) - 1.0f)) + mfBackGraphTime, displaySize.Up_RatioHeight(-((BackSize - 1.0f) * 0.5f)));
	// 	rightDown = Vector2(displaySize.Left_RatioWidth(-((BackSize * 2) - 1.0f)) + mfBackGraphTime, displaySize.Up_RatioHeight(((BackSize - 1.0f) * 0.5f) + 1.0f));

	// 	Master::mpResourceManager->DrawData_Graph(Master::mpResourceManager->GetDrawGraphData(handle, leftUp, rightUp, leftDown, rightDown));

	// 	leftUp = Vector2(displaySize.Left_RatioWidth(-((BackSize * 3) - 1.0f)) + mfBackGraphTime, displaySize.Up_RatioHeight(-((BackSize - 1.0f) * 0.5f)));
	// 	leftDown = Vector2(displaySize.Left_RatioWidth(-((BackSize * 3) - 1.0f)) + mfBackGraphTime, displaySize.Up_RatioHeight(((BackSize - 1.0f) * 0.5f) + 1.0f));
	// 	rightUp = Vector2(displaySize.Left_RatioWidth(-((BackSize * 2) - 1.0f)) + mfBackGraphTime, displaySize.Up_RatioHeight(-((BackSize - 1.0f) * 0.5f)));
	// 	rightDown = Vector2(displaySize.Left_RatioWidth(-((BackSize * 2) - 1.0f)) + mfBackGraphTime, displaySize.Up_RatioHeight(((BackSize - 1.0f) * 0.5f) + 1.0f));

	// 	Master::mpResourceManager->DrawData_Graph(Master::mpResourceManager->GetDrawGraphData(handle, leftUp, rightUp, leftDown, rightDown));
	}
		
	// 選択
	{
		DisplaySize displaySize = ResourceManager::mstDisplaySize;
		Vector2_Int leftUp = displaySize.LeftUp_Ratio(Vector2(0.1f, 0.1f + (0.2f * ui->GetSelectNumber())));
		Vector2_Int rightDown = displaySize.LeftUp_Ratio(Vector2(0.9f, 0.15f + (0.2f * ui->GetSelectNumber())));

		DrawBox(leftUp.x, leftUp.y, rightDown.x, rightDown.y, GetColor(255, 255, 255), TRUE);
		
		for (int i = 0; i < str.size(); i++)
		{
			Vector2_Int stringDrawPos = displaySize.LeftUp_Ratio(Vector2(0.5f, 0.11f + (0.2f * i)));
			DrawString(stringDrawPos.x - (str[i].size() * 5), stringDrawPos.y, str[i].c_str(), GetColor(0, 0, 0));
		}
	}
}

// この状態に入った時の処理
void TitleUIStateProcess::ProcessOnEnter(UIBase* ui)
{
	mnPreSelectNumber = -1;
}

// この状態を出る時の処理
void TitleUIStateProcess::ProcessOnExit(UIBase* ui)
{
}

// 更新
void TitleUIStateProcess::ProcessUpadate(UIBase* ui)
{
	// mfBackGraphTime += 0.2f;

	// if (mfBackGraphTime > (ResourceManager::mstDisplaySize.x * 2 * BackSize))
	// {
	// 	mfBackGraphTime = 0.0f;
	// }

	if (ui->GetMovieHandleCount() >= 1)
	{
		Master::mpResourceManager->MovieLoop(ui->GetMovieHandles()[0]);
	}

	if (mnPreSelectNumber != ui->GetSelectNumber())
	{
		std::vector<std::map<int, VECTOR>> uiPositionData = ui->GetUIPositionData(ui->GetFsm()->GetCurrentState());
		for (int i = 0; i < uiPositionData.size(); i++)
		{
			if (uiPositionData[i].find(ui->GetSelectNumber()) != uiPositionData[i].end())
			{
				ui->GetModelsController(i)->SetModelPosition(uiPositionData[i][ui->GetSelectNumber()]);
			}
		}
		mnPreSelectNumber = ui->GetSelectNumber();
	}
}

// ゲーム開始
void TitleUIStateProcess::StartGame(UIBase* ui)
{
	// TODO: セーブデータが出来たらデータ0に固定をなくす
	ui->SetSelectNumber(0);

	Master::mpDataManager->SetPlayPlayer(ui->GetSelectNumber());
	Master::mpGameManager->GetSceneManager()->SetNextScene(Master::mpDataManager->GetPlayPlayerData().mapType);
}

// セーブデータを描画
void TitleUIStateProcess::DrawSaveData(UIBase* ui, int displayPos, int playerGraphNumber)
{
	// INPROGRESS: セーブデータ
	Vector2_Int drawPos = Vector2_Int(0, 0);

	switch (displayPos)
	{
	case 0:
		drawPos = ResourceManager::mstDisplaySize;
		break;
	case 1:
		drawPos = ResourceManager::mstDisplaySize;
		break;
	case 2:
		drawPos = ResourceManager::mstDisplaySize;
		break;
	}

}

/*----------------------*/
/*【開始画面UIステート】*/
/*----------------------*/

StartTitleUIState::StartTitleUIState()
: IStateUI()
, TitleUIStateProcess(TITLE_UI_STATE::START_TITLE_UI_STATE)
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
	if (ui->GetMovieHandleCount() >= 1)
	{
		Master::mpResourceManager->PlayMovie(ui->GetMovieHandles()[0]);
	}
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
	// HACK: ハンドルで大きくした文字を描画する
    DisplaySize displaySize = ResourceManager::mstDisplaySize;

    Vector2_Int stringDrawPos = displaySize.LeftUp_Ratio(Vector2(0.5f, 0.2f));
    DrawString(stringDrawPos.x - 50, stringDrawPos.y, "タイトル", GetColor(0, 0, 0));
	stringDrawPos.y = displaySize.Up_RatioHeight(0.7f);
    DrawString(stringDrawPos.x - 50, stringDrawPos.y, "Enter", GetColor(0, 0, 0));
}

/*----------------------*/
/*【選択画面UIステート】*/
/*----------------------*/

SelectTitleUIState::SelectTitleUIState()
: IStateUI()
, TitleUIStateProcess(TITLE_UI_STATE::START_TITLE_UI_STATE)
{
	mStateNumber = (int)TITLE_UI_STATE::SELECT_TITLE_UI_STATE;
}

// この状態に入った時の処理
void SelectTitleUIState::OnEnter(UIBase* ui)
{
	ProcessOnEnter(ui);

	if (Master::mpDataManager->GetPlayerData().size() == 0)
	{
		ui->SetSelectNumber(0);
	}
	else
	{
		ui->SetSelectNumber(1);
	}
	
	ui->SetSelectMaxNumber(4);
	ui->SetSelectBoundaryValue(2);

	for(int i = 0; i < ui->GetDrawModels().size(); i++)
	{
		ui->GetAnimation(i)->SetAnimationType(ANIMATION_TYPE::FADE_OUT);
	}

	printfDx("テロップ：選択　Enter\n");
}

// この状態を出る時の処理
void SelectTitleUIState::OnExit(UIBase* ui)
{
	ProcessOnExit(ui);

	for(int i = 0; i < ui->GetDrawModels().size(); i++)
	{
		ui->GetAnimation(i)->SetAnimationType(ANIMATION_TYPE::FADE_IN);
	}
}

// 更新
int SelectTitleUIState::Update(UIBase* ui)
{
	ui->DefaultSelectProcess();
	ui->LeftRightSelectProcess();
	ui->DefaultCloce();

	ProcessUpadate(ui);

	return mStateNumber;
}

// 決定
int SelectTitleUIState::Decision(UIBase* ui)
{
	/*/
	switch (ui->GetSelectNumber())
	{
	case 0:
	case 1:
	case 2:
	case 3:
		return (int)TITLE_UI_STATE::DATA_SELECT_TITLE_UI_STATE;
	}
	/*/
	switch (ui->GetSelectNumber())
	{
	case 0:
		break;
		return (int)TITLE_UI_STATE::NEW_DATA_CHECK_TITLE_UI_STATE;
									
	case 1:							
		return (int)TITLE_UI_STATE::DATA_SELECT_TITLE_UI_STATE;
		
	case 2:
		break;
		return (int)TITLE_UI_STATE::TUTORIAL_TITLE_UI_STATE;
		
	case 3:
		break;
		return (int)TITLE_UI_STATE::SETTING_TITLE_UI_STATE;
	}//*/

	return mStateNumber;
}

// 戻る
int SelectTitleUIState::Cloce(UIBase* ui)
{
	return GetPreUiState();
}

// 描画
void SelectTitleUIState::Draw(UIBase* ui)
{
	std::vector<std::string> str;
	str.push_back("新しく始める");
	str.push_back("データを選択");
	str.push_back("チュートリアル");
	str.push_back("設定");
	DrawBackground(ui, str);
}

/*------------------------------------------------*/
/*【新しいデータの入る場所があるか確認UIステート】*/
/*------------------------------------------------*/

NewDataCheckTitleUIState::NewDataCheckTitleUIState()
: IStateUI()
, TitleUIStateProcess(TITLE_UI_STATE::SELECT_TITLE_UI_STATE)
{
	mStateNumber = (int)TITLE_UI_STATE::NEW_DATA_CHECK_TITLE_UI_STATE;
}

// この状態に入った時の処理
void NewDataCheckTitleUIState::OnEnter(UIBase* ui)
{
	ProcessOnEnter(ui);

	// TODO: ステートを作って機能を追加する 確認用ステートに移動
}

// この状態を出る時の処理
void NewDataCheckTitleUIState::OnExit(UIBase* ui)
{
	ProcessOnExit(ui);
}

// 更新
int NewDataCheckTitleUIState::Update(UIBase* ui)
{
	ui->DefaultDecision();
	ui->DefaultCloce();

	ProcessUpadate(ui);

	return mStateNumber;
}

// 決定
int NewDataCheckTitleUIState::Decision(UIBase* ui)
{
	return (int)TITLE_UI_STATE::CHARACTER_SELECT_TITLE_UI_STATE;
}

// 戻る
int NewDataCheckTitleUIState::Cloce(UIBase* ui)
{
	return GetPreUiState();
}

// 描画
void NewDataCheckTitleUIState::Draw(UIBase* ui)
{
	std::vector<std::string> str;
	str.push_back("新しデータを作りますか?");
	DrawBackground(ui, str);
}

/*----------------------------*/
/*【データ選択画面UIステート】*/
/*----------------------------*/

DataSelectTitleUIState::DataSelectTitleUIState()
: IStateUI()
, TitleUIStateProcess(TITLE_UI_STATE::SELECT_TITLE_UI_STATE)
{
	mStateNumber = (int)TITLE_UI_STATE::DATA_SELECT_TITLE_UI_STATE;
}

// この状態に入った時の処理
void DataSelectTitleUIState::OnEnter(UIBase* ui)
{
	ProcessOnEnter(ui);

	ui->SetSelectNumber(0);
	ui->SetSelectMaxNumber((const int)Master::mpDataManager->GetPlayerData().size());

	printfDx("テロップ：情報選択　Enter\n");
}

// この状態を出る時の処理
void DataSelectTitleUIState::OnExit(UIBase* ui)
{
	ProcessOnExit(ui);
}

// 更新
int DataSelectTitleUIState::Update(UIBase* ui)
{
	ui->DefaultSelectProcess();
	ui->DefaultCloce();

	ProcessUpadate(ui);

	return mStateNumber;
}

// 決定
int DataSelectTitleUIState::Decision(UIBase* ui)
{
	StartGame(ui);
	return mStateNumber;
}

// 戻る
int DataSelectTitleUIState::Cloce(UIBase* ui)
{
	return GetPreUiState();
}

// 描画
void DataSelectTitleUIState::Draw(UIBase* ui)
{
	std::vector<std::string> str;
	str.push_back("セーブデータ(今は一つ)");
	DrawBackground(ui, str);
}

/*----------------------------*/
/*【チュートリアルUIステート】*/
/*----------------------------*/

TutorialTitleUIState::TutorialTitleUIState()
: IStateUI()
, TitleUIStateProcess(TITLE_UI_STATE::SELECT_TITLE_UI_STATE)
{
	mStateNumber = (int)TITLE_UI_STATE::TUTORIAL_TITLE_UI_STATE;
}

// この状態に入った時の処理
void TutorialTitleUIState::OnEnter(UIBase* ui)
{
	ProcessOnEnter(ui);

}

// この状態を出る時の処理
void TutorialTitleUIState::OnExit(UIBase* ui)
{
	ProcessOnExit(ui);
}

// 更新
int TutorialTitleUIState::Update(UIBase* ui)
{
	ui->DefaultDecision();
	ui->DefaultCloce();

	ProcessUpadate(ui);

	return mStateNumber;
}

// 決定
int TutorialTitleUIState::Decision(UIBase* ui)
{
	StartGame(ui);
	return mStateNumber;
}

// 戻る
int TutorialTitleUIState::Cloce(UIBase* ui)
{
	return GetPreUiState();
}

// 描画
void TutorialTitleUIState::Draw(UIBase* ui)
{
	std::vector<std::string> str;
	str.push_back("チュートリアル開始します");
	DrawBackground(ui, str);
}

/*--------------------------*/
/*【セッティングUIステート】*/
/*--------------------------*/

SettingTitleUIState::SettingTitleUIState()
: IStateUI()
, TitleUIStateProcess(TITLE_UI_STATE::SELECT_TITLE_UI_STATE)
{
	mStateNumber = (int)TITLE_UI_STATE::SETTING_TITLE_UI_STATE;
}

// この状態に入った時の処理
void SettingTitleUIState::OnEnter(UIBase* ui)
{
	ProcessOnEnter(ui);

	ui->SetSelectNumber(0);
	ui->SetSelectMaxNumber(2);
}

// この状態を出る時の処理
void SettingTitleUIState::OnExit(UIBase* ui)
{
	ProcessOnExit(ui);
}

// 更新
int SettingTitleUIState::Update(UIBase* ui)
{
	ui->DefaultSelectProcess();
	ui->DefaultCloce();

	ProcessUpadate(ui);

	return mStateNumber;
}

// 決定
int SettingTitleUIState::Decision(UIBase* ui)
{
	switch (ui->GetSelectNumber())
	{
	case 0:
		return (int)TITLE_UI_STATE::SCREEN_SIZE_TITLE_UI_STATE;

	case 1:
		return (int)TITLE_UI_STATE::VOLUME_TITLE_UI_STATE;
	}

	return mStateNumber;
}

// 戻る
int SettingTitleUIState::Cloce(UIBase* ui)
{
	return GetPreUiState();
}

// 描画
void SettingTitleUIState::Draw(UIBase* ui)
{
	std::vector<std::string> str;
	str.push_back("設定");
	DrawBackground(ui, str);
}

/*----------------------------*/
/*【キャラクター種類選択UIステート】*/
/*----------------------------*/

CharacterSelectTitleUIState::CharacterSelectTitleUIState()
: IStateUI()
, TitleUIStateProcess(TITLE_UI_STATE::SELECT_TITLE_UI_STATE)
{
	mStateNumber = (int)TITLE_UI_STATE::CHARACTER_SELECT_TITLE_UI_STATE;
}

// この状態に入った時の処理
void CharacterSelectTitleUIState::OnEnter(UIBase* ui)
{
	ProcessOnEnter(ui);

}

// この状態を出る時の処理
void CharacterSelectTitleUIState::OnExit(UIBase* ui)
{
	ProcessOnExit(ui);
}

// 更新
int CharacterSelectTitleUIState::Update(UIBase* ui)
{
	ui->DefaultDecision();
	ui->DefaultCloce();

	ProcessUpadate(ui);

	return mStateNumber;
}

// 決定
int CharacterSelectTitleUIState::Decision(UIBase* ui)
{
	return (int)TITLE_UI_STATE::PLAYER_NAME_TITLE_UI_STATE;
}

// 戻る
int CharacterSelectTitleUIState::Cloce(UIBase* ui)
{
	return GetPreUiState();
}

// 描画
void CharacterSelectTitleUIState::Draw(UIBase* ui)
{
	std::vector<std::string> str;
	str.push_back("キャラクターを選択してください");
	DrawBackground(ui, str);
}

/*----------------------------*/
/*【プレイヤー名設定UIステート】*/
/*----------------------------*/

PlayerNameTitleUIState::PlayerNameTitleUIState()
: IStateUI()
, TitleUIStateProcess(TITLE_UI_STATE::CHARACTER_SELECT_TITLE_UI_STATE)
{
	mStateNumber = (int)TITLE_UI_STATE::PLAYER_NAME_TITLE_UI_STATE;
}

// この状態に入った時の処理
void PlayerNameTitleUIState::OnEnter(UIBase* ui)
{
	ProcessOnEnter(ui);

}

// この状態を出る時の処理
void PlayerNameTitleUIState::OnExit(UIBase* ui)
{
	ProcessOnExit(ui);
}

// 更新
int PlayerNameTitleUIState::Update(UIBase* ui)
{
	ui->DefaultDecision();
	ui->DefaultCloce();

	ProcessUpadate(ui);

	return mStateNumber;
}

// 決定
int PlayerNameTitleUIState::Decision(UIBase* ui)
{
	return (int)TITLE_UI_STATE::INPUT_CHECK_TITLE_UI_STATE;
}

// 戻る
int PlayerNameTitleUIState::Cloce(UIBase* ui)
{
	return GetPreUiState();
}

// 描画
void PlayerNameTitleUIState::Draw(UIBase* ui)
{
	std::vector<std::string> str;
	str.push_back("名前を入力してください");
	DrawBackground(ui, str);
}

/*----------------------------*/
/*【入力情報の最終確認UIステート】*/
/*----------------------------*/

InputCheckTitleUIState::InputCheckTitleUIState()
: IStateUI()
, TitleUIStateProcess(TITLE_UI_STATE::PLAYER_NAME_TITLE_UI_STATE)
{
	mStateNumber = (int)TITLE_UI_STATE::INPUT_CHECK_TITLE_UI_STATE;
}

// この状態に入った時の処理
void InputCheckTitleUIState::OnEnter(UIBase* ui)
{
	ProcessOnEnter(ui);

}

// この状態を出る時の処理
void InputCheckTitleUIState::OnExit(UIBase* ui)
{
	ProcessOnExit(ui);
}

// 更新
int InputCheckTitleUIState::Update(UIBase* ui)
{
	ui->DefaultDecision();
	ui->DefaultCloce();

	ProcessUpadate(ui);

	return mStateNumber;
}

// 決定
int InputCheckTitleUIState::Decision(UIBase* ui)
{
	StartGame(ui);
	return mStateNumber;
}

// 戻る
int InputCheckTitleUIState::Cloce(UIBase* ui)
{
	return GetPreUiState();
}

// 描画
void InputCheckTitleUIState::Draw(UIBase* ui)
{
	std::vector<std::string> str;
	str.push_back("このデータでいいですか?");
	DrawBackground(ui, str);
}

/*----------------------------*/
/*【画面サイズ調整UIステート】*/
/*----------------------------*/

ScreenSizeTitleUIState::ScreenSizeTitleUIState()
: IStateUI()
, TitleUIStateProcess(TITLE_UI_STATE::SETTING_TITLE_UI_STATE)
{
	mStateNumber = (int)TITLE_UI_STATE::SCREEN_SIZE_TITLE_UI_STATE;
}

// この状態に入った時の処理
void ScreenSizeTitleUIState::OnEnter(UIBase* ui)
{
	ProcessOnEnter(ui);

}

// この状態を出る時の処理
void ScreenSizeTitleUIState::OnExit(UIBase* ui)
{
	ProcessOnExit(ui);
}

// 更新
int ScreenSizeTitleUIState::Update(UIBase* ui)
{
	ui->DefaultDecision();
	ui->DefaultCloce();

	ProcessUpadate(ui);

	return mStateNumber;
}

// 決定
int ScreenSizeTitleUIState::Decision(UIBase* ui)
{
	return (int)TITLE_UI_STATE::SETTING_TITLE_UI_STATE;
}

// 戻る
int ScreenSizeTitleUIState::Cloce(UIBase* ui)
{
	return GetPreUiState();
}

// 描画
void ScreenSizeTitleUIState::Draw(UIBase* ui)
{
	std::vector<std::string> str;
	str.push_back("画面サイズの調整つ");
	DrawBackground(ui, str);
}

/*----------------------------*/
/*【音量調整UIステート】*/
/*----------------------------*/

VolumeTitleUIState::VolumeTitleUIState()
: IStateUI()
, TitleUIStateProcess(TITLE_UI_STATE::SETTING_TITLE_UI_STATE)
{
	mStateNumber = (int)TITLE_UI_STATE::VOLUME_TITLE_UI_STATE;
}

// この状態に入った時の処理
void VolumeTitleUIState::OnEnter(UIBase* ui)
{
	ProcessOnEnter(ui);

}

// この状態を出る時の処理
void VolumeTitleUIState::OnExit(UIBase* ui)
{
	ProcessOnExit(ui);
}

// 更新
int VolumeTitleUIState::Update(UIBase* ui)
{
	ui->DefaultDecision();
	ui->DefaultCloce();

	ProcessUpadate(ui);

	return mStateNumber;
}

// 決定
int VolumeTitleUIState::Decision(UIBase* ui)
{
	return (int)TITLE_UI_STATE::SETTING_TITLE_UI_STATE;
}

// 戻る
int VolumeTitleUIState::Cloce(UIBase* ui)
{
	return GetPreUiState();
}

// 描画
void VolumeTitleUIState::Draw(UIBase* ui)
{
	std::vector<std::string> str;
	str.push_back("音量の調節");
	DrawBackground(ui, str);
}