#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include <map>
#include <Windows.h>

#include "CharacterEnum.h"
#include "SceneEnum.h"
#include "GameDatas.h"
#include "MapData.h"

#include "DxLib.h"

#include "Master.h"

#include "DataManager.h"
#include "EndManager.h"
#include "ObjectBase_Character.h"
#include "UtilCalc.h"
#include "UtilChange.h"

DataManager::DataManager()
: mnPlayPlayerNumber(-1)
, mpEndManger(nullptr)
, mnDungeonDeleteCharacterData(DELETE_CHARACTER_DATA())
, mnTownDeleteCharacterData(DELETE_CHARACTER_DATA())
, mnAcquisitionExp(0)
{
	mwMsg = {};

	/*初期化*/
	mstBaseData = OnePlayerAllData();
	mstBaseData.dataFlag = false;
	mstBaseData.playerData.dataFlag = false;
	mstBaseData.oneDatas.clear();

	/*初期プレイヤーデータ*/
	mstInitPlayerDatas.clear();


	// プレイ情報初期化
	{
		mstPlayPlayerData = OnePlayerAllData();
		mstPlayPlayerData.dataFlag = false;
		mstPlayPlayerData.playerData.dataFlag = false;
		mstPlayPlayerData.oneDatas.clear();
	}

	// セーブデータ
	mstPlayerDatas.clear();

	// プレイヤーファイルネーム
	msPlayerDatasFileName.clear();

	// 取得済みファイル名
	mmGetFilePosNumbers.clear();
}

DataManager::~DataManager()
{
}

