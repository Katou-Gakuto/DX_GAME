#include <string>
#include <vector>

#include "ResourceSound.h"

#include "DataManager.h"

#ifdef _DEBUG
#include "DebugLogs/DebugLog.h"
#endif

ResourceSoundBase::ResourceSoundBase()
: mnSoundVolume(0)
, mnPreSoundVolume(-1)
, mnFixedVolumeHandle()
{
}

ResourceSoundBase::~ResourceSoundBase()
{
}

void ResourceSoundBase::Initilize()
{
	mmSettingHandleFlagByProcess[RESOURCE_BASE_HANDLE_FLAG_SETTING_TYPE::GENERATION_RESOURCE]  = HANDLE_FLAG::ZERO_LOOK;
	mmSettingHandleFlagByProcess[RESOURCE_BASE_HANDLE_FLAG_SETTING_TYPE::DUPLICATION_RESOURCE] = HANDLE_FLAG::ZERO_LOOK;
	mmSettingHandleFlagByProcess[RESOURCE_BASE_HANDLE_FLAG_SETTING_TYPE::REDUCE_RESOURCE]      = HANDLE_FLAG::ZERO_LOOK;

	mmSettingHandleFlagByProcess[RESOURCE_SOUND_HANDLE_FLAG_SETTING_TYPE::SOUND_PLAY]      	   = HANDLE_FLAG::ZERO_EXCEPT_LOOK;
	mmSettingHandleFlagByProcess[RESOURCE_SOUND_HANDLE_FLAG_SETTING_TYPE::SOUND_UPDATE]    	   = HANDLE_FLAG::ZERO_EXCEPT_LOOK;

	mclHandleContainer.SetHandleFlag(HANDLE_FLAG::ZERO_LOOK);

	// mpSoundHandleContainer = new HandleContainer<std::string>();
	// mpSoundHandleContainer->SetHandleFlag(HANDLE_FLAG::ZERO_LOOK);
	// mpPlaySoundHandleContainer = new HandleContainer<int>();
	// mpPlaySoundHandleContainer->SetHandleFlag(HANDLE_FLAG::NONE);

	// mp3DSoundHandleContainer = new HandleContainer<std::string>();
	// mp3DSoundHandleContainer->SetHandleFlag(HANDLE_FLAG::ZERO_LOOK);
	// mpPlay3DSoundHandleContainer = new HandleContainer<int>();
	// mpPlay3DSoundHandleContainer->SetHandleFlag(HANDLE_FLAG::NONE);
}

void ResourceSoundBase::Finalize()
{
	for (std::pair<std::string, std::vector<int>> soundHandle : mclHandleContainer.GetHandleMap())
	{
		for (int i = 0; i < soundHandle.second.size(); i++)
		{
			DeleteSoundMem(soundHandle.second[i]);
#ifdef _DEBUG
			DEBUG::SaveText("サウンド(原本)ハンドル削除(最終) : " + std::to_string(soundHandle.second[i]) + " : " + soundHandle.first + " : HandleNumber <=" + std::to_string(mclHandleContainer.GetHandleCount(soundHandle.second[i])) + '\n');
#endif
		}
	}

// 	for (std::pair<int, std::vector<int>> playSoundHandle : mclPlaySoundHandleContainer.GetHandleMap())
// 	{
// 		for (int i = 0; i < playSoundHandle.second.size(); i++)
// 		{
// 			DeleteSoundMem(playSoundHandle.second[i]);
// #ifdef _DEBUG
// 			DEBUG::SaveText("サウンドハンドル削除(最終) : " + std::to_string(playSoundHandle.second[i]) + " : " + std::to_string(playSoundHandle.first) + " : HandleNumber <=" + std::to_string(mpPlaySoundHandleContainer->GetHandleCount(playSoundHandle.second[i])) + '\n');
// #endif
// 		}
// 	}

// 	for (std::pair<std::string, std::vector<int>> sound3DHandle : mp3DSoundHandleContainer->GetHandleMap())
// 	{
// 		for (int i = 0; i < sound3DHandle.second.size(); i++)
// 		{
// 			DeleteSoundMem(sound3DHandle.second[i]);
// #ifdef _DEBUG
// 			DEBUG::SaveText("3Dサウンド(原本)ハンドル削除(最終) : " + std::to_string(sound3DHandle.second[i]) + " : " + sound3DHandle.first + " : HandleNumber <=" + std::to_string(mp3DSoundHandleContainer->GetHandleCount(sound3DHandle.second[i])) + '\n');
// #endif
// 		}
// 	}
// 	delete mp3DSoundHandleContainer;
// 	mp3DSoundHandleContainer = nullptr;

// 	for (std::pair<int, std::vector<int>> playSound3DHandle : mpPlay3DSoundHandleContainer->GetHandleMap())
// 	{
// 		for (int i = 0; i < playSound3DHandle.second.size(); i++)
// 		{
// 			DeleteSoundMem(playSound3DHandle.second[i]);
// #ifdef _DEBUG
// 			DEBUG::SaveText("3Dサウンドハンドル削除(最終) : " + std::to_string(playSound3DHandle.second[i]) + " : " + std::to_string(playSound3DHandle.first) + " : HandleNumber <=" + std::to_string(mpPlay3DSoundHandleContainer->GetHandleCount(playSound3DHandle.second[i])) + '\n');
// #endif
// 		}
// 	}
// 	delete mpPlay3DSoundHandleContainer;
// 	mpPlay3DSoundHandleContainer = nullptr;
}

