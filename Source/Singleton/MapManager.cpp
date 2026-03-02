#include <fstream>
#include <string>
#include <vector>

#include "ImguiEnum.h"
#include "BitFlag.h"
#include "CollisionData.h"
#include "ImguiData.h"
#include "MinMapData.h"
#include "ResourceData.h"
#include "TargetData.h"
#include "TileData.h"
#include "Vector2.h"

#include "DxLib.h"

#include "Master.h"

#include "CameraManager.h"
#include "DataManager.h"
#include "EndManager.h"
#include "GameManager.h"
#include "ImguiManager.h"
#include "MapManager.h"
#include "ModelMap.h"
#include "ResourceManager.h"
#include "TargetManager.h"
#include "UtilCalc.h"

MapManager::MapManager()
: mvTileHalfSize(VGet(250.0f, 0.0f, 250.0f))
, mvMapMinPos(VGet(250.0f, 0.0f, 250.0f))

/*【ミニマップ関係変数】*/
, mstDisplaySize(nullptr)
, mstPreDisplaySize()
, mstMinMapSize()
, mstMinMapCenterPos()
, mstMinMapDrawDistance(Vector2(1000.0f, 0.0f))// HACK: 仮設定
, mnDrawMinMapScreenHandle(-1)
{
    mpModelMap = new ModelMap();
    mpModelMap->Initilize();

    mstMapData.clear();
}
MapManager::~MapManager()
{
}

// 初期化
void MapManager::Initilize()
{
    // 画面の大きさ取得
    mstDisplaySize = &ResourceManager::mstDisplaySize;

    // 初期サイズ設定
    mstMinMapSize = Vector2(0.1f, 0.1f);

    // 中央取得
    mstMinMapCenterPos.x = mstDisplaySize->Left_SeparateRatioWidth(MIN_MAP_LEFT_UP_POS.x, MIN_MAP_LEFT_UP_POS.x + (mstMinMapSize.x * 0.5f/*半分*/));
    mstMinMapCenterPos.y = mstDisplaySize->Up_SeparateRatioHeight( MIN_MAP_LEFT_UP_POS.y, MIN_MAP_LEFT_UP_POS.y + (mstMinMapSize.y * 0.5f/*半分*/));

    // 画像取得初期位置設定
    {
        Vector2_Int setUISize = Vector2_Int(static_cast<int>(mstMinMapSize.x), static_cast<int>(mstMinMapSize.y));
        // 背景
        mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::BACK_GROUND] =
                                    Master::mpResourceManager->GetDrawGraphData(
                                        Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/Red.png"),
                                        Vector2_Int(0, 0),
                                        setUISize
        );
        // 枠
        mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::FRAME] =
                                    Master::mpResourceManager->GetDrawGraphData(
                                        Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/MiniMapWindow.png"),
                                        Vector2_Int(0, 0),
                                        setUISize
        );
        // マスクデータ
        mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::MASK] =
                                    Master::mpResourceManager->GetDrawGraphData(
                                        Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/MiniMapMask.png"),
                                        Vector2_Int(0, 0),
                                        setUISize
        );


        Vector2_Int setCharacterSize = Vector2_Int(mstMinMapCenterPos.Left_SeparateRatioWidth(1.0f, mstMinMapDrawDistance.y/*タイポじゃない*/, true),
                                                   mstMinMapCenterPos.Left_SeparateRatioWidth(1.0f, mstMinMapDrawDistance.y, true));
        // 範囲外キャラ
        mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::MIN_MAP_OUTSIDE_CHARACTER] =
                                    Master::mpResourceManager->GetDrawGraphData(
                                        Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/RobotSphere.png"),
                                        Vector2_Int(),
                                        setCharacterSize
        );
        // 範囲内キャラ
        mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::MIN_MAP_WITHIN_CHARACTER] =
                                    Master::mpResourceManager->GetDrawGraphData(
                                        Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/RobotSphere.png"),
                                        Vector2_Int(),
                                        setCharacterSize
        );

        // プレイヤー
        mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::PLAYER] =
                                    Master::mpResourceManager->GetDrawGraphData(
                                        Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/RobotSphere.png"),
                                        Vector2_Int(static_cast<int>(mstMinMapCenterPos.x), static_cast<int>(mstMinMapCenterPos.y)),
                                        setCharacterSize
        );
    }
}

// 終了
void MapManager::Finalize()
{
    for (int i = 0; i < MIN_MAP_DRAW_GRAPH_TYPE::MAX; i++)
    {
        Master::mpResourceManager->ReduceGraphHandle(mstMinMapDrawGraphData[i].handle);
    }

    if (mnDrawMinMapScreenHandle != -1)
    {
        DeleteGraph(mnDrawMinMapScreenHandle);
        mnDrawMinMapScreenHandle = -1;
    }

    Release();
}

