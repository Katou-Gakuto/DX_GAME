#include<string>

#include "AnimationData.h"
#include "ResourceData.h"
#include "StateData.h"

#include "DxLib.h"

#include "Master.h"

#include "Animation.h"
#include "ModelBase.h"
#include "ResourceEffect.h"
#include "ResourceManager.h"
#include "StateAnimation.h"
#include "UtilCalc.h"

/*----------------------------*/
/*�y3D�A�j���[�V�������ʏ����z*/
/*----------------------------*/
State3DAnimationProcess::State3DAnimationProcess()
: mnModelHandle(-1)
, mfAnimBlendRate(0.0f)
, mfAnimBlendSpeed(0.1f)
, mfAnimationSpeed(0.5f)
, mstMyAniationData()
{
    mstPreAnimationData.animationCount = 0.0f;
    mstPreAnimationData.animationHandle = -1;
    mstPreAnimationData.loopFlag = false;
}

State3DAnimationProcess::State3DAnimationProcess(int modelHandle)
: mnModelHandle(modelHandle)
, mfAnimBlendRate(0.0f)
, mfAnimBlendSpeed(0.1f)
, mfAnimationSpeed(0.5f)
, mstMyAniationData()
{
    mstPreAnimationData.animationCount = 0.0f;
    mstPreAnimationData.animationHandle = -1;
    mstPreAnimationData.loopFlag = false;
}

void State3DAnimationProcess::AnimationDetach(STATE_ANEMATION_DATA* stateAnimationData)
{
    const int currentAnimationHandle = stateAnimationData->nowAnimationData == nullptr
        ? -1
        : stateAnimationData->nowAnimationData->animationHandle;
    if (currentAnimationHandle != -1)
    {
        MV1DetachAnim(mnModelHandle, currentAnimationHandle);
        stateAnimationData->nowAnimationData->animationHandle = -1;
    }

    if (mstPreAnimationData.animationHandle != -1 &&
        mstPreAnimationData.animationHandle != currentAnimationHandle)
    {
        MV1DetachAnim(mnModelHandle, mstPreAnimationData.animationHandle);
    }
    mstPreAnimationData.animationHandle = -1;
    // ���̃X�e�[�g��O�̃X�e�[�g�Ƃ��Đݒ�
    stateAnimationData->preAnimationData = &mstMyAniationData;
    //animationDatas->animDatas[animation->GetAnimationType()].preAnimationType = meAnimationType;
}

// �A�j���[�V�������A�^�b�`
void State3DAnimationProcess::AnimationAttach(STATE_ANEMATION_DATA* stateAnimationData)
{
    // ���̃X�e�[�g�����݂̃X�e�[�g�Ƃ��Đݒ�
    stateAnimationData->nowAnimationData = &mstMyAniationData;
    stateAnimationData->nowAnimationData->animationHandle = MV1AttachAnim(mnModelHandle, stateAnimationData->nowAnimationData->number);
    stateAnimationData->nowAnimationData->animationCount = 0.0f;
}

// ��O�̃A�j���[�V��������ݒ肷��
void State3DAnimationProcess::PreAnimationDataSetting(STATE_ANEMATION_DATA* stateAnimationData)
{
    if (stateAnimationData->nowAnimationData->preAnimationType != ANIMATION_MOVE_TYPE::NONE)
    {
        mstPreAnimationData.animationHandle = stateAnimationData->nowAnimationData->animationHandle;
        mstPreAnimationData.animationCount = stateAnimationData->nowAnimationData->animationCount;
        mstPreAnimationData.loopFlag = stateAnimationData->nowAnimationData->loopFlag;

        mfAnimBlendRate = ((mstPreAnimationData.animationHandle == -1) ? 1.0f : 0.0f);
    }
}

// �A�j���[�V����������
void State3DAnimationProcess::Init(STATE_ANEMATION_DATA* stateAnimationData)
{
    // �A�^�b�`
    AnimationAttach(stateAnimationData);

    // �O�̃A�j���[�V��������ݒ�
    PreAnimationDataSetting(stateAnimationData);
}

// �A�j���[�V�����X�V
void State3DAnimationProcess::UpdateAnimation(STATE_ANEMATION_DATA* stateAnimationData)
{
    if (mnModelHandle != -1) {

        // �u�����h���X�V
        UpdateBlend();

        // ���݂̃A�j���[�V�������Ԃ�i�߂�
        AdvanceAnimationTime(stateAnimationData->nowAnimationData->animationHandle, &stateAnimationData->nowAnimationData->animationCount, stateAnimationData->nowAnimationData->loopFlag, mfAnimBlendRate);

        // �O�̃A�j���[�V�������Ԃ�i�߂�
        AdvanceAnimationTime(mstPreAnimationData.animationHandle, &mstPreAnimationData.animationCount, mstPreAnimationData.loopFlag, ANIMATION_BLEND_RATE_MAX - mfAnimBlendRate);
    }
}

// �u�����h�X�V
void State3DAnimationProcess::UpdateBlend()
{
    // �u�����h�������Z���Ă���
    if (mfAnimBlendRate < ANIMATION_BLEND_RATE_MAX)
    {
        mfAnimBlendRate += mfAnimBlendSpeed;

        if (mfAnimBlendRate > ANIMATION_BLEND_RATE_MAX)
        {
            mfAnimBlendRate = ANIMATION_BLEND_RATE_MAX;
        }
    }
}

