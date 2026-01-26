#include "CharacterEnum.h"
#include "AnimationData.h"
#include "CameraData.h"
#include "GameDatas.h"

#include "Master.h"

#include "AttackManager.h"
#include "CameraManager.h"
#include "Character_Map.h"
#include "Character_Shot.h"
#include "DataManager.h"
#include "EndManager.h"
#include "FSM.h"
#include "GameManager.h"
#include "MapManager.h"
#include "ModelsControllerBase.h"
#include "ObjectBases.h"
#include "UI_Result.h"
#include "SceneManager.h"
#include "StateBase.h"
#include "StateScene.h"
#include "TargetManager.h"
#include "UI_Game.h"
#include "UI_Title.h"
#include "UtilCalc.h"
#include "UtilFactorys.h"

// TODO: 町、ダンジョン記録を関数化、プレイヤー、エネミー、カメラ生成ファクトリーに移す エネミー移動先データマネージャーから受け取るようにする

/*----------*/
/*【シーンステート共通処理用】
/*----------*/

// TODO: シーンナンバーをファクトリーナンバーに変換する仕組みを作る
// キャラクターモデル設定
void SceneStateProcess::CharacterModelSetting(CharacterBase* character, ANIMATION_FACTORY_NUMBER animationFactoryNumber)
{
	// モデル設定
	character->GetModelsController()->AddModel(UtilFactorys::ModelFactory(MODEL_TYPE::MV1_MODEL, "../Resource/3D/Robot/robotSphere.mv1", UtilCalc::VZero, UtilCalc::VZero, VScale(UtilCalc::VOne, 20.0f)));
	//character->GetModelsController()->AddModel(UtilFactorys::ModelFactory(MODEL_TYPE::MV1_MODEL, "../Resource/3D/Human/Hero.x"));
	// アニメション設定
	 {
	 	AnimationBase* characterAnimation = character->GetAnimation();
	 	std::vector<std::vector<LoadAnimationData>> setcharacterLoadAnimationData;
	 	// 読み込み用アニメーションデータ設定
	 	setcharacterLoadAnimationData.push_back(UtilFactorys::LoadAnimationDataFactory(characterAnimation, LOAD_ANIMATION_DATA_FACTORY_NUMBER::ROBOT));
	 	// アニメーション有限状態マシン設定
	 	characterAnimation->SetFsm(UtilFactorys::FSMAnimationFactory(characterAnimation, animationFactoryNumber, LOAD_ANIMATION_DATA_FACTORY_NUMBER::ROBOT, setcharacterLoadAnimationData));
	 }
}

/*--------------------------*/
/*【スタートシーンステート】*/
/*--------------------------*/
StartScene::StartScene()
: IStateScene()
, SceneStateProcess()
{
	mbStartFlag = false;
	mStateNumber = SCENE::START;
}

void StartScene::OnEnter(SceneManager* sceneManager)
{
	Master::mpEndManager->SetEndFlag(mbStartFlag, END_FLAG_NUMBER::START_SCENE_FLAG);
	mbStartFlag = true;
	sceneManager->SetNextScene(SCENE::TITLE);
}

void StartScene::OnExit(SceneManager* sceneManager)
{
}


/*--------------------------*/
/*【タイトルシーンステート】*/
/*--------------------------*/
TitleScene::TitleScene()
: IStateScene()
, SceneStateProcess()
{
	mStateNumber = SCENE::TITLE;
}

void TitleScene::OnEnter(SceneManager* sceneManager)
{
	// マップ処理
	if (mpMapManager == nullptr)
	{
		mpMapManager = Master::mpGameManager->GetMapManager();
	}
	mpMapManager->SetMapData(MapType::None);

	UI_Title* title = new UI_Title();
	title->Initilize();
	title->SetFsm(UtilFactorys::FSMUIFactory(title, UI_FACTORY_NUMBER::TITLE));

	// カメラ作成
	{
		CameraData cameraData = CameraData();
		cameraData.cameraMode = CAMERA_MODE::FIXED;
		cameraData.position = VGet(0.0f, 180.0f, -180.0f);
		cameraData.targetPosition = VGet(0.0f, 180.0f, 0.0f);
		cameraData.threeDFlag = true;
		cameraData.SetColor(F4Get(128, 128, 128, 0));
		mnSceneCameraID = Master::mpGameManager->GetCameraManager()->NewCamera(cameraData);
		Master::mpGameManager->GetCameraManager()->SetCameraMode(mnSceneCameraID);
	}
}
void TitleScene::OnExit(SceneManager* sceneManager)
{
	// カメラ削除
	Master::mpGameManager->GetCameraManager()->DeleteCameraData(mnSceneCameraID);
	mnSceneCameraID = -1;
}