// 初期化
void DataManager::Initilize()
{
	mpEndManger = Master::mpEndManager;


	// ベースデータ
	{
		// TODO: ファイルから取得できるようにする
		/*初期化*/
		mstBaseData = OnePlayerAllData();
		mstBaseData.dataFlag = false;
		mstBaseData.playerData.dataFlag = false;
		mstBaseData.oneDatas.clear();

		ONE_DATA setBaseData = ONE_DATA();
		// ファイル
		{
			setBaseData.dataChangeFlag = false;
			setBaseData.typeNumber = 0;
			setBaseData.name = "GameData/FileNames_Data.txt";

			FILE_DATA setFileData = FILE_DATA();
			setFileData.name = "GameData/Player_Data.txt";
			setFileData.typeNumber = 2;
			setFileData.sceneType = (SCENE)0;
			setBaseData.datas.fileNameDatas.push_back(setFileData);

			setFileData.name = "GameData/Default_Map_Character_Data.txt";
			setFileData.typeNumber = 1;
			setFileData.sceneType = (SCENE)3;
			setBaseData.datas.fileNameDatas.push_back(setFileData);

			setFileData.name = "GameData/MapEnemyDatas/Map_Enemy1_Data.txt";
			setFileData.typeNumber = 1;
			setFileData.sceneType = (SCENE)7;
			setBaseData.datas.fileNameDatas.push_back(setFileData);

			setFileData.name = "GameData/MapEnemyDatas/Map1_Boss_Data.txt";
			setFileData.typeNumber = 1;
			setFileData.sceneType = (SCENE)7;
			setBaseData.datas.fileNameDatas.push_back(setFileData);

			mstBaseData.oneDatas.push_back(setBaseData);

			setBaseData.datas.fileNameDatas.clear();
		}
		// キャラクター1
		{
			setBaseData.dataChangeFlag = false;
			setBaseData.typeNumber = 1;
			setBaseData.name = "GameData/Default_Map_Character_Data.txt";

			CHARACTER_DATA setCharacterData;
			setCharacterData.survivalFlag = true;
			setCharacterData.name = "1";
			setCharacterData.typeNumber = 2;
			setCharacterData.status = STATUS::SetStatus(20, 20, 1, 5, 1, 1, CHARACTER_TYPE::ROBOT);
			setCharacterData.mapType = (SCENE)7;
			setCharacterData.position = VGet(-150.0f, 0.0f, 500.0f);
			setCharacterData.angle = VGet(0.0f, 3.14f, 0.0f);
			setBaseData.datas.characterDatas.push_back(setCharacterData);

			setCharacterData.survivalFlag = true;
			setCharacterData.name = "ROBOT_ENEMY_2";
			setCharacterData.typeNumber = 2;
			setCharacterData.status = STATUS::SetStatus(20, 20, 10, 5, 1, 1, CHARACTER_TYPE::ROBOT);
			setCharacterData.mapType = (SCENE)7;
			setCharacterData.position = VGet(800.0f, 0.0f, 1000.0f);
			setCharacterData.angle = VGet(0.0f, 3.14f, 0.0f);
			setBaseData.datas.characterDatas.push_back(setCharacterData);

			mstBaseData.oneDatas.push_back(setBaseData);
			setBaseData.datas.characterDatas.clear();
		}
		// キャラクター2
		{
			setBaseData.dataChangeFlag = false;
			setBaseData.typeNumber = 1;
			setBaseData.name = "GameData/MapEnemyDatas/Map_Enemy1_Data.txt";

			CHARACTER_DATA setCharacterData;
			setCharacterData.survivalFlag = true;
			setCharacterData.name = "ROBOT_ENEMY1";
			setCharacterData.typeNumber = 3;
			setCharacterData.status = STATUS::SetStatus(20, 20, 1, 5, 1, 1, CHARACTER_TYPE::ROBOT);
			setCharacterData.mapType = (SCENE)12;
			setCharacterData.position = VGet(-150.0f, 0.0f, 300.0f);
			setCharacterData.angle = VGet(0.0f, 3.14f, 0.0f);
			setBaseData.datas.characterDatas.push_back(setCharacterData);

			setCharacterData.survivalFlag = true;
			setCharacterData.name = "ROBOT_ENEMY2";
			setCharacterData.typeNumber = 3;
			setCharacterData.status = STATUS::SetStatus(20, 20, 10, 5, 1, 1, CHARACTER_TYPE::ROBOT);
			setCharacterData.mapType = (SCENE)12;
			setCharacterData.position = VGet(1000.0f, 0.0f, 2000.0f);
			setCharacterData.angle = VGet(0.0f, 3.14f, 0.0f);
			setBaseData.datas.characterDatas.push_back(setCharacterData);

			setCharacterData.survivalFlag = true;
			setCharacterData.name = "ROBOT_ENEMY3";
			setCharacterData.typeNumber = 3;
			setCharacterData.status = STATUS::SetStatus(20, 20, 10, 5, 1, 1, CHARACTER_TYPE::ROBOT);
			setCharacterData.mapType = (SCENE)12;
			setCharacterData.position = VGet(2000.0f, 0.0f, 500.0f);
			setCharacterData.angle = VGet(0.0f, 3.14f, 0.0f);
			setBaseData.datas.characterDatas.push_back(setCharacterData);

			mstBaseData.oneDatas.push_back(setBaseData);
			setBaseData.datas.characterDatas.clear();
		}
		// キャラクター3(ボス)
		{
			setBaseData.dataChangeFlag = false;
			setBaseData.typeNumber = 1;
			setBaseData.name = "GameData/MapEnemyDatas/Map1_Boss_Data.txt";

			CHARACTER_DATA setCharacterData;
			setCharacterData.survivalFlag = true;
			setCharacterData.name = "ROBOT_BOSS";
			setCharacterData.typeNumber = 4;
			setCharacterData.status = STATUS::SetStatus(30, 30, 1, 15, 3, 2, CHARACTER_TYPE::ROBOT);
			setCharacterData.mapType = (SCENE)13;
			setCharacterData.position = VGet(3000.0f, 0.0f, 3500.0f);
			setCharacterData.angle = VGet(0.0f, 3.14f, 0.0f);
			setBaseData.datas.characterDatas.push_back(setCharacterData);

			mstBaseData.oneDatas.push_back(setBaseData);
			setBaseData.datas.characterDatas.clear();
		}
		// レベル 1
		{
			setBaseData.dataChangeFlag = false;
			setBaseData.typeNumber = (int)DATA_TYPE::LEVEL;
			setBaseData.name = "GameData/LevelDatas/LevelData.txt";

			LEVEL_DATA levelData;
			levelData.characterType = (int)CHARACTER_TYPE::ROBOT;
			for (int i = 0; i < 20; i++)
			{
				levelData.levelNumber.push_back(i + 1);
				levelData.levelUpExpNumber.push_back(10);
			}
			levelData.upStatsMagnification = 1.0f;
			levelData.upStatus = STATUS::SetStatus(100, 100, 1, 0, 10, 1, CHARACTER_TYPE::ROBOT);
			levelData.maxLevelNumber = levelData.levelNumber.size();
			setBaseData.datas.levelData = levelData;

			mstBaseData.oneDatas.push_back(setBaseData);
			setBaseData.datas.levelData.levelNumber.clear();
			setBaseData.datas.levelData.levelUpExpNumber.clear();
		}
		mstBaseData.dataFlag = true;
	}

	// 初期プレイヤー情報
	{
		mstInitPlayerDatas.clear();
		PLAYER_DATA setInitPlayer = PLAYER_DATA();
		setInitPlayer.mapType = SCENE::TOWN_1;
		setInitPlayer.sceneData[DATA_SCENE::TOWN].sceneType = SCENE::TOWN_1;
		setInitPlayer.sceneData[DATA_SCENE::TOWN].scenePos = UtilCalc::VZero;
		setInitPlayer.sceneData[DATA_SCENE::TOWN].sceneAngle = UtilCalc::VZero;
		setInitPlayer.sceneData[DATA_SCENE::DUNGEON].sceneType = SCENE::NONE;
		setInitPlayer.sceneData[DATA_SCENE::DUNGEON].scenePos = UtilCalc::VZero;
		setInitPlayer.sceneData[DATA_SCENE::DUNGEON].sceneAngle = UtilCalc::VZero;
		setInitPlayer.preMap = SCENE::NONE;
		setInitPlayer.position = UtilCalc::VZero;
		setInitPlayer.angle = UtilCalc::VZero;
		setInitPlayer.dataFlag = true;
		setInitPlayer.survivalFlag = 1;
		setInitPlayer.name = "アボカド";
		setInitPlayer.status = STATUS::SetStatus(100, 100, 1, 0, 10, 10, CHARACTER_TYPE::ROBOT);
		mstInitPlayerDatas.push_back(setInitPlayer);
	}

	// プレイ情報初期化
	{
		mstPlayPlayerData = OnePlayerAllData();
		mstPlayPlayerData.dataFlag = false;
		mstPlayPlayerData.playerData.dataFlag = false;
		mstPlayPlayerData.oneDatas.clear();
	}

	// セーブデータ
	{
		mstPlayerDatas.clear();

		PLAYER_DATA setPlayer = PLAYER_DATA();
		setPlayer.mapType = SCENE::TOWN_1;
		setPlayer.sceneData[DATA_SCENE::TOWN].sceneType = SCENE::TOWN_1;
		setPlayer.sceneData[DATA_SCENE::TOWN].scenePos = UtilCalc::VZero;
		setPlayer.sceneData[DATA_SCENE::TOWN].sceneAngle = VGet(0.0f, UtilCalc::Pi * 1.5f, 0.0f);
		setPlayer.sceneData[DATA_SCENE::DUNGEON].sceneType = SCENE::NONE;
		setPlayer.sceneData[DATA_SCENE::DUNGEON].scenePos = UtilCalc::VZero;
		setPlayer.sceneData[DATA_SCENE::DUNGEON].sceneAngle = VGet(0.0f, UtilCalc::Pi * -1.5f, 0.0f);
		setPlayer.preMap = SCENE::NONE;
		setPlayer.position = VGet(2000.0f, 0.0f, 500.0f);
		setPlayer.angle = UtilCalc::VZero;
		setPlayer.dataFlag = true;
		setPlayer.survivalFlag = 1;
		setPlayer.name = "アボカド";
		setPlayer.status = STATUS::SetStatus(100, 100, 1, 0, 10, 10, CHARACTER_TYPE::ROBOT);

		mstPlayerDatas.push_back(setPlayer);

		setPlayer.mapType = SCENE::TOWN_1;
		setPlayer.sceneData[DATA_SCENE::TOWN].sceneType = SCENE::TOWN_1;
		setPlayer.sceneData[DATA_SCENE::DUNGEON].sceneType = SCENE::NONE;
		setPlayer.name = "アボカド2";
		setPlayer.status = STATUS::SetStatus(100, 100, 1, 0, 10, 10, CHARACTER_TYPE::ROBOT);

		mstPlayerDatas.push_back(setPlayer);

		setPlayer.mapType = SCENE::TOWN_1;
		setPlayer.sceneData[DATA_SCENE::TOWN].sceneType = SCENE::TOWN_1;
		setPlayer.sceneData[DATA_SCENE::DUNGEON].sceneType = SCENE::NONE;
		setPlayer.name = "アボカド3";
		setPlayer.status = STATUS::SetStatus(100, 100, 1, 0, 10, 10, CHARACTER_TYPE::ROBOT);

		mstPlayerDatas.push_back(setPlayer);
	}
	msPlayerDatasFileName.clear();

	mmGetFilePosNumbers.clear();

	SetBaseFile("後でファイル名入れる");

	// ウェーブデータ
	{
		mnWaveNumber = -1;
		mstWaveEnemyData.clear();
		meWaveMapData.clear();
		std::vector<MapType> mapDatas = {
											MapType::Battle,
											MapType::Battle,
											MapType::Battle,
											MapType::Battle,
											MapType::Battle,
											MapType::Battle,
										};


		// TODO: ファイルから読み込む
		for (int i = 1; i < 7; i++)
		{
			std::vector<CHARACTER_DATA> enemyDatas;
			enemyDatas.clear();

			CHARACTER_DATA enemyData = CHARACTER_DATA();
			
			{
				enemyData.survivalFlag = true;
				enemyData.name = "ROBOT_ENEMY1";
				enemyData.typeNumber = 3;
				enemyData.status = STATUS::SetStatus(20 * i, 20 * i, 1 * i, 5, (1 + 19) * i, ((1 * i) * 0.5) + 1, CHARACTER_TYPE::ROBOT);
				enemyData.mapType = SCENE::BATTLE_LOOP;
				enemyData.angle = VGet(0.0f, -2.6166667f, 0.0f);
				switch (i)
				{
				case 1:
				case 3:
				case 5:
					enemyData.position = VGet(2500.0f, 0.0f, 2500.0f);
					break;
					
					
				case 6:
					enemyData.position = VGet(3000.0f, 0.0f, 2000.0f);
					enemyDatas.push_back(enemyData);
					enemyData.position = VGet(2500.0f, 0.0f, 3000.0f);
					enemyDatas.push_back(enemyData);
					enemyData.position = VGet(3250.0f, 0.0f, 3500.0f);
					break;
					
				case 2:
				case 4:
					enemyData.position = VGet(3200.0f, 0.0f, 2000.0f);
					enemyDatas.push_back(enemyData);
					enemyData.position = VGet(2600.0f, 0.0f, 2500.0f);
					break;
				}

				enemyDatas.push_back(enemyData);
			}

			{
				enemyData.status = STATUS::SetStatus(20 * i, 20 * i, 1 * i, 5, (1 + 19) * i, ((1 * i) * 0.5) + 1, CHARACTER_TYPE::ROBOT);
				enemyData.mapType = SCENE::BATTLE_LOOP;
				enemyData.angle = VGet(0.0f, 2.6166667f, 0.0f);
				switch (i)
				{
				case 1:
				case 3:
				case 5:
					enemyData.position = VGet(1500.0f, 0.0f, 2500.0f);
					break;
					
				case 6:
					enemyData.position = VGet(1000.0f, 0.0f, 2000.0f);
					enemyDatas.push_back(enemyData);
					enemyData.position = VGet(1500.0f, 0.0f, 3000.0f);
					enemyDatas.push_back(enemyData);
					enemyData.position = VGet(750.0f, 0.0f, 3500.0f);
					break;
					
				case 2:
				case 4:
					enemyData.position = VGet(800.0f, 0.0f, 2000.0f);
					enemyDatas.push_back(enemyData);
					enemyData.position = VGet(1400.0f, 0.0f, 2500.0f);
					break;
				}

				enemyDatas.push_back(enemyData);

				switch (i)
				{
				case 2:
					enemyData.name == "BOSS";
					enemyData.typeNumber = 3;
					enemyData.status = STATUS::SetStatus(1000, 1000, 15, 40, 200, 5, CHARACTER_TYPE::ROBOT);
					enemyData.angle = VGet(0.0f, 3.14f, 0.0f);
					enemyData.position = VGet(2000.0f, 0.0f, 3750.0f);

					enemyDatas.push_back(enemyData);
					break;

				case 4:
					enemyData.name == "BOSS";
					enemyData.typeNumber = 3;
					enemyData.status = STATUS::SetStatus(3000, 3000, 30, 70, 400, 10, CHARACTER_TYPE::ROBOT);
					enemyData.angle = VGet(0.0f, 3.14f, 0.0f);
					enemyData.position = VGet(2000.0f, 0.0f, 3750.0f);

					enemyDatas.push_back(enemyData);
					break;
				}
			}


			mstWaveEnemyData.push_back(enemyDatas);

			meWaveMapData.push_back(mapDatas[i - 1]);
		}
	}
}

