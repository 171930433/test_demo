#include <iostream>
#include <chrono>
#include <unordered_map>
#include <functional>
#include <string>
#include <mutex>

// 定义一个结构来存储函数的统计信息
struct FunctionStats
{
    int call_count_ = 0;            // 调用次数
    double total_elapsed_time_ms_ = 0; // 总耗时
    std::string function_name_;     // 函数名称
    std::mutex mutex;              // 互斥锁，用于保护统计信息的并发访问
};

// 使用 unordered_map 来映射函数指针到统计信息
std::unordered_map<void *, FunctionStats> function_statistics;


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
    std::cout << __PRETTY_FUNCTION__ << " called\n";
    for (int i = 0; i < 1000000; ++i)
    {
        int result = arg1 * arg1;
    }
}

struct ADEMO
{
    void example2(int arg1)
    {
        std::cout << __PRETTY_FUNCTION__ << " called\n";
        for (int i = 0; i < 1000000; ++i)
        {
            int result = arg1 * arg1;
        }
    }
};

int FunMeasurementTime()
{
    ADEMO a0;

    // 调用示例函数并计算其耗时
    for (int i = 0; i < 10; ++i)
    {
        MEASURE_TIME(example_function);
        MEASURE_TIME(example1, 100);
        MEASURE_TIME(&ADEMO::example2, &a0, 100);
    }

    // 打印每个函数的热力统计
    for (const auto &pair : function_statistics)
    {
        std::cout << "Function " << pair.second.function_name_ << " was called "
                  << pair.second.call_count_ << " times, with total elapsed time "
                  << pair.second.total_elapsed_time_ms_ << " milliseconds" << std::endl;
    }

    return 0;
}