/*--------------------------*/
/*【町シーンステート】*/
/*--------------------------*/
TownScene::TownScene()
: IStateScene()
, SceneStateProcess()
{
	mStateNumber = SCENE::TOWN;
}

void TownScene::OnEnter(SceneManager* sceneManager)
{
	// マップ処理
	if (mpMapManager == nullptr)
	{
		mpMapManager = Master::mpGameManager->GetMapManager();
	}
	mpMapManager->SetMapData(MapType::Normal);

	StageOnEnter(sceneManager);

	{// 町を記録
		PLAYER_DATA playerData = Master::mpDataManager->GetPlayPlayerData();
		playerData.townType = mStateNumber;
		Master::mpDataManager->SetPlayPlayerData(playerData);
	}

	mStateNumber = sceneManager->GetNowScene();

	// プレイヤー作成
	Character_Map* player = new Character_Map(Master::mpDataManager->GetPlayPlayerData().status);
	player->Initilize();
	player->SetPos(Master::mpDataManager->GetPlayPlayerData().townPos);
	player->SetFSM(UtilFactorys::FSMCharacterFactory(player, CHARACTER_FACTORY_NUMBER::TOWN_PLAYER));
	// モデルとアニメション設定
	CharacterModelSetting(player, ANIMATION_FACTORY_NUMBER::TOWN);
	// // モデル設定
	// player->GetModelsController()->AddModel(UtilFactorys::ModelFactory(MODEL_TYPE::MV1_MODEL, "../Resource/3D/Human/Hero.x"));
	// // アニメション設定
	// {
	// 	AnimationBase* playerAnimation = player->GetAnimation();
	// 	std::vector<std::vector<LoadAnimationData>> setPlayerLoadAnimationData;
	// 	// 読み込み用アニメーションデータ設定
	// 	setPlayerLoadAnimationData.push_back(UtilFactorys::LoadAnimationDataFactory(playerAnimation, LOAD_ANIMATION_DATA_FACTORY_NUMBER::HUMAN));
	// 	// アニメーション有限状態マシン設定
	// 	playerAnimation->SetFsm(UtilFactorys::FSMAnimationFactory(playerAnimation, ANIMATION_FACTORY_NUMBER::TOWN, setPlayerLoadAnimationData));
	// }

	// カメラ作成
	{
		CameraData cameraData = CameraData();
		cameraData.cameraMode = CAMERA_MODE::PLAYER;
		cameraData.plusPosition = VGet(0.0f, 180.0f, 0.0f);
		cameraData.cameraDistance = 550.0f;
		cameraData.targetCharacter = player;
		cameraData.threeDFlag = true;
		cameraData.SetColor(F4Get(128, 128, 128, 0));
		mnSceneCameraID = Master::mpGameManager->GetCameraManager()->NewCamera(cameraData);
		Master::mpGameManager->GetCameraManager()->SetCameraMode(mnSceneCameraID);
	}

	for (int i = 0; i < 3; i++) {// 敵
		Character_Map* enemy = new Character_Map(Master::mpDataManager->GetPlayPlayerData().status);
		enemy->Initilize();
		enemy->SetPos(VGet(-150.0f, 0.0f, 500.0f));
		enemy->SetAngle(VGet(0.0f, 3.14f, 0.0f));
		enemy->SetFSM(UtilFactorys::FSMCharacterFactory(enemy, CHARACTER_FACTORY_NUMBER::MAP_ENEMY, SCENE::DUNGEON_3));
		// モデルとアニメション設定
		CharacterModelSetting(enemy, ANIMATION_FACTORY_NUMBER::TOWN);
		// // モデル設定
		// enemy->GetModelsController()->AddModel(UtilFactorys::ModelFactory(MODEL_TYPE::MV1_MODEL, "../Resource/3D/Human/Hero.x"));
		// // アニメション設定
		// {
		// 	AnimationBase* enemyAnimation = enemy->GetAnimation();
		// 	std::vector<std::vector<LoadAnimationData>> setEnemyLoadAnimationData;
		// 	// 読み込み用アニメーションデータ設定
		// 	setEnemyLoadAnimationData.push_back(UtilFactorys::LoadAnimationDataFactory(enemyAnimation, LOAD_ANIMATION_DATA_FACTORY_NUMBER::HUMAN));
		// 	// アニメーション有限状態マシン設定
		// 	enemyAnimation->SetFsm(UtilFactorys::FSMAnimationFactory(enemyAnimation, ANIMATION_FACTORY_NUMBER::TOWN, setEnemyLoadAnimationData));
		// }
	}

	// UI生成
	{
		UI_Game* gameUI = new UI_Game();
		gameUI->Initilize();
		gameUI->SetFsm(UtilFactorys::FSMUIFactory(gameUI, UI_FACTORY_NUMBER::TOWN));
	}

	switch (sceneManager->GetNowScene())
	{
	case SCENE::TOWN:
		break;
	case SCENE::TOWN_1:
		break;
	case SCENE::TOWN_2:
		break;
	case SCENE::TOWN_3:
		break;
	}
}

