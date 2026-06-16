#include <vector>

#include "BitFlag.h"
#include "TileData.h"

#include "DxLib.h"

#include "MapManager.h"
#include "ObjectBase.h"
#include "UtilCalc.h"

// タイルデータ
TileData::TileData()
: tileType(TileType::None)
, tileDisplacedPos(UtilCalc::VZero)
, tileFlag(BIT_FLAG<unsigned long long>(0))
, tilePos(TilePos())
{
	adjacentData.clear();
}
// タイルデータ
TileData::TileData(bool flag)
: tileType(TileType::Ground)
, tileDisplacedPos(UtilCalc::VZero)
, tileFlag(BIT_FLAG<unsigned long long>(flag ? 1 : 0))
, tilePos(TilePos())
{
	adjacentData.clear();
}

// タイル処理
TilePos TileData::TileProcess(CharacterBase* character, MapManager* mapManager)
{
	std::vector<TilePos> characterPos;
	characterPos.clear();
	TilePos pos;
	
	{
		mapManager->GetMapPos(pos.x, pos.z, VGet(character->GetMovePos().x + (character->GetSize().x * 0.5f), 0, character->GetMovePos().z + (character->GetSize().z * 0.5f)));
		if ((pos.x != this->tilePos.x) || (pos.z != this->tilePos.z))
		{
			characterPos.push_back(pos);
		}
	}
	{
		mapManager->GetMapPos(pos.x, pos.z, VGet(character->GetMovePos().x - (character->GetSize().x * 0.5f), 0, character->GetMovePos().z + (character->GetSize().z * 0.5f)));
		if ((pos.x != this->tilePos.x) || (pos.z != this->tilePos.z))
		{
			characterPos.push_back(pos);
		}
	}
	{
		mapManager->GetMapPos(pos.x, pos.z, VGet(character->GetMovePos().x + (character->GetSize().x * 0.5f), 0, character->GetMovePos().z - (character->GetSize().z * 0.5f)));
		if ((pos.x != this->tilePos.x) || (pos.z != this->tilePos.z))
		{
			characterPos.push_back(pos);
		}
	}
	{
		mapManager->GetMapPos(pos.x, pos.z, VGet(character->GetMovePos().x - (character->GetSize().x * 0.5f), 0, character->GetMovePos().z - (character->GetSize().z * 0.5f)));
		if ((pos.x != this->tilePos.x) || (pos.z != this->tilePos.z))
		{
			characterPos.push_back(pos);
		}
	}

	for (int i = 0; i < this->adjacentData.size(); i++)
	{
		for (int j = 0; j < characterPos.size(); j++)
		{
			if (this->adjacentData[i] == characterPos[j])
			{
				// TODO: 何か書く
				switch (*(this->adjacentData[i].tileFlag) & 0xffff'ffff'ffff'ff00ull)
				{
				default:
					break;
				}
				characterPos.erase(characterPos.begin() + j);
				j--;
			}
		}
	}

	mapManager->GetMapPos(pos.x, pos.z, VGet(character->GetMovePos().x, 0, character->GetMovePos().z));
	if (pos != this->tilePos)
	{
		for (int i = 0; i < this->adjacentData.size(); i++)
		{
			if (this->adjacentData[i] == pos)
			{
				if (*(this->adjacentData[i].tileFlag) & 0b1ull)
				{
					return pos;
				}
				break;
			}
		}

		for (int tileDirectionType = 0; tileDirectionType < TILE_DIRECTION_TYPE::MAX; tileDirectionType++)
		{
			TilePos checkPos = pos;
			switch (tileDirectionType)
			{
			case TILE_DIRECTION_TYPE::X_DIRECTION:
				checkPos.x = this->tilePos.x;
				break;

			case TILE_DIRECTION_TYPE::Z_DIRECTION:
				checkPos.z = this->tilePos.z;
				break;
			}

			for (int i = 0; i < this->adjacentData.size(); i++)
			{
				if (this->adjacentData[i] == checkPos)
				{
					if (*(this->adjacentData[i].tileFlag) & 0b1ull)
					{

						VECTOR norm = VGet((float)(this->adjacentData[i].x - pos.x), 0.0f, (float)(this->adjacentData[i].z - pos.z));

						// 進行ベクトルと、壁の法線ベクトルの内情の逆を係数aとしておく
						float a = -VDot(character->GetVec(), norm);

						character->SetVec(VAdd(VAdd(character->GetVec(), VScale(norm, a)), VScale(norm, 0.001f)));

						pos = this->adjacentData[i];
						return pos;
					}
				}
			}
		}

		VECTOR norm = VGet((float)(this->tilePos.x - pos.x), 0.0f, (float)(this->tilePos.z - pos.z));

		// 進行ベクトルと、壁の法線ベクトルの内情の逆を係数aとしておく
		float a = -VDot(character->GetVec(), norm);

		character->SetVec(VAdd(VAdd(character->GetVec(), VScale(norm, a)), VScale(norm, 0.001f)));
	}
	return this->tilePos;
}