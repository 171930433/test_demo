#include <iostream>
#include <chrono>
#include <unordered_map>
#include <functional>
#include <string>
#include <mutex>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/key.hpp>
#include <boost/multi_index/ordered_index.hpp>

// 定义一个结构来存储函数的统计信息
struct FunctionStats
{
    int call_count_ = 0;               // 调用次数
    double total_elapsed_time_ms_ = 0; // 总耗时
    std::string function_name_;        // 函数名称
    std::mutex mutex;                  // 互斥锁，用于保护统计信息的并发访问
};

double MeanTime_ms(FunctionStats *fs)
{
    return fs->total_elapsed_time_ms_ / fs->call_count_;
}

std::ostream &operator<<(std::ostream &os, FunctionStats const &fs)
{
    os << "Function " << fs.function_name_ << " was called "
       << fs.call_count_ << " times, with total elapsed time "
       << fs.total_elapsed_time_ms_ << " milliseconds, with mean "
       << (fs.total_elapsed_time_ms_ / fs.call_count_) << " milliseconds";
    return os;
}

namespace inner
{
    struct FuncName
    {
    };
    struct CallConut
    {
    };
    struct TotalTime
    {
    };
    struct MeanTime
    {
    };
}

// 使用 unordered_map 来映射函数指针到统计信息
std::unordered_map<void *, FunctionStats> function_statistics;

using namespace boost::multi_index;

using FunctionCallStatistics = multi_index_container<
    FunctionStats *,
    indexed_by<
        ordered_unique<tag<inner::FuncName>, key<&FunctionStats::function_name_>>,
        ordered_non_unique<tag<inner::CallConut>, key<&FunctionStats::call_count_>>,
        ordered_non_unique<tag<inner::MeanTime>, key<MeanTime_ms>>,
        ordered_non_unique<tag<inner::TotalTime>, key<&FunctionStats::total_elapsed_time_ms_>>>>;

FunctionCallStatistics function_statistics2;

// 更新函数统计信息的辅助函数
template <typename Func>
void update_function_stats(Func &&func, double duration, const std::string &function_name)
{
    auto &stats = function_statistics[reinterpret_cast<void *>(std::addressof(func))];
    std::lock_guard<std::mutex> lock(stats.mutex); // 使用互斥锁保护统计信息的并发访问
    stats.call_count_++;
    stats.total_elapsed_time_ms_ += duration;
    stats.function_name_ = function_name;
}

#define MEASURE_TIME(func, ...) TimerRun(func, #func, ##__VA_ARGS__)

// 带耗时测量的函数调用
template <typename Func, typename... Args>
auto TimerRun(Func &&func, const std::string &function_name, Args &&...args)
{
    auto start = std::chrono::steady_clock::now();

    if constexpr (std::is_void_v<std::invoke_result_t<Func, Args...>>)
    {
        std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration<double, std::milli>(end - start).count();
        update_function_stats(func, duration, function_name);
        return duration;
    }
    else
    {
        auto result = std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);
        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration<double, std::milli>(end - start).count();
        update_function_stats(func, duration, function_name);

        return std::make_pair(result, duration);
    }
}

// 示例函数
void example_function()
{
    // 模拟一个耗时操作
    for (int i = 0; i < 1000000; ++i)
    {
        int result = i * i;
    }
}

void example1(int arg1)
{
    // std::cout << __PRETTY_FUNCTION__ << " called\n";
    for (int i = 0; i < 1000000; ++i)
    {
        int result = arg1 * arg1;
    }
}

struct ADEMO
{
    void example2(int arg1)
    {
        // std::cout << __PRETTY_FUNCTION__ << " called\n";
        for (int i = 0; i < 1000000; ++i)
        {
            int result = arg1 * arg1;
        }
    }
};

int FunMeasurementTime()
{
    ADEMO a0;

    MEASURE_TIME(example_function);

    // 调用示例函数并计算其耗时
    for (int i = 0; i < 10; ++i)
    {
        MEASURE_TIME(example_function);
        MEASURE_TIME(example1, 100);
        MEASURE_TIME(&ADEMO::example2, &a0, 100);
    }
    MEASURE_TIME(&ADEMO::example2, &a0, 100);
    MEASURE_TIME(&ADEMO::example2, &a0, 100);

    // 打印每个函数的热力统计
    for (auto &pair : function_statistics)
    {
        std::cout << pair.second << std::endl;
        // copy to 2
        function_statistics2.insert(&pair.second);
    }
    std::cout << "FuncName ------------------------\n";
    //
    for (auto const &val : function_statistics2.get<inner::FuncName>())
    {
        std::cout << *val << std::endl;
    }
    std::cout << "CallConut ------------------------\n";
    //
    for (auto const &val : function_statistics2.get<inner::CallConut>())
    {
        std::cout << *val << std::endl;
    }

    std::cout << "TotalTime ------------------------\n";
    for (auto const &val : function_statistics2.get<inner::TotalTime>())
    {
        std::cout << *val << std::endl;
    }

    std::cout << "MeanTime ------------------------\n";
    for (auto const &val : function_statistics2.get<inner::MeanTime>())
    {
        std::cout << *val << std::endl;
    }
    return 0;
}
