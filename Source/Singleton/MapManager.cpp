
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string>
#include <vector>

#include "ImguiEnum.h"
#include "BitFlag.h"
#include "CollisionData.h"
#include "FileLoadingData.h"
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
#include "ObjectBases.h"
#include "ResourceManager.h"
#include "StopManager.h"
#include "TargetManager.h"
#include "UtilCalc.h"
#include "UtilChange.h"
#include "UtilFileLoading.h"

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
, mnMapBackHandle(-1)
, mnMapBackResourceHandle(-1)
{
    mpModelMap = new ModelMap();
    mpModelMap->Initilize();

    mstMapData.clear();

    mstMaskData.maskData = nullptr;
    mstMaskData.maskSize = Vector2_Int(0, 0);
}
MapManager::~MapManager()
{
}

static FLOAT4 testDrawPos = F4Get(10000.0f, 0.9f, 1.0f, 0.0f);
static std::vector<std::vector<bool>> bitFlag;
static float testSize = 50.0f;
// 初期化
void MapManager::Initilize()
{
    mnMapBackHandle = Master::mpResourceManager->GetModelHandle(ResourceManager::msResourceFile + "3D/Sky/SkySphere.mv1");
    MV1SetScale(mnMapBackHandle, VScale(UtilCalc::VOne, 200.0f));
    mnMapBackResourceHandle = Master::mpResourceManager->GetMovieHandle(ResourceManager::msResourceFile + "Movie/TitleBack_1.mp4");
    MV1SetMaterialDrawBlendMode(mnMapBackHandle, 0, DX_BLENDMODE_ALPHA);
    MV1SetMaterialDrawBlendParam(mnMapBackHandle, 0, 200);

    Master::mpImguiManager->SetFloatImgui(IMGUI_FLOAT_DATA::GetImguiData(
        { &testSize },
        0.1f,
        0.1f,
        0.1f,
        0.0f,
        250.0f,
        "TEST_SIZE_BACK_",
        "%f",
        0,
        IMGUI_TYPE::SLIDER1
    )
    );

    // モデルの頂点数を取得
    int vertexCount = (mnMapBackHandle);

    // 画面の大きさ取得
    mstDisplaySize = &ResourceManager::mstDisplaySize;

    // 初期サイズ設定
    mstMinMapSize = mstDisplaySize->LeftDown_SeparateRatio(MIN_MAP_LEFT_UP_POS, Vector2(0.1f, 0.1f), true);

    // 中央取得
    mstMinMapCenterPos = mstMinMapSize.LeftUp_FloatRatio(0.5f);

    // 画像取得初期位置設定
    {
        Vector2_Int setUISize = mstMinMapSize.GetVecInt();
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
        {
            int maskGraphHandle = LoadSoftImage((ResourceManager::msResourceFile + "2D/MiniMapMask.bmp").c_str());
            Vector2_Int maskGraphSize = Vector2_Int(0, 0);
            mstMaskData.maskGraphPixelData.clear();
            //mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::MASK] =
            //    Master::mpResourceManager->GetDrawGraphData(
            //        //LoadMask((ResourceManager::msResourceFile + "2D/MiniMapMask.png").c_str()),
            //        //Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/MiniMapMask.png"),
            //        ,
            //        Vector2_Int(0, 0)/**/,
            //        setUISize//*/
            //    );

            GetSoftImageSize(maskGraphHandle, &maskGraphSize.x, &maskGraphSize.y);
            mstMaskData.maskGraphPixelData.resize(maskGraphSize.y);
            std::vector<std::vector<INT4>> deleteVariable;
            deleteVariable.resize(maskGraphSize.y);
            for (int y = 0; y < maskGraphSize.y; y++)
            {
                deleteVariable[y].resize(maskGraphSize.x);
                mstMaskData.maskGraphPixelData[y].resize(maskGraphSize.x);
                for (int x = 0; x < maskGraphSize.x; x++)
                {
                    deleteVariable[y][x].x = GetPixelSoftImage(maskGraphHandle, x, y,
                        &mstMaskData.maskGraphPixelData[y][x],
                        &deleteVariable[y][x].y,
                        &deleteVariable[y][x].z,
                        &deleteVariable[y][x].w
                    );
                }
            }
            deleteVariable.clear();

            // マスクにデータをセット
            ReSetMask(128, 96);

            DeleteSoftImage(maskGraphHandle);
        }

        Vector2_Int setCharacterSize = Vector2_Int(mstMinMapCenterPos.Left_RatioWidth(mstMinMapDrawDistance.y/*タイポじゃない*/),
            mstMinMapCenterPos.Up_RatioHeight(mstMinMapDrawDistance.y));
        // 範囲外キャラ
        mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::MIN_MAP_OUTSIDE_CHARACTER] =
            Master::mpResourceManager->GetDrawGraphData(
                Master::mpResourceManager->GetGraphHandle(ResourceManager::msResourceFile + "2D/RobotSphere.png"),
                Vector2_Int(),
                Vector2_Int(mstMinMapCenterPos.Left_SeparateRatioWidth(1.0f, mstMinMapDrawDistance.y/*タイポじゃない*/, true),
                    mstMinMapCenterPos.Left_SeparateRatioWidth(1.0f, mstMinMapDrawDistance.y, true))
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


#ifdef _DEBUG

    IMGUI_FLOAT_DATA imguiFloatData;
    imguiFloatData.AddVariable(&MIN_MAP_LEFT_UP_POS.x);
    imguiFloatData.AddVariable(&MIN_MAP_LEFT_UP_POS.y);
    imguiFloatData.AddVariable(&mstMinMapSize.x);
    imguiFloatData.AddVariable(&mstMinMapSize.y);
    imguiFloatData.SetLabel("MinMapSize_");
    imguiFloatData.SetImguiType(IMGUI_TYPE::DRAG4);
    imguiFloatData.SetMin(-1000000.0f);
    imguiFloatData.SetMax(1000000.0f);
    imguiFloatData.SetStep(0.1f);
    imguiFloatData.SetSpeed(0.01f);
    imguiFloatData.SetStepFast(0.1f);

    Master::mpImguiManager->SetFloatImgui(imguiFloatData);

    imguiFloatData.ReSetVariable();
    imguiFloatData.AddVariable(&testDrawPos.x);
    imguiFloatData.AddVariable(&testDrawPos.y);
    imguiFloatData.AddVariable(&testDrawPos.z);
    imguiFloatData.AddVariable(&testDrawPos.w);
    imguiFloatData.SetLabel("MINMAP_TEST_SIZE");
    imguiFloatData.SetSpeed(0.001f);
    imguiFloatData.SetSpeed(10.0f);
    Master::mpImguiManager->SetFloatImgui(imguiFloatData);


    IMGUI_INT_DATA imguiIntData;
    imguiIntData.SetImguiType(IMGUI_TYPE::DRAG4);
    imguiIntData.SetFormat("%d");
    imguiIntData.SetMin(-5000);
    imguiIntData.SetMax(5000);
    imguiIntData.SetStep(10);
    imguiIntData.SetSpeed(5.0f);
    imguiIntData.SetStepFast(5.0f);
    for (int i = 0; i < MIN_MAP_DRAW_GRAPH_TYPE::MAX; i++)
    {
        imguiIntData.ReSetVariable();
        imguiIntData.AddVariable(&mstMinMapDrawGraphData[i].pos.x);
        imguiIntData.AddVariable(&mstMinMapDrawGraphData[i].pos.y);
        imguiIntData.AddVariable(&mstMinMapDrawGraphData[i].size.x);
        imguiIntData.AddVariable(&mstMinMapDrawGraphData[i].size.y);
        imguiIntData.SetLabel("MIN_MAP_DATA_" + std::to_string(i));

        Master::mpImguiManager->SetIntImgui(imguiIntData);
    }

    Master::mpImguiManager->SetIntImgui(IMGUI_INT_DATA::GetImguiData(
                                                                     { &mstMinMapDrawGraphData[0].pos.x, &mstMinMapDrawGraphData[0].pos.y, &mstMinMapDrawGraphData[0].size.x, &mstMinMapDrawGraphData[0].size.y },
                                                                     1.0f,
                                                                     1.0f,
                                                                     1.0f,
                                                                     0,
                                                                     1000,
                                                                     "NONE_",
                                                                     "%d",
                                                                     0,
                                                                     IMGUI_TYPE::SLIDER4
                                                                    )
                                        );

#endif

    SetMinMapDrawLength(10000.0f);
}

// 終了
void MapManager::Finalize()
{
    // マスクデータを削除します
    mstMaskData.maskGraphPixelData.clear();
    free(mstMaskData.maskData);

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

    // マップ背景削除
    Master::mpResourceManager->ReduceModelHandle(mnMapBackHandle);
    Master::mpResourceManager->ReduceMovie(mnMapBackResourceHandle);
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
    // 動画ループ再生
    CharacterBase* backGroundDrawPlayer = Master::mpGameManager->GetTargetManager()->GetTarget(TARGET_TYPE::PLAYER).target;
    if ((backGroundDrawPlayer != nullptr) && !Master::mpStopManager->GetStopFlag(STOP_FLAG_TYPE::BACK_GROUND))
    {
        SetUseLighting(FALSE);
        MV1SetPosition(mnMapBackHandle, backGroundDrawPlayer->GetPos());
        Master::mpResourceManager->MovieLoop(mnMapBackResourceHandle);
        MV1SetTextureGraphHandle(mnMapBackHandle, 0, mnMapBackResourceHandle, FALSE);
        Master::mpResourceManager->DrawModelHandle(mnMapBackHandle);
        SetUseLighting(TRUE);
    }

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

// ミニマップサイス変更(0.0f～1.0f)
void MapManager::SetMinMapSize_And_CreateHandle(Vector2 minMapSize)
{
    mstMinMapSize = mstDisplaySize->LeftDown_SeparateRatio(MIN_MAP_LEFT_UP_POS, minMapSize, true);
    CreateMinMapScreenHandle(true);
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

    mstMinMapDrawDistance.y = testDrawPos.z - ((mstMinMapDrawDistance.x / MIN_MAP_DRAW_MAX_DISTANCE) * /*0.9f*/testDrawPos.y);

    Vector2_Int setCharacterSize = Vector2_Int(mstMinMapCenterPos.Left_RatioWidth(mstMinMapDrawDistance.y/*タイポじゃない*/),
                                               mstMinMapCenterPos.Up_RatioHeight(mstMinMapDrawDistance.y));

    mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::MIN_MAP_OUTSIDE_CHARACTER].size =   setCharacterSize;// ここ変更ミニマップの描画サイズ変えた時のみでいいと思う
    mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::MIN_MAP_WITHIN_CHARACTER].size =    setCharacterSize;
    mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::PLAYER].size =  setCharacterSize;
    mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::PLAYER].pos =   Vector2_Int(static_cast<int>(mstMinMapCenterPos.x), static_cast<int>(mstMinMapCenterPos.y));

    return true;
}

