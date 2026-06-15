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

            // •`‰æ
            DrawData_Draw(&drawData);
            // if (!drawData->drawFlag)
            // {
            //     continue;
            // }

            // switch (drawData->drawManagerDrawType)
            // {
            // case DRAW_MANAGER_DRAW_TYPE::GRAPH:
            //     SetDrawBlendMode(drawData->drawConfigData.blendMode, drawData->drawConfigData.blendParameter);

            //     Master::mpResourceManager->DrawData_Graph(drawData->drawGraphData);

            //     SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
            //     break;
            // }
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
            if (mstDrawData[orderIt][dataIt].drawID == changeDataID)
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
DRAW_DATA* DrawManager::AddDrawData(DRAW_DATA *drawData, int orderNumber)
{
    if ((orderNumber < 0) ||
        (DRAW_ORDER_MAX <= orderNumber))
    {
        orderNumber = DRAW_ORDER_CENTER;
    }

    // •`‰æî•ñ’Ç‰Áˆ—
    drawData->drawID = mnDrawDataID;
    mnDrawDataID += 1;
    mstDrawData[orderNumber].push_back(*drawData);

    return &mstDrawData[orderNumber][mstDrawData[orderNumber].size() - 1];
}

// •`‰æî•ñIDw’èíœ
void DrawManager::DeleteDrawData_ID(int id)
{
    // •`‰æî•ñíœ
    for (auto& oneOrderData : mstDrawData)
    {
        for (auto it = oneOrderData.begin(); it != oneOrderData.end(); )
        {
            if (it->drawID == id)
            {
                switch (it->drawManagerDrawType)
                {
                case DRAW_MANAGER_DRAW_TYPE::GRAPH:
                    Master::mpResourceManager->ReduceGraphHandle(it->drawGraphData.handle);
                    break;
                }

                it = oneOrderData.erase(it);
                return;
            }
            else
            {
                ++it;
            }
        }
    }
}

// ‘S•`‰æî•ñíœ
void DrawManager::DeleteDrawData()
{
    // •`‰æî•ñíœ
    for (int orderIt = 0; orderIt < DRAW_ORDER_MAX; ++orderIt) {
        for (auto drawData : mstDrawData[orderIt])
        {
            switch (drawData.drawManagerDrawType)
            {
            case DRAW_MANAGER_DRAW_TYPE::GRAPH:
                Master::mpResourceManager->ReduceGraphHandle(drawData.drawGraphData.handle);
                break;
            }
        }

        mstDrawData[orderIt].clear();
    }

    mnDrawDataID = 0;
}


// •`‰æî•ñ‚ğ•`‰æ
void DrawManager::DrawData_Draw(DRAW_DATA *drawData, bool absoluteDrawFlag)
{
    if (!drawData->drawFlag && !absoluteDrawFlag)
    {
        return;
    }

    switch (drawData->drawManagerDrawType)
    {
    case DRAW_MANAGER_DRAW_TYPE::GRAPH:
        SetDrawBlendMode(drawData->drawConfigData.blendMode, drawData->drawConfigData.blendParameter);

        Master::mpResourceManager->DrawData_Graph(drawData->drawGraphData);

        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
        break;
    }
}

// •`‰æî•ñæ“¾
DRAW_DATA* DrawManager::GetDrawData(int drawId)
{
    for (int orderIt = 0; orderIt < DRAW_ORDER_MAX; ++orderIt) {
        for (int drawDataIndex = 0; drawDataIndex < mstDrawData[orderIt].size(); drawDataIndex++)
        {
            if (mstDrawData[orderIt][drawDataIndex].drawID == drawId)
            {
                return &mstDrawData[orderIt][drawDataIndex];
            }
        }
    }

    return nullptr;
}