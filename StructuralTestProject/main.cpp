#define TEST_MODE 1

#if TEST_MODE == 0
#include <iostream>
#include <chrono>
#include <cstdint>
#include <random>

#include "BitFlag.h"

constexpr uint64_t LOOP_COUNT = 100000000; // 1億回

int main()
{
    using Clock = std::chrono::high_resolution_clock;

    BIT_FLAG<uint32_t> bit;
    volatile uint64_t dummy = 0; // 最適化防止

    // 乱数生成（ビット位置用）
    std::mt19937 rng(12345);
    std::uniform_int_distribution<int> dist(0, 31);

    // ---------------- EnableFlag ----------------
    {
        auto start = Clock::now();
        for (uint64_t i = 0; i < LOOP_COUNT; ++i)
        {
            bit.EnableFlag(dist(rng));
        }
        auto end = Clock::now();
        std::cout << "EnableFlag: "
            << std::chrono::duration<double>(end - start).count()
            << " sec\n";
    }

    // ---------------- DisableFlag ----------------
    {
        auto start = Clock::now();
        for (uint64_t i = 0; i < LOOP_COUNT; ++i)
        {
            bit.DisableFlag(dist(rng));
        }
        auto end = Clock::now();
        std::cout << "DisableFlag: "
            << std::chrono::duration<double>(end - start).count()
            << " sec\n";
    }

    // ---------------- InvertFlag ----------------
    {
        auto start = Clock::now();
        for (uint64_t i = 0; i < LOOP_COUNT; ++i)
        {
            bit.InvertFlag(dist(rng));
        }
        auto end = Clock::now();
        std::cout << "InvertFlag: "
            << std::chrono::duration<double>(end - start).count()
            << " sec\n";
    }

    // ---------------- GetFlag ----------------
    {
        auto start = Clock::now();
        for (uint64_t i = 0; i < LOOP_COUNT; ++i)
        {
            dummy += bit.GetFlag(dist(rng));
        }
        auto end = Clock::now();
        std::cout << "GetFlag: "
            << std::chrono::duration<double>(end - start).count()
            << " sec\n";
    }

    std::cout << "Dummy (ignore): " << dummy << std::endl;
}
#elif TEST_MODE == 1

#include <iostream>
#include <bitset>
#include <chrono>
#include <vector>
#include <thread>
#include <random>
#include <atomic>

#include "BitFlag.h"

using Clock = std::chrono::high_resolution_clock;
constexpr uint64_t LOOP_COUNT = 100000000; // 1億
constexpr int BIT_SIZE = 32;
constexpr int THREAD_COUNT = 4;

// =====================================================
// 2. Check無し版
// =====================================================
template<typename T>
struct BIT_FLAG_NO_CHECK
{
    T flags = 0;

    inline void EnableFlag(int number) {
        flags |= ((T)1 << number);
    }

    inline bool GetFlag(int number) const {
        return (flags & ((T)1 << number)) != 0;
    }
};

// =====================================================
// 共通テスト関数（1スレッド）
// =====================================================
template<typename FUNC>
double RunSingle(FUNC func)
{
    auto start = Clock::now();
    func();
    auto end = Clock::now();
    return std::chrono::duration<double>(end - start).count();
}

// =====================================================
// マルチスレッド実行
// =====================================================
template<typename FUNC>
double RunMulti(FUNC func)
{
    auto start = Clock::now();

    std::vector<std::thread> threads;
    for (int i = 0; i < THREAD_COUNT; ++i)
        threads.emplace_back(func);

    for (auto& t : threads)
        t.join();

    auto end = Clock::now();
    return std::chrono::duration<double>(end - start).count();
}

int main()
{
    std::cout << "Loop Count: " << LOOP_COUNT << "\n\n";

    std::mt19937 rng(1234);
    std::uniform_int_distribution<int> dist(0, BIT_SIZE - 1);

    // 乱数事前生成（乱数コスト除外）
    std::vector<int> indices(LOOP_COUNT);
    for (uint64_t i = 0; i < LOOP_COUNT; ++i)
        indices[i] = dist(rng);

    // =====================================================
    // 1. BIT_FLAG (Checkあり)
    // =====================================================
    {
        BIT_FLAG<uint32_t> bit;
        volatile uint64_t dummy = 0;

        double t = RunSingle([&]() {
            for (uint64_t i = 0; i < LOOP_COUNT; ++i) {
                bit.EnableFlag(indices[i]);
                dummy += bit.GetFlag(indices[i]);
            }
            });

        std::cout << "[Single] BIT_FLAG(Check) : " << t << " sec\n";
    }

    // =====================================================
    // 2. BIT_FLAG_NO_CHECK
    // =====================================================
    {
        BIT_FLAG_NO_CHECK<uint32_t> bit;
        volatile uint64_t dummy = 0;

        double t = RunSingle([&]() {
            for (uint64_t i = 0; i < LOOP_COUNT; ++i) {
                bit.EnableFlag(indices[i]);
                dummy += bit.GetFlag(indices[i]);
            }
            });

        std::cout << "[Single] BIT_FLAG(NoCheck): " << t << " sec\n";
    }

    // =====================================================
    // 3. std::bitset
    // =====================================================
    {
        std::bitset<BIT_SIZE> bit;
        volatile uint64_t dummy = 0;

        double t = RunSingle([&]() {
            for (uint64_t i = 0; i < LOOP_COUNT; ++i) {
                bit.set(indices[i]);
                dummy += bit.test(indices[i]);
            }
            });

        std::cout << "[Single] std::bitset      : " << t << " sec\n";
    }

    // =====================================================
    // 4. 生ビット演算
    // =====================================================
    {
        uint32_t flags = 0;
        volatile uint64_t dummy = 0;

        double t = RunSingle([&]() {
            for (uint64_t i = 0; i < LOOP_COUNT; ++i) {
                flags |= (1u << indices[i]);
                dummy += ((flags & (1u << indices[i])) != 0);
            }
            });

        std::cout << "[Single] Raw Bit         : " << t << " sec\n";
    }

    std::cout << "\n---- Multi Thread (" << THREAD_COUNT << ") ----\n";

    // =====================================================
    // マルチスレッド比較（Rawのみ例示）
    // =====================================================
    {
        double t = RunMulti([&]() {
            uint32_t flags = 0;
            for (uint64_t i = 0; i < LOOP_COUNT / THREAD_COUNT; ++i) {
                flags |= (1u << (i % BIT_SIZE));
            }
            });

        std::cout << "[Multi] Raw Bit         : " << t << " sec\n";
    }

    return 0;
}

#elif TEST_MODE == 2


#endif