// ミニマップ描画
void MapManager::DrawMinMap()
{
    MV1SetScale(mnMapBackHandle, VScale(UtilCalc::VOne, testSize));

    SetMinMapDrawLength(testDrawPos.x);
    // 必要ならハンドル作成
    CreateMinMapScreenHandle();

    // 描画物取得
    ALL_MIN_MAP_DRAW_DATA allMinMapDrawData = GetMinMapDrawPos();

    // 描画
    {
        // 描画先を変更
        SetDrawScreen(mnDrawMinMapScreenHandle);
        ClearDrawScreen();

        // マスク画面を作成します
        CreateMaskScreen() ;
        // HACK: デバック用にコメントアウトしてる
        DrawMaskToDirectData(0, 0, mstMaskData.maskSize.x, mstMaskData.maskSize.y, mstMaskData.maskData, DX_MASKTRANS_NONE);
        /*
#define TEST_MODE 3
#if TEST_MODE == 0
        for (int y = (128 * testDrawPos.x); y < (128 * testDrawPos.z); y++)
        {
            for (int x = (128 * testDrawPos.y); x < (96 * testDrawPos.w); x++)
            {
                if (mstMaskData.maskData[y][x] == 0)
#elif TEST_MODE == 1
        for (int y = (mstMaskData.maskGraphPixelData.size() * testDrawPos.x); y < (mstMaskData.maskGraphPixelData.size() * testDrawPos.z); y++)
        {
            if ((0 > y) || (y >= mstMaskData.maskGraphPixelData.size()))
            {
                continue;
            }
            for (int x = (mstMaskData.maskGraphPixelData[y].size() * testDrawPos.y); x < (mstMaskData.maskGraphPixelData[y].size() * testDrawPos.w); x++)
            {
                if ((0 > x) || (x >= mstMaskData.maskGraphPixelData[y].size()))
                {
                    continue;
                }
                if (mstMaskData.maskGraphPixelData[y][x] == 0)
//#elif TEST_MODE == 2
        // for (int y = (bitFlag.size() * testDrawPos.x); y < (bitFlag.size() * testDrawPos.z); y++)
        // {
        //     if ((0 > y) || (y >= bitFlag.size()))
        //     {
        //         continue;
        //     }
        //     for (int x = (bitFlag[y].size() * testDrawPos.y); x < (bitFlag[y].size() * testDrawPos.w); x++)
        //     {
        //         if ((0 > x) || (x >= bitFlag[y].size()))
        //         {
        //             continue;
        //         }
        //         if (bitFlag[y][x])
#elif TEST_MODE == 3
        for (int y = (96 * testDrawPos.x); y < (96 * testDrawPos.z); y++)
        {
            if ((0 > y) || (y >= 96))
            {
                continue;
            }
            for (int x = (128 * testDrawPos.y); x < (128 * testDrawPos.w); x++)
            {
                if ((0 > x) || (x >= 128))
                {
                    continue;
                }
                if (mstMaskData.maskData[y][x] == 0)
#endif
                {
                    printfDx("■");
                }
                else
                {
                    printfDx("□");
                }            
            }
            printfDx("\n");
        }
        printfDx("\n");*/

        // HACK: デバック用にコメントアウトしてる
        // ミニマップ背景
        Master::mpResourceManager->DrawData_Graph(mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::BACK_GROUND]);
    
        // ミニマップ内キャラクター描画
        for (int i = 0; i < allMinMapDrawData.minMapWithinRangePos.size(); i++)
        {
            mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::MIN_MAP_WITHIN_CHARACTER].pos = mstMinMapSize.LeftUp_Ratio(allMinMapDrawData.minMapWithinRangePos[i].vectorData) - (mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::MIN_MAP_WITHIN_CHARACTER].size * 0.5f);
            Master::mpResourceManager->DrawData_Graph(mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::MIN_MAP_WITHIN_CHARACTER]);
        }

        // プレイヤー描画
        Master::mpResourceManager->DrawData_Graph(mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::PLAYER]);
        
        // マスク画面を削除します
        DeleteMaskScreen() ;

        
        // HACK: デバック用にコメントアウトしてる
        // ミニマップ枠
        Master::mpResourceManager->DrawData_Graph(mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::FRAME]);


        // ミニマップ外キャラクター描画
        for (int i = 0; i < allMinMapDrawData.minMapOutsideRangeDir.size(); i++)
        {
            mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::MIN_MAP_OUTSIDE_CHARACTER].pos = mstMinMapSize.LeftUp_Ratio(allMinMapDrawData.minMapOutsideRangeDir[i].vectorData) - (mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::MIN_MAP_OUTSIDE_CHARACTER].size * 0.5f);
            Master::mpResourceManager->DrawData_Graph(mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::MIN_MAP_OUTSIDE_CHARACTER]);
        }

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


    mnDrawMinMapScreenHandle = MakeScreen(mstMinMapSize.IntX(), mstMinMapSize.IntY(), TRUE);

    mstMinMapCenterPos = mstMinMapSize.LeftUp_FloatRatio(0.5f);

    // TODO: 描画情報も変更
    Vector2_Int setUISize = mstMinMapSize.GetVecInt();
    mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::BACK_GROUND].size = setUISize;
    mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::FRAME].size =       setUISize;

    Vector2_Int setCharacterSize = Vector2_Int(mstMinMapCenterPos.Left_RatioWidth(mstMinMapDrawDistance.y/*タイポじゃない*/),
                                               mstMinMapCenterPos.Up_RatioHeight(mstMinMapDrawDistance.y));

    mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::MIN_MAP_WITHIN_CHARACTER].size =    setCharacterSize;
    mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::MIN_MAP_WITHIN_CHARACTER].size =    setCharacterSize;
    mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::PLAYER].size =  setCharacterSize;
    mstMinMapDrawGraphData[MIN_MAP_DRAW_GRAPH_TYPE::PLAYER].pos =   Vector2_Int(static_cast<int>(mstMinMapCenterPos.x - (static_cast<float>(setCharacterSize.x) * 0.5f)), static_cast<int>(mstMinMapCenterPos.y - (static_cast<float>(setCharacterSize.y) * 0.5f)));

    // マスク再設定
    ReSetMask(mstMinMapSize.IntX(), mstMinMapSize.IntY());
}

