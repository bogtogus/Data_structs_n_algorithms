#include <iostream>
#include <menu.h>
using namespace std;

int menu(passenger*& sheet, flight*& flights, ticket_trade*& tickets, int sheet_size) {
    int hashed = 0;
    int num = 0;
    bool cycle = true;
    const int passnum_size = 11; //NNNN-NNNNNN  
    const int avianum_size = 7; // AAA-NNN
    menu_help();
    while (cycle) {
        cout << "������� �������:" << endl;
        while(input_int(num)) {
            cout << "������ �����. ���������� ������: ";
        }
        switch(num) {
            case 1: {
                menu_pass(sheet, flights, tickets, sheet_size, passnum_size);
                menu_help();
                break;
            }
            case 2: {
                menu_avia(sheet, flights, tickets, sheet_size, passnum_size);
                menu_help();
                break;
            }
            case 3: { //reg ticket
                menu_reg_ticket(tickets, sheet, flights, passnum_size, sheet_size);
                break;
            }
            case 4: { // refund ticket
                menu_ref_ticket(tickets, sheet, flights, passnum_size, sheet_size);
                break;
            }
            case 5: {
                show_list(tickets, passnum_size, avianum_size);
            }
            case 6: {
                menu_help();
                break;
            }
            case 7: {
                menu_load_data(sheet, flights, tickets, sheet_size, passnum_size);
                break;
            }
            case 8: {
                cout << "�� �������, ��� ������ �����? (1 - ��, 2 - ���)" << endl;
                int ex_des = 0;
                while(input_int(ex_des)) {
                    cout << "������ �����. ���������� ������: ";
                }
                if (ex_des == 1) {
                    cout << "����� �� ����." << endl;
                    cycle = false;
                }
                else if (ex_des == 2) {
                    cout << "����������� � ����." << endl;
                }
                else {
                    cout << "������� �� ����������. ����������� � ����." << endl;
                }
                break;
            }
            default: {
                cout << "������� �� ����������." << endl;
            }
        }
    }

    return 0;
}

void menu_help() {
    cout << "= ���� =" << endl << "�������:" << endl;
    cout << "1 - ������� � ������� \"���������\";" << endl;
    cout << "2 - ������� � ������� \"���������\";" << endl;
    cout << "3 - ���������������� ������� ������;" << endl;
    cout << "4 - ���������������� ������� ������;" << endl;
    cout << "5 - ������� ������ ���� �������;" << endl;
    cout << "6 - ������ �� ��������;" << endl;
    cout << "7 - �������� ���� ������ �� �����;" << endl;
    cout << "8 - ����� �� ����;" << endl;
}

int menu_reg_ticket(ticket_trade*& tickets, passenger*& sheet, flight*& flights, const int passnum_size, const int sheet_size) {
    while (true) {
        cout << "���������� ���������� � ������� ������." << endl;
        cout << "������� ������� ���������� � ������� \"NNNN-NNNNNN\":" << endl;
        string pass;
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(),'\n');
        getline(cin, pass);
        if (strcmp(pass.c_str(), "/") == 0) {
            cout << "����������� � ����." << endl;
            break;
        }
        if (!is_key_correct(pass, passnum_size)) {
            cout << "�������� ����� �������. ���������� ������" << endl;
            cout << "��� ������� \"/\" ��� ������ � ����." << endl;
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail(),'\n');
            continue;
        }
        else if (!is_pass_exists(sheet, pass, passnum_size, sheet_size)) {
            cout << "����� �������� �� ���������������." << endl;
            continue;
        }
        pass.erase(4, 1);
        cout << "������� ����� ��������� � ������� \"AAA-NNN\":" << endl;
        string avia;
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(),'\n');
        getline(cin, avia);
        while (!is_num_correct(avia, 7)) {
            cout << "����� ��������� ����� �������. ���������� ������" << endl;
            cout << "��� ������� \"/\" ��� ������ � ����." << endl;
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail(),'\n');
            getline(cin, avia);
        }
        if (!is_exists(flights, avia)) {
            cout << "����� ������� �� ���������������." << endl;
            continue;
        }
        avia.erase(3, 1); // AAANNN
        if (!is_copy(tickets, pass, avia)) {
            push_ticket(tickets, pass, avia);
            cout << "���������� � ������� ������ ���������." << endl;
            sort(tickets);
        }
        else {
            cout << "����� ����� ��� ���������������." << endl;
        }
        break;
    }
    return 0;
}

