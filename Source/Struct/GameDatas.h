#pragma once
#include <string>
#include <vector>

#include "BitFlag.h"
#include "Status.h"

#include "DxLib.h"

enum class SCENE;

enum class DATA_TYPE
{
	FILE_NAME = 0,
	CHARACTER,
	PLAYER,
	INIT_PLAYER,
	LEVEL,
};

// 種類と名前のデータ
typedef struct TypeAndNameData
{
	std::string name = "";
	long long typeNumber = 0;

	bool operator==(TypeAndNameData src)
	{
		if ((this->name != src.name) || (this->typeNumber != src.typeNumber))
		{
			return false;
		}

		return true;
	}
	bool operator!=(TypeAndNameData src)
	{
		return !(*this == src);
	}
}NAME_TYPE_DATA;

// ファイル名:name;_ファイル種類:typeNumber;_シーン:sceneType;
typedef struct FileData : public NAME_TYPE_DATA
{
	SCENE sceneType;


	bool operator==(FileData src)
	{
		if ((this->name != src.name) || (this->typeNumber != src.typeNumber) || (this->sceneType != src.sceneType))
		{
			return false;
		}

		return true;
	}
	bool operator!=(FileData src)
	{
		return !(*this == src);
	}
}FILE_DATA;

// キャラクターのデータ
typedef struct CharacterData : public NAME_TYPE_DATA
{
	BIT_FLAG<unsigned int> survivalFlag;	// 生存フラグ

	STATUS status;	// ステータス

	SCENE mapType;	// マップ

	VECTOR position;	// ポジション

	VECTOR angle;	// 方向

	// TODO: 残しておかないと町に戻るときにバグる可能性あり
	int objectID;	// オブジェクトID


	bool operator==(CharacterData src)
	{
		if ((this->name != src.name) || (this->typeNumber != src.typeNumber) || (this->survivalFlag != src.survivalFlag) || (this->status != src.status) || (this->mapType != src.mapType))
		{
			return false;
		}

		return true;
	}
	bool operator!=(CharacterData src)
	{
		return !(*this == src);
	}
}CHARACTER_DATA;

// プレイヤーデータ
typedef struct PlayerData : public CHARACTER_DATA
{
	std::string playerFolderName;	// プレイヤー情報があるフォルダー名

	SCENE townType;	// 町
	SCENE dungeonType;	// ダンジョン
	SCENE preMap;	// 前居たマップ

	VECTOR townPos;	// 町ポジション
	VECTOR dungeonPos;	// ダンジョンポジション
	
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


	bool operator==(LevelData src)
	{
		if ((this->maxLevelNumber != src.maxLevelNumber) || (this->characterType != src.characterType) || (this->upStatus != src.upStatus) || (this->levelNumber.size() != src.levelNumber.size()) || (this->levelUpExpNumber.size() != src.levelUpExpNumber.size()))
		{
			return false;
		}

		for (int i = 0; i < this->levelNumber.size(); i++)
		{
			if (this->levelNumber[i] != src.levelNumber[i])
			{
				return false;
			}
		}

		for (int i = 0; i < this->levelUpExpNumber.size(); i++)
		{
			if (this->levelUpExpNumber[i] != src.levelUpExpNumber[i])
			{
				return false;
			}
		}

		return true;
	}
	bool operator!=(LevelData src)
	{
		return !(*this == src);
	}

}LEVEL_DATA;

// 情報の集まり ここら辺修正予定
struct DATAS
{
	/*---* データ *---*/
	std::vector<FILE_DATA> fileNameDatas;       // ファイルネームデータズ
	std::vector<CHARACTER_DATA> characterDatas; // キャラクターデータズ
	LEVEL_DATA levelData;                       // レベルデータ
	/*---*        *---*/

	DATAS()
	{
		levelData.levelNumber.clear();
		levelData.levelUpExpNumber.clear();
		levelData.maxLevelNumber = 0;
		levelData.characterType = 0;
		levelData.upStatus = STATUS();
	}
	~DATAS()
	{
		levelData.levelNumber.clear();
		levelData.levelUpExpNumber.clear();
		levelData.maxLevelNumber = 0;
		levelData.characterType = 0;
		levelData.upStatus = STATUS();
	}

	bool operator==(DATAS src)
	{
		// データの中身が完成したら作る
		return false;
	}

	bool operator!=(DATAS src)
	{
		// データの中身が完成したら作る
		return false;
	}
};

// 一つ分のデータ
typedef struct OneData : public NAME_TYPE_DATA
{
	DATAS datas;	// データ

	bool dataChangeFlag = false;	// 変更フラグ

	OneData(const OneData& src)
	{
		*this = src;
	}

	OneData()
	: NAME_TYPE_DATA()
	, dataChangeFlag(false)
	{
	}

	~OneData()
	{
	}

	OneData& operator=(const OneData& src)
	{
		this->dataChangeFlag = src.dataChangeFlag;
		this->name = src.name;
		this->typeNumber = src.typeNumber;
		switch (this->typeNumber)
		{
		case (int)DATA_TYPE::FILE_NAME:
			this->datas.fileNameDatas = src.datas.fileNameDatas;
			break;
			
		case (int)DATA_TYPE::CHARACTER:
			this->datas.characterDatas = src.datas.characterDatas;
			break;
			
		case (int)DATA_TYPE::LEVEL:
			this->datas.levelData = src.datas.levelData;
			break;
		}

		return *this;
	}

	bool operator==(OneData src)
	{
		if ((this->dataChangeFlag != src.dataChangeFlag) || (this->name != src.name) || (this->typeNumber != src.typeNumber))
		{
			return false;
		}

		switch (this->typeNumber)
		{
		case (int)DATA_TYPE::FILE_NAME:
			if (this->datas.fileNameDatas.size() != src.datas.fileNameDatas.size())
			{
				return false;
			}
			for (int i = 0; i < this->datas.fileNameDatas.size(); i++)
			{
				if (this->datas.fileNameDatas[i] != src.datas.fileNameDatas[i])
				{
					return false;
				}
			}
			break;

		case (int)DATA_TYPE::CHARACTER:
			if (this->datas.characterDatas.size() != src.datas.characterDatas.size())
			{
				return false;
			}
			for (int i = 0; i < this->datas.characterDatas.size(); i++)
			{
				if (this->datas.characterDatas[i] != src.datas.characterDatas[i])
				{
					return false;
				}
			}

			break;

		case (int)DATA_TYPE::LEVEL:
			if (this->datas.levelData != src.datas.levelData)
			{

			}
			break;
		}

		return true;
	}

	bool operator!=(OneData src)
	{
		return !(*this == src);
	}

}ONE_DATA;

// プレイデータ全部
typedef struct OnePlayerAllData
{
	PLAYER_DATA playerData;	// プレイヤーデータ

	std::vector<ONE_DATA> oneDatas;	// データ1つ分を全部

	bool dataFlag;	// データが存在しているか
}ONE_PLAYER_ALL_DATA;


// 削除予定キャラクター情報
typedef struct DeleteCharacterData
{
	SCENE sceneType;	// シーン種類

	int characterID;	// キャラクターID
}DELETE_CHARACTER_DATA;