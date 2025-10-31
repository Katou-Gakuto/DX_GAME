#pragma once

class CameraManager;
class FSMCamera;
class FSMScene;
class FSMUI;
class SceneManager;
class UIBase;

// UI作成ナンバー
enum class UI_FACTORY_NUMBER
{
	TITLE = 0,
};

namespace UtilFactorys
{
	/*カメラ有限状態マシン作成*/
	FSMCamera* FSMCameraFactory();

	/*シーン有限状態マシン作成*/
	FSMScene* FSMSceneFactory(SceneManager* sceneManager);

	/*UI有限状態マシン作成*/
	FSMUI* FSMUIFactory(UIBase* ui, UI_FACTORY_NUMBER number);
};