int menu_ref_ticket(ticket_trade*& tickets, passenger*& sheet, flight*& flights, const int passnum_size, const int sheet_size) {
    if (is_list_empty(tickets)) {
        cout << "���� ������ � �������� �����. �������� �� ���������." << endl;
    }
    while (true) {
        cout << "������� ������." << endl;
        cout << "������� ������� ��������� � ������� \"NNNN-NNNNNN\":" << endl;
        string pass;
        int flag = 0;
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(),'\n');
        getline(cin, pass);
        if (strcmp(pass.c_str(), "/") == 0) {
            cout << "����������� � ����." << endl;
            break;
        }
        if (!is_key_correct(pass, passnum_size)) {
            cout << "�������� ����� �������. ���������� ������" << endl;
            cout << "��� ������� \"/\" ��� ������ � ����." << endl;
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail(),'\n');
            continue;
        }
        else if (!is_pass_exists(sheet, pass, passnum_size, sheet_size)) {
            cout << "����� �������� �� ���������������." << endl;
            continue;
        }
        pass.erase(4, 1);
        cout << "������� ����� ��������� � ������� \"AAA-NNN\":" << endl;
        string avia;
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(),'\n');
        getline(cin, avia);
        while (!is_num_correct(avia, 7)) {
            cout << "����� ��������� ����� �������. ���������� ������." << endl;
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail(),'\n');
            getline(cin, avia);
        }
        if (!is_exists(flights, avia)) {
            cout << "����� ������� �� ���������������." << endl;
            continue;
        }
        avia.erase(3, 1); // AAANNN
        flag = pop_ticket(tickets, pass, avia);
        if (flag == 0) {
            cout << "����� ����� �� ����." << endl;
            sort(tickets);
        }
        else if (flag == 2){
            cout << "������ ������ �� ����������������." << endl;
        }
        break;
    }
    return 0;
}

int menu_load_data(passenger*& sheet, flight*& flights, ticket_trade*& tickets, 
                   int sheet_size, const int passnum_size) {
    
    int flag = 0;
    cout << "�������� ������ �� �����." << endl;
    char buff[512]{};
    GetModuleFileNameA(NULL, buff, 512);
    string path(buff);
    path.erase(path.rfind('\\') + 1, 9);
    ifstream file;
    cout << path << endl;
    file.open(path + "_passengers.txt");
    if (!file.is_open()) {
        cout << "���� 1 �� ������." << endl;
        flag = 1;
    }
    else {
        flag = load_pass(file, sheet, sheet_size, passnum_size);
    }
    file.close();
    file.open(path + "_flights.txt");
    if (!file.is_open()) {
        cout << "���� 2 �� ������." << endl;
        flag = 1;
    }
    else {
        flag = load_avia(file, flights);
    }
    file.close();
    file.open(path + "_tickets.txt");
    if (!file.is_open()) {
        cout << "���� 3 �� ������." << endl;
        flag = 1;
    }
    else {
        flag = load_tickets(file, tickets, passnum_size);
    }
    file.close();
    if (!flag) {
        cout << "�������� ���������." << endl;
    }
    return 0;
}

