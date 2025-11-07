#pragma once
#include <iostream>
#include <type_traits>

// ビットフラグ用構造体
template<typename T, typename = typename std::enable_if<std::is_integral<T>::value&& std::is_unsigned<T>::value>::type>
struct BIT_FLAG
{
public:
	T flags;// フラグ

	BIT_FLAG() : flags((T)0) {}
	BIT_FLAG(T flag) : flags(flag) {}

	operator T&(){
		return this->flags;
	}

	bool operator &(T flag) const {
		return ((this->flags & flag) != 0);
	}

	/*初期化*/
	inline void Init() { flags = (T)0; }
	/*全ビット有効*/
	inline void SetAllBit() { flags = ~((T)0); }

	/*1のビットがあれば「true」を返す*/
	inline bool Bool() const {
		return this->flags != 0;
	}

	/*-----【指定ビット設定】-----*/
	inline void SetFlag(bool flag, int number){
		if (flag){
			EnableFlag(number);
		}
		else
		{
			DisableFlag(number);
		}
	}
	/*【指定ビット設定】*/
	template<typename ENUM_T>
	inline void SetFlag(bool flag, ENUM_T number) { SetFlag(flag, (int)number); }
	/*----------------------------*/


	/*-----【指定ビット有効化】-----*/
	inline void EnableFlag(int number){
		if (CheckNumber(number)){
			flags |= ((T)1 << number);
		}
	}
	/*【指定ビット有効化】*/
	template<typename ENUM_T>
	inline void EnableFlag(ENUM_T number) { EnableFlag((int)number); }
	/*------------------------------*/


	/*-----【指定ビット無効化】-----*/
	inline void DisableFlag(int number){
		if (CheckNumber(number)){
			flags &= ~((T)1 << number);
		}
	}
	/*【指定ビット無効化】*/
	template<typename ENUM_T>
	inline void DisableFlag(ENUM_T number) { DisableFlag((int)number); }
	/*------------------------------*/


	/*-----【指定ビット反転】-----*/
	inline void InvertFlag(int number){
		if (CheckNumber(number)){
			flags ^= ((T)1 << number);
		}
	}
	/*【指定ビット反転】*/
	template<typename ENUM_T>
	inline void InvertFlag(ENUM_T number) { InvertFlag((int)number); }
	/*----------------------------*/
	

	/*-----【指定ビット取得】-----*/
	inline bool GetFlag(int number) const {
		if (CheckNumber(number)){
			return ((flags & ((T)1 << number)) != 0);
		}
		return false;
	}
	/*【指定ビット取得】*/
	template<typename ENUM_T>
	inline bool GetFlag(ENUM_T number) const { return GetFlag((int)number); }
	/*----------------------------*/


	/*Tのビット数を超えてないかを確認する(超えていれば「false」を返す)*/
	static inline bool CheckNumber(int number){

		int test = sizeof(T) * 8;
		if ((sizeof(T) * 8) > number){
			return true;
		}
		return false;
	}

	/*指定のビットだけ1の整数を取得*/
	inline static BIT_FLAG BIT_GET(int number) { return BIT_FLAG((T)1 << number); }
};