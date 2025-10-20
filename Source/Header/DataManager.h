#pragma once
#include <list>
#include <map>
#include <vector>
#include <Windows.h>

#include "GameDatas.h"

#include "SceneManager.h"

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

public:
	inline PLAYER_DATA GetPlayPlayerData() const { return mstPlayPlayerData.playerData; }

private:
	/// <summary>
	/// ベースファイル設定
	/// </summary>
	/// <param name="fileName">ベースファイルのファイル名があるファイル</param>
	void SetBaseFile(std::string fileName);
};