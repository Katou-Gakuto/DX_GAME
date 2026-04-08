#pragma once
#include <list>
#include <map>
#include <vector>
#include <Windows.h>

#include "SceneEnum.h"
#include "GameDatas.h"
#include "Status.h"

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

public:

	/// <summary>ウェーブ進行</summary>
	bool SetNextWave();
	/// <summary>ウェーブ初期化</summary>
	void InitWave();

	/// <summary>ウェーブのエネミーデータ取得</summary>
	std::vector<CHARACTER_DATA> GetWaveEnemy();


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
	
// bool imguiSetFlag_Config = true;
// Vector2 pos_Config = Vector2(0.37f, 0.17f);
// float posMove_Config = 0.1f;
// float centerPos_Config = 0.5f;
// Vector2 size_Config = Vector2(0.24f, 0.02f);
// Vector2 buttonSize_Config = Vector2(0.01f, 0.02f);
// DisplaySize graphSize_Config = { Vector2(3221.0f, 218.0f), 0.0f };

	public:
};