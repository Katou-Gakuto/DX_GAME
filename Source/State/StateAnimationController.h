// #pragma once

// #include "TimeData.h"

// #include "AnimationBase.h"
// #include "StateBase.h"

// /*--------------------*/
// /*     【ベースアニメーションコントローラーステート】
// /*--------------------*/

// /*----------*/
// /*【アニメションコントローラーステート共通処理用】
// /*----------*/
// class StateAnimationControllerProcess
// {
// protected:
// 	// 終了時間
// 	TIME_DATA mstEndTime;

// protected:
// 	StateAnimationControllerProcess();

// 	/*終了時間設定*/
// 	void SetEndTime(AnimationBase* animation, ANIMATION_TYPE state, int addEndTime);

// 	/*終了時間確認(一定時間経っていれば「true」を返す)*/
// 	bool ChackEndTime();

// 	/*変更確認*/
// 	ANIMATION_TYPE ChangeCheck(AnimationBase* animation, ANIMATION_TYPE nextState);
// };

// /*----------*/
// /*【待機アニメションコントローラーステート】
// /*----------*/
// class StateIdleAnimationController : public IStateAnimationController, public StateAnimationControllerProcess
// {
// public:
// 	// FIXME: コンストラクタでステート変更条件を渡せます
// 	StateIdleAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_TYPE, void>> stateChangeCriterias);
	
// 	/// <summary>この状態に入った時の処理</summary>
// 	virtual void OnEnter(AnimationBase* modelsController, ANIMATION_TYPE oldState) override;

// 	/// <summary>この状態を出る時の処理</summary>
// 	virtual void OnExit(AnimationBase* modelsController, ANIMATION_TYPE newState) override;

// 	/// <summary>ステート変更確認</summary>
// 	virtual ANIMATION_TYPE CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState) override;
// };

// /*----------*/
// /*【移動アニメションコントローラーステート】
// /*----------*/
// class StateMoveAnimationController : public IStateAnimationController, public StateAnimationControllerProcess
// {
// public:
// 	// FIXME: コンストラクタでステート変更条件を渡せます
// 	StateMoveAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_TYPE, void>> stateChangeCriterias);
	
// 	/// <summary>この状態に入った時の処理</summary>
// 	virtual void OnEnter(AnimationBase* modelsController, ANIMATION_TYPE oldState) override;

// 	/// <summary>この状態を出る時の処理</summary>
// 	virtual void OnExit(AnimationBase* modelsController, ANIMATION_TYPE newState) override;

// 	/// <summary>ステート変更確認</summary>
// 	virtual ANIMATION_TYPE CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState) override;
// };

// /*----------*/
// /*【攻撃開始アニメションコントローラーステート】
// /*----------*/
// class StateAttackInAnimationController : public IStateAnimationController, public StateAnimationControllerProcess
// {
// public:
// 	// FIXME: コンストラクタでステート変更条件を渡せます
// 	StateAttackInAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_TYPE, void>> stateChangeCriterias);
	
// 	/// <summary>この状態に入った時の処理</summary>
// 	virtual void OnEnter(AnimationBase* modelsController, ANIMATION_TYPE oldState) override;

// 	/// <summary>この状態を出る時の処理</summary>
// 	virtual void OnExit(AnimationBase* modelsController, ANIMATION_TYPE newState) override;

// 	/// <summary>ステート変更確認</summary>
// 	virtual ANIMATION_TYPE CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState) override;

// 	/// <summary>同分類の種類かを確認する</summary>
// 	virtual bool CheckSameType(ANIMATION_TYPE animationType) override;
// };

// /*----------*/
// /*【攻撃アニメションコントローラーステート】
// /*----------*/
// class StateAttackAnimationController : public IStateAnimationController, public StateAnimationControllerProcess
// {
// public:
// 	// FIXME: コンストラクタでステート変更条件を渡せます
// 	StateAttackAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_TYPE, void>> stateChangeCriterias);
	
// 	/// <summary>この状態に入った時の処理</summary>
// 	virtual void OnEnter(AnimationBase* modelsController, ANIMATION_TYPE oldState) override;

// 	/// <summary>この状態を出る時の処理</summary>
// 	virtual void OnExit(AnimationBase* modelsController, ANIMATION_TYPE newState) override;

// 	/// <summary>ステート変更確認</summary>
// 	virtual ANIMATION_TYPE CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState) override;

// 	/// <summary>同分類の種類かを確認する</summary>
// 	virtual bool CheckSameType(ANIMATION_TYPE animationType) override;
// };

