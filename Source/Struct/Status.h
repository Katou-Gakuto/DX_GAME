#pragma once

enum class CHARACTER_TYPE;

// ステータス
struct STATUS
{
private:
	int plusAttckPower = 0;	// プラス攻撃力
	int plusSpeed = 0;	// プラス速度

public:
	int hp;		// ヒットポイント
	int maxHp;	// 最大ヒットポイント

	int level;	// レベル

	int exp = 0;	// 経験値

	int baseAttckPower;	// 攻撃力
	int baseSpeed;	// 速度
	float jumpForceMagnification = 1.0f;	// ジャンプ力倍率
	CHARACTER_TYPE characterType;	// キャラクター種類

	STATUS operator *(float number) const
	{
		STATUS status = *this;

		status.hp         		= (int)((float)this->hp         * number);
		status.maxHp      		= (int)((float)this->maxHp      * number);
		status.baseAttckPower 	= (int)((float)this->baseAttckPower * number);
		status.baseSpeed      	= (int)((float)this->baseSpeed      * number);
							  
		return status;
	}
	
	STATUS operator +(STATUS src) const
	{
		STATUS status = *this;

		status.hp         		+= src.hp;
		status.maxHp      		+= src.maxHp;
		status.baseAttckPower 	+= src.baseAttckPower;
		status.baseSpeed      	+= src.baseSpeed;
							  
		return status;		  
	}

	bool operator==(STATUS src)
	{
		if ((this->hp != src.hp) || (this->maxHp != src.maxHp) || (this->level != src.level) || (this->baseAttckPower != src.baseAttckPower) || (this->baseSpeed != src.baseSpeed) || (this->characterType != src.characterType))
		{
			return false;
		}

		return true;
	}
	bool operator!=(STATUS src)
	{
		return !(*this == src);
	}

	inline static STATUS SetStatus(int Hp, int MaxHp, int Level, int exp, int AttckPower, int Speed, CHARACTER_TYPE CharacterType)
	{
		STATUS result = STATUS();

		result.hp = Hp;
		result.maxHp = MaxHp;
		result.level = Level;
		result.exp = exp;
		result.baseAttckPower = AttckPower;
		result.baseSpeed = Speed;
		result.characterType = CharacterType;

		return result;
	}

	/// <summary>現在の速度を取得</summary>
	int GetNowSpeed() const { return baseSpeed + plusSpeed; }
	/// <summary>プラスする速度に加算</summary>
	void AddSpeed(int addSpeed) { plusSpeed += addSpeed; }
	/// <summary>プラスする速度に減算</summary>
	void SubSpeed(int subSpeed) { plusSpeed -= subSpeed; }

	/// <summary>現在の攻撃力を取得</summary>
	int GetNowAttckPower() const { return baseAttckPower + plusAttckPower; }
	/// <summary>プラスする攻撃力に加算</summary>
	void AddAttckPower(int addAttckPower) { plusAttckPower += addAttckPower; }
	/// <summary>プラスする攻撃力に減算</summary>
	void SubAttckPower(int subAttckPower) { plusAttckPower -= subAttckPower; }
};