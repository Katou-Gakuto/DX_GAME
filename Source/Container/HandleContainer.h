#pragma once
#include <map>
#include <string>
#include <vector>

#include "HandleContainer.h"

// INPROGRESS: 作業中　メモ　

class HandleContainer
{
private:
    // ハンドル
    std::map<std::string, std::vector<int>> mmHandle;

    // カウント
    std::map<int, int> mmHandleCount;

    // 次のハンドル追加ファイル
    std::string msRegisterFileName;

    // 0関係確認フラグ
    char mbZeroCheckFlag;

public:
    HandleContainer();
    ~HandleContainer();

    /*--------*/
    /*【追加】*/
    /*--------*/
    /// <summary>同名のファイルがあるかを確認する</summary>
    bool CheckFileName(std::string fileName);

    /// <summary>ハンドルを登録する</summary>
    int RegisterHandle(bool countFlag = true);
    /// <summary>ハンドルを登録する</summary>
    int RegisterHandle(std::string fileName, bool countFlag = true);

    /*--------*/
    /*【削除】*/
    /*--------*/
    /// <summary>ハンドル削除</summary>
    int DeleteHandle(int handle, bool countFlag = true);
};