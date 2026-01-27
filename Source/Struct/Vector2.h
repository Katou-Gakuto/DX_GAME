#pragma once

// 2Dベクトル(int)
struct Vector2_Int
{
	int x;
	int y;

	Vector2_Int()
	{
		this->x = 0;
		this->y = 0;
	}
	Vector2_Int(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
};


// 2Dベクトル
struct Vector2
{
	float x;
	float y;

	Vector2()
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}
	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	operator Vector2_Int()
	{
		Vector2_Int vecInt;
		vecInt.x = static_cast<int>(this->x);
		vecInt.y = static_cast<int>(this->y);
		return vecInt;
	}
};