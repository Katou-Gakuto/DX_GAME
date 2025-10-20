#pragma once
#include <string>
#include <vector>

#include "BitFlag.h"
#include "Status.h"

#include "DxLib.h"

enum class SCENE;

// 種類と名前のデータ
typedef struct TypeAndNameData
{
	std::string name;
	long long typeNumber = 0;
}NAME_TYPE_DATA;

// ファイル名:name;_ファイル種類:typeNumber;_シーン:sceneType;
typedef struct FileData : public NAME_TYPE_DATA
{
	SCENE sceneType;
}FILE_DATA;

// キャラクターのデータ
typedef struct CharacterData : public NAME_TYPE_DATA
{
	BIT_FLAG<unsigned int> survivalFlag;	// 生存フラグ

	STATUS status;	// ステータス

	SCENE mapType;	// マップ

	VECTOR position;	// ポジション

	VECTOR angle;	// 方向

}CHARACTER_DATA;

// プレイヤーデータ
typedef struct PlayerData : public CHARACTER_DATA
{
	std::string playerFolderName;	// プレイヤー情報があるフォルダー名

	SCENE townType;	// 町
	
	bool dataFlag;	// データが存在するかどうか
}PLAYER_DATA;

// レベルデータ
typedef struct LevelData
{
	int maxLevelNumber; // 最大レベル
	std::vector<int> levelNumber;   // レベル
	std::vector<int> levelUpExpNumber;  // 次のレベルまで必要な経験値

	int characterType;	// キャラクターの種類
	STATUS upStatus;	// 成長倍率
}LEVEL_DATA;

// 情報の集まり
union DATAS
{
	/*---* データ *---*/
	/*---*        *---*/

	DATAS()
	{
	}

	~DATAS()
	{
	}
};

// 一つ分のデータ
typedef struct OneData : public NAME_TYPE_DATA
{
	DATAS datas;	// データ

	bool dataChangeFlag = false;	// 変更フラグ

	OneData(const OneData& src)
	{
	}

	OneData()
	: NAME_TYPE_DATA()
	{
	}

	~OneData()
	{
	}

	OneData& operator=(const OneData& src)
	{
		return *this;
	}

}ONE_DATA;

// プレイデータ全部
typedef struct OnePlayerAllData
{
	PLAYER_DATA playerData;	// プレイヤーデータ

	std::vector<ONE_DATA> oneDatas;	// データ1つ分を全部

	bool dataFLag;	// データが存在しているか
}ONE_PLAYER_ALL_DATA;