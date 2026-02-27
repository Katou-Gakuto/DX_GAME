#include <fstream>
#include <string>
#include <vector>

#include "BitFlag.h"
#include "CollisionData.h"
#include "MinMapData.h"
#include "ResourceData.h"
#include "TargetData.h"
#include "TileData.h"

#include "DxLib.h"

#include "Master.h"

#include "DataManager.h"
#include "EndManager.h"
#include "GameManager.h"
#include "MapManager.h"
#include "ModelMap.h"
#include "ResourceManager.h"
#include "TargetManager.h"
#include "UtilCalc.h"

MapManager::MapManager()
: mvTileHalfSize(VGet(250.0f, 0.0f, 250.0f))
, mvMapMinPos(VGet(250.0f, 0.0f, 250.0f))
, mstPreDisplaySize()
, mnDrawMinMapScreenHandle(-1)
{
    mpModelMap = new ModelMap();
    mpModelMap->Initilize();

    mstMapData.clear();
}
MapManager::~MapManager()
{
}

// データ解放
void MapManager::Release()
{
    if (mnDrawMinMapScreenHandle != -1)
    {
        DeleteGraph(mnDrawMinMapScreenHandle);
        mnDrawMinMapScreenHandle = -1;
    }

    // モデルデータ解放
    mpModelMap->ReleaseMapModel();
    mstMapData.clear();
}


// マップ情報設定
void MapManager::SetMapData(MapType mapType)
{
    // データ解放
    Release();

    //mstMapData = Master::mpDataManager->GetMapData(mapType);
    switch (mapType)
    {
    case MapType::None:
        break;

    case MapType::Normal:
        mstMapData = {
            { TileData(true), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true) },
            { TileData(true), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true) },
            { TileData(true), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true) },
            { TileData(true), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true) },
            { TileData(true), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true) },
            { TileData(true), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true) },
            { TileData(true), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true) },
            { TileData(true), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true) },
        };
        break;

    case MapType::Battle:
        mstMapData = {
            { TileData(true), TileData(), TileData(), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true) },
            { TileData(true), TileData(true), TileData(), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true) },
            { TileData(), TileData(), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true) },
            { TileData(), TileData(), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true) },
            { TileData(), TileData(), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true) },
            { TileData(), TileData(), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true) },
            { TileData(), TileData(), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true) },
            { TileData(), TileData(), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true), TileData(true) },
        };
        break;
    }

    for (int z = 0; z < mstMapData.size(); z++)
    {
        for (int x = 0; x < mstMapData[z].size(); x++)
        {
            mstMapData[z][x].tilePos = TilePos(x, z);

            for (int zPos = -1; zPos <= 1; zPos++)
            {
                for (int xPos = -1; xPos <= 1; xPos++)
                {
                    if (((z + zPos) >= 0) && ((x + xPos) >= 0) &&
                        ((z + zPos) < mstMapData.size()) && ((x + xPos) < mstMapData[z + zPos].size()) &&
                        !(((z + zPos) == z) && ((x + xPos) == x)))
                    {
                        mstMapData[z][x].adjacentData.push_back(TilePos(x + xPos, z + zPos));

                        mstMapData[z][x].adjacentData[mstMapData[z][x].adjacentData.size() - 1].tileFlag = &mstMapData[z + zPos][x + xPos].tileFlag;
                    }
                }
            }
        }
    }

    // マップデータをモデルに読み込ませる
    mpModelMap->LoadMapData(mstMapData, mvMapMinPos, mvTileHalfSize);
}

// マップ情報設定
void MapManager::SetMapData(std::vector<std::vector<TileData>> mapData)
{
    mstMapData = mapData;
    /*
    * マップタイルに応じた処理
    */
}

