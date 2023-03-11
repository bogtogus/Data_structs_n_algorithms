#pragma once
//#include <string>

struct passenger {
    char passport[11]{}; // NNNNNNNNNN
    std::string issuance;
    std::string fio;
    char birth[11]{}; // DD.MM.YYYY
};

int hash_key(const std::string key, const int key_size, const int size);
bool validate_date(const std::string date);
bool is_key_correct(const std::string key, const int key_size);
bool is_key_correct(char key[], const int key_size);
void clear_sheet(passenger*& sheet, const int size);
bool is_pass_exists(passenger*& sheet, std::string pass, const int passnum_size, const int sheet_size);

void format_fio(std::string& fio);
void downcase_word(std::string& word);
bool is_letter_upper(const char ch);
char uppercase(const char ch);