int load_pass(ifstream& file, passenger*& sheet, int sheet_size, const int passnum_size) {
    int hashed = 0;
    bool something_read = false;
    int i = 0;
    string* data = new string[4]{};
    while (!file.eof()) {
        for (i = 0; i < 4; i++) {
            getline(file, data[i]);
            if (!data[i].compare("") || !data[i].compare("@")) {
                break;
            }
            if (file.eof() || !file.good()) {
                file.clear();
                file.ignore(file.rdbuf()->in_avail(), '@');
                break;
            }
        }
        if (i != 4) {
            continue;
        }
        else if (!is_key_correct(data[0], passnum_size) ||
                !validate_date(data[3])) {
            file.clear();
            file.ignore(file.rdbuf()->in_avail(), '@');
            continue;
        }
        data[0].erase(4, 1);
        hashed = hash_key(data[0], passnum_size, sheet_size);
        int o = 1;
        //cout << (sheet[hashed] == nullptr) << endl;
        while (strcmp(sheet[hashed].passport, "\0") != 0) {
            hashed += 3*o + 7*pow(o, 2);
            hashed %= sheet_size;
            o++;
            if (o == sheet_size) {
                break;
            }
        }
        if (o < sheet_size) {
            strcpy(sheet[hashed].passport, data[0].c_str());
            sheet[hashed].issuance = data[1];
            sheet[hashed].fio = data[2];
            strcpy(sheet[hashed].birth, data[3].c_str());
            something_read = true;
        }
    }
    delete[] data;
    if(!something_read) return 1;
    return 0;
}

int load_avia(ifstream& file, flight*& flights) {
    string* data = new string[8]{};
    bool something_read = false;
    int i = 0;
    while (!file.eof()) {
        for (i = 0; i < 8; i++) {
            getline(file, data[i]);
            if (!data[i].compare("") || !data[i].compare("@")) {
                break;
            }
            if (file.eof() || !file.good()) {
                file.clear();
                file.ignore(file.rdbuf()->in_avail(), '@');
                break;
            }
        }
        if (i != 8) {
            continue;
        }
        else if (!is_num_correct(data[0], 7) || !is_number(data[6]) || !is_number(data[7])) {
            file.clear();
            file.ignore(file.rdbuf()->in_avail(), '@');
            continue;
        }
        data[0].erase(3, 1);
        flight* f = new flight;
        strcpy(f->number, data[0].c_str());
        f->company = data[1];
        f->departure = data[2];
        f->arriving = data[3];
        f->dep_time = data[4];
        f->arv_time = data[5];
        f->places = stoi(data[6]);
        f->free = stoi(data[7]);
        add_element(flights, *f);
        something_read = true;
    }
    delete[] data;
    if(!something_read) return 1;
    return 0;
}

int load_tickets(ifstream& file, ticket_trade*& tickets, const int passnum_size) {
    bool something_read = false;
    int i = 0;
    string* data = new string[3]{};
    while (!file.eof()) {
        for (i = 0; i < 3; i++) {
            getline(file, data[i]);
            if (!data[i].compare("") || !data[i].compare("@")) {
                break;
            }
            if (file.eof() || !file.good()) {
                file.clear();
                file.ignore(file.rdbuf()->in_avail(), '@');
                break;
            }
        }
        if (i != 3) {
            continue;
        }
        else if (!is_key_correct(data[0], passnum_size) || !is_num_correct(data[1], 7)) {
            file.clear();
            file.ignore(file.rdbuf()->in_avail(), '@');
            continue;
        }
        data[0].erase(4, 1);
        data[1].erase(3, 1);
        push_ticket_ff(tickets, data[0], data[1], data[2]);
        something_read = true;
    }
    delete[] data;
    //show_list(tickets, passnum_size, 7);
    sort(tickets);
    if(!something_read) return 1;
    return 0;
}

int menu_pass(passenger*& sheet, flight*& flights, ticket_trade*& tickets, int sheet_size,  const int passnum_size) {
    int hashed = 0;
    int num = 0;
    bool cycle = true;

    menu_help_psg();
    while (cycle) {
        cout << "������� �������:" << endl;
        while(input_int(num)) {
            cout << "������ �����. ���������� ������: ";
        }
        switch(num) {
            case 0: {
                cycle = false;
                cout << "������� � ������� ����." << endl;
                break;
            }
            case 1: {
                menu_add_psg(sheet, sheet_size, passnum_size);
                break;
            }
            case 2: {
                menu_del_psg(sheet, sheet_size, passnum_size);
                break;
            }
            case 3: { //find passport
                menu_find_num_psg(sheet, sheet_size, passnum_size);
                break;
            }
            case 4: { // find fio
                menu_find_fio_psg(sheet, sheet_size, passnum_size);
                break;
            }
            case 5: {
                menu_show_psg(sheet, sheet_size, passnum_size);
                break;
            }
            case 6: {
                cout << "�� �������, ��� ������ �������� ������ ����������? " << endl;
                cout << "(1 - ��, 2 - ���)" << endl;
                int ex_des = 0;
                while(input_int(ex_des)) {
                    cout << "������ �����. ���������� ������: ";
                }
                if (ex_des == 1) {
                    cout << "�������." << endl;
                    clear_sheet(sheet, sheet_size);
                }
                else if (ex_des == 2) {
                    cout << "����������� � ����." << endl;
                }
                else {
                    cout << "������� �� ����������. ����������� � ����." << endl;
                }
                break;
            }
            case 7: {
                menu_help_psg();
            }
            default: {
                cout << "������� �� ����������." << endl;
            }
        }
    }

    return 0;
}