// ベースファイル設定
void DataManager::SetBaseFile(std::string fileName)
{
}

/*--------*/
/*【処理】*/
/*--------*/

// データを保存
void DataManager::Save(CharacterBase* playerObject)
{
	if ((mnPlayPlayerNumber != -1) && mstPlayPlayerData.dataFlag)
	{
		if (playerObject != nullptr)
		{
			mstPlayPlayerData.playerData.angle = playerObject->GetAngle();
			mstPlayPlayerData.playerData.position = playerObject->GetPos();
		}

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
	Save(nullptr);
}

/*--------*/
/*【削除】*/
/*--------*/

// エネミーデータ削除
void DataManager::DeleteEnemyData(SCENE deleteScene)
{
	DELETE_CHARACTER_DATA deleteData;

	if (UtilChange::SceneState(deleteScene) == SCENE::DUNGEON)
	{
		deleteData = mnDungeonDeleteCharacterData;
	}
	else if (UtilChange::SceneState(deleteScene) == SCENE::TOWN)
	{
		DeleteEnemyData(SCENE::DUNGEON);
		deleteData = mnTownDeleteCharacterData;
	}
	std::vector<std::string> sceneFileNames = GetSceneFileNames(deleteScene, false);

	for (int i = 0; i < mstPlayPlayerData.oneDatas.size(); i++)
	{
		// データ種類確認
		if (mstPlayPlayerData.oneDatas[i].typeNumber == (int)DATA_TYPE::CHARACTER)
		{
			// シーン確認
			if (std::find(sceneFileNames.begin(), sceneFileNames.end(), mstPlayPlayerData.oneDatas[i].name) == sceneFileNames.end())
			{
				continue;
			}

			// キャラクター確認
			for (int j = 0; j < mstPlayPlayerData.oneDatas[i].datas.characterDatas.size(); j++)
			{
				// IDを確認
				if (mstPlayPlayerData.oneDatas[i].datas.characterDatas[j].objectID == deleteData.characterID)
				{
					// 削除
					mstPlayPlayerData.oneDatas[i].datas.characterDatas.erase(mstPlayPlayerData.oneDatas[i].datas.characterDatas.begin() + j);
					return;
				}
			}
		}
	}
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

			
			// HACK: とりあえず適当に入れてる
			// データ設定用初期化
			OneData setData;
			setData.dataChangeFlag = false;
			setData.name = mstPlayPlayerData.playerData.playerFolderName + "/FileNames_Data.txt";
			setData.typeNumber = (int)DATA_TYPE::FILE_NAME;
			setData.datas.fileNameDatas.clear();
			// for (int i = 0; i < mstBaseData.oneDatas[0].datas.fileNameDatas.size(); i++)
			// {
			// 	setData.datas.fileNameDatas.push_back(mstBaseData.oneDatas[0].datas.fileNameDatas[i]);
			// }

			mstPlayPlayerData.oneDatas.push_back(setData);


			mstPlayPlayerData.dataFlag = true;
		}
	}
}

