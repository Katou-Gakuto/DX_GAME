// #include <map>
// #include <string>
// #include <vector>

// #include "Master.h"

// #include "EndManager.h"
// #include "HandleContainer.h"


// // デストラクタ
// template<typename QUOTE_SOURCE>
// HandleContainer<QUOTE_SOURCE>::~HandleContainer()
// {
//     mmHandles.clear();
//     mmHandleCounts.clear();
// }

// /*--------*/
// /*【追加】*/
// /*--------*/
// // 同名のファイルがあるかを確認する
// template<typename QUOTE_SOURCE>
// bool HandleContainer<QUOTE_SOURCE>::CheckFileName(QUOTE_SOURCE fileName)
// {
//     msRegisterFileName = fileName;

//     return mmHandles.find(fileName) != mmHandles.end();
// }

// // ハンドルを登録する（デフォルト）
// template<typename QUOTE_SOURCE>
// int HandleContainer<QUOTE_SOURCE>::RegisterHandle(int handle, bool countFlag)
// {
// 	// ハンドルが-1なら実行を終了させる
//     if (handle == (-1))
//     {
//         Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::HANDLE_FLAG);
//         return -1;
//     }

// 	// 設定されたファイル名が使われていないなら新しく設定する
//     if (mmHandles.find(msRegisterFileName) == mmHandles.end())
//     {
//         std::vector<int> enptyHandleList;
//         enptyHandleList.clear();
//         mmHandles[msRegisterFileName] = enptyHandleList;
        
//         mmHandleCounts[handle] = 0;
//     }
// 	switch (meHandleFlag)
// 	{
// 	case HANDLE_FLAG::ZERO_LOOK:
// 		// 返すハンドルを設定する
// 		if (mmHandles[msRegisterFileName].size() <= 0)
// 		{
// 			mmHandles[msRegisterFileName].push_back(handle);
// 		}
// 		else
// 		{
// 			handle = mmHandles[msRegisterFileName][0];
// 		}
// 		break;

// 	case HANDLE_FLAG::ZERO_EXCEPT_LOOK:
// 	default:
// 		// ハンドルを追加する
// 		mmHandles[msRegisterFileName].push_back(handle);
// 	break;
// 	}

// 	// カウントフラグが「true」ならカウントを増やす
//     if (countFlag)
//     {
//         mmHandleCounts[mmHandles[msRegisterFileName][0]] += 1;
//     }
//     /*
    
// 	int handle = -1;
// 	if (mmModelHandle.find(fileName) != mmModelHandle.end())
// 	{
// 		handle = mmModelHandle[fileName][0];
// 		mmModelCount[handle] += 1;
// 		int resultHandle = MV1DuplicateModel(handle);
// 		mmModelHandle[fileName].push_back(resultHandle);
// 		return resultHandle;
// 	}

// 	handle = MV1LoadModel(fileName.c_str());
// 	if (handle == -1)
// 	{
// 		Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::RESOURCE_FLAG);
// 		return -1;
// 	}
// 	std::vector<int> setHandle;
// 	setHandle.clear();
// 	setHandle.reserve(2);
// 	setHandle.push_back(handle);
// 	setHandle.push_back(MV1DuplicateModel(handle));
// 	mmModelHandle[fileName] = setHandle;
// 	mmModelCount[handle] = 1;
//     */

//     return handle;
// }

// // ハンドルを登録する（ファイル名指定）
// template<typename QUOTE_SOURCE>
// int HandleContainer<QUOTE_SOURCE>::RegisterHandle(int handle, QUOTE_SOURCE fileName, bool countFlag)
// {
//     msRegisterFileName = fileName;

//     return RegisterHandle(handle, countFlag);
// }


// /*--------*/
// /*【削除】*/
// /*--------*/
// // ハンドル削除
// template<typename QUOTE_SOURCE>
// std::vector<int> HandleContainer<QUOTE_SOURCE>::DeleteHandle(int handle, bool countFlag)
// {
// 	// HACK: 変数名紛らわしいから変更
//     for (auto myHandle : mmHandles)
//     {
// 		for (int i = 0; i < myHandle.second.size(); i++)
// 		{
// 			switch (meHandleFlag)
// 			{
// 			case HANDLE_FLAG::ZERO_LOOK:
// 				// 0以外なら何もしない
// 				if (i != 0)
// 				{
// 					break;
// 				}
				
