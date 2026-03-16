#include <vector>

#include "DrawData.h"
#include "ResourceData.h"

#include "Master.h"

#include "DrawManager.h"
#include "ResourceManager.h"

/*--------*/
/*y‹¤’Êz*/
/*--------*/

// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
DrawManager::DrawManager()
: mnDrawDataID(0)
{
}

// ƒfƒXƒgƒ‰ƒNƒ^
DrawManager::~DrawManager()
{
}

// ‰Šú‰»
void DrawManager::Initilize()
{
    // •`‰æî•ñ‚Ì‰Šú‰»
    for (int orderIt = 0; orderIt < DRAW_ORDER_MAX; ++orderIt) {
        mstDrawData[orderIt].clear();
    }
    mnDrawDataID = 0;
}

// I—¹
void DrawManager::Finalize()
{
    // •`‰æî•ñíœ
    DeleteDrawData();
}

// •`‰æ
void DrawManager::Draw()
{
    for (int orderIt = 0; orderIt < DRAW_ORDER_MAX; orderIt++)
    {
        for (auto drawData : mstDrawData[orderIt])
        {
            if (!drawData->drawFlag)
            {
                continue;
            }

            switch (drawData->drawManagerDrawType)
            {
            case DRAW_MANAGER_DRAW_TYPE::GRAPH:
                SetDrawBlendMode(drawData->drawConfigData.blendMode, drawData->drawConfigData.blendParameter);

                // INPROGRESS: ì‹Æ’†‚È‚º‚©•`‰æ‚·‚é
                Master::mpResourceManager->DrawData_Graph(drawData->drawGraphData);

                SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
                break;
            }
        }
    }
}

// •`‰æ
void DrawManager::Draw(DRAW_GRAPH_DATA drawGraphData, DRAW_CONFIG_DATA drawConfigData)
{
}

// •`‰æ‡‚ğ•ÏX‚·‚é
bool DrawManager::ChangeDrawOrder(int changeDataID, int orderNumber)
{
    if ((orderNumber < 0) || (DRAW_ORDER_MAX <= orderNumber))
    {
        return true;    // ¸”sƒtƒ‰ƒO
    }

    for (int orderIt = 0; orderIt < DRAW_ORDER_MAX; orderIt++)
    {
        for (int dataIt = 0; dataIt < mstDrawData[orderIt].size(); dataIt++)
        {
            if (mstDrawData[orderIt][dataIt]->drawID == changeDataID)
            {
                mstDrawData[orderNumber].push_back(mstDrawData[orderIt][dataIt]);
                mstDrawData[orderIt].erase(mstDrawData[orderIt].begin() + dataIt);
                return false;   // ¸”sƒtƒ‰ƒO
            }
        }
    }

    return true;    // ¸”sƒtƒ‰ƒO
}

// •`‰æî•ñ’Ç‰Á
int DrawManager::AddDrawData(DRAW_DATA *drawData, int orderNumber)
{
    // •`‰æî•ñ’Ç‰Áˆ—
    drawData->drawID = mnDrawDataID;
    mnDrawDataID += 1;
    mstDrawData[orderNumber].push_back(drawData);

    return mnDrawDataID - 1;
}

// ‘S•`‰æî•ñíœ
void DrawManager::DeleteDrawData()
{
    // •`‰æî•ñíœ
    for (int orderIt = 0; orderIt < DRAW_ORDER_MAX; ++orderIt) {
        for (auto drawData : mstDrawData[orderIt])
        {
            switch (drawData->drawManagerDrawType)
            {
            case DRAW_MANAGER_DRAW_TYPE::GRAPH:
                Master::mpResourceManager->ReduceGraphHandle(drawData->drawGraphData.handle);
                break;
            }
        }

        mstDrawData[orderIt].clear();
    }
}