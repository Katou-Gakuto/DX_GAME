#pragma once
#include <map>
#include <string>
#include <vector>

// DIV画像データ
struct DIV_GRAPH_DATA
{
public:
	int* handle;

	int allNum;
	
	int xNum;
	int yNum;

	int xSize;
	int ySize;

	int number;
	int count;

	DIV_GRAPH_DATA()
	{
		handle = nullptr;
		allNum = 0;
		xNum = 0;
		yNum = 0;
		xSize = 0;
		ySize = 0;
		number = -1;
		count = 0;
	}

	/*初期化用(ハンドルの配列と全画像の枚数のみ設定)*/
	DIV_GRAPH_DATA(int allNumber)
	{
		handle = (int *)malloc(sizeof(int) * allNumber);
		allNum = allNumber;
		xNum = 0;
		yNum = 0;
		xSize = 0;
		ySize = 0;
		number = -1;
		count = 0;
	}
};

class ResourceManager
{
	/*--------*/
	/*【共通】*/
	/*--------*/
public:
	ResourceManager();
	~ResourceManager();

	/*終了*/
	void Finailize();

	/*------------*/
	/*【3Dモデル】*/
	/*------------*/
private:
	// 3Dモデルハンドル
	std::map<std::string, std::vector<int>> mmModelHandle;
	// 3Dモデルカウンター
	std::map<int, int> mmModelCount;

public:
	/*3Dモデルハンドル取得*/
	int GetModelHandle(std::string fileName);
	/*3Dモデルカウントを減らす*/
	void ReduceModelHandle(int handle);
	/* 便利用増やす
	*/

	/*--------*/
	/*【画像】*/
	/*--------*/
private:
	// 画像ハンドル
	std::map<std::string, int> mmGraphHandle;
	// 画像カウンター
	std::map<int, int> mmGraphCount;

	// Div画像ハンドル
	std::map<std::string, DIV_GRAPH_DATA> mmDivGraphHandle;
	// Div画像ファイつ名
	std::vector<std::string> msDivGraphFileNames;

public:
	/*画像ハンドル取得*/
	int GetGraphHandle(std::string fileName);
	/*画像カウントを減らす*/
	void ReduceGraphHandle(int handle);

	/*Div画像ハンドル取得*/
	void GetDivGraphHandle(std::string fileName, DIV_GRAPH_DATA* graphData);
	/*Div画像カウントを減らす*/
	void ReduceDivGraphHandle(int number);

	/*--------*/
	/*【動画】*/
	/*--------*/
private:
	// 動画ハンドル
	std::map<std::string, int> mmMovieHandle;
	// 動画カウンター
	std::map<int, int> mmMovieCount;
public:
	/*動画ハンドル取得*/
	int GetMovieHandle(std::string fileName);
	/*動画カウントを減らす*/
	void ReduceMovie(int handle);
	
	/*動画音の設定が必要なら作る
	*/

	/*------------*/
	/*【サウンド】*/
	/*------------*/
private:
public:
};