// ミニマップ表示ポジション取得
ALL_MIN_MAP_DRAW_DATA MapManager::GetMinMapDrawPos()
{
    ALL_MIN_MAP_DRAW_DATA allMinMapDrawData;

    CharacterBase* player = Master::mpGameManager->GetTargetManager()->GetTarget(TARGET_TYPE::PLAYER);
    std::vector<CharacterTargetData> enemys = Master::mpGameManager->GetTargetManager()->GetTargets(TARGET_TYPE::ENEMY);
    allMinMapDrawData.minMapOutsideRangeDir.reserve(enemys.size());
    allMinMapDrawData.minMapWithinRangePos.reserve(enemys.size());
    MIN_MAP_DATA minMapData;

    // プレイヤーが見ている方向
    VECTOR playerAngle = VGet(0.0f, Master::mpGameManager->GetCameraManager()->GetCameraData().angle.y, 0.0f);
    
    for (int i = 0; i < enemys.size(); i++)
    {
        // エネミーへのベクトル
        VECTOR enemyVec = VSub(enemys[i].target->GetPos(), player->GetPos());

        // 範囲内
        if (UtilCalc::SphereCollision(player->GetPos(), mstMinMapDrawDistance.x * 0.5f, enemys[i].target->GetPos(), 0.0f))
        {            
            minMapData.vectorData.x = enemyVec.x / mstMinMapDrawDistance.x;
            minMapData.vectorData.y = enemyVec.z / mstMinMapDrawDistance.x;

            minMapData.vectorData = UtilChange::ChangeVector_XZ(
                                                                VAdd(
                                                                    UtilCalc::VSphericalMovePos(minMapData.vectorData.x, VAdd(UtilCalc::VRadChange(playerAngle), VGet(0.0f, UtilCalc::Pi * 0.5f ,0.0f))),
                                                                    UtilCalc::VSphericalMovePos(minMapData.vectorData.y, UtilCalc::VRadChange(playerAngle))    
                                                                    )
                                                                );
            // 座標修正
            minMapData.vectorData.x += 0.5f;
            minMapData.vectorData.y += 0.5f;

            allMinMapDrawData.minMapWithinRangePos.push_back(minMapData);
        }
        // 範囲外
        else
        {
            // プレイヤーが向いている方向に対してエネミーがどれくらいずれたアングルにいるか
            VECTOR enemyAngleFromPlayerForward = UtilCalc::VNotExceedAngle(VAdd(UtilCalc::VVecToAngle(enemyVec), UtilCalc::VRadChange(playerAngle)));

            minMapData.vectorData = UtilChange::ChangeVector_XZ(
                                                                UtilCalc::VSphericalMovePos(0.5f, enemyAngleFromPlayerForward)
                                                                );

            // 座標修正
            minMapData.vectorData.x += 0.5f;
            minMapData.vectorData.y += 0.5f;

            allMinMapDrawData.minMapOutsideRangeDir.push_back(minMapData);
        }
        

    }

    return allMinMapDrawData;
}

