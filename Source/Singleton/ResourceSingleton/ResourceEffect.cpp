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
	mmSettingHandleFlagByProcess[RESOURCE_BASE_HANDLE_FLAG_SETTING_TYPE::GENERATION_RESOURCE]  = HANDLE_FLAG::ZERO_LOOK;
	mmSettingHandleFlagByProcess[RESOURCE_BASE_HANDLE_FLAG_SETTING_TYPE::DUPLICATION_RESOURCE] = HANDLE_FLAG::ZERO_LOOK;
	mmSettingHandleFlagByProcess[RESOURCE_BASE_HANDLE_FLAG_SETTING_TYPE::REDUCE_RESOURCE]      = HANDLE_FLAG::ZERO_LOOK;
	
	mmSettingHandleFlagByProcess[RESOURCE_EFFECT_HANDLE_FLAG_SETTING_TYPE::EFFECT_HANDLE] = HANDLE_FLAG::ZERO_EXCEPT_LOOK;
	mmSettingHandleFlagByProcess[RESOURCE_EFFECT_HANDLE_FLAG_SETTING_TYPE::DELETE_EFFECT_HANDLE] = HANDLE_FLAG::ZERO_EXCEPT_LOOK;

	if (Effekseer_Init(20000 * 10) == -1)
	{
		Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::RESOURCE_FLAG);
		return;
	}

	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	mnEffectDrawPreHandle = graph->GetResourceHandle(resourceFile + "Effect/Background.png", nullptr);
}

void ResourceEffect::Finalize()
{
	for (auto& handle : mclHandleContainer.GetHandleMap())
	{
		DeleteEffekseerEffect(handle.second[0]);
	}

	Effkseer_End();
}

// int ResourceEffect::GetEffectResource(std::string fileName, float size)
// {
// 	mclHandleContainer.SetHandleFlag(HANDLE_FLAG::ZERO_LOOK);

// 	if (mclHandleContainer.CheckFileName(fileName))
// 	{
// #ifdef _DEBUG
// 		int resultHandle = mclHandleContainer.RegisterHandle(0);
// 		DEBUG::SaveText("エフェクトハンドル取得 : " + fileName + "; HANDLE : " + std::to_string(resultHandle) + "; HANDLE(原本) : " + std::to_string(mclHandleContainer.GetHandleMap()[fileName][0]) + "; COUNT : " + std::to_string(mclHandleContainer.GetHandleCount(mclHandleContainer.GetHandleMap()[fileName][0])) + '\n', DEBUG::DEBUG_MAP_TYPE::DEBUG_EFFECT);
// 		return resultHandle;
// #endif
// 		return mclHandleContainer.RegisterHandle(0);
// 	}

// #ifdef _DEBUG
// 	int handle = mclHandleContainer.RegisterHandle(LoadEffekseerEffect(fileName.c_str(), size));
// 	DEBUG::SaveText("エフェクトハンドル(原本)取得 : " + fileName + "; HANDLE : " + std::to_string(handle) + "; COUNT : " + std::to_string(mclHandleContainer.GetHandleCount(mclHandleContainer.GetHandleMap()[fileName][0])) + '\n', DEBUG::DEBUG_MAP_TYPE::DEBUG_EFFECT);
// 	return handle;
// #endif
// 	return mclHandleContainer.RegisterHandle(LoadEffekseerEffect(fileName.c_str(), size));
// }

