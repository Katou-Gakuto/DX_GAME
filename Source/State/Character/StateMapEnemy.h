#pragma once

#include "EnemyCommonProcessing.h"
#include "ObjectBases.h"
#include "StateBase.h"

class KeyState;
class SceneManager;
class TargetManager;

/*------------------*/
/*     【共通】     */
/*------------------*/

/*--------------------------*/
/*【マップエネミーステート】*/
/*--------------------------*/

enum class MAP_ENEMY_STATE
{
	IDLE_MAP_ENEMY_STATE = 0,
	TELOP_MAP_ENEMY_STATE,
};

/*----------------------------*/
/*【マップエネミー共通処理用】*/
/*----------------------------*/
class MapEnemyProcess : public EnemyCommonProcessing
{
protected:
	// キーステート
	KeyState* mpKeyState;

	// シーンマネージャー
	SceneManager* mpSceneManager;

	// ターゲットマネージャー
	TargetManager* mpTargetManager;

	// マップシーン
	SCENE meMapScene;

protected:
	MapEnemyProcess(SCENE mapScene);
	~MapEnemyProcess() = default;

	/*一定範囲内にプレイヤーターゲットがいるなら「true」*/
	bool PlayerTargetCheck(CharacterBase* character, float range);

	/*死亡*/
	void MapEnemyDeath(CharacterBase* character);

	/*マップシーンに移動開始する*/
	void SetMapScene(CharacterBase* character);
};

/*--------------------------*/
/*     【基本ステート】     */
/*--------------------------*/

/*----------------------------*/
/*【Idleマップエネミーテート】*/
/*----------------------------*/
class IdleMapEnemyState : public IStateCharacter, public MapEnemyProcess
{
public:
	IdleMapEnemyState(SCENE mapScene);
	~IdleMapEnemyState() = default;

	void Finalize(CharacterBase* character) override { EnemyCommonProcessingData_Delete();}

	/*この状態に入った時の処理*/
	void OnEnter(CharacterBase* character) override;
	/*この状態を出る時の処理*/
	void OnExit(CharacterBase* character) override;

	/*ステート変更確認*/
	virtual int StateCheck(CharacterBase* character) override;

	/*更新*/
	void Update(CharacterBase* character) override;

	/*最終更新*/
	void LastUpdate(CharacterBase* character) override;

	/*描画*/
	void Draw(CharacterBase* character) override;

	/*死亡*/
	void Death(CharacterBase* character) override;
};

/*--------------------------------*/
/*【テロップマップエネミーテート】*/
/*--------------------------------*/
class TelopMapEnemyState : public IStateCharacter, public MapEnemyProcess
{
public:
	TelopMapEnemyState(SCENE mapScene);
	~TelopMapEnemyState() = default;

	void Finalize(CharacterBase* character) override { EnemyCommonProcessingData_Delete();}

	/*この状態に入った時の処理*/
	void OnEnter(CharacterBase* character) override;
	/*この状態を出る時の処理*/
	void OnExit(CharacterBase* character) override;

	/*ステート変更確認*/
	virtual int StateCheck(CharacterBase* character) override;

	/*更新*/
	void Update(CharacterBase* character) override;

	/*最終更新*/
	void LastUpdate(CharacterBase* character) override;

	/*描画*/
	void Draw(CharacterBase* character) override;

	/*死亡*/
	void Death(CharacterBase* character) override;
};