#pragma once
#include <string>

#include "HandleContainer.h"

class Resource3DModel
{
private:
	HandleContainer<std::string>* mp3DModelHandleContainer;

public:
	Resource3DModel();
	~Resource3DModel();

	void Initilize();
	void Finalize();

	int GetModelHandle(std::string fileName);
	void ReduceModelHandle(int handle);
	void DrawModelHandle(int modelHandle);
};
