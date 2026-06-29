#pragma once
typedef struct CoinData
{
public:
	unsigned int Coin;

	operator unsigned int&()
	{
		return Coin;
	}

	/// <summary>最小値設定</summary>
	void SetMin();
	/// <summary>最大値設定</summary>
	void SetMax();

	/// <summary>減らす</summary>
	/// <param name="price">値段</param>
	/// <param name="count">個数</param>
	/// <returns>失敗フラグ(マイナスのコイン数になってる)</returns>
	bool ReduceCoin(unsigned int price, int count = 1, bool checkFlag = false);

	/// <summary>増やす</summary>
	/// <param name="price">値段</param>
	/// <param name="count">個数</param>
	/// <returns>失敗フラグ(コイン数上限を上回っている)</returns>
	bool IncreaseCoin(unsigned int price, int count = 1, bool checkFlag = false);

}COIN_DATA;