// キャラクターID設定
void DataManager::SetCharacterID(int id, std::string fileName, int index)
{
	for (int i = 0; i < mstPlayPlayerData.oneDatas.size(); i++)
	{
		if (mstPlayPlayerData.oneDatas[i].name == fileName)
		{
			mstPlayPlayerData.oneDatas[i].datas.characterDatas[index].objectID = id;
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

		std::vector<int> setData = mmGetFilePosNumbers[sceneName];

		resultData.reserve(setData.size() - 1);
		for (int checkNumber : setData)
		{
			resultData.push_back(mstPlayPlayerData.oneDatas[checkNumber]);
		}

		return resultData;
	}

	std::vector<std::string> baseFileNames;
	baseFileNames.clear();

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
		resultData.reserve(baseFileNames.size());
		// 処理の正しさを後で調べる
		
		// データ場所記録用
		std::vector<int> setGetFilePosNumbers;
		setGetFilePosNumbers.clear();

		// プレイ中データの何処にファイルネームデータあるかを取得する
		std::vector<int> fileNameDataPos;
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
						mstPlayPlayerData.oneDatas[0].datas.fileNameDatas.push_back(setFileName);
						break;
					}
				}
			}
		}

		mmGetFilePosNumbers[sceneName] = setGetFilePosNumbers;
		return resultData;
	}
}


