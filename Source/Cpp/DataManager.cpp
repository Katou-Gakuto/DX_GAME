#include <string>
#include <vector>
#include <list>

#include <map>
#include <Windows.h>

#include "../Header/CharacterEnum.h"
#include "../Header/SceneEnum.h"
#include "../Header/GameDatas.h"

#include "DxLib.h"

#include "../Header/Master.h"

#include "../Header/DataManager.h"
#include "../Header/EndManager.h"
#include "../Header/UtilCalc.h"

DataManager::DataManager()
: mnPlayPlayerNumber(-1)
, mpEndManger(nullptr)
{
	mwMsg = {};

	mstBaseData = OnePlayerAllData();
	mstBaseData.dataFlag = false;
	mstBaseData.playerData.dataFlag = false;
	mstBaseData.oneDatas.clear();

	mstInitPlayerDatas.clear();

	mstPlayPlayerData = OnePlayerAllData();
	mstPlayPlayerData.dataFlag = false;
	mstPlayPlayerData.playerData.dataFlag = false;
	mstPlayPlayerData.oneDatas.clear();

	{
		mstPlayerDatas.clear();

		PLAYER_DATA setPlayer = PLAYER_DATA();
		setPlayer.mapType = SCENE::BATTLE_1;
		setPlayer.townType = SCENE::TOWN_1;
		setPlayer.preMap = SCENE::NONE;
		setPlayer.position = UtilCalc::VZero();
		setPlayer.angle = UtilCalc::VZero();
		setPlayer.dataFlag = true;
		setPlayer.survivalFlag = 1;
		setPlayer.name = "アボカド";
		setPlayer.status = STATUS::SetStatus(100, 100, 1, 10, 10, CHARACTER_TYPE::ROBOT);

		mstPlayerDatas.push_back(setPlayer);

		setPlayer.mapType = SCENE::BATTLE_2;
		setPlayer.townType = SCENE::TOWN_2;
		setPlayer.name = "アボカド2";
		setPlayer.status = STATUS::SetStatus(100, 100, 1, 10, 10, CHARACTER_TYPE::ROBOT);

		mstPlayerDatas.push_back(setPlayer);

		setPlayer.mapType = SCENE::BATTLE_3;
		setPlayer.townType = SCENE::TOWN_3;
		setPlayer.name = "アボカド3";
		setPlayer.status = STATUS::SetStatus(100, 100, 1, 10, 10, CHARACTER_TYPE::ROBOT);

		mstPlayerDatas.push_back(setPlayer);
	}
	msPlayerDatasFileName.clear();

	mmGetFilePosNumbers.clear();

	SetBaseFile("後でファイル名入れる");
}

DataManager::~DataManager()
{
}

// 初期化
void DataManager::Initilize()
{
	mpEndManger = Master::mpEndManager;
}

// ベースファイル設定
void DataManager::SetBaseFile(std::string fileName)
{
}

/*--------*/
/*【処理】*/
/*--------*/

// データを保存
void DataManager::Save()
{
	if ((mnPlayPlayerNumber != -1) && mstPlayPlayerData.dataFlag)
	{
		mstPlayerDatas[mnPlayPlayerNumber] = mstPlayPlayerData.playerData;
	}
}

// プレイ中データに設定されたデータを削除する
void DataManager::PlayDataDelete(int playerNumber)
{
	if (playerNumber >= mstPlayerDatas.size())
	{
		return;
	}
	// 消すデータを設定する
	SetPlayPlayer(playerNumber);

	/*
	* 【ファイル名データに載っているファイルを全削除】
	*/
	/*
	if (mstPlayPlayerData.oneDatas[0].typeNumber == (int)DataType::FILE_NAME)
	{
		for (int i = 0; i < mstPlayPlayerData.oneDatas[0].datas.fileNameDatas.size(); i++)
		{
			/*ファイルを削除出来たらプレイヤーデータも削除する
			if (std::remove(mstPlayPlayerData.oneDatas[0].datas.fileNameDatas[i].fileName.c_str()) == 0)
			{

				for (int j = 0; j < mstPlayPlayerData.oneDatas.size(); j++)
				{
					if (mstPlayPlayerData.oneDatas[j].name == mstPlayPlayerData.oneDatas[0].datas.fileNameDatas[i].fileName)
					{
						// vectorから削除
						mstPlayPlayerData.oneDatas.erase(mstPlayPlayerData.oneDatas.begin() + j);
						break;
					}
				}
			}
			}
		}
	}
	*/

	// キャラクターフラグをfalseにする
	mstPlayPlayerData.playerData.dataFlag = false;

	/*
	* 【プレイヤーデータ削除した後に削除した状態を設定する】
	*/
	Save();
}

