#pragma once
#include<string> 

#include "AnimationData.h"
#include "StateData.h"
#include "StateAnimation.h"
#include "StateAnimationBase.h"
#include "UtilCalc.h"

/*----------------------------*/
/*�y3D�A�j���[�V�������ʏ����z*/
/*----------------------------*/
class State3DAnimationProcess
{
protected:
    // ��O�̃A�j���[�V�������
    struct MVOneAnimationData
    {
        float animationCount;   // �A�j���[�V�����J�E���g
        int animationHandle;    // �A�j���[�V�����n���h��
        bool loopFlag;          // ���[�v�t���O
    };

protected:

    // ���f���n���h��
    int mnModelHandle;
    
    // ��O�̃A�j���[�V�������
    MVOneAnimationData mstPreAnimationData;

    // �̃X�e�[�g�̃A�j���[�V�����f�[�^
    OneAnimationData mstMyAniationData;

    // �u�����h��
    float mfAnimBlendRate;

    // �u�����h���x
    float mfAnimBlendSpeed;

    // �Đ����x
    float mfAnimationSpeed;

    // �u�����h���ő�
    const float ANIMATION_BLEND_RATE_MAX = 1.0f;

public:
    State3DAnimationProcess();
    explicit State3DAnimationProcess(int modelHandle);
    ~State3DAnimationProcess() = default;

    /// <summary>���̃X�e�[�g�̃A�j���[�V�����f�[�^�ݒ�</summary>
    void SetMyAniamtionData(const OneAnimationData& oneAnimationData) { mstMyAniationData = oneAnimationData; }

protected:
    /*�A�j���[�V�������f�^�b�`*/
    virtual void AnimationDetach(STATE_ANEMATION_DATA* stateAnimationData);

    /*�A�j���[�V�������A�^�b�`*/
    virtual void AnimationAttach(STATE_ANEMATION_DATA* stateAnimationData);

    /*��O�̃A�j���[�V��������ݒ肷��*/
    virtual void PreAnimationDataSetting(STATE_ANEMATION_DATA* stateAnimationData);

    /*�A�j���[�V����������*/
    virtual void Init(STATE_ANEMATION_DATA* stateAnimationData);

    /*�A�j���[�V�����X�V*/
    void UpdateAnimation(STATE_ANEMATION_DATA* stateAnimationData);

    /*�u�����h�X�V*/
    void UpdateBlend();

    /*�A�j���[�V�������Ԃ�i�߂�*/
    void AdvanceAnimationTime(int animationHandle, float* animationCount, bool loopFlag, float animBlendRate);
};

/*----------*/
/*�y�A�j���[�V���������z*/
/*----------*/
class StateNoneAnimation : public IStateAnimation
{
public:
    StateNoneAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias);
    ~StateNoneAnimation() = default;

    /// <summary>���̏�Ԃɓ��������̏���(�������Ȃ�)</summary>
    virtual void OnEnter(STATE_ANEMATION_DATA* stateAnimationData, int preState) override {}

    /// <summary>���̏�Ԃ��o�鎞�̏���(�������Ȃ�)</summary>
    virtual void OnExit(STATE_ANEMATION_DATA* stateAnimationData, int nextState) override {}

    /// <summary>�I��</summary>
    virtual void Finalize(STATE_ANEMATION_DATA* stateAnimationData) override {}

    /// <summary>�X�V(�������Ȃ�)</summary>
    virtual void Update(STATE_ANEMATION_DATA* stateAnimationData) override {}

private:
    /*�A�j���[�V�������[�u��ނ����ނȂ�utrue�v��Ԃ�*/
    virtual bool CheckSimilarAnimationType(ANIMATION_TYPE animationMoveType) override;
};

