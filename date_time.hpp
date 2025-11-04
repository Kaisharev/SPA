#pragma once
#include <string>
class Date {
    private:
        // Date
        int day;
        int month; 
        int year;
        
        long string_to_numeric () const {
            return (year*1000) + (month*100) + day;
        }
        
    public:

        Date (std::string date_string);
        std::string date_to_string ();

        //operatori poređenja

};

class Time {
    private:
        int hour;
        int minute;
        int second; 

};