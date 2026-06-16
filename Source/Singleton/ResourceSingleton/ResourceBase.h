#pragma once
#include <map>
#include <string>

#include "HandleContainer.h"

template<typename QUOTE_SOURCE>
class ResourceBase
{
private:
    // ハンドルコンテナ
    HandleContainer<QUOTE_SOURCE>* mpHandleContainer;

    // 処理別設定ハンドルフラグ
    std::map<std::string, HANDLE_FLAG> mmSettingHandleFlagByProcess; 

public:
    ResourceBase() = default;
    virtual ~ResourceBase() = default;

    /// <summary>初期化</summary>
    virtual void Initilize() = 0;
    /// <summary>終了</summary>
    virtual void Finalize() = 0;

    /// <summary>リソース生成</summary>// TODO: 生成で複製をやる
    QUOTE_SOURCE ResourceGeneration(std::string fileName) = 0;
    /// <summary>リソース複製</summary>
    QUOTE_SOURCE ResourceDuplication(std::string fileName) = 0;
    /// <summary>リソース削除</summary>
    QUOTE_SOURCE ResourceDelete(int handle) = 0;

    /// <summary>リソースハンドル取得</summary>
	virtual QUOTE_SOURCE GetResourceHandle(std::string fileName)
    {
        if (container->CheckFileName(fileName))
        {
            return container->ResourceDuplication(ResourceDuplication(fileName));
        }

        return container->RegisterHandle(ResourceGeneration(fileName));
    }

	/// <summary>リソースカウントを減らす</summary>
	virtual void ReduceResourceHandle(QUOTE_SOURCE handle)
    {
        container->SetHandleFlag(mmSettingHandleFlagByProcess["Reduce"]);

        std::vector<int> deleteHandles = container->DeleteHandle(handle);

        for (int handle : deleteHandles)
        {
            ResourceDelete(handle);
        }
    }
};