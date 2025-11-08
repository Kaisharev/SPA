// Diary.cpp
#include "Diary.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>



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
    if (!index.is_open()){
        std::cout << "Prazan dnecni"
    }
}

void Diary::SaveIndexFile () {
    // TODO: Implementiraj čuvanje u index fajl
}

void Diary::SaveEntryContent (const DiaryEntry& entry) {
    // TODO: Implementiraj čuvanje sadržaja u poseban fajl
}

std::string Diary::LoadEntryContent (const std::string& filename) {
    // TODO: Implementiraj učitavanje sadržaja iz fajla
    return "";
}

DiaryEntry Diary::ParseIndexLine (const std::string& line) {
    // TODO: Implementiraj parsiranje linije iz index fajla
    // Format: ID|Prioritet|Datum|Vrijeme|Kratak_Opis|Ime_Fajla

    // Privremeno vraćam dummy objekat
    return DiaryEntry (0, 0, Date::Today (), Time::CurrentTime (), "", "", "");
}

std::string Diary::EntryToIndexLine (const DiaryEntry& entry) {
    // TODO: Implementiraj formatiranje u liniju za index
    return "";
}

// ====================================================================
// PUBLIC INTERFACE
// ====================================================================

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