// �A�j���[�V�������Ԃ�i�߂�
void State3DAnimationProcess::AdvanceAnimationTime(int animationHandle, float* animationCount, bool loopFlag, float animBlendRate)
{
    // �A�j���[�V��������
    if (animationHandle != -1)
    {
        // ���Đ����Ԃ��擾
        float animTotalTime = MV1GetAttachAnimTotalTime(mnModelHandle, animationHandle);

        // �Đ����Ԃ�i�߂�
        *animationCount += mfAnimationSpeed;

        // ���[�v������
        if (*animationCount >= animTotalTime)
        {
            if (loopFlag)
            {
                *animationCount = fmodf(*animationCount, animTotalTime);
            }
            else
            {
                if (true/* TODO:�e�X�g�i�K*/)
                {
                    *animationCount = animTotalTime;
                }
                else
                {
                    *animationCount -= mfAnimationSpeed;
                }
            }
        }

        // ���f���ɔ��f
        MV1SetAttachAnimTime(mnModelHandle, animationHandle, *animationCount);

        // �A�j���[�V�������f����ݒ�
        MV1SetAttachAnimBlendRate(mnModelHandle, animationHandle, animBlendRate);
    }
}

/*----------*/
/*�y�A�j���[�V���������z*/
/*----------*/
StateNoneAnimation::StateNoneAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias)
: IStateAnimation(stateChangeCriterias)
{}

// �A�j���[�V�������[�u��ނ����ނȂ�utrue�v��Ԃ�
bool StateNoneAnimation::CheckSimilarAnimationType(ANIMATION_TYPE animationMoveType)
{
    return false;
}

/*------------------------*/
/*�yMV1���f���A�j���[�V�����z*/
/*------------------------*/
StateMVOneAnimation::StateMVOneAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias, int modelHandle, std::string fileName)
: IStateAnimation(stateChangeCriterias)
, State3DAnimationProcess(modelHandle)
{
    // �A�j���[�V�����t���[���Œ�
    {
        // �A�j���[�V�����ňړ������Ă���t���[���̔ԍ�����������
        int moveAnimFrameIndex = MV1SearchFrame(mnModelHandle, fileName.c_str());

        // �A�j���[�V�����ňړ����Ă���t���[���𖳌��ɂ���
        if (moveAnimFrameIndex >= 0)
        {
            MV1SetFrameUserLocalMatrix(mnModelHandle, moveAnimFrameIndex, MV1GetFrameLocalMatrix(mnModelHandle, moveAnimFrameIndex));
        }
    }
}

// ���̏�Ԃɓ��������̏���
void StateMVOneAnimation::OnEnter(STATE_ANEMATION_DATA* stateAnimationData, int preState)
{
    Init(stateAnimationData);
}

// ���̏�Ԃ��o�鎞�̏���
void StateMVOneAnimation::OnExit(STATE_ANEMATION_DATA* stateAnimationData, int nextState)
{
    AnimationDetach(stateAnimationData);
}

// �I��
void StateMVOneAnimation::Finalize(STATE_ANEMATION_DATA* stateAnimationData)
{
}

// �X�V
void StateMVOneAnimation::Update(STATE_ANEMATION_DATA* stateAnimationData)
{
    // �A�j���[�V�����X�V
    UpdateAnimation(stateAnimationData);
}

/*�A�j���[�V�������[�u��ނ����ނȂ�utrue�v��Ԃ�*/
bool StateMVOneAnimation::CheckSimilarAnimationType(ANIMATION_TYPE animationMoveType)
{
    switch (animationMoveType)
    {
    case ANIMATION_TYPE::MV1_MODEL:
        return true;
    }

    return false;
}

/*--------------------------------*/
/*�yMV1���f�� �A�j���[�V�����������f���z*/
/*--------------------------------*/

StateMVOneOnlyAnimation::StateMVOneOnlyAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias, int modelHandle)
: IStateAnimation(stateChangeCriterias)
, State3DAnimationProcess(modelHandle)
{
}

// ���̏�Ԃɓ��������̏���
void StateMVOneOnlyAnimation::OnEnter(STATE_ANEMATION_DATA* stateAnimationData, int preState)
{
    Init(stateAnimationData);
}

// ���̏�Ԃ��o�鎞�̏���
void StateMVOneOnlyAnimation::OnExit(STATE_ANEMATION_DATA* stateAnimationData, int nextState)
{
    AnimationDetach(stateAnimationData);
}

// �I��
void StateMVOneOnlyAnimation::Finalize(STATE_ANEMATION_DATA* stateAnimationData)
{
}

// �X�V
void StateMVOneOnlyAnimation::Update(STATE_ANEMATION_DATA* stateAnimationData)
{
    // �A�j���[�V�����X�V
    UpdateAnimation(stateAnimationData);
}

/*�A�j���[�V�������A�^�b�`*/
void StateMVOneOnlyAnimation::AnimationAttach(STATE_ANEMATION_DATA* stateAnimationData)
{
    stateAnimationData->nowAnimationData = &mstMyAniationData;
    stateAnimationData->nowAnimationData->animationHandle = MV1AttachAnim(mnModelHandle, 0, stateAnimationData->nowAnimationData->number, FALSE);
    stateAnimationData->nowAnimationData->animationCount = 0.0f;
}

/*�A�j���[�V�������[�u��ނ����ނȂ�utrue�v��Ԃ�*/
bool StateMVOneOnlyAnimation::CheckSimilarAnimationType(ANIMATION_TYPE animationMoveType)
{
    switch (animationMoveType)
    {
    case ANIMATION_TYPE::MV1_MODEL_MOVE:
    case ANIMATION_TYPE::MV1_MODEL_ONLY:
        return true;
    }

    return false;
}

