#include "DiaryEntry.hpp"

std::string DiaryEntry::GetStringifiedEntry () {
    return "ID: " + std::to_string (this->id) + " | " + "Prioritet: " + std::to_string (this->priority) + " | " +
           "Datum: " + this->date.GetDateAsString () + " | " + "Vrijeme:" + this->time.GetTimeAsString () + " | " +
           "Kratak Opis:" + this->short_description;
}

int DiaryEntry::CompareTo (const DiaryEntry& other) const {
    if (this->date < other.date) return -1;
    if (this->date > other.date) return 1;

    // Ako je isti datum, uporedi po vremenu
    if (this->time < other.time) return -1;
    if (this->time > other.time) return 1;

    return 0;  // Potpuno isti datum i vreme
}

bool DiaryEntry::operator< (const DiaryEntry& other) const {
    if (this->priority != other.priority) {
        return this->priority < other.priority;
    }

    return this->CompareTo (other) < 0;
}

bool DiaryEntry::operator> (const DiaryEntry& other) const {
    if (this->priority != other.priority) {
        return this->priority > other.priority;
    }
    return CompareTo (other) > 0;
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

// TODO dodati komparatore > < kao i komparacije po datumima