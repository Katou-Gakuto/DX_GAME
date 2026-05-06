#pragma once
#include <map>
#include <string>
#include <vector>

#include "Master.h"

#include "EndManager.h"

#ifdef _DEBUG
#include "DebugLogs/DebugLog.h"
#endif

enum class HANDLE_FLAG
{
    NONE = 0,
    ZERO_LOOK,
    ZERO_EXCEPT_LOOK,
};

// TODO: 交換とswitchで似た処理を関数化する
template<typename QUOTE_SOURCE>
class HandleContainer
{
private:
    // ハンドル
    std::map<QUOTE_SOURCE, std::vector<int>> mmHandles;

    // カウント
    std::map<int, int> mmHandleCounts;

    // 次のハンドル追加ファイル
    QUOTE_SOURCE msRegisterFileName;

    // ハンドルフラグ
    HANDLE_FLAG meHandleFlag;

public:
    HandleContainer()
    : msRegisterFileName()
    , meHandleFlag(HANDLE_FLAG::NONE)
    {
        mmHandles.clear();
        mmHandleCounts.clear();
    }

    ~HandleContainer()
    {
        mmHandles.clear();
        mmHandleCounts.clear();
    }

    /*--------*/
    /*【取得】*/
    /*--------*/
    /// <summary>ハンドルファイル名取得</summary>
    QUOTE_SOURCE GetHandleQuoteSource(int handle)
    {
        for (std::pair<QUOTE_SOURCE, std::vector<int>> chaeckHandle : mmHandles)
        {
            for (int i = 0; i < chaeckHandle.second.size(); i++)
            {
                if (chaeckHandle.second[i] == handle)
                {
                    return chaeckHandle.first;
                }
            }
        }

        QUOTE_SOURCE null;
        return null;
    }

    /// <summary>ハンドル取得</summary>
    std::vector<int> GetHandles(QUOTE_SOURCE fileName) { return mmHandles[fileName]; }

    /// <summary>ハンドルマップ取得</summary>
    std::map<QUOTE_SOURCE, std::vector<int>> GetHandleMap() { return mmHandles; }

    /// <summary>ハンドルマップポインタ取得</summary>
    std::map<QUOTE_SOURCE, std::vector<int>>* GetHandleMapPointer() { return &mmHandles; }

    /// <summary>ハンドルカウント取得</summary>
    int GetHandleCount(int handle) { return mmHandleCounts[handle]; }
    
    /// <summary>ハンドルカウントマップ取得</summary>
    std::map<int, int> GetHandleCountMap() const { return mmHandleCounts; }

    /*--------*/
    /*【設定】*/
    /*--------*/
    /// <summary>ハンドルフラグ設定</summary>
    inline void SetHandleFlag(HANDLE_FLAG handleFlag) { meHandleFlag = handleFlag; }

    /*--------*/
    /*【追加】*/
    /*--------*/
    /// <summary>同名のファイルがあるかを確認する</summary>
    bool CheckFileName(QUOTE_SOURCE fileName)
    {
        msRegisterFileName = fileName;

        return mmHandles.find(fileName) != mmHandles.end();
    }

    /// <summary>ハンドルを登録する</summary>
    int RegisterHandle(int handle, bool countFlag = true)
    {
        // ハンドルが-1なら実行を終了させる
        if (handle == (-1))
        {
            Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::HANDLE_FLAG);
            return -1;
        }

        // 設定されたファイル名が使われていないなら新しく設定する
        if (mmHandles.find(msRegisterFileName) == mmHandles.end())
        {
            std::vector<int> enptyHandleList;
            enptyHandleList.clear();
            mmHandles[msRegisterFileName] = enptyHandleList;
            
            mmHandleCounts[handle] = 0;
        }
        switch (meHandleFlag)
        {
        case HANDLE_FLAG::ZERO_LOOK:
            // 返すハンドルを設定する
            if (mmHandles[msRegisterFileName].size() <= 0)
            {
                mmHandles[msRegisterFileName].push_back(handle);
            }
            else
            {
                handle = mmHandles[msRegisterFileName][0];
            }
            break;

        case HANDLE_FLAG::ZERO_EXCEPT_LOOK:
        default:
            // ハンドルを追加する
            mmHandles[msRegisterFileName].push_back(handle);
        break;
        }

        // カウントフラグが「true」ならカウントを増やす
        if (countFlag)
        {
            mmHandleCounts[mmHandles[msRegisterFileName][0]] += 1;
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

        return handle;
    }

    /// <summary>ハンドルを登録する</summary>
    int RegisterHandle(int handle, QUOTE_SOURCE fileName, bool countFlag = true)
    {
        msRegisterFileName = fileName;

        return RegisterHandle(handle, countFlag);
    }

