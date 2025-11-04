#pragma once

/*------------------*/
/*     【共通】     */
/*------------------*/

/*--------------------*/
/*【エネミーステート】*/
/*--------------------*/

enum class ENEMY_STATE
{
	IDLE_ENEMY_STATE = 0,
	MOVE_ENEMY_STATE,
	ATTACK_ENEMY_STATE,
};

/*----------------------*/
/*【エネミー共通処理用】*/
/*----------------------*/
class EnemyProcess
{
protected:
	EnemyProcess();
	~EnemyProcess() = default;
};