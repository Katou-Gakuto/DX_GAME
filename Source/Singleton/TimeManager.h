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
    // 開始時間
    TIME_DATA mstStartTime;
    // 前回の時間
    TIME_DATA mstPreviousTime;
    // ゲーム一時停止時間
    TIME_DATA mstGameStopTime;
    // タイムスケール
    float mfTimeScale;
    // デルタタイム
    float mfDeltaTime;

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
    FRAME_DATA mstGameFrameCount;
    
    // シーン経過フレーム
    FRAME_DATA mstSceneElapsedFrame;

    // バックグラウンド時間
    TIME_DATA mstBackgroundTime;
    // 未処理のバックグラウンド時間
    TIME_DATA mstUnprocessedBackgroundTime;
    // バックグラウンド開始時間
    unsigned long mulBackgroundStartTime;

    // ゲームストップフラグ
    bool mbGameStopFlag;

    // 新しいシーンに移っている処理をしたフラグ
    bool mbNewSceneTimeFlag;

public:
    /*コンストラクタ*/
    TimeManager(int oneFrameTime = 17);
    /*デストラクタ*/
    ~TimeManager();

    /*初期化*/
    void Initilize();

    /*更新処理をやるかを返す*/
    bool GetNextUpdateFlag();

    /// <summary>バックグラウンドに出た時の処理</summary>
    void OnEnterBackground();
    /// <summary>バックグラウンドから戻った処理</summary>
    void OnReturnForeground();

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

    /// <summary>
    /// ゲーム停止フラグ取得
    /// </summary>
    /// <returns>停止しているなら「true」</returns>
    inline bool GetGameStopFlag() const { return mbGameStopFlag; }

    /// <summary>
    /// 1フレームの秒数取得(ミリ秒)
    /// </summary>
    /// <returns>1フレームの秒数(ミリ秒)</returns>
    inline unsigned int GetOneFrame() const { return munLowestOneFrameSeconds; }

    /// <summary>開始時間取得</summary>
    inline TIME_DATA GetStartTime() const { return mstStartTime; }

    /// <summary>経過時間取得</summary>
    inline TIME_DATA GetElapsedTime() const { return mstElapsedTime; }
    /// <summary>ゲーム経過時間取得</summary>
    inline TIME_DATA GetGameElapsedTime() const { return mstGameElapsedTime; }
    /// <summary>ゲーム停止時間取得</summary>
    inline TIME_DATA GetGameStopTime() const { return mstGameStopTime; }

    /// <summary>バックグラウンド時間取得</summary>
    inline TIME_DATA GetBackgroundTime() const { return mstBackgroundTime; }

    /// <summary>フレーム取得</summary>
    inline FRAME_DATA GetFrame() const { return mstFrameCount; }
    /// <summary>ゲームフレーム取得</summary>
    inline FRAME_DATA GetGameFrame() const { return mstGameFrameCount; }

    /// <summary>デルタタイム取得</summary>
    inline float GetDeltaTime() const { return mfDeltaTime; }


    /*--------*/
    /*【設定】*/
    /*--------*/

    /// <summary>
    /// ゲーム停止フラグ設定
    /// </summary>
    /// <param name="flag">停止するかどうか「true」で止まる</param>
    inline void SetGameStopFlag(bool flag) { mbGameStopFlag = flag; }

    /// <summary>
    /// 1フレームの秒数設定(ミリ秒)
    /// </summary>
    /// <param name="time">1フレームの秒数(ミリ秒)</param>
    inline void SetOneFrame(int time) { munLowestOneFrameSeconds = time; }

    /// <summary>
    /// シーン変更中に経ったゲーム時間を一定化するフラグを設定
    /// </summary>
    /// <param name="flag">新しいシーン移動中かどうか</param>
    inline void SetNewSceneTimeFlag(bool flag) { mbNewSceneTimeFlag = flag; }
};