#pragma once
#include <string>

#include "ResourceBase.h"

class Resource3DModel : public ResourceBase<int>
{
public:
	Resource3DModel();
	~Resource3DModel();

	void Initilize();
	void Finalize() override;

private:
    /// <summary>リソース本体作成</summary>
    int CreateResource(const std::string& fileName, void* plusData = nullptr) override;
    /// <summary>リソース複製</summary>
    int ResourceDuplication(const std::string& fileName, void* plusData = nullptr) override;
    /// <summary>リソース削除</summary>
    void ResourceDelete(const std::vector<int>& handles) override;
};