/*------------------------*/
/*�yMV1���f���A�j���[�V�����z*/
/*------------------------*/
class StateMVOneAnimation : public IStateAnimation, public State3DAnimationProcess
{
public:
    StateMVOneAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias, int modelHandle, std::string fileName);
    ~StateMVOneAnimation() = default;

    /// <summary>���̏�Ԃɓ��������̏���</summary>
    virtual void OnEnter(STATE_ANEMATION_DATA* stateAnimationData, int preState) override;

    /// <summary>���̏�Ԃ��o�鎞�̏���</summary>
    virtual void OnExit(STATE_ANEMATION_DATA* stateAnimationData, int nextState) override;

    /// <summary>�I��</summary>
    virtual void Finalize(STATE_ANEMATION_DATA* stateAnimationData) override;

    /// <summary>�X�V</summary>
    virtual void Update(STATE_ANEMATION_DATA* stateAnimationData) override;

private:
    /*�A�j���[�V�������[�u��ނ����ނȂ�utrue�v��Ԃ�*/
    virtual bool CheckSimilarAnimationType(ANIMATION_TYPE animationMoveType) override;
};

/*--------------------------------*/
/*�yMV1���f�� �A�j���[�V�����������f���z*/
/*--------------------------------*/
class StateMVOneOnlyAnimation : public IStateAnimation, public State3DAnimationProcess
{
public:
    StateMVOneOnlyAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias, int modelHandle = -1);
    ~StateMVOneOnlyAnimation() = default;

    /// <summary>���̏�Ԃɓ��������̏���</summary>
    virtual void OnEnter(STATE_ANEMATION_DATA* stateAnimationData, int preState) override;

    /// <summary>���̏�Ԃ��o�鎞�̏���</summary>
    virtual void OnExit(STATE_ANEMATION_DATA* stateAnimationData, int nextState) override;

    /// <summary>�I��</summary>
    virtual void Finalize(STATE_ANEMATION_DATA* stateAnimationData) override;

    /// <summary>�X�V</summary>
    virtual void Update(STATE_ANEMATION_DATA* stateAnimationData) override;

protected:
    /*�A�j���[�V�������A�^�b�`*/
    virtual void AnimationAttach(STATE_ANEMATION_DATA* stateAnimationData) override;

    /*�A�j���[�V�������[�u��ނ����ނȂ�utrue�v��Ԃ�*/
    virtual bool CheckSimilarAnimationType(ANIMATION_TYPE animationMoveType) override;
};

/*----------------------*/
/*�yMV1���f�� ���f������z*/
/*----------------------*/
class StateMVOneOperationAnimation : public StateMVOneOnlyAnimation
{
private:
    // �ύX�ړ���
    VECTOR mvChangeMove;
    // �ړ���
    VECTOR mvMove;

    // �ύX�A���O����
    VECTOR mvChangeAngle;
    // �A���O��
    VECTOR mvAngle;

    // �傫���ύX��
    VECTOR mvChangeSize;
    // �傫��
    VECTOR mvSize;

public:
    StateMVOneOperationAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias, VECTOR changeVec = UtilCalc::VZero, VECTOR changeAngle = UtilCalc::VZero, VECTOR changeSize = UtilCalc::VZero, int modelHandle = -1);
    ~StateMVOneOperationAnimation() = default;

    /// <summary>���̏�Ԃɓ��������̏���</summary>
    virtual void OnEnter(STATE_ANEMATION_DATA* stateAnimationData, int preState) override;

    /// <summary>���̏�Ԃ��o�鎞�̏���</summary>
    virtual void OnExit(STATE_ANEMATION_DATA* stateAnimationData, int nextState) override;

    /// <summary>�X�V</summary>
    virtual void Update(STATE_ANEMATION_DATA* stateAnimationData) override;

protected:
    /*�A�j���[�V�������[�u��ނ����ނȂ�utrue�v��Ԃ�*/
    virtual bool CheckSimilarAnimationType(ANIMATION_TYPE animationMoveType) override;
};

