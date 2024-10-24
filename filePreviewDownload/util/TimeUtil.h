//
// Created by ZHOU on 24-10-25.
//

#ifndef TIMEUTIL_H
#define TIMEUTIL_H

#include <chrono>
#include<string>

inline std::string get_current_time() {
    // 获取当前时间点
    const auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);

    // 转换为本地时间
    std::tm local_time{};
#ifdef _WIN32
    localtime_s(&local_time, &now_time_t); // Windows
#else
    localtime_r(&now_time_t, &local_time); // Linux / Unix
#endif

    // 获取微秒
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % 1000000;

    // 格式化时间为字符串
    std::ostringstream oss;
    oss << std::put_time(&local_time, "%Y_%m_%d_%H_%M_%S") << "_" << std::setw(6) << std::setfill('0') << microseconds.
            count();

    return oss.str();
}

#endif //TIMEUTIL_H
