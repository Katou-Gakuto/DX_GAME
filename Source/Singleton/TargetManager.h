#pragma once

class CharacterBase;

enum class TARGET_NUMBER
{
	PLAYER = 0,
};

class TargetManager
{
private:
	CharacterBase* mpPlayer;

public:
	TargetManager();
	~TargetManager() = default;

	/*--------*/
	/*yİ’èz*/
	/*--------*/

	/*ƒ^[ƒQƒbƒgİ’è*/
	void SetTarget(CharacterBase* target, TARGET_NUMBER targetNumber);

	/*--------*/
	/*yæ“¾z*/
	/*--------*/

	/*ƒ^[ƒQƒbƒgæ“¾*/
	CharacterBase* GetTarget(TARGET_NUMBER targetNumber);
};