// /*----------*/
// /*【攻撃終了アニメションコントローラーステート】
// /*----------*/
// class StateAttackOutAnimationController : public IStateAnimationController, public StateAnimationControllerProcess
// {
// public:
// 	// FIXME: コンストラクタでステート変更条件を渡せます
// 	StateAttackOutAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_TYPE, void>> stateChangeCriterias);
	
// 	/// <summary>この状態に入った時の処理</summary>
// 	virtual void OnEnter(AnimationBase* modelsController, ANIMATION_TYPE oldState) override;

// 	/// <summary>この状態を出る時の処理</summary>
// 	virtual void OnExit(AnimationBase* modelsController, ANIMATION_TYPE newState) override;

// 	/// <summary>ステート変更確認</summary>
// 	virtual ANIMATION_TYPE CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState) override;

// 	/// <summary>同分類の種類かを確認する</summary>
// 	virtual bool CheckSameType(ANIMATION_TYPE animationType) override;
// };

// /*----------*/
// /*【2D移動アニメーションコントローラーステート】
// /*----------*/
// class State2DMoveAnimationController : public IStateAnimationController, public StateAnimationControllerProcess
// {
// public:
// 	// FIXME: コンストラクタでステート変更条件を渡せます
// 	State2DMoveAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_TYPE, void>> stateChangeCriterias);
	
// 	/// <summary>この状態に入った時の処理</summary>
// 	virtual void OnEnter(AnimationBase* modelsController, ANIMATION_TYPE oldState) override;

// 	/// <summary>この状態を出る時の処理</summary>
// 	virtual void OnExit(AnimationBase* modelsController, ANIMATION_TYPE newState) override;

// 	/// <summary>ステート変更確認</summary>
// 	virtual ANIMATION_TYPE CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState) override;
// };

// /*----------------------------------------------------*/
// /*【フェードアウトアニメーションコントローラーステート】*/
// /*----------------------------------------------------*/
// class StateFadeOutAnimationController : public IStateAnimationController, public StateAnimationControllerProcess
// {
// public:
// 	// FIXME: コンストラクタでステート変更条件を渡せます
// 	StateFadeOutAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_TYPE, void>> stateChangeCriterias);
	
// 	/// <summary>この状態に入った時の処理</summary>
// 	virtual void OnEnter(AnimationBase* modelsController, ANIMATION_TYPE oldState) override;

// 	/// <summary>この状態を出る時の処理</summary>
// 	virtual void OnExit(AnimationBase* modelsController, ANIMATION_TYPE newState) override;

// 	/// <summary>ステート変更確認</summary>
// 	virtual ANIMATION_TYPE CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState) override;
// };

// /*----------------------------------------------------*/
// /*【フェードインアニメーションコントローラーステート】*/
// /*----------------------------------------------------*/
// class StateFadeInAnimationController : public IStateAnimationController, public StateAnimationControllerProcess
// {
// public:
// 	// FIXME: コンストラクタでステート変更条件を渡せます
// 	StateFadeInAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_TYPE, void>> stateChangeCriterias);
	
// 	/// <summary>この状態に入った時の処理</summary>
// 	virtual void OnEnter(AnimationBase* modelsController, ANIMATION_TYPE oldState) override;

// 	/// <summary>この状態を出る時の処理</summary>
// 	virtual void OnExit(AnimationBase* modelsController, ANIMATION_TYPE newState) override;

// 	/// <summary>ステート変更確認</summary>
// 	virtual ANIMATION_TYPE CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState) override;
// };

// /*--------------------*/
// /*     【派生アニメーションコントローラーステート】
// /*--------------------*/

// /*----------*/
// /*【攻撃中終了アニメーションステート】
// /*----------*/
// class StateAttackEndAnimationController : public StateAttackAnimationController
// {
// public:
// 	// FIXME: コンストラクタでステート変更条件を渡せます
// 	StateAttackEndAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_TYPE, void>> stateChangeCriterias);

// 	/// <summary>ステート変更確認</summary>
// 	virtual ANIMATION_TYPE CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState) override;
// };

// /*----------*/
// /*【攻撃停止アニメーションステート】
// /*----------*/
// class StateAttackOutStopAnimationController : public StateAttackOutAnimationController
// {
// public:
// 	// FIXME: コンストラクタでステート変更条件を渡せます
// 	StateAttackOutStopAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_TYPE, void>> stateChangeCriterias);

// 	/// <summary>ステート変更確認</summary>
// 	virtual ANIMATION_TYPE CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState) override;
// };

// /*----------------------------------------------------------------通常攻撃------------------------------------------------------------------*/
// /*----------*/
// /*【通常攻撃開始アニメションコントローラーステート】
// /*----------*/
// class StateNormalAttackInAnimationController : public StateAttackInAnimationController
// {
// public:
// 	// FIXME: コンストラクタでステート変更条件を渡せます
// 	StateNormalAttackInAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_TYPE, void>> stateChangeCriterias);

