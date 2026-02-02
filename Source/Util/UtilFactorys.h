#pragma once
#include <iostream>
#include <map>
#include <string>

#include "ResourceData.h"

#include "SceneEnum.h"
#include "AnimationData.h"
#include "AttackData.h"
#include "UtilCalc.h"

enum class MODEL_TYPE;

class CameraManager;
class CharacterBase;
class FSMCamera;
class FSMCharacter;
class FSMScene;
class FSMUI;
class ModelBase;
class ModelsControllerBase;
class SceneManager;
class UIBase;

// アニメション作成ナンバー
enum class ANIMATION_FACTORY_NUMBER
{
	// TODO: 仮でシーン名でやっている
	TOWN = 0,
	DUNGEON,
	BATTLE,

	SHOT_ATTACK,

	UI
};

// 読み込み用アニメーションデータ作成ナンバー
enum class LOAD_ANIMATION_DATA_FACTORY_NUMBER
{
	HUMAN = 0,
	ROBOT,

	SHOT_ATTACK,

	ROBOT_SPCEIAL,

	UI_TITLE,
	UI_GAME,
	UI_RESULT,
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
	TOWN,
	DUNGEON,
	BATTLE,
	RESULT,
};

// キャラクター攻撃情報作成ナンバー攻撃種類
enum class CHARACTER_ATTACK_DATA_FACTORY__ATTACK_METHOD
{
	SHOT_NORMAL = 0,
	SHOT_SPCEIAL,
};
// キャラクター攻撃情報作成ナンバーモデル種類
enum class CHARACTER_ATTACK_DATA_FACTORY__MODEL_TYPE
{
	HUMAN = 0,
	ROBOT,
};
// 作成ナンバーオブジェクト攻撃種類
enum class ATTACK_DATA_FACTORY__OBJECT_ATTACK_TYPE
{
	SHOT
};

namespace UtilFactorys
{
	// TODO: 改善する
	// HACK: 変数名変更する
	/// <summary>アニメーション有限状態マシン作成</summary>
	/// <param name="animationData">アニメーション情報</param>
	/// <param name="modelBases">モデル</param>
	/// <returns>有限状態マシン</returns>
	FSMAnimation* FSMAnimationFactory(AnimationBase* animation, ANIMATION_FACTORY_NUMBER animationFactoryNumber, LOAD_ANIMATION_DATA_FACTORY_NUMBER ladoAnimationDataFactorynumber, std::vector<std::vector<LoadAnimationData>> loadAnimationData);

	/// <summary>アニメーションデータ作成</summary>
	/// <param name="type">モデル種類</param>
	/// <returns>アニメーションデータ</returns>
	AnimationDatas* AnimationDataFactory(std::vector<LoadAnimationData> loadAnimationData);
	
	/// <summary>読み込み用アニメーションデータ作成</summary>
	/// <param name="animation">アニメーション</param>
	std::vector<LoadAnimationData> LoadAnimationDataFactory(AnimationBase* animation, LOAD_ANIMATION_DATA_FACTORY_NUMBER nmber);

	/// <summary>キャラクタ攻撃情報作成</summary>
	CharacterAttackData CharacterAttackDataFactory(CHARACTER_ATTACK_DATA_FACTORY__ATTACK_METHOD factoryNumberAttackMethod, CHARACTER_ATTACK_DATA_FACTORY__MODEL_TYPE factoryNumberModelType);

	// TODO: 作る
	/// <summary>全アニメーションとモデル設定</summary>
	//void SettingAnimationAndModelFactory(AnimationBase* animation, ModelsControllerBase* modelsController, std::string filePath, objectType, characterType, moveType);

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
	ModelBase* ModelFactory(MODEL_TYPE type, std::string modelPath, VECTOR position = UtilCalc::VZero, VECTOR angle = UtilCalc::VZero, VECTOR size = UtilCalc::VOne, std::vector<DRAW_GRAPH_DATA>* drawData = nullptr);

	/// <summary>攻撃データ作成</summary>
	std::map<ATTACK_METHOD_TYPE, AttackData> AttackDataFactory(CHARACTER_ATTACK_DATA_FACTORY__MODEL_TYPE modelTypeFactoryNumber, ATTACK_DATA_FACTORY__OBJECT_ATTACK_TYPE objectAttackTypeFactoryNumber);

	/// <summary>モデル位置設定</summary>
	void SetModelPosition(ModelBase* model, VECTOR position, VECTOR angle, VECTOR size);
};