#include "SceneEnum.h"

#include "Master.h"

#include "FSMUI.h"
#include "GameManager.h"
#include "ObjectBase_UI.h"
#include "SceneManager.h"
#include "UI_GameClear.h"

UI_GameClear::UI_GameClear()
: UIBase(true, 1)
{
}

UI_GameClear::~UI_GameClear()
{
}

// UI‰Šú‰»
void UI_GameClear::UIInitilize()
{
}

// UIƒV[ƒ“ÅI‰Šú‰»
void UI_GameClear::UISceneLastInitilize()
{
}

// UII—¹
void UI_GameClear::UIFinalize()
{
}

// UIXV
void UI_GameClear::UIUpdate()
{
}

// UIÅIXV
void UI_GameClear::UILastUpdate()
{
}

// UI•`‰æ
void UI_GameClear::UIDraw()
{
}

// ‘I‘ðŒˆ’èŽžˆ—
void UI_GameClear::DecisionProcess()
{
    if (mpFsm != nullptr)
    {
        mpFsm->Decision(this);
    }

	Master::mpGameManager->GetSceneManager()->SetNextScene(SCENE::TITLE);
}