#pragma once
#include <map>
#include <string>
#include <vector>

#include "ResourceEnum.h"
#include "ResourceData.h"
#include "Vector2.h"

#include "DxLib.h"

#include "HandleContainer.h"
#include "UtilCalc.h"

class DataManager;

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
	/// <summary>終了</summary>
	void Finalize();

	/// <summary>更新</summary>
	void Update();

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
	
	// シャドウ描画中フラグ
	bool mbDrawShadowMapFlag;
public:
	/// <summary>モデル描画</summary>
	void DrawModelHandle(int modelHandle);

	/// <summary>頂点情報による描画</summary>
	void DrawIndexed(const VERTEX3D*VertexArray, int VertexNum, const unsigned short *IndexArray, int PolygonNum, int GrHandle, int TransFlag);

	/// <summary>画像描画</summary>
	void DrawData_Graph(DRAW_GRAPH_DATA drawData);

private:

	/// <summary>シャドウマップの初期化</summary>
	void ShadowMapInit();

	/*----------*/
	/*【取得】
	/*----------*/
public:
	/// <summary>描画情報取得</summary>
	DRAW_GRAPH_DATA GetDrawGraphData(int handle, int x, 		 int y);
	DRAW_GRAPH_DATA GetDrawGraphData(int handle, int x, 		 int y, 	   int sizeX, 		 int sizeY);
	DRAW_GRAPH_DATA GetDrawGraphData(int handle, int x, 		 int y,		   float sizeXRatio, float sizeYRatio);
	DRAW_GRAPH_DATA GetDrawGraphData(int handle, float xRatio, float yRatio);
	DRAW_GRAPH_DATA GetDrawGraphData(int handle, float xRatio, float yRatio, int sizeX, 		 int sizeY);
	DRAW_GRAPH_DATA GetDrawGraphData(int handle, float xRatio, float yRatio, float sizeXRatio, float sizeYRatio);
	DRAW_GRAPH_DATA GetDrawGraphData(int handle, Vector2_Int pos);
	DRAW_GRAPH_DATA GetDrawGraphData(int handle, Vector2_Int pos, Vector2_Int size);
	DRAW_GRAPH_DATA GetDrawGraphData(int handle, Vector2_Int leftUp, Vector2_Int rightUp, Vector2_Int leftDown, Vector2_Int rightDown);
	
	/// <summary>シャドウマップ描画フラグ</summary>
	inline bool GetShadowMapDrawFlag() const { return mbDrawShadowMapFlag; }

	/*------------*/
	/*【3Dモデル】*/
	/*------------*/
private:
	// 3Dモデルハンドルコンテナ
	HandleContainer<std::string>* mp3DModelHandleContainer;

	// // 3Dモデルハンドル
	// std::map<std::string, std::vector<int>> mmModelHandle;
	// // 3Dモデルカウンター
	// std::map<int, int> mmModelCount;

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
	// 画像ハンドルコンテナ
	HandleContainer<std::string>* mpGraphHandleContainer;

	// // 画像ハンドル
	// std::map<std::string, int> mmGraphHandle;
	// // 画像カウンター
	// std::map<int, int> mmGraphCount;

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
	// 動画ハンドルコンテナ
	HandleContainer<std::string>* mpMovieHandleContainer;

	// // 動画ハンドル
	// std::map<std::string, std::vector<int>> mmMovieHandle;
	
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

	/*------------*/
	/*【サウンド】*/
	/*------------*/
private:
	// デーマネージャー
	DataManager* mpDataManager;

	// サウンドハンドル
	HandleContainer<std::string>* mpSoundHandleContainer;
	// 再生中サウンドハンドル
	HandleContainer<int>* mpPlaySoundHandleContainer;
	// サウンドボリューム
	int mnSoundVolume;

	// 3Dサウンドハンドル
	HandleContainer<std::string>* mp3DSoundHandleContainer;
	// 再生中3Dサウンドハンドル
	HandleContainer<int>* mpPlay3DSoundHandleContainer;
	// 3Dサウンドボリューム
	int mn3DSoundVolume;

	// 再生中バックサウンドハンドル
	int mnPlayBackSoundHandle = -1;
	// バックサウンドボリューム
	int mnBackSoundVolume = -1;


public:
	/// <summary>サウンドハンドル取得</summary>
	int GetSoundHandle(std::string fileName);
	/// <summary>サウンドカウントを減らす</summary>
	void ReduceSoundHandle(int handle);

	/// <summary>3Dサウンドハンドル取得</summary>
	int Get3DSoundHandle(std::string fileName);
	/// <summary>3Dサウンドカウントを減らす</summary>
	void Reduce3DSoundHandle(int handle);

	/// <summary>バックグラウンドハンドル設定</summary>
	void SetBackSoundHandle(int handle);

	/// <summary>サウンド更新</summary>
	void SoundUpdate();

	/// <summary>サウンド再生設定</summary>
	void SetPlaySound(int handle, int volume = -1);

	/// <summary>3Dサウンド再生設定</summary>
	void SetPlay3DSound(int handle, VECTOR position, int volume = -1);

	/// <summary>3Dのリスナー位置を設定</summary>
	/// <param name="position">現在地</param>
	/// <param name="frontPosition">向いてる方向</param>
	void Set3DListenerPosition(VECTOR position, VECTOR frontPosition) { Set3DSoundListenerPosAndFrontPos_UpVecY(position, frontPosition); }

	/*----------*/
	/*【エフェクト】
	/*----------*/
	// FIXME: フェードで非同期している影響でハンドル取得時エラーが出る
private:
	// エフェクトハンドルコンテナ
	HandleContainer<std::string>* mpEffectHandleContainer;

	// // エフェクトハンドル
	// std::map<std::string, std::vector<int>> mmEffectHandle;
	// // エフェクトカウンター
	// std::map<int, int> mmEffectCount;

	// エフェクト描画フラグ
	bool mbEffectDrawFlag;

	// エフェクト描画時使用画像ハンドル
	int mnEffectDrawPreHandle;

public:
	/// <summary>エフェクト情報取得</summary>
	int GetEffectResource(std::string fileName, float size = 1.0f);

	/// <summary>エフェクトハンドルを取得する</summary>
	int GetEffectHandle(int handle, int oldHandle);

	/// <summary>再生中エフェクトハンドルを削除する</summary>
	void DeletePlayEffectHandle(int handle);

	/// <summary>情報エフェクトハンドルのカウントを減らす</summary>
	/// <param name="handle">エフェクト情報ハンドル</param>
	void ReduceEffectDataHandle(int handle);

	/// <summary>エフェクト描画</summary>
	void DrawEffect(int handle, VECTOR position, VECTOR angle = UtilCalc::VZero, VECTOR size = UtilCalc::VOne);

	/// <summary>エフェクト停止</summary>
	void StopEffect(int handle);
	/// <summary>エフェクト再生</summary>
	void PlayEffect(int handle, float speed);

	/// <summary>全エフェクト停止</summary>
	void StopAllEfect();

	/// <summary>全エフェクト再生開始</summary>
	void PlayAllEfect();

private:
	/// <summary>エフェクト初期化</summary>
	void EffectInit();

	/// <summary>エフェクト終了</summary>
	void EffectFinalize();

	/// <summary>エフェクト描画処理</summary>
	void EffectDrawProcess();
};