/*----------------------*/
/*�yMV1���f�� ���f������z*/
/*----------------------*/
StateMVOneOperationAnimation::StateMVOneOperationAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias, VECTOR changeVec, VECTOR changeAngle, VECTOR changeSize, int modelHandle)
: StateMVOneOnlyAnimation(stateChangeCriterias, modelHandle)
, mvChangeMove(changeVec)
, mvMove(UtilCalc::VZero)
, mvChangeAngle(changeAngle)
, mvAngle(UtilCalc::VZero)
, mvChangeSize(changeSize)
, mvSize(UtilCalc::VZero)
{
}

// ���̏�Ԃɓ��������̏���
void StateMVOneOperationAnimation::OnEnter(STATE_ANEMATION_DATA* stateAnimationData, int preState)
{
    Init(stateAnimationData);

    mvMove  = UtilCalc::VZero;
    mvAngle = UtilCalc::VZero;
    mvSize  = UtilCalc::VZero;
}

// ���̏�Ԃ��o�鎞�̏���
void StateMVOneOperationAnimation::OnExit(STATE_ANEMATION_DATA* stateAnimationData, int nextState)
{
    AnimationDetach(stateAnimationData);

    stateAnimationData->animation->GetModel()->SetPosition( VSub(stateAnimationData->animation->GetModel()->GetPosition(), mvMove));
    stateAnimationData->animation->GetModel()->SetAngle(    VSub(stateAnimationData->animation->GetModel()->GetAngle(),    mvAngle));
    stateAnimationData->animation->GetModel()->SetSize(     VSub(stateAnimationData->animation->GetModel()->GetSize(),     mvSize));
}

// �X�V
void StateMVOneOperationAnimation::Update(STATE_ANEMATION_DATA* stateAnimationData)
{
    mvMove  = VAdd(mvMove,  mvChangeMove);
    mvAngle = VAdd(mvAngle, mvChangeAngle);
    mvSize  = VAdd(mvSize,  mvChangeSize);

    stateAnimationData->animation->GetModel()->SetPosition( VAdd(stateAnimationData->animation->GetModel()->GetPosition(), mvChangeMove));
    stateAnimationData->animation->GetModel()->SetAngle(    VAdd(stateAnimationData->animation->GetModel()->GetAngle(),    mvChangeAngle));
    stateAnimationData->animation->GetModel()->SetSize(     VAdd(stateAnimationData->animation->GetModel()->GetSize(),     mvChangeSize));
}

/*�A�j���[�V�������[�u��ނ����ނȂ�utrue�v��Ԃ�*/
bool StateMVOneOperationAnimation::CheckSimilarAnimationType(ANIMATION_TYPE animationMoveType)
{
    switch (animationMoveType)
    {
    case ANIMATION_TYPE::MV1_MODEL_MOVE:
    case ANIMATION_TYPE::MV1_MODEL_ONLY:
        return true;
    }

    return false;
}

/*--------------------*/
/*�y�G�t�F�N�g�A�j���[�V�����z*/
/*--------------------*/
StateEffectAnimation::StateEffectAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias)
: IStateAnimation(stateChangeCriterias)
, mnEffectHandle()
{
}

// ���̏�Ԃɓ��������̏���
void StateEffectAnimation::OnEnter(STATE_ANEMATION_DATA* stateAnimationData, int preState)
{
    if (!stateAnimationData->animation->GetModel()->GetDrawFlag())
    {
        return;
    }

    mnEffectHandle = Master::mpResourceManager->GetEffectResource()->GetEffectHandle(stateAnimationData->nowAnimationData->number, mnEffectHandle);
}
// ���̏�Ԃ��o�鎞�̏���
void StateEffectAnimation::OnExit(STATE_ANEMATION_DATA* stateAnimationData, int nextState)
{
    if (mnEffectHandle == -1)
    {
        return;
    }

    Master::mpResourceManager->GetEffectResource()->DeletePlayEffectHandle(mnEffectHandle);
    mnEffectHandle = -1;
}
// �I��
void StateEffectAnimation::Finalize(STATE_ANEMATION_DATA* stateAnimationData)
{
    if (mnEffectHandle == -1)
    {
        return;
    }

    Master::mpResourceManager->GetEffectResource()->DeletePlayEffectHandle(mnEffectHandle);
    mnEffectHandle = -1;
}
// �X�V(�������Ȃ�)
void StateEffectAnimation::Update(STATE_ANEMATION_DATA* stateAnimationData)
{
}

/*�A�j���[�V�������[�u��ނ����ނȂ�utrue�v��Ԃ�*/
bool StateEffectAnimation::CheckSimilarAnimationType(ANIMATION_TYPE animationMoveType)
{
    switch (animationMoveType)
    {
    case ANIMATION_TYPE::EFFECT:
        return true;
    }

    return false;
}

/*--------------*/
/*�y�摜�A�j���[�V�����z*/
/*--------------*/
StateGraphAnimation::StateGraphAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias)
: IStateAnimation(stateChangeCriterias)
{
}


// ���̏�Ԃɓ��������̏���
void StateGraphAnimation::OnEnter(STATE_ANEMATION_DATA* stateAnimationData, int preState)
{
}
// ���̏�Ԃ��o�鎞�̏���
void StateGraphAnimation::OnExit(STATE_ANEMATION_DATA* stateAnimationData, int nextState)
{
}
// �I��
void StateGraphAnimation::Finalize(STATE_ANEMATION_DATA* stateAnimationData)
{
}
// �X�V(�������Ȃ�)
void StateGraphAnimation::Update(STATE_ANEMATION_DATA* stateAnimationData)
{
}

