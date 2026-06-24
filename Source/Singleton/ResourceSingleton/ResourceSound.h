#pragma once
#include <string>
#include <vector>

#include "DxLib.h"

#include "ResourceBase.h"

class DataManager;

class ResourceSoundBase : public ResourceBase<int>
{
protected:
	enum RESOURCE_SOUND_HANDLE_FLAG_SETTING_TYPE
	{
		SOUND_PLAY = RESOURCE_BASE_HANDLE_FLAG_SETTING_TYPE::RESOURCE_BASE_HANDLE_FLAG_TYPE_MAX,
		SOUND_UPDATE,
	};

	int mnSoundVolume;
	int mnPreSoundVolume;
	 
	std::vector<int> mnFixedVolumeHandle;

	// HandleContainer<std::string>* mpSoundHandleContainer;
	// HandleContainer<int>* mpPlaySoundHandleContainer;

	// HandleContainer<std::string>* mp3DSoundHandleContainer;
	// HandleContainer<int>* mpPlay3DSoundHandleContainer;
	// int mn3DSoundVolume;


public:
	ResourceSoundBase();
	~ResourceSoundBase();

	void Initilize();
	void Finalize() override;

	virtual void SoundUpdate();

	void DownSoundVolume(int number) { mnSoundVolume -= number; if (mnSoundVolume < 0) { mnSoundVolume = 0; } }		// サウンド音量ダウン
	void UpSoundVolume(int number) { mnSoundVolume += number; if (mnSoundVolume > 255) { mnSoundVolume = 255; } }	// サウンド音量アップ

	int GetSoundVolume() { return mnSoundVolume; }

private:
    /// <summary>リソース本体作成</summary>
    int CreateResource(const std::string& fileName, void* plusData = nullptr) override;
    /// <summary>リソース複製</summary>
    int ResourceDuplication(const std::string& fileName, void* plusData = nullptr) override;
    /// <summary>リソース削除</summary>
    void ResourceDelete(const std::vector<int>& handles) override;
};

class ResourceSound : public ResourceSoundBase
{
public:
	ResourceSound();
	~ResourceSound();

	int SetPlaySound(std::string fileName, int handle, bool fixedVolumeFlag = false, int volume = -1);
	int SetPlaySound_FindFileName(int handle, bool fixedVolumeFlag = false, int volume = -1);
};

class ResourceBackSound : public ResourceSoundBase
{
private:
	int mnNowBackSound;
public:
	ResourceBackSound();
	~ResourceBackSound();

	void SoundUpdate() override;

	void SetPlayBackSound(std::string fileName);
};

class Resource3DSound : public ResourceSoundBase
{
public:
	Resource3DSound();
	~Resource3DSound();

	int SetPlay3DSound(std::string fileName, int handle, VECTOR position, float Radius = 2000.0f, bool fixedVolumeFlag = false, int volume = -1);
	int SetPlay3DSound_FindFileName(int handle, VECTOR position, float Radius = 2000.0f, bool fixedVolumeFlag = false, int volume = -1);
	/// <summary>
	/// 3Dのリスナー位置を設定
	/// </summary>
	/// <param name="position">現在地</param>
	/// <param name="frontPosition">向いてる方向</param>
	inline void Set3DListenerPosition(VECTOR position, VECTOR frontPosition) { Set3DSoundListenerPosAndFrontPos_UpVecY(position, frontPosition); }
};