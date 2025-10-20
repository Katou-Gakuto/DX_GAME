#include "../Header/SceneManager.h"
#include "../Header/StateBase.h"

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