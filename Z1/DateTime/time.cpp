#include "Time.hpp"
#include <regex>
#include <stdexcept>
#include <chrono>

Time::Time()
{
    // Initialize to the current time
    *this = Time::CurrentTime();
}

bool Time::IsValidTime(int h, int m, int s)
{
    return (h >= 0 && h <= 23) &&
           (m >= 0 && m <= 59) &&
           (s >= 0 && s <= 59);
}

int Time::ConcatenateTime()
{
    return std::stoi(
        std::to_string(this->hour) +
        std::to_string(this->minute) +
        std::to_string(this->second));
}

Time Time::ParseTime(const std::string &time_string)
{
    std::regex time_regex("([0-9]{2}):([0-9]{2}):([0-9]{2})(\\.[0-9]{1,3})?");
    std::smatch regex_result;

    if (!std::regex_match(time_string, regex_result, time_regex))
    {
        throw std::invalid_argument("Uneseno vrijeme nije u ispravnom formatu (HH:MM:SS)");
    }
    if (!IsValidTime(
            std::stoi(regex_result[1]),
            std::stoi(regex_result[2]),
            std::stoi(regex_result[3])))
        throw std::invalid_argument("Uneseni datum nije validan");

    return Time(
        std::stoi(regex_result[1]),
        std::stoi(regex_result[2]),
        std::stoi(regex_result[3]));
}

Time Time::CurrentTime()
{
    const auto current_time = std::chrono::system_clock::now();
    const auto time_of_day = std::chrono::hh_mm_ss{std::chrono::floor<std::chrono::seconds>(current_time - std::chrono::floor<std::chrono::days>(current_time))};

    return Time(
        static_cast<int>(time_of_day.hours().count()),
        static_cast<int>(time_of_day.minutes().count()),
        static_cast<int>(time_of_day.seconds().count()));
}

bool Time::operator<(const Time &other) const
{
    if (hour != other.hour)
        return hour < other.hour;
    if (minute != other.minute)
        return minute < other.minute;
    return second < other.second;
}