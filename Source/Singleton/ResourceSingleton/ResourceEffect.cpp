#include "ResourceEffect.h"

#include "EffekseerForDXLib.h"

#include "Master.h"
#include "EndManager.h"
#include "ResourceGraph.h"

#ifdef _DEBUG
#include "DebugLogs/DebugLog.h"
#endif

ResourceEffect::ResourceEffect()
: mbEffectDrawFlag(false)
, mnEffectDrawPreHandle(-1)
{
}

ResourceEffect::~ResourceEffect()
{
}

void ResourceEffect::Initilize(ResourceGraph* graph, const std::string& resourceFile)
{
	mpHandleContainer = new HandleContainer<std::string, int>();

	mmSettingHandleFlagByProcess[RESOURCE_BASE_HANDLE_FLAG_SETTING_TYPE::GET_RESOURCE]         = HANDLE_FLAG::ZERO_LOOK;
	mmSettingHandleFlagByProcess[RESOURCE_BASE_HANDLE_FLAG_SETTING_TYPE::REDUCE_RESOURCE]      = HANDLE_FLAG::ZERO_EXCEPT_LOOK;
	mmSettingHandleFlagByProcess[RESOURCE_BASE_HANDLE_FLAG_SETTING_TYPE::GENERATION_RESOURCE]  = HANDLE_FLAG::NONE;
	mmSettingHandleFlagByProcess[RESOURCE_BASE_HANDLE_FLAG_SETTING_TYPE::DUPLICATION_RESOURCE] = HANDLE_FLAG::NONE;

	if (Effekseer_Init(20000 * 10) == -1)
	{
		Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::RESOURCE_FLAG);
		return;
	}

	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	mnEffectDrawPreHandle = graph->GetGraphHandle(resourceFile + "Effect/Background.png");
}

void ResourceEffect::Finalize()
{
	for (auto& handle : mpHandleContainer->GetHandleMap())
	{
		DeleteEffekseerEffect(handle.second[0]);
	}

	delete mpHandleContainer;
	mpHandleContainer = nullptr;
	Effkseer_End();
}

int ResourceEffect::GetEffectResource(std::string fileName, float size)
{
	mpHandleContainer->SetHandleFlag(HANDLE_FLAG::ZERO_LOOK);

	if (mpEffectHandleContainer->CheckFileName(fileName))
	{
#ifdef _DEBUG
		int resultHandle = mpEffectHandleContainer->RegisterHandle(0);
		DEBUG::SaveText("エフェクトハンドル取得 : " + fileName + "; HANDLE : " + std::to_string(resultHandle) + "; HANDLE(原本) : " + std::to_string(mpEffectHandleContainer->GetHandleMap()[fileName][0]) + "; COUNT : " + std::to_string(mpEffectHandleContainer->GetHandleCount(mpEffectHandleContainer->GetHandleMap()[fileName][0])) + '\n', DEBUG::DEBUG_MAP_TYPE::DEBUG_EFFECT);
		return resultHandle;
#endif
		return mpEffectHandleContainer->RegisterHandle(0);
	}

#ifdef _DEBUG
	int handle = mpEffectHandleContainer->RegisterHandle(LoadEffekseerEffect(fileName.c_str(), size));
	DEBUG::SaveText("エフェクトハンドル(原本)取得 : " + fileName + "; HANDLE : " + std::to_string(handle) + "; COUNT : " + std::to_string(mpEffectHandleContainer->GetHandleCount(mpEffectHandleContainer->GetHandleMap()[fileName][0])) + '\n', DEBUG::DEBUG_MAP_TYPE::DEBUG_EFFECT);
	return handle;
#endif
	return mpEffectHandleContainer->RegisterHandle(LoadEffekseerEffect(fileName.c_str(), size));
}

int ResourceEffect::GetEffectHandle(int handle, int oldHandle)
{
	mpEffectHandleContainer->SetHandleFlag(HANDLE_FLAG::ZERO_EXCEPT_LOOK);

	for (std::pair<std::string, std::vector<int>> effectHandle : mpEffectHandleContainer->GetHandleMap())
	{
		if (effectHandle.second[0] == handle)
		{
			if (oldHandle != -1)
			{
				std::vector<int> deleteHandle = mpEffectHandleContainer->DeleteHandle(oldHandle, false);

#ifdef _DEBUG
				std::string text = "オルドエフェクトハンドル削除 : " + std::to_string(oldHandle) + "(NOT_DELETE)";
				for (int i = 0; i < deleteHandle.size(); i++)
				{
					text = text + " : " + std::to_string(deleteHandle[i]);
				}
				text = text + '\n';
				DEBUG::SaveText(text);
#endif

#ifdef _DEBUG
				handle = mpEffectHandleContainer->RegisterHandle(PlayEffekseer3DEffect(handle), effectHandle.first, false);
				DEBUG::SaveText("エフェクトハンドル(交換)取得 : " + std::to_string(handle) + '\n', DEBUG::DEBUG_MAP_TYPE::DEBUG_EFFECT);
				return handle;
#endif
				return mpEffectHandleContainer->RegisterHandle(PlayEffekseer3DEffect(handle), effectHandle.first, false);
			}
			else
			{
#ifdef _DEBUG
				handle = mpEffectHandleContainer->RegisterHandle(PlayEffekseer3DEffect(handle), effectHandle.first, false);
				DEBUG::SaveText("エフェクトプレイハンドル取得 : " + std::to_string(handle) + '\n', DEBUG::DEBUG_MAP_TYPE::DEBUG_EFFECT);
				return handle;
#endif
				return mpEffectHandleContainer->RegisterHandle(PlayEffekseer3DEffect(handle), effectHandle.first, false);
			}
		}
	}

	return -1;
}

