#include "date.hpp"
#include <chrono>
#include <regex>
#include <stdexcept>

Date::Date()
{
    *this = Date::Today();
}
bool Date::IsValidDate(int d, int m, int y)
{
    auto day = std::chrono::day(static_cast<unsigned>(d));
    auto month = std::chrono::month(static_cast<unsigned>(m));
    auto year = std::chrono::year(static_cast<unsigned>(y));

    return std::chrono::year_month_day{year, month, day}.ok();
}

Date Date::ParseDate(const std::string &date_string)
{
    std::regex date_regex("^(\\d{1,2})[.\\/-](\\d{1,2})[.\\/-](\\d{4})$");
    std::smatch regex_result;

    if (!std::regex_match(date_string, regex_result, date_regex))
    {
        throw std::invalid_argument("Uneseni datum nije u ispravnom formatu!");
    }

    if (!IsValidDate(
            std::stoi(regex_result[1]),
            std::stoi(regex_result[2]),
            std::stoi(regex_result[3])))
        throw std::invalid_argument("Uneseni datum nije validan");

    return Date(
        std::stoi(regex_result[1]),
        std::stoi(regex_result[2]),
        std::stoi(regex_result[3]));
}

Date Date::Today()
{
    const auto now = std::chrono::system_clock::now();

    const std::chrono::year_month_day today{std::chrono::floor<std::chrono::days>(now)};

    int day = static_cast<unsigned>(today.day());
    int month = static_cast<unsigned>(today.month());
    int year = static_cast<int>(today.year());

    return Date(day, month, year);
}
