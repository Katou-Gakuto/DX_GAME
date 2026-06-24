#include <string>

#include "DxLib.h"

#include "Master.h"

#include "DataManager.h"
#include "ModelMap.h"
#include "ResourceManager.h"


ModelMap::ModelMap()
: mnGroundModelGraphHandle(-1)
{
    mstTileModelDatas.clear();
}
ModelMap::~ModelMap()
{
}

// モデル初期化
void ModelMap::ModelInitilize()
{
    mnGroundModelGraphHandle = Master::mpResourceManager->GetGraphResource()->GetResourceHandle((ResourceManager::msResourceFile + "2D/Floor.png");
}

// モデル終了
void ModelMap::ModelFinalize()
{
}

// モデル描画
void ModelMap::ModelDraw()
{
    if (!mbDrawFlag)
    {
        return;
    }

    
    for (int z = 0; z < mstTileModelDatas.size(); z++)
    {
        for (int x = 0; x < mstTileModelDatas[z].size(); x++)
        {
            switch (mstTileModelDatas[z][x].tileModelType)
            {
                case TILE_MODEL_TYPE::HANDLE:
                    ModelDraw_Handle(mstTileModelDatas[z][x].modelHandle);
                break;

                case TILE_MODEL_TYPE::INDEXED:
                    ModelDraw_Indexed(mstTileModelDatas[z][x].modelVertex);
                break;
            }
        }
    }
}

// マップデータ読み込み
void ModelMap::LoadMapData(std::vector<std::vector<TileData>>& mapData, VECTOR mapMinPos, VECTOR tileHalfSize)
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
    // TODO: ハンドルしか制作してないし分ける情報も変えたほうが良いと思う
    for (int z = 0; z < mapData.size(); z++)
    {
        std::vector<TileModelData> setTileModelLine;
        setTileModelLine.clear();
        for (int x = 0; x < mapData[z].size(); x++)
        {
            TileModelData setTileModel = TileModelData();
            switch (mapData[z][x].tileType)
            {
                case TileType::Ground:
                    setTileModel.modelHandle = Master::mpResourceManager->GetModelHandle(Master::mpDataManager->GetMapResourceFileName(DataManager::MAP_RESOURCE_FILE_NUMBWER::GRTOUND));
                    setTileModel.tileModelType = TILE_MODEL_TYPE::HANDLE;

                    MV1SetTextureGraphHandle(setTileModel.modelHandle, 0, mnGroundModelGraphHandle, FALSE);
                    MV1SetWriteZBuffer(setTileModel.modelHandle, FALSE);
                    int materialNumber = MV1GetMaterialNum(setTileModel.modelHandle);
                    for (int i = 0; i < materialNumber; i++)
                    {
                        MV1SetMaterialDrawBlendMode(setTileModel.modelHandle, i, DX_BLENDMODE_ALPHA);
                        MV1SetMaterialDrawBlendParam(setTileModel.modelHandle, i, 128);
                    }
                    // HACK: 縦とりあえずいれてる
                    MV1SetPosition(setTileModel.modelHandle, VGet(mapMinPos.x + ((tileHalfSize.x + tileHalfSize.x) * x), mapMinPos.y + 50.0f, mapMinPos.z + ((tileHalfSize.z + tileHalfSize.z) * z)));
                    MV1SetScale(setTileModel.modelHandle, VGet(0.85f, 1.0f, 0.85f));
                break;
            }
            setTileModelLine.push_back(setTileModel);
        }
        mstTileModelDatas.push_back(setTileModelLine);
    }
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

// マップデータ解放
void ModelMap::ReleaseMapModel()
{
    for (int z = 0; z < mstTileModelDatas.size(); z++)
    {
        for (int x = 0; x < mstTileModelDatas[z].size(); x++)
        {
            switch (mstTileModelDatas[z][x].tileModelType)
            {
                case  TILE_MODEL_TYPE::HANDLE:
                    Master::mpResourceManager->ReduceModelHandle(mstTileModelDatas[z][x].modelHandle);
                    mstTileModelDatas[z][x].modelHandle = -1;
                break;
                
                case  TILE_MODEL_TYPE::INDEXED:
                    for (int i = 0; i < mstTileModelDatas[z][x].modelVertex.size(); i++)
                    {
                        if (mstTileModelDatas[z][x].modelVertex[i].textureType.GetFlag_BitShift(TEXTURE_TYPE::GRAPH))
                        {
                            Master::mpResourceManager->ReduceGraphHandle(mstTileModelDatas[z][x].modelVertex[i].textureHandle);
                            mstTileModelDatas[z][x].modelVertex[i].textureHandle = -1;
                        }
                        else if (mstTileModelDatas[z][x].modelVertex[i].textureType.GetFlag_BitShift(TEXTURE_TYPE::MOVIE))
                        {
                            Master::mpResourceManager->ReduceMovie(mstTileModelDatas[z][x].modelVertex[i].textureHandle);
                            mstTileModelDatas[z][x].modelVertex[i].textureHandle = -1;
                        }
                    }
                break;
            }
        }
    }
}