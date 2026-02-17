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
bool EndManager::EndFlag()
{
#if _DEBUG
	// ビットフラグ設定
	if (BIT_FAILURE_FLAG)
	{
		SetEndFlag(true, END_FLAG_NUMBER::BIT_FLAG);
	}
#endif


	bool endFlag = false;

	endFlag |= (ProcessMessage() != 0);

	endFlag |= ((GetAsyncKeyState(VK_ESCAPE) & 0x8000) != 0);

	if (mullEndFlag.Bool())
	{
		endFlag = true;
		ErrorLogFmtAdd("%llu", mullEndFlag);
	}

	return endFlag;
}