#pragma once

#include "AttackEnum.h"

class AnimationBase;
class CharacterBase;
class ModelsControllerBase;

// 攻撃情報設定用情報
struct AttackData
{
	CharacterBase* attackCharacter;	// 攻撃キャラクター

	ATTACK_TYPE attackType;	// 攻撃種類
	
	ATTACK_METHOD_TYPE attackMethdType;	// 攻撃手段種類

	int attackTime;	// 攻撃時間

	int attackPower = -1; // 攻撃力
};

// キャラクター攻撃情報
struct CharacterAttackData
{
    ModelsControllerBase* modelController;  // モデルベース

    AnimationBase* animation;   // アニメションベース

    int attackDataNumber;	// 攻撃情報ナンバー
};