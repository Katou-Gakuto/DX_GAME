#pragma once
#include <string>

#include "DxLib.h"
#include "HandleContainer.h"

class DataManager;

class ResourceSound
{
private:
	DataManager* mpDataManager;

	HandleContainer<std::string>* mpSoundHandleContainer;
	HandleContainer<int>* mpPlaySoundHandleContainer;
	int mnSoundVolume;

	HandleContainer<std::string>* mp3DSoundHandleContainer;
	HandleContainer<int>* mpPlay3DSoundHandleContainer;
	int mn3DSoundVolume;

	int mnPlayBackSoundHandle = -1;
	int mnBackSoundVolume = -1;

public:
	ResourceSound();
	~ResourceSound();

	void Initilize(DataManager* dataManager);
	void Finalize();

	int GetSoundHandle(std::string fileName);
	void ReduceSoundHandle(int handle);

	int Get3DSoundHandle(std::string fileName);
	void Reduce3DSoundHandle(int handle);

	void SetBackSoundHandle(int handle);
	void SoundUpdate();

	void SetPlaySound(int handle, int volume = -1);
	void SetPlay3DSound(int handle, VECTOR position, int volume = -1);
	void Set3DListenerPosition(VECTOR position, VECTOR frontPosition);
};