// リソース本体作成
int ResourceSoundBase::CreateResource(const std::string& fileName, void* plusData)
{
	return LoadSoundMem(fileName.c_str());
}

// リソース複製
int ResourceSoundBase::ResourceDuplication(const std::string& fileName, void* plusData)
{
	SetHandleFlag(RESOURCE_BASE_HANDLE_FLAG_SETTING_TYPE::DUPLICATION_RESOURCE);

	return 0;
}

// リソース削除
void ResourceSoundBase::ResourceDelete(const std::vector<int>& handles)
{
	for (int i = 0; i < handles.size(); i++)
	{
		DeleteSoundMem(handles[i]);
	}
}

// int ResourceSound::GetSoundHandle(std::string fileName)
// {
// 	if (mpSoundHandleContainer->CheckFileName(fileName))
// 	{
// 		return mpSoundHandleContainer->RegisterHandle(0);
// 	}

// #ifdef _DEBUG
// 	int handle = mpSoundHandleContainer->RegisterHandle(LoadSoundMem(fileName.c_str()));
// 	DEBUG::SaveText("サウンドハンドル(原本)取得 : " + fileName + " : " + std::to_string(handle) + '\n');
// 	return handle;
// #endif
// 	return mpSoundHandleContainer->RegisterHandle(LoadSoundMem(fileName.c_str()));
// }

// void ResourceSound::ReduceSoundHandle(int handle)
// {
// 	std::vector<int> deleteHandle = mpSoundHandleContainer->DeleteHandle(handle);

// #ifdef _DEBUG
// 	std::string text = "サウンドハンドル削除 : " + std::to_string(handle) + "(NOT_DELETE)";
// 	for (int i = 0; i < deleteHandle.size(); i++)
// 	{
// 		text = text + " : " + std::to_string(deleteHandle[i]);
// 	}
// 	text = text + '\n';
// 	DEBUG::SaveText(text);
// #endif

// 	for (int i = 0; i < deleteHandle.size(); i++)
// 	{
// 		DeleteSoundMem(deleteHandle[i]);
// 	}
// }

// int ResourceSound::Get3DSoundHandle(std::string fileName)
// {
// 	if (mp3DSoundHandleContainer->CheckFileName(fileName))
// 	{
// 		return mp3DSoundHandleContainer->RegisterHandle(0);
// 	}

// 	int handle = mp3DSoundHandleContainer->RegisterHandle(LoadSoundMem(fileName.c_str()));
// #ifdef _DEBUG
// 	DEBUG::SaveText("3Dサウンドハンドル(原本)取得 : " + fileName + " : " + std::to_string(handle) + '\n');
// #endif
// 	return handle;
// }

// void ResourceSound::Reduce3DSoundHandle(int handle)
// {
// 	std::vector<int> deleteHandle = mp3DSoundHandleContainer->DeleteHandle(handle);

// #ifdef _DEBUG
// 	std::string text = "3Dサウンドハンドル削除 : " + std::to_string(handle) + "(NOT_DELETE)";
// 	for (int i = 0; i < deleteHandle.size(); i++)
// 	{
// 		text = text + " : " + std::to_string(deleteHandle[i]);
// 	}
// 	text = text + '\n';
// 	DEBUG::SaveText(text);
// #endif

