#include <string>
#include <vector>

#include "Master.h"

#include "TelopManager.h"
#include "TimeManager.h"

TelopManager::TelopManager()
: mnPreTelopDrawTime(0)
{
    msTelopStrings.clear();
}

TelopManager::~TelopManager()
{
}

// 終了
void TelopManager::Finalize()
{
}

// 更新
void TelopManager::Update()
{
    if ((mnPreTelopDrawTime < Master::mpTimeManager->GetTime()) && (msTelopStrings.size() > 0))
    {
        DeleteTelop();
    }
}

// 描画
void TelopManager::Draw()
{
}

// テロップ追加
void TelopManager::AddTelop(std::string telop)
{
    msTelopStrings.push_back(telop);
    mnPreTelopDrawTime = Master::mpTimeManager->GetTime() + TELOP_TIME;
}

// テロップ削除
void TelopManager::DeleteTelop()
{
    msTelopStrings.clear();
}