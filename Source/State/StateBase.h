#pragma once
#include <map>
#include <vector>

#include "StateEnum.h"
#include "AnimationData.h"
#include "CameraData.h"
#include "StateData.h"

#ifdef _DEBUG
#include "Master.h"
#include "EndManager.h"
#include "DebugLogs/DebugLog.h"
#endif

enum class MODEL_TYPE;
enum class CAMERA_MODE;
enum class DOT_WEEN_TYPE;
enum class SCENE;

struct AnimationStateData;
struct DOT_WEEN_DATA;

class AnimationBase;
class CameraManager;
class CharacterBase;
class MapManager;
class ModelBase;
class SceneManager;
class TargetManager;
class UIBase;

/*------------------*/
/*【ステートベース】*/
/*------------------*/
template<typename number, typename conditionData>
class StateBase
{
protected:
	// ステートナンバー
	number mStateNumber = (number) - 1;

	// ステート変更条件
	std::vector<STATE_CHANGE_CRITERIA_DATA<number, conditionData>> mfpStateChangeCriterias;
public:
	StateBase(number stateNumber, std::vector<STATE_CHANGE_CRITERIA_DATA<number, conditionData>> stateChangeCriterias)
	: mStateNumber(stateNumber)
	, mfpStateChangeCriterias(stateChangeCriterias)
	{
	}

	virtual ~StateBase() = default;

	/// <summary>ステート取得</summary>
	inline number GetStateNumber() const { return mStateNumber; }

	/// <summary>ステート設定</summary>
	/// <param name="stateNumber">設定ステートナンバー</param>
	inline void SetStatenumber(number stateNumber) { mStateNumber = stateNumber; }

	// TODOｆｓｍbaseでやる
	/// <summary>次のステートを取得する</summary>
	inline number GetNextState()
	{
		for (auto& stateChangeCriteriaData : mfpStateChangeCriterias)
		{
#ifdef _DEBUG
			if (stateChangeCriteriaData.ChangeFlag == nullptr)
			{
				Master::mpEndManager.SetEndFlag(true, END_FLAG_NUMBER::STATE_NULL_FUNCTION_FLAG);
				DEBUG::SaveText("ステート未設定", DEBUG::DEBUG_MAP_TYPE::DEBUG_FAILURE_LOG);
				return mStateNumber;
			}
#endif
			if (stateChangeCriteriaData.ChangeFlag())
			{
				if (mStateNumber == stateChangeCriteriaData.ChangeNumber)
				{
					return;
				}
				return stateChangeCriteriaData.ChangeNumber;
			}
		}
	}
};

/*------------------------*/
/*【カメラステートベース】*/
/*------------------------*/
class IStateCamera : public StateBase<CAMERA_MODE, void>
{
protected:
	// カメラ1フレーム移動量
	const float CAMERA_ONE_FRAME_AMOUNT = 3.0f;

public:
	IStateCamera(CAMERA_MODE stateNumber, std::vector<STATE_CHANGE_CRITERIA_DATA<CAMERA_MODE, void>> stateChangeCriterias)
	: StateBase<CAMERA_MODE, void>(stateNumber, stateChangeCriterias)
	{
	}
	virtual ~IStateCamera() = default;

	/*この状態に入った時の処理*/
	virtual void OnEnter(CameraManager* cameraManager, CameraData cameraData, int& preThreeDFlag) = 0;
	/*この状態を出る時の処理*/
	virtual void OnExit(CameraManager* cameraManager, CameraData cameraData) = 0;

	/*初期化*/
	virtual void Initilize(CameraManager* cameraManager, CameraData cameraData) = 0;

	/*更新*/
	virtual void Update(CameraManager* cameraManager, CameraData cameraData) = 0;

	/*描画*/
	virtual void Draw(CameraManager* cameraManager, CameraData cameraData) = 0;

protected:
	/*カメラの共通設定をする*/
	void CommonSetCamera(CameraData cameraData, int& preThreeDFlag);

	/*カメラポジション設置*/
	void SetCameraPos(VECTOR cameraPos, VECTOR cameraLookPos);
};

