#pragma once

#include "StateEnum.h"
#include "TimeData.h"

#include "EnemyCommonProcessing.h"
#include "ObjectBases.h"
#include "StateCharacterBase.h"

class TargetManager;

// TODO: �ړ�����V�[���𐶐����擾

/*------------------*/
/*     �y���ʁz     */
/*------------------*/

/*--------------------*/
/*�y�G�l�~�[�X�e�[�g�z*/
/*--------------------*/

// enum class ENEMY_STATE
// {
// 	IDLE_ENEMY_STATE = 0,
// 	MOVE_ENEMY_STATE,
// 	ATTACK_IN_ENEMY_STATE,
// 	ATTACK_ENEMY_STATE,
// 	RIGHT_AVOID_ENEMY_STATE,
// 	LEFT_AVOID_ENEMY_STATE,
// 	ESCAPE_ENEMY_STATE,
// };

/*----------*/
/*�y�G�l�~�[�R�}���h�i���o�[�z
/*----------*/
enum class ENEMY_COMMAND_NUMBER
{
	NONE = -1,
	SHORT_RANGE = 0,
	MEDIUM_RANGE,
	LONG_RANGE,
};

// ��������
const int ESCAPE_TIME = 17 * 100;

/*----------------------*/
/*�y�G�l�~�[���ʏ����p�z*/
/*----------------------*/
class EnemyProcess : public EnemyCommonProcessing
{

protected:
	// �^�[�Q�b�g�}�l�[�W���[
	TargetManager* mpTargetManager;

protected:
	EnemyProcess();
	~EnemyProcess() = default;

	/*�v���C���[�̃X�e�[�^�X�ݒ�*/
	void SetPlayerStatus();

	/*���͈͓��Ƀv���C���[�^�[�Q�b�g������Ȃ�utrue�v*/
	bool PlayerTargetCheck(CharacterBase* character, float range);

	/*�v���C���[�����������Ĉړ�����*/
	void PlayerTargetMove(CharacterBase* character);

	/*�v���C���[�^�[�Q�b�g�̕����Ɍ���*/
	void PlayerTargetAngle(CharacterBase* character);

	/*���S����*/
	virtual void EnemyDeath(CharacterBase* character);

	/*�v���C���[�̈ʒu�ɂ���ăR�}���h��Ԃ�*/
	virtual ENEMY_COMMAND_NUMBER GetPlayerDistance_Command(CharacterBase* character);

	/*��^�̎��̃X�e�[�g���擾����*/
	STATE_TYPE_CHARACTER TemplateNextState(CharacterBase* character, STATE_TYPE_CHARACTER myState);
};

/*--------------------------*/
/*     �y��{�X�e�[�g�z     */
/*--------------------------*/

/*----------------------*/
/*�yIdle�G�l�~�[�e�[�g�z*/
/*----------------------*/
class IdleEnemyState : public IStateCharacter, public EnemyProcess
{
public:
	// FIXME: �Ăяo�����őJ�ڏ�����n���܂�
	IdleEnemyState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias = {});
	~IdleEnemyState() = default;

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

/*----------*/
/*�y�ړ��G�l�~�[�X�e�[�g�z
/*----------*/
class MoveEnemyState : public IStateCharacter, public EnemyProcess
{
public:
	// FIXME: �Ăяo�����őJ�ڏ�����n���܂�
	MoveEnemyState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias = {});
	~MoveEnemyState() = default;

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

/*----------*/
/*�y�U������G�l�~�[�X�e�[�g�z
/*----------*/
class AttackInEnemyState : public IStateCharacter, public EnemyProcess
{
private:
	// ������t���O
	bool mbLeftMoveFlag;

	// �O��U������
	TIME_DATA mstPreAttackTime;

public:
	// FIXME: �Ăяo�����őJ�ڏ�����n���܂�
	AttackInEnemyState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias = {});
	~AttackInEnemyState() = default;

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

/*----------*/
/*�y�U���G�l�~�[�X�e�[�g�z
/*----------*/
class AttackEnemyState : public IStateCharacter, public EnemyProcess
{
public:
	// FIXME: �Ăяo�����őJ�ڏ�����n���܂�
	AttackEnemyState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias = {});
	~AttackEnemyState() = default;

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

/*------------------------*/
/*�y�����G�l�~�[�X�e�[�g�z*/
/*------------------------*/
class EscapeEnemyState : public IStateCharacter, public EnemyProcess
{
protected:
	// ��������
	TIME_DATA mstEscapeTime;

public:
	// FIXME: �Ăяo�����őJ�ڏ�����n���܂�
	EscapeEnemyState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias = {});
	~EscapeEnemyState() = default;

	void Finalize(CharacterBase* character) override { EnemyCommonProcessingData_Delete();}

	/*���̏�Ԃɓ��������̏���*/
	virtual void OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState) override;
	/*���̏�Ԃ��o�鎞�̏���*/
	void OnExit(CharacterBase* character, STATE_TYPE_CHARACTER nextState) override;
	STATE_TYPE_CHARACTER StateCheck(CharacterBase* character) override;

	/*�X�V*/
	virtual void Update(CharacterBase* character) override;

	/*�ŏI�X�V*/
	void LastUpdate(CharacterBase* character) override;

	/*�`��*/
	void Draw(CharacterBase* character) override;
	void Death(CharacterBase* character) override;
};

/*--------------------------*/
/*     �y�h���X�e�[�g�z     */
/*--------------------------*/

/*--------------------------*/
/*�y������G�l�~�[�X�e�[�g�z*/
/*--------------------------*/
class LeftAvoidEnemyState : public EscapeEnemyState
{
public:
	// FIXME: �Ăяo�����őJ�ڏ�����n���܂�
	LeftAvoidEnemyState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias = {});
	~LeftAvoidEnemyState() = default;

	/*���̏�Ԃɓ��������̏���*/
	virtual void OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState) override;

	/*�X�V*/
	virtual void Update(CharacterBase* character) override;
};

/*--------------------------*/
/*�y�E����G�l�~�[�X�e�[�g�z*/
/*--------------------------*/
class RightAvoidEnemyState : public EscapeEnemyState
{
public:
	// FIXME: �Ăяo�����őJ�ڏ�����n���܂�
	RightAvoidEnemyState(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias = {});
	~RightAvoidEnemyState() = default;

	/*���̏�Ԃɓ��������̏���*/
	virtual void OnEnter(CharacterBase* character, STATE_TYPE_CHARACTER preState) override;

	/*�X�V*/
	virtual void Update(CharacterBase* character) override;
};

/*
�ǉ��\��X�e�[�g
�Ō�ɑҋ@���Ă����ꏊ�ɖ߂�
�����������ߎ��������
�v���C���[�̉����߂����畷�������̂Ōx������
�v���C���[���������̂Œǂ�������
�v���C���[����Q���Ō����Ȃ��Ȃ���������܂Ō������ʒu�܂ňړ�
��HP�Ȃ̂Ō�����ʒu�ɂ��閡�����狗�����Ƃ�����v���C���[�̎��F�ɂ�����炸�����̂ق��Ɉړ�����
�����Ƀv���C���[�̈ʒu��������ꂽ�̂ł��Ă���
�����Ƀv���C���[�̈ʒu��������ꂽ�̂ŏo�������Ȃ���肷��
�������U���Ȃ��ߐi�s�����������Ȃ��疡���̌��(�ߐڍU����)�ɂ�
�ҋ@�ꏊ�����������̂Ō��ݒn��ҋ@�ꏊ�ɂ���
���R�ɍs������
*/
