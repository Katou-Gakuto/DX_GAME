#pragma once
#include "AnimationBase.h"
#include "StateBase.h"

/*--------------------*/
/*     【ベースアニメーションコントローラーステート】
/*--------------------*/

/*----------*/
/*【アニメションコントローラーステート共通処理用】
/*----------*/
class StateAnimationControllerProcess
{
protected:
	// 終了時間
	int mnEndTime;
protected:
	StateAnimationControllerProcess();

	/*終了時間設定*/
	void SetEndTime(AnimationBase* animation, ANIMATION_TYPE state);

	/*終了時間確認(一定時間経っていれば「true」を返す)*/
	bool ChackEndTime();

	/*変更確認*/
	ANIMATION_TYPE ChangeCheck(AnimationBase* animation, ANIMATION_TYPE nextState);
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
public:
    StateAttackAnimationController();
	
	/// <summary>この状態に入った時の処理</summary>
	virtual void OnEnter(AnimationBase* modelsController, ANIMATION_TYPE oldState) override;

	/// <summary>この状態を出る時の処理</summary>
	virtual void OnExit(AnimationBase* modelsController, ANIMATION_TYPE newState) override;

	/// <summary>ステート変更確認</summary>
	virtual ANIMATION_TYPE CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState) override;
};

/*----------*/
/*【攻撃開始アニメションコントローラーステート】
/*----------*/
class StateAttackInAnimationController : public IStateAnimationController, public StateAnimationControllerProcess
{
public:
    StateAttackInAnimationController();
	
	/// <summary>この状態に入った時の処理</summary>
	virtual void OnEnter(AnimationBase* modelsController, ANIMATION_TYPE oldState) override;

	/// <summary>この状態を出る時の処理</summary>
	virtual void OnExit(AnimationBase* modelsController, ANIMATION_TYPE newState) override;

	/// <summary>ステート変更確認</summary>
	virtual ANIMATION_TYPE CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState) override;
};

/*----------*/
/*【攻撃終了アニメションコントローラーステート】
/*----------*/
class StateAttackOutAnimationController : public IStateAnimationController, public StateAnimationControllerProcess
{
public:
	StateAttackOutAnimationController();
	
	/// <summary>この状態に入った時の処理</summary>
	virtual void OnEnter(AnimationBase* modelsController, ANIMATION_TYPE oldState) override;

	/// <summary>この状態を出る時の処理</summary>
	virtual void OnExit(AnimationBase* modelsController, ANIMATION_TYPE newState) override;

	/// <summary>ステート変更確認</summary>
	virtual ANIMATION_TYPE CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState) override;
};



/*--------------------*/
/*     【派生アニメーションコントローラーステート】
/*--------------------*/

class StateAttackMiddleAnimationController : public StateAttackAnimationController
{
public:
	StateAttackMiddleAnimationController();

	/// <summary>ステート変更確認</summary>
	virtual ANIMATION_TYPE CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState) override;
};