    /*--------*/
    /*【削除】*/
    /*--------*/
    /// <summary>ハンドル削除</summary>
    std::vector<int> DeleteHandle(int handle, bool countFlag = true)
    {
        if (handle == -1)
        {
            return {};
        }

        // HACK: 変数名紛らわしいから変更
        for (auto myHandle : mmHandles)
        {
            for (int i = 0; i < myHandle.second.size(); i++)
            {
                switch (meHandleFlag)
                {
                case HANDLE_FLAG::ZERO_LOOK:
                    // 0以外なら何もしない
                    if (i != 0)
                    {
                        i = myHandle.second.size();
                        break;
                    }
                    
                    // 指定のハンドルと比較する
                    if (myHandle.second[i] == handle)
                    { 
                        // カウント減少
                        int countHandle = mmHandles[myHandle.first][0];
                        if (countFlag && (mmHandleCounts.find(countHandle) != mmHandleCounts.end()))
                        {
                            mmHandleCounts[countHandle] -= 1;
                        }

                        // 削除ハンドル
                        std::vector<int> deleteHandles;
                        deleteHandles.clear();

                        if (mmHandleCounts[countHandle] <= 0)
                        {
                            // 削除予定のハンドルを全取得
                            deleteHandles = mmHandles[myHandle.first];

                            // カウントが0以下なためハンドルとカウント削除
                            mmHandles.erase(myHandle.first);
                            mmHandleCounts.erase(countHandle);
                        }

                        return deleteHandles;
                    }

                    break;

                case HANDLE_FLAG::ZERO_EXCEPT_LOOK:
                    // 0なら何もしない
                    if (i == 0)
                    {
                        break;
                    }

                    // 指定のハンドルと比較する
                    if (myHandle.second[i] == handle)
                    {
                        // カウント減少
                        int countHandle = mmHandles[myHandle.first][0];
                        if (countFlag && (mmHandleCounts.find(countHandle) != mmHandleCounts.end()))
                        {
                            mmHandleCounts[countHandle] -= 1;
                        }

                        // 削除ハンドル
                        std::vector<int> deleteHandles;
                        deleteHandles.clear();

                        if (mmHandleCounts[countHandle] <= 0)
                        {
                            // 削除予定のハンドルを全取得
                            deleteHandles = mmHandles[myHandle.first];

                            // カウントが0以下なためハンドルとカウント削除
                            mmHandles.erase(myHandle.first);
                            mmHandleCounts.erase(countHandle);
                        }
                        else
                        {
                            // 削除予定のハンドルを保存
                            deleteHandles.push_back(mmHandles[myHandle.first][i]);

                            // ハンドル削除					
                            mmHandles[myHandle.first].erase(mmHandles[myHandle.first].begin() + i);
                        }

                        return deleteHandles;
                    }
                    break;

                default:
                    // 指定のハンドルと比較する
                    if (myHandle.second[i] == handle)
                    {
                        // カウント減少
                        int countHandle = mmHandles[myHandle.first][0];
                        if (countFlag && (mmHandleCounts.find(countHandle) != mmHandleCounts.end()))
                        {
                            mmHandleCounts[countHandle] -= 1;
                        }

                        // 削除ハンドル
                        std::vector<int> deleteHandles;
                        deleteHandles.clear();

                        if (mmHandleCounts[countHandle] <= 0)
                        {
                            // 削除予定のハンドルを全取得
                            deleteHandles = mmHandles[myHandle.first];

                            // カウントが0以下なためハンドルとカウント削除
                            mmHandles.erase(myHandle.first);
                            mmHandleCounts.erase(countHandle);
                        }
                        else
                        {
                            // 削除予定のハンドルを保存
                            deleteHandles.push_back(mmHandles[myHandle.first][i]);

                            // ハンドル削除					
                            mmHandles[myHandle.first].erase(mmHandles[myHandle.first].begin() + i);

                            // カウントが参照しているハンドルなら入れ替える
                            if (i == 0)
                            {
                                mmHandleCounts[mmHandles[myHandle.first][0]] = mmHandleCounts[countHandle];
                                mmHandleCounts.erase(countHandle);
                            }
                        }

                        // 削除したハンドルを返す
                        return deleteHandles;
                    }
                    break;
                }
            }
        }

        

#ifdef _DEBUG
    //Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::HANDLE_FLAG);
    DEBUG::SaveText("\nハンドル未発見 : " + std::to_string(handle) + " <= ", DEBUG::DEBUG_MAP_TYPE::DEBUG_UNDISCOVERED);
#endif

        return {};
        /*
        
        for (auto movieHandle : mmMovieHandle)
        {
            for (int i = 0; i < movieHandle.second.size(); i++)
            {
                if (movieHandle.second[i] == handle)
                {
                    if ((movieHandle.second.size() - 1) <= 0)
                    {
                        mmMovieHandle.erase(movieHandle.first);
                    }
                    else
                    {
                        mmMovieHandle[movieHandle.first].erase(mmMovieHandle[movieHandle.first].begin() + i);
                    }
                    return;
                }
            }
        }
        */
    }

    /*--------*/
    /*【交換】*/
    /*--------*/
    /// <summary>ハンドルの値を交換する</summary>
    void SwapHandle(int srcHandle, int destHandle)
    {
    }
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