// 	for (int i = 0; i < deleteHandle.size(); i++)
// 	{
// 		DeleteSoundMem(deleteHandle[i]);
// 	}
// }

// void ResourceSound::SetBackSoundHandle(int handle)
// {
// 	if (mnPlayBackSoundHandle != -1)
// 	{
// 		StopSoundMem(mnPlayBackSoundHandle);
// 		DeleteSoundMem(mnPlayBackSoundHandle);
// 	}

// 	int backSoundHandle = DuplicateSoundMem(handle);

// 	ChangeVolumeSoundMem(mnBackSoundVolume, backSoundHandle);

// 	PlaySoundMem(backSoundHandle, DX_PLAYTYPE_LOOP, TRUE);

// 	mnPlayBackSoundHandle = backSoundHandle;
// }

void ResourceSoundBase::SoundUpdate()
{
	std::map<std::string, std::vector<int>>* soundHandleMap = mclHandleContainer.GetHandleMapPointer();

	// ボリュウーム変更
	{
		if (mnPreSoundVolume != mnSoundVolume)
		{
			bool soundVolumeChangeFlag;
			for (std::pair<const std::string, std::vector<int>>& playSoundHandle : *soundHandleMap)
			{
				for (int i = 1; i < playSoundHandle.second.size(); i++)
				{
					soundVolumeChangeFlag = true;
					for (int j = 0; j < mnFixedVolumeHandle.size(); j++)
					{
						if (playSoundHandle.second[i] == mnFixedVolumeHandle[j])
						{
							soundVolumeChangeFlag = false;
							break;
						}
					}
					if (soundVolumeChangeFlag)
					{
						ChangeVolumeSoundMem(mnSoundVolume, playSoundHandle.second[i]);
					}
				}
			}

			mnPreSoundVolume = mnSoundVolume;
		}
	}

	SetHandleFlag(RESOURCE_SOUND_HANDLE_FLAG_SETTING_TYPE::SOUND_UPDATE);
	std::vector<int> deleteHandleNumbers;
	for (std::pair<const std::string, std::vector<int>>& playSoundHandle : *soundHandleMap)
	{
		for (int i = 1; i < playSoundHandle.second.size(); i++)
		{
			if (CheckSoundMem(playSoundHandle.second[i]) == 0)
			{
				deleteHandleNumbers.push_back(playSoundHandle.second[i]);
				DeleteSoundMem(playSoundHandle.second[i]);
			}
		}
	}
	for (int deleteHandleNumber : deleteHandleNumbers)
	{
		std::vector<int> deleteHandle = mclHandleContainer.DeleteHandle(deleteHandleNumber);
#ifdef _DEBUG
				std::string text = "プレイサウンドハンドル削除 : " + std::to_string(deleteHandleNumber) + "(NOT_DELETE)";
				for (int j = 0; j < deleteHandle.size(); j++)
				{
					text = text + " : " + std::to_string(deleteHandle[j]);
				}
				text = text + '\n';
				DEBUG::SaveText(text);
#endif
	}
}

// void ResourceSound::SetPlaySound(int handle, int volume)
// {
// 	int soundHandle = mpPlaySoundHandleContainer->RegisterHandle(DuplicateSoundMem(handle), handle);
// #ifdef _DEBUG
// 	DEBUG::SaveText((std::string)"サウンドハンドル取得 : " + (std::string)"なし" + (std::string)" : " + std::to_string(soundHandle) + '\n');
// #endif

// 	ChangeVolumeSoundMem(mnSoundVolume, soundHandle);

// 	PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK, TRUE);
// }

// void ResourceSound::SetPlay3DSound(int handle, VECTOR position, int volume)
// {
// 	SetCreate3DSoundFlag(TRUE);

// 	int soundHandle = mpPlay3DSoundHandleContainer->RegisterHandle(DuplicateSoundMem(handle), handle);
// #ifdef _DEBUG
// 	DEBUG::SaveText((std::string)"3Dサウンドハンドル取得 : " + (std::string)"なし" + (std::string)" : " + std::to_string(soundHandle) + '\n');
// #endif

// 	Set3DPositionSoundMem(position, soundHandle);
// 	Set3DRadiusSoundMem(2000.0f, soundHandle);

// 	ChangeVolumeSoundMem(mnSoundVolume, soundHandle);

