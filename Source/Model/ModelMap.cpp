#include "DxLib.h"

#include "Master.h"

#include "DataManager.h"
#include "ModelMap.h"
#include "ResourceManager.h"


ModelMap::ModelMap()
{
    mstTileModelDatas.clear();
}
ModelMap::~ModelMap()
{
}

// モデル初期化
void ModelMap::ModelInitilize()
{
}

// モデル終了
void ModelMap::ModelFinalize()
{
}

// モデル描画
void ModelMap::ModelDraw()
{
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
void ModelMap::LoadMapData(std::vector<std::vector<TileData>>& mapData)
{

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
                    MV1SetPosition(setTileModel.modelHandle, VGet(0.0f + (500.0f * x), 150.0f, 0.0f + (500.0f * z)));
                break;
            }
            setTileModelLine.push_back(setTileModel);
        }
        mstTileModelDatas.push_back(setTileModelLine);
    }
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
                break;
                
                case  TILE_MODEL_TYPE::INDEXED:
                    for (int i = 0; i < mstTileModelDatas[z][x].modelVertex.size(); i++)
                    {
                        if (mstTileModelDatas[z][x].modelVertex[i].textureType.GetFlag(TEXTURE_TYPE::GRAPH))
                        {
                            Master::mpResourceManager->ReduceGraphHandle(mstTileModelDatas[z][x].modelVertex[i].textureHandle);
                        }
                        else if (mstTileModelDatas[z][x].modelVertex[i].textureType.GetFlag(TEXTURE_TYPE::MOVIE))
                        {
                            Master::mpResourceManager->ReduceMovie(mstTileModelDatas[z][x].modelVertex[i].textureHandle);
                        }
                    }
                break;
            }
        }
    }
}