bool StateGraphAnimation::CheckSimilarAnimationType(ANIMATION_TYPE animationMoveType)
{
    switch (animationMoveType)
    {
    case ANIMATION_TYPE::GRAPH:
        return true;
    }

    return false;
}

/*--------------*/
/*�y����A�j���[�V�����z*/
/*--------------*/
StateMovieAnimation::StateMovieAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias)
: IStateAnimation(stateChangeCriterias)
{
}

// ���̏�Ԃɓ��������̏���
void StateMovieAnimation::OnEnter(STATE_ANEMATION_DATA* stateAnimationData, int preState)
{
}
// ���̏�Ԃ��o�鎞�̏���
void StateMovieAnimation::OnExit(STATE_ANEMATION_DATA* stateAnimationData, int nextState)
{
}
// �I��
void StateMovieAnimation::Finalize(STATE_ANEMATION_DATA* stateAnimationData)
{
}
// �X�V(�������Ȃ�)
void StateMovieAnimation::Update(STATE_ANEMATION_DATA* stateAnimationData)
{
}

bool StateMovieAnimation::CheckSimilarAnimationType(ANIMATION_TYPE animationMoveType)
{
    switch (animationMoveType)
    {
    case ANIMATION_TYPE::MOVIE:
        return true;
    }

    return false;
}

/*----------------------*/
/*�y�t�F�[�h�摜�A�j���[�V�����z*/
/*----------------------*/
StateFadeGraphAnimation::StateFadeGraphAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias)
: IStateAnimation(stateChangeCriterias)
{
}

// ���̏�Ԃɓ��������̏���
void StateFadeGraphAnimation::OnEnter(STATE_ANEMATION_DATA* stateAnimationData, int preState)
{
    DrawConfigData drawConfigData = stateAnimationData->animation->GetModel()->GetDrawConfigData();

    if (drawConfigData.blendMode != DX_BLENDMODE_ALPHA)
    {
        drawConfigData.blendMode = DX_BLENDMODE_ALPHA;
        if (stateAnimationData->nowAnimationData->blendParameter > 0)
        {
            drawConfigData.blendParameter = 0;
        }
        else
        {
            drawConfigData.blendParameter = 255;
        }
        stateAnimationData->animation->GetModel()->SetDrawConfigData(drawConfigData);
    }
}
// ���̏�Ԃ��o�鎞�̏���
void StateFadeGraphAnimation::OnExit(STATE_ANEMATION_DATA* stateAnimationData, int nextState)
{
}
// �I��
void StateFadeGraphAnimation::Finalize(STATE_ANEMATION_DATA* stateAnimationData)
{
}
// �X�V(�������Ȃ�)
void StateFadeGraphAnimation::Update(STATE_ANEMATION_DATA* stateAnimationData)
{
    FadeProcess(stateAnimationData);
}

/*�t�F�[�h����*/
void StateFadeGraphAnimation::FadeProcess(STATE_ANEMATION_DATA* stateAnimationData)
{
    // �`������擾���ύX����
    DrawConfigData drawConfigData = stateAnimationData->animation->GetModel()->GetDrawConfigData();
    drawConfigData.blendParameter += stateAnimationData->nowAnimationData->blendParameter;


    // �`���񂪔͈͊O�Ȃ�C������
    if (drawConfigData.blendParameter > 255)
    {
        drawConfigData.blendParameter = 255;  
    }
    else if (drawConfigData.blendParameter < 0)
    {
        drawConfigData.blendParameter = 0;    
    }

    // �ύX�����`�����ݒ�
    stateAnimationData->animation->GetModel()->SetDrawConfigData(drawConfigData); 
}

/*�A�j���[�V�������[�u��ނ����ނȂ�utrue�v��Ԃ�*/
bool StateFadeGraphAnimation::CheckSimilarAnimationType(ANIMATION_TYPE animationMoveType)
{
    switch (animationMoveType)
    {
    case ANIMATION_TYPE::FADE:
        return true;
    }

    return false;
}

/*-------------------*/
/*�yDOTween�A�j���[�V�����z*/
/*-------------------*/
StateDOTweenAnimation::StateDOTweenAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias)
: IStateAnimation(stateChangeCriterias)
{
}

// ���̏�Ԃɓ��������̏���
void StateDOTweenAnimation::OnEnter(STATE_ANEMATION_DATA* stateAnimationData, int preState)
{
}
// ���̏�Ԃ��o�鎞�̏���
void StateDOTweenAnimation::OnExit(STATE_ANEMATION_DATA* stateAnimationData, int nextState)
{
}
// �I��
void StateDOTweenAnimation::Finalize(STATE_ANEMATION_DATA* stateAnimationData)
{
}
// �X�V(�������Ȃ�)
void StateDOTweenAnimation::Update(STATE_ANEMATION_DATA* stateAnimationData)
{
}

// �A�j���[�V�������[�u��ނ����ނȂ�utrue�v��Ԃ�
bool StateDOTweenAnimation::CheckSimilarAnimationType(ANIMATION_TYPE animationMoveType)
{
    switch (animationMoveType)
    {
    case ANIMATION_TYPE::DOT_WEEN:
        return true;
    }

    return false;
}

// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// #include <map>
// #include <math.h>
// #include <string>

// #include "AnimationEnum.h"
// #include "AnimationData.h"
// #include "ResourceData.h"

// #include "DxLib.h"

// #include "Master.h"

