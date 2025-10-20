#include "../Header/Master.h"

#include "../Header/DataManager.h"
#include "../Header/GameManager.h"
#include "../Header/SceneManager.h"
#include "../Header/TitleUI.h"

TitleUI::TitleUI()
: UIBase(true, 1)
{
}

TitleUI::~TitleUI()
{
}

// UI初期化
void TitleUI::UIInitilize()
{
}

// UI終了
void TitleUI::UIFinalize()
{
}

// UI更新
void TitleUI::UIUpdate()
{
}

// UI最終更新
void TitleUI::UILastUpdate()
{
}

// UI描画
void TitleUI::UIDraw()
{
}


// 選択決定時処理
void TitleUI::DecisionProcess()
{
	Master::mpGameManager->GetSceneManager()->SetNextScene(Master::mpDataManager->GetPlayPlayerData().mapType);
}