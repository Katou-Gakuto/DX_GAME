#pragma once

#include "SceneEnum.h"

class CameraManager;
class CharacterBase;
class FSMCamera;
class FSMCharacter;
class FSMScene;
class FSMUI;
class ModelBase;
class SceneManager;
class UIBase;

// キャラクター作成ナンバー
enum class CHARACTER_FACTORY_NUMBER
{
	TOWN_PLAYER = 0,
	DUNGEON_PLAYER,
	BATTLE_PLAYER,

	MAP_ENEMY,
	ENEMY,
	BOSS_ENEMY,
};

// UI作成ナンバー
enum class UI_FACTORY_NUMBER
{
	TITLE = 0,
	RESULT,
};

// TODO: 情報の種類から処理の種類に変更
// モデル作成ナンバー
enum class MODEL_FACTORY_NUMBER
{
	POLYGON_INDEXED = 0,
	MV1,
};

namespace UtilFactorys
{
	/*カメラ有限状態マシン作成*/
	FSMCamera* FSMCameraFactory();

	/*キャラクター有限状態マシン作成*/
	FSMCharacter* FSMCharacterFactory(CharacterBase* character, CHARACTER_FACTORY_NUMBER number, SCENE mapScene = SCENE::NONE);

	/*シーン有限状態マシン作成*/
	FSMScene* FSMSceneFactory(SceneManager* sceneManager);

	/*UI有限状態マシン作成*/
	FSMUI* FSMUIFactory(UIBase* ui, UI_FACTORY_NUMBER number);

	/*モデル作成*/
	ModelBase* ModelFactory(MODEL_FACTORY_NUMBER number);
};