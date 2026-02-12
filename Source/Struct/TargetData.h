#pragma once
class CharacterBase;

struct CharacterTargetData
{
	// ターゲット
	CharacterBase* target;
	// マップポジションX
	int mapPosX;
	// マップポジションZ
	int mapPosZ;

	CharacterTargetData();
	CharacterTargetData(CharacterBase* src);

	operator CharacterBase*()
	{
		return this->target;
	}
};