#include "HandleContainer.h"
#include "ResourceBase.h"
#include "Resource3DModel.h"

#include "DxLib.h"

#ifdef _DEBUG
#include "DebugLogs/DebugLog.h"
#endif

Resource3DModel::Resource3DModel()
{
}

Resource3DModel::~Resource3DModel()
{
}

void Resource3DModel::Initilize()
{
	mmSettingHandleFlagByProcess[RESOURCE_BASE_HANDLE_FLAG_SETTING_TYPE::GENERATION_RESOURCE]  = HANDLE_FLAG::ZERO_LOOK;
	mmSettingHandleFlagByProcess[RESOURCE_BASE_HANDLE_FLAG_SETTING_TYPE::DUPLICATION_RESOURCE] = HANDLE_FLAG::ZERO_EXCEPT_LOOK;
	mmSettingHandleFlagByProcess[RESOURCE_BASE_HANDLE_FLAG_SETTING_TYPE::REDUCE_RESOURCE]      = HANDLE_FLAG::ZERO_EXCEPT_LOOK;
}

void Resource3DModel::Finalize()
{
	MV1InitModel();
}

// リソース本体作成
int Resource3DModel::CreateResource(const std::string& fileName, int* plusData)
{
	return MV1LoadModel(fileName.c_str());
}

// リソース複製
int Resource3DModel::ResourceDuplication(const std::string& fileName, int* plusData)
{
	SetHandleFlag(RESOURCE_BASE_HANDLE_FLAG_SETTING_TYPE::DUPLICATION_RESOURCE);

	int handle = mclHandleContainer.GetHandles(fileName)[0];
	return MV1DuplicateModel(handle);
}

// リソース削除
void Resource3DModel::ResourceDelete(const std::vector<int>& handles)
{
	for (int i = 0; i < handles.size(); i++)
	{
		MV1DeleteModel(handles[i]);
	}
}