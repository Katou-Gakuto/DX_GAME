#pragma once
#include <vector>

#include "DotWeenData.h"

class DotWeenManager
{
private:
    std::vector<DOT_WEEN_DATA> mstDotWeenDatas;

    int mnIdMax;

    static constexpr int DOT_WEEN_ID_MAX = 2'000'000'000;

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
    int SetDotWeen(DOT_WEEN_DATA dotWeenData);
    
    /// <summary>DotWeenî•ñíœ</summary>
    void DeleteDotWeenData(int id);

private:
    /*DotWeenˆ—*/
    void DotWeenProcess(DOT_WEEN_DATA dotWeenData);
};