// #include "Animation.h"
// #include "ModelBase.h"
// #include "ModelsControllerBase.h"
// #include "ResourceEffect.h"
// #include "ResourceManager.h"
// #include "Resource3DModel.h"
// #include "StateAnimation.h"
// #include "StateAnimation.h"
// #include "UtilCalc.h"

// /*----------*/
// /*�y�A�j���[�V�����X�e�[�g���ʏ����z
// /*----------*/

// StateAnimationProcess::StateAnimationProcess(int modelHandle)
// : /*mnModelHandle(modelHandle)
// , */mfAnimBlendRate(0.0f)
// , mfAnimBlendSpeed(0.1f)
// , mfAnimationSpeed(0.5f)
// , meAnimationType(ANIMATION_MOVE_TYPE::IDLE)
// {
//     mstPreAnimationData.animationCount = 0.0f;
//     mstPreAnimationData.animationHandle = -1;
//     mstPreAnimationData.loopFlag = false;
// }

// // �A�j���[�V�������f�^�b�`
// void StateAnimationProcess::AnimationDetach(Animation* animation, AnimationDatas* animationDatas)
// {
//     if (mstPreAnimationData.animationHandle != (-1))
//     {
//         MV1DetachAnim(mnModelHandle, mstPreAnimationData.animationHandle);
//         mstPreAnimationData.animationHandle = -1;
//     }

//     // ���݂̃X�e�[�g�Ǝ��̃X�e�[�g��R�Â��đO�̃X�e�[�g�Ƃ��Ĉ���
//     animationDatas->animDatas[animation->GetAnimationType()].preAnimationType = meAnimationType;
// }

// // �A�j���[�V�������A�^�b�`
// void StateAnimationProcess::AnimationAttach(Animation* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas)
// {
//     nowAnimationData->animationHandle = MV1AttachAnim(mnModelHandle, nowAnimationData->number);
//     nowAnimationData->animationCount = 0.0f;
// }

// // ��O�̃A�j���[�V��������ݒ肷��
// void StateAnimationProcess::PreAnimationDataSetting(Animation* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas)
// {
//     if (nowAnimationData->preAnimationType != ANIMATION_MOVE_TYPE::NONE)
//     {
//         meAnimationType = animation->GetAnimationType();

//         mstPreAnimationData.animationHandle = animationDatas->animDatas[nowAnimationData->preAnimationType].animationHandle;
//         mstPreAnimationData.animationCount = animationDatas->animDatas[nowAnimationData->preAnimationType].animationCount;
//         mstPreAnimationData.loopFlag = animationDatas->animDatas[nowAnimationData->preAnimationType].loopFlag;

//         mfAnimBlendRate = ((mstPreAnimationData.animationHandle == -1) ? 1.0f : 0.0f);
//     }
// }

// // ������
// void StateAnimationProcess::Init(Animation* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas)
// {
//     // �A�^�b�`
//     AnimationAttach(animation, nowAnimationData, animationDatas);

//     // �O�̃A�j���[�V��������ݒ�
//     PreAnimationDataSetting(animation, nowAnimationData, animationDatas);
// }

// // �A�j���[�V�����X�V
// void StateAnimationProcess::UpdateAnimation(OneAnimationData *nowAnimationData)
// {
//     if (mnModelHandle != -1) {

//         // �u�����h���X�V
//         UpdateBlend();

//         // ���݂̃A�j���[�V�������Ԃ�i�߂�
//         AdvanceAnimationTime(nowAnimationData->animationHandle, &nowAnimationData->animationCount, nowAnimationData->loopFlag, mfAnimBlendRate, true);

//         // �O�̃A�j���[�V�������Ԃ�i�߂�
//         AdvanceAnimationTime(mstPreAnimationData.animationHandle, &mstPreAnimationData.animationCount, mstPreAnimationData.loopFlag, ANIMATION_BLEND_RATE_MAX - mfAnimBlendRate, true);
//     }
// }

// void StateAnimationProcess::UpdateBlend()
// {
//     // �u�����h�������Z���Ă���
//     if (mfAnimBlendRate < ANIMATION_BLEND_RATE_MAX)
//     {
//         mfAnimBlendRate += mfAnimBlendSpeed;

//         if (mfAnimBlendRate > ANIMATION_BLEND_RATE_MAX)
//         {
//             mfAnimBlendRate = ANIMATION_BLEND_RATE_MAX;
//         }
//     }
// }

// /*�A�j���[�V�������Ԃ�i�߂�*/
// void StateAnimationProcess::AdvanceAnimationTime(int animationHandle, float* animationCount, bool loopFlag, float animBlendRate, bool testFlag)
// {
//     // �A�j���[�V��������
//     if (animationHandle != -1)
//     {
//         // ���Đ����Ԃ��擾
//         float animTotalTime = MV1GetAttachAnimTotalTime(mnModelHandle, animationHandle);

//         // �Đ����Ԃ�i�߂�
//         *animationCount += mfAnimationSpeed;

//         // ���[�v������
//         if (*animationCount >= animTotalTime)
//         {
//             if (loopFlag)
//             {
//                 *animationCount = fmodf(*animationCount, animTotalTime);
//             }
//             else
//             {
//                 if (testFlag)
//                 {
//                     *animationCount = animTotalTime;
//                 }
//                 else
//                 {
//                     *animationCount -= mfAnimationSpeed;
//                 }
//             }
//         }

//         // ���f���ɔ��f
//         MV1SetAttachAnimTime(mnModelHandle, animationHandle, *animationCount);

