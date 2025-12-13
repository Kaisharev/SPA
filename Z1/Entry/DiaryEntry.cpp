#include "DiaryEntry.hpp"

std::string DiaryEntry::GetStringifiedEntry () const {
    return "ID: " + std::to_string (id) + " | " + "Prioritet: " + std::to_string (priority) + " | " +
           "Datum: " + date.GetDateAsString () + " | " + "Vrijeme: " + time.GetTimeAsString () + " | " +
           "Kratak Opis: " + short_description;
}

std::string DiaryEntry::GetIndexFormat () const {
    return std::to_string (id) + " | " + std::to_string (priority) + " | " + date.GetDateAsString () + " | " +
           time.GetTimeAsString () + " | " + short_description + " | " + file_name;
}

int DiaryEntry::CompareTo (const DiaryEntry& other) const {
    if (date < other.date) return -1;
    if (date > other.date) return 1;

    // Ako je isti datum, uporedi po vremenu
    if (time < other.time) return -1;
    if (time > other.time) return 1;

    return 0;
}

std::string DiaryEntry::LoadEntryFromFile () {
    std::filesystem::path file_path = std::filesystem::path ("unosi") / file_name;
    std::ifstream inputFile (file_path);

    if (!inputFile.is_open ()) {
        throw std::invalid_argument ("Traženi fajl ne postoji!");
    }

    std::string content;
    std::string line;
    while (std::getline (inputFile, line)) {
        content += line + "\n";
    }
    inputFile.close ();

    return content;
}

std::string DiaryEntry::GetEntryText () const {
    return entry_text;
}

std::string DiaryEntry::GetFileName () const {
    return file_name;
}
Date DiaryEntry::GetDate () const {
    return date;
}
bool DiaryEntry::operator< (const DiaryEntry& other) const {
    if (priority != other.priority) {
        return priority < other.priority;
    }

    return CompareTo (other) < 0;
}
bool DiaryEntry::operator> (const DiaryEntry& other) const {
    if (priority != other.priority) {
        return priority > other.priority;
    }

    return CompareTo (other) > 0;
}