void TownScene::OnExit(SceneManager* sceneManager)
{
	// 前居たマップを記録
	PLAYER_DATA playerData = Master::mpDataManager->GetPlayPlayerData();
	playerData.preMap = mStateNumber;
	playerData.townPos = Master::mpGameManager->GetTargetManager()->GetTarget(TARGET_TYPE::PLAYER).target->GetPos();
	playerData.dungeonPos = UtilCalc::VZero;
	Master::mpDataManager->SetPlayPlayerData(playerData);

	// マップデータ解放
	mpMapManager->Release();

	// カメラ削除
	Master::mpGameManager->GetCameraManager()->DeleteCameraData(mnSceneCameraID);
	mnSceneCameraID = -1;
}


/*----------------------------*/
/*【ダンジョンシーンステート】*/
/*----------------------------*/
DungeonScene::DungeonScene()
: IStateScene()
, SceneStateProcess()
{
	mStateNumber = SCENE::DUNGEON;
}

void DungeonScene::OnEnter(SceneManager* sceneManager)
{
	// マップ処理
	if (mpMapManager == nullptr)
	{
		mpMapManager = Master::mpGameManager->GetMapManager();
	}
	mpMapManager->SetMapData(MapType::Normal);

	StageOnEnter(sceneManager);

	{// ダンジョンを記録
		PLAYER_DATA playerData = Master::mpDataManager->GetPlayPlayerData();
		playerData.dungeonType = mStateNumber;
		Master::mpDataManager->SetPlayPlayerData(playerData);
	}

	mStateNumber = sceneManager->GetNowScene();
	Character_Map* player = new Character_Map(Master::mpDataManager->GetPlayPlayerData().status);
	player->Initilize();
	player->SetPos(Master::mpDataManager->GetPlayPlayerData().dungeonPos);
	player->SetFSM(UtilFactorys::FSMCharacterFactory(player, CHARACTER_FACTORY_NUMBER::DUNGEON_PLAYER));
	// モデルとアニメション設定
	CharacterModelSetting(player, ANIMATION_FACTORY_NUMBER::DUNGEON);

	// カメラ作成
	{
		CameraData cameraData = CameraData();
		cameraData.cameraMode = CAMERA_MODE::PLAYER;
		cameraData.plusPosition = VGet(0.0f, 180.0f, 0.0f);
		cameraData.cameraDistance = 550.0f;
		cameraData.targetCharacter = player;
		cameraData.threeDFlag = true;
		cameraData.SetColor(F4Get(128, 128, 128, 0));
		mnSceneCameraID = Master::mpGameManager->GetCameraManager()->NewCamera(cameraData);
		Master::mpGameManager->GetCameraManager()->SetCameraMode(mnSceneCameraID);
	}

	{// 敵
		Character_Map* enemy = new Character_Map(Master::mpDataManager->GetPlayPlayerData().status);
		enemy->Initilize();
		enemy->SetPos(VGet(-150.0f, 0.0f, 300.0f));
		enemy->SetFSM(UtilFactorys::FSMCharacterFactory(enemy, CHARACTER_FACTORY_NUMBER::MAP_ENEMY, SCENE::BATTLE_2));
		// モデルとアニメション設定
		CharacterModelSetting(enemy, ANIMATION_FACTORY_NUMBER::DUNGEON);
	}
	{// 敵
		Character_Map* enemy = new Character_Map(Master::mpDataManager->GetPlayPlayerData().status);
		enemy->Initilize();
		enemy->SetPos(VGet(3000.0f, 0.0f, 3500.0f));
		enemy->SetFSM(UtilFactorys::FSMCharacterFactory(enemy, CHARACTER_FACTORY_NUMBER::MAP_ENEMY, SCENE::BATTLE_3));
		// モデルとアニメション設定
		CharacterModelSetting(enemy, ANIMATION_FACTORY_NUMBER::DUNGEON);
	}
	{// 敵
		Character_Map* enemy = new Character_Map(Master::mpDataManager->GetPlayPlayerData().status);
		enemy->Initilize();
		enemy->SetPos(VGet(2000.0f, 0.0f, 500.0f));
		enemy->SetFSM(UtilFactorys::FSMCharacterFactory(enemy, CHARACTER_FACTORY_NUMBER::MAP_ENEMY, SCENE::BATTLE_2));
		// モデルとアニメション設定
		CharacterModelSetting(enemy, ANIMATION_FACTORY_NUMBER::DUNGEON);
	}
	{// 敵
		Character_Map* enemy = new Character_Map(Master::mpDataManager->GetPlayPlayerData().status);
		enemy->Initilize();
		enemy->SetPos(VGet(1000.0f, 0.0f, 2000.0f));
		enemy->SetFSM(UtilFactorys::FSMCharacterFactory(enemy, CHARACTER_FACTORY_NUMBER::MAP_ENEMY, SCENE::BATTLE_2));
		// モデルとアニメション設定
		CharacterModelSetting(enemy, ANIMATION_FACTORY_NUMBER::DUNGEON);
	}

	// UI生成
	{
		UI_Game* gameUI = new UI_Game();
		gameUI->Initilize();
		gameUI->SetFsm(UtilFactorys::FSMUIFactory(gameUI, UI_FACTORY_NUMBER::TOWN));
	}

	switch (sceneManager->GetNowScene())
	{
	case SCENE::DUNGEON:
		break;
	case SCENE::DUNGEON_1:
		break;
	case SCENE::DUNGEON_2:
		break;
	case SCENE::DUNGEON_3:
		break;
	}
}
void DungeonScene::OnExit(SceneManager* sceneManager)
{
	// 前居たマップを記録
	PLAYER_DATA playerData = Master::mpDataManager->GetPlayPlayerData();
	playerData.preMap = mStateNumber;
	playerData.dungeonPos = Master::mpGameManager->GetTargetManager()->GetTarget(TARGET_TYPE::PLAYER).target->GetPos();
	Master::mpDataManager->SetPlayPlayerData(playerData);

	// マップデータ解放
	mpMapManager->Release();

	// カメラ削除
	Master::mpGameManager->GetCameraManager()->DeleteCameraData(mnSceneCameraID);
	mnSceneCameraID = -1;
}