// マスクリセット
void MapManager::ReSetMask(int width, int height)
{
    // 例外確認
    if ((width == 0) || (height == 0))
    {
        return;
    }

    if (mstMaskData.maskData != nullptr)
    {
        free(mstMaskData.maskData);
    }
    mstMaskData.maskData = static_cast<unsigned char*>(malloc(sizeof(unsigned char) * width * height));
    mstMaskData.maskSize = Vector2_Int(width, height);

    // マスクを1ピクセルずつ記入
    Vector2 oneBitSize = Vector2(static_cast<float>(mstMaskData.maskGraphPixelData[0].size()) / width, static_cast<float>(mstMaskData.maskGraphPixelData.size()) / height);
    Vector2 nowBitPos = Vector2(0.0f, 0.0f);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (mstMaskData.maskData == nullptr)
            {
                return;
            }
            mstMaskData.maskData[(y * width) + x] = 0xff;
            if (mstMaskData.maskGraphPixelData[static_cast<int>(nowBitPos.y)][static_cast<int>(nowBitPos.x)] != 255)
            {
                mstMaskData.maskData[(y * width) + x] = 0;
            }
            nowBitPos.x += oneBitSize.x;
        }
         nowBitPos.y += oneBitSize.y;
        nowBitPos.x = 0.0f;
    }
}