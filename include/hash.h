#pragma once
//#include <string>

struct passenger {
    char passport[11]{}; // NNNNNNNNNN
    std::string issuance;
    std::string fio;
    char birth[11]{}; // DD.MM.YYYY
};

struct found_passengers {
    passenger* psg = nullptr;
    found_passengers* next = nullptr;
};

int hash_key(const std::string key, const int key_size, const int sheet_size);
bool is_key_correct(const std::string key, const int key_size);
bool is_key_correct(const char key[], const int key_size);
void clear_sheet(passenger*& sheet, const int sheet_size);
bool is_pass_exists(const database* const DB, const std::string pass);
bool is_sheet_empty(const passenger*, const int);
void push_back(found_passengers*&, passenger* const);
void copy_element(const passenger& src, passenger*& dest);
void push_back(found_passengers*& fpas, passenger* const psg);
void output_passengers(found_passengers* const a);
void clear_list(found_passengers*& head);
