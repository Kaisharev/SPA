#include "Diary.hpp"

Diary& Diary::GetInstance () {
    static Diary instance;
    return instance;
}

Diary::Diary () : index_file ("dnevnik.txt"), entries_directory ("unosi/"), next_id (1) {
    try {
        std::filesystem::create_directories (entries_directory);
    } catch (const std::exception& e) {
        std::cerr << "Ne mogu kreirati direktorijum: " << e.what ();
    }

    try {
        LoadFromFile ();
    } catch (const std::exception& e) {
        std::cerr << "Greška pri otvaranju dnevnika: " << e.what ();
    }
}

Diary::~Diary () {
    try {
        SaveIndexFile ();
    } catch (const std::exception& e) {
        std::cerr << "Greška pri čuvanju dnevnika: " << e.what () << std::endl;
    }
}

bool Diary::ValidateEntry (int priority, std::string short_description, std::string entry_text) const {
    if (priority < 1 || priority > 10) {
        throw std::invalid_argument ("Niste unijeli adekvatan prioritet!");
        return false;
    }

    if (short_description.empty () || entry_text.empty ()) {
        throw std::invalid_argument ("Niste unijeli adekvatan prioritet!");
        return false;
    }

    if (short_description.length () < 10) {
        throw std::invalid_argument ("Prekratak opis!");
        return false;
    }

    if (short_description.length () > entry_text.length ()) {
        throw std::invalid_argument ("Kratki opis je duži od punog opisa!");
        return false;
    }

    return true;
}

void Diary::LoadFromFile () {
    std::fstream index (index_file);
    if (!index.is_open () || index.fail () || index.bad ()) {
        std::cerr << "Greška pri otvaranju index fajla: " << index_file << std::endl;
        return;
    }

    std::string current_line;
    while (std::getline (index, current_line)) {
        if (current_line.empty ()) {
            continue;
        }

        try {
            DiaryEntry entry = ParseIndexLine (current_line);
            all_entries.InsertBack (entry);
            if (entry.GetID () >= next_id) {
                next_id = entry.GetID () + 1;
            }
        } catch (const std::exception& e) {
            std::cerr << "Greška " << e.what () << " pri parsiranju linije - " << current_line << std::endl;
        }
    }
}

void Diary::SaveIndexFile () {
    std::ofstream output_file (index_file, std::ios::trunc);
    if (!output_file.is_open ()) {
        throw std::runtime_error ("Ne mogu otvoriti index fajl!");
    }

    for (const auto& entry : all_entries) {
        output_file << EntryToIndexLine (entry) << "\n";
    }
}

void Diary::SaveEntryContent (const DiaryEntry& entry) {
    std::ofstream entry_output (entries_directory + entry.GetFileName (), std::ios::trunc);
    if (!entry_output.is_open ()) {
        throw std::runtime_error ("Ne mogu otvoriti index fajl!");
    }
    entry_output << entry.GetEntryText ();
}

std::string Diary::LoadEntryContent (const std::string& filename) {
    std::fstream entry_input (entries_directory + filename);
    std::string file_content ((std::istreambuf_iterator<char> (entry_input)), std::istreambuf_iterator<char> ());

    return file_content;
}

DiaryEntry Diary::ParseIndexLine (const std::string& line) {
    int id, priority;
    Date date;
    Time time;
    std::string short_description, file_name;

    int index = 0;
    auto split_view = std::views::split (line, '|');
    std::string entry_text;
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
                    date = Date::ParseDate (sub_string);
                    break;
                case 3:
                    time = Time::ParseTime (sub_string);
                    break;
                case 4:
                    short_description = sub_string;
                    break;
                case 5:
                    file_name = sub_string;
            }
            index++;
        }
        entry_text = LoadEntryContent (file_name);

    } catch (std::invalid_argument& e) {
        std::cerr << "Neispravan format: " << e.what () << std::endl;
    }
    return DiaryEntry (id, priority, date, time, short_description, entry_text, file_name);
}