int ResourceEffect::GetEffectHandle(int handle, int oldHandle)
{
	SetHandleFlag(RESOURCE_EFFECT_HANDLE_FLAG_SETTING_TYPE::EFFECT_HANDLE);

	for (std::pair<std::string, std::vector<int>> effectHandle : mclHandleContainer.GetHandleMap())
	{
		if (effectHandle.second[0] == handle)
		{
			if (oldHandle != -1)
			{
				std::vector<int> deleteHandle = mclHandleContainer.DeleteHandle(oldHandle, false);

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
				handle = mclHandleContainer.RegisterHandle(PlayEffekseer3DEffect(handle), effectHandle.first, false);
				DEBUG::SaveText("エフェクトハンドル(交換)取得 : " + std::to_string(handle) + '\n', DEBUG::DEBUG_MAP_TYPE::DEBUG_EFFECT);
				return handle;
#endif
				int resultHandle = PlayEffekseer3DEffect(handle);
				if (mclHandleContainer.SwapHandle(resultHandle, oldHandle))
				{
					return resultHandle;
#ifdef _DEBUG
				DEBUG::SaveText("エフェクトハンドル(交換)取得成功 : " + std::to_string(resultHandle) + '\n', DEBUG::DEBUG_MAP_TYPE::DEBUG_EFFECT);
#endif
				}
#ifdef _DEBUG
				DEBUG::SaveText("エフェクトハンドル(交換)取得失敗 : " + std::to_string(resultHandle) + ", " + std::to_string(oldHandle) + '\n', DEBUG::DEBUG_MAP_TYPE::DEBUG_EFFECT);
#endif
				return -1;
			}
			else
			{
#ifdef _DEBUG
				handle = mclHandleContainer.RegisterHandle(PlayEffekseer3DEffect(handle), effectHandle.first, false);
				DEBUG::SaveText("エフェクトプレイハンドル取得 : " + std::to_string(handle) + '\n', DEBUG::DEBUG_MAP_TYPE::DEBUG_EFFECT);
				return handle;
#endif
				return mclHandleContainer.RegisterHandle(PlayEffekseer3DEffect(handle), effectHandle.first, false);
			}
		}
	}

	return -1;
}

void ResourceEffect::DeletePlayEffectHandle(int handle)
{
	SetHandleFlag(RESOURCE_EFFECT_HANDLE_FLAG_SETTING_TYPE::DELETE_EFFECT_HANDLE);
	std::vector<int> deleteHandle = mclHandleContainer.DeleteHandle(handle, false);
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
	std::map<int, int> handleCountMap = mclHandleContainer.GetHandleCountMap();
	if (handleCountMap.find(handle) != handleCountMap.end())
	{
		text = text + "; COUNT : " + std::to_string(mclHandleContainer.GetHandleCountMap()[handle]);
	}
	text = text + '\n';
	DEBUG::SaveText(text, DEBUG::DEBUG_MAP_TYPE::DEBUG_EFFECT);
#endif
}

// void ResourceEffect::ReduceEffectDataHandle(int handle)
// {
// 	mclHandleContainer.SetHandleFlag(HANDLE_FLAG::ZERO_LOOK);
// 	std::vector<int> deleteHandle = mclHandleContainer.DeleteHandle(handle);

// #ifdef _DEBUG
// 	std::string text = "エフェクトハンドル削除 : " + std::to_string(handle) + "(NOT_DELETE)";
// 	for (int i = 0; i < deleteHandle.size(); i++)
// 	{
// 		text = text + " : " + std::to_string(deleteHandle[i]);
// 	}
// 	text = text + '\n';
// 	DEBUG::SaveText(text, DEBUG::DEBUG_MAP_TYPE::DEBUG_EFFECT);
// #endif

// 	if (deleteHandle.size() > 0)
// 	{
// 		for (int i = 1; i < deleteHandle.size(); i++)
// 		{
// 			StopEffekseer3DEffect(deleteHandle[i]);
// 		}

// 		DeleteEffekseerEffect(deleteHandle[0]);
// 	}
// }

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
	for (std::pair<std::string, std::vector<int>> effectHandle : mclHandleContainer.GetHandleMap())
	{
		for (int i = 1; i < effectHandle.second.size(); i++)
		{
			StopEffect(effectHandle.second[i]);
		}
	}
}

void ResourceEffect::PlayAllEfect()
{
	for (std::pair<std::string, std::vector<int>> effectHandle : mclHandleContainer.GetHandleMap())
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

void ResourceEffect::EffectDrawFlagReset()
{
	mbEffectDrawFlag = false;
}

// リソース本体作成
int ResourceEffect::CreateResource(const std::string& fileName, float plusData)
{
	return LoadEffekseerEffect(fileName.c_str(), plusData);
}

// リソース複製
int ResourceEffect::ResourceDuplication(const std::string& fileName, float plusData)
{
	SetHandleFlag(RESOURCE_BASE_HANDLE_FLAG_SETTING_TYPE::DUPLICATION_RESOURCE);
	return 0;
}

// リソース削除
void ResourceEffect::ResourceDelete(const std::vector<int>& handles)
{
	if (handles.size() > 0)
	{
		for (int i = 1; i < handles.size(); i++)
		{
			StopEffekseer3DEffect(handles[i]);
		}

		DeleteEffekseerEffect(handles[0]);
	}
}