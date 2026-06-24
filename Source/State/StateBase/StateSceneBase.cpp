#include "DxLib.h"

#include "Master.h"

#include "GameManager.h"
#include "SceneManager.h"
#include "StateSceneBase.h"
#include "TargetManager.h"

/*------------------------*/
/*【シーンステートベース】*/
/*------------------------*/
IStateScene::IStateScene(std::vector<STATE_CHANGE_CRITERIA_DATA<SCENE, SceneManager>> stateChangeCriterias, SCENE stateNumber)
: StateBase(stateChangeCriterias, stateNumber)
, mpMapManager(nullptr)
, mpTargetManager(nullptr)
, mnSceneCameraID(-1)
{
}

// 状態に入った時の共通処理
void IStateScene::StageOnEnter(SceneManager* sceneManager)
{
	if (mpTargetManager == nullptr)
	{
		mpTargetManager = Master::mpGameManager->GetTargetManager();
	}
	mpTargetManager->TargetInit((unsigned int)((1 << (int)TARGET_TYPE::PLAYER) | (1 << (int)TARGET_TYPE::ENEMY)));
}