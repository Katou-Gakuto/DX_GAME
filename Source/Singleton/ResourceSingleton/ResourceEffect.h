#pragma once
#include <string>

#include "HandleContainer.h"
#include "ResourceBase.h"
#include "UtilCalc.h"

class ResourceGraph;

class ResourceEffect : public ResourceBase<int, std::string, float>
{
private:

	enum RESOURCE_EFFECT_HANDLE_FLAG_SETTING_TYPE
	{
		EFFECT_HANDLE = RESOURCE_BASE_HANDLE_FLAG_SETTING_TYPE::RESOURCE_BASE_HANDLE_FLAG_TYPE_MAX,
		DELETE_EFFECT_HANDLE,
	};

	bool mbEffectDrawFlag;
	int mnEffectDrawPreHandle;

public:
	ResourceEffect();
	~ResourceEffect();

	void Initilize(ResourceGraph* graph, const std::string& resourceFile);
	void Finalize() override;

	int GetEffectHandle(int handle, int oldHandle);
	void DeletePlayEffectHandle(int handle);

	void DrawEffect(int handle, VECTOR position, VECTOR angle = UtilCalc::VZero, VECTOR size = UtilCalc::VOne);
	void StopEffect(int handle);
	void PlayEffect(int handle, float speed);
	void StopAllEfect();
	void PlayAllEfect();

	void EffectDrawProcess();
	void EffectDrawFlagReset();

protected:

    /// <summary>リソース本体作成</summary>
    int CreateResource(const std::string& fileName, float* plusData) override;
    /// <summary>リソース複製</summary>
    int ResourceDuplication(const std::string& fileName, float* plusData) override;
    /// <summary>リソース削除</summary>
    void ResourceDelete(const std::vector<int>& handles) override;
};
