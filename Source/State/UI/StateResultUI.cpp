
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
    // シーン移動
	Master::mpGameManager->GetSceneManager()->SetNextScene(Master::mpDataManager->GetPlayPlayerData().dungeonType);

    // エネミー削除
    Master::mpDataManager->DeleteEnemyData(Master::mpDataManager->GetPlayPlayerData().dungeonType);

	return mStateNumber;
}

// 描画
void StartResultUIState::Draw(UIBase* ui)
{
	// // TODO: 画面全体に描画
    // // TODO: 画像ハンドルに変更
    // DisplaySize displaySize = ResourceManager::mstDisplaySize;
    // Vector2_Int leftUp = displaySize.LeftUp_FloatRatio(0.1f);
    // Vector2_Int rightDown = displaySize.RightDown_FloatRatio(0.1f);
    // DrawBox(leftUp.x, leftUp.y, rightDown.x, rightDown.y, GetColor(255, 255, 255), TRUE);

    // Vector2_Int stringDrawPos = displaySize.LeftUp_Ratio(Vector2(0.5f, 0.11f));
    // DrawString(stringDrawPos.x - 50, stringDrawPos.y, "リザルト", GetColor(0, 0, 0));
}
