#pragma once
#include "AnimationBase.h"
#include "StateBase.h"

/*----------*/
/*【アニメションコントローラーステート共通処理用】
/*----------*/
class StateAnimationControllerProcess
{
protected:
};

/*----------*/
/*【待機アニメションコントローラーステート】
/*----------*/
class StateIdleAnimationController : public IStateAnimationController, public StateAnimationControllerProcess
{
public:
    StateIdleAnimationController();
	
	/// <summary>この状態に入った時の処理</summary>
	virtual void OnEnter(AnimationBase* modelsController, ANIMATION_TYPE oldState) override;

	/// <summary>この状態を出る時の処理</summary>
	virtual void OnExit(AnimationBase* modelsController, ANIMATION_TYPE newState) override;

	/// <summary>ステート変更確認</summary>
	virtual ANIMATION_TYPE CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState) override;
};

/*----------*/
/*【移動アニメションコントローラーステート】
/*----------*/
class StateMoveAnimationController : public IStateAnimationController, public StateAnimationControllerProcess
{
public:
    StateMoveAnimationController();
	
	/// <summary>この状態に入った時の処理</summary>
	virtual void OnEnter(AnimationBase* modelsController, ANIMATION_TYPE oldState) override;

	/// <summary>この状態を出る時の処理</summary>
	virtual void OnExit(AnimationBase* modelsController, ANIMATION_TYPE newState) override;

	/// <summary>ステート変更確認</summary>
	virtual ANIMATION_TYPE CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState) override;
};

/*----------*/
/*【攻撃アニメションコントローラーステート】
/*----------*/
class StateAttackAnimationController : public IStateAnimationController, public StateAnimationControllerProcess
{
private:
	int mnEndTime;
public:
    StateAttackAnimationController();
	
	/// <summary>この状態に入った時の処理</summary>
	virtual void OnEnter(AnimationBase* modelsController, ANIMATION_TYPE oldState) override;

	/// <summary>この状態を出る時の処理</summary>
	virtual void OnExit(AnimationBase* modelsController, ANIMATION_TYPE newState) override;

	/// <summary>ステート変更確認</summary>
	virtual ANIMATION_TYPE CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState) override;
};