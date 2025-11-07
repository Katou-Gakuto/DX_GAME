#include <string>

#include "ObjectBases.h"
#include "UI_Check.h"

template<typename T>
UI_Check<T>::UI_Check(void* yesArgument, void* noArgument, void(T::* yesExecuteMemberFunction)(void*), void(T::* noExecuteMemberFunction)(void*), T* yesFunctionPointer, T* noFunctionPointer, std::string messageWord, std::string yesWord, std::string noWord)
: UIBase(true, 2, true)
, mpYesArgument(yesArgument)
, mpNoArgument(noArgument)
, mfnYesExecuteMemberFunction(yesExecuteMemberFunction)
, mfnNoExecuteMemberFunction(noExecuteMemberFunction)
, mpYesFunctionPointer(yesFunctionPointer)
, mpNoFunctionPointer(noFunctionPointer)
, msMessageWord(messageWord)
, msYesWord(yesWord)
, msNoWord(noWord)
{
}

template<typename T>
UI_Check<T>::~UI_Check()
{
}


// UI初期化
template<typename T>
void UI_Check<T>::UIInitilize()
{
}

// UI終了
template<typename T>
void UI_Check<T>::UIFinalize()
{
}

// UI更新
template<typename T>
void UI_Check<T>::UIUpdate()
{
	LeftRightSelectProcess();
}

// UI最終更新
template<typename T>
void UI_Check<T>::UILastUpdate()
{
}

// UI描画
template<typename T>
void UI_Check<T>::UIDraw()
{
}

// 選択決定時処理
template<typename T>
void UI_Check<T>::DecisionProcess()
{
	switch (mnSelectNumber)
	{
	case 0:
		(mpYesFunctionPointer->*mfnYesExecuteMemberFunction)(mpYesArgument);
		break;

	case 1:
		(mpNoFunctionPointer->*mfnNoExecuteMemberFunction)(mpNoArgument);
		break;
	}

	CloceProcess();
}