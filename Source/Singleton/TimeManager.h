#pragma once
#include <windows.h>

#ifdef _DEBUG
#include <map>
#endif

#include "TimeEnum.h"
#include "TimeData.h"

// TODO: long long int 以上対応の構造体を作る 判定を関数化して受け取らせない(loop対策)
class TimeManager
{
private:
    // 最低1フレームの秒数
    unsigned int munLowestOneFrameSeconds;
    // 次の処理秒数
    unsigned int munNextProcessingSeconds;
    // 開始時間
    TIME_DATA mstStartTime;
    // 前回の時間
    TIME_DATA mstPreviousTime;
    // 一時停止時間
    TIME_DATA mstStopTime;
    // タイムスケール
    float mfTimeScale;
    // デルタタイム
    TIME_DATA mstDeltaTime;

#ifdef _DEBUG
    // 過去のフレーム秒数保存用
    std::map<unsigned long, unsigned int> mmForPastFrameSecondsSave;
#endif

    // 経過時間
    TIME_DATA mstElapsedTime;
    // フレーム数
    FRAME_DATA mstFrameCount;
    
    // ゲーム経過時間
    TIME_DATA mstGameElapsedTime;
    // ゲームフレーム数
    FRAME_DATA mstGameFrameNumber;
    
    // シーン経過フレーム
    FRAME_DATA mstSceneElapsedFrame;

    // バックグラウンドタイム
    TIME_DATA mstBackgroundTime;

    // ストップフラグ
    bool mbStopFlag;

    // 新しいシーンに移っている処理をしたフラグ
    bool mbNewSceneTimeFlag;

    // 時間がリセットされたフラグ
    int mnTimeResetFlag;

public:
    /*コンストラクタ*/
    TimeManager(int oneFrameTime = 17);
    /*デストラクタ*/
    ~TimeManager();

    /*初期化*/
    void Initilize();

    /*更新処理をやるかを返す*/
    bool GetNextUpdateFlag();

    /*--------*/
    /*【比較】*/
    /*--------*/
    /// <summary>時間比較</summary>
    bool IsOverTime(TIME_DATA comparisonTime, TIME_PROCESSING_TYPE timeProcessingType);
    /// <summary>フレーム数比較</summary>
    bool IsOverFrame(FRAME_DATA comparisonFrame, FRAME_PROCESSING_TYPE frameProcessingType);

    /*--------*/
    /*【取得】*/
    /*--------*/

    /*--------*/
    /*【設定】*/
    /*--------*/


    /// <summary>
    /// フレーム数取得
    /// </summary>
    /// <returns>経過フレーム数</returns>
    unsigned int GetFrame() const { return munFrameCount; }

    /// <summary>
    /// ゲーム時間取得
    /// </summary>
    /// <returns>ゲームの経過時間</returns>
    unsigned int GetGameTime() const { return timeGetTime() - (munStartTime + (mbNewSceneTimeFlag ? (munStopTime + (timeGetTime() - munPreviousTime)) : munStopTime)); }
    // TODO: timeGetTime　1フレームに1回呼ぶだけにする
    /// <summary>
    /// スタートからの経過時間
    /// </summary>
    /// <returns>経過時間</returns>
    unsigned int GetTime() const { return timeGetTime() - munStartTime; }

    /// <summary>
    /// 一つ前の更新時間
    /// </summary>
    /// <returns>更新時間</returns>
    unsigned int GetPreviousTime() const { return munPreviousTime; }

    /// <summary>
    /// ゲーム停止フラグ取得
    /// </summary>
    /// <returns>停止しているなら「true」</returns>
    bool GetStopFlag() const { return mbStopFlag; }

    /// <summary>
    /// ゲーム停止フラグ設定
    /// </summary>
    /// <param name="flag">停止するかどうか「true」で止まる</param>
    void SetStopFlag(bool flag) { mbStopFlag = flag; }

    /// <summary>
    /// 1フレームの秒数取得(ミリ秒)
    /// </summary>
    /// <returns>1フレームの秒数(ミリ秒)</returns>
    unsigned int GetOneFrame() const { return munLowestOneFrameSeconds; }

    /// <summary>
    /// 1フレームの秒数設定(ミリ秒)
    /// </summary>
    /// <param name="time">1フレームの秒数(ミリ秒)</param>
    void SetOneFrame(int time) { munLowestOneFrameSeconds = time; }

    /// <summary>
    /// シーン変更中に経ったゲーム時間を一定化するフラグを設定
    /// </summary>
    /// <param name="flag">新しいシーン移動中かどうか</param>
    void SetNewSceneTimeFlag(bool flag) { mbNewSceneTimeFlag = flag; }
};