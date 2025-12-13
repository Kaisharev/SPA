#pragma once
#include <string>
class Date {
    private:
        int day;
        int month;
        int year;

        Date (int day, int month, int year) : day (day), month (month), year (year) {}

        static bool IsValidDate (int day, int month, int year);

        long StringToInteger () const {
            return (year * 10000) + (month * 100) + day;
        }

    public:
        Date ();
        static Date ParseDate (const std::string& date_string);
        static Date Today ();

        int GetDay () const {
            return day;
        }

        int GetMonth () const {
            return month;
        }

        int GetYear () const {
            return year;
        }

        std::string GetDateAsString () const {
            return std::to_string (day) + "." + std::to_string (month) + "." + std::to_string (year);
        }

        bool operator== (const Date& other) const {
            return StringToInteger () == other.StringToInteger ();
        }

        bool operator< (const Date& other) const {
            return StringToInteger () < other.StringToInteger ();
        }

        bool operator> (const Date& other) const {
            return StringToInteger () > other.StringToInteger ();
        }

        bool operator<= (const Date& other) const {
            return StringToInteger () <= other.StringToInteger ();
        }

        bool operator>= (const Date& other) const {
            return StringToInteger () >= other.StringToInteger ();
        }
};