/*--------------------*/
/*�y�G�t�F�N�g�A�j���[�V�����z*/
/*--------------------*/
class StateEffectAnimation : public IStateAnimation
{
private:
    int mnEffectHandle;

public:
    StateEffectAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias);
    ~StateEffectAnimation() = default;

    /// <summary>���̏�Ԃɓ��������̏���</summary>
    virtual void OnEnter(STATE_ANEMATION_DATA* stateAnimationData, int preState) override;
    /// <summary>���̏�Ԃ��o�鎞�̏���</summary>
    virtual void OnExit(STATE_ANEMATION_DATA* stateAnimationData, int nextState) override;
    /// <summary>�I��</summary>
    virtual void Finalize(STATE_ANEMATION_DATA* stateAnimationData) override;
    /// <summary>�X�V(�������Ȃ�)</summary>
    virtual void Update(STATE_ANEMATION_DATA* stateAnimationData) override;

private:
    /*�A�j���[�V�������[�u��ނ����ނȂ�utrue�v��Ԃ�*/
    virtual bool CheckSimilarAnimationType(ANIMATION_TYPE animationMoveType) override;
};

/*--------------*/
/*�y�摜�A�j���[�V�����z*/
/*--------------*/
class StateGraphAnimation : public IStateAnimation
{
public:
    StateGraphAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias);
    ~StateGraphAnimation() = default;


    /// <summary>���̏�Ԃɓ��������̏���</summary>
    virtual void OnEnter(STATE_ANEMATION_DATA* stateAnimationData, int preState) override;
    /// <summary>���̏�Ԃ��o�鎞�̏���</summary>
    virtual void OnExit(STATE_ANEMATION_DATA* stateAnimationData, int nextState) override;
    /// <summary>�I��</summary>
    virtual void Finalize(STATE_ANEMATION_DATA* stateAnimationData) override;
    /// <summary>�X�V(�������Ȃ�)</summary>
    virtual void Update(STATE_ANEMATION_DATA* stateAnimationData) override;

private:
    virtual bool CheckSimilarAnimationType(ANIMATION_TYPE animationMoveType) override;
};

/*--------------*/
/*�y����A�j���[�V�����z*/
/*--------------*/
class StateMovieAnimation : public IStateAnimation
{
public:
    StateMovieAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias);
    ~StateMovieAnimation() = default;

    /// <summary>���̏�Ԃɓ��������̏���</summary>
    virtual void OnEnter(STATE_ANEMATION_DATA* stateAnimationData, int preState) override;
    /// <summary>���̏�Ԃ��o�鎞�̏���</summary>
    virtual void OnExit(STATE_ANEMATION_DATA* stateAnimationData, int nextState) override;
    /// <summary>�I��</summary>
    virtual void Finalize(STATE_ANEMATION_DATA* stateAnimationData) override;
    /// <summary>�X�V(�������Ȃ�)</summary>
    virtual void Update(STATE_ANEMATION_DATA* stateAnimationData) override;

private:
    virtual bool CheckSimilarAnimationType(ANIMATION_TYPE animationMoveType) override;
};

/*----------------------*/
/*�y�t�F�[�h�摜�A�j���[�V�����z*/
/*----------------------*/
class StateFadeGraphAnimation : public IStateAnimation
{
public:
    StateFadeGraphAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias);
    ~StateFadeGraphAnimation() = default;

    /// <summary>���̏�Ԃɓ��������̏���</summary>
    virtual void OnEnter(STATE_ANEMATION_DATA* stateAnimationData, int preState) override;
    /// <summary>���̏�Ԃ��o�鎞�̏���</summary>
    virtual void OnExit(STATE_ANEMATION_DATA* stateAnimationData, int nextState) override;
    /// <summary>�I��</summary>
    virtual void Finalize(STATE_ANEMATION_DATA* stateAnimationData) override;
    /// <summary>�X�V(�������Ȃ�)</summary>
    virtual void Update(STATE_ANEMATION_DATA* stateAnimationData) override;

