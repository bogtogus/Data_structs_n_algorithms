#pragma once
//#include <string>

struct passenger {
    char passport[11]{}; // NNNNNNNNNN
    std::string issuance;
    std::string fio;
    char birth[11]{}; // DD.MM.YYYY
};

int hash_key(const std::string key, const int key_size, const int sheet_size);
bool is_key_correct(const std::string key, const int key_size);
bool is_key_correct(const char key[], const int key_size);
void clear_sheet(passenger*& sheet, const int sheet_size);
bool is_pass_exists(const database* const DB, const std::string pass);
bool is_sheet_empty(const passenger*, const int);
