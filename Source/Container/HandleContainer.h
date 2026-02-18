#pragma once
#include <map>
#include <string>
#include <vector>

#include "HandleContainer.h"

enum class HANDLE_FLAG
{
    NONE = 0,
    ZERO_LOOK,
    ZERO_EXCEPT_LOOK,
};

// TODO: 交換とswitchで似た処理を関数化する
class HandleContainer
{
private:
    // ハンドル
    std::map<std::string, std::vector<int>> mmHandles;

    // カウント
    std::map<int, int> mmHandleCounts;

    // 次のハンドル追加ファイル
    std::string msRegisterFileName;

    // ハンドルフラグ
    HANDLE_FLAG meHandleFlag;

public:
    HandleContainer();
    ~HandleContainer();

    /*--------*/
    /*【取得】*/
    /*--------*/
    /// <summary>ハンドルファイル名取得</summary>
    std::string GetHandleFileName(int handle);

    /// <summary>ハンドル取得</summary>
    std::vector<int> GetHandles(std::string fileName) { return mmHandles[fileName]; }

    /// <summary>ハンドルマップ取得</summary>
    std::map<std::string, std::vector<int>> GetHandleMap() { return mmHandles; }

    /// <summary>ハンドルカウント取得</summary>
    int GetHandleCount(int handle) { return mmHandleCounts[handle]; }

    /*--------*/
    /*【設定】*/
    /*--------*/
    /// <summary>ハンドルフラグ設定</summary>
    inline void SetHandleFlag(HANDLE_FLAG handleFlag) { meHandleFlag = handleFlag; }

    /*--------*/
    /*【追加】*/
    /*--------*/
    /// <summary>同名のファイルがあるかを確認する</summary>
    bool CheckFileName(std::string fileName);

    /// <summary>ハンドルを登録する</summary>
    int RegisterHandle(int handle, bool countFlag = true);
    /// <summary>ハンドルを登録する</summary>
    int RegisterHandle(int handle, std::string fileName, bool countFlag = true);

    /*--------*/
    /*【削除】*/
    /*--------*/
    /// <summary>ハンドル削除</summary>
    std::vector<int> DeleteHandle(int handle, bool countFlag = true);

    /*--------*/
    /*【交換】*/
    /*--------*/
    /// <summary>ハンドルの値を交換する</summary>
};

/*
ハンドルマネージャーメモ

カウント

作成予定関数

全部 0だけ見るもしくは見ないのも作る

【追加】
string走査&次の追加予定物にする

追加(同じのがある場合は何もしない　カウントに追加するフラグを設定
-1が来たら終了
追加したハンドルを返す

stringを設定してから追加するのも作る


【削除】

削除
カウント探してなければハンドルの方を探す　カウントを減らすフラグ設定
削除したハンドルを返す
*/