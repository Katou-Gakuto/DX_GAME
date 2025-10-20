#include "../Header/FSM.h"
#include "../Header/SceneManager.h"
#include "../Header/StateScene.h"
#include "../Header/UtilFactorys.h"

// ƒV[ƒ“ì¬
FSMScene* UtilFactorys::Scenefactory(SceneManager* sceneManager)
{
	FSMScene* fsmScene = new FSMScene();

	fsmScene->RegisterState(new StartScene());

	fsmScene->SetCurrentState((int)SCENE::START, sceneManager);

	return fsmScene;
}