#pragma once
#include <string>
class Date {
    private:
        // Date
        int day;
        int month; 
        int year;
        
        Date (int day, int month, int year) : day (day), month (month), year(year) {

        }

        static bool IsValidDate (int day, int month, int year);

        long StringToInteger () const {
            return (year*10000) + (month*100) + day;
        }
        
    public:
        Date ();
        static Date ParseDate (const std::string& date_string);
        static Date Today();
        // Geteri


        int GetDay () const {
            return this -> day;
        }
        
        
        int GetMonth () const {
            return this -> month;
        }
        
        int GetYear () const {
            return this -> year;
        }
        
        std::string GetDateAsString () const{
            return std::to_string(this -> day) + "." + 
                   std::to_string(this -> month) + "." + 
                   std::to_string(this -> year);
        }

        // Operatori poređenja
        bool operator == (const Date& other) const {
            return this -> StringToInteger () == other.StringToInteger();
        }

        bool operator < (const Date& other) const {
            return this -> StringToInteger () < other.StringToInteger();

        }

        bool operator > (const Date& other) const {
            return this -> StringToInteger () > other.StringToInteger();

        }
        
        bool operator <= (const Date& other) const {
            return this -> StringToInteger () <= other.StringToInteger();

        }

        bool operator >= (const Date& other) const {
            return this -> StringToInteger () >= other.StringToInteger();

        }
};

