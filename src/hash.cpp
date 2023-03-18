#include <main.h>
#include <hash.h>
#include <functionality.h>

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

void push_back(found_passengers*& fpas, passenger* const psg) {
    found_passengers* new_fpas = new found_passengers;
    found_passengers* cur_fpas = fpas;
    new_fpas->psg = new passenger;
    copy_element(*psg, new_fpas->psg);
    if (fpas == nullptr) {
        fpas = new_fpas;
    }
    else {
        while (cur_fpas->next != nullptr) {
            cur_fpas = cur_fpas->next;
        }
        cur_fpas->next = new_fpas;
    }
}

void copy_element(const passenger& src, passenger*& dest) {
    strcpy_s(dest->passport, src.passport);
    dest->issuance = src.issuance;
    dest->fio = src.fio;
    strcpy_s(dest->birth, src.birth);
}

void output_passengers(found_passengers* const a) {
    if (a == nullptr) {
        return;
    }
    char* passport = new char[12]{};
    found_passengers* b = a;
    while(b != nullptr) {
        extend_passport(b->psg->passport, passport, 11);
        std::cout << std::setw(16) << std::left << "Паспорт №" << passport << std::endl;
        std::cout << std::setw(16) << std::left << "Выдан " << b->psg->issuance << std::endl;
        std::cout << std::setw(16) << std::left << "Ф.И.О. " << b->psg->fio << std::endl;
        std::cout << std::setw(16) << std::left << "Дата рождения: " << b->psg->birth << std::endl;
        std::cout << std::setw(16) << std::left << "Возвращение в меню." << std::endl;  
        b = b->next;
    }
    delete[] passport;
}

void clear_list(found_passengers*& head) {
    if (head == nullptr) {
        return;
    }
    found_passengers* cur_passenger = head;
    found_passengers* next_passenger = cur_passenger->next;
    while (next_passenger != nullptr) {
        delete cur_passenger;
        cur_passenger = next_passenger;
        next_passenger = cur_passenger->next;
    }
    delete cur_passenger;
    head = nullptr;
}
