#include <windows.h>

#include "../Header/BitFlag.h"

#include "DxLib.h"

#include "../Header/EndManager.h"

EndManager::EndManager()
: mullEndFlag(BIT_FLAG<unsigned long long>())
, mpDeleteObject(nullptr)
{
}
EndManager::~EndManager()
{
	if (mpDeleteObject != nullptr)
	{
		delete mpDeleteObject;
	}
}

// 初期化
void EndManager::Init()
{
}

// 終了フラグ
bool EndManager::EndFlag()
{
	bool endFlag = false;

	endFlag |= (ProcessMessage() != 0);

	endFlag |= ((GetAsyncKeyState(VK_ESCAPE) & 0x8000) != 0);

	if (mullEndFlag.Bool())
	{
		endFlag = true;
	}

	return endFlag;
}

// 終了フラグ設定
void EndManager::SetEndFlag(bool flag, END_FLAG_NUMBER number)
{
	mullEndFlag.SetFlag(flag, number);
}