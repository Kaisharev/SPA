#pragma once
#include <string>
class Time {
    private:
        int hour;
        int minute; 
        int second;
        
        Time (int h, int m, int s) : hour (h), minute (m), second (s){};
        static bool IsValidTime (int h, int m, int s);
        int ConcatenateTime ();

    public: 
        static Time ParseTime(const std::string& time_string);
        static Time CurrentTime();

        // Getteri

        int GetHour () const;
        int GetMinute () const;
        int GetSecond () const;
        std::string GetTimeAsString () const;

};


