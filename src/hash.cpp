#include <main.h>
#include <math.h>
#include <hash.h>

int hash_key(const std::string key, const int key_size, const int size) {
    unsigned long int result=((int)key[0]+1) * 11;
    for (int i = 1; i < key_size; i++) {
        if (i % 2 == 0) {
            result += ((int)key[i]+pow(3,i)) * pow(11, (int)log10(result) + 1);
        }
        else {
            result += ((int)key[i]+pow(4,i)) * pow(7, (int)log10(result) + 1);
        }
    }
    result %= size;
    return (int)result;
}

bool is_key_correct(char key[], const int key_size) {
    for (int i=0; i< key_size; i++) {
        if (!isdigit(key[i])) {
            if (key[i] == '-' && i == 4) {
                continue;
            }
            return false;
        }
    }
    return true;
}

bool is_key_correct(const std::string key, const int key_size) {
    if (key.length() > key_size) {
        return false;
    }
    for (int i=0; i< key_size; i++) {
        if (!isdigit(key[i])) {
            if (key[i] == '-' && i == 4) {
                continue;
            }
            return false;
        }
    }
    return true;
}

bool validate_date(const std::string date) {
    if (date.length() > 10) {
        return false;
    }
    const char* mask = "DD.MM.YYYY";
    for (int i=0; i < 10; i++) {
        if (mask[i] == 'D' || mask[i] == 'M' || mask[i] == 'Y') {
            if (!isdigit(date[i])) {
                return false;
            }
        }
        else {
            if (date[i] != '.') {
                return false;
            }
        }
    }
    return true;
}

void clear_sheet(passenger*& sheet, const int size) {
    for (int i = 0; i< size; i++) {
        strcpy(sheet[i].passport, "");
    }
}

void format_fio(std::string& fio) {
    bool space = false;
    downcase_word(fio);
    for (std::string::size_type i = 0; i < fio.size(); i++) {
        if (i == 0) {
            fio[i] = uppercase(fio[i]);
            continue;
        }
        if (fio[i] == ' ') {
            space = true;
            continue;
        }
        if (space) {
            fio[i] = uppercase(fio[i]);
            space = false;
        }
    }
}

void downcase_word(std::string& word) {
    int first_up = (int)'А';
    int last_up = (int)'Я';
    int yo_up = (int)'Ё';
    for (std::string::size_type i = 0; i < word.size(); i++) {
        if (is_letter_upper(word[i])) {
            if ((int)word[i] > 0) {
                word[i] = tolower(word[i]);
            }
            else {
                if ((int)word[i] >= first_up && (int)word[i] <= last_up) {
                    word[i] = (char)((int)word[i] + 32);
                }
                else if ((int)word[0] == yo_up) {
                    word[i] = 'ё';
                }
                else {
                    continue;
                }
            }
        }
    }
}

bool is_letter_upper(const char ch) {
    int first_down = (int)'а';
    int last_down = (int)'я';
    int yo_down = (int)'ё';
    if ((((int)ch >= first_down && (int)ch <= last_down) ||
            (int)ch == yo_down)) { // если расширенный символ - строчная буква или не буква
        return false;
    }
    else if ((islower(ch) || !isalpha(ch))) { // если ASCII - строчная буква или не буква
        return false;
    }
    return true;
}

char uppercase(const char ch) {
    int first_down = (int)'а';
    int last_down = (int)'я';
    int yo_down = (int)'ё';
    if (ch > 0) {
        return toupper(ch);
    }
    else {
        if ((int)ch >= first_down && (int)ch <= last_down) {
            return (char)((int)ch - 32);
        }
        else if ((int)ch == yo_down) {
            return 'Ё';
        }
    }
    return ch;
}

bool is_pass_exists(passenger*& sheet, std::string pass, const int passnum_size, const int sheet_size) {
    int hashed = hash_key(pass, passnum_size, sheet_size);
    int o = 1;
    while (strcmp(sheet[hashed].passport, "\0") != 0) {
        hashed += 3*o + 7*pow(o, 2);
        hashed %= sheet_size;
        o++;
        if (o == sheet_size) {
            return false;
        }
    }
    if (o < sheet_size && strcmp(sheet[hashed].passport, pass.c_str()) == 0) {
        return true;
    }
    return false;
}
