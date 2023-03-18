#include <list.h>
using namespace std;

void clear_list(ticket_trade*& head) {
    if (head == nullptr) {
        return;
    }
    ticket_trade* cur_ticket = head;
    ticket_trade* next_ticket = cur_ticket->next;
    while (next_ticket != head) {
        delete cur_ticket;
        cur_ticket = next_ticket;
        next_ticket = cur_ticket->next;
    }
    delete cur_ticket;
    head = nullptr;
}

void show_list(ticket_trade* head, const int pass_size, const int avianum_size) {
    if (head == nullptr) {
        return;
    }
    ticket_trade* cur_ticket = head;
    char* passport = new char[pass_size + 1]{};
    char* flight = new char[avianum_size + 1]{};
    do {
        cout << setfill('-') << '/' << setw(33) << '\\' << setfill(' ') << endl;
        cout << setw(22) << left << "¦ Билет №";
        cout << setw(11) << right << cur_ticket->ticket << setw(1) << '|' << endl;
        cout << setw(22) << left << "¦ Паспорт покупателя: "; 
        extend_passport(cur_ticket->passport, passport, pass_size);
        cout << setw(11) << right << passport << setw(1) << '|'<< endl;
        cout << setw(22) << left << "¦ Рейс №";
        extend_flight(cur_ticket->flight_number, flight, avianum_size);
        cout << setw(11) << right << flight << setw(1) << '|' << endl;
        cout << setfill('-') << '\\'<< setw(33) << '/' << setfill(' ') << endl;
        cur_ticket = cur_ticket->next;
    } while (cur_ticket != head);
    delete[] passport;
    delete[] flight;
}

int pop_ticket(ticket_trade*& head, const string passport, const string flight) {
    ticket_trade* prev = nullptr;
    if (head == nullptr) {
        return 1;
    }
    ticket_trade* current = head;
    while (current->next != head &&
                (current->passport != passport ||
                current->flight_number != flight)) {
        prev = current;
        current = current->next;
    }
    if (current->next == head &&
            (current->passport != passport ||
            current->flight_number != flight)) {
        return 2;
    }
    if (prev != nullptr) {
        prev->next = current->next;
    }
    else {
        head = nullptr;
    }
    delete current;
    return 0;
}

void push_ticket(ticket_trade*& head, const string passport, const string flight) {
    ticket_trade* p = new ticket_trade{};
    strcpy_s(p->passport, passport.c_str());
    strcpy_s(p->flight_number, flight.c_str());
    ticket_trade* current = head;
    char* temp = nullptr;
    if (head == nullptr) {
        temp = encode_ticket(1);
        //cout << &temp << endl;
        strcpy_s(p->ticket, temp);
        delete[] temp;
        head = p;
        p->next = p;
    }
    else {
        while (current->next != head && 
                decode_ticket(current->ticket) + 1 == decode_ticket(current->next->ticket)) {
            current = current->next;
        }
        temp = encode_ticket(decode_ticket(current->ticket) + 1);
        //cout << &temp << endl;
        strcpy_s(p->ticket, temp);
        delete[] temp;
        p->next = current->next;
        current->next = p;
    }
}

void push_ticket_ff(ticket_trade*& head, const std::string passport, const std::string flight, const std::string tnum) {
    ticket_trade* p = new ticket_trade{};
    strcpy_s(p->passport, passport.c_str());
    strcpy_s(p->flight_number, flight.c_str());
    ticket_trade* current = head;
    if (head == nullptr) {
        strcpy_s(p->ticket, tnum.c_str());
        head = p;
        p->next = p;
    }
    else {
        while (current->next != head) {
            current = current->next;
        }
        strcpy_s(p->ticket, tnum.c_str());
        p->next = current->next;
        current->next = p;
    }
}

unsigned int decode_ticket(const char tnum[]) {
    unsigned int number = 0;
    for (int i = 8; i >= 0; i--) {
        if (tnum[i] >= '0') {
            //cout << tnum[i] << endl;
            number += ((int)tnum[i] - (int)'0') * pow(10, 8-i);
        }
    }
    return number;
}

char* encode_ticket(const unsigned int number) {
    char* tnum = new char[10]{};
    unsigned int n = number;
    for (int i = 8; i >= 0; i--) {
        tnum[i] = ('0' + (n % 10));
        n /= 10;
    }
    return tnum;
}