//         // �A�j���[�V�������f����ݒ�
//         MV1SetAttachAnimBlendRate(mnModelHandle, animationHandle, animBlendRate);
//     }
// }

// /*----------*/
// /*�yMV1���f���A�j���[�V�����z
// /*----------*/

// StateMVOneAnimation::StateMVOneAnimation(int modelHandle, std::string fileName, std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias)
// : IStateAnimation(ANIMATION_TYPE::MV1_MODEL, stateChangeCriterias)
// , StateAnimationProcess(modelHandle)
// {
//     // �A�j���[�V�����t���[���Œ�
//     {
//         // �A�j���[�V�����ňړ������Ă���t���[���̔ԍ�����������
//         int moveAnimFrameIndex = MV1SearchFrame(mnModelHandle, fileName.c_str());

//         // �A�j���[�V�����ňړ����Ă���t���[���𖳌��ɂ���
//         MV1SetFrameUserLocalMatrix(mnModelHandle, moveAnimFrameIndex, MV1GetFrameLocalMatrix(mnModelHandle, moveAnimFrameIndex));
//     }

//     mStateNumber = ANIMATION_TYPE::MV1_MODEL;
// }

// // ���̏�Ԃɓ��������̏���
// void StateMVOneAnimation::OnEnter(Animation* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, ANIMATION_TYPE oldModelType)
// {
//     Init(animation, nowAnimationData, animationDatas);
// }

// // ���̏�Ԃ��o�鎞�̏���
// void StateMVOneAnimation::OnExit(Animation* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, ANIMATION_TYPE newModelType)
// {
//     AnimationDetach(animation, animationDatas);
// }

// // �I��
// void StateMVOneAnimation::Finalize(Animation* animation, AnimationDatas* animationDatas)
// {
// }

// // �X�V
// void StateMVOneAnimation::Update(Animation* animation, OneAnimationData *nowAnimationData)
// {
//     // �A�j���[�V�����X�V
//     UpdateAnimation(nowAnimationData);
// }

// // ���f����ނ����ނȂ�utrue�v��Ԃ�
// bool StateMVOneAnimation::CheckSimilarModelType(ANIMATION_TYPE modelType)
// {
//     switch (modelType)
//     {
//     case ANIMATION_TYPE::MV1_MODEL:
//         return true;
//     }

//     return false;
// }


// /*----------*/
// /*�yMV1���f���@�A�j���[�V�����������f���z
// /*----------*/
// StateMVOneOnlyAnimation::StateMVOneOnlyAnimation(int modelHandle, std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias)
// : IStateAnimation(ANIMATION_TYPE::MV1_MODEL_ONLY, stateChangeCriterias)
// , StateAnimationProcess(modelHandle)
// {
//     mStateNumber = ANIMATION_TYPE::MV1_MODEL_ONLY;
// }

// // ���̏�Ԃɓ��������̏���
// void StateMVOneOnlyAnimation::OnEnter(Animation* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, ANIMATION_TYPE oldModelType)
// {
//     Init(animation, nowAnimationData, animationDatas);
// }

// // ���̏�Ԃ��o�鎞�̏���
// void StateMVOneOnlyAnimation::OnExit(Animation* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, ANIMATION_TYPE newModelType)
// {
//     AnimationDetach(animation, animationDatas);
// }

// // �I��
// void StateMVOneOnlyAnimation::Finalize(Animation* animation, AnimationDatas* animationDatas)
// {
//     std::vector<ANIMATION_MOVE_TYPE> deleteAnimationType;
//     deleteAnimationType.clear();
//     deleteAnimationType.reserve(animationDatas->animDatas.size());

//     for (auto& animationData : animationDatas->animDatas)
//     {
//         if (animationData.second.number!= (-1))
//         {
//             deleteAnimationType.push_back(animationData.first);
//             Master::mpResourceManager->Get3DModelResource()->ReduceResourceHandle(animationData.second.number);
//         }
//     }

//     if (deleteAnimationType.size() == animationDatas->animDatas.size())
//     {
//         animationDatas->animDatas.clear();
//         return;
//     }

//     for (int i = 0; i < deleteAnimationType.size(); i++)
//     {
//         animationDatas->animDatas.erase(deleteAnimationType[i]);
//     }
// }

// // �X�V
// void StateMVOneOnlyAnimation::Update(Animation* animation, OneAnimationData *nowAnimationData)
// {
//     // �A�j���[�V�����X�V
//     UpdateAnimation(nowAnimationData);
// }

// // ���f����ނ����ނȂ�utrue�v��Ԃ�
// bool StateMVOneOnlyAnimation::CheckSimilarModelType(ANIMATION_TYPE modelType)
// {
//     switch (modelType)
//     {
//     case ANIMATION_TYPE::MV1_MODEL_MOVE:
//     case ANIMATION_TYPE::MV1_MODEL_ONLY:
//         return true;
//     }

//     return false;
// }

// // �A�j���[�V�������A�^�b�`
// void StateMVOneOnlyAnimation::AnimationAttach(Animation* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas)
// {
//     nowAnimationData->animationHandle = MV1AttachAnim(mnModelHandle, 0, nowAnimationData->number, FALSE);
//     nowAnimationData->animationCount = 0.0f;
// }

// /*----------*/
// /*�yMV1���f�� ���f������z
// /*----------*/
// : StateMVOneOperationAnimation::StateMVOneOperationAnimation(int modelHandle, VECTOR changeVec, VECTOR changeAngle, VECTOR changeSize, std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias)
// : StateMVOneOnlyAnimation(modelHandle, stateChangeCriterias)
// , mvChangeMove(changeVec)
// , mvMove(UtilCalc::VZero)
// , mvChangeAngle(changeAngle)
// , mvAngle(UtilCalc::VZero)
// , mvChangeSize(changeSize)
// , mvSize(UtilCalc::VZero)
// {
//     mStateNumber = ANIMATION_TYPE::MV1_MODEL_MOVE;
// }