/*--------*/
/*【設定】*/
/*--------*/

// プレイヤー設定
void DataManager::SetPlayPlayer(int playerNumber)
{
	if (mstPlayerDatas.size() > playerNumber)
	{
		if (mstPlayerDatas[playerNumber].survivalFlag)
		{
			// プレイヤーデータ初期化
			{
				// 前のデータで使用していたアイテムオブジェクトを削除する
				/*
				for (int i = 0; i < mstPlayPlayerData.playerData.item.size(); i++)
				{
					delete mstPlayPlayerData.playerData.item[i];
				}
				mstPlayPlayerData.playerData.item.clear();
				*/

				// 取得したシーンのファイルポジションを消す
				mmGetFilePosNumbers.clear();

				// プレイヤーデータを設定
				mnPlayPlayerNumber = playerNumber;
				mstPlayPlayerData.dataFlag = false;
				mstPlayPlayerData.playerData = mstPlayerDatas[playerNumber];
				mstPlayPlayerData.oneDatas.clear();
				
				// アイテムを設定
				/*
				for (int i = 0; i < mstPlayPlayerData.playerData.itemNumber; i++) {

					Item_Base* itemBase;
					ITEM_DATA checkItemData = mstPlayPlayerData.playerData.itemData[i];

					switch ((ItemType)checkItemData.templateData.typeNumber)
					{
					case ItemType::RECOVERY_MEDICIN_SMALL:
						itemBase = new ItemRecoveryMedicine(checkItemData, 30);
						break;

					case ItemType::RECOVERY_MEDICIN_MEDIUM:
						itemBase = new ItemRecoveryMedicine(checkItemData, 100);
						break;

					case ItemType::RECOVERY_MEDICIN_LARGE:
						itemBase = new ItemRecoveryMedicine(checkItemData, 500);
						break;
					}

					mstPlayPlayerData.playerData.item.push_back(itemBase);
				}*/
			}

			// ファイル情報を読み取る
			/* 
			// データ設定用初期化
			OneData setData;
			setData.dataChangeFlag = false;
			setData.name = mstPlayPlayerData.playerData.playerFolderName + "/FileNames_Data.txt";
			setData.typeNumber = -1;

			// ファイルを開ける
			std::ifstream nameDataFile;
			nameDataFile.open(setData.name, std::ios_base::in);

			// ファイルデータ取得
			if (nameDataFile.is_open())
			{
				// ファイル確認
				nameDataFile >> setData.typeNumber;
				if (setData.typeNumber == (int)DataType::FILE_NAME)
				{
					setData = GetOneFileData(setData, &nameDataFile);
				}
			}
			else
			{
				mbFailureFlag = true;
				return;
			}

			nameDataFile.close();
			mstPlayPlayerData.oneDatas.push_back(setData);
			setData.name.clear();
			setData.typeNumber = -1;


			// ファイル名に保存されているファイルをすべて取得する
			for (DATA_NAME fileNameData : mstPlayPlayerData.oneDatas[0].datas.fileNameDatas)
			{
				setData.name = fileNameData.fileName;

				// ファイルを開ける
				std::ifstream dataFile;
				dataFile.open(setData.name, std::ios_base::in);

				if (dataFile.is_open())
				{
					dataFile >> setData.typeNumber;
					if (setData.typeNumber == (int)DataType::PLAYER ||
						setData.typeNumber == (int)DataType::INIT_PLAYER)
					{
						return;
					}
					else
					{
						setData = GetOneFileData(setData, &dataFile);
						mstPlayPlayerData.oneDatas.push_back(setData);
					}
				}
				else
				{
					mbFailureFlag = true;
					return;
				}

				dataFile.close();
				setData.name.clear();
				setData.typeNumber = -1;
			}
			*/

			mstPlayPlayerData.dataFlag = true;
		}
	}
}

/*--------*/
/*【取得】*/
/*--------*/

