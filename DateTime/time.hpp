#pragma once
#include <string>
class Time {
    private:
        int hour;
        int minute; 
        int second;
        
        static bool IsValdTime (int h, int m, int s);
        int ConcatenateTime ();
        Time();

    public: 
        static Time ParseTime(const std::string& TimeString);
        static Time CurrentTime();

        // Getteri

        int GetHour () const;
        int GetMinute () const;
        int GetSecond () const;
        std::string GetTimeAsString () const;

};