#pragma once
#include <map>

#include "AnimationData.h"

class IStateAnimation;

class AnimationStateManager
{
private:
	// アニメーションステート生成情報
	std::map<int, ANIMATION_STATE_INFO> mstAnimationStateInfos;
public:

	/// <summary>アニメーションステート取得</summary>
	/// <param name="key">アニメーションのキー</param>
	/// <returns>keyがサイズを超えていたらnullを返す</returns>
	inline IStateAnimation* GetAnimationState(int key) { if (mstAnimationStateInfos.find(key) == mstAnimationStateInfos.end()) { return nullptr; } return mstAnimationStateInfos[key].AnimationState; }

	/// <summary>アニメーション情報入力</summary>
	/// <param name="animationStateInfo">アニメーション生成情報</param>
	/// <returns>アニメーション情報が入っているkeyを返す</returns>
	int AnimationInfoEntry(ANIMATION_STATE_INFO animationStateInfo);

	/// <summary>アニメーション情報参照数減らす</summary>
	/// <param name="key">アニメーションのキー</param>
	inline void ReduceAnimationStateInfo(int key) { if (mstAnimationStateInfos.find(key) == mstAnimationStateInfos.end()) { return; } mstAnimationStateInfos[key].ReferenceNumber--; if (mstAnimationStateInfos[key].ReferenceNumber == 0) { DeleteAnimationStateInfo(key); } }

private:
	/// <summary>アニメーション情報削除</summary>
	/// <param name="key">アニメーション情報インデックス</param>
	void DeleteAnimationStateInfo(int key);
};