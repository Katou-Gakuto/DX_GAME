#pragma once
#include <vector>

#include "AnimationEnum.h"
#include "StateData.h"

#include "StateBase.h"

class IStateAnimation : public StateBase<int, STATE_ANEMATION_DATA>
{
protected:
	// �A�j���[�V�������

public:
	IStateAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias)
	: StateBase(stateChangeCriterias, -1)
	{
	}
	virtual ~IStateAnimation() = default;

	/// <summary>������</summary>
	virtual void Initilize(STATE_ANEMATION_DATA* stateAnimationData){}
	/// <summary>�I��</summary>
	virtual void Finalize(STATE_ANEMATION_DATA* stateAnimationData) = 0;

	/// <summary>���̃X�e�[�g���擾����</summary>
	int GetNextState(STATE_ANEMATION_DATA* stateAnimationData) override
	{
		for (auto& stateChangeCriteriaData : mfpStateChangeCriterias)
		{
#ifdef _DEBUG
			if (stateChangeCriteriaData.ChangeFlag == nullptr)
			{
				Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::STATE_NULL_FUNCTION_FLAG);
				DEBUG::SaveText("�X�e�[�g���ݒ�", DEBUG::DEBUG_MAP_TYPE::DEBUG_FAILURE_LOG);
				return mStateNumber;
			}
#endif
			if (stateChangeCriteriaData.ChangeFlag(stateAnimationData))
			{
				return stateChangeCriteriaData.ChangeNumber;
			}
		}

		return stateAnimationData->nextState;
	}

	/// <summary>�X�V</summary>
	virtual void Update(STATE_ANEMATION_DATA* stateAnimationData) = 0;

	/// <summary>�A�j���[�V������ނ����ނȂ�utrue�v��Ԃ�</summary>
	/// <param name="animationMoveType">�A�j���[�V�������</param>
	/// <returns>���ނ�</returns>
	virtual bool CheckSimilarAnimationType(ANIMATION_TYPE animationMoveType) = 0;
};

// #pragma once
// #include <vector>

// #include "StateData.h"
// #include "AnimationData.h"

// #include "StateBase.h"

// enum class MODEL_TYPE;
// enum class CAMERA_MODE;
// enum class DOT_WEEN_TYPE;
// enum class SCENE;

// class Animation;

// /*----------*/
// /*�y�A�j���[�V�����X�e�[�g�x�[�X�z
// /*----------*/
// class IStateAnimation : public StateBase<int, STATE_ANEMATION_DATA>
// {
// protected:
// 	// �A�j���[�V�����X�e�[�g�ݒ���i���o�[
// 	int mnAnimationStateSettingInfoNumber;
// // 	// ���f���x�[�X
// // 	ModelBase* mpModelBase;


// public:
// 	IStateAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias, int stateNumber)
// 	: StateBase(stateChangeCriterias, stateNumber)
// 	{
// 	}
// 	~IStateAnimation() = default;

// 	/// <summary>���̃X�e�[�g���擾����</summary>
// 	int GetNextState(STATE_ANEMATION_DATA* stateAnimationData) override
// 	{
// 		for (auto& stateChangeCriteriaData : mfpStateChangeCriterias)
// 		{
// #ifdef _DEBUG
// 			if (stateChangeCriteriaData.ChangeFlag == nullptr)
// 			{
// 				Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::STATE_NULL_FUNCTION_FLAG);
// 				DEBUG::SaveText("�X�e�[�g���ݒ�", DEBUG::DEBUG_MAP_TYPE::DEBUG_FAILURE_LOG);
// 				return mStateNumber;
// 			}
// #endif
// 			if (stateChangeCriteriaData.ChangeFlag(stateAnimationData))
// 			{
// 				return stateChangeCriteriaData.ChangeNumber;
// 			}
// 		}

// 		return stateAnimationData->nextState;
// 	}

// 	// /// <summary>���̏�Ԃɓ��������̏���</summary>
// 	// virtual void OnEnter(Animation* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, MODEL_TYPE oldModelType) = 0;
// 	// /// <summary>���̏�Ԃ��o�鎞�̏���</summary>
// 	// virtual void OnExit(Animation* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, MODEL_TYPE newModelType) = 0;
	
// 	/// <summary>������</summary>
// 	virtual void Initilize(STATE_ANEMATION_DATA* stateAnimationData){}
// 	/// <summary>�I��</summary>
// 	virtual void Finalize(STATE_ANEMATION_DATA* stateAnimationData) = 0;

// 	/// <summary>�X�V</summary>
// 	virtual void Update(STATE_ANEMATION_DATA* stateAnimationData) = 0;

// 	/// <summary>�A�j���[�V�������[�u��ނ����ނȂ�utrue�v��Ԃ�</summary>
// 	/// <param name="animationMoveType">�A�j���[�V�������[�u���</param>
// 	/// <returns>���ނ�</returns>
// 	virtual bool CheckSimilarAnimationMoveType(ANIMATION_MOVE_TYPE animationMoveType) = 0;

// 	// /// <summary>�A�j���[�V�����X�e�[�g�ݒ���i���o�[�擾</summary>
// 	// int GetAnimationStateSettingInfoNumber() { return mnAnimationStateSettingInfoNumber; }
// 	// /// <summary>�A�j���[�V�����X�e�[�g�ݒ���i���o�[�ݒ�</summary>
// 	// void SetAnimationStateSettingInfoNumber(int infoNumber) { mnAnimationStateSettingInfoNumber = infoNumber; }

// 	// /// <summary>���f���ݒ�</summary>
// 	// /// <param name="modelBase">���f��</param>
// 	// void SetModelBase(ModelBase* modelBase);
// };