// マップ当たり判定
void MapManager::MapCollision()
{
    if (mstMapData.size() > 0)
    {
        Master::mpGameManager->GetTargetManager()->SetTarget(CharacterCollision(Master::mpGameManager->GetTargetManager()->GetTargets(TARGET_TYPE::PLAYER)), TARGET_TYPE::PLAYER);
        Master::mpGameManager->GetTargetManager()->SetTarget(CharacterCollision(Master::mpGameManager->GetTargetManager()->GetTargets(TARGET_TYPE::ENEMY)), TARGET_TYPE::ENEMY);
        // std::vector<CharacterTargetData> character = Master::mpGameManager->GetTargetManager()->GetTargets(TARGET_TYPE::ENEMY);
        // character.push_back(Master::mpGameManager->GetTargetManager()->GetTarget(TARGET_TYPE::PLAYER));

        // for (int i = 0; i < character.size(); i++)
        // {
        //     if ((character[i].mapPosZ >= 0) && (character[i].mapPosX >= 0) &&
        //         (character[i].mapPosZ < mstMapData.size()) && (character[i].mapPosX < mstMapData[character[i].mapPosZ].size()))
        //     {
        //         TilePos tilePos = mstMapData[character[i].mapPosZ][character[i].mapPosX].TileProcess(character[i], this);
        //         if (tilePos != TilePos(character[i].mapPosX, character[i].mapPosZ))
        //         {
        //             character[i].mapPosX = tilePos.x;
        //             character[i].mapPosZ = tilePos.z;
        //         }
        //         //for (int j = 0; j < mstMapData[character[i].mapPosZ][character[i].mapPosX].adjacentData.size(); j++)
        //         //{
        //         //}
        //     }
        //     else
        //     {
        //         Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::MAP_FLAG);
        //     }
        // }


        /*
        // 反射後速度を算出
        VECTOR N = VNorm(collision->vec);

        D3DXVec3Normalize(&N, pNormal);
        *pOut_velo = *pVelo - (1 + res) * D3DXVec3Dot(&N, pVelo) * N;

        // 移動位置を計算
        *pOut_pos = *pColliPos + *pOut_velo * time;
        */
        /*if (UtilCalc::BoxCollision(VAdd(collision->position, VScale(UtilCalc::VOne, collision->size * 0.5f)), VSub(collision->position, VScale(UtilCalc::VOne, collision->size * 0.5f)),
                                   VAdd(collision->position, VScale(UtilCalc::VOne, collision->size * 0.5f)), VSub(collision->position, VScale(UtilCalc::VOne, collision->size * 0.5f))))
        {
            VECTOR norm = VGet(0.0f, 0.0f, 1.0f);

            // 進行ベクトルと、壁の法線ベクトルの内情の逆を係数aとしておく
            float a = -VDot(collision->vec, norm);

            collision->vec = VAdd(VAdd(collision->vec, VScale(norm, a)), VScale(norm, 1.0f));
        }*/
    }
}

// キャラクターとの当たり判定
std::vector<CharacterTargetData> MapManager::CharacterCollision(std::vector<CharacterTargetData> characterData)
{
    for (int i = 0; i < characterData.size(); i++)
    {
        if ((characterData[i].mapPosZ >= 0) && (characterData[i].mapPosX >= 0) &&
            (characterData[i].mapPosZ < mstMapData.size()) && (characterData[i].mapPosX < mstMapData[characterData[i].mapPosZ].size()))
        {
            TilePos tilePos = mstMapData[characterData[i].mapPosZ][characterData[i].mapPosX].TileProcess(characterData[i], this);
            if (tilePos != TilePos(characterData[i].mapPosX, characterData[i].mapPosZ))
            {
                characterData[i].mapPosX = tilePos.x;
                characterData[i].mapPosZ = tilePos.z;
            }
        }
        else
        {
            Master::mpEndManager->SetEndFlag(true, END_FLAG_NUMBER::MAP_FLAG);
        }
    }

    return characterData;
}

// マップポジション取得
void MapManager::GetMapPos(int& setPosX, int& setPosZ, VECTOR pos)
{
    setPosX = (int)((pos.x + mvMapMinPos.x) / GetTileSize().x);
    setPosZ = (int)((pos.z + mvMapMinPos.z) / GetTileSize().z);

    if ((pos.x + mvMapMinPos.x) < 0.0f)
    {
        setPosX -= 1;
    }
    if ((pos.z + mvMapMinPos.z) < 0.0f)
    {
        setPosZ -= 1;
    }
}

// 描画
void MapManager::Draw()
{
    mpModelMap->ModelDraw();
    // for (int z = 0; z < mstMapData.size(); z++)
    // {
    //     for (int x = 0; x < mstMapData[z].size(); x++)
    //     {
    //         TileData& tile = mstMapData[z][x];
    //         VECTOR drawPos = VGet(tile.tileDisplacedPos.x + (x * GetTileSize().x), tile.tileDisplacedPos.y, tile.tileDisplacedPos.z + (z * GetTileSize().z));

    //         switch (tile.tileType)
    //         {
    //         case TileType::Ground:
    //             // 左奥
    //             DrawTriangle3D(VGet(drawPos.x + mvTileHalfSize.x, drawPos.y, drawPos.z + mvTileHalfSize.z),
    //                 VGet(drawPos.x - mvTileHalfSize.x, drawPos.y, drawPos.z + mvTileHalfSize.z),
    //                 VGet(drawPos.x - mvTileHalfSize.x, drawPos.y, drawPos.z - mvTileHalfSize.z),
    //                 GetColor(0, 0, 255),
    //                 TRUE);

    //             // 右手前
    //             DrawTriangle3D(VGet(drawPos.x + mvTileHalfSize.x, drawPos.y, drawPos.z - mvTileHalfSize.z),
    //                 VGet(drawPos.x + mvTileHalfSize.x, drawPos.y, drawPos.z + mvTileHalfSize.z),
    //                 VGet(drawPos.x - mvTileHalfSize.x, drawPos.y, drawPos.z - mvTileHalfSize.z),
    //                 GetColor(0, 0, 255),
    //                 TRUE);
    //             break;
    //         }
    //     }
    // }
}