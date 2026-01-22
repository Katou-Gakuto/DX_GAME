#pragma once
#include <map>
#include <string>
#include <vector>

#include "ResourceEnum.h"
#include "ResourceData.h"


class ResourceManager
{
	/*--------*/
	/*【共通】*/
	/*--------*/

public:
	// リソースファイルの名前
	static std::string msResourceFile;

	static DisplaySize mstDisplaySize;

public:
	ResourceManager();
	~ResourceManager();

	/// <summary>初期化</summary>
	void Initilize();
	/*終了*/
	void Finailize();

	/// <summary>開始描画</summary>
	void StartDraw();
	/// <summary>中間描画</summary>
	void MiddleDraw();
	/// <summary>最終描画</summary>
	void LastDraw();

	/// <summary>描画データ解放</summary>
	void DrawDataRelease();

	/*----------*/
	/*【描画】
	/*----------*/
private:
	// シャドウマップハンドル
	int mnShadowMapHandle;
public:
	/// <summary>モデル描画</summary>
	void DrawModelHandle(int modelHandle);

	/// <summary>頂点情報による描画</summary>
	void DrawIndexed(const VERTEX3D*VertexArray, int VertexNum, const unsigned short *IndexArray, int PolygonNum, int GrHandle, int TransFlag);
private:
	/// <summary>シャドウマップの初期化</summary>
	void ShadowMapInit();

	/// <summary>画像や動画の描画</summary>
	void DrawGraphAndMovie(DRAW_GRAPH_DATA drawData);

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
	
	/// <summary>動画再生</summary>
	void PlayMovie(int handle);

	/// <summary>動画停止</summary>
	void StopMovie(int handle);

	/// <summary>動画リセット</summary>
	void MovieReset(int handle);

	/// <summary>動画ループ</summary>
	void MovieLoop(int handle);

	/// <summary>動画描画</summary>
	void DrawMovie(int handle, int x, 		 int y);
	void DrawMovie(int handle, int x, 		 int y, 	   int sizeX, 		 int sizeY);
	void DrawMovie(int handle, int x, 		 int y,		   float sizeXRatio, float sizeYRatio);
	void DrawMovie(int handle, float xRatio, float yRatio);
	void DrawMovie(int handle, float xRatio, float yRatio, int sizeX, 		 int sizeY);
	void DrawMovie(int handle, float xRatio, float yRatio, float sizeXRatio, float sizeYRatio);
	void DrawMovie(DRAW_GRAPH_DATA drawData);

	/*動画音の設定が必要なら作る
	*/

	/*------------*/
	/*【サウンド】*/
	/*------------*/
private:
public:

	/*----------*/
	/*【エフェクト】
	/*----------*/
	// FIXME: 別の場所で変えた設定の影響でハンドル取得時エラーが出る
private:
	// エフェクトハンドル
	std::map<std::string, std::vector<int>> mmEffectHandle;
	// エフェクトカウンター
	std::map<int, int> mmEffectCount;

	// エフェクト描画フラグ
	bool mbEffectDrawFlag;

	// エフェクト描画時使用画像ハンドル
	int mnEffectDrawPreHandle;

public:
	/// <summary>エフェクト情報取得</summary>
	int GetEffectResource(std::string fileName, float size = 1.0f);

	/// <summary>エフェクトハンドルを取得する</summary>
	int GetEffectHandle(int handle, int oldHandle);

	/// <summary>エフェクトカウントを減らす</summary>
	/// <param name="handle">エフェクトハンドル エフェクトの情報のハンドルを渡すとバグる</param>
	void ReduceEffect(int handle);

	/// <summary>エフェクト描画</summary>
	void DrawEffect(int handle, VECTOR position);

	/// <summary>エフェクト停止</summary>
	void StopEffect(int handle);
	/// <summary>エフェクト再生</summary>
	void PlayEffect(int handle, float speed);

private:
	/// <summary>エフェクト初期化</summary>
	void EffectInit();

	/// <summary>エフェクト終了</summary>
	void EffectFinailize();

	/// <summary>エフェクト描画処理</summary>
	void EffectDrawProcess();
};