/*------------------------*/
/*【バトルシーンステート】*/
/*------------------------*/
BattleScene::BattleScene()
: IStateScene()
, SceneStateProcess()
{
	mStateNumber = SCENE::BATTLE;
}

void BattleScene::OnEnter(SceneManager* sceneManager)
{
	// マップ処理
	if (mpMapManager == nullptr)
	{
		mpMapManager = Master::mpGameManager->GetMapManager();
	}
	mpMapManager->SetMapData(MapType::Battle);

	StageOnEnter(sceneManager);

	mStateNumber = sceneManager->GetNowScene();

	CharacterBase* player = nullptr;
	switch (Master::mpDataManager->GetPlayPlayerData().status.characterType)
	{
	case CHARACTER_TYPE::ROBOT:
		// TODO: アニメーションを設定してから
	{
		// HACK: 仮テキトウ実装
		std::map<ATTACK_METHOD_TYPE, CharacterAttackData> playerAttackData;
		playerAttackData[ATTACK_METHOD_TYPE::NORMAL] = UtilFactorys::CharacterAttackDataFactory(CHARACTER_ATTACK_DATA_FACTORY__ATTACK_METHOD::SHOT_NORMAL, CHARACTER_ATTACK_DATA_FACTORY__MODEL_TYPE::ROBOT);
		playerAttackData[ATTACK_METHOD_TYPE::SPCEIAL] = UtilFactorys::CharacterAttackDataFactory(CHARACTER_ATTACK_DATA_FACTORY__ATTACK_METHOD::SHOT_SPCEIAL, CHARACTER_ATTACK_DATA_FACTORY__MODEL_TYPE::ROBOT);

		player = new Character_Shot(true, Master::mpDataManager->GetPlayPlayerData().status, SHOT_TYPE::DEFAULT, playerAttackData, UtilFactorys::AttackDataFactory(CHARACTER_ATTACK_DATA_FACTORY__MODEL_TYPE::ROBOT, ATTACK_DATA_FACTORY__OBJECT_ATTACK_TYPE::SHOT));
		player->Initilize();
		player->SetPos(VGet(10.0f, 0.0f, 10.0f));
	}
		break;
	}
	player->SetFSM(UtilFactorys::FSMCharacterFactory(player, CHARACTER_FACTORY_NUMBER::BATTLE_PLAYER));
	// モデルとアニメション設定
	CharacterModelSetting(player, ANIMATION_FACTORY_NUMBER::BATTLE);

	// カメラ作成
	{
		CameraData cameraData = CameraData();
		cameraData.cameraMode = CAMERA_MODE::PLAYER;
		cameraData.plusPosition = VGet(0.0f, 180.0f, 0.0f);
		cameraData.cameraDistance = 550.0f;
		cameraData.targetCharacter = player;
		cameraData.threeDFlag = true;
		cameraData.SetColor(F4Get(128, 128, 128, 0));
		mnSceneCameraID = Master::mpGameManager->GetCameraManager()->NewCamera(cameraData);
		Master::mpGameManager->GetCameraManager()->SetCameraMode(mnSceneCameraID);
	}

	{// 敵
		// HACK: 仮テキトウ実装
		std::map<ATTACK_METHOD_TYPE, CharacterAttackData> enemyAttackData;
		enemyAttackData[ATTACK_METHOD_TYPE::NORMAL] = UtilFactorys::CharacterAttackDataFactory(CHARACTER_ATTACK_DATA_FACTORY__ATTACK_METHOD::SHOT_NORMAL, CHARACTER_ATTACK_DATA_FACTORY__MODEL_TYPE::ROBOT);
		enemyAttackData[ATTACK_METHOD_TYPE::SPCEIAL] = UtilFactorys::CharacterAttackDataFactory(CHARACTER_ATTACK_DATA_FACTORY__ATTACK_METHOD::SHOT_SPCEIAL, CHARACTER_ATTACK_DATA_FACTORY__MODEL_TYPE::ROBOT);
		{
			// enemyAttackData[ATTACK_METHOD_TYPE::NORMAL] = CharacterAttackData();
			// enemyAttackData[ATTACK_METHOD_TYPE::NORMAL].modelData.push_back(UtilFactorys::ModelFactory(MODEL_TYPE::MV1_MODEL, "../Resource/3D/Robot/robotSphere.mv1", UtilCalc::VZero, UtilCalc::VZero, VScale(UtilCalc::VOne, 20.0f)));
			
		 	//std::vector<std::vector<LoadAnimationData>> setcharacterLoadAnimationData;
	 		// 読み込み用アニメーションデータ設定
		 	//setcharacterLoadAnimationData.push_back(UtilFactorys::LoadAnimationDataFactory(nullptr, LOAD_ANIMATION_DATA_FACTORY_NUMBER::SHOT_ATTACK));

			//enemyAttackData[ATTACK_METHOD_TYPE::NORMAL].animationFSM = UtilFactorys::FSMAnimationFactory(nullptr, ANIMATION_FACTORY_NUMBER::ATTACK, LOAD_ANIMATION_DATA_FACTORY_NUMBER::ROBOT, setcharacterLoadAnimationData);
		}
		Character_Shot* enemy = new Character_Shot(true, Master::mpDataManager->GetPlayPlayerData().status, SHOT_TYPE::DEFAULT, enemyAttackData, UtilFactorys::AttackDataFactory(CHARACTER_ATTACK_DATA_FACTORY__MODEL_TYPE::ROBOT, ATTACK_DATA_FACTORY__OBJECT_ATTACK_TYPE::SHOT));
		enemy->Initilize();
		enemy->SetPos(VGet(0.0f, 0.0f, 300.0f));
		enemy->SetFSM(UtilFactorys::FSMCharacterFactory(enemy, CHARACTER_FACTORY_NUMBER::ENEMY));
		// モデルとアニメション設定
		CharacterModelSetting(enemy, ANIMATION_FACTORY_NUMBER::BATTLE);
	}

	// UI生成
	{
		UI_Game* gameUI = new UI_Game();
		gameUI->Initilize();
		gameUI->SetFsm(UtilFactorys::FSMUIFactory(gameUI, UI_FACTORY_NUMBER::TOWN));
	}

	switch (sceneManager->GetNowScene())
	{
	case SCENE::BATTLE :
		break;
	case SCENE::BATTLE_1:
		break;
	case SCENE::BATTLE_2:
		break;
	case SCENE::BATTLE_3:
	{// ボス
		// HACK: 仮テキトウ実装
		std::map<ATTACK_METHOD_TYPE, CharacterAttackData> enemyAttackData;
		enemyAttackData[ATTACK_METHOD_TYPE::NORMAL] = UtilFactorys::CharacterAttackDataFactory(CHARACTER_ATTACK_DATA_FACTORY__ATTACK_METHOD::SHOT_NORMAL, CHARACTER_ATTACK_DATA_FACTORY__MODEL_TYPE::ROBOT);
		enemyAttackData[ATTACK_METHOD_TYPE::SPCEIAL] = UtilFactorys::CharacterAttackDataFactory(CHARACTER_ATTACK_DATA_FACTORY__ATTACK_METHOD::SHOT_SPCEIAL, CHARACTER_ATTACK_DATA_FACTORY__MODEL_TYPE::ROBOT);
		//{
		//	enemyAttackData[ATTACK_METHOD_TYPE::NORMAL] = CharacterAttackData();
		//	enemyAttackData[ATTACK_METHOD_TYPE::NORMAL].modelData.push_back(UtilFactorys::ModelFactory(MODEL_TYPE::MV1_MODEL, "../Resource/3D/Robot/robotSphere.mv1", UtilCalc::VZero, UtilCalc::VZero, VScale(UtilCalc::VOne, 20.0f)));
		//	
		// 	//std::vector<std::vector<LoadAnimationData>> setcharacterLoadAnimationData;
	 //		// 読み込み用アニメーションデータ設定
		// 	//setcharacterLoadAnimationData.push_back(UtilFactorys::LoadAnimationDataFactory(nullptr, LOAD_ANIMATION_DATA_FACTORY_NUMBER::SHOT_ATTACK));

		//	//enemyAttackData[ATTACK_METHOD_TYPE::NORMAL].animationFSM = UtilFactorys::FSMAnimationFactory(nullptr, ANIMATION_FACTORY_NUMBER::ATTACK, LOAD_ANIMATION_DATA_FACTORY_NUMBER::ROBOT, setcharacterLoadAnimationData);
		//}

		Character_Shot* enemy = new Character_Shot(true, Master::mpDataManager->GetPlayPlayerData().status, SHOT_TYPE::DEFAULT, enemyAttackData, UtilFactorys::AttackDataFactory(CHARACTER_ATTACK_DATA_FACTORY__MODEL_TYPE::ROBOT, ATTACK_DATA_FACTORY__OBJECT_ATTACK_TYPE::SHOT));
		enemy->Initilize();
		enemy->SetPos(VGet(3500.0f, 0.0f, 3500.0f));
		enemy->SetFSM(UtilFactorys::FSMCharacterFactory(enemy, CHARACTER_FACTORY_NUMBER::BOSS_ENEMY));
	}
		break;
	}
	
	// UNDONE: 削除
	printfDx("テロップ：Lで攻撃 仮実装\n");
}
void BattleScene::OnExit(SceneManager* sceneManager)
{
	// 前居たマップを記録
	PLAYER_DATA playerData = Master::mpDataManager->GetPlayPlayerData();
	playerData.preMap = mStateNumber;
	Master::mpDataManager->SetPlayPlayerData(playerData);

	// マップデータ解放
	mpMapManager->Release();

	// カメラ削除
	Master::mpGameManager->GetCameraManager()->DeleteCameraData(mnSceneCameraID);
	mnSceneCameraID = -1;

	// 攻撃削除
	Master::mpGameManager->GetAttackManager()->SetDelete();
}


/*--------------------------*/
/*【リザルトシーンステート】*/
/*--------------------------*/
ResultScene::ResultScene()
: IStateScene()
, SceneStateProcess()
{
	mStateNumber = SCENE::RESULT;
}

void ResultScene::OnEnter(SceneManager* sceneManager)
{
	UI_Result* result = new UI_Result();
	result->Initilize();
	result->SetFsm(UtilFactorys::FSMUIFactory(result, UI_FACTORY_NUMBER::RESULT));

	mStateNumber = sceneManager->GetNowScene();
	switch (sceneManager->GetNowScene())
	{
	case SCENE::RESULT:
		break;
	case SCENE::DUNGEON_RESULT:
		break;
	case SCENE::BATTLR_RESULT:
		break;
	}
}

void ResultScene::OnExit(SceneManager* sceneManager)
{
}