#include "Diary.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string_view>

Diary& Diary::GetInstance () {
    static Diary instance;
    return instance;
}

Diary::Diary () : index_file ("dnevnik.txt"), entries_directory ("unosi/"), next_id (1) {
    std::filesystem::create_directories (entries_directory);

    LoadFromFile ();
}

Diary::~Diary () {
    try {
        SaveIndexFile ();
    } catch (const std::exception& e) {
        std::cerr << "Greška pri čuvanju dnevnika: " << e.what () << std::endl;
    }
}

void Diary::LoadFromFile () {
    std::fstream index (index_file);
    if (!index.is_open ()) {
        std::cout << "Prazan dnevnik" << std::endl;
        return;
    }

    std::string current_line;
    while (std::getline (index, current_line)) {
        if (current_line.empty ()) continue;

        try {
            DiaryEntry entry = ParseIndexLine (current_line);
            if (entry.GetID () >= next_id) {
                next_id = entry.GetID () + 1;
            }
        } catch (const std::exception e) {
            std::cerr << "Greška " << e.what () << " pri parsiranju linije - " << current_line << std::endl;
        }
    }

    index.close ();
}

void Diary::SaveIndexFile () {
    std::ofstream output_file (index_file, std::ios::trunc);
    if (!output_file.is_open ()) {
        throw std::runtime_error ("Ne mogu otvoriti index fajl!");
    }

    for (const auto& entry : entries) {
        output_file << EntryToIndexLine (entry) << "\n";
    }
    output_file.close ();
}

void Diary::SaveEntryContent (const DiaryEntry& entry) {
    // TODO: Implementiraj čuvanje sadržaja u poseban fajl
}

std::string Diary::LoadEntryContent (const std::string& filename) {
    // TODO: Implementiraj učitavanje sadržaja iz fajla
    return "";
}

DiaryEntry Diary::ParseIndexLine (const std::string& line) {
    int id, priority;
    Date date;
    Time time;
    std::string short_description, file_name;

    int index = 0;
    auto split_view = std::views::split (line, '|');

    try {
        for (const auto subrange : split_view) {
            std::string sub_string (subrange.begin (), subrange.end ());
            switch (index) {
                case 0:
                    id = std::stoi (sub_string);
                    break;
                case 1:
                    priority = std::stoi (sub_string);
                    break;
                case 2:
                    date.ParseDate (sub_string);
                    break;
                case 3:
                    time.ParseTime (sub_string);
                    break;
                case 4:
                    short_description = sub_string;
                    break;
                case 5:
                    file_name = sub_string;
                    break;
            }
        }
    } catch (std::invalid_argument& e) {
        std::cerr << "Neispravan format: " << e.what () << std::endl;
    }
    return DiaryEntry (id, priority, date, time, short_description, file_name);
}

std::string Diary::EntryToIndexLine (const DiaryEntry& entry) {
    return entry.GetStringifiedEntry ();
}

void Diary::AddEntry (int priority, const Date& date, const Time& time, const std::string& short_description,
                      const std::string& entry_text) {
    // TODO: Implementiraj dodavanje unosa
}

void Diary::DeleteLastEntry () {
    // TODO: Implementiraj brisanje posljednjeg unosa
}

void Diary::UndoDelete () {
    // TODO: Implementiraj vraćanje obrisanog unosa
}

void Diary::ShowTop5Priority () {
    // TODO: Implementiraj prikaz top 5 prioritetnih unosa
}

void Diary::ShowAllDates () {
    // TODO: Implementiraj prikaz svih datuma
}

void Diary::ShowEntriesForDate (const Date& date) {
    // TODO: Implementiraj prikaz unosa za datum
}

void Diary::ShowEntriesByDateRange (const Date& from, const Date& to) {
    // TODO: Implementiraj filtriranje po opsegu datuma
}

int Diary::GetTotalEntries () const {
    return entries.GetSize ();
}

void Diary::ClearAll () {
    // TODO: Implementiraj brisanje svih unosa
}