// データ解放
void MapManager::Release()
{
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

// ミニマップ描画長さ変更
bool MapManager::SetMinMapDrawLength(float minMapDrawLength)
{
    if ((minMapDrawLength > MIN_MAP_DRAW_MAX_DISTANCE) ||
        (minMapDrawLength < MIN_MAP_DRAW_MIN_DISTANCE))
    {
        return false;
    }

    mstMinMapDrawDistance.x = minMapDrawLength;

    mstMinMapDrawDistance.y = 1.0f - (mstMinMapDrawDistance.x / MIN_MAP_DRAW_MIN_DISTANCE);

    Vector2_Int setCharacterSize = Vector2_Int(mstMinMapCenterPos.Left_SeparateRatioWidth(1.0f, mstMinMapDrawDistance.y/*タイポじゃない*/, true),
                                               mstMinMapCenterPos.Left_SeparateRatioWidth(1.0f, mstMinMapDrawDistance.y, true));

    mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::MIN_MAP_OUTSIDE_CHARACTER].size =   setCharacterSize;
    mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::MIN_MAP_WITHIN_CHARACTER].size =    setCharacterSize;
    mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::PLAYER].size =  setCharacterSize;
    mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::PLAYER].pos =   Vector2_Int(static_cast<int>(mstMinMapCenterPos.x), static_cast<int>(mstMinMapCenterPos.y));

    return true;
}

// ミニマップ描画
void MapManager::DrawMinMap()
{
#if _DEBUG

	IMGUI_FLOAT_DATA imguiFloatData;
	imguiFloatData.SetVariable(&mstMinMapSize.x);
	imguiFloatData.SetVariable(&mstMinMapSize.y);
	imguiFloatData.SetLabel("MinMapSize_");
	imguiFloatData.SetImguiType(IMGUI_TYPE::DRAG2);
	imguiFloatData.SetMin(-100.0f);
	imguiFloatData.SetMax(100.0f);
    imguiFloatData.SetStep(0.1f);
	imguiFloatData.SetSpeed(0.01f);
    imguiFloatData.SetStepFast(0.1f);

    Master::mpImguiManager->AddDrawImgui(imguiFloatData);
#endif

    // 必要ならハンドル作成
    CreateMinMapScreenHandle(true);

    // 描画物取得
    ALL_MIN_MAP_DRAW_DATA allMinMapDrawData = GetMinMapDrawPos();

    // 描画
    {
        // 描画先を変更
        SetDrawScreen(mnDrawMinMapScreenHandle);
        ClearDrawScreen();

        // ミニマップ外キャラクター描画
        for (int i = 0; i < allMinMapDrawData.minMapOutsideRangeDir.size(); i++)
        {
            mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::MIN_MAP_OUTSIDE_CHARACTER].pos = mstMinMapSize.LeftUp_Ratio(allMinMapDrawData.minMapOutsideRangeDir[i].vectorData);
            Master::mpResourceManager->DrawData_Graph(mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::MIN_MAP_OUTSIDE_CHARACTER]);
        }

        
        // マスクを適用（円の外は透明）// TODO: マスク関連見る
        //SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
        //Master::mpResourceManager->DrawData_Graph(mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::MASK]);
        //SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

        // ミニマップ背景
        Master::mpResourceManager->DrawData_Graph(mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::BACK_GROUND]);
    
        // ミニマップ内キャラクター描画
        for (int i = 0; i < allMinMapDrawData.minMapWithinRangePos.size(); i++)
        {
            mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::MIN_MAP_WITHIN_CHARACTER].pos = mstMinMapSize.LeftUp_Ratio(allMinMapDrawData.minMapWithinRangePos[i].vectorData);
            Master::mpResourceManager->DrawData_Graph(mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::MIN_MAP_WITHIN_CHARACTER]);
        }

        // プレイヤー描画
        Master::mpResourceManager->DrawData_Graph(mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::PLAYER]);
        
        // ミニマップ枠
        Master::mpResourceManager->DrawData_Graph(mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::FRAME]);

        DrawBoxAA(0, 0, 100, 100, GetColor(255, 255, 255), TRUE);
        // 描画先戻す
        SetDrawScreen(DX_SCREEN_BACK);
        // 3Dカメラ設定
        Master::mpGameManager->GetCameraManager()->Draw();
        //SetDrawBlendMode(DX_BLENDMODE_PMA_ALPHA, 128);
        DrawGraph(mstDisplaySize->Left_RatioWidth(MIN_MAP_LEFT_UP_POS.x), mstDisplaySize->Up_RatioHeight(MIN_MAP_LEFT_UP_POS.y), mnDrawMinMapScreenHandle, TRUE);
        //SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
    }
}

