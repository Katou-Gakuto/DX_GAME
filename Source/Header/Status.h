#pragma once

// ステータス
struct STATUS
{
	int hp;
	int maxHp;

	int level;

	int attckPower;
	int speed;
	int characterType;

	STATUS operator *(float number) const
	{
		STATUS status = *this;

		status.hp         = (int)((float)this->hp         * number);
		status.maxHp      = (int)((float)this->maxHp      * number);
		status.attckPower = (int)((float)this->attckPower * number);
		status.speed      = (int)((float)this->speed      * number);
							  
		return status;		  
	}
};