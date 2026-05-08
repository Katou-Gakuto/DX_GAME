#pragma once

// 時間情報
struct TIME_DATA
{
    TIME_DATA()
    : Time(0lu)
    , Count(0u)
    {}

    unsigned long Time;  // 時間
    unsigned int Count; // カウント

    TIME_DATA operator+(unsigned int time) const
    {
        TIME_DATA timeData = *this;

        unsigned long preTime = timeData.Time;
        timeData.Time += time;

        if (timeData.Time < preTime)
        {
            timeData.Count++;
        }

        return timeData;
    }

    TIME_DATA operator+(const TIME_DATA& time) const
    {
        TIME_DATA timeData = *this;
        timeData.Count += time.Count;

        unsigned long preTime = timeData.Time;
        timeData.Time += time.Time;

        if (timeData.Time < preTime)
        {
            timeData.Count++;
        }

        return timeData;
    }
};

// フレーム情報
struct FRAME_DATA
{
    FRAME_DATA()
    : Frame(0u)
    {}
    
    unsigned int Frame; // フレーム
};