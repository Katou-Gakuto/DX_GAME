#pragma once

class CameraManager;
class CharacterBase;
class FSMCamera;
class FSMCharacter;
class FSMScene;
class FSMUI;
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
};

// UI作成ナンバー
enum class UI_FACTORY_NUMBER
{
	TITLE = 0,
	RESULT,
};

namespace UtilFactorys
{
	/*カメラ有限状態マシン作成*/
	FSMCamera* FSMCameraFactory();

	/*キャラクター有限状態マシン作成*/
	FSMCharacter* FSMCharacterFactory(CharacterBase* character, CHARACTER_FACTORY_NUMBER number);

	/*シーン有限状態マシン作成*/
	FSMScene* FSMSceneFactory(SceneManager* sceneManager);

	/*UI有限状態マシン作成*/
	FSMUI* FSMUIFactory(UIBase* ui, UI_FACTORY_NUMBER number);
};