/*------------------------------*/
/*【キャラクターステートベース】*/
/*------------------------------*/
class IStateCharacter : public StateBase<STATE_TYPE_CHARACTER, void>
{
protected:
	// 共通キャラクターステート
	enum COMMON_CHARACTER_STATE
	{
		IDEL_COMMON_CHARACTER_STATE = 0,	// 通常
		MOVE_COMMON_CHARACTER_STATE,	// 移動
		FLINCH_COMMON_CHARACTER_STATE,	// 怯み
		AVOID_COMMON_CHARACTER_STATE,	// 回避
		GUARD_COMMON_CHARACTER_STATE,	// ガード
		FALL_DOWN_COMMON_CHARACTER_STATE,	// 倒れる

		ATTACK_COMMON_CHARACTER_STATE,	// 攻撃
		NORMAL_ATTACK_COMMON_CHARACTER_STATE,	// 通常攻撃
		SPCEIAL_ONE_ATTACK_COMMON_CHARACTER_STATE,	// 特殊攻撃 1
		SPCEIAL_TWO_ATTACK_COMMON_CHARACTER_STATE,	// 特殊攻撃 1

		COMMON_CHARACTER_STATE_MAX	// 共通キャラクターステート最大数
	};
	// INPROGRESS: ステート条件金曜過ぎたら変更

public:
	IStateCharacter(STATE_TYPE_CHARACTER stateNumber, std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_CHARACTER, void>> stateChangeCriterias)
	: StateBase<STATE_TYPE_CHARACTER, void>(stateNumber, stateChangeCriterias)
	{
	}
	virtual ~IStateCharacter() = default;

	/// <summary>終了</summary>
	virtual void Finalize(CharacterBase* character) {}

	/*この状態に入った時の処理*/
	virtual void OnEnter(CharacterBase* character) = 0;
	/*この状態を出る時の処理*/
	virtual void OnExit(CharacterBase* character) = 0;

	/*ステート変更確認*/
	virtual STATE_TYPE_CHARACTER StateCheck(CharacterBase* character) = 0;
	/*更新*/
	virtual void Update(CharacterBase* character) = 0;
	/*最終更新*/
	virtual void LastUpdate(CharacterBase* character) = 0;

	/*描画*/
	virtual void Draw(CharacterBase* character) = 0;

	/*死亡*/
	virtual void Death(CharacterBase* character) = 0;
};

/*----------*/
/*【アニメーションステートベース】
/*----------*/
class IStateAnimation : public StateBase<MODEL_TYPE, void>
{
protected:
	// モデルベース
	ModelBase* mpModelBase;

public:
	IStateAnimation(MODEL_TYPE stateNumber, std::vector<STATE_CHANGE_CRITERIA_DATA<MODEL_TYPE, void>> stateChangeCriterias)
	: StateBase<MODEL_TYPE, void>(stateNumber, stateChangeCriterias)
	{
	}
	virtual ~IStateAnimation() = default;

	/// <summary>この状態に入った時の処理</summary>
	virtual void OnEnter(AnimationBase* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, MODEL_TYPE oldModelType) = 0;
	/// <summary>この状態を出る時の処理</summary>
	virtual void OnExit(AnimationBase* animation, OneAnimationData *nowAnimationData, AnimationDatas* animationDatas, MODEL_TYPE newModelType) = 0;
	
	/// <summary>終了</summary>
	virtual void Finalize(AnimationBase* animation, AnimationDatas *nowAnimationData) = 0;

	/// <summary>更新</summary>
	virtual void Update(AnimationBase* animation, OneAnimationData *nowAnimationData) = 0;

	/// <summary>モデル種類が同類なら「true」を返す</summary>
	/// <param name="modelType">モデル種類</param>
	/// <returns>同類か</returns>
	virtual bool CheckSimilarModelType(MODEL_TYPE modelType) = 0;

	/// <summary>モデル設定</summary>
	/// <param name="modelBase">モデル</param>
	void SetModelBase(ModelBase* modelBase);
};

/*----------*/
/*【アニメション操作ステートベース】
/*----------*/
class IStateAnimationController : public StateBase<ANIMATION_TYPE, void>
{
protected:
	// 追加終了時間
	int mnAddEndTime;
	
public:
	IStateAnimationController(ANIMATION_TYPE stateNumber, std::vector<STATE_CHANGE_CRITERIA_DATA<ANIMATION_TYPE, void>> stateChangeCriterias)
	: StateBase<ANIMATION_TYPE, void>(stateNumber, stateChangeCriterias)
	{
	}
	virtual ~IStateAnimationController() = default;
	
