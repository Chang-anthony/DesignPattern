#include <StandardLayout.hpp>
#include <Logger.hpp>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <iostream>
#include <sstream>
#include <Level.hpp>

StandardLayout::StandardLayout() : Layout()
{
}

std::string StandardLayout::format(std::string message)
{
    std::string CurrentTime = GetCurrentTime();
    std::string Level = levelToString[logger->GetLevel()];
    std::string Name = logger->GetName();
    std::string formattedMessage = CurrentTime + " |-" + Level + " " + Name + " - " + message + "\n";

    return formattedMessage;
}

std::string StandardLayout::GetCurrentTime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    std::tm local_tm;
    #ifdef _WIN32
        localtime_s(&local_tm, &now_time_t);
    #else
        localtime_r(&now_time_t, &local_tm);
    #endif

    std::ostringstream oss;
    oss << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S") << "." 
        << std::setfill('0') << std::setw(3) << now_ms.count();

    return oss.str();
}

StandardLayout::~StandardLayout()
{
}