#include <map>
#include <string>

#include "DxLib.h"

#include "../Header/Master.h"

#include "../Header/EndManager.h"
#include "../Header/ResourceManager.h"


/*--------*/
/*【共通】*/
/*--------*/
ResourceManager::ResourceManager()
{
	// 3Dモデル
	mmModelHandle.clear();
	mmModelCount.clear();

	// 画像
	mmGraphHandle.clear();
	mmGraphCount.clear();
	mmDivGraphHandle.clear();
	msDivGraphFileNames.clear();
}
ResourceManager::~ResourceManager()
{
}

// 終了
void ResourceManager::Finailize()
{
	{// 3Dモデル
		MV1InitModel();
		mmModelCount.clear();
		mmModelHandle.clear();
	}

	{// 画像
		for (std::pair<std::string, int> graphHandle : mmGraphHandle)
		{
			DeleteGraph(graphHandle.second);
		}
		mmGraphHandle.clear();
		mmGraphCount.clear();

		for (const std::pair<std::string, DIV_GRAPH_DATA>& divHandle : mmDivGraphHandle)
		{
			for (int i = 0; i < divHandle.second.allNum; i++)
			{
				DeleteGraph(*(divHandle.second.handle + i));
			}
		}
		mmDivGraphHandle.clear();
		msDivGraphFileNames.clear();
	}

	{// 動画
		for (std::pair<std::string, int> moveiHandle : mmMovieHandle)
		{
			DeleteGraph(moveiHandle.second);
		}
		mmMovieHandle.clear();
		mmMovieCount.clear();
	}

	{// サウンド
	}
}


/*------------*/
/*【3Dモデル】*/
/*------------*/
// モデルハンドル取得
int ResourceManager::GetModelHandle(std::string fileName)
{
	int handle = -1;
	if (mmModelHandle.find(fileName) != mmModelHandle.end())
	{
		handle = mmModelHandle[fileName];
		mmModelCount[handle] += 1;
		return MV1DuplicateModel(handle);
	}

	handle = MV1LoadModel(fileName.c_str());
	if (handle == -1)
	{
		Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::RESOURCE_FLAG);
		return -1;
	}
	mmModelHandle[fileName] = handle;
	mmModelCount[handle] = 1;

	return handle;
}

// モデルハンドル削除
void ResourceManager::ReduceModelHandle(int handle)
{
	mmModelCount[handle] -= 1;
	if (mmModelCount[handle] <= 0)
	{
		MV1DeleteModel(handle);
		mmModelCount.erase(handle);

		std::string fileName;
		for (std::pair<std::string, int> modelHandle : mmModelHandle)
		{
			if (modelHandle.second == handle)
			{
				fileName = modelHandle.first;
				break;
			}
		}
		mmModelHandle.erase(fileName);
	}
}


/*--------*/
/*【画像】*/
/*--------*/
// 画像ハンドル取得
int ResourceManager::GetGraphHandle(std::string fileName)
{
	int handle = -1;
	if (mmGraphHandle.find(fileName) != mmGraphHandle.end())
	{
		handle = mmGraphHandle[fileName];
		mmGraphCount[handle] += 1;
		return handle;
	}

	handle = LoadGraph(fileName.c_str());
	if (handle == -1)
	{
		Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::RESOURCE_FLAG);
		return -1;
	}
	mmGraphHandle[fileName] = handle;
	mmGraphCount[handle] = 1;

	return handle;
}

// 画像カウントを減らす
void ResourceManager::ReduceGraphHandle(int handle)
{
	mmGraphCount[handle] -= 1;
	if (mmGraphCount[handle] <= 0)
	{
		DeleteGraph(handle);
		mmGraphCount.erase(handle);

		std::string fileName;
		for (std::pair<std::string, int> graphHandle : mmGraphHandle)
		{
			if (graphHandle.second == handle)
			{
				fileName = graphHandle.first;
				break;
			}
		}
		mmGraphHandle.erase(fileName);
	}
}

// Div画像ハンドル取得
void ResourceManager::GetDivGraphHandle(std::string fileName, DIV_GRAPH_DATA* graphData)
{
	if (mmGraphHandle.find(fileName) != mmGraphHandle.end())
	{
		*graphData = mmDivGraphHandle[fileName];
		graphData->count += 1;
		return;
	}


	if (LoadDivGraph(fileName.c_str(), graphData->allNum, graphData->xNum, graphData->yNum, graphData->xSize, graphData->ySize, graphData->handle) == -1)
	{
		Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::RESOURCE_FLAG);
		return;
	}
	mmDivGraphHandle[fileName] = *graphData;
	msDivGraphFileNames.push_back(fileName);
	graphData->count += 1;
	graphData->number = ((int)msDivGraphFileNames.size() - 1);
}

// Div画像カウントを減らす
void ResourceManager::ReduceDivGraphHandle(int number)
{
	if ((mmDivGraphHandle[msDivGraphFileNames[number]].count -= 1) <= 0)
	{
		for (int i = 0; i < mmDivGraphHandle[msDivGraphFileNames[number]].allNum; i++)
		{
			DeleteGraph(*(mmDivGraphHandle[msDivGraphFileNames[number]].handle + i));
		}
		mmDivGraphHandle.erase(msDivGraphFileNames[number]);
		msDivGraphFileNames.erase(msDivGraphFileNames.begin() + number);
	}
}


/*--------*/
/*【動画】*/
/*--------*/
// 動画ハンドル取得
int ResourceManager::GetMovieHandle(std::string fileName)
{
	int handle = -1;
	if (mmMovieHandle.find(fileName) != mmMovieHandle.end())
	{
		handle = mmMovieHandle[fileName];
		mmMovieCount[handle] += 1;
		return handle;
	}

	handle = LoadGraph(fileName.c_str());
	if (handle == -1)
	{
		Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::RESOURCE_FLAG);
		return -1;
	}
	mmMovieHandle[fileName] = handle;
	mmMovieCount[handle] = 1;

	return handle;
}

// 動画カウントを減らす
void ResourceManager::ReduceMovie(int handle)
{
	mmMovieCount[handle] -= 1;
	if (mmMovieCount[handle] <= 0)
	{
		DeleteGraph(handle);
		mmMovieCount.erase(handle);

		std::string fileName;
		for (std::pair<std::string, int> graphHandle : mmMovieHandle)
		{
			if (graphHandle.second == handle)
			{
				fileName = graphHandle.first;
				break;
			}
		}
		mmMovieHandle.erase(fileName);
	}
}


/*------------*/
/*【サウンド】*/
/*------------*/
