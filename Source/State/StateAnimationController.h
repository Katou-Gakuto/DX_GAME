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

	/// <summary>同分類の種類かを確認する</summary>
	virtual bool CheckSameType(ANIMATION_TYPE animationType) override;
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

	/// <summary>同分類の種類かを確認する</summary>
	virtual bool CheckSameType(ANIMATION_TYPE animationType) override;
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

	/// <summary>同分類の種類かを確認する</summary>
	virtual bool CheckSameType(ANIMATION_TYPE animationType) override;
};

/*----------*/
/*【2D移動アニメーションコントローラーステート】
/*----------*/
class State2DMoveAnimationController : public IStateAnimationController, public StateAnimationControllerProcess
{
public:
	State2DMoveAnimationController();
	
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

/*----------*/
/*【通常攻撃開始アニメションコントローラーステート】
/*----------*/
class StateNormalAttackInAnimationController : public StateAttackInAnimationController
{
public:
	StateNormalAttackInAnimationController();

	/// <summary>ステート変更確認</summary>
	virtual ANIMATION_TYPE CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState) override;
};

/*----------*/
/*【通常攻撃終了アニメションコントローラーステート】
/*----------*/
class StateNormalAttackOutAnimationController : public StateAttackOutAnimationController
{
public:
	StateNormalAttackOutAnimationController();

	/// <summary>ステート変更確認</summary>
	virtual ANIMATION_TYPE CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState) override;
};


/*----------*/
/*【攻撃中アニメーションステート】
/*----------*/
class StateAttackMiddleAnimationController : public StateAttackAnimationController
{
public:
	StateAttackMiddleAnimationController();

	/// <summary>ステート変更確認</summary>
	virtual ANIMATION_TYPE CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState) override;
};

/*----------*/
/*【攻撃専用待機アニメーションステート】
/*----------*/
class StateAttackIdleAnimationController : public StateIdleAnimationController
{
public:
	StateAttackIdleAnimationController();

	virtual ANIMATION_TYPE CheckState(AnimationBase* animation, ANIMATION_TYPE nextState) override;
};


/*----------*/
/*【攻撃終了アニメーションステート】
/*----------*/
class StateAttackEndAnimationController : public StateAttackOutAnimationController
{
public:
	StateAttackEndAnimationController();

	/// <summary>ステート変更確認</summary>
	virtual ANIMATION_TYPE CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState) override;
};