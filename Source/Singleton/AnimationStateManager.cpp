#include <map>

#include "AnimationData.h"

#include "AnimationStateManager.h"
#include "UtilCalc.h"

AnimationStateManager::AnimationStateManager()
: mstAnimationStateInfos()
{
}
AnimationStateManager::~AnimationStateManager()
{
}

// 終了処理
void AnimationStateManager::Finalize()
{
	for (auto& animationStateInfos : mstAnimationStateInfos)
	{
		if (animationStateInfos.second.AnimationState != nullptr)
		{
			delete animationStateInfos.second.AnimationState;
		}
	}
	mstAnimationStateInfos.clear();
}

// アニメーション情報入力
int AnimationStateManager::AnimationInfoEntry(ANIMATION_STATE_INFO animationStateInfo)
{

	for (auto& generatedAnimationStateInfo : mstAnimationStateInfos)
	{
		if (generatedAnimationStateInfo.second == animationStateInfo)
		{
			generatedAnimationStateInfo.second.ReferenceNumber++;
			return generatedAnimationStateInfo.second.MyKey;
		}
	}

	int key = 0;
	while (true)
	{
		if (key == UtilCalc::IntMax)
		{
			break;
		}
		if (mstAnimationStateInfos.find(key) == mstAnimationStateInfos.end())
		{
			// TODO: アニメーション種類変更
			switch (animationStateInfo.AnimationType)
			{
			case ANIMATION_TYPE::ATTACK:
				//animationStateInfo.AnimationState = new;
				break;
			}
			animationStateInfo.MyKey = key;
			animationStateInfo.ReferenceNumber = 1;
			mstAnimationStateInfos[key] = animationStateInfo;
		}

		key++;
	}
	return -1;
}

// アニメーション情報削除
void AnimationStateManager::DeleteAnimationStateInfo(int key)
{
	auto& animationStateInfoIt = mstAnimationStateInfos.find(key);
	if (animationStateInfoIt == mstAnimationStateInfos.end())
	{
		return;
	}

	delete mstAnimationStateInfos[key].AnimationState;
	mstAnimationStateInfos.erase(animationStateInfoIt);
}