// // ���̏�Ԃɓ��������̏���
// void StateMVOneOperationAnimation::OnEnter(Animation* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, ANIMATION_TYPE oldModelType)
// {
//     Init(animation, nowAnimationData, animationDatas);

//     mvMove  = UtilCalc::VZero;
//     mvAngle = UtilCalc::VZero;
//     mvSize  = UtilCalc::VZero;
// }

// // ���̏�Ԃ��o�鎞�̏���
// void StateMVOneOperationAnimation::OnExit(Animation* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, ANIMATION_TYPE newModelType)
// {
//     AnimationDetach(animation, animationDatas);

//     mpModelBase->SetPosition( VSub(mpModelBase->GetPosition(), mvMove));
//     mpModelBase->SetAngle(    VSub(mpModelBase->GetAngle(),    mvAngle));
//     mpModelBase->SetSize(     VSub(mpModelBase->GetSize(),     mvSize));
// }

// // �X�V
// void StateMVOneOperationAnimation::Update(Animation* animation, OneAnimationData *nowAnimationData)
// {
//     mvMove  = VAdd(mvMove,  mvChangeMove);
//     mvAngle = VAdd(mvAngle, mvChangeAngle);
//     mvSize  = VAdd(mvSize,  mvChangeSize);

//     mpModelBase->SetPosition( VAdd(mpModelBase->GetPosition(), mvChangeMove));
//     mpModelBase->SetAngle(    VAdd(mpModelBase->GetAngle(),    mvChangeAngle));
//     mpModelBase->SetSize(     VAdd(mpModelBase->GetSize(),     mvChangeSize));
// }

// // ���f����ނ����ނȂ�utrue�v��Ԃ�
// bool StateMVOneOperationAnimation::CheckSimilarModelType(ANIMATION_TYPE modelType)
// {
//     switch (modelType)
//     {
//     case ANIMATION_TYPE::MV1_MODEL_MOVE:
//     case ANIMATION_TYPE::MV1_MODEL_ONLY:
//         return false;
//     }

//     return false;
// }

// /*----------*/
// /*�y�G�t�F�N�g�A�j���[�V�����z
// /*----------*/

// StateEffectAnimation::StateEffectAnimation(int* effectHandle, std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias)
// : IStateAnimation(ANIMATION_TYPE::EFFECT, stateChangeCriterias)
// , mnEffectHandle(effectHandle)
// {
//     mStateNumber = ANIMATION_TYPE::EFFECT;
// }

// // ���̏�Ԃɓ��������̏���
// void StateEffectAnimation::OnEnter(Animation* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, ANIMATION_TYPE oldModelType)
// {
//     if (!mpModelBase->GetDrawFlag())
//     {
//         return;
//     }

//     *mnEffectHandle = Master::mpResourceManager->GetEffectResource()->GetEffectHandle(nowAnimationData->number, *mnEffectHandle);
// }

// // ���̏�Ԃ��o�鎞�̏���
// void StateEffectAnimation::OnExit(Animation* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, ANIMATION_TYPE newModelType)
// {
//     if (*mnEffectHandle == -1)
//     {
//         return;
//     }

//     Master::mpResourceManager->GetEffectResource()->DeletePlayEffectHandle(*mnEffectHandle);
//     *mnEffectHandle = -1;
// }

// // �I��
// void StateEffectAnimation::Finalize(Animation* animation, AnimationDatas* animationDatas)
// {
//     std::vector<ANIMATION_MOVE_TYPE> deleteAnimationType;
//     deleteAnimationType.clear();
//     deleteAnimationType.reserve(animationDatas->animDatas.size());

//     if (mpModelBase->GetHandle() != -1)
//     {
//         Master::mpResourceManager->GetEffectResource()->DeletePlayEffectHandle(mpModelBase->GetHandle());
//     }

//     for (auto& animationData : animationDatas->animDatas)
//     {
//         if (animationData.second.number != (-1))
//         {
//             deleteAnimationType.push_back(animationData.first);
//              Master::mpResourceManager->GetEffectResource()->ReduceResourceHandle(animationData.second.number);
//         }
//     }

//     if (deleteAnimationType.size() == animationDatas->animDatas.size())
//     {
//         animationDatas->animDatas.clear();
//         return;
//     }

//     for (int i = 0; i < deleteAnimationType.size(); i++)
//     {
//         animationDatas->animDatas.erase(deleteAnimationType[i]);
//     }
// }

// // �X�V
// void StateEffectAnimation::Update(Animation* animation, OneAnimationData *nowAnimationData)
// {
// }

// // ���f����ނ����ނȂ�utrue�v��Ԃ�
// bool StateEffectAnimation::CheckSimilarModelType(ANIMATION_TYPE modelType)
// {
//     return false;
// }

// /*----------*/
// /*�y�摜�A�j���[�V�����z
// /*----------*/
// StateGraphAnimation::StateGraphAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias)
// : IStateAnimation(ANIMATION_TYPE::GRAPH, stateChangeCriterias)
// {
//     mStateNumber = ANIMATION_TYPE::GRAPH;
// }

// // ���̏�Ԃɓ��������̏���
// void StateGraphAnimation::OnEnter(Animation* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, ANIMATION_TYPE oldModelType)
// {
// }

