
/*----------*/
/*【アニメーション有限状態マシン】
/*----------*/
FSMAnimation::FSMAnimation()
: FSMBase()
{
}

// // 初期化
// void FSMAnimation::Initilize(AnimationBase* animation)
// {
// 	mCurrentState = 0;

// 	// 新しいStateの開始処理
// 	for (int i = 0; i < mmAnimationStates.size(); i++)
// 	{
// 		NewStateSetting(i, animation, MODEL_TYPE::NONE);
// 	}
// }

// 終了
void FSMAnimation::Finalize(AnimationBase* animation)
{
	// for (int i = 0; i < mmAnimationStates.size(); i++)
	// {
	// 	for (auto animationState : mmAnimationStates[i])
	// 	{
	// 		animationState.second->Finalize(animation, animation->GetAnimationDatas()[i]);
	// 		delete animationState.second;
	// 	}
	// }
	// mmAnimationStates.clear();
}

// // サブ状態マップのサイズを増やす
// void FSMAnimation::IncreaseAnimationStateSize(int size)
// {
// 	mmAnimationStates.resize(size);
// }

// // アニメーションステート情報設定
// void FSMAnimation::SetAnimationStateDatas(int animationStateIndex, std::map<MODEL_TYPE, IStateAnimation*> animationStateMap)
// {
// 	mmAnimationStates[animationStateIndex] = animationStateMap;
// }

// 更新
void FSMAnimation::Update(AnimationBase* animation, std::vector<AnimationDatas*> animationDatas)
{
	// 古いアニメーション種類を一時的に保存しておく
	ANIMATION_TYPE oldAnimationState = mCurrentState;

	// アニメーションが変更されたか確認
	mnNextState = mmStateMap[mCurrentState]->CheckState(animation, mnNextState);
	if (mnNextState != mCurrentState)
	{
		mmStateMap[mCurrentState]->OnExit(animation, mnNextState);

		mCurrentState = mnNextState;
		mmStateMap[mCurrentState]->OnEnter(animation, oldAnimationState);
	}
	// TODO: この1行なくせるようにした(UIの方になるになる)
	mnNextState = ANIMATION_TYPE::IDLE;

	// 変更処理
	for (int i = 0; i < mmAnimationStates.size(); i++)
	{
		// モデル取得
//		ModelBase* model = animation->GetModelsController()->GetModelList()[i];

		// ステート変更
		if (mCurrentState != oldAnimationState)
		{
			ChangeState(i, animation, oldAnimationState);
		}

		// 更新
		GetAnimationState(i, animation, mCurrentState)->Update(animation, &animationDatas[i]->animDatas[mCurrentState]);
	}
}

// 新しいステートを設定する
void FSMAnimation::NewStateSetting(int animationIndex, AnimationBase* animation, MODEL_TYPE oldModelType)
{
	GetAnimationState(animationIndex, animation, mCurrentState)->OnEnter(animation, &animation->GetAnimationDatas()[animationIndex]->animDatas[mCurrentState], animation->GetAnimationDatas()[animationIndex], oldModelType);
}

// 次のステートが現在のステートと違うならステート変更処理をする
void FSMAnimation::ChangeState(int animationStateIndex, AnimationBase* animation, ANIMATION_TYPE oldAnimationType)
{
	AnimationDatas* animationDatas = animation->GetAnimationDatas()[animationStateIndex];

	// 現在のState終了処理
	GetAnimationState(animationStateIndex, animation, oldAnimationType)->OnExit(animation, &animationDatas->animDatas[oldAnimationType], animationDatas, animationDatas->animDatas[mCurrentState].modelType);

	// 新しいState設定
	NewStateSetting(animationStateIndex, animation, animationDatas->animDatas[oldAnimationType].modelType);
}

// 現在のステート取得
IStateAnimation* FSMAnimation::GetAnimationState(int index, AnimationBase* animation, ANIMATION_TYPE animationType)
{
	return mmAnimationStates[index][animation->GetAnimationDatas()[index]->animDatas[animationType].modelType];
}