// *指定のシーンに必要な全データを取得
std::vector<ONE_DATA> DataManager::GetSceneData(SCENE sceneName)
{
	// 以前見つけたファイルなら見つけたファイルをプレイ中のデータから取り出す
	if (mmGetFilePosNumbers.find(sceneName) != mmGetFilePosNumbers.end())
	{
		std::vector<OneData> resultData;
		resultData.clear();

		std::list<int> setData = mmGetFilePosNumbers[sceneName];

		resultData.reserve(setData.size() - 1);
		for (int checkNumber : setData)
		{
			resultData.push_back(mstPlayPlayerData.oneDatas[checkNumber]);
		}

		return resultData;
	}

	std::list <std::string> baseFileNames;

	// ベースファイルにいくつこのシーンの情報があるかを調べる
	for (int i = 0; i < mstBaseData.oneDatas.size(); i++)
	{
		if (mstBaseData.oneDatas[i].typeNumber == (int)DATA_TYPE::FILE_NAME)
		{
			for (int j = 0; j < mstBaseData.oneDatas[i].datas.fileNameDatas.size(); j++)
			{
				if (mstBaseData.oneDatas[i].datas.fileNameDatas[j].sceneType == sceneName)
				{
					baseFileNames.push_back(mstBaseData.oneDatas[i].datas.fileNameDatas[j].name);
				}
			}
		}
	}

	// 必要なデータを返す
	{
		// 返すデータ
		std::vector<OneData> resultData;
		resultData.clear();
		resultData.reserve(baseFileNames.size() - 1);
		// 処理の正しさを後で調べる
		/*
		// デート場所記録用
		std::list<int> setGetFilePosNumbers;
		setGetFilePosNumbers.clear();

		// プレイ中データの何処にファイルネームデータあるかを取得する
		std::list<int> fileNameDataPos;
		fileNameDataPos.clear();
		for (int i = 0; i < mstPlayPlayerData.oneDatas.size(); i++)
		{
			if (mstPlayPlayerData.oneDatas[i].typeNumber == (int)DATA_TYPE::FILE_NAME)
			{
				fileNameDataPos.push_back(i);
			}
		}
		for (std::string baseFileName : baseFileNames)
		{
			// プレイ中データにあるか探す
			bool checkFile = false;
			std::string checkName = baseFileName;
			for (int namePos : fileNameDataPos)
			{
				for (int i = 0; i < mstPlayPlayerData.oneDatas[namePos].datas.fileNameDatas.size(); i++)
				{
					if (mstPlayPlayerData.oneDatas[namePos].datas.fileNameDatas[i].name.substr(18) == baseFileName.substr(9))
					{
						checkFile = true;
						for (int j = 0; j < mstPlayPlayerData.oneDatas.size(); j++)
						{
							if (mstPlayPlayerData.oneDatas[j].name == mstPlayPlayerData.oneDatas[namePos].datas.fileNameDatas[i].name)
							{
								resultData.push_back(mstPlayPlayerData.oneDatas[j]);
								setGetFilePosNumbers.push_back(j);
								break;
							}
						}
						break;
					}
				}
				if (checkFile)
				{
					break;
				}
			}

			// プレイ中データにない場合ベースデータから取得する
			if (!checkFile)
			{
				for (int i = 0; i < mstBaseData.oneDatas.size(); i++)
				{
					if (mstBaseData.oneDatas[i].name == baseFileName)
					{
						// プレイヤーデータに情報を追加
						ONE_DATA setData = mstBaseData.oneDatas[i];
						setData.dataChangeFlag = true;
						setData.name = (mstPlayPlayerData.playerData.playerFolderName + "/" + setData.name.substr(9));
						mstPlayPlayerData.oneDatas.push_back(setData);
						setGetFilePosNumbers.push_back(mstPlayPlayerData.oneDatas.size() - 1);

						// リザルトに情報追加
						resultData.push_back(setData);


						// ファイル名データに情報追加
						FILE_DATA setFileName;
						setFileName.sceneType = sceneName;
						setFileName.name = setData.name;
						setFileName.typeNumber = setData.typeNumber;
						// ファイルにデータを追加する
						//mstPlayPlayerData.oneDatas[0].datas.fileNameDatas.push_back(setFileName);
						break;
					}
				}
			}
		}

		mmGetFilePosNumbers[sceneName] = setGetFilePosNumbers;*/
		return resultData;
	}
}