private:
    /*�t�F�[�h����*/
    void FadeProcess(STATE_ANEMATION_DATA* stateAnimationData);

    /*�A�j���[�V�������[�u��ނ����ނȂ�utrue�v��Ԃ�*/
    virtual bool CheckSimilarAnimationType(ANIMATION_TYPE animationMoveType) override;
};

/*-------------------*/
/*�yDOTween�A�j���[�V�����z*/
/*-------------------*/
class StateDOTweenAnimation : public IStateAnimation
{
public:
    StateDOTweenAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias);
    ~StateDOTweenAnimation() = default;

    /// <summary>���̏�Ԃɓ��������̏���</summary>
    virtual void OnEnter(STATE_ANEMATION_DATA* stateAnimationData, int preState) override;
    /// <summary>���̏�Ԃ��o�鎞�̏���</summary>
    virtual void OnExit(STATE_ANEMATION_DATA* stateAnimationData, int nextState) override;
    /// <summary>�I��</summary>
    virtual void Finalize(STATE_ANEMATION_DATA* stateAnimationData) override;
    /// <summary>�X�V(�������Ȃ�)</summary>
    virtual void Update(STATE_ANEMATION_DATA* stateAnimationData) override;

private:
    /*�A�j���[�V�������[�u��ނ����ނȂ�utrue�v��Ԃ�*/
    virtual bool CheckSimilarAnimationType(ANIMATION_TYPE animationMoveType) override;
};
// #pragma once
// #include <map>
// #include <string>

// #include "AnimationEnum.h"
// #include "AnimationData.h"

// #include "Animation.h"
// #include "ModelBase.h"
// #include "StateAnimation.h"
// #include "UtilCalc.h"
// // TODO: 3D�A�j���[�V������2D�A�j���[�V�����ŕ����� �X�e�[�g�ݒ莞�i���o�[�ݒ�

// /*----------*/
// /*�y�A�j���[�V�����X�e�[�g���ʏ����z
// /*----------*/
// class StateAnimationProcess
// {
// protected:
//     // MV1�A�j���V�������
//     struct MVOneAnimationData
//     {
//         float animationCount;   // �A�j���[�V�����J�E���g
//         int animationHandle;    // �A�j���V�����n���h��
//         bool loopFlag;          // ���[�v�t���O
//     };

// protected:
//     // // ���f���n���h��
//     // int mnModelHandle;
    
//     // ��O�̃A�j���[�V�������
//     MVOneAnimationData mstPreAnimationData;

//     // �A�j���[�V�������
//     ANIMATION_MOVE_TYPE_TYPE meAnimationType;

//     // �u�����h��
//     float mfAnimBlendRate;

//     // �u�����h���x
//     float mfAnimBlendSpeed;

//     // �Đ����x
//     float mfAnimationSpeed;

//     // �u�����h���ő�
//     const float ANIMATION_BLEND_RATE_MAX = 1.0f;
// public:
//     StateAnimationProcess(int handle);
//     ~StateAnimationProcess() = default;

// protected:
//     /*�A�j���[�V�������f�^�b�`*/
//     virtual void AnimationDetach(Animation* animation, AnimationDatas* animationDatas);

//     /*�A�j���[�V�������A�^�b�`*/
//     virtual void AnimationAttach(Animation* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas);

//     /*��O�̃A�j���[�V��������ݒ肷��*/
//     virtual void PreAnimationDataSetting(Animation* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas);

//     /*�A�j���[�V����������*/
//     virtual void Init(Animation* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas);

//     /*�A�j���[�V�����X�V*/
//     void UpdateAnimation(OneAnimationData *nowAnimationData);

//     /*�u�����h�X�V*/
//     void UpdateBlend();

//     /*�A�j���[�V�������Ԃ�i�߂�*/
//     void AdvanceAnimationTime(int animationHandle, float* animationCount, bool loopFlag, float animBlendRate, bool testFlag);
// };

// /*----------*/
// /*�y�A�j���[�V���������z
// /*----------*/
// class StateNoneAnimation : public IStateAnimation
// {
// public:
//     StateNoneAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias);
//     ~StateNoneAnimation() = default;