// 	PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK, TRUE);

// 	SetCreate3DSoundFlag(FALSE);
// }

// void ResourceSound::Set3DListenerPosition(VECTOR position, VECTOR frontPosition)
// {
// 	Set3DSoundListenerPosAndFrontPos_UpVecY(position, frontPosition);
// }

ResourceSound::ResourceSound()
: ResourceSoundBase()
{
}

ResourceSound::~ResourceSound()
{
}

int ResourceSound::SetPlaySound(std::string fileName, int handle, bool fixedVolumeFlag, int volume)
{
	SetHandleFlag(RESOURCE_SOUND_HANDLE_FLAG_SETTING_TYPE::SOUND_PLAY);
	int soundHandle = mclHandleContainer.RegisterHandle(DuplicateSoundMem(handle), fileName, false);

	if (fixedVolumeFlag)
	{

		ChangeVolumeSoundMem(volume, soundHandle);
		mnFixedVolumeHandle.push_back(soundHandle);
	}
	else
	{
		ChangeVolumeSoundMem(mnSoundVolume, soundHandle);
	}

	PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK, TRUE);

	return soundHandle;
}

// サウンド再生　
int ResourceSound::SetPlaySound_FindFileName(int handle, bool fixedVolumeFlag, int volume)
{
	std::string fileName = "";
	for (auto& handleMap : mclHandleContainer.GetHandleMap())
	{
		if (handleMap.second[0] == handle)
		{
			fileName = handleMap.first;
			break;
		}
	}
	if (fileName == "")
	{
		Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::RESOURCE_FLAG);
		return -1;
	}
	return SetPlaySound(fileName, handle, fixedVolumeFlag, volume);
}

ResourceBackSound::ResourceBackSound()
: ResourceSoundBase()
, mnNowBackSound(-1)
{
}

ResourceBackSound::~ResourceBackSound()
{
}

void ResourceBackSound::SoundUpdate()
{
	if (mnPreSoundVolume != mnSoundVolume)
	{
		ChangeVolumeSoundMem(mnSoundVolume, mnNowBackSound);
	}
}

void ResourceBackSound::SetPlayBackSound(std::string fileName)
{
	if (mclHandleContainer.GetHandleMap()[fileName].empty())
	{
		return;
	}
	SetHandleFlag(RESOURCE_SOUND_HANDLE_FLAG_SETTING_TYPE::SOUND_PLAY);
	StopSoundMem(mnNowBackSound);

	mnNowBackSound = mclHandleContainer.GetHandleMap()[fileName][0];

	PlaySoundMem(mnNowBackSound, DX_PLAYTYPE_LOOP, TRUE);
}

Resource3DSound::Resource3DSound()
: ResourceSoundBase()
{
}

Resource3DSound::~Resource3DSound()
{
}

int Resource3DSound::SetPlay3DSound(std::string fileName, int handle, VECTOR position, float Radius, bool fixedVolumeFlag, int volume)
{
	SetHandleFlag(RESOURCE_SOUND_HANDLE_FLAG_SETTING_TYPE::SOUND_PLAY);
	SetCreate3DSoundFlag(TRUE);	
	int soundHandle = mclHandleContainer.RegisterHandle(DuplicateSoundMem(handle), fileName, false);

	Set3DPositionSoundMem(position, soundHandle);
	Set3DRadiusSoundMem(Radius, soundHandle);

	if (fixedVolumeFlag)
	{

		ChangeVolumeSoundMem(volume, soundHandle);
		mnFixedVolumeHandle.push_back(soundHandle);
	}
	else
	{
		ChangeVolumeSoundMem(mnSoundVolume, soundHandle);
	}

	PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK, TRUE);

	SetCreate3DSoundFlag(FALSE);

	return soundHandle;
}
int Resource3DSound::SetPlay3DSound_FindFileName(int handle, VECTOR position, float Radius, bool fixedVolumeFlag, int volume)
{
	std::string fileName = "";
	for (auto& handleMap : mclHandleContainer.GetHandleMap())
	{
		if (handleMap.second[0] == handle)
		{
			fileName = handleMap.first;
			break;
		}
	}
	if (fileName == "")
	{
		Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::RESOURCE_FLAG);
		return -1;
	}
	return SetPlay3DSound(fileName, handle, position, Radius, fixedVolumeFlag, volume);
}