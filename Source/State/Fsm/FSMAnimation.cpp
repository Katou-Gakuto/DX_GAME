#include "Animation.h"
#include "FSM.h"
#include "FSMAnimation.h"
#include "StateAnimation.h"

FSMAnimation::FSMAnimation()
: FSMBase()
{
}

// ������
void FSMAnimation::Initilize(STATE_ANEMATION_DATA* stateAnimationData)
{
}

void FSMAnimation::StateInitilize(STATE_ANEMATION_DATA* stateAnimationData)
{
	FSMBase::StateInitilize(stateAnimationData);

	if (mmStateMap.empty())
	{
		Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::ANIMATION_MISSING_FLAG);
		return;
	}

	auto initialState = mmStateMap.find(mNextState);
	if (initialState == mmStateMap.end())
	{
		initialState = mmStateMap.find(static_cast<int>(ANIMATION_MOVE_TYPE::IDLE));
		if (initialState == mmStateMap.end())
		{
			initialState = mmStateMap.begin();
		}
	}

	mNextState = initialState->first;
	SetCurrentState(initialState->first, stateAnimationData);
}

// �I��
void FSMAnimation::Finalize(STATE_ANEMATION_DATA* stateAnimationData)
{
	auto currentState = mmStateMap.find(mCurrentState);
	if (currentState != mmStateMap.end())
	{
		currentState->second->OnExit(stateAnimationData, -1);
		currentState->second->Finalize(stateAnimationData);
	}
}

// �X�V
void FSMAnimation::Update(STATE_ANEMATION_DATA* stateAnimationData)
{
	if (mmStateMap.find(mCurrentState) == mmStateMap.end() ||
		mmStateMap.find(mNextState) == mmStateMap.end())
	{
		Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::ANIMATION_MISSING_FLAG);
		return;
	}

	stateAnimationData->nextState = mNextState;

	CheckChangeState(stateAnimationData);
	
	mmStateMap[mCurrentState]->Update(stateAnimationData);
}


// ���̃A�j���[�V�������[�u�ݒ�
void FSMAnimation::SetNextAnimationMove(ANIMATION_MOVE_TYPE animatioMoveType)
{
	for (auto& state : mmStateMap)
	{
		if (state.first == static_cast<int>(animatioMoveType))
		{
			mNextState = state.first;
			return;
		}
	}

	{
		Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::ANIMATION_MISSING_FLAG);
	}
}

// #include "AnimationData.h"
// #include "StateData.h"

// #include "FSM.h"
// #include "FSMAnimation.h"
// #include "StateAnimation.h"

// /*----------*/
// /*�y�A�j���[�V�����L����ԃ}�V���z
// /*----------*/
// FSMAnimation::FSMAnimation()
// : FSMBase()
// {
// }

// // // ������
// // void FSMAnimation::Initilize(Animation* animation)
// // {
// // 	mCurrentState = 0;

// // 	// �V����State�̊J�n����
// // 	for (int i = 0; i < mmAnimationStates.size(); i++)
// // 	{
// // 		NewStateSetting(i, animation, ANIMATION_TYPE::NONE);
// // 	}
// // }

// // �I��
// void FSMAnimation::Finalize(Animation* animation)
// {
// 	// for (int i = 0; i < mmAnimationStates.size(); i++)
// 	// {
// 	// 	for (auto animationState : mmAnimationStates[i])
// 	// 	{
// 	// 		animationState.second->Finalize(animation, animation->GetAnimationDatas()[i]);
// 	// 		delete animationState.second;
// 	// 	}
// 	// }
// 	// mmAnimationStates.clear();
// }

// // // �T�u��ԃ}�b�v�̃T�C�Y�𑝂₷
// // void FSMAnimation::IncreaseAnimationStateSize(int size)
// // {
// // 	mmAnimationStates.resize(size);
// // }

// // // �A�j���[�V�����X�e�[�g���ݒ�
// // void FSMAnimation::SetAnimationStateDatas(int animationStateIndex, std::map<ANIMATION_TYPE, IStateAnimation*> animationStateMap)
// // {
// // 	mmAnimationStates[animationStateIndex] = animationStateMap;
// // }

// // �X�V
// void FSMAnimation::Update(Animation* animation, std::vector<AnimationDatas*> animationDatas)
// {
// 	// TODO: �A�j���[�V��������������Ƌl�߂Ă���
// 	STATE_ANEMATION_DATA stateAnimationData;
// 	stateAnimationData.StateAnimation = animation;
// 	//stateAnimationData.StateOneAnimationData = ;
// 	//stateAnimationData.StateAnimationDatas = ;

// 	CheckChangeState(&stateAnimationData);


// 	// TODO: �A�j���[�V��������������Ƌl�߂Ă���
// 	// �ύX����
// 	for (int i = 0; i < mmAnimationStates.size(); i++)
// 	{
// 		// ���f���擾
// //		ModelBase* model = animation->GetModelsController()->GetModelList()[i];

// 		// �X�e�[�g�ύX
// 		if (mCurrentState != oldAnimationState)
// 		{
// 			ChangeState(i, animation, oldAnimationState);
// 		}

// 		// �X�V
// 		GetAnimationState(i, animation, mCurrentState)->Update(animation, &animationDatas[i]->animDatas[mCurrentState]);
// 	}
// }

// // �V�����X�e�[�g��ݒ肷��
// void FSMAnimation::NewStateSetting(int animationIndex, Animation* animation, ANIMATION_TYPE oldModelType)
// {
// 	GetAnimationState(animationIndex, animation, mCurrentState)->OnEnter(animation, &animation->GetAnimationDatas()[animationIndex]->animDatas[mCurrentState], animation->GetAnimationDatas()[animationIndex], oldModelType);
// }

// // ���̃X�e�[�g�����݂̃X�e�[�g�ƈႤ�Ȃ�X�e�[�g�ύX����������
// void FSMAnimation::ChangeState(int animationStateIndex, Animation* animation, ANIMATION_MOVE_TYPE oldAnimationType)
// {
// 	AnimationDatas* animationDatas = animation->GetAnimationDatas()[animationStateIndex];

// 	// ���݂�State�I������
// 	GetAnimationState(animationStateIndex, animation, oldAnimationType)->OnExit(animation, &animationDatas->animDatas[oldAnimationType], animationDatas, animationDatas->animDatas[mCurrentState].modelType);

// 	// �V����State�ݒ�
// 	NewStateSetting(animationStateIndex, animation, animationDatas->animDatas[oldAnimationType].modelType);
// }

// // ���݂̃X�e�[�g�擾
// IStateAnimation* FSMAnimation::GetAnimationState(int index, Animation* animation, ANIMATION_MOVE_TYPE animationType)
// {
// 	return mmAnimationStates[index][animation->GetAnimationDatas()[index]->animDatas[animationType].modelType];
// }