//     /// <summary>���̏�Ԃɓ��������̏���(�������Ȃ�)</summary>
//     /// <param name="animationData">�A�j���[�V�������</param>
//     /// <param name="preState">�A�j���[�V�������</param>
//     //virtual void OnEnter(STATE_ANEMATION_DATA* animationData, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, ANIMATION_TYPE oldModelType) override {}
//     virtual void OnEnter(STATE_ANEMATION_DATA* animationData, ANIMATION_MOVE_TYPE_TYPE preState) override {}
//     /// <summary>���̏�Ԃ��o�鎞�̏���(�������Ȃ�)</summary>
//     /// <param name="animationData">�A�j���[�V�������</param>
//     /// <param name="nextState">���̃A�j���[�V�������</param>
//     //virtual void OnExit(Animation* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, ANIMATION_TYPE newModelType) override {}
//     virtual void OnExit(STATE_ANEMATION_DATA* animationData, ANIMATION_MOVE_TYPE_TYPE nextState) override {}

//     /// <summary>�I��</summary>
//     virtual void Finalize(Animation* animation, AnimationDatas* animationDatas) override {}

//     /// <summary>�X�V(�������Ȃ�)</summary>
//     /// <param name="animation">�A�j���[�V����</param>
//     /// <param name="animationDatas">�A�j���[�V�������</param>
//     virtual void Update(Animation* animation, OneAnimationData *nowAnimationData) override {}

// private:
//     /*���f����ނ����ނȂ�utrue�v��Ԃ�*/
//     bool CheckSimilarModelType(ANIMATION_TYPE modelType) override { return false; }

// };


// /*----------*/
// /*�yMV1���f���A�j���[�V�����z
// /*----------*/
// class StateMVOneAnimation : public IStateAnimation, public StateAnimationProcess
// {
// public:
//     // FIXME: �R���X�g���N�^�ŃX�e�[�g�ύX������n���܂�
//     StateMVOneAnimation(int modelHandle, std::string fileName, std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias);
//     ~StateMVOneAnimation() = default;

//    /// <summary>���̏�Ԃɓ��������̏���</summary>
//     /// <param name="animationData">�A�j���[�V�������</param>
//     /// <param name="preState">�A�j���[�V�������</param>
//     virtual void OnEnter(STATE_ANEMATION_DATA* animationData, ANIMATION_MOVE_TYPE_TYPE preState) override;
//   /// <summary>���̏�Ԃ��o�鎞�̏���</summary>
//     /// <param name="animationData">�A�j���[�V�������</param>
//     /// <param name="nextState">���̃A�j���[�V�������</param>
//     virtual void OnExit(STATE_ANEMATION_DATA* animationData, ANIMATION_MOVE_TYPE_TYPE nextState) override;

//     /// <summary>�I��</summary>
//     virtual void Finalize(Animation* animation, AnimationDatas* animationDatas) override;

//     /// <summary>�X�V</summary>
//     /// <param name="animation">�A�j���[�V����</param>
//     /// <param name="animationDatas">�A�j���[�V�������</param>
//     virtual void Update(Animation* animation, OneAnimationData *nowAnimationData) override;

// private:
//     /*���f����ނ����ނȂ�utrue�v��Ԃ�*/
//     bool CheckSimilarModelType(ANIMATION_TYPE modelType) override;
// };

// /*----------*/
// /*�yMV1���f���@�A�j���[�V�����������f���z
// /*----------*/
// class StateMVOneOnlyAnimation : public IStateAnimation, public StateAnimationProcess
// {
// public:
//     // FIXME: �R���X�g���N�^�ŃX�e�[�g�ύX������n���܂�
//     StateMVOneOnlyAnimation(int modelHandle, std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias);
//     ~StateMVOneOnlyAnimation() = default;

