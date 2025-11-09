#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>

#include "../DataStructures/LinkedList.hpp"
#include "../DataStructures/PriorityQueue.hpp"
#include "../DataStructures/Stack.hpp"
#include "../DateTime/Date.hpp"
#include "../DateTime/Time.hpp"
#include "../Entry/DiaryEntry.hpp"
#include "../Utils/utils.hpp"
class Diary {
    private:
        Diary ();

        Diary (const Diary&) = delete;
        Diary& operator= (const Diary&) = delete;

        LinkedList<DiaryEntry> all_entries;
        LinkedList<DiaryEntry> current_entries;
        Stack<DiaryEntry> undo_stack;

        std::string index_file;
        std::string entries_directory;
        int next_id;

        void LoadFromFile ();
        void SaveIndexFile ();
        void SaveEntryContent (const DiaryEntry& entry);
        std::string LoadEntryContent (const std::string& filename);

        DiaryEntry ParseIndexLine (const std::string& line);
        std::string EntryToIndexLine (const DiaryEntry& entry);
        bool ValidateEntry (int priority, std::string short_description, std::string entry_text) const;

    public:
        static Diary& GetInstance ();

        ~Diary ();

        void AddEntry (int priority, const Date& date, const Time& time, const std::string& short_description,
                       const std::string& entry_text);

        void DeleteLastEntry ();

        void UndoDelete ();

        void ShowTop5Priority ();

        void ShowAllDates ();

        void ShowEntriesForDate (const Date& date);

        void ShowEntriesByDateRange (const Date& from, const Date& to);

        int GetTotalEntries () const;

        void ClearAll ();
};