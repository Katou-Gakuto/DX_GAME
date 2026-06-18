#pragma once
#include <string>

#include "HandleContainer.h"
#include "ResourceBase.h"
#include "UtilCalc.h"

class ResourceGraph;

class ResourceEffect : public ResourceBase<int>
{
private:
	bool mbEffectDrawFlag;
	int mnEffectDrawPreHandle;

public:
	ResourceEffect();
	~ResourceEffect();

	void Initilize(ResourceGraph* graph, const std::string& resourceFile);
	void Finalize();

	int GetEffectResource(std::string fileName, float size = 1.0f);
	int GetEffectHandle(int handle, int oldHandle);
	void DeletePlayEffectHandle(int handle);
	void ReduceEffectDataHandle(int handle);

	void DrawEffect(int handle, VECTOR position, VECTOR angle = UtilCalc::VZero, VECTOR size = UtilCalc::VOne);
	void StopEffect(int handle);
	void PlayEffect(int handle, float speed);
	void StopAllEfect();
	void PlayAllEfect();

	void EffectDrawProcess();
	void EffectDrawFlagReset();
};
