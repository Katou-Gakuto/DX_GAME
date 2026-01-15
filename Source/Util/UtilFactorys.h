#pragma once
#include <iostream>
#include <map>
#include <string>

#include "SceneEnum.h"
#include "AnimationData.h"

enum class MODEL_TYPE;

class CameraManager;
class CharacterBase;
class FSMCamera;
class FSMCharacter;
class FSMScene;
class FSMUI;
class ModelBase;
class SceneManager;
class UIBase;

// アニメション作成ナンバー
enum class ANIMATION_FACTORY_NUMBER
{
	// TODO: 仮でシーン名でやっている
	TOWN = 0,
};

// 読み込み用アニメーションデータ作成ナンバー
enum class LOAD_ANIMATION_DATA_FACTORY_NUMBER
{
	HUMAN = 0,
};

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

namespace UtilFactorys
{
	// HACK: データマネージャーから受け取るようにするまでの簡易処置(第二引数)
	/// <summary>アニメーション有限状態マシン作成</summary>
	/// <param name="animationData">アニメーション情報</param>
	/// <param name="modelBases">モデル</param>
	/// <returns>有限状態マシン</returns>
	FSMAnimation* FSMAnimationFactory(AnimationBase* animation, ANIMATION_FACTORY_NUMBER number, std::vector<std::vector<LoadAnimationData>> loadAnimationData);

	/// <summary>アニメーションデータ作成</summary>
	/// <param name="type">モデル種類</param>
	/// <returns>アニメーションデータ</returns>
	std::map<ANIMATION_TYPE, AnimationDatas> AnimationDataFactory(MODEL_TYPE type, std::vector<LoadAnimationData> loadAnimationData);
	
	/// <summary>読み込み用アニメーションデータ作成</summary>
	/// <param name="animation">アニメーション</param>
	std::vector<LoadAnimationData> LoadAnimationDataFactory(AnimationBase* animation, LOAD_ANIMATION_DATA_FACTORY_NUMBER nmber);

	/*カメラ有限状態マシン作成*/
	FSMCamera* FSMCameraFactory();

	/*キャラクター有限状態マシン作成*/
	FSMCharacter* FSMCharacterFactory(CharacterBase* character, CHARACTER_FACTORY_NUMBER number, SCENE mapScene = SCENE::NONE);

	/*シーン有限状態マシン作成*/
	FSMScene* FSMSceneFactory(SceneManager* sceneManager);

	/*UI有限状態マシン作成*/
	FSMUI* FSMUIFactory(UIBase* ui, UI_FACTORY_NUMBER number);

	/// <summary>モデル作成</summary>
	/// <param name="type">モデル種類</param>
	/// <param name="modelPath">モデルファイル座標</param>
	/// <returns>モデルベース</returns>
	ModelBase* ModelFactory(MODEL_TYPE type, std::string modelPath = "");
};