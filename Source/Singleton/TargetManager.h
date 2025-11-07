#pragma once
#include <vector>

#include "BitFlag.h"

class CharacterBase;

enum class TARGET_NUMBER
{
	PLAYER = 0,
	ENEMY,
};

class TargetManager
{
private:
	CharacterBase* mpPlayer;	// プレイヤー

	std::vector<CharacterBase*> mpEnemys;	// エネミー

public:
	TargetManager();
	~TargetManager() = default;


	/*----------*/
	/*【初期化】*/
	/*----------*/

	/*全初期化*/
	void Init();

	/*指定ターゲット初期化*/
	void TargetInit(TARGET_NUMBER targetNumber);

	/*指定ターゲット初期化*/
	void TargetInit(BIT_FLAG<unsigned int> targetNumber);

	/*--------*/
	/*【削除】*/
	/*--------*/

	/*削除*/
	void Delete(CharacterBase* character, TARGET_NUMBER targetNumber);


	/*--------*/
	/*【設定】*/
	/*--------*/

	/*ターゲット設定*/
	void SetTarget(CharacterBase* target, TARGET_NUMBER targetNumber);


	/*--------*/
	/*【取得】*/
	/*--------*/

	/*ターゲット取得*/
	CharacterBase* GetTarget(TARGET_NUMBER targetNumber);

	/*ターゲット取得*/
	std::vector<CharacterBase*> GetTargets(TARGET_NUMBER targetNumber);
};