// 				// 指定のハンドルと比較する
// 				if (myHandle.second[i] == handle)
// 				{ 
// 					// カウント減少
// 					int countHandle = mmHandles[myHandle.first][0];
// 					if (countFlag && (mmHandleCounts.find(countHandle) != mmHandleCounts.end()))
// 					{
// 						mmHandleCounts[countHandle] -= 1;
// 					}

// 					// 削除ハンドル
// 					std::vector<int> deleteHandles;
// 					deleteHandles.clear();

// 					if (mmHandleCounts[countHandle] <= 0)
// 					{
// 						// 削除予定のハンドルを全取得
// 						deleteHandles = mmHandles[myHandle.first];

// 						// カウントが0以下なためハンドルとカウント削除
// 						mmHandles.erase(myHandle.first);
// 						mmHandleCounts.erase(countHandle);
// 					}

// 					return deleteHandles;
// 				}

// 				break;

// 			case HANDLE_FLAG::ZERO_EXCEPT_LOOK:
// 				// 0なら何もしない
// 				if (i == 0)
// 				{
// 					break;
// 				}

// 				// 指定のハンドルと比較する
// 				if (myHandle.second[i] == handle)
// 				{
// 					// カウント減少
// 					int countHandle = mmHandles[myHandle.first][0];
// 					if (countFlag && (mmHandleCounts.find(countHandle) != mmHandleCounts.end()))
// 					{
// 						mmHandleCounts[countHandle] -= 1;
// 					}

// 					// 削除ハンドル
// 					std::vector<int> deleteHandles;
// 					deleteHandles.clear();

// 					if (mmHandleCounts[countHandle] <= 0)
// 					{
// 						// 削除予定のハンドルを全取得
// 						deleteHandles = mmHandles[myHandle.first];

// 						// カウントが0以下なためハンドルとカウント削除
// 						mmHandles.erase(myHandle.first);
// 						mmHandleCounts.erase(countHandle);
// 					}
// 					else
// 					{
// 						// 削除予定のハンドルを保存
// 						deleteHandles.push_back(mmHandles[myHandle.first][i]);

// 						// ハンドル削除					
// 						mmHandles[myHandle.first].erase(mmHandles[myHandle.first].begin() + i);
// 					}

// 					return deleteHandles;
// 				}
// 				break;

// 			default:
// 				// 指定のハンドルと比較する
// 				if (myHandle.second[i] == handle)
// 				{
// 					// カウント減少
// 					int countHandle = mmHandles[myHandle.first][0];
// 					if (countFlag && (mmHandleCounts.find(countHandle) != mmHandleCounts.end()))
// 					{
// 						mmHandleCounts[countHandle] -= 1;
// 					}

// 					// 削除ハンドル
// 					std::vector<int> deleteHandles;
// 					deleteHandles.clear();

// 					if (mmHandleCounts[countHandle] <= 0)
// 					{
// 						// 削除予定のハンドルを全取得
// 						deleteHandles = mmHandles[myHandle.first];

// 						// カウントが0以下なためハンドルとカウント削除
// 						mmHandles.erase(myHandle.first);
// 						mmHandleCounts.erase(countHandle);
// 					}
// 					else
// 					{
// 						// 削除予定のハンドルを保存
// 						deleteHandles.push_back(mmHandles[myHandle.first][i]);

// 						// ハンドル削除					
// 						mmHandles[myHandle.first].erase(mmHandles[myHandle.first].begin() + i);

// 						// カウントが参照しているハンドルなら入れ替える
// 						if (i == 0)
// 						{
// 							mmHandleCounts[mmHandles[myHandle.first][0]] = mmHandleCounts[countHandle];
// 							mmHandleCounts.erase(countHandle);
// 						}
// 					}

// 					// 削除したハンドルを返す
// 					return deleteHandles;
// 				}
// 				break;
// 			}
// 		}
//     }

//     return {};
//     /*
    
// 	for (auto movieHandle : mmMovieHandle)
// 	{
// 		for (int i = 0; i < movieHandle.second.size(); i++)
// 		{
// 			if (movieHandle.second[i] == handle)
// 			{
// 				if ((movieHandle.second.size() - 1) <= 0)
// 				{
// 					mmMovieHandle.erase(movieHandle.first);
// 				}
// 				else
// 				{
// 					mmMovieHandle[movieHandle.first].erase(mmMovieHandle[movieHandle.first].begin() + i);
// 				}
// 				return;
// 			}
// 		}
// 	}
//     */
// }