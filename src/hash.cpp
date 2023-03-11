#include <main.h>
#include <hash.h>

int hash_key(const std::string key, const int passnum_size, const int sheet_size) {
    unsigned long int result=((int)key[0]+1) * 11;
    for (int i = 1; i < passnum_size; i++) {
        if (i % 2 == 0) {
            result += ((int)key[i] + pow(3,i)) * pow(11, (int)log10(result) + 1);
        }
        else {
            result += ((int)key[i] + pow(4,i)) * pow(7, (int)log10(result) + 1);
        }
    }
    result %= sheet_size;
    return (int)result;
}

bool is_key_correct(const char key[], const int passnum_size) {
    for (int i=0; i< passnum_size; i++) {
        if (!isdigit(key[i])) {
            if (key[i] == '-' && i == 4) {
                continue;
            }
            return false;
        }
    }
    return true;
}

bool is_key_correct(const std::string key, const int passnum_size) {
    if (key.length() > passnum_size) {
        return false;
    }
    for (int i=0; i< passnum_size; i++) {
        if (!isdigit(key[i])) {
            if (key[i] == '-' && i == 4) {
                continue;
            }
            return false;
        }
    }
    return true;
}

void clear_sheet(passenger*& sheet, const int size) {
    for (int i = 0; i< size; i++) {
        strcpy_s(sheet[i].passport, "");
    }
}

bool is_pass_exists(const database* const DB, const std::string pass) {
    std::string ps = pass;
    if (pass.find('-') != std::string::npos) {
        ps.erase(4, 1);
    }
    int hashed = hash_key(ps, DB->passnum_size, DB->sheet_size);
    int o = 1;
    while (strcmp(DB->passengers[hashed].passport, ps.c_str()) != 0 &&
            strcmp(DB->passengers[hashed].passport, "\0") != 0) {
        hashed += 3*o + 7 * (int)pow(o, 2);
        hashed %= DB->sheet_size;
        o++;
        if (o == DB->sheet_size) {
            return false;
        }
    }
    if (o < DB->sheet_size && strcmp(DB->passengers[hashed].passport, ps.c_str()) == 0) {
        return true;
    }
    return false;
}

bool is_sheet_empty(const passenger* sheet, const int sheet_size) {
    for (int i = 0; i < sheet_size; i++) {
        if (std::strcmp(sheet[i].passport, "\0") != 0) {
            return false;
        }
    }
    return true;
}
