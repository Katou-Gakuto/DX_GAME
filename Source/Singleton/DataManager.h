#pragma once
#include <list>
#include <map>
#include <vector>
#include <Windows.h>

#include "SceneEnum.h"
#include "GameDatas.h"

class EndManager;

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

	/*----------------*/
	/*【ゲームデータ】*/
	/*----------------*/

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

	// ダンジョンの削除キャラクターID
	int mnDungeonDeleteCharacterID;

public:

	/*--------*/
	/*【処理】*/
	/*--------*/

	/*データを保存*/
	void Save();

	/*プレイ中データに設定されたデータを削除する*/
	void PlayDataDelete(int playerNumber);

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

	/*ダンジョンの削除キャラクターID取得*/
	inline void SetDungeonDeleteCharacterID(int dungeonDeleteCharacterID) { mnDungeonDeleteCharacterID = dungeonDeleteCharacterID; }

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

	/*ダンジョンの削除キャラクターID取得*/
	inline int GetDungeonDeleteCharacterID() const { return mnDungeonDeleteCharacterID; }

private:
	/// <summary>
	/// ベースファイル設定
	/// </summary>
	/// <param name="fileName">ベースファイルのファイル名があるファイル</param>
	void SetBaseFile(std::string fileName);
};