//    /// <summary>���̏�Ԃɓ��������̏���</summary>
//     /// <param name="animationData">�A�j���[�V�������</param>
//     /// <param name="preState">�A�j���[�V�������</param>
//     virtual void OnEnter(STATE_ANEMATION_DATA* animationData, ANIMATION_MOVE_TYPE_TYPE preState) override;
//   /// <summary>���̏�Ԃ��o�鎞�̏���</summary>
//     /// <param name="animationData">�A�j���[�V�������</param>
//     /// <param name="nextState">���̃A�j���[�V�������</param>
//     virtual void OnExit(STATE_ANEMATION_DATA* animationData, ANIMATION_MOVE_TYPE_TYPE nextState) override;

//     /// <summary>�I��</summary>
//     virtual void Finalize(Animation* animation, AnimationDatas* animationDatas) override;

//     /// <summary>�X�V</summary>
//     /// <param name="animation">�A�j���[�V����</param>
//     /// <param name="animationDatas">�A�j���[�V�������</param>
//     virtual void Update(Animation* animation, OneAnimationData *nowAnimationData) override;

// protected:

//     /*���f����ނ����ނȂ�utrue�v��Ԃ�*/
//     virtual bool CheckSimilarModelType(ANIMATION_TYPE modelType) override;

//     /*�A�j���[�V�������A�^�b�`*/
//     virtual void AnimationAttach(Animation* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas) override;
// };


// /*----------*/
// /*�yMV1���f�� ���f������z
// /*----------*/
// class StateMVOneOperationAnimation : public StateMVOneOnlyAnimation
// {
// private:
//     // �ύX�ړ���
//     VECTOR mvChangeMove;
//     // �ړ���
//     VECTOR mvMove;

//     // �ύX�A���O����
//     VECTOR mvChangeAngle;
//     // �A���O��
//     VECTOR mvAngle;

    
//     // �傫���ύX��
//     VECTOR mvChangeSize;
//     // �傫��
//     VECTOR mvSize;

// public:
//     // FIXME: �R���X�g���N�^�ŃX�e�[�g�ύX������n���܂�
//     StateMVOneOperationAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias, int modelHandle, VECTOR changeVec = UtilCalc::VZero, VECTOR changeAngle = UtilCalc::VZero, VECTOR changeSize = UtilCalc::VZero);
//     ~StateMVOneOperationAnimation() = default;

//    /// <summary>���̏�Ԃɓ��������̏���</summary>
//     /// <param name="animationData">�A�j���[�V�������</param>
//     /// <param name="preState">�A�j���[�V�������</param>
//     virtual void OnEnter(STATE_ANEMATION_DATA* animationData, ANIMATION_MOVE_TYPE_TYPE preState) override;
//   /// <summary>���̏�Ԃ��o�鎞�̏���</summary>
//     /// <param name="animationData">�A�j���[�V�������</param>
//     /// <param name="nextState">���̃A�j���[�V�������</param>
//     virtual void OnExit(STATE_ANEMATION_DATA* animationData, ANIMATION_MOVE_TYPE_TYPE nextState) override;

//     /// <summary>�X�V</summary>
//     /// <param name="animation">�A�j���[�V����</param>
//     /// <param name="animationDatas">�A�j���[�V�������</param>
//     virtual void Update(Animation* animation, OneAnimationData *nowAnimationData) override;


// protected:
//     /*���f����ނ����ނȂ�utrue�v��Ԃ�*/
//     virtual bool CheckSimilarModelType(ANIMATION_TYPE modelType) override;
// };


// /*----------*/
// /*�y�G�t�F�N�g�A�j���[�V�����z
// /*----------*/
// class StateEffectAnimation : public IStateAnimation
// {
// private:
//     int* mnEffectHandle;

// public:
//     // FIXME: �R���X�g���N�^�ŃX�e�[�g�ύX������n���܂�
//     StateEffectAnimation(int* effectHandle, std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias);
//     ~StateEffectAnimation() = default;