void menu_help_psg() {
    cout << "[���������] �������:" << endl;
    cout << "0 - ������� �����;" << endl;
    cout << "1 - �������� ���������;" << endl;
    cout << "2 - ������� ���������;" << endl;
    cout << "3 - ����� ��������� �� ��������;" << endl;
    cout << "4 - ����� ��������� �� ��� ���;" << endl;
    cout << "5 - ����� ���� ����������;" << endl;
    cout << "6 - ������� ���� ������ � ����������;" << endl;
    cout << "7 - ������ �� ��������;" << endl;
}

int menu_avia(passenger*& sheet, flight*& flights, ticket_trade*& tickets, int sheet_size, const int passnum_size) {
    int hashed = 0;
    int num = 0;
    bool cycle = true;
    int avianum_size = 7;

    menu_help_avr();
    while (cycle) {
        cout << "������� �������:" << endl;
        while(input_int(num)) {
            cout << "������ �����. ���������� ������: ";
        }
        switch(num) {
            case 0: {
                cycle = false;
                cout << "������� � ������� ����." << endl;
                break;
            }
            case 1: {
                menu_add_avr(flights, avianum_size);
                break;
            }
            case 2: {
                menu_del_avr(flights, avianum_size);
                break;
            }
            case 3: { //find passport
                menu_find_num_avr(flights, avianum_size);
                break;
            }
            case 4: { // find fio
                menu_find_dest_avr(flights, avianum_size);
                break;
            }
            case 5: {
                menu_show_avr(flights, avianum_size);
                break;
            }
            case 6: {
                cout << "�� �������, ��� ������ �������� ������ ����������? " << endl;
                cout << "(1 - ��, 2 - ���)" << endl;
                int ex_des = 0;
                while(input_int(ex_des)) {
                    cout << "������ �����. ���������� ������: ";
                }
                if (ex_des == 1) {
                    cout << "�������." << endl;
                    clear_flights(flights);
                }
                else if (ex_des == 2) {
                    cout << "����������� � ����." << endl;
                }
                else {
                    cout << "������� �� ����������. ����������� � ����." << endl;
                }
                break;
            }
            case 7: {
                menu_help_avr();
            }
            case 8: {
                output_tree_height(flights, 0, 1);
            }
            default: {
                cout << "������� �� ����������." << endl;
            }
        }
    }

    return 0;
}

void menu_help_avr() {
    cout << "[���������] �������:" << endl;
    cout << "0 - ������� �����;" << endl;
    cout << "1 - �������� ��������;" << endl;
    cout << "2 - ������� ��������;" << endl;
    cout << "3 - ����� �������� �� ��� ������;" << endl;
    cout << "4 - ����� �������� �� �������� ��������� ��������;" << endl;
    cout << "5 - ����� ���� ����������;" << endl;
    cout << "6 - ������� ���� ������ �� ����������;" << endl;
    cout << "7 - ������ �� ��������;" << endl;
}

int input_int(int& num) {
    int n=0;
    cin >> n;
    while (!cin.good()) {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(),'\n');
        return 1;
    }
    if (cin.rdbuf()->in_avail() > 1) {
        cin.ignore(cin.rdbuf()->in_avail(),'\n');
    }
    num = n;
    return 0;
}