// マップデータ取得
std::vector<std::vector<TileData>> DataManager::GetMapData(MapType tileType)
{
	std::vector<std::vector<TileData>> mapData;
	mapData.clear();

	std::ifstream csvFile;
	csvFile.open("MapData/Map" + std::to_string((int)tileType) + ".csv");

	if (csvFile.is_open())
	{
		// ファイルの行数と列数を数える
		std::string line;
		int rowCount = 0;
		int colCount = 0;
		while (std::getline(csvFile, line))
		{
			rowCount++;
			if (rowCount == 1)
			{
				std::string cell;
				while (std::getline(csvFile, cell, ','))
				{
					colCount++;
				}
			}
		}
		// ファイルの先頭に戻る
		csvFile.clear();
		csvFile.seekg(0, std::ios::beg);
		// マップデータの2次元ベクトルを初期化
		mapData.resize(rowCount, std::vector<TileData>(colCount));
		// マップデータを読み込む
		int currentRow = 0;
		while (std::getline(csvFile, line))
		{
			std::string cell;
			int currentCol = 0;
			while (std::getline(csvFile, cell, ','))
			{
				int tileValue = std::stoi(cell);
				TileData& tileData = mapData[currentRow][currentCol];
				tileData.tileType = static_cast<TileType>(tileValue);
				tileData.tileDisplacedPos = VGet(static_cast<float>(currentCol), static_cast<float>(currentRow), 0.0f);
				currentCol++;
			}
			currentRow++;
		}
	}

	/*std::ifstream csv_file(file_path); // ファイルを開く

if (!csv_file.is_open()) {
std::cerr << "ファイルが開けませんでした: " << file_path << std::endl;
return 1;
}

std::string line; // 1行分のデータ
while (std::getline(csv_file, line)) {
std::istringstream line_stream(line);
std::string cell;

// カンマ区切りでデータを取得
while (std::getline(line_stream, cell, ',')) {
std::cout << cell << " "; // 各セルのデータを出力
}
std::cout << std::endl; // 行ごとに改行
}

csv_file.close(); // ファイルを閉じる
return 0;*/

	csvFile.close();
	return mapData;
}