std::string Diary::EntryToIndexLine (const DiaryEntry& entry) {
    return entry.GetStringifiedEntry ();
}

void Diary::AddEntry (int priority, const Date& date, const Time& time, const std::string& short_description,
                      const std::string& entry_text) {
    if (!ValidateEntry (priority, short_description, entry_text)) return;

    std::string file_name = "unos" + std::to_string (next_id) + ".txt";

    DiaryEntry new_entry (next_id++, priority, date, time, short_description, entry_text, file_name);

    all_entries.InsertBack (new_entry);
    current_entries.InsertBack (new_entry);

    SaveEntryContent (new_entry);
    SaveIndexFile ();
}

void Diary::DeleteLastEntry () {
    if (current_entries.IsEmpty ()) {
        throw std::logic_error ("Ne postoji unos koji možete obrisati!");
    }
    DiaryEntry last_entry = current_entries.GetLastElement ();
    undo_stack.push (last_entry);
    std::filesystem::remove (entries_directory + last_entry.GetFileName ());

    current_entries.RemoveBack ();
    all_entries.RemoveBack ();

    SaveIndexFile ();
    std::cout << "Obrisan poslednji unos" << std::endl;
}

void Diary::UndoDelete () {
    if (undo_stack.IsEmpty ()) {
        throw std::logic_error ("Ne postoji unos koji možete vratiti!");
    }
    DiaryEntry undo_entry = undo_stack.peek ();
    current_entries.InsertBack (undo_entry);
    all_entries.InsertBack (undo_entry);
    undo_stack.pop ();

    SaveEntryContent (undo_entry);
    SaveIndexFile ();
    std::cout << "Vraćen unos (ID: " << undo_entry.GetID () << ")" << std::endl;
}

void Diary::ShowTop5Priority () {
    PriorityQueue<DiaryEntry> queue;
    int counter = 0;
    all_entries.ForEach ([&queue] (const DiaryEntry& entry) {
        queue.Insert (entry);
    });

    for (int i = 0; i < MAX_ENTRIES && !queue.IsEmpty (); i++) {
        DiaryEntry priority_entry = queue.ExtractMax ();
        std::cout << "P R I O R I T E T N I  P R I K A Z \n\n" << std::endl;
        std::cout << priority_entry.GetStringifiedEntry () << std::endl;
    }
    // TODO: Implementiraj prikaz top 5 prioritetnih unosa
}

void Diary::ShowAllDates () {
    // TODO: Implementiraj prikaz svih datuma
}

void Diary::ShowEntriesForDate (const Date& date) {
    bool found_entry = false;
    std::cout << "Unosi za " << date.GetDateAsString () << std::endl;

    for (auto& entry : all_entries) {
        if (entry.GetDate () == date) {
            found_entry = true;
            std::cout << "\n" << entry.GetStringifiedEntry () << std::endl;

            std::string entry_content = LoadEntryContent (entry.GetFileName ());
            std::cout << "Sadržaj unosa \n" << entry_content << std::endl;
        }
    }

    if (!found_entry) {
        std::cout << "Ne postoji unos za ovaj datum!" << std::endl;
    }
}

void Diary::ShowEntriesByDateRange (const Date& from, const Date& to) {
    bool found_entry = false;
    std::cout << "Unosi u intervalu od: " << from.GetDateAsString () << " do: " << to.GetDateAsString () << std::endl;
    for (auto& entry : all_entries) {
        if (entry.GetDate () >= from && entry.GetDate () <= to) {
            found_entry = true;
            std::cout << "\n" << entry.GetStringifiedEntry () << std::endl;

            std::string entry_content = LoadEntryContent (entry.GetFileName ());
            std::cout << "Sadržaj unosa \n" << entry_content << std::endl;
        }
    }
}

int Diary::GetTotalEntries () const {
    return all_entries.GetSize ();
}

void Diary::ClearAll () {
    // TODO: Implementiraj brisanje svih unosa
}