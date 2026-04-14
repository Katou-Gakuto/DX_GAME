#pragma once
#include <vector>

#include "DrawData.h"
#include "ResourceData.h"

class DrawManager
{
public:
    // •`‰æ‡”Ô Å‘å
    static constexpr int DRAW_ORDER_MAX = 3;

    // •`‰æ‡”Ô ’†‰›
    static constexpr int DRAW_ORDER_CENTER = DRAW_ORDER_MAX / 2;

private:
    // •`‰æî•ñ
    std::vector<DRAW_DATA*> mstDrawData[DRAW_ORDER_MAX];

    // •`‰æÅ‘åID
    int mnDrawDataID;

public:
    DrawManager();
    ~DrawManager();

    /// <summary>‰Šú‰»</summary>
    void Initilize();
    /// <summary>I—¹</summary>
    void Finalize();

    /// <summary>•`‰æ</summary>
    void Draw();
    /// <summary>•`‰æ</summary>
    void Draw(DRAW_GRAPH_DATA drawGraphData, DRAW_CONFIG_DATA drawConfigData = DRAW_CONFIG_DATA());

    /// <summary>•`‰æ‡‚ğ•ÏX‚·‚é</summary>
    /// <param name="changeDataID">•ÏX‚·‚é•`‰æî•ñID</param>
    /// <param name="orderNumber">•`‰æ‡(0ˆÈãDRAW_ORDER_MAX–¢–)</param>
    /// <returns>¸”sƒtƒ‰ƒO</returns>
    bool ChangeDrawOrder(int changeDataID, int orderNumber = DRAW_ORDER_CENTER);

    /// <summary>•`‰æî•ñ’Ç‰Á¦vcector‚ÅÄŠm•Û‚·‚é‚Æ•Ï”‚Ì•Û‘¶êŠ‚ª‚¸‚ê‚é‚½‚ßƒoƒO‚é‚½‚ßupush_backv‚ªI‚í‚Á‚½Œã‚ª—‘z</summary>
    /// <param name="drawData">’Ç‰Á‚·‚é•`‰æî•ñ</param>
    /// <param name="orderNumber">•`‰æ‡(0ˆÈãDRAW_ORDER_MAX–¢–)</param>
    /// <returns>•`‰æî•ñID</returns>
    int AddDrawData(DRAW_DATA *drawData, int orderNumber = DRAW_ORDER_CENTER);

    /// <summary>‘S•`‰æî•ñíœ</summary>
    void DeleteDrawData();
};