//    /// <summary>���̏�Ԃɓ��������̏���</summary>
//     /// <param name="animationData">�A�j���[�V�������</param>
//     /// <param name="preState">�A�j���[�V�������</param>
//     virtual void OnEnter(STATE_ANEMATION_DATA* animationData, ANIMATION_MOVE_TYPE_TYPE preState) override;
//   /// <summary>���̏�Ԃ��o�鎞�̏���</summary>
//     /// <param name="animationData">�A�j���[�V�������</param>
//     /// <param name="nextState">���̃A�j���[�V�������</param>
//     virtual void OnExit(STATE_ANEMATION_DATA* animationData, ANIMATION_MOVE_TYPE_TYPE nextState) override;

//     /// <summary>�I��</summary>
//     virtual void Finalize(Animation* animation, AnimationDatas* animationDatas) override;

//     /// <summary>�X�V(�������Ȃ�)</summary>
//     /// <param name="animation">�A�j���[�V����</param>
//     /// <param name="animationDatas">�A�j���[�V�������</param>
//     virtual void Update(Animation* animation, OneAnimationData *nowAnimationData) override;

// private:
//     /*���f����ނ����ނȂ�utrue�v��Ԃ�*/
//     bool CheckSimilarModelType(ANIMATION_TYPE modelType) override;

// };


// /*----------*/
// /*�y�摜���[�V�����z
// /*----------*/
// class StateGraphAnimation : public IStateAnimation
// {
// public:
//     // FIXME: �R���X�g���N�^�ŃX�e�[�g�ύX������n���܂�
//     StateGraphAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias);
//     ~StateGraphAnimation() = default;

//    /// <summary>���̏�Ԃɓ��������̏���</summary>
//     /// <param name="animationData">�A�j���[�V�������</param>
//     /// <param name="preState">�A�j���[�V�������</param>
//     virtual void OnEnter(STATE_ANEMATION_DATA* animationData, ANIMATION_MOVE_TYPE_TYPE preState) override;
//   /// <summary>���̏�Ԃ��o�鎞�̏���</summary>
//     /// <param name="animationData">�A�j���[�V�������</param>
//     /// <param name="nextState">���̃A�j���[�V�������</param>
//     virtual void OnExit(STATE_ANEMATION_DATA* animationData, ANIMATION_MOVE_TYPE_TYPE nextState) override;

//     /// <summary>�I��</summary>
//     virtual void Finalize(Animation* animation, AnimationDatas* animationDatas) override;

//     /// <summary>�X�V(�������Ȃ�)</summary>
//     /// <param name="animation">�A�j���[�V����</param>
//     /// <param name="animationDatas">�A�j���[�V�������</param>
//     virtual void Update(Animation* animation, OneAnimationData *nowAnimationData) override;

// private:
//     /*���f����ނ����ނȂ�utrue�v��Ԃ�*/
//     bool CheckSimilarModelType(ANIMATION_TYPE modelType) override;

// };


// /*----------*/
// /*�y����A�j���[�V�����z
// /*----------*/
// class StateMovieAnimation : public IStateAnimation
// {
// public:
//     // FIXME: �R���X�g���N�^�ŃX�e�[�g�ύX������n���܂�
//     StateMovieAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias);
//     ~StateMovieAnimation() = default;

//    /// <summary>���̏�Ԃɓ��������̏���</summary>
//     /// <param name="animationData">�A�j���[�V�������</param>
//     /// <param name="preState">�A�j���[�V�������</param>
//     virtual void OnEnter(STATE_ANEMATION_DATA* animationData, ANIMATION_MOVE_TYPE_TYPE preState) override;
//   /// <summary>���̏�Ԃ��o�鎞�̏���</summary>
//     /// <param name="animationData">�A�j���[�V�������</param>
//     /// <param name="nextState">���̃A�j���[�V�������</param>
//     virtual void OnExit(STATE_ANEMATION_DATA* animationData, ANIMATION_MOVE_TYPE_TYPE nextState) override;

//     /// <summary>�I��</summary>
//     virtual void Finalize(Animation* animation, AnimationDatas* animationDatas) override;

