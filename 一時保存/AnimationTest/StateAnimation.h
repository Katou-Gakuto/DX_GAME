#pragma once
#include <string>
#include <vector>

#include "DxLib.h"

#include "StateData.h"
#include "StateAnimationBase.h"

struct OneAnimationData;
struct AnimationDatas;

class AnimationBase;
class ModelBase;

/*----------*/
/*ÅyÉAÉjÉÅÅ[ÉVÉáÉìèàóùã§í Åz*/
/*----------*/
class StateAnimationProcess
{
protected:
    int mnModelHandle;

    ModelBase* mpModelBase;

    float mfAnimationSpeed;

public:
    StateAnimationProcess(int modelHandle);
    ~StateAnimationProcess() = default;

protected:
    void Init(
        AnimationBase* animation,
        OneAnimationData* nowAnimationData,
        AnimationDatas* animationDatas);

    virtual void AnimationAttach(
        AnimationBase* animation,
        OneAnimationData* nowAnimationData,
        AnimationDatas* animationDatas);

    void AnimationDetach(
        AnimationBase* animation,
        AnimationDatas* animationDatas);

    void UpdateAnimation(
        OneAnimationData* nowAnimationData);

    void AdvanceAnimationTime(
        int animationHandle,
        float* animationCount,
        bool loopFlag,
        float animBlendRate,
        bool testFlag = false);
};

/*----------*/
/*ÅyMV1ÉÇÉfÉãÉAÉjÉÅÅ[ÉVÉáÉìÅz*/
/*----------*/
class StateMVOneAnimation
    : public IStateAnimation
    , protected StateAnimationProcess
{
public:
    StateMVOneAnimation(
        int modelHandle,
        std::string fileName,
        std::vector<
            STATE_CHANGE_CRITERIA_DATA<
                int,
                STATE_ANEMATION_DATA
            >
        > stateChangeCriterias);

    void OnEnter(
        STATE_ANEMATION_DATA* data,
        int preState) override;

    void OnExit(
        STATE_ANEMATION_DATA* data,
        int nextState) override;

    void Finalize(
        STATE_ANEMATION_DATA* data) override;

    void Update(
        STATE_ANEMATION_DATA* data) override;

    bool CheckSimilarModelType(
        MODEL_TYPE modelType) override;
};

/*-----------------------------*/
/*ÅyMV1ÉÇÉfÉã ÉAÉjÉÅÅ[ÉVÉáÉìÇÃÇ›Åz*/
/*-----------------------------*/
class StateMVOneOnlyAnimation
    : public StateMVOneAnimation
{
public:
    StateMVOneOnlyAnimation(
        int modelHandle,
        std::vector<
            STATE_CHANGE_CRITERIA_DATA<
                int,
                STATE_ANEMATION_DATA
            >
        > stateChangeCriterias);

    void OnEnter(
        STATE_ANEMATION_DATA* data,
        int preState) override;

    void OnExit(
        STATE_ANEMATION_DATA* data,
        int nextState) override;

    void Finalize(
        STATE_ANEMATION_DATA* data) override;

    void Update(
        STATE_ANEMATION_DATA* data) override;

    bool CheckSimilarModelType(
        MODEL_TYPE modelType) override;

protected:
    void AnimationAttach(
        AnimationBase* animation,
        OneAnimationData* nowAnimationData,
        AnimationDatas* animationDatas) override;
};

/*-------------------------*/
/*ÅyMV1ÉÇÉfÉã ÉÇÉfÉãëÄçÏÅz*/
/*-------------------------*/
class StateMVOneOperationAnimation
    : public StateMVOneOnlyAnimation
{
private:
    VECTOR mvChangeMove;
    VECTOR mvMove;

    VECTOR mvChangeAngle;
    VECTOR mvAngle;

    VECTOR mvChangeSize;
    VECTOR mvSize;

public:
    StateMVOneOperationAnimation(
        int modelHandle,
        VECTOR changeVec,
        VECTOR changeAngle,
        VECTOR changeSize,
        std::vector<
            STATE_CHANGE_CRITERIA_DATA<
                int,
                STATE_ANEMATION_DATA
            >
        > stateChangeCriterias);

    void OnEnter(
        STATE_ANEMATION_DATA* data,
        int preState) override;

    void OnExit(
        STATE_ANEMATION_DATA* data,
        int nextState) override;

    void Update(
        STATE_ANEMATION_DATA* data) override;

    bool CheckSimilarModelType(
        MODEL_TYPE modelType) override;
};

