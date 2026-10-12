#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "ResourceData.h"

#include "SceneEnum.h"
#include "AnimationData.h"
#include "AttackData.h"
#include "UtilCalc.h"

enum class ANIMATION_TYPE;

class Animation;
class CameraManager;
class CharacterBase;
class FSMAnimation;
class FSMCamera;
class FSMCharacter;
class FSMScene;
class FSMUI;
class ModelBase;
class ModelsControllerBase;
class SceneManager;
class UIBase;

// �A�j���V�����쐬�i���o�[
enum class ANIMATION_FACTORY_NUMBER
{
	// TODO: ���ŃV�[�����ł���Ă���
	TOWN = 0,
	DUNGEON,
	BATTLE,

	SHOT_ATTACK,

	UI
};

// �ǂݍ��ݗp�A�j���[�V�����f�[�^�쐬�i���o�[
enum class LOAD_ANIMATION_DATA_FACTORY_NUMBER
{
	HUMAN = 0,
	ROBOT,

	SHOT_ATTACK,

	ROBOT_SPCEIAL,

	JUMP_ROBOT_ATTACK,

	UI_BASE,
	UI_BASE_MOVIE,
	UI_FADE,
};

// �L�����N�^�[�쐬�i���o�[
enum class CHARACTER_FACTORY_NUMBER
{
	TOWN_PLAYER = 0,
	DUNGEON_PLAYER,
	BATTLE_PLAYER,

	MAP_ENEMY,
	ENEMY,
	BOSS_ENEMY,
};

// UI�쐬�i���o�[
enum class UI_FACTORY_NUMBER
{
	TITLE = 0,
	TOWN,
	DUNGEON,
	BATTLE,
	RESULT,
};

// �L�����N�^�[�U�����쐬�i���o�[�U�����
enum class CHARACTER_ATTACK_DATA_FACTORY__ATTACK_METHOD
{
	SHOT_NORMAL = 0,
	SHOT_SPCEIAL,
	JUMP_ATTACK,
};
// �L�����N�^�[�U�����쐬�i���o�[���f�����
enum class CHARACTER_ATTACK_DATA_FACTORY__ANIMATION_TYPE
{
	HUMAN = 0,
	ROBOT,
};
// �쐬�i���o�[�I�u�W�F�N�g�U�����
enum class ATTACK_DATA_FACTORY__OBJECT_ATTACK_TYPE
{
	SHOT
};

namespace UtilFactorys
{
	/// <summary>モデルのアニメーション有限状態マシンを作成</summary>
	FSMAnimation* FSMAnimationFactory(Animation* animation, ANIMATION_FACTORY_NUMBER animationFactoryNumber, const std::vector<LoadAnimationData>& loadAnimationData);

	/// <summary>読み込み用アニメーションデータを作成</summary>
	std::vector<LoadAnimationData> LoadAnimationDataFactory(LOAD_ANIMATION_DATA_FACTORY_NUMBER number);

	/// <summary>�L�����N�^�U�����쐬</summary>
	CharacterAttackData CharacterAttackDataFactory(CHARACTER_ATTACK_DATA_FACTORY__ATTACK_METHOD factoryNumberAttackMethod, CHARACTER_ATTACK_DATA_FACTORY__ANIMATION_TYPE factoryNumberModelType);

	// TODO: ���
	/// <summary>�S�A�j���[�V�����ƃ��f���ݒ�</summary>
	//void SettingAnimationAndModelFactory(Animation* animation, ModelsControllerBase* modelsController, std::string filePath, objectType, characterType, moveType);

	/*�J�����L����ԃ}�V���쐬*/
	FSMCamera* FSMCameraFactory();

	/*�L�����N�^�[�L����ԃ}�V���쐬*/
	FSMCharacter* FSMCharacterFactory(CharacterBase* character, CHARACTER_FACTORY_NUMBER number, SCENE mapScene = SCENE::NONE);

	/*�V�[���L����ԃ}�V���쐬*/
	FSMScene* FSMSceneFactory(SceneManager* sceneManager);

	/*UI�L����ԃ}�V���쐬*/
	FSMUI* FSMUIFactory(UIBase* ui, UI_FACTORY_NUMBER number);

	/// <summary>���f���쐬</summary>
	/// <param name="type">���f�����</param>
	/// <param name="modelPath">���f���t�@�C�����W</param>
	/// <returns>���f���x�[�X</returns>
	ModelBase* ModelFactory(ANIMATION_TYPE type, std::string modelPath, VECTOR position = UtilCalc::VZero, VECTOR angle = UtilCalc::VZero, VECTOR size = UtilCalc::VOne, std::vector<DRAW_GRAPH_DATA>* drawData = nullptr);

	/// <summary>�U���f�[�^�쐬</summary>
	std::map<ATTACK_METHOD_TYPE, AttackData> AttackDataFactory(CHARACTER_ATTACK_DATA_FACTORY__ANIMATION_TYPE modelTypeFactoryNumber, ATTACK_DATA_FACTORY__OBJECT_ATTACK_TYPE objectAttackTypeFactoryNumber);

	/// <summary>���f���ʒu�ݒ�</summary>
	void SetModelPosition(ModelBase* model, VECTOR position, VECTOR angle, VECTOR size);
}