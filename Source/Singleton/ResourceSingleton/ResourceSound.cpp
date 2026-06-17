#include "ResourceSound.h"

#include "DataManager.h"

#ifdef _DEBUG
#include "DebugLogs/DebugLog.h"
#endif

ResourceSound::ResourceSound()
: mpDataManager(nullptr)
, mpSoundHandleContainer(nullptr)
, mpPlaySoundHandleContainer(nullptr)
, mnSoundVolume(-1)
, mp3DSoundHandleContainer(nullptr)
, mpPlay3DSoundHandleContainer(nullptr)
, mn3DSoundVolume(-1)
, mnPlayBackSoundHandle(-1)
, mnBackSoundVolume(-1)
{
}

ResourceSound::~ResourceSound()
{
}

void ResourceSound::Initilize(DataManager* dataManager)
{
	mpDataManager = dataManager;

	mpSoundHandleContainer = new HandleContainer<std::string>();
	mpSoundHandleContainer->SetHandleFlag(HANDLE_FLAG::ZERO_LOOK);
	mpPlaySoundHandleContainer = new HandleContainer<int>();
	mpPlaySoundHandleContainer->SetHandleFlag(HANDLE_FLAG::NONE);

	mp3DSoundHandleContainer = new HandleContainer<std::string>();
	mp3DSoundHandleContainer->SetHandleFlag(HANDLE_FLAG::ZERO_LOOK);
	mpPlay3DSoundHandleContainer = new HandleContainer<int>();
	mpPlay3DSoundHandleContainer->SetHandleFlag(HANDLE_FLAG::NONE);
}

void ResourceSound::Finalize()
{
	for (std::pair<std::string, std::vector<int>> soundHandle : mpSoundHandleContainer->GetHandleMap())
	{
		for (int i = 0; i < soundHandle.second.size(); i++)
		{
			DeleteSoundMem(soundHandle.second[i]);
#ifdef _DEBUG
			DEBUG::SaveText("サウンド(原本)ハンドル削除(最終) : " + std::to_string(soundHandle.second[i]) + " : " + soundHandle.first + " : HandleNumber <=" + std::to_string(mpSoundHandleContainer->GetHandleCount(soundHandle.second[i])) + '\n');
#endif
		}
	}
	delete mpSoundHandleContainer;
	mpSoundHandleContainer = nullptr;

	for (std::pair<int, std::vector<int>> playSoundHandle : mpPlaySoundHandleContainer->GetHandleMap())
	{
		for (int i = 0; i < playSoundHandle.second.size(); i++)
		{
			DeleteSoundMem(playSoundHandle.second[i]);
#ifdef _DEBUG
			DEBUG::SaveText("サウンドハンドル削除(最終) : " + std::to_string(playSoundHandle.second[i]) + " : " + std::to_string(playSoundHandle.first) + " : HandleNumber <=" + std::to_string(mpPlaySoundHandleContainer->GetHandleCount(playSoundHandle.second[i])) + '\n');
#endif
		}
	}
	delete mpPlaySoundHandleContainer;
	mpPlaySoundHandleContainer = nullptr;

	for (std::pair<std::string, std::vector<int>> sound3DHandle : mp3DSoundHandleContainer->GetHandleMap())
	{
		for (int i = 0; i < sound3DHandle.second.size(); i++)
		{
			DeleteSoundMem(sound3DHandle.second[i]);
#ifdef _DEBUG
			DEBUG::SaveText("3Dサウンド(原本)ハンドル削除(最終) : " + std::to_string(sound3DHandle.second[i]) + " : " + sound3DHandle.first + " : HandleNumber <=" + std::to_string(mp3DSoundHandleContainer->GetHandleCount(sound3DHandle.second[i])) + '\n');
#endif
		}
	}
	delete mp3DSoundHandleContainer;
	mp3DSoundHandleContainer = nullptr;

	for (std::pair<int, std::vector<int>> playSound3DHandle : mpPlay3DSoundHandleContainer->GetHandleMap())
	{
		for (int i = 0; i < playSound3DHandle.second.size(); i++)
		{
			DeleteSoundMem(playSound3DHandle.second[i]);
#ifdef _DEBUG
			DEBUG::SaveText("3Dサウンドハンドル削除(最終) : " + std::to_string(playSound3DHandle.second[i]) + " : " + std::to_string(playSound3DHandle.first) + " : HandleNumber <=" + std::to_string(mpPlay3DSoundHandleContainer->GetHandleCount(playSound3DHandle.second[i])) + '\n');
#endif
		}
	}
	delete mpPlay3DSoundHandleContainer;
	mpPlay3DSoundHandleContainer = nullptr;
}

