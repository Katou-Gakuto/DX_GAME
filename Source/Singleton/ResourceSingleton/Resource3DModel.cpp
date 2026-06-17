#include "Resource3DModel.h"

#include "DxLib.h"

#ifdef _DEBUG
#include "DebugLogs/DebugLog.h"
#endif

Resource3DModel::Resource3DModel()
: mp3DModelHandleContainer(nullptr)
{
}

Resource3DModel::~Resource3DModel()
{
}

void Resource3DModel::Initilize()
{
	mp3DModelHandleContainer = new HandleContainer<std::string>();
}

void Resource3DModel::Finalize()
{
	MV1InitModel();
	delete mp3DModelHandleContainer;
	mp3DModelHandleContainer = nullptr;
}

int Resource3DModel::GetModelHandle(std::string fileName)
{
	int handle = -1;
	if (mp3DModelHandleContainer->CheckFileName(fileName))
	{
		handle = mp3DModelHandleContainer->GetHandles(fileName)[0];

		mp3DModelHandleContainer->SetHandleFlag(HANDLE_FLAG::ZERO_EXCEPT_LOOK);
#ifdef _DEBUG
		int resultHandle = mp3DModelHandleContainer->RegisterHandle(MV1DuplicateModel(handle));
		DEBUG::SaveText("モデルハンドル取得 : " + fileName + " : " + std::to_string(resultHandle) + '\n', DEBUG::DEBUG_MAP_TYPE::DEBUG_3D_MODEL);
		return resultHandle;
#endif
		return mp3DModelHandleContainer->RegisterHandle(MV1DuplicateModel(handle));
	}

	mp3DModelHandleContainer->SetHandleFlag(HANDLE_FLAG::ZERO_LOOK);
	handle = mp3DModelHandleContainer->RegisterHandle(MV1LoadModel(fileName.c_str()), false);
#ifdef _DEBUG
	DEBUG::SaveText("モデルハンドル(原本)取得 : " + fileName + " : " + std::to_string(handle) + '\n', DEBUG::DEBUG_MAP_TYPE::DEBUG_3D_MODEL);
#endif

	mp3DModelHandleContainer->SetHandleFlag(HANDLE_FLAG::ZERO_EXCEPT_LOOK);
#ifdef _DEBUG
	handle = mp3DModelHandleContainer->RegisterHandle(MV1DuplicateModel(handle));
	DEBUG::SaveText("モデルハンドル(一つ目)取得 : " + fileName + " : " + std::to_string(handle) + '\n', DEBUG::DEBUG_MAP_TYPE::DEBUG_3D_MODEL);
	return handle;
#endif
	return mp3DModelHandleContainer->RegisterHandle(MV1DuplicateModel(handle));
}

void Resource3DModel::ReduceModelHandle(int handle)
{
	mp3DModelHandleContainer->SetHandleFlag(HANDLE_FLAG::ZERO_EXCEPT_LOOK);
	std::vector<int> deleteHnadle = mp3DModelHandleContainer->DeleteHandle(handle);

#ifdef _DEBUG
	std::string text = "モデルハンドル削除 : " + std::to_string(handle) + "(NOT_DELETE)";
	for (int i = 0; i < deleteHnadle.size(); i++)
	{
		text = text + " : " + std::to_string(deleteHnadle[i]);
	}
	text = text + '\n';
	DEBUG::SaveText(text, DEBUG::DEBUG_MAP_TYPE::DEBUG_3D_MODEL);
#endif

	for (int i = 0; i < deleteHnadle.size(); i++)
	{
		MV1DeleteModel(deleteHnadle[i]);
	}
}

void Resource3DModel::DrawModelHandle(int modelHandle)
{
	MV1DrawModel(modelHandle);
}
