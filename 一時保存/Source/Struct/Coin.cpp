#include "Coin.h"

// TODO: ğŒ‚ğconstexpr‚Ì•Ï”‚É‚·‚é

// Å¬’lİ’è
void CoinData::SetMin()
{
    Coin = 0u;
}

// Å‘å’lİ’è
void CoinData::SetMax()
{
    Coin = 999'999'999u;
}

// Œ¸‚ç‚·
bool CoinData::ReduceCoin(unsigned int price, int count, bool checkFlag)
{
    if ((static_cast<unsigned long long>(Coin) - static_cast<unsigned long long>(count * checkFlag)) < 0llu)
    {
        return true;
    }

    return false;
}

// ‘‚â‚·
bool CoinData::IncreaseCoin(unsigned int price, int count, bool checkFlag)
{
    if ((static_cast<unsigned long long>(Coin) + static_cast<unsigned long long>(count * checkFlag)) > 999'999'999llu)
    {
        return true;
    }

    return false;
}