int ResourceSound::GetSoundHandle(std::string fileName)
{
	if (mpSoundHandleContainer->CheckFileName(fileName))
	{
		return mpSoundHandleContainer->RegisterHandle(0);
	}

#ifdef _DEBUG
	int handle = mpSoundHandleContainer->RegisterHandle(LoadSoundMem(fileName.c_str()));
	DEBUG::SaveText("サウンドハンドル(原本)取得 : " + fileName + " : " + std::to_string(handle) + '\n');
	return handle;
#endif
	return mpSoundHandleContainer->RegisterHandle(LoadSoundMem(fileName.c_str()));
}

void ResourceSound::ReduceSoundHandle(int handle)
{
	std::vector<int> deleteHandle = mpSoundHandleContainer->DeleteHandle(handle);

#ifdef _DEBUG
	std::string text = "サウンドハンドル削除 : " + std::to_string(handle) + "(NOT_DELETE)";
	for (int i = 0; i < deleteHandle.size(); i++)
	{
		text = text + " : " + std::to_string(deleteHandle[i]);
	}
	text = text + '\n';
	DEBUG::SaveText(text);
#endif

	for (int i = 0; i < deleteHandle.size(); i++)
	{
		DeleteSoundMem(deleteHandle[i]);
	}
}

int ResourceSound::Get3DSoundHandle(std::string fileName)
{
	if (mp3DSoundHandleContainer->CheckFileName(fileName))
	{
		return mp3DSoundHandleContainer->RegisterHandle(0);
	}

	int handle = mp3DSoundHandleContainer->RegisterHandle(LoadSoundMem(fileName.c_str()));
#ifdef _DEBUG
	DEBUG::SaveText("3Dサウンドハンドル(原本)取得 : " + fileName + " : " + std::to_string(handle) + '\n');
#endif
	return handle;
}

void ResourceSound::Reduce3DSoundHandle(int handle)
{
	std::vector<int> deleteHandle = mp3DSoundHandleContainer->DeleteHandle(handle);

#ifdef _DEBUG
	std::string text = "3Dサウンドハンドル削除 : " + std::to_string(handle) + "(NOT_DELETE)";
	for (int i = 0; i < deleteHandle.size(); i++)
	{
		text = text + " : " + std::to_string(deleteHandle[i]);
	}
	text = text + '\n';
	DEBUG::SaveText(text);
#endif

	for (int i = 0; i < deleteHandle.size(); i++)
	{
		DeleteSoundMem(deleteHandle[i]);
	}
}

void ResourceSound::SetBackSoundHandle(int handle)
{
	if (mnPlayBackSoundHandle != -1)
	{
		StopSoundMem(mnPlayBackSoundHandle);
		DeleteSoundMem(mnPlayBackSoundHandle);
	}

	int backSoundHandle = DuplicateSoundMem(handle);

	ChangeVolumeSoundMem(mnBackSoundVolume, backSoundHandle);

	PlaySoundMem(backSoundHandle, DX_PLAYTYPE_LOOP, TRUE);

	mnPlayBackSoundHandle = backSoundHandle;
}

