#pragma once

// 時間処理種類
enum class TIME_PROCESSING_TYPE {
    ELAPSED,      // 実経過時間 (mstElapsedTime)
    GAME_ELAPSED, // ゲーム内経過時間 (mstGameElapsedTime)
    STOP,         // 停止時間 (mstGameStopTime)
    BACKGROUND    // バックグラウンド時間 (mstBackgroundTime)
};

// フレーム処理種類
enum class FRAME_PROCESSING_TYPE {
    TOTAL,        // 全フレーム (mstFrameCount)
    GAME          // ゲーム内有効フレーム (mstGameFrameCount)
};