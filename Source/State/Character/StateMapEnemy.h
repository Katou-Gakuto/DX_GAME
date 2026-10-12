#pragma once

#include "StateEnum.h"

#include "EnemyCommonProcessing.h"
#include "ObjectBases.h"
#include "StateCharacterBase.h"

class KeyState;
class SceneManager;
class TargetManager;

// TODO: UI�ł��

/*------------------*/
/*     �y���ʁz     */
/*------------------*/

/*--------------------------*/
/*�y�}�b�v�G�l�~�[�X�e�[�g�z*/
/*--------------------------*/

// enum class MAP_ENEMY_STATE
// {
// 	IDLE_MAP_ENEMY_STATE = 0,
// 	TELOP_MAP_ENEMY_STATE,
// };

/*----------------------------*/
/*�y�}�b�v�G�l�~�[���ʏ����p�z*/
/*----------------------------*/
class MapEnemyProcess : public EnemyCommonProcessing
{
protected:
	// �L�[�X�e�[�g
	KeyState* mpKeyState;

	// �V�[���}�l�[�W���[
	SceneManager* mpSceneManager;

	// �^�[�Q�b�g�}�l�[�W���[
	TargetManager* mpTargetManager;

	// �}�b�v�V�[��
	SCENE meMapScene;

protected:
	MapEnemyProcess(SCENE mapScene);
	~MapEnemyProcess() = default;

	/*���͈͓��Ƀv���C���[�^�[�Q�b�g������Ȃ�utrue�v*/
	bool PlayerTargetCheck(CharacterBase* character, float range);

	/*���S*/
	void MapEnemyDeath(CharacterBase* character);

	/*�}�b�v�V�[���Ɉړ��J�n����*/
	void SetMapScene(CharacterBase* character);
};

/*--------------------------*/
/*     �y��{�X�e�[�g�z     */
/*--------------------------*/

/*----------------------------*/
/*�yIdle�}�b�v�G�l�~�[�e�[�g�z*/
/*----------------------------*/
class IdleMapEnemyState : public IStateCharacter, public MapEnemyProcess
{
public:
	// FIXME: �Ăяo�����őJ�ڏ�����n���ꍇ�� stateChangeCriterias ��n��
	IdleMapEnemyState(SCENE mapScene, std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias = {});
	~IdleMapEnemyState() = default;

	void Finalize(CharacterBase* character) override { EnemyCommonProcessingData_Delete();}

	/*���̏�Ԃɓ��������̏���*/
	void OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState) override;
	/*���̏�Ԃ��o�鎞�̏���*/
	void OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState) override;
	STATE_TYPE_CHARACTER StateCheck(CharacterBase* character) override;

	/*�X�V*/
	void Update(CharacterBase* character) override;

	/*�ŏI�X�V*/
	void LastUpdate(CharacterBase* character) override;

	/*�`��*/
	void Draw(CharacterBase* character) override;
	void Death(CharacterBase* character) override;
};

/*--------------------------------*/
/*�y�e���b�v�}�b�v�G�l�~�[�e�[�g�z*/
/*--------------------------------*/
class TelopMapEnemyState : public IStateCharacter, public MapEnemyProcess
{
public:
	// FIXME: �Ăяo�����őJ�ڏ�����n���ꍇ�� stateChangeCriterias ��n��
	TelopMapEnemyState(SCENE mapScene, std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias = {});
	~TelopMapEnemyState() = default;

	void Finalize(CharacterBase* character) override { EnemyCommonProcessingData_Delete();}

	/*���̏�Ԃɓ��������̏���*/
	void OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState) override;
	/*���̏�Ԃ��o�鎞�̏���*/
	void OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState) override;
	STATE_TYPE_CHARACTER StateCheck(CharacterBase* character) override;

	/*�X�V*/
	void Update(CharacterBase* character) override;

	/*�ŏI�X�V*/
	void LastUpdate(CharacterBase* character) override;

	/*�`��*/
	void Draw(CharacterBase* character) override;
	void Death(CharacterBase* character) override;
};
