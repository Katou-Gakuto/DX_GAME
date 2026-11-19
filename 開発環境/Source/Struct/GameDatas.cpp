#include "GameDatas.h"
#include "Status.h"


// レベルアップ処理
void PLAYER_DATA::LevelUpProcess(LevelData levelData, int addExp)
{
    int upLevelCount = 0;
    this->status.exp += addExp;

    while ((this->status.level < levelData.maxLevelNumber) && (levelData.levelUpExpNumber[this->status.level] <= this->status.exp))
    {
        upLevelCount++;
        this->status.level++;
        this->status.exp -= levelData.levelUpExpNumber[this->status.level];
    }

    if (0 < upLevelCount)
    {
        this->status = this->status + (levelData.upStatus * (levelData.upStatsMagnification * upLevelCount));
    }
}