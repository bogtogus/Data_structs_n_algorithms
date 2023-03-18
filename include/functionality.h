#pragma once

void extend_passport(const char passport[], char*& dest, const int key_size);
void extend_flight(const char flight[], char*& dest, const int num_size);
bool is_number(const std::string& s);
bool is_avianum_correct(const std::string number, const int num_size);
bool compare_fragments(const std::string& line, const std::string& need);
bool validate_date(const std::string date, bool birth=false);
bool validate_dateNtime(const std::string dateNtime);
bool validate_name(const std::string name, bool fio=false);
void format_fio(std::string& fio);
void downcase_word(std::string& word);
bool is_letter_upper(const char ch);
char uppercase(const char ch);
