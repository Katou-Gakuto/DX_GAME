#include "HandleContainer.h"

// コンストラクタ
HandleContainer::HandleContainer()
    : mbZeroCheckFlag(0)
{
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
    return mmHandle.find(fileName) != mmHandle.end();
}

// ハンドルを登録する（デフォルト）
int HandleContainer::RegisterHandle(bool countFlag)
{
    return 0;
}

// ハンドルを登録する（ファイル名指定）
int HandleContainer::RegisterHandle(std::string fileName, bool countFlag)
{
    return 0;
}


/*--------*/
/*【削除】*/
/*--------*/
// ハンドル削除
int HandleContainer::DeleteHandle(int handle, bool countFlag)
{
    return 0;
}