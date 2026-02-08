#include "Master.h"

#include "EndManager.h"
#include "HandleContainer.h"

// コンストラクタ
HandleContainer::HandleContainer()
: msRegisterFileName("")
{
    meHandleFlag = HANDLE_FLAG::NONE;
    mmHandle.clear();
    mmHandleCount.clear();
}

// デストラクタ
HandleContainer::~HandleContainer()
{
}

/*--------*/
/*【追加】*/
/*--------*/
// 同名のファイルがあるかを確認する
bool HandleContainer::CheckFileName(std::string fileName)
{
    msRegisterFileName = fileName;

    return mmHandle.find(fileName) != mmHandle.end();
}

// ハンドルを登録する（デフォルト）
int HandleContainer::RegisterHandle(int handle, bool countFlag)
{
    if (handle == (-1))
    {
        Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::HANDLE_FLAG);
        return -1;
    }

    if (mmHandle.find(msRegisterFileName) == mmHandle.end())
    {
        std::vector<int> enptyHandleList;
        enptyHandleList.clear();
        mmHandle[msRegisterFileName] = enptyHandleList;
        
        mmHandleCount[handle] = 0;
    }
    mmHandle[msRegisterFileName].push_back(handle);
    if (countFlag)
    {
        mmHandleCount[mmHandle[msRegisterFileName][0]] += 1;
    }
    /*
    
	int handle = -1;
	if (mmModelHandle.find(fileName) != mmModelHandle.end())
	{
		handle = mmModelHandle[fileName][0];
		mmModelCount[handle] += 1;
		int resultHandle = MV1DuplicateModel(handle);
		mmModelHandle[fileName].push_back(resultHandle);
		return resultHandle;
	}

	handle = MV1LoadModel(fileName.c_str());
	if (handle == -1)
	{
		Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::RESOURCE_FLAG);
		return -1;
	}
	std::vector<int> setHandle;
	setHandle.clear();
	setHandle.reserve(2);
	setHandle.push_back(handle);
	setHandle.push_back(MV1DuplicateModel(handle));
	mmModelHandle[fileName] = setHandle;
	mmModelCount[handle] = 1;
    */

    return 0;
}

// ハンドルを登録する（ファイル名指定）
int HandleContainer::RegisterHandle(int handle, std::string fileName, bool countFlag)
{
    msRegisterFileName = fileName;

    return RegisterHandle(handle, countFlag);
}


/*--------*/
/*【削除】*/
/*--------*/
// ハンドル削除
int HandleContainer::DeleteHandle(int handle, bool countFlag)
{
    return 0;
}