//     /// <summary>�X�V(�������Ȃ�)</summary>
//     /// <param name="animation">�A�j���[�V����</param>
//     /// <param name="animationDatas">�A�j���[�V�������</param>
//     virtual void Update(Animation* animation, OneAnimationData *nowAnimationData) override;

// private:
//     /*���f����ނ����ނȂ�utrue�v��Ԃ�*/
//     bool CheckSimilarModelType(ANIMATION_TYPE modelType) override;

// };

// /*------------------------------*/
// /*�y�t�F�[�h�摜�A�j���[�V�����z*/
// /*------------------------------*/
// class StateFadeGraphAnimation : public IStateAnimation
// {
// public:
//     // FIXME: �R���X�g���N�^�ŃX�e�[�g�ύX������n���܂�
//     StateFadeGraphAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias);
//     ~StateFadeGraphAnimation() = default;

//    /// <summary>���̏�Ԃɓ��������̏���</summary>
//     /// <param name="animationData">�A�j���[�V�������</param>
//     /// <param name="preState">�A�j���[�V�������</param>
//     virtual void OnEnter(STATE_ANEMATION_DATA* animationData, ANIMATION_MOVE_TYPE_TYPE preState) override;
//   /// <summary>���̏�Ԃ��o�鎞�̏���</summary>
//     /// <param name="animationData">�A�j���[�V�������</param>
//     /// <param name="nextState">���̃A�j���[�V�������</param>
//     virtual void OnExit(STATE_ANEMATION_DATA* animationData, ANIMATION_MOVE_TYPE_TYPE nextState) override;

//     /// <summary>�I��</summary>
//     virtual void Finalize(Animation* animation, AnimationDatas* animationDatas) override;
//     /// <summary>�X�V(�������Ȃ�)</summary>
//     /// <param name="animation">�A�j���[�V����</param>
//     /// <param name="animationDatas">�A�j���[�V�������</param>
//     virtual void Update(Animation* animation, OneAnimationData *nowAnimationData) override;

// private:

//     /*�t�F�[�h����*/
//     void FadeProcess(OneAnimationData *nowAnimationData);

//     /*���f����ނ����ނȂ�utrue�v��Ԃ�*/
//     bool CheckSimilarModelType(ANIMATION_TYPE modelType) override;
// };

// /*-------------------------*/
// /*�yDOTween�A�j���[�V�����z*/
// /*-------------------------*/
// class StateDOTweenAnimation : public IStateAnimation
// {
// public:
//     // FIXME: �R���X�g���N�^�ŃX�e�[�g�ύX������n���܂�
//     StateDOTweenAnimation(std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias);
//     ~StateDOTweenAnimation() = default;

//    /// <summary>���̏�Ԃɓ��������̏���</summary>
//     /// <param name="animationData">�A�j���[�V�������</param>
//     /// <param name="preState">�A�j���[�V�������</param>
//     virtual void OnEnter(STATE_ANEMATION_DATA* animationData, ANIMATION_MOVE_TYPE_TYPE preState) override;
//   /// <summary>���̏�Ԃ��o�鎞�̏���</summary>
//     /// <param name="animationData">�A�j���[�V�������</param>
//     /// <param name="nextState">���̃A�j���[�V�������</param>
//     virtual void OnExit(STATE_ANEMATION_DATA* animationData, ANIMATION_MOVE_TYPE_TYPE nextState) override;
    
//     /// <summary>�I��</summary>
//     virtual void Finalize(Animation* animation, AnimationDatas* animationDatas) override;

//     /// <summary>�X�V</summary>
//     /// <param name="animation">�A�j���[�V����</param>
//     /// <param name="animationDatas">�A�j���[�V�������</param>
//     virtual void Update(Animation* animation, OneAnimationData *nowAnimationData) override;

// private:
//     /*���f����ނ����ނȂ�utrue�v��Ԃ�*/
//     bool CheckSimilarModelType(ANIMATION_TYPE modelType) override;
// };