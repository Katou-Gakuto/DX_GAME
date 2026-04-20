#pragma once
#include <list>
#include <map>
#include <vector>
#include <Windows.h>

#include "SceneEnum.h"
#include "GameDatas.h"
#include "Status.h"
#include "TileData.h"
#include "Vector2.h"

enum class MapType;
struct TileData;

class EndManager;
class CharacterBase;

class DataManager
{
private:
	// ウィンドウメッセージ
	MSG mwMsg;

	// 終了マネージャー
	EndManager* mpEndManger;

public:
	DataManager();
	~DataManager();

	/*初期化*/
	void Initilize();

	/// <summary>
	/// ウィンドウメッセージ取得
	/// </summary>
	inline MSG* GetMsg() { return &mwMsg; }

	/// <summary>
	/// ウィンドウメッセージ設定
	/// </summary>
	inline void SetMsg(MSG msg) { mwMsg = msg; }

	/*--------------------------*/
	/*     【ゲームデータ】     */
	/*--------------------------*/

private:
	// プレイ中のプレイヤーデータ
	ONE_PLAYER_ALL_DATA mstPlayPlayerData;
	// プレイ中のセーブ番号
	int mnPlayPlayerNumber;

	// ベースのデータ
	ONE_PLAYER_ALL_DATA mstBaseData;

	// 初期化用プレイヤーデータ
	std::vector<PLAYER_DATA> mstInitPlayerDatas;

	// 選択用プレイヤー
	std::vector<PLAYER_DATA> mstPlayerDatas;
	// 全プレイヤー共通部分ファイル名
	std::string msPlayerDatasFileName;

	// 取得済みデータ場所保存用
	std::map<SCENE, std::list<int>> mmGetFilePosNumbers;

	// アイテム作成後// 削除予定アイテム名

	// ダンジョンの削除キャラクター情報
	DELETE_CHARACTER_DATA mnDungeonDeleteCharacterData;

	// 町の削除キャラクター情報
	DELETE_CHARACTER_DATA mnTownDeleteCharacterData;

	// 獲得経験値
	int mnAcquisitionExp;

public:

	/*--------*/
	/*【処理】*/
	/*--------*/

	/*データを保存*/
	void Save(CharacterBase* playerObject);

	/*プレイ中データに設定されたデータを削除する*/
	void PlayDataDelete(int playerNumber);

	/*--------*/
	/*【削除】*/
	/*--------*/

	/// <summary>エネミーデータ削除</summary>
	void DeleteEnemyData(SCENE deleteScene);

	/*--------*/
	/*【変更】*/
	/*--------*/

	/*プレイヤーデータ設定*/
	inline void SetChangePlayerData(PLAYER_DATA data, int playerNumber) { for(int i=0; i<mstPlayerDatas.size(); ++i){ if(i==playerNumber){ mstPlayerDatas[i]=data; } } }
	/*一種類分データを変更*/
	inline void ChangeOneData(ONE_DATA data, std::string fileName, int fileType){ if(mstPlayPlayerData.dataFlag){ for(int i=0; i<mstPlayPlayerData.oneDatas.size(); i++){ if((mstPlayPlayerData.oneDatas[i].name==fileName)&&(mstPlayPlayerData.oneDatas[i].typeNumber==fileType)){ data.dataChangeFlag|=(mstPlayPlayerData.oneDatas[i]!=data); mstPlayPlayerData.oneDatas[i]=data; } } } }
	/*全データを変更*/
	inline void ChangeAllData(std::vector<ONE_DATA> data) { mstPlayPlayerData.oneDatas = data; }

	/*--------*/
	/*【設定】*/
	/*--------*/

	/*プレイヤー設定*/
	void SetPlayPlayer(int playerNumber);

	/*プレイプレイヤーデータ設定*/
	inline void SetPlayPlayerData(const PLAYER_DATA& data) { mstPlayPlayerData.playerData = data; }

	/// <summary>プレイ中ステータス設定</summary>
	inline void SetPlayPlayerStatus(const STATUS status) { mstPlayPlayerData.playerData.status = status; }

	/// <summary>ダンジョンの削除キャラクターID取得</summary>
	/// <param name="dungeonDeleteCharacterData">ID情報</param>
	inline void SetDungeonDeleteCharacterID(DELETE_CHARACTER_DATA dungeonDeleteCharacterData) { mnDungeonDeleteCharacterData = dungeonDeleteCharacterData; }

	/// <summary>町の削除キャラクターID取得</summary>
	/// <param name="townDeleteCharacterData">ID情報</param>
	inline void SetTownDeleteCharacterID(DELETE_CHARACTER_DATA townDeleteCharacterData) { mnTownDeleteCharacterData = townDeleteCharacterData; }

	/// <summary>キャラクターID設定</summary>
	void SetCharacterID(int id, std::string fileName, int index);

	/*--------*/
	/*【取得】*/
	/*--------*/

	/*プレイプレイヤーデータ取得*/
	inline PLAYER_DATA GetPlayPlayerData() const { return mstPlayPlayerData.playerData; }

	/*プレイヤーデータを取得*/
	inline std::vector<PLAYER_DATA> GetPlayerData() const { return mstPlayerDatas; }

	/*初期化用プレイヤーデータ取得*/
	inline std::vector<PLAYER_DATA> GetInitPlayerData() const { return mstInitPlayerDatas; }