// 	/// <summary>ステート変更確認</summary>
// 	virtual ANIMATION_TYPE CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState) override;
// };

// /*----------*/
// /*【通常攻撃終了アニメションコントローラーステート】
// /*----------*/
// class StateNormalAttackOutAnimationController : public StateAttackOutAnimationController
// {
// public:
// 	// FIXME: コンストラクタでステート変更条件を渡せます
// 	StateNormalAttackOutAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_TYPE, void>> stateChangeCriterias);

// 	/// <summary>ステート変更確認</summary>
// 	virtual ANIMATION_TYPE CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState) override;
// };
// /*------------------------------------------------------------------------------------------------------------------------------------------*/


// /*----------------------------------------------------------------特殊攻撃------------------------------------------------------------------*/
// /*----------*/
// /*【特殊攻撃開始アニメションコントローラーステート】
// /*----------*/
// class StateSpceialAttackInAnimationController : public StateAttackInAnimationController
// {
// public:
// 	// FIXME: コンストラクタでステート変更条件を渡せます
// 	StateSpceialAttackInAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_TYPE, void>> stateChangeCriterias);

// 	/// <summary>ステート変更確認</summary>
// 	virtual ANIMATION_TYPE CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState) override;
// };

// /*----------*/
// /*【特殊攻撃アニメションコントローラーステート】
// /*----------*/
// class StateSpceialAttackAnimationController : public StateAttackAnimationController
// {
// public:
// 	// FIXME: コンストラクタでステート変更条件を渡せます
// 	StateSpceialAttackAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_TYPE, void>> stateChangeCriterias);

// 	/// <summary>ステート変更確認</summary>
// 	virtual ANIMATION_TYPE CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState) override;
// };

// /*----------*/
// /*【特殊攻撃終了アニメションコントローラーステート】
// /*----------*/
// class StateSpceialAttackOutAnimationController : public StateAttackOutAnimationController
// {
// public:
// 	// FIXME: コンストラクタでステート変更条件を渡せます
// 	StateSpceialAttackOutAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_TYPE, void>> stateChangeCriterias);

// 	/// <summary>ステート変更確認</summary>
// 	virtual ANIMATION_TYPE CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState) override;
// };
// /*------------------------------------------------------------------------------------------------------------------------------------------*/


// /*----------------------------------------------------------------ジャンプ攻撃------------------------------------------------------------------*/
// /*----------*/
// /*【ジャンプ攻撃開始アニメションコントローラーステート】
// /*----------*/
// class StateJumpAttackInAnimationController : public StateAttackInAnimationController
// {
// public:
// 	// FIXME: コンストラクタでステート変更条件を渡せます
// 	StateJumpAttackInAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_TYPE, void>> stateChangeCriterias);

// 	/// <summary>ステート変更確認</summary>
// 	virtual ANIMATION_TYPE CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState) override;
// };

// /*----------*/
// /*【ジャンプ攻撃アニメションコントローラーステート】
// /*----------*/
// class StateJumpAttackAnimationController : public StateAttackAnimationController
// {
// public:
// 	// FIXME: コンストラクタでステート変更条件を渡せます
// 	StateJumpAttackAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_TYPE, void>> stateChangeCriterias);

// 	/// <summary>ステート変更確認</summary>
// 	virtual ANIMATION_TYPE CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState) override;
// };

// /*----------*/
// /*【ジャンプ攻撃終了アニメションコントローラーステート】
// /*----------*/
// class StateJumpAttackOutAnimationController : public StateAttackOutAnimationController
// {
// public:
// 	// FIXME: コンストラクタでステート変更条件を渡せます
// 	StateJumpAttackOutAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_TYPE, void>> stateChangeCriterias);

// 	/// <summary>ステート変更確認</summary>
// 	virtual ANIMATION_TYPE CheckState(AnimationBase* modelsController, ANIMATION_TYPE nextState) override;
// };
// /*------------------------------------------------------------------------------------------------------------------------------------------*/


// /*----------*/
// /*【攻撃専用待機アニメーションステート】
// /*----------*/
// class StateAttackIdleAnimationController : public StateIdleAnimationController
// {
// public:
// 	// FIXME: コンストラクタでステート変更条件を渡せます
// 	StateAttackIdleAnimationController(std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_TYPE, void>> stateChangeCriterias);

// 	virtual ANIMATION_TYPE CheckState(AnimationBase* animation, ANIMATION_TYPE nextState) override;
// };