// 必要ならミニマップスクリーンハンドル作成する
void MapManager::CreateMinMapScreenHandle(bool createRequiredFlag)
{
    // 必要かどうか調べる
    if (!createRequiredFlag)
    {

        if ((mnDrawMinMapScreenHandle != -1) &&
            UtilCalc::FloatEqual(mstPreDisplaySize.x, mstDisplaySize->x) && UtilCalc::FloatEqual(mstPreDisplaySize.y, mstDisplaySize->y)
            )
        {
            return;
        }

    }
    else
    {
        // 作成済みなら削除して作り直す
        if (mnDrawMinMapScreenHandle != -1)
        {
            DeleteGraph(mnDrawMinMapScreenHandle);
            mnDrawMinMapScreenHandle = -1;
        }
    }
    mstPreDisplaySize = *mstDisplaySize;

    /*
    // 画面サイズ取得
    COORDINATE_X_Y_INT set = XYGet_Int(0, 0);
    int colorBit = 0;
    GetScreenState(&set.x, &set.y, &colorBit);
    /*
    msMapUpperLeft = XYGet((set.x / 10) * 0.2, set.y / 24); // 左上
    msMapLowerRight = XYGet((set.x / 10) * 1.67, set.y / 4);  // 右下*//*
//    /*/
    // msMapUpperLeft = XYGet((set.x / 10) * 8.33 , set.y / 24); // 左上
    // msMapLowerRight = XYGet((set.x / 10) *  9.8, set.y / 4);  // 右下*//*1280, 960*/
    // Vector2 mapSide = Vector2((msMapLowerRight.x - mstPreDisplaySize.x), (msMapLowerRight.y - mstPreDisplaySize.y));
    // Vector2 mapMiddle = Vector2((msMapSide.x / 2) + mnMapFrameDreadth, (msMapSide.y / 2) + mnMapFrameDreadth);

    // mnMapDrawHandle = MakeScreen(msMapSide.x + (mnMapFrameDreadth * 2), msMapSide.y + (mnMapFrameDreadth * 2), TRUE);


    mnDrawMinMapScreenHandle = MakeScreen(mstDisplaySize->Left_SeparateRatioWidth(MIN_MAP_LEFT_UP_POS.x, mstMinMapSize.x, true), 
                                          mstDisplaySize->Up_SeparateRatioHeight( MIN_MAP_LEFT_UP_POS.y, mstMinMapSize.y, true), 
                                          TRUE);

    mstMinMapCenterPos.x = mstDisplaySize->Left_SeparateRatioWidth(MIN_MAP_LEFT_UP_POS.x, mstMinMapSize.x * 0.5f/*半分*/, true);
    mstMinMapCenterPos.y = mstDisplaySize->Up_SeparateRatioHeight( MIN_MAP_LEFT_UP_POS.y, mstMinMapSize.y * 0.5f/*半分*/, true);

    // TODO: 描画情報も変更
    Vector2_Int setUISize = Vector2_Int(static_cast<int>(mstMinMapSize.x), static_cast<int>(mstMinMapSize.y));
    mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::BACK_GROUND].size = Vector2_Int(setUISize);
    mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::FRAME].size =       Vector2_Int(setUISize);
    mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::MASK].size =        Vector2_Int(setUISize);

    Vector2_Int setCharacterSize = Vector2_Int(mstMinMapCenterPos.Left_SeparateRatioWidth(1.0f, mstMinMapDrawDistance.y/*タイポじゃない*/, true),
                                               mstMinMapCenterPos.Left_SeparateRatioWidth(1.0f, mstMinMapDrawDistance.y, true));

    mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::MIN_MAP_OUTSIDE_CHARACTER].size =   setCharacterSize;
    mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::MIN_MAP_WITHIN_CHARACTER].size =    setCharacterSize;
    mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::PLAYER].size =  setCharacterSize;
    mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::PLAYER].pos =   Vector2_Int(static_cast<int>(mstMinMapCenterPos.x), static_cast<int>(mstMinMapCenterPos.y));
}

// ミニマップ表示ポジション取得
ALL_MIN_MAP_DRAW_DATA MapManager::GetMinMapDrawPos()
{
    ALL_MIN_MAP_DRAW_DATA allMinMapDrawData;

    return allMinMapDrawData;
}