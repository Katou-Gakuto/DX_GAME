#pragma once
#include <cassert>

#include "Animation.h"
#include "FSM.h"
#include "StateAnimationBase.h"

class FSMAnimation : public FSMBase<IStateAnimation, int, STATE_ANEMATION_DATA>
{
public:
	using FSMBase<IStateAnimation, int, STATE_ANEMATION_DATA>::RegisterState;

	FSMAnimation();

    // �����ݒ�����肷�邽�߂ɌĂяo���Ȃ��悤�ɂ���
    void RegisterState(IStateAnimation* state) override
	{
		// �g�p������G���[���o������悤�ɂ���
		assert(false && " : ���̊֐��̓A�j���[�V�����X�e�[�g�Ŏg����");
	}

	/// <summary>������</summary>
    void Initilize(STATE_ANEMATION_DATA* stateAnimationData);
	void StateInitilize(STATE_ANEMATION_DATA* stateAnimationData) override;
	/// <summary>�I��</summary>
	void Finalize(STATE_ANEMATION_DATA* stateAnimationData);
	
	/// <summary>�X�V</summary>
	void Update(STATE_ANEMATION_DATA* stateAnimationData);

	/// <summary>���̃A�j���[�V�������[�u�ݒ�</summary>
	void SetNextAnimationMove(ANIMATION_MOVE_TYPE animatioMoveType);

	/// <summary>���݂̃X�e�[�g�Ɠ�����ނ����m�F����</summary>
	bool CheckNowStateSameType(ANIMATION_TYPE animationType) { return mmStateMap[mCurrentState]->CheckSimilarAnimationType(animationType); }
};
// #include <cassert>

// #include "AnimationData.h"
// #include "StateData.h"

// #include "FSM.h"
// #include "StateAnimation.h"

// // TODO: 1�̃��f���ɑ΂��ĕ����̃A�j���[�V�������ォ��K�p�ł���悤�ɂ���
// /*----------*/
// /*�y�A�j���[�V�����L����ԃ}�V���z
// /*----------*/
// class FSMAnimation : public FSMBase<IStateAnimation, int, STATE_ANEMATION_DATA>
// {
// private:
// 	// // �A�j���[�V�����X�e�[�g�B
// 	// std::vector<std::map<MODEL_TYPE, IStateAnimation*>> mmAnimationStates;
// public:
// 	FSMAnimation();

//     // �����ݒ�����肷�邽�߂ɌĂяo���Ȃ��悤�ɂ���
//     void RegisterState(IStateAnimation* state) override
// 	{
// 		assert(false && " : �Ăяo����");
// 		// HACK: ����ŃG���[���o�Ȃ���΂��̒��Ŏg�p������G���[���o������悤�ɂ���
// 	}

//     /// <summary>������</summary>
//     void Initilize(Animation* animation);
// 	/// <summary>�I��</summary>
// 	void Finalize(Animation* animation);

// 	// /*�A�j���[�V������ԒB�̃T�C�Y�𑝂₷*/
// 	// void IncreaseAnimationStateSize(int size);

// 	// /// <summary>�A�j���[�V�����X�e�[�g���ݒ�</summary>
// 	// void SetAnimationStateDatas(int animationStateIndex, std::map<MODEL_TYPE, IStateAnimation*> animationStateMap);

// 	/// <summary>�X�V</summary>
// 	void Update(Animation* animation, std::vector<AnimationDatas*> animationDatas);

// 	/// <summary>���̃X�e�[�g�ݒ�</summary>
// 	// TODO: �\���̂ŃA�j���[�V������ݒ�o����悤�ɕύX����
// 	//inline void SetNextState(ANIMATION_TYPE animationType) { mnNextState = animationType; }

// 	/// <summary>���݂̃X�e�[�g�Ɠ�����ނ����m�F����</summary>
// 	//bool CheckNowStateSameType(ANIMATION_TYPE animationType) { return mmStateMap[mCurrentState]->CheckSameType(animationType); }
	
// // private:
// // 	/*�V�����X�e�[�g��ݒ肷��*/
// // 	void NewStateSetting(int animationIndex, Animation* animation, MODEL_TYPE oldModelType);

// // 	/*���̃X�e�[�g�����݂̃X�e�[�g�ƈႤ�Ȃ�X�e�[�g�ύX����������*/
// // 	void ChangeState(int animationStateIndex, Animation* animation, ANIMATION_TYPE oldAnimationType);

// // 	/*���݂̃X�e�[�g�擾*/
// // 	IStateAnimation* GetAnimationState(int index, Animation* animation, ANIMATION_TYPE animationType);
// };