int menu_add_psg(passenger*& sheet, int size, const int passnum_size) {
    int hashed = 0;
    while (true) {
        cout << "����������. ������� ������� � ������� \"NNNN-NNNNNN\":" << endl;
        string inp;
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(),'\n');
        getline(cin, inp);
        if (is_key_correct(inp, passnum_size)) {
            inp.erase(4, 1);
            hashed = hash_key(inp, passnum_size, size);
            int o = 1;
            while (strcmp(sheet[hashed].passport, "\0") != 0) {
                hashed += 3*o + 7*pow(o, 2);
                hashed %= size;
                o++;
                if (o == size) {
                    break;
                }
            }
            if (o < size) {
                if (is_pass_exists(sheet, inp, passnum_size, size)) {
                    cout << "����� �������� ��� ����������." << endl;
                    break;
                }
                strcpy(sheet[hashed].passport, inp.c_str());
                string longinp;
                //cout << sheet[hashed].passport << endl;
                cout << "������� ����� � ���� ������ ��������:" << endl;
                getline(cin, longinp);
                longinp.resize(128);
                sheet[hashed].issuance = longinp;
                //cout << sheet[hashed].passport << endl;
                cout << "������� ��� ���������:" << endl;
                getline(cin, longinp);
                format_fio(longinp);
                sheet[hashed].fio = longinp;
                
                cout << "������� ���� �������� ��������� (DD.MM.YYYY):" << endl;
                getline(cin, longinp);
                while(!validate_date(longinp)) {
                    cout << "���� �������� ������� �������. ���������� ������:" << endl;
                    getline(cin, longinp);
                }
                strcpy(sheet[hashed].birth, longinp.c_str());
                cout << "�������� ��������." << endl;
            }
            else {
                cout << "�� ������� �������� ���������." << endl;
            }
            break;
        }
        else {
            cout << "������� ����� �������. ���������� ������." << endl;
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail(),'\n');
            continue;
        }
    }
    return 0;
}

int menu_del_psg(passenger*& sheet, int size, const int passnum_size) {
    cout << "��������. ������� �������:" << endl;
    int hashed = 0;
    while (true) {
        string inp;
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(),'\n');
        getline(cin, inp);
        if (is_key_correct(inp, passnum_size)) {
            inp.erase(4, 1);
            hashed = hash_key(inp, passnum_size, size);
            if (strcmp(sheet[hashed].passport, inp.c_str()) == 0) {
                char emptys[12]{};
                strcpy(sheet[hashed].passport, (const char*)emptys);
                cout << "�������� �����." << endl;
            }
            else {
                int o = 1;
                while (strcmp(sheet[hashed].passport, "\0") != 0) {
                    hashed += 3*o + 7*pow(o, 2);
                    hashed %= size;
                    o++;
                    if (o == size) {
                        break;
                    }
                }
                if (o < size && strcmp(sheet[hashed].passport, inp.c_str()) == 0) {
                    char emptys[12]{};
                    strcpy(sheet[hashed].passport, (const char*)emptys);
                    cout << "�������� �����." << endl;
                }
                else {
                    cout << "�� ������� ������� ���������." << endl;
                }
            }
            break;
        }
        else {
            cout << "������� ��������� ����� �������. ���������� ������." << endl;
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail(),'\n');
            continue;
        }
    }
    return 0;
}

int menu_find_num_psg(passenger* sheet, int size, const int passnum_size) {
    cout << "�����. ������� ����� �������� ���������:" << endl;
    int hashed = 0;
    while (true) {
        string inp;
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(),'\n');
        getline(cin, inp);
        if (strcmp(inp.c_str(), "/") == 0) {
            cout << "����������� � ����." << endl;
            break;
        }
        if (is_key_correct(inp, passnum_size)) {
            inp.erase(4, 1);
            hashed = hash_key(inp, passnum_size, size);
            int o = 1;
            while (hashed < size && strcmp(sheet[hashed].passport, inp.c_str()) != 0) {
                hashed += 3*o + 7*pow(o, 2);
                hashed %= size;
                o++;
                if (o == size) {
                    break;
                }
            }
            if (o < size) {
                cout << "�������� ������(" << hashed << "). ���������� � ��:" << endl;
                cout << "������� �" << sheet[hashed].passport << endl;
                cout << "����� " << sheet[hashed].issuance << endl;
                cout << sheet[hashed].fio << endl;
                cout << "���� �������� " <<sheet[hashed].birth << endl;
                cout << "����������� � ����." << endl;
                break;
            }
            else {
                cout << "�� ������� ����� ���������. ���������� ������"<< endl;
                cout << "��� ������� \"/\" ��� ������ � ����:" << endl;
                cin.clear();
                cin.ignore(cin.rdbuf()->in_avail(),'\n');
                continue;
            }
        }
        else {
            cout << "������� ����� �������. ���������� ������." << endl;
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail(),'\n');
            continue;
        }
    }
    return 0;
}

