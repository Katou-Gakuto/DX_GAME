#include "ModelMap.h"


ModelMap::ModelMap()
{
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
    for (int z = 0; z < mstMapData->size(); z++)
    {
        for (int x = 0; x < mstMapData[z].size(); x++)
        {
            switch ((*mstMapData)[z][x].tileFlag.GetNumber(0ull, 0))
            {
                case 0:
                break;
            }
        }
    }
}