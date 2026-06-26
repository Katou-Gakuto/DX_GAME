/*----------*/
/*ÅyMV1ÉÇÉfÉãÉAÉjÉÅÅ[ÉVÉáÉìÅz*/
/*----------*/

StateMVOneAnimation::StateMVOneAnimation(
    int modelHandle,
    std::string fileName,
    std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>>
        stateChangeCriterias)
    : IStateAnimation(
        stateChangeCriterias,
        static_cast<int>(MODEL_TYPE::MV1_MODEL))
    , StateAnimationProcess(modelHandle)
{
    int moveAnimFrameIndex =
        MV1SearchFrame(mnModelHandle, fileName.c_str());

    MV1SetFrameUserLocalMatrix(
        mnModelHandle,
        moveAnimFrameIndex,
        MV1GetFrameLocalMatrix(
            mnModelHandle,
            moveAnimFrameIndex));

    mStateNumber = static_cast<int>(MODEL_TYPE::MV1_MODEL);
}

void StateMVOneAnimation::OnEnter(
    STATE_ANEMATION_DATA* data,
    int preState)
{
    Init(
        data->StateAnimation,
        data->StateOneAnimationData,
        data->StateAnimationDatas);
}

void StateMVOneAnimation::OnExit(
    STATE_ANEMATION_DATA* data,
    int nextState)
{
    AnimationDetach(
        data->StateAnimation,
        data->StateAnimationDatas);
}

void StateMVOneAnimation::Finalize(
    STATE_ANEMATION_DATA* data)
{
}

void StateMVOneAnimation::Update(
    STATE_ANEMATION_DATA* data)
{
    UpdateAnimation(
        data->StateOneAnimationData);
}

bool StateMVOneAnimation::CheckSimilarModelType(
    MODEL_TYPE modelType)
{
    switch (modelType)
    {
    case MODEL_TYPE::MV1_MODEL:
        return true;
    }

    return false;
}


/*-----------------------------*/
/*ÅyMV1ÉÇÉfÉã ÉAÉjÉÅÅ[ÉVÉáÉìÇÃÇ›Åz*/
/*-----------------------------*/

StateMVOneOnlyAnimation::StateMVOneOnlyAnimation(
    int modelHandle,
    std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>>
        stateChangeCriterias)
    : StateMVOneAnimation(
        modelHandle,
        "",
        stateChangeCriterias)
{
    mStateNumber =
        static_cast<int>(MODEL_TYPE::MV1_MODEL_ONLY);
}

void StateMVOneOnlyAnimation::OnEnter(
    STATE_ANEMATION_DATA* data,
    int preState)
{
    Init(
        data->StateAnimation,
        data->StateOneAnimationData,
        data->StateAnimationDatas);
}

void StateMVOneOnlyAnimation::OnExit(
    STATE_ANEMATION_DATA* data,
    int nextState)
{
    AnimationDetach(
        data->StateAnimation,
        data->StateAnimationDatas);
}

void StateMVOneOnlyAnimation::Finalize(
    STATE_ANEMATION_DATA* data)
{
    AnimationDatas* animationDatas =
        data->StateAnimationDatas;

    std::vector<ANIMATION_TYPE>
        deleteAnimationType;

    deleteAnimationType.reserve(
        animationDatas->animDatas.size());

    for (auto& animationData :
         animationDatas->animDatas)
    {
        if (animationData.second.number != -1)
        {
            deleteAnimationType.push_back(
                animationData.first);

            Master::mpResourceManager
                ->Get3DModelResource()
                ->ReduceResourceHandle(
                    animationData.second.number);
        }
    }

    if (deleteAnimationType.size() ==
        animationDatas->animDatas.size())
    {
        animationDatas->animDatas.clear();
        return;
    }

    for (auto type : deleteAnimationType)
    {
        animationDatas->animDatas.erase(type);
    }
}

void StateMVOneOnlyAnimation::Update(
    STATE_ANEMATION_DATA* data)
{
    UpdateAnimation(
        data->StateOneAnimationData);
}

bool StateMVOneOnlyAnimation::CheckSimilarModelType(
    MODEL_TYPE modelType)
{
    switch (modelType)
    {
    case MODEL_TYPE::MV1_MODEL_MOVE:
    case MODEL_TYPE::MV1_MODEL_ONLY:
        return true;
    }

    return false;
}

void StateMVOneOnlyAnimation::AnimationAttach(
    AnimationBase* animation,
    OneAnimationData* nowAnimationData,
    AnimationDatas* animationDatas)
{
    nowAnimationData->animationHandle =
        MV1AttachAnim(
            mnModelHandle,
            0,
            nowAnimationData->number,
            FALSE);

    nowAnimationData->animationCount = 0.0f;
}


/*-------------------------*/
/*ÅyMV1ÉÇÉfÉã ÉÇÉfÉãëÄçÏÅz*/
/*-------------------------*/

StateMVOneOperationAnimation::StateMVOneOperationAnimation(
    int modelHandle,
    VECTOR changeVec,
    VECTOR changeAngle,
    VECTOR changeSize,
    std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>>
        stateChangeCriterias)
    : StateMVOneOnlyAnimation(
        modelHandle,
        stateChangeCriterias)
    , mvChangeMove(changeVec)
    , mvMove(UtilCalc::VZero)
    , mvChangeAngle(changeAngle)
    , mvAngle(UtilCalc::VZero)
    , mvChangeSize(changeSize)
    , mvSize(UtilCalc::VZero)
{
    mStateNumber =
        static_cast<int>(MODEL_TYPE::MV1_MODEL_MOVE);
}