void ResourceEffect::DeletePlayEffectHandle(int handle)
{
	mpEffectHandleContainer->SetHandleFlag(HANDLE_FLAG::ZERO_EXCEPT_LOOK);
	std::vector<int> deleteHandle = mpEffectHandleContainer->DeleteHandle(handle, false);
	if (deleteHandle.size() > 0)
	{
		StopEffekseer3DEffect(handle);
	}
#ifdef _DEBUG
	std::string text = "プレイエフェクトハンドル削除 : " + std::to_string(handle) + "(NOT_DELETE)";
	for (int i = 0; i < deleteHandle.size(); i++)
	{
		text = text + " : " + std::to_string(deleteHandle[i]);
	}
	std::map<int, int> handleCountMap = mpEffectHandleContainer->GetHandleCountMap();
	if (handleCountMap.find(handle) != handleCountMap.end())
	{
		text = text + "; COUNT : " + std::to_string(mpEffectHandleContainer->GetHandleCountMap()[handle]);
	}
	text = text + '\n';
	DEBUG::SaveText(text, DEBUG::DEBUG_MAP_TYPE::DEBUG_EFFECT);
#endif
}

void ResourceEffect::ReduceEffectDataHandle(int handle)
{
	mpEffectHandleContainer->SetHandleFlag(HANDLE_FLAG::ZERO_LOOK);
	std::vector<int> deleteHandle = mpEffectHandleContainer->DeleteHandle(handle);

#ifdef _DEBUG
	std::string text = "エフェクトハンドル削除 : " + std::to_string(handle) + "(NOT_DELETE)";
	for (int i = 0; i < deleteHandle.size(); i++)
	{
		text = text + " : " + std::to_string(deleteHandle[i]);
	}
	text = text + '\n';
	DEBUG::SaveText(text, DEBUG::DEBUG_MAP_TYPE::DEBUG_EFFECT);
#endif

	if (deleteHandle.size() > 0)
	{
		for (int i = 1; i < deleteHandle.size(); i++)
		{
			StopEffekseer3DEffect(deleteHandle[i]);
		}

		DeleteEffekseerEffect(deleteHandle[0]);
	}
}

void ResourceEffect::DrawEffect(int handle, VECTOR position, VECTOR angle, VECTOR size)
{
	if (!mbEffectDrawFlag)
	{
		DrawGraph(0, 0, mnEffectDrawPreHandle, TRUE);
		mbEffectDrawFlag = true;
	}

	SetPosPlayingEffekseer3DEffect(handle, position.x, position.y, position.z);
	SetRotationPlayingEffekseer3DEffect(handle, angle.x, angle.y, angle.z);
	SetScalePlayingEffekseer3DEffect(handle, size.x, size.y, size.z);
}

void ResourceEffect::StopEffect(int handle)
{
	SetSpeedPlayingEffekseer3DEffect(handle, 0.0f);
}

void ResourceEffect::PlayEffect(int handle, float speed)
{
	SetSpeedPlayingEffekseer3DEffect(handle, speed);
}

void ResourceEffect::StopAllEfect()
{
	for (std::pair<std::string, std::vector<int>> effectHandle : mpEffectHandleContainer->GetHandleMap())
	{
		for (int i = 1; i < effectHandle.second.size(); i++)
		{
			StopEffect(effectHandle.second[i]);
		}
	}
}

void ResourceEffect::PlayAllEfect()
{
	for (std::pair<std::string, std::vector<int>> effectHandle : mpEffectHandleContainer->GetHandleMap())
	{
		for (int i = 1; i < effectHandle.second.size(); i++)
		{
			PlayEffect(effectHandle.second[i], 1.0f);
		}
	}
}

void ResourceEffect::EffectDrawProcess()
{
	Effekseer_Sync3DSetting();
	UpdateEffekseer3D();
	DrawEffekseer3D();
}

void ResourceEffect::DrawDataRelease()
{
	mbEffectDrawFlag = false;
}