	/// <summary>この状態に入った時の処理</summary>
	virtual void OnEnter(AnimationBase* animation, ANIMATION_TYPE oldState) = 0;
	/// <summary>この状態を出る時の処理</summary>
	virtual void OnExit(AnimationBase* animation, ANIMATION_TYPE newState) = 0;

	/// <summary>ステート変更確認</summary>
	virtual ANIMATION_TYPE CheckState(AnimationBase* animation, ANIMATION_TYPE nextState) = 0;

	/// <summary>同分類の種類かを確認する</summary>
	virtual bool CheckSameType(ANIMATION_TYPE animationType)
	{
		return mStateNumber == animationType;
	}

	/// <summary>追加終了時間設定</summary>
	void SetAddEndTime(int addEndTime) 
	{ mnAddEndTime = addEndTime; }
};

/*-------------------------*/
/*【DotWeenステートベース】*/
/*-------------------------*/
class IStateDotWeen : public StateBase<DOT_WEEN_TYPE, void>
{
public:
	IStateDotWeen()
	: StateBase<DOT_WEEN_TYPE, void>(DOT_WEEN_TYPE::NONE, std::vector<STATE_CHANGE_CRITERIA_DATA<DOT_WEEN_TYPE, void>>{})
	{
	}

	virtual void Update(DOT_WEEN_DATA dotWeenData) = 0;
};

/*------------------------*/
/*【シーンステートベース】*/
/*------------------------*/
class IStateScene : public StateBase<SCENE, void>
{
protected:
	// ターゲットマネージャー
	TargetManager* mpTargetManager;
	
	// マップマネージャー
	MapManager* mpMapManager;

	// シーンカメラID
	int mnSceneCameraID;

public:
	IStateScene(SCENE stateNumber, std::vector<STATE_CHANGE_CRITERIA_DATA<SCENE, void>> stateChangeCriterias);
	virtual ~IStateScene() = default;

	/*この状態に入った時の処理*/
	virtual void OnEnter(SceneManager* sceneManager) = 0;
	/*この状態を出る時の処理*/
	virtual void OnExit(SceneManager* sceneManager) = 0;

	/*ステージ状態に入った時の共通処理*/
	void StageOnEnter(SceneManager* sceneManager);

	/*更新*/
	SCENE Update(SceneManager* sceneManager);

	/*シーンカメラID*/
	inline int GetSceneCameraID() const { return mnSceneCameraID; }
};

/*--------------------*/
/*【UIステートベース】*/
/*--------------------*/
class IStateUI : public StateBase<STATE_TYPE_UI, void>
{
public:
	IStateUI(STATE_TYPE_UI stateNumber, std::vector<STATE_CHANGE_CRITERIA_DATA<STATE_TYPE_UI, void>> stateChangeCriterias)
	: StateBase<STATE_TYPE_UI, void>(stateNumber, stateChangeCriterias)
	{
	}
	virtual ~IStateUI() = default;

	/// <summary>終了</summary>
	virtual void Finalize() {}

	/*この状態に入った時の処理*/
	virtual void OnEnter(UIBase* ui) = 0;
	/*この状態を出る時の処理*/
	virtual void OnExit(UIBase* ui) = 0;

	/*更新*/
	virtual STATE_TYPE_UI Update(UIBase* ui) { return mStateNumber; }

	/*決定*/
	virtual STATE_TYPE_UI Decision(UIBase* ui) { return mStateNumber; }
	/*終了*/
	virtual STATE_TYPE_UI Cloce(UIBase* ui) { return mStateNumber; }

	/*マウス*/
	virtual STATE_TYPE_UI Mouse(UIBase* ui) { return mStateNumber; }
	/*キーボード*/
	virtual STATE_TYPE_UI Keyboard(UIBase* ui) { return mStateNumber; }
	/*コントローラー*/
	virtual STATE_TYPE_UI Controller(UIBase* ui) { return mStateNumber; }
	/*キーボードとコントローラー*/
	virtual STATE_TYPE_UI Keyboard_Controller(UIBase* ui) { return mStateNumber; }

	/*描画*/
	virtual void Draw(UIBase* ui) = 0;
};