void StateMVOneOperationAnimation::OnEnter(
    STATE_ANEMATION_DATA* data,
    int preState)
{
    Init(
        data->StateAnimation,
        data->StateOneAnimationData,
        data->StateAnimationDatas);

    mvMove = UtilCalc::VZero;
    mvAngle = UtilCalc::VZero;
    mvSize = UtilCalc::VZero;
}

void StateMVOneOperationAnimation::OnExit(
    STATE_ANEMATION_DATA* data,
    int nextState)
{
    AnimationDetach(
        data->StateAnimation,
        data->StateAnimationDatas);

    mpModelBase->SetPosition(
        VSub(
            mpModelBase->GetPosition(),
            mvMove));

    mpModelBase->SetAngle(
        VSub(
            mpModelBase->GetAngle(),
            mvAngle));

    mpModelBase->SetSize(
        VSub(
            mpModelBase->GetSize(),
            mvSize));
}

void StateMVOneOperationAnimation::Update(
    STATE_ANEMATION_DATA* data)
{
    mvMove =
        VAdd(mvMove, mvChangeMove);

    mvAngle =
        VAdd(mvAngle, mvChangeAngle);

    mvSize =
        VAdd(mvSize, mvChangeSize);

    mpModelBase->SetPosition(
        VAdd(
            mpModelBase->GetPosition(),
            mvChangeMove));

    mpModelBase->SetAngle(
        VAdd(
            mpModelBase->GetAngle(),
            mvChangeAngle));

    mpModelBase->SetSize(
        VAdd(
            mpModelBase->GetSize(),
            mvChangeSize));
}

bool StateMVOneOperationAnimation::CheckSimilarModelType(
    MODEL_TYPE modelType)
{
    return false;
}


/*----------*/
/*ÅyÉGÉtÉFÉNÉgÅz*/
/*----------*/

void StateEffectAnimation::OnEnter(
    STATE_ANEMATION_DATA* data,
    int preState)
{
    if (!mpModelBase->GetDrawFlag())
    {
        return;
    }

    *mnEffectHandle =
        Master::mpResourceManager
            ->GetEffectResource()
            ->GetEffectHandle(
                data->StateOneAnimationData->number,
                *mnEffectHandle);
}

void StateEffectAnimation::OnExit(
    STATE_ANEMATION_DATA* data,
    int nextState)
{
    if (*mnEffectHandle == -1)
    {
        return;
    }

    Master::mpResourceManager
        ->GetEffectResource()
        ->DeletePlayEffectHandle(
            *mnEffectHandle);

    *mnEffectHandle = -1;
}

void StateEffectAnimation::Finalize(
    STATE_ANEMATION_DATA* data)
{
}

void StateEffectAnimation::Update(
    STATE_ANEMATION_DATA* data)
{
}

bool StateEffectAnimation::CheckSimilarModelType(
    MODEL_TYPE modelType)
{
    return false;
}


/*----------*/
/*ÅyâÊëúÅz*/
/*----------*/

void StateGraphAnimation::OnEnter(
    STATE_ANEMATION_DATA* data,
    int preState)
{
}

void StateGraphAnimation::OnExit(
    STATE_ANEMATION_DATA* data,
    int nextState)
{
}

void StateGraphAnimation::Finalize(
    STATE_ANEMATION_DATA* data)
{
}

void StateGraphAnimation::Update(
    STATE_ANEMATION_DATA* data)
{
}

bool StateGraphAnimation::CheckSimilarModelType(
    MODEL_TYPE modelType)
{
    return false;
}


/*----------*/
/*ÅyìÆâÊÅz*/
/*----------*/

void StateMovieAnimation::OnEnter(
    STATE_ANEMATION_DATA* data,
    int preState)
{
}

void StateMovieAnimation::OnExit(
    STATE_ANEMATION_DATA* data,
    int nextState)
{
}

void StateMovieAnimation::Finalize(
    STATE_ANEMATION_DATA* data)
{
}

void StateMovieAnimation::Update(
    STATE_ANEMATION_DATA* data)
{
}

bool StateMovieAnimation::CheckSimilarModelType(
    MODEL_TYPE modelType)
{
    return false;
}


/*------------------------------*/
/*ÅyÉtÉFÅ[ÉhâÊëúÉAÉjÉÅÅ[ÉVÉáÉìÅz*/
/*------------------------------*/

void StateFadeGraphAnimation::OnEnter(
    STATE_ANEMATION_DATA* data,
    int preState)
{
}

void StateFadeGraphAnimation::OnExit(
    STATE_ANEMATION_DATA* data,
    int nextState)
{
}

void StateFadeGraphAnimation::Finalize(
    STATE_ANEMATION_DATA* data)
{
}

void StateFadeGraphAnimation::Update(
    STATE_ANEMATION_DATA* data)
{
    FadeProcess(
        data->StateOneAnimationData);
}

bool StateFadeGraphAnimation::CheckSimilarModelType(
    MODEL_TYPE modelType)
{
    return false;
}


/*----------*/
/*ÅyDOTweenÅz*/
/*----------*/

void StateDOTweenAnimation::OnEnter(
    STATE_ANEMATION_DATA* data,
    int preState)
{
}

void StateDOTweenAnimation::OnExit(
    STATE_ANEMATION_DATA* data,
    int nextState)
{
}

void StateDOTweenAnimation::Finalize(
    STATE_ANEMATION_DATA* data)
{
}

void StateDOTweenAnimation::Update(
    STATE_ANEMATION_DATA* data)
{
}

bool StateDOTweenAnimation::CheckSimilarModelType(
    MODEL_TYPE modelType)
{
    return false;
}