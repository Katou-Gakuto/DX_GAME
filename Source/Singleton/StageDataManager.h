#pragma once

class StageDataManager
{
private:
	// ステージ開始期間フラグ
	bool mbStageStartPeriodFlag;

public:

	StageDataManager();
	~StageDataManager();

	void Init();

	void SetStageStartPeriodFlag(bool stageStartPeriodFlag) { mbStageStartPeriodFlag = stageStartPeriodFlag; }
	/// <summary>ステージ開始期間フラグ取得</summary>
	bool GetStageStartPeriodFlag() { return mbStageStartPeriodFlag; }
};