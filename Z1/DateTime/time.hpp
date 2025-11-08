#pragma once
#include <string>
class Time {
    private:
        int hour;
        int minute;
        int second;

        Time (int h, int m, int s) : hour (h), minute (m), second (s) {};
        static bool IsValidTime (int h, int m, int s);
        int ConcatenateTime ();

    public:
        Time ();
        static Time ParseTime (const std::string& time_string);
        static Time CurrentTime ();

        // Getteri
        int GetHour () const {
            return this->hour;
        }

        int GetMinute () const {
            return this->minute;
        }

        int GetSecond () const {
            return this->second;
        }

        std::string GetTimeAsString () const {
            return std::to_string (this->hour) + ":" + std::to_string (this->minute) + ":" + std::to_string (this->second);
        }

        bool operator== (const Time& other) const {
            return hour == other.hour && minute == other.minute && second == other.second;
        }

        bool operator!= (const Time& other) const {
            return !(*this == other);
        }
        bool operator<= (const Time& other) const {
            return *this < other || *this == other;
        }

        bool operator> (const Time& other) const {
            return !(*this <= other);
        }

        bool operator>= (const Time& other) const {
            return !(*this < other);
        }
        bool operator< (const Time& other) const;
};
