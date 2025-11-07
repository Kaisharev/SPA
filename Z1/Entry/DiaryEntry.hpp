#pragma once
#include <string>
#include <fstream>
#include <filesystem>
#include <stdexcept>


#include "../DateTime/Date.hpp"
#include "../DateTime/Time.hpp"
class DiaryEntry {
    private:
        int id; 
        int priority;
        Date date;
        Time time;
        std::string short_description;
        std::string entry_text;
        std::string file_name;  
    public:
        DiaryEntry (int id, int priority, Date date, Time time, std::string short_description, std::string entry_text, std::string file_name) : id (id), priority (priority), date (date), time(time), short_description(short_description), entry_text(entry_text), file_name(file_name){};
        std::string GetStringifiedEntry();

        bool operator < (const DiaryEntry& other) const;
        bool operator > (const DiaryEntry& other) const;
        int CompareByDate (const DiaryEntry& other) const;
        int CompareTo(const DiaryEntry& other) const;

        std::string LoadEntryFromFile ();
};