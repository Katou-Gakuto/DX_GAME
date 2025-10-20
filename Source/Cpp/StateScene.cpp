#include "../Header/FSM.h"
#include "../Header/SceneManager.h"
#include "../Header/StateBase.h"
#include "../Header/StateScene.h"

/*------------------------*/
/*【継承用シーンステート】*/
/*------------------------*/
// 更新
int IStateScene::Update(SceneManager* sceneManager)
{
	if ((int)sceneManager->GetNextScene() != sceneManager->GetFSMScene()->GetCurrentState())
	{
		return (int)sceneManager->GetNextScene();
	}

	return sceneManager->GetFSMScene()->GetCurrentState();
}


/*--------------------------*/
/*【スタートシーンステート】*/
/*--------------------------*/
StartScene::StartScene()
{
	mnStateNumber = (int)SCENE::START;
}

void StartScene::OnEnter(SceneManager* sceneManager)
{
	sceneManager->SetNextScene(SCENE::TITLE);
}
void StartScene::OnExit(SceneManager* sceneManager)
{
}