#pragma once
#include <vector>

#include "DotWeenData.h"

class DotWeenManager
{
private:
    std::vector<DOT_WEEN_DATA> mstDotWeenDatas;

    int mnIdMax;

public:
    DotWeenManager();
    ~DotWeenManager();

    /// <summary>‰Šú‰»</summary>
    void Initilize();
    /// <summary>I—¹</summary>
    void Finailize();
    /// <summary>XV</summary>
	void Update();

    /// <summary>DotWennî•ñİ’è</summary>
    inline int SetDotWeen(DOT_WEEN_DATA dotWeenData) { mstDotWeenDatas.push_back(dotWeenData); }
    
    /// <summary>DotWeenî•ñíœ</summary>
    void DeleteDotWeenData(int id);

private:
    /*DotWeenˆ—*/
    void DotWeenProcess(DOT_WEEN_DATA dotWeenData);
};