#include "SceneEnum.h"

#include "Master.h"

#include "FSM.h"
#include "GameManager.h"
#include "ObjectBases.h"
#include "SceneManager.h"
#include "UI_GameClear.h"

UI_GameClear::UI_GameClear()
: UIBase(true, 1)
{
}

UI_GameClear::~UI_GameClear()
{
}

// UI初期化
void UI_GameClear::UIInitilize()
{
}

// UIシーン最終初期化
void UI_GameClear::UISceneLastInitilize()
{
}

// UI終了
void UI_GameClear::UIFinalize()
{
}

// UI更新
void UI_GameClear::UIUpdate()
{
}

// UI最終更新
void UI_GameClear::UILastUpdate()
{
}

// UI描画
void UI_GameClear::UIDraw()
{
}

// 選択決定時処理
void UI_GameClear::DecisionProcess()
{
    if (mpFsm != nullptr)
    {
        mpFsm->Decision(this);
    }

	Master::mpGameManager->GetSceneManager()->SetNextScene(SCENE::TITLE);
}