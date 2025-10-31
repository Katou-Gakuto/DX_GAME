#include <string>

#include "../Header/CheckUI.h"
#include "../Header/ObjectBases.h"

template<typename T>
CheckUI<T>::CheckUI(void* yesArgument, void* noArgument, void(T::* yesExecuteMemberFunction)(void*), void(T::* noExecuteMemberFunction)(void*), T* yesFunctionPointer, T* noFunctionPointer, std::string messageWord, std::string yesWord, std::string noWord)
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
CheckUI<T>::~CheckUI()
{
}


// UI初期化
template<typename T>
void CheckUI<T>::UIInitilize()
{
}

// UI終了
template<typename T>
void CheckUI<T>::UIFinalize()
{
}

// UI更新
template<typename T>
void CheckUI<T>::UIUpdate()
{
	LeftRightSelectProcess();
}

// UI最終更新
template<typename T>
void CheckUI<T>::UILastUpdate()
{
}

// UI描画
template<typename T>
void CheckUI<T>::UIDraw()
{
}

// 選択決定時処理
template<typename T>
void CheckUI<T>::DecisionProcess()
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