void ResourceSound::SoundUpdate()
{
	std::map<int, std::vector<int>>* playSoundHandleMap = mpPlaySoundHandleContainer->GetHandleMapPointer();
	std::map<int, std::vector<int>>* play3DSoundHandleMap = mpPlay3DSoundHandleContainer->GetHandleMapPointer();

	{
		if (mpDataManager->GetSeVolume() != mnSoundVolume)
		{
			mnSoundVolume = mpDataManager->GetSeVolume();
			for (std::pair<const int, std::vector<int>>& playSoundHandle : *playSoundHandleMap)
			{
				for (int i = 0; i < playSoundHandle.second.size(); i++)
				{
					ChangeVolumeSoundMem(mnSoundVolume, playSoundHandle.second[i]);
				}
			}
			for (std::pair<const int, std::vector<int>>& play3DSoundHandle : *play3DSoundHandleMap)
			{
				for (int i = 0; i < play3DSoundHandle.second.size(); i++)
				{
					ChangeVolumeSoundMem(mnSoundVolume, play3DSoundHandle.second[i]);
				}
			}
		}

		if (mpDataManager->GetBgmVolume() != mnBackSoundVolume)
		{
			mnBackSoundVolume = mpDataManager->GetBgmVolume();
			if (mnPlayBackSoundHandle != -1)
			{
				ChangeVolumeSoundMem(mnBackSoundVolume, mnPlayBackSoundHandle);
			}
		}
	}

	for (std::pair<int, std::vector<int>> playSoundHandle : *playSoundHandleMap)
	{
		for (int i = 0; i < playSoundHandle.second.size(); i++)
		{
			if (CheckSoundMem(playSoundHandle.second[i]) == 0)
			{
				StopSoundMem(playSoundHandle.second[i]);
				std::vector<int> deleteHandle = mpPlaySoundHandleContainer->DeleteHandle(playSoundHandle.second[i]);

#ifdef _DEBUG
				std::string text = "プレイサウンドハンドル削除 : " + std::to_string(playSoundHandle.second[i]) + "(NOT_DELETE)";
				for (int j = 0; j < deleteHandle.size(); j++)
				{
					text = text + " : " + std::to_string(deleteHandle[j]);
				}
				text = text + '\n';
				DEBUG::SaveText(text);
#endif
				DeleteSoundMem(playSoundHandle.second[i]);
			}
		}
	}
	for (std::pair<int, std::vector<int>> play3DSoundHandle : *play3DSoundHandleMap)
	{
		for (int i = 0; i < play3DSoundHandle.second.size(); i++)
		{
			if (CheckSoundMem(play3DSoundHandle.second[i]) == 0)
			{
				StopSoundMem(play3DSoundHandle.second[i]);
				std::vector<int> deleteHandle = mpPlay3DSoundHandleContainer->DeleteHandle(play3DSoundHandle.second[i]);

#ifdef _DEBUG
				std::string text = "プレイ3Dサウンドハンドル削除 : " + std::to_string(play3DSoundHandle.second[i]) + "(NOT_DELETE)";
				for (int j = 0; j < deleteHandle.size(); j++)
				{
					text = text + " : " + std::to_string(deleteHandle[j]);
				}
				text = text + '\n';
				DEBUG::SaveText(text);
#endif
				DeleteSoundMem(play3DSoundHandle.second[i]);
			}
		}
	}
}

void ResourceSound::SetPlaySound(int handle, int volume)
{
	int soundHandle = mpPlaySoundHandleContainer->RegisterHandle(DuplicateSoundMem(handle), handle);
#ifdef _DEBUG
	DEBUG::SaveText((std::string)"サウンドハンドル取得 : " + (std::string)"なし" + (std::string)" : " + std::to_string(soundHandle) + '\n');
#endif

	ChangeVolumeSoundMem(mnSoundVolume, soundHandle);

	PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK, TRUE);
}

void ResourceSound::SetPlay3DSound(int handle, VECTOR position, int volume)
{
	SetCreate3DSoundFlag(TRUE);

	int soundHandle = mpPlay3DSoundHandleContainer->RegisterHandle(DuplicateSoundMem(handle), handle);
#ifdef _DEBUG
	DEBUG::SaveText((std::string)"3Dサウンドハンドル取得 : " + (std::string)"なし" + (std::string)" : " + std::to_string(soundHandle) + '\n');
#endif

	Set3DPositionSoundMem(position, soundHandle);
	Set3DRadiusSoundMem(2000.0f, soundHandle);

	ChangeVolumeSoundMem(mnSoundVolume, soundHandle);

	PlaySoundMem(soundHandle, DX_PLAYTYPE_BACK, TRUE);

	SetCreate3DSoundFlag(FALSE);
}

void ResourceSound::Set3DListenerPosition(VECTOR position, VECTOR frontPosition)
{
	Set3DSoundListenerPosAndFrontPos_UpVecY(position, frontPosition);
}
