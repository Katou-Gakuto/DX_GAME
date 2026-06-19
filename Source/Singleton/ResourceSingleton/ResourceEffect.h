#pragma once
#include <string>

#include "HandleContainer.h"
#include "ResourceBase.h"
#include "UtilCalc.h"

template<typename HANDLE_TYPE = int>
class ResourceGraph;

class ResourceEffect : public ResourceBase<int>
{
private:
	bool mbEffectDrawFlag;
	int mnEffectDrawPreHandle;

public:
	ResourceEffect();
	~ResourceEffect();

	void Initilize(ResourceGraph<int>* graph, const std::string& resourceFile);
	void Finalize() override;

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

protected:

    /// <summary>リソース本体作成</summary>
    virtual HANDLE_TYPE CreateResource(const QUOTE_SOURCE& fileName) = 0;
    /// <summary>リソース複製</summary>
    virtual HANDLE_TYPE ResourceDuplication(const QUOTE_SOURCE& fileName) = 0;
    /// <summary>リソース削除</summary>
    virtual void ResourceDelete(HANDLE_TYPE handle) = 0;
};
