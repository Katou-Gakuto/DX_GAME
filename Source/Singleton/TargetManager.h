#pragma once
#include <vector>

#include "BitFlag.h"
#include "TargetData.h"

class CharacterBase;

enum class TARGET_TYPE
{
	PLAYER = 0,
	ENEMY,
};

class TargetManager
{
private:
	CharacterTargetData mstPlayer;	// プレイヤー

	std::vector<CharacterTargetData> mstEnemys;	// エネミー

public:
	TargetManager();
	~TargetManager() = default;


	/*----------*/
	/*【初期化】*/
	/*----------*/

	/*全初期化*/
	void Init();

	/*指定ターゲット初期化*/
	void TargetInit(TARGET_TYPE targetNumber);

	/*指定ターゲット初期化*/
	void TargetInit(BIT_FLAG<unsigned int> targetNumber);

	/*--------*/
	/*【削除】*/
	/*--------*/

	/*削除*/
	void Delete(CharacterBase* character, TARGET_TYPE targetNumber);


	/*--------*/
	/*【設定】*/
	/*--------*/

	/*ターゲット設定*/
	void SetTarget(CharacterBase* target, TARGET_TYPE targetNumber);
	/*ターゲット設定*/
	void SetTarget(std::vector<CharacterTargetData> target, TARGET_TYPE targetNumber);


	/*--------*/
	/*【取得】*/
	/*--------*/

	/*ターゲット取得*/
	CharacterTargetData GetTarget(TARGET_TYPE targetNumber);

	/*ターゲット取得*/
	std::vector<CharacterTargetData> GetTargets(TARGET_TYPE targetNumber);
};