int menu_find_fio_psg(passenger* sheet, int size, const int passnum_size) {
    cout << "�����. ������� ��� ���������:" << endl;
    int hashed = 0;
    while (true) {
        string inp;
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(),'\n');
        getline(cin, inp);
        if (strcmp(inp.c_str(), "/") == 0) {
            cout << "����������� � ����." << endl;
            break;
        }
        format_fio(inp);
        int i = 0;
        for (i = 0; i < size; i++) { 
            if (strcmp(sheet[i].fio.c_str(), inp.c_str()) == 0) {
                break;
            }
        }
        if (i < size) {
            cout << "�������� ������(" << i << "). ���������� � ��:" << endl;
            cout << "������� �" << sheet[i].passport << endl;
            cout << "����� " << sheet[i].issuance << endl;
            cout << sheet[i].fio << endl;
            cout << "���� �������� " <<sheet[i].birth << endl;
            cout << "����������� � ����." << endl;
            break;
        }
        else {
            cout << "�� ������� ����� ���������. ���������� ������"<< endl;
            cout << "��� ������� \"/\" ��� ������ � ����:" << endl;
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail(),'\n');
            continue;
        }
    }
    return 0;
}

void menu_show_psg(passenger* sheet, int size, const int passnum_size) {
    cout << "�������: " << endl;
    bool not_empty = false;
    for (int i = 0; i< size; i++) {
        if (strcmp(sheet[i].passport, "\0") != 0) {
            cout << i << ": " << extend_passport(sheet[i].passport, passnum_size) << " " << sheet[i].issuance << " " << sheet[i].fio << endl;
            not_empty = true;
        }
    }
    if (!not_empty) {
        cout << "...�����." << endl;
    }
}

int menu_add_avr(flight*& flights, const int number_size) {
    while (true) {
        cout << "����������. ������� ����� ����� � ������� \"NNN-NNN\":" << endl;
        string inp;
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(),'\n');
        getline(cin, inp);
        if (strcmp(inp.c_str(), "/") == 0) {
            cout << "����������� � ����." << endl;
            break;
        }
        if (is_num_correct(inp, number_size)) {
            if (is_exists(flights, inp)) {
                cout << "����� ���� ��� ����������. ���������� ������" << endl;
                cout << "��� ������� \"/\" ��� ������ � ����:" << endl;
                cin.clear();
                cin.ignore(cin.rdbuf()->in_avail(),'\n');
                continue;
            }
            string longinp;
            flight* newflight = new flight;
            int places = 0;
            inp.erase(3, 1);
            strcpy(newflight->number, inp.c_str());
            cout << "������� �������� �����:" << endl;
            getline(cin, longinp);
            longinp.resize(128);
            newflight->company = longinp;
            cout << "������� ����� ����������� �����:" << endl;
            getline(cin, longinp);
            longinp.resize(128);
            newflight->departure = longinp;
            cout << "������� ����� �������� �����:" << endl;
            getline(cin, longinp);
            longinp.resize(128);
            newflight->arriving = longinp;
            cout << "������� ����� ����������� �����:" << endl;
            getline(cin, longinp);
            longinp.resize(128);
            newflight->dep_time = longinp;
            cout << "������� ����� �������� �����:" << endl;
            getline(cin, longinp);
            longinp.resize(128);
            newflight->arv_time = longinp;
            cout << "������� ���������� ���� � �������:" << endl;
            while(input_int(places)) {
                cout << "������ �����. ���������� ������: ";
            }
            newflight->places = places;
            cout << "������� ���������� ��������� ����:" << endl;
            while(input_int(places) || places > newflight->places) {
                cout << "������ �����. ���������� ������: ";
            }
            newflight->free = places;
            add_element(flights, *newflight);
            cout << "�������� ��������." << endl;
            break;
        }
        else {
            cout << "����� ����� �������. ���������� ������" << endl;
            cout << "��� ������� \"/\" ��� ������ � ����:" << endl;
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail(),'\n');
            continue;
        }
    }
    return 0;
}

