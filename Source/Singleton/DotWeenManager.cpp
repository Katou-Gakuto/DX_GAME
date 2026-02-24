#include "DotWeenEnum.h"
#include "DotWeenData.h"

#include "DotWeenManager.h"

// コンストラクタ
DotWeenManager::DotWeenManager()
: mnIdMax(0)
{
    mstDotWeenDatas.clear();
}

// デストラクタ
DotWeenManager::~DotWeenManager()
{
}

// 初期化
void DotWeenManager::Initilize()
{
}

// 終了
void DotWeenManager::Finailize()
{
    mstDotWeenDatas.clear();
}

// 更新
void DotWeenManager::Update()
{
    // DotWeen情報の更新処理
    for (int i = 0; i < mstDotWeenDatas.size(); ++i)
    {
        DotWeenProcess(mstDotWeenDatas[i]);
    }
}

// DotWenn情報設定
int DotWeenManager::SetDotWeen(DOT_WEEN_DATA dotWeenData)
{
    dotWeenData.Id = mnIdMax;
    mnIdMax += 1;
    if (mnIdMax > DOT_WEEN_ID_MAX)
    {
        mnIdMax = 0;
    }

    mstDotWeenDatas.push_back(dotWeenData);

    return dotWeenData.Id;
}

// DotWeen情報削除
void DotWeenManager::DeleteDotWeenData(int id)
{
    // IDに対応するDotWeen情報を削除
    for (int i = 0; i < mstDotWeenDatas.size(); ++i)
    {
        if (mstDotWeenDatas[i].Id == id)
        {
            mstDotWeenDatas.erase(mstDotWeenDatas.begin() + i);
            return;
        }
    }
}

// DotWeen処理
void DotWeenManager::DotWeenProcess(DOT_WEEN_DATA dotWeenData)
{
    // ステートで処理
}