bool is_exists(ticket_trade*& head, const string number) {
    if (head == nullptr) {
        return false;
    }
    ticket_trade* cur_ticket = head;
    if (strcmp(cur_ticket->ticket, number.c_str()) == 0) {
        return true;
    }
    cur_ticket = cur_ticket->next;
    while (cur_ticket != head) {
        if (strcmp(cur_ticket->ticket, number.c_str()) == 0) {
            return true;
        }
        cur_ticket = cur_ticket->next;
    }
    return false;
}

bool is_copy(ticket_trade*& head, const string passport, string flight) {
    if (head == nullptr) {
        return false;
    }
    ticket_trade* cur_ticket = head;
    if (strcmp(cur_ticket->passport, passport.c_str()) == 0 && 
            strcmp(cur_ticket->flight_number, flight.c_str()) == 0) {
        return true;
    }
    cur_ticket = cur_ticket->next;
    while (cur_ticket != head) {
        if (strcmp(cur_ticket->passport, passport.c_str()) == 0 && 
                strcmp(cur_ticket->flight_number, flight.c_str())) {
            return true;
        }
        cur_ticket = cur_ticket->next;
    }
    return false;
}

bool is_list_empty(ticket_trade*& head) {
    if (head == nullptr) {
        return true;
    }
    return false;
}

void sort(ticket_trade*& head) {
    if (head == nullptr) {
        return;
    }
    else if (head->next == head) {
        return;
    }
    ticket_trade* current = head->next;
    ticket_trade** pointers_array = nullptr; // массив указателей
    ticket_trade* temp = nullptr;
    int k = 1;
    while (current != head) {
        k++;
        current = current->next;
    }
    current = head;
    pointers_array = new ticket_trade*[k]{};
    for (int i = 0; i < k; i++) {
        pointers_array[i] = current;
        current = current->next;
    }
    for (int i = 1; i < k; i++) {
        for(int j = i; j >= 1; j--) { // сдвиг текущего элемента влево
            if (decode_ticket(pointers_array[j]->ticket) < decode_ticket(pointers_array[j - 1]->ticket)) {
                temp = pointers_array[j];
                pointers_array[j] = pointers_array[j - 1];
                pointers_array[j - 1] = temp;
            }
            else {
                break; // элемент на своём месте
            }
        }
        //for (int o = 0; o< k; o++) {
        //    cout << pointers_array[o]->ticket << " | ";
        //}
        //cout << endl;
    }
    head = pointers_array[0];
    current = head;
    for (int i = 1; i < k; i++) {
        current->next = pointers_array[i];
        current = current->next;
    }
    current->next = head;
    delete[] pointers_array;
}

void del_tickets_byAvr(ticket_trade*& head, const char* number) {
    ticket_trade* prev = nullptr;
    ticket_trade* new_head = nullptr;
    ticket_trade* current = head;
    if (head == nullptr) {
        return;
    }
    else if (head->next == head) {
        delete head;
        head = nullptr;
    }
    else {
        while (strcmp(head->flight_number, number) == 0) { // удаление пока в голове списка нужное число
            prev = head;
            new_head = head->next;
            current = current->next;
            while (current->next != head) { // замена зацикливающего(конечного) указателя на новый
                current = current->next;
            }
            current->next = new_head;
            delete head;
            head = new_head;
        }
        prev = current;
        current = current->next;
        while (current != head) {
            if (strcmp(current->flight_number, number) == 0) {
                prev->next = current->next;
                delete current;
                current = prev;
            }
            prev = current;
            current = current->next;
        }
    }
}

void del_tickets_byPass(ticket_trade*& head, const char* passport) {
    ticket_trade* prev = nullptr;
    ticket_trade* new_head = nullptr;
    ticket_trade* current = head;
    if (head == nullptr) {
        return;
    }
    else if (head->next == head) {
        delete head;
        head = nullptr;
    }
    else {
        while (strcmp(head->passport, passport) == 0) { // удаление пока в голове списка нужное число
            prev = head;
            new_head = head->next;
            current = current->next;
            while (current->next != head) { // замена зацикливающего(конечного) указателя на новый
                current = current->next;
            }
            current->next = new_head;
            delete head;
            head = new_head;
        }
        prev = current;
        current = current->next;
        while (current != head) {
            if (strcmp(current->passport, passport) == 0) {
                prev->next = current->next;
                delete current;
                current = prev;
            }
            prev = current;
            current = current->next;
        }
    }
}
