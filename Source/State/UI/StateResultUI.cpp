
#include "Master.h"

#include "DataManager.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "StateResultUI.h"

/*--------------------------------*/
/*     【タイトルUIステート】     */
/*--------------------------------*/

/*----------------------*/
/*【開始画面UIステート】*/
/*----------------------*/

StartResultUIState::StartResultUIState()
{
	mStateNumber = (int)RESULT_UI_STATE::START_RESULT_UI_STATE;
}

// この状態に入った時の処理
void StartResultUIState::OnEnter(UIBase* ui)
{
}

// この状態を出る時の処理
void StartResultUIState::OnExit(UIBase* ui)
{
}

// 更新
int StartResultUIState::Update(UIBase* ui)
{
	ui->DefaultDecision();

	return mStateNumber;
}

// 決定
int StartResultUIState::Decision(UIBase* ui)
{
	Master::mpGameManager->GetSceneManager()->SetNextScene(Master::mpDataManager->GetPlayPlayerData().dungeonType);

	return mStateNumber;
}

// 描画
void StartResultUIState::Draw(UIBase* ui)
{
}