int menu_del_avr(flight*& flights, const int number_size) {
    if (flights == nullptr) {
        cout << "������ ���������� ����. �������� �� ���������." << endl;
        return 1;
    }
    while (true) {
        cout << "��������. ������� ����� �����:" << endl;
        string inp;
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(),'\n');
        getline(cin, inp);
        if (strcmp(inp.c_str(), "/") == 0) {
            cout << "����������� � ����." << endl;
            break;
        }
        if (is_num_correct(inp, number_size)) {
            inp.erase(3, 1);
            if (delete_element(flights, stoi(inp)) == 2) {
                cout << "�������� �� ������. ���������� ������" << endl;
                cout << "��� ������� \"/\" ��� ������ � ����:" << endl;
                continue;
            }
            else {
                cout << "�������� �����." << endl;
                break;
            }
        }
    }
    return 0;
}

int menu_find_num_avr(flight* flights, const int number_size) {
    if (flights == nullptr) {
        cout << "������ ���������� ����. �������� �� ���������." << endl;
        return 1;
    }
    while (true) {
        cout << "����� �����. ������� ����� �����:" << endl;
        string inp;
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(),'\n');
        getline(cin, inp);
        if (strcmp(inp.c_str(), "/") == 0) {
            cout << "����������� � ����." << endl;
            break;
        }
        if (is_num_correct(inp, number_size)) {
            flight* found = nullptr;
            inp.erase(3, 1);
            found = find_element(flights, stoi(inp));
            if (found == nullptr) {
                cout << "�������� �� ������. ���������� ������" << endl;
                cout << "��� ������� \"/\" ��� ������ � ����:" << endl;
                cin.clear();
                cin.ignore(cin.rdbuf()->in_avail(),'\n');
                continue;
            }
            else {
                cout << "�������� ������. ���������� � ��:" << endl;
                std::cout << "���� �" << found->number << std::endl;
                std::cout << "��������: " << found->company << std::endl;
                std::cout << "������������ ��: " << found->departure << std::endl;
                std::cout << "�: " << found->arriving << std::endl;
                std::cout << "����� �����������: " << found->dep_time << std::endl;
                std::cout << "����� ��������: " << found->arv_time << std::endl;
                std::cout << "����� " << found->places << " ����, �� ������� " << found->free << "��������." << std::endl;
                break;
            }
        }
        else {

        }
    }
    return 0;
}

int menu_find_dest_avr(flight* flights, const int number_size) {
    if (flights == nullptr) {
        cout << "������ ���������� ����. �������� �� ���������." << endl;
        return 1;
    }
    while (true) {
        cout << "����� ������. ������� ����� ����������:" << endl;
        string inp;
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(),'\n');
        getline(cin, inp);
        if (strcmp(inp.c_str(), "/") == 0) {
            cout << "����������� � ����." << endl;
            break;
        }
        found_flights* found = nullptr;
        find_elements_bytext(flights, found, inp);
        if (found == nullptr) {
            cout << "�������� �� ������. ���������� ������" << endl;
            cout << "��� ������� \"/\" ��� ������ � ����:" << endl;
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail(),'\n');
            continue;
        }
        else {
            output_flights(found);
            break;
        }
    }
    return 0;
}

void menu_show_avr(flight* flights, const int number_size) {
    if (flights == nullptr) {
        cout << "������ ���������� ����. �������� �� ���������." << endl;
    }
    else {
        cout << "���������:" << endl;
        output_flights(flights);
    }
}