// // ���̏�Ԃ��o�鎞�̏���
// void StateGraphAnimation::OnExit(Animation* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, ANIMATION_TYPE newModelType)
// {
// }

// // �I��
// void StateGraphAnimation::Finalize(Animation* animation, AnimationDatas* animationDatas)
// {
// }

// // �X�V
// void StateGraphAnimation::Update(Animation* animation, OneAnimationData *nowAnimationData)
// {
// }

// // ���f����ނ����ނȂ�utrue�v��Ԃ�
// bool StateGraphAnimation::CheckSimilarModelType(ANIMATION_TYPE modelType)
// {
//     return false;
// }

// /*----------*/
// /*�y����A�j���[�V�����z
// /*----------*/
// StateMovieAnimation::StateMovieAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias)
// : IStateAnimation(ANIMATION_TYPE::MOVIE, stateChangeCriterias)
// {
//     mStateNumber = ANIMATION_TYPE::MOVIE;
// }

// // ���̏�Ԃɓ��������̏���
// void StateMovieAnimation::OnEnter(Animation* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, ANIMATION_TYPE oldModelType)
// {
// }

// // ���̏�Ԃ��o�鎞�̏���
// void StateMovieAnimation::OnExit(Animation* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, ANIMATION_TYPE newModelType)
// {
// }

// // �I��
// void StateMovieAnimation::Finalize(Animation* animation, AnimationDatas* animationDatas)
// {
// }

// // �X�V
// void StateMovieAnimation::Update(Animation* animation, OneAnimationData *nowAnimationData)
// {
// }

// // ���f����ނ����ނȂ�utrue�v��Ԃ�
// bool StateMovieAnimation::CheckSimilarModelType(ANIMATION_TYPE modelType)
// {
//     return false;
// }


// /*------------------------------*/
// /*�y�t�F�[�h�摜�A�j���[�V�����z*/
// /*------------------------------*/
// StateFadeGraphAnimation::StateFadeGraphAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias)
// : IStateAnimation(ANIMATION_TYPE::FADE, stateChangeCriterias)
// {
//     mStateNumber = ANIMATION_TYPE::FADE;
// }

// // ���̏�Ԃɓ��������̏���
// void StateFadeGraphAnimation::OnEnter(Animation* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, ANIMATION_TYPE oldModelType)
// {
//     DrawConfigData drawConfigData = mpModelBase->GetDrawConfigData();

//     if (drawConfigData.blendMode != DX_BLENDMODE_ALPHA)
//     {
//         drawConfigData.blendMode = DX_BLENDMODE_ALPHA;
//         if (nowAnimationData->blendParameter > 0)
//         {
//             drawConfigData.blendParameter = 0;
//         }
//         else
//         {
//             drawConfigData.blendParameter = 255;
//         }
//         mpModelBase->SetDrawConfigData(drawConfigData);
//     }
// }

// // ���̏�Ԃ��o�鎞�̏���
// void StateFadeGraphAnimation::OnExit(Animation* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, ANIMATION_TYPE newModelType)
// {
// }

// // �I��
// void StateFadeGraphAnimation::Finalize(Animation* animation, AnimationDatas* animationDatas)
// {
// }

// // �X�V
// void StateFadeGraphAnimation::Update(Animation* animation, OneAnimationData *nowAnimationData)
// {
//     FadeProcess(nowAnimationData);
// }

// // �t�F�[�h����
// void StateFadeGraphAnimation::FadeProcess(OneAnimationData *nowAnimationData)
// {
//     // �`������擾���ύX����
//     DrawConfigData drawConfigData = mpModelBase->GetDrawConfigData();
//     drawConfigData.blendParameter += nowAnimationData->blendParameter;


//     // �`���񂪔͈͊O�Ȃ�C������
//     if (drawConfigData.blendParameter > 255)
//     {
//         drawConfigData.blendParameter = 255;  
//     }
//     else if (drawConfigData.blendParameter < 0)
//     {
//         drawConfigData.blendParameter = 0;    
//     }

//     // �ύX�����`�����ݒ�
//     mpModelBase->SetDrawConfigData(drawConfigData); 
// }

// // ���f����ނ����ނȂ�utrue�v��Ԃ�
// bool StateFadeGraphAnimation::CheckSimilarModelType(ANIMATION_TYPE modelType)
// {
//     return false;
// }

// /*----------*/
// /*�yDOTween�A�j���[�V�����z*/
// /*----------*/
// StateDOTweenAnimation::StateDOTweenAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias)
// : IStateAnimation(ANIMATION_TYPE::TOD_WEEN, stateChangeCriterias)
// {
//     mStateNumber = ANIMATION_TYPE::TOD_WEEN;
// }

// // ���̏�Ԃɓ��������̏���
// void StateDOTweenAnimation::OnEnter(Animation* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, ANIMATION_TYPE oldModelType)
// {
//     // �����ݒ�
// }

// // ���̏�Ԃ��o�鎞�̏���
// void StateDOTweenAnimation::OnExit(Animation* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, ANIMATION_TYPE newModelType)
// {
// }

// // �I��
// void StateDOTweenAnimation::Finalize(Animation* animation, AnimationDatas* animationDatas)
// {
// }

// // �X�V
// void StateDOTweenAnimation::Update(Animation* animation, OneAnimationData *nowAnimationData)
// {
// }

// // ���f����ނ����ނȂ�utrue�v��Ԃ�
// bool StateDOTweenAnimation::CheckSimilarModelType(ANIMATION_TYPE modelType)
// {
//     return false;
// }