// シーンに合ったファイル名を取得
std::vector<std::string> DataManager::GetSceneFileNames(SCENE scsene, bool baseFlag)
{
	ONE_PLAYER_ALL_DATA* onePlayerAllData = (baseFlag ? &mstBaseData : &mstPlayPlayerData);

	std::vector <std::string> baseFileNames;
	baseFileNames.clear();
	
	for (int i = 0; i < onePlayerAllData->oneDatas.size(); i++)
	{
		if (onePlayerAllData->oneDatas[i].typeNumber == (int)DATA_TYPE::FILE_NAME)
		{
			for (int j = 0; j < onePlayerAllData->oneDatas[i].datas.fileNameDatas.size(); j++)
			{
				if (onePlayerAllData->oneDatas[i].datas.fileNameDatas[j].sceneType == scsene)
				{
					baseFileNames.push_back(onePlayerAllData->oneDatas[i].datas.fileNameDatas[j].name);
				}
			}
		}
	}

	return baseFileNames;
}


/*------------*/
/*【ウェーブ】*/
/*------------*/

// ウェーブ進行
bool DataManager::SetNextWave()
{
	if ((mnWaveNumber + 1) >= mstWaveEnemyData.size())
	{
		return false;
	}

	mnWaveNumber += 1;
	return true;
}

// ウェーブ初期化
void DataManager::InitWave()
{
	mnWaveNumber = -1;
}

// ウェーブのエネミーデータ取得
std::vector<CHARACTER_DATA> DataManager::GetWaveEnemy()
{
	return mstWaveEnemyData[mnWaveNumber];
}



/*--------------------------*/
/*     【マップデータ】     */
/*--------------------------*/

// マップリソースファイル名取得
std::string DataManager::GetMapResourceFileName(MAP_RESOURCE_FILE_NUMBWER fileNumber)
{
	return "Resource/3D/Floor/Ceiling_Closed.mv1";
}