#pragma once
#include <windows.h>

// TODO: long long int 以上対応の構造体を作る
class TimeManager
{
private:

    // フレームカウント
    unsigned int munFrameCount;
    // スタートタイム
    unsigned int munStartTime;
    // 一つ前の時間
    unsigned int munPreviousTime;
    // ストップタイム
    unsigned int munStopTime;
    // 1フレームの秒数
    unsigned int munOneFrame;

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
    unsigned int GetOneFrame() const { return munOneFrame; }

    /// <summary>
    /// 1フレームの秒数設定(ミリ秒)
    /// </summary>
    /// <param name="time">1フレームの秒数(ミリ秒)</param>
    void SetOneFrame(int time) { munOneFrame = time; }

    /// <summary>
    /// シーン変更中に経ったゲーム時間を一定化するフラグを設定
    /// </summary>
    /// <param name="flag">新しいシーン移動中かどうか</param>
    void SetNewSceneTimeFlag(bool flag) { mbNewSceneTimeFlag = flag; }
};