#pragma once
#include <string>

#include "ResourceData.h"
#include "UtilCalc.h"

class Resource3DModel;
class ResourceGraph;
class ResourceMovie;
class ResourceSound;
class ResourceEffect;

class ResourceManager
{
	/*--------*/
	/*【共通】*/
	/*--------*/

public:
	// リソースファイルの名前
	static std::string msResourceFile;
	// ディスプレイサイズ
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
	/*【描画】*/
	/*----------*/
private:
	// シャドウマップハンドル
	int mnShadowMapHandle;
	
	// シャドウ描画中フラグ
	bool mbDrawShadowMapFlag;

private:
	/// <summary>シャドウマップの初期化</summary>
	void ShadowMapInit();

	/*----------*/
	/*【取得】*/
	/*----------*/
	/// <summary>シャドウマップ描画フラグ</summary>
	inline bool GetShadowMapDrawFlag() const { return mbDrawShadowMapFlag; }

	/*------------*/
	/*【3Dモデル】*/
	/*------------*/
private:
	Resource3DModel* mp3DModelResource;
public:
	/// <summary>3Dモデルリソース取得</summary>
	Resource3DModel* Get3DModelResource() { return mp3DModelResource; }

	// int GetModelHandle(std::string fileName);
	// void ReduceModelHandle(int handle);

	/*--------*/
	/*【画像】*/
	/*--------*/
public:

private:
	ResourceGraph* mpGraphResource;
	ResourceDivGraph* mpDivGraphResource;


public:
	/// <summary>画像リソース取得</summary>
	ResourceGraph* GetGraphResource() { return mpGraphResource; }
	/// <summary>分割画像リソース取得</summary>
	ResourceDivGraph* GetDivGraphResource() { return mpDivGraphResource; }
	// int GetGraphHandle(std::string fileName);
	// void ReduceGraphHandle(int handle);
	// void GetDivGraphHandle(std::string fileName, DIV_GRAPH_DATA* graphData);
	// void ReduceDivGraphHandle(int number);

	/*--------*/
	/*【動画】*/
	/*--------*/
private:
	ResourceMovie* mpMovieResource;

public:
	/// <summary>動画リソース取得</summary>
	ResourceMovie* GetMovieResource() { return mpMovieResource; }

	// int GetMovieHandle(std::string fileName);
	// void ReduceMovie(int handle);
	// void PlayMovie(int handle);
	// void StopMovie(int handle);
	// void MovieReset(int handle);
	// void MovieLoop(int handle);

	/*------------*/
	/*【サウンド】*/
	/*------------*/
public:
	enum SOUND_RESOURCE_TYPE
	{
		SOUND = 0,
		SOUND_3D,
		SOUND_RESOURCE_TYPE_MAX
	};
private:
	ResourceSound* mpSoundResource[SOUND_RESOURCE_TYPE::SOUND_RESOURCE_TYPE_MAX];

public:
	/// <summary>サウンドリソース取得</summary>
	ResourceSound* GetSoundResource() { return mpSoundResource[SOUND_RESOURCE_TYPE::SOUND]; }
	/// <summary>3Dサウンドリソース取得</summary>
	ResourceSound* GetSoundResource() { return mpSoundResource[SOUND_RESOURCE_TYPE::SOUND_3D]; }

	// int GetSoundHandle(std::string fileName);
	// void ReduceSoundHandle(int handle);
	// int Get3DSoundHandle(std::string fileName);
	// void Reduce3DSoundHandle(int handle);
	// void SetBackSoundHandle(int handle);
	// void SoundUpdate();
	// void SetPlaySound(int handle, int volume = -1);
	// void SetPlay3DSound(int handle, VECTOR position, int volume = -1);
	// void Set3DListenerPosition(VECTOR position, VECTOR frontPosition);

	/*----------*/
	/*【エフェクト】*/
	/*----------*/
private:
	ResourceEffect* mpEffectResource;

public:
	/// <summary>エフェクトリソース取得</summary>
	ResourceEffect* GetEffectResource() { return mpEffectResource; }

	// int GetEffectResource(std::string fileName, float size = 1.0f);
	// int GetEffectHandle(int handle, int oldHandle);
	// void DeletePlayEffectHandle(int handle);
	// void ReduceEffectDataHandle(int handle);
	// void DrawEffect(int handle, VECTOR position, VECTOR angle = UtilCalc::VZero, VECTOR size = UtilCalc::VOne);
	// void StopEffect(int handle);
	// void PlayEffect(int handle, float speed);
	// void StopAllEfect();
	// void PlayAllEfect();
};
