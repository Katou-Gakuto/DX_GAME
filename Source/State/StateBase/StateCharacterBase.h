#pragma once
#include <vector>

#include "StateEnum.h"

#include "StateBase.h"

class CharacterBase;

/*------------------------------*/
/*�y�L�����N�^�[�X�e�[�g�x�[�X�z*/
/*------------------------------*/
class IStateCharacter : public StateBase<STATE_TYPE_CHARACTER, CharacterBase>
{
protected:
	STATE_TYPE_CHARACTER meMyStateType;
	// // ���ʃL�����N�^�[�X�e�[�g
	// enum COMMON_CHARACTER_STATE
	// {
	// 	IDEL_COMMON_CHARACTER_STATE = 0,	// �ʏ�
	// 	MOVE_COMMON_CHARACTER_STATE,	// �ړ�
	// 	FLINCH_COMMON_CHARACTER_STATE,	// ����
	// 	AVOID_COMMON_CHARACTER_STATE,	// ���
	// 	GUARD_COMMON_CHARACTER_STATE,	// �K�[�h
	// 	FALL_DOWN_COMMON_CHARACTER_STATE,	// �|���

	// 	ATTACK_COMMON_CHARACTER_STATE,	// �U��
	// 	NORMAL_ATTACK_COMMON_CHARACTER_STATE,	// �ʏ�U��
	// 	SPCEIAL_ONE_ATTACK_COMMON_CHARACTER_STATE,	// ����U�� 1
	// 	SPCEIAL_TWO_ATTACK_COMMON_CHARACTER_STATE,	// ����U�� 1

	// 	COMMON_CHARACTER_STATE_MAX	// ���ʃL�����N�^�[�X�e�[�g�ő吔
	// };
	// // INPROGRESS: �X�e�[�g�������j�߂�����ύX

public:
	IStateCharacter(std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, CharacterBase>> stateChangeCriterias, STATE_TYPE_CHARACTER stateNumber, STATE_TYPE_CHARACTER stateType)
	: StateBase(stateChangeCriterias, stateNumber)
	, meMyStateType(stateType)
	{
	}
	virtual ~IStateCharacter() = default;

	/// <summary>������</summary>
	virtual void Initilize(CharacterBase* character) {}
	/// <summary>�I��</summary>
	virtual void Finalize(CharacterBase* character) {}

	
	/*�X�V*/
	virtual void Update(CharacterBase* character) = 0;
	/*�ŏI�X�V*/
	virtual void LastUpdate(CharacterBase* character) = 0;

	/*�`��*/
	virtual void Draw(CharacterBase* character) = 0;

	virtual STATE_TYPE_CHARACTER StateCheck(CharacterBase* character) { return meMyStateType; }

	STATE_TYPE_CHARACTER GetNextState(CharacterBase* character) override
	{
		return StateCheck(character);
	}

	virtual void Death(CharacterBase* character) {}

	/// <summary>�X�e�[�g�i���o�[���炵�Ă��g����Œ�X�e�[�g��ގ擾</summary>
	/// <returns>�Œ�X�e�[�g���</returns>
	STATE_TYPE_CHARACTER GetMyStateType() { return meMyStateType; }
};