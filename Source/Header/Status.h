#pragma once

enum class CHARACTER_TYPE;

// ステータス
struct STATUS
{
	int hp;
	int maxHp;

	int level;

	int attckPower;
	int speed;
	CHARACTER_TYPE characterType;

	STATUS operator *(float number) const
	{
		STATUS status = *this;

		status.hp         = (int)((float)this->hp         * number);
		status.maxHp      = (int)((float)this->maxHp      * number);
		status.attckPower = (int)((float)this->attckPower * number);
		status.speed      = (int)((float)this->speed      * number);
							  
		return status;		  
	}

	bool operator==(STATUS src)
	{
		if ((this->hp != src.hp) || (this->maxHp != src.maxHp) || (this->level != src.level) || (this->attckPower != src.attckPower) || (this->speed != src.speed) || (this->characterType != src.characterType))
		{
			return false;
		}

		return true;
	}
	bool operator!=(STATUS src)
	{
		return !(*this == src);
	}

	inline static STATUS SetStatus(int Hp, int MaxHp, int Level, int AttckPower, int Speed, CHARACTER_TYPE CharacterType)
	{
		STATUS result = STATUS();

		result.hp = Hp;
		result.maxHp = MaxHp;
		result.level = Level;
		result.attckPower = AttckPower;
		result.speed = Speed;
		result.characterType = CharacterType;

		return result;
	}
};