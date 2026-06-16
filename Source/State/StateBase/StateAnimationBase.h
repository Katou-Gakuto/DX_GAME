#pragma once
#include <vector>

#include "StateData.h"
#include "AnimationData.h"

#include "StateBase.h"

enum class MODEL_TYPE;
enum class CAMERA_MODE;
enum class DOT_WEEN_TYPE;
enum class SCENE;

class AnimationBase;

/*----------*/
/*【アニメーションステートベース】
/*----------*/
class IStateAnimation : public StateBase<int, STATE_ANEMATION_DATA>
{
protected:
	// アニメーションステート設定情報ナンバー
	int mnAnimationStateSettingInfoNumber;
// 	// モデルベース
// 	ModelBase* mpModelBase;


public:
	IStateAnimation(int stateNumber, std::vector<STATE_CHANGE_CRITERIA_DATA<int, STATE_ANEMATION_DATA>> stateChangeCriterias)
	: StateBase(stateNumber, stateChangeCriterias)
	{
	}
	virtual ~IStateAnimation() = default;

	// /// <summary>この状態に入った時の処理</summary>
	// virtual void OnEnter(AnimationBase* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, MODEL_TYPE oldModelType) = 0;
	// /// <summary>この状態を出る時の処理</summary>
	// virtual void OnExit(AnimationBase* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, MODEL_TYPE newModelType) = 0;
	
	/// <summary>初期化</summary>
	virtual void Initilize(AnimationBase* animation){}

	/// <summary>終了</summary>
	//virtual void Finalize(AnimationBase* animation, AnimationDatas *nowAnimationData) = 0;

	/// <summary>更新</summary>
	virtual void Update(AnimationBase* animation, OneAnimationData *nowAnimationData) = 0;

	/// <summary>モデル種類が同類なら「true」を返す</summary>
	/// <param name="modelType">モデル種類</param>
	/// <returns>同類か</returns>
	virtual bool CheckSimilarModelType(MODEL_TYPE modelType) = 0;

	/// <summary>アニメーションステート設定情報ナンバー取得</summary>
	int GetAnimationStateSettingInfoNumber() { return mnAnimationStateSettingInfoNumber; }
	/// <summary>アニメーションステート設定情報ナンバー設定</summary>
	void SetAnimationStateSettingInfoNumber(int infoNumber) { mnAnimationStateSettingInfoNumber = infoNumber; }

	// /// <summary>モデル設定</summary>
	// /// <param name="modelBase">モデル</param>
	// void SetModelBase(ModelBase* modelBase);
};