/*----------*/
/*ÅyÉGÉtÉFÉNÉgÅz*/
/*----------*/
class StateEffectAnimation
    : public IStateAnimation
{
private:
    int* mnEffectHandle;

public:
    StateEffectAnimation(
        int* effectHandle,
        std::vector<
            STATE_CHANGE_CRITERIA_DATA<
                int,
                STATE_ANEMATION_DATA
            >
        > stateChangeCriterias);

    void OnEnter(
        STATE_ANEMATION_DATA* data,
        int preState) override;

    void OnExit(
        STATE_ANEMATION_DATA* data,
        int nextState) override;

    void Finalize(
        STATE_ANEMATION_DATA* data) override;

    void Update(
        STATE_ANEMATION_DATA* data) override;

    bool CheckSimilarModelType(
        MODEL_TYPE modelType) override;
};

/*----------*/
/*ÅyâÊëúÅz*/
/*----------*/
class StateGraphAnimation
    : public IStateAnimation
{
public:
    StateGraphAnimation(
        std::vector<
            STATE_CHANGE_CRITERIA_DATA<
                int,
                STATE_ANEMATION_DATA
            >
        > stateChangeCriterias);

    void OnEnter(
        STATE_ANEMATION_DATA* data,
        int preState) override;

    void OnExit(
        STATE_ANEMATION_DATA* data,
        int nextState) override;

    void Finalize(
        STATE_ANEMATION_DATA* data) override;

    void Update(
        STATE_ANEMATION_DATA* data) override;

    bool CheckSimilarModelType(
        MODEL_TYPE modelType) override;
};

/*----------*/
/*ÅyìÆâÊÅz*/
/*----------*/
class StateMovieAnimation
    : public IStateAnimation
{
public:
    StateMovieAnimation(
        std::vector<
            STATE_CHANGE_CRITERIA_DATA<
                int,
                STATE_ANEMATION_DATA
            >
        > stateChangeCriterias);

    void OnEnter(
        STATE_ANEMATION_DATA* data,
        int preState) override;

    void OnExit(
        STATE_ANEMATION_DATA* data,
        int nextState) override;

    void Finalize(
        STATE_ANEMATION_DATA* data) override;

    void Update(
        STATE_ANEMATION_DATA* data) override;

    bool CheckSimilarModelType(
        MODEL_TYPE modelType) override;
};

/*------------------------------*/
/*ÅyÉtÉFÅ[ÉhâÊëúÉAÉjÉÅÅ[ÉVÉáÉìÅz*/
/*------------------------------*/
class StateFadeGraphAnimation
    : public IStateAnimation
{
public:
    StateFadeGraphAnimation(
        std::vector<
            STATE_CHANGE_CRITERIA_DATA<
                int,
                STATE_ANEMATION_DATA
            >
        > stateChangeCriterias);

    void OnEnter(
        STATE_ANEMATION_DATA* data,
        int preState) override;

    void OnExit(
        STATE_ANEMATION_DATA* data,
        int nextState) override;

    void Finalize(
        STATE_ANEMATION_DATA* data) override;

    void Update(
        STATE_ANEMATION_DATA* data) override;

    bool CheckSimilarModelType(
        MODEL_TYPE modelType) override;

private:
    void FadeProcess(
        OneAnimationData* nowAnimationData);
};

/*----------*/
/*ÅyDOTweenÅz*/
/*----------*/
class StateDOTweenAnimation
    : public IStateAnimation
{
public:
    StateDOTweenAnimation(
        std::vector<
            STATE_CHANGE_CRITERIA_DATA<
                int,
                STATE_ANEMATION_DATA
            >
        > stateChangeCriterias);

    void OnEnter(
        STATE_ANEMATION_DATA* data,
        int preState) override;

    void OnExit(
        STATE_ANEMATION_DATA* data,
        int nextState) override;

    void Finalize(
        STATE_ANEMATION_DATA* data) override;

    void Update(
        STATE_ANEMATION_DATA* data) override;

    bool CheckSimilarModelType(
        MODEL_TYPE modelType) override;
};