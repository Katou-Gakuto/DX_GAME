#include <Windows.h>

#include "../Header/GameDatas.h"

#include "../Header/Master.h"

#include "../Header/DataManager.h"
#include "../Header/EndManager.h"

DataManager::DataManager()
: mnPlayPlayerNumber(-1)
, mpEndManger(nullptr)
{
	mwMsg = {};

	mstBaseData = OnePlayerAllData();
	mstBaseData.dataFLag = false;
	mstBaseData.playerData.dataFlag = false;
	mstBaseData.oneDatas.clear();

	mstInitPlayerDatas.clear();

	mstPlayPlayerData = OnePlayerAllData();
	mstPlayPlayerData.dataFLag = false;
	mstPlayPlayerData.playerData.dataFlag = false;
	mstPlayPlayerData.oneDatas.clear();

	mstPlayerDatas.clear();
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