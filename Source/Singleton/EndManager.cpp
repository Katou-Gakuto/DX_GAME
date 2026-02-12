#include <windows.h>

#include "BitFlag.h"

#include "DxLib.h"

#include "EndManager.h"

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
bool EndManager::EndFlag() const
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