	/*指定のシーンに必要な全データを取得*/
	std::vector<ONE_DATA> GetSceneData(SCENE sceneName);
	/*一種類分データを取得*/
	inline ONE_DATA GetOneData(std::string fileName, int fileType, bool baseFlag = false) const { std::vector<ONE_DATA>oneDatas=GetAllData(baseFlag); for(int i=0; i<oneDatas.size(); ++i) { if((oneDatas[i].typeNumber==fileType)&&(oneDatas[i].name==fileName)){ return oneDatas[i]; } } ONE_DATA nullData; return nullData;}
	/*全データを取得*/
	inline std::vector<ONE_DATA> GetAllData(bool baseFlag = false) const { return (baseFlag ? mstBaseData.oneDatas : mstPlayPlayerData.oneDatas); }

	/*マップデータ取得*/
	std::vector<std::vector<TileData>> GetMapData(MapType tileType);

	/// <summary>獲得経験値取得</summary>
	inline int GetAcquisitionExpQuantity() { return mnAcquisitionExp; }

	/*--------*/
	/*【追加】*/
	/*--------*/

	/// <summary>獲得経験値リセット</summary>
	inline void ResetAcquisitionExp() { mnAcquisitionExp = 0; }

	/*------------*/
	/*【リセット】*/
	/*------------*/

	/// <summary>獲得経験値増やす</summary>
	inline void AddAcquisitionExp(int addExp) { mnAcquisitionExp += addExp; }

private:
	/// <summary>
	/// ベースファイル設定
	/// </summary>
	/// <param name="fileName">ベースファイルのファイル名があるファイル</param>
	void SetBaseFile(std::string fileName);

	/// <summary>シーンに合ったファイル名を取得</summary>
	std::vector<std::string> GetSceneFileNames(SCENE scsene, bool baseFlag);

	/*------------*/
	/*【ウェーブ】*/
	/*------------*/
private:
	// ウェーブ数
	int mnWaveNumber;

	// ウェーブ別エネミーデータ
	std::vector<std::vector<CHARACTER_DATA>> mstWaveEnemyData;

	// ウェーブ別マップデータ
	std::vector<MapType> meWaveMapData;

public:

	/// <summary>ウェーブ進行</summary>
	bool SetNextWave();
	/// <summary>ウェーブ初期化</summary>
	void InitWave();

	/// <summary>ウェーブのエネミーデータ取得</summary>
	std::vector<CHARACTER_DATA> GetWaveEnemy();

	/// <summary>ウェーブのマップ種類取得</summary>
	inline MapType GetWaveMapData() { return meWaveMapData[mnWaveNumber]; }

	/*--------------------------*/
	/*     【マップデータ】     */
	/*--------------------------*/

	// TODO: ファイルから受け取れるようにする
private:
	// マップリソースファイル名保存用変数

public:
	 enum class MAP_RESOURCE_FILE_NUMBWER
	{
		GRTOUND,
	};

	/*マップリリソースファイル名取得*/
	std::string GetMapResourceFileName(MAP_RESOURCE_FILE_NUMBWER fileNumber);

	/*--------------------*/
	/*【コンフィグデータ】*/
	/*--------------------*/
private:
	// ミニマップ感知範囲
	float MiniMapSensedRange;
	// ミニマップ画面描画サイズ
	float MiniMapScreenDrawSize;
	// サウンドの音量
	int mnSeVolume;
	// バックグラウンドミュージックの音量
	int mnBgmVolume;
	// 画面の明るさ
	int mnScreenBrightness;
	// 画面のサイズ
	Vector2_Int mstScreenSize;

public:
	/*--------*/
	/*【取得】*/
	/*--------*/
	/*ミニマップ感知範囲取得*/
	inline float GetMiniMapSensedRange() const { return MiniMapSensedRange; }
	/*ミニマップ感知範囲取得*/
	inline float* GetMiniMapSensedRangePointer() { return &MiniMapSensedRange; }
	/*ミニマップ画面描画サイズ取得*/
	inline float GetMiniMapScreenDrawSize() const { return MiniMapScreenDrawSize; }
	/*ミニマップ画面描画サイズ取得*/
	inline float* GetMiniMapScreenDrawSizePointer() { return &MiniMapScreenDrawSize; }
	/*サウンドの音量取得*/
	inline int GetSeVolume() const { return mnSeVolume; }
	/*サウンドの音量取得*/
	inline int* GetSeVolumePointer() { return &mnSeVolume; }
	/*バックグラウンドミュージックの音量取得*/
	inline int GetBgmVolume() const { return mnBgmVolume; }
	/*バックグラウンドミュージックの音量取得*/
	inline int* GetBgmVolumePointer() { return &mnBgmVolume; }
	/*画面の明るさ取得*/
	inline int GetScreenBrightness() const { return mnScreenBrightness; }
	/*画面の明るさ取得*/
	inline int* GetScreenBrightnessPointer() { return &mnScreenBrightness; }
	/*画面のサイズ取得*/
	inline Vector2_Int GetScreenSize() const { return mstScreenSize; }
	/*画面のサイズ取得*/
	inline Vector2_Int* GetScreenSizePointer() { return &mstScreenSize; }

	/*--------*/
	/*【設定】*/
	/*--------*/
	/*ミニマップ感知範囲設定*/
	inline void SetMiniMapSensedRange(float range) { MiniMapSensedRange = range; }
	/*ミニマップ画面描画サイズ設定*/
	inline void SetMiniMapScreenDrawSize(float size) { MiniMapScreenDrawSize = size; }
	/*サウンドの音量設定*/
	inline void SetSeVolume(int volume) { mnSeVolume = volume; }
	/*バックグラウンドミュージックの音量設定*/
	inline void SetBgmVolume(int volume) { mnBgmVolume = volume; }
	/*画面の明るさ設定*/
	inline void SetScreenBrightness(int brightness) { mnScreenBrightness = brightness; }
	/*画面のサイズ設定*/
	inline void SetScreenSize(Vector2_Int size) { mstScreenSize = size; }
};