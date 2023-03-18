#define STRINGIFY(x) #x
#define EXPAND(x) STRINGIFY(x)
#include <iostream>
#include <menu.h>
using namespace std;

int menu(database* const DB) {
    int hashed = 0;
    int num = 0;
    bool cycle = true;
    menu_help();
    while (cycle) {
        cout << "Введите команду:" << endl;
        while(input_int(num)) {
            cout << "[X] Ошибка ввода. Попробуйте заново: ";
        }
        switch(num) {
            case 1: {
                menu_pass(DB);
                menu_help();
                break;
            }
            case 2: {
                menu_avia(DB);
                menu_help();
                break;
            }
            case 3: { //reg ticket
                menu_reg_ticket(DB);
                break;
            }
            case 4: { // refund ticket
                menu_ref_ticket(DB);
                break;
            }
            case 5: {
                menu_show_tickets(DB); 
            }
            case 6: {
                menu_help();
                break;
            }
            case 7: {
                menu_load_data(DB);
                break;
            }
            case 0: {
                cout << "Вы уверены, что хотите выйти? (1 - да, 2 - нет)" << endl;
                int ex_des = 0;
                while(input_int(ex_des)) {
                    cout << "Ошибка ввода. Попробуйте заново: ";
                }
                if (ex_des == 1) {
                    cout << "Выход из меню." << endl;
                    cycle = false;
                }
                else if (ex_des == 2) {
                    cout << "Возвращение в меню." << endl;
                }
                else {
                    cout << "Команда не распознана. Возвращение в меню." << endl;
                }
                break;
            }
            default: {
                cout << "Команда не распознана." << endl;
            }
        }
    }

    return 0;
}

void menu_help() {
    cout << "= МЕНЮ =" << endl << "Команды:" << endl;
    cout << "1 - перейти к разделу \"Пассажиры\";" << endl;
    cout << "2 - перейти к разделу \"Авиарейсы\";" << endl;
    cout << "3 - зарегистрировать продажу билета;" << endl;
    cout << "4 - зарегистрировать возврат билета;" << endl;
    cout << "5 - вывести список всех билетов;" << endl;
    cout << "6 - помощь по командам;" << endl;
    cout << "7 - загрузка всех данных из файла;" << endl;
    cout << "0 - выход из меню;" << endl;
}

int menu_reg_ticket(database* const DB) {
    while (true) {
        cout << "Добавление информации о покупке билета." << endl;
        cout << "Введите паспорт покупателя в формате \"NNNN-NNNNNN\":" << endl;
        string pass;
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(),'\n');
        getline(cin, pass);
        if (strcmp(pass.c_str(), "/") == 0) {
            cout << "Возвращение в меню." << endl;
            break;
        }
        if (!is_key_correct(pass, DB->passnum_size)) {
            cout << "|\\/| Пасспорт введён неверно. Попробуйте заново" << endl;
            cout << "|/\\| или введите \"/\" для выхода в меню." << endl;
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail(),'\n');
            continue;
        }
        else if (!is_pass_exists(DB, pass)) {
            cout << "[X] Такой пассажир не зарегистрирован." << endl;
            continue;
        }
        pass.erase(4, 1);
        cout << "Введите номер авиарейса в формате \"AAA-NNN\":" << endl;
        string avia;
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(),'\n');
        getline(cin, avia);
        while (!is_avianum_correct(avia, DB->avianum_size)) {
            cout << "|\\/| Номер авиарейса введён неверно. Попробуйте заново" << endl;
            cout << "|/\\| или введите \"/\" для выхода в меню." << endl;
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail(),'\n');
            getline(cin, avia);
        }
        if (!is_exists(DB->flights, avia)) {
            cout << "[X] Такой авирейс не зарегистрирован." << endl;
            continue;
        }
        avia.erase(3, 1); // AAANNN
        if (!is_copy(DB->tickets, pass, avia)) {
            push_ticket(DB->tickets, pass, avia);
            cout << "Информация о покупке билета добавлена." << endl;
            sort(DB->tickets);
        }
        else {
            cout << "[X] Такой билет уже зарегистрирован." << endl;
        }
        break;
    }
    return 0;
}

int menu_ref_ticket(database* const DB) {
    if (is_list_empty(DB->tickets)) {
        cout << "База данных с билетами пуста. Операция не выполнена." << endl;
        return 1;
    }
    while (true) {
        cout << "Возврат билета." << endl;
        cout << "Введите паспорт пассажира в формате \"NNNN-NNNNNN\":" << endl;
        string pass;
        int flag = 0;
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(),'\n');
        getline(cin, pass);
        if (strcmp(pass.c_str(), "/") == 0) {
            cout << "Возвращение в меню." << endl;
            break;
        }
        if (!is_key_correct(pass, DB->passnum_size)) {
            cout << "|\\/| Пасспорт введён неверно. Попробуйте заново" << endl;
            cout << "|/\\| или введите \"/\" для выхода в меню." << endl;
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail(),'\n');
            continue;
        }
        //else if (!is_pass_exists(sheet, pass, passnum_size, sheet_size)) {
        //    cout << "Такой пассажир не зарегистрирован." << endl;
        //    continue;
        //}
        pass.erase(4, 1);
        cout << "Введите номер авиарейса в формате \"AAA-NNN\":" << endl;
        string avia;
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(),'\n');
        getline(cin, avia);
        while (!is_avianum_correct(avia, DB->avianum_size)) {
            cout << "Номер авиарейса введён неверно. Попробуйте заново." << endl;
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail(),'\n');
            getline(cin, avia);
        }
        //if (!is_exists(flights, avia)) {
        //    cout << "Такой авирейс не зарегистрирован." << endl;
        //    continue;
        //}
        avia.erase(3, 1); // AAANNN
        flag = pop_ticket(DB->tickets, pass, avia);
        if (flag == 0) {
            cout << "Билет удалён из базы." << endl;
            sort(DB->tickets);
        }
        else if (flag == 2){
            cout << "[X] Такого билета не зарегестрировано." << endl;
        }
        break;
    }
    return 0;
}

void menu_show_tickets(const database* const DB) {
    if (DB->tickets == nullptr) {
        cout << "Список билетов пуст. Операция не выполнена." << endl;
    }
    else {
        cout << "Список билетов:" << endl;
        show_list(DB->tickets, DB->passnum_size, DB->avianum_size);
    }
}

int menu_load_data(database* const DB) {
    int flag = 0;
    cout << "Загрузка данных из файла." << endl;
    //string path = EXPAND(UNITTESTPRJ);
    //path.erase(0, 1);
    //path.erase(path.length() - 2);
    char* locpath = new char[MAX_PATH]{};
    GetModuleFileNameA(NULL, locpath, MAX_PATH);
    string path = locpath;
    while (path.find('\\') != string::npos) {
        path.replace(path.find('\\'), 1, "/");
    }
    path.erase(path.rfind('/') + 1, 8);
    delete[] locpath;
    ifstream file;
    cout << path << endl;
    file.open(path + "_passengers.txt");
    if (!file.is_open()) {
        cout << "[X] Файл 1 не найден." << endl;
    }
    else {
        flag = load_pass(file, DB);
    }
    file.close();
    file.open(path + "_flights.txt");
    if (!file.is_open()) {
        cout << "[X] Файл 2 не найден." << endl;
    }
    else {
        flag = load_avia(file, DB);
    }
    file.close();
    file.open(path + "_tickets.txt");
    if (!file.is_open()) {
        cout << "[X] Файл 3 не найден." << endl;
    }
    else {
        flag = load_tickets(file, DB);
    }
    file.close();
    if (!flag) {
        cout << "Загрузка завершена." << endl;
    }
    return 0;
}

int load_pass(ifstream& file, database* const DB) {
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
        else if (!is_key_correct(data[0], DB->passnum_size) ||
                !validate_name(data[1].substr(0, data[1].rfind(' '))) ||
                !validate_date(data[1].substr(data[1].rfind(' ') + 1)) ||
                !validate_name(data[2]) ||
                !validate_date(data[3])) {
            file.clear();
            file.ignore(file.rdbuf()->in_avail(), '@');
            continue;
        }
        data[0].erase(4, 1);
        hashed = hash_key(data[0], DB->passnum_size, DB->sheet_size);
        int o = 1;
        //cout << (DB->passengers[hashed] == nullptr) << endl;
        while (strcmp(DB->passengers[hashed].passport, data[0].c_str()) != 0 &&
                strcmp(DB->passengers[hashed].passport, "\0") != 0) {
            hashed += 3*o + 7*(int)pow(o, 2);
            hashed %= DB->sheet_size;
            o++;
            if (o == DB->sheet_size) {
                break;
            }
        }
        if (o < DB->sheet_size) {
            if (strcmp(DB->passengers[hashed].passport, data[0].c_str()) == 0) {
                //cout << "Такой пассажир уже существует." << endl;
                break;
            }
            strcpy_s(DB->passengers[hashed].passport, data[0].c_str());
            DB->passengers[hashed].issuance = data[1];
            DB->passengers[hashed].fio = data[2];
            strcpy_s(DB->passengers[hashed].birth, data[3].c_str());
            something_read = true;
        }
    }
    delete[] data;
    if(!something_read) return 1;
    return 0;
}

int load_avia(ifstream& file, database* const DB) {
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
        else if (!is_avianum_correct(data[0], DB->avianum_size) || 
            !validate_name(data[2]) ||
            !validate_name(data[3]) ||
            !validate_dateNtime(data[4]) ||
            !validate_dateNtime(data[5]) ||
            !is_number(data[6]) || 
            !is_number(data[7])) {
            file.clear();
            file.ignore(file.rdbuf()->in_avail(), '@');
            continue;
        }
        else if (is_exists(DB->flights, (const string)data[0])) {
            file.clear();
            file.ignore(file.rdbuf()->in_avail(), '@');
            continue;
        }
        data[0].erase(3, 1);
        flight* f = new flight;
        strcpy_s(f->number, data[0].c_str());
        f->company = data[1];
        f->departure = data[2];
        f->arriving = data[3];
        f->dep_time = data[4];
        f->arv_time = data[5];
        f->places = stoi(data[6]);
        f->free = stoi(data[7]);
        add_element(DB->flights, *f);
        delete f;
        something_read = true;
    }
    delete[] data;
    if(!something_read) return 1;
    return 0;
}

int load_tickets(ifstream& file, database* const DB) {
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
        else if (!is_key_correct(data[0], DB->passnum_size) || 
                !is_avianum_correct(data[1], DB->avianum_size) ||
                data[2].length() != 9 ||
                !is_number(data[2]) ||
                is_exists(DB->tickets, data[2])) {
            file.clear();
            file.ignore(file.rdbuf()->in_avail(), '@');
            continue;
        }
        data[0].erase(4, 1);
        data[1].erase(3, 1);
        push_ticket_ff(DB->tickets, data[0], data[1], data[2]);
        something_read = true;
    }
    delete[] data;
    //show_list(tickets, passnum_size, 7);
    sort(DB->tickets);
    if(!something_read) return 1;
    return 0;
}

int menu_pass(database* const DB) {
    int hashed = 0;
    int num = 0;
    bool cycle = true;

    menu_help_psg();
    while (cycle) {
        cout << "Введите команду:" << endl;
        while(input_int(num)) {
            cout << "[X] Ошибка ввода. Попробуйте заново: ";
        }
        switch(num) {
            case 0: {
                cycle = false;
                cout << "Возврат в главное меню." << endl;
                break;
            }
            case 1: {
                menu_add_psg(DB);
                break;
            }
            case 2: {
                menu_del_psg(DB);
                break;
            }
            case 3: { //find passport
                menu_find_num_psg(DB);
                break;
            }
            case 4: { // find fio
                menu_find_fio_psg(DB);
                break;
            }
            case 5: {
                menu_show_psg(DB);
                break;
            }
            case 6: {
                cout << "Вы уверены, что хотите очистить список пассажиров? " << endl;
                cout << "(1 - да, 2 - нет)" << endl;
                int ex_des = 0;
                while(input_int(ex_des)) {
                    cout << "[X] Ошибка ввода. Попробуйте заново: ";
                }
                if (ex_des == 1) {
                    cout << "Очистка." << endl;
                    clear_sheet(DB->passengers, DB->sheet_size);
                }
                else if (ex_des == 2) {
                    cout << "Возвращение в меню." << endl;
                }
                else {
                    cout << "Команда не распознана. Возвращение в меню." << endl;
                }
                break;
            }
            case 7: {
                menu_help_psg();
            }
            default: {
                cout << "Команда не распознана." << endl;
            }
        }
    }

    return 0;
}

void menu_help_psg() {
    cout << "[ПАССАЖИРЫ] Команды:" << endl;
    cout << "0 - возврат назад;" << endl;
    cout << "1 - добавить пассажира;" << endl;
    cout << "2 - удалить пассажира;" << endl;
    cout << "3 - найти пассажира по паспорту;" << endl;
    cout << "4 - найти пассажира по его ФИО;" << endl;
    cout << "5 - вывод всех пассажиров;" << endl;
    cout << "6 - очистка всех данных о пассажирах;" << endl;
    cout << "7 - помощь по командам;" << endl;
}

int menu_avia(database* const DB) {
    int hashed = 0;
    int num = 0;
    bool cycle = true;

    menu_help_avr();
    while (cycle) {
        cout << "Введите команду:" << endl;
        while(input_int(num)) {
            cout << "Ошибка ввода. Попробуйте заново: ";
        }
        switch(num) {
            case 0: {
                cycle = false;
                cout << "Возврат в главное меню." << endl;
                break;
            }
            case 1: {
                menu_add_avr(DB);
                break;
            }
            case 2: {
                menu_del_avr(DB);
                break;
            }
            case 3: { //find passport
                menu_find_num_avr(DB);
                break;
            }
            case 4: { // find fio
                menu_find_dest_avr(DB);
                break;
            }
            case 5: {
                menu_show_avr(DB);
                break;
            }
            case 6: {
                cout << "Вы уверены, что хотите очистить список авиарейсов? " << endl;
                cout << "(1 - да, 2 - нет)" << endl;
                int ex_des = 0;
                while(input_int(ex_des)) {
                    cout << "Ошибка ввода. Попробуйте заново: ";
                }
                if (ex_des == 1) {
                    cout << "Очистка." << endl;
                    clear_flights(DB->flights);
                }
                else if (ex_des == 2) {
                    cout << "Возвращение в меню." << endl;
                }
                else {
                    cout << "Команда не распознана. Возвращение в меню." << endl;
                }
                break;
            }
            case 7: {
                menu_help_avr();
                break;
            }
            case 15: {
                cout << endl;
                output_tree_height(DB->flights, 0, 1);
                cout << tree_accuracy(DB->flights) << endl;
                break;
            }
            default: {
                cout << "Команда не распознана." << endl;
            }
        }
    }

    return 0;
}

void menu_help_avr() {
    cout << "[АВИАРЕЙСЫ] Команды:" << endl;
    cout << "0 - возврат назад;" << endl;
    cout << "1 - добавить авиарейс;" << endl;
    cout << "2 - удалить авиарейс;" << endl;
    cout << "3 - найти авиарейс по его номеру;" << endl;
    cout << "4 - найти авиарейс по названию аэропорта прибытия;" << endl;
    cout << "5 - вывод всех авиарейсов;" << endl;
    cout << "6 - очистка всех данных об авиарейсах;" << endl;
    cout << "7 - помощь по командам;" << endl;
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

int menu_add_psg(database* const DB) {
    int hashed = 0;
    while (true) {
        cout << "Добавление. Введите паспорт в формате \"NNNN-NNNNNN\":" << endl;
        string inp;
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(),'\n');
        getline(cin, inp);
        if (strcmp(inp.c_str(), "/") == 0) {
            cout << "Возвращение в меню." << endl;
            break;
        }
        if (is_key_correct(inp, DB->passnum_size)) {
            inp.erase(4, 1);
            hashed = hash_key(inp, DB->passnum_size, DB->sheet_size);
            int o = 1;
            while (strcmp(DB->passengers[hashed].passport, inp.c_str()) != 0 &&
                    strcmp(DB->passengers[hashed].passport, "\0") != 0) {
                hashed += 3*o + 7 * (int)pow(o, 2);
                hashed %= DB->sheet_size;
                o++;
                if (o == DB->sheet_size) {
                    break;
                }
            }
            if (o < DB->sheet_size) {
                if (strcmp(DB->passengers[hashed].passport, inp.c_str()) == 0) {
                    cout << "Такой пассажир уже существует." << endl;
                    break;
                }
                strcpy_s(DB->passengers[hashed].passport, inp.c_str());
                string longinp;
                //cout << DB->passengers[hashed].passport << endl;
                cout << "Введите место и дату выдачи паспорта." << endl;
                cout << "Дата от места выдачи должна отделяться пробелом:" << endl;
                getline(cin, longinp);
                while (!validate_name(longinp.substr(0, longinp.rfind(' '))) ||
                       !validate_date(longinp.substr(longinp.rfind(' ') + 1))) {
                    cout << "[X] Ошибка ввода. Попробуйте заново:" << endl;
                    getline(cin, longinp);
                }
                DB->passengers[hashed].issuance = longinp;
                //cout << DB->passengers[hashed].passport << endl;
                cout << "Введите ФИО пассажира:" << endl;
                getline(cin, longinp);
                format_fio(longinp);
                while (!validate_name(longinp, true)) {
                    cout << "[X] Ошибка ввода. Попробуйте заново:" << endl;
                    getline(cin, longinp);
                    format_fio(longinp);
                }
                DB->passengers[hashed].fio = longinp;
                
                cout << "Введите дату рождения пассажира (DD.MM.YYYY):" << endl;
                getline(cin, longinp);
                while(!validate_date(longinp, true)) {
                    cout << "[X] Дата рождения введена неверно. попробуйте заново:" << endl;
                    getline(cin, longinp);
                }
                strcpy_s(DB->passengers[hashed].birth, longinp.c_str());
                cout << "Пассажир добавлен." << endl;
            }
            else {
                cout << "[X] Не удалось добавить пассажира." << endl;
            }
            break;
        }
        else {
            cout << "|\\/| Паспорт введён неверно. Попробуйте заново" << endl;
            cout << "|/\\| или введите \"/\" для выхода в меню:" << endl;
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail(),'\n');
            continue;
        }
    }
    return 0;
}

int menu_del_psg(database* const DB) {
    cout << "Удаление. Введите паспорт:" << endl;
    int hashed = 0;
    while (true) {
        string inp;
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(),'\n');
        getline(cin, inp);
        if (strcmp(inp.c_str(), "/") == 0) {
            cout << "Возвращение в меню." << endl;
            break;
        }
        if (is_key_correct(inp, DB->passnum_size)) {
            inp.erase(4, 1);
            hashed = hash_key(inp, DB->passnum_size, DB->sheet_size);
            if (strcmp(DB->passengers[hashed].passport, inp.c_str()) == 0) {
                char emptys[12]{};
                strcpy_s(DB->passengers[hashed].passport, (const char*)emptys);
                cout << "Пассажир удалён вместе с его билетами." << endl;
                del_tickets_byPass(DB->tickets, inp.c_str());
            }
            else {
                int o = 1;
                while (strcmp(DB->passengers[hashed].passport, inp.c_str()) != 0 &&
                    strcmp(DB->passengers[hashed].passport, "\0") != 0) {
                    hashed += 3 * o + 7 * (int)pow(o, 2);
                    hashed %= DB->sheet_size;
                    o++;
                    if (o == DB->sheet_size) {
                        break;
                    }
                }
                if (o < DB->sheet_size && strcmp(DB->passengers[hashed].passport, inp.c_str()) == 0) {
                    char emptys[12]{};
                    strcpy_s(DB->passengers[hashed].passport, (const char*)emptys);
                    cout << "Пассажир удалён." << endl;
                }
                else {
                    cout << "[X] Не удалось удалить пассажира." << endl;
                }
            }
            break;
        }
        else {
            cout << "|\\/| Паспорт пассажира введён неверно. Попробуйте заново" << endl;
            cout << "|/\\| или введите \"/\" для выхода в меню:" << endl;
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail(),'\n');
            continue;
        }
    }
    return 0;
}

int menu_find_num_psg(database* const DB) {
    cout << "Поиск. Введите номер паспорта пассажира:" << endl;
    int hashed = 0;
    char* passport = new char[DB->passnum_size + 1] {};
    while (true) {
        string inp;
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(),'\n');
        getline(cin, inp);
        if (strcmp(inp.c_str(), "/") == 0) {
            cout << "Возвращение в меню." << endl;
            break;
        }
        if (is_key_correct(inp, DB->passnum_size)) {
            inp.erase(4, 1);
            hashed = hash_key(inp, DB->passnum_size, DB->sheet_size);
            int o = 1;
            while (hashed < DB->sheet_size && strcmp(DB->passengers[hashed].passport, inp.c_str()) != 0) {
                hashed += 3*o + 7 * (int)pow(o, 2);
                hashed %= DB->sheet_size;
                o++;
                if (o == DB->sheet_size) {
                    break;
                }
            }
            if (o < DB->sheet_size) {
                cout << "Пассажир найден(№" << hashed << "). Информация о нём:" << endl;
                extend_passport(DB->passengers[hashed].passport, passport, DB->passnum_size);
                cout << setw(16) << left << "Паспорт №" << passport << endl;
                cout << setw(16) << left << "Выдан " << DB->passengers[hashed].issuance << endl;
                cout << setw(16) << left << "Ф.И.О. " << DB->passengers[hashed].fio << endl;
                cout << setw(16) << left << "Дата рождения " <<DB->passengers[hashed].birth << endl;
                cout << setw(16) << left << "Возвращение в меню." << endl;
                break;
            }
            else {
                cout << "|\\/| Не удалось найти пассажира. Попробуйте заново"<< endl;
                cout << "|/\\| или введите \"/\" для выхода в меню:" << endl;
                cin.clear();
                cin.ignore(cin.rdbuf()->in_avail(),'\n');
                continue;
            }
        }
        else {
            cout << "[X] Паспорт введён неверно. Попробуйте заново." << endl;
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail(),'\n');
            continue;
        }
    }
    delete[] passport;
    return 0;
}

int menu_find_fio_psg(database* const DB) {
    
    found_passengers* fpas = nullptr;
    cout << "Поиск. Введите ФИО пассажира:" << endl;
    while (true) {
        string inp;
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(),'\n');
        getline(cin, inp);
        if (strcmp(inp.c_str(), "/") == 0) {
            cout << "Возвращение в меню." << endl;
            break;
        }
        format_fio(inp);
        int i = 0;
        for (i = 0; i < DB->sheet_size; i++) {
            if (strcmp(DB->passengers[i].fio.c_str(), inp.c_str()) == 0) {
                push_back(fpas, &DB->passengers[i]);
            }
        }
        if (fpas != nullptr) {
            std::cout << "Пассажир(ы) найден(ы). Информация:" << std::endl;
            output_passengers(fpas);
            clear_list(fpas);
            break;
        }
        else {
            cout << "|\\/| Не удалось найти пассажиров с такими ФИО. Попробуйте заново"<< endl;
            cout << "|/\\| или введите \"/\" для выхода в меню:" << endl;
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail(),'\n');
            continue;
        }
    }
    
    return 0;
}

void menu_show_psg(database* const DB) {
    if (!is_sheet_empty(DB->passengers, DB->sheet_size)) {
        cout << "Таблица пассажиров: " << endl;
        char* passport = new char[DB->passnum_size + 1]{};
        for (int i = 0; i < DB->sheet_size; i++) {
            if (strcmp(DB->passengers[i].passport, "\0") != 0) {
                extend_passport(DB->passengers[i].passport, passport, DB->passnum_size);
                cout << left << setw(2) << "+-" << setfill('-') << setw(29) << right << '<' << setfill(' ') << endl;
                cout << left << setw(2) << "|" << setw(16) << "Паспорт №" << passport << endl;
                cout << left << setw(2) << "|" << setw(16) << "Выдан " << DB->passengers[i].issuance << endl;
                cout << left << setw(2) << "|" << setw(16) << "Ф.И.О. " << DB->passengers[i].fio << endl;
                cout << left << setw(2) << "|" << setw(16) << "Дата рождения: " << DB->passengers[i].birth << endl;
            }
        }
        cout << left << setw(2) << "+-" << setfill('-') << setw(29) << right << '<' << setfill(' ') << endl;
        delete[] passport;
    }
    else {
        cout << "Таблица пассажиров пуста." << endl;
    }
    cout << "Возвращение в меню." << endl;
}

int menu_add_avr(database* const DB) {
    while (true) {
        cout << "Добавление. Введите номер рейса в формате \"AAA-NNN\":" << endl;
        string inp;
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(),'\n');
        getline(cin, inp);
        if (strcmp(inp.c_str(), "/") == 0) {
            cout << "Возвращение в меню." << endl;
            break;
        }
        if (is_avianum_correct(inp, DB->avianum_size)) {
            if (is_exists(DB->flights, (const string)inp)) {
                cout << "|\\/| Такой рейс уже существует. Попробуйте заново" << endl;
                cout << "|/\\| или введите \"/\" для выхода в меню:" << endl;
                cin.clear();
                cin.ignore(cin.rdbuf()->in_avail(),'\n');
                continue;
            }
            string longinp;
            flight* newflight = new flight;
            int places = 0;
            inp.erase(3, 1);
            strcpy_s(newflight->number, inp.c_str());
            cout << "Введите компанию рейса:" << endl;
            getline(cin, longinp);
            longinp.shrink_to_fit();
            newflight->company = longinp;
            cout << "Введите место отправления рейса:" << endl;
            getline(cin, longinp);
            longinp.shrink_to_fit();
            newflight->departure = longinp;
            cout << "Введите место прибытия рейса:" << endl;
            getline(cin, longinp);
            longinp.shrink_to_fit();
            newflight->arriving = longinp;
            cout << "Введите время отправления рейса:" << endl;
            getline(cin, longinp);
            while (!validate_dateNtime(longinp)) {
                cout << "[X] Время отправления введено неверно. Попробуйте заново:" << endl;
                cin.clear();
                cin.ignore(cin.rdbuf()->in_avail(), '\n');
                getline(cin, longinp);
            }
            longinp.shrink_to_fit();
            newflight->dep_time = longinp;
            cout << "Введите время прибытия рейса (DD.MM.YYYY HH:MM):" << endl;
            getline(cin, longinp);
            while (!validate_dateNtime(longinp)) {
                cout << "[X] Время прибытия введено неверно. Попробуйте заново:" << endl;
                cin.clear();
                cin.ignore(cin.rdbuf()->in_avail(), '\n');
                getline(cin, longinp);
            }
            longinp.shrink_to_fit();
            newflight->arv_time = longinp;
            if (is_copy(DB->flights, newflight)) {
                cout << "[X] Рейс является копией существующего." << endl;
                break;
            }
            cout << "Введите количество мест в самолёте:" << endl;
            while(input_int(places) || places < 1) {
                cout << "[X] Ошибка ввода. Попробуйте заново: ";
            }
            newflight->places = places;
            cout << "Введите количество свободных мест:" << endl;
            while(input_int(places) || places < 0 || places > newflight->places) {
                cout << "[X] Ошибка ввода. Попробуйте заново: ";
            }
            newflight->free = places;
            add_element(DB->flights, *newflight);
            delete newflight;
            cout << "Авиарейс добавлен." << endl;
            break;
        }
        else {
            cout << "|\\/| Номер введён неверно. Попробуйте заново" << endl;
            cout << "|/\\| или введите \"/\" для выхода в меню:" << endl;
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail(),'\n');
            continue;
        }
    }
    return 0;
}

int menu_del_avr(database* const DB) {
    if (DB->flights == nullptr) {
        cout << "Список авиарейсов пуст. Операция не выполнена." << endl;
        return 1;
    }
    while (true) {
        cout << "Удаление. Введите номер рейса:" << endl;
        string inp;
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(),'\n');
        getline(cin, inp);
        if (strcmp(inp.c_str(), "/") == 0) {
            cout << "Возвращение в меню." << endl;
            break;
        }
        if (is_avianum_correct(inp, DB->avianum_size)) {
            if (delete_element(DB->flights, inp.erase(3, 1).c_str()) == 2) {
                cout << "|\\/| Авиарейс не найден. Попробуйте заново" << endl;
                cout << "|/\\| или введите \"/\" для выхода в меню:" << endl;
                continue;
            }
            else {
                cout << "Авиарейс удалён." << endl;
                cout << "«Уважаемые пассажиры. Рейс №" << inp << " отмененён."
                    " За дополнительной информацией обращайтесь к представителю авиакомпании.»" << endl;
                del_tickets_byAvr(DB->tickets, inp.c_str());
                break;
            }
        }
    }
    return 0;
}

int menu_find_num_avr(database* const DB) {
    if (DB->flights == nullptr) {
        cout << "Список авиарейсов пуст. Операция не выполнена." << endl;
        return 1;
    }
    while (true) {
        cout << "Поиск рейса. Введите номер рейса:" << endl;
        string inp;
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(),'\n');
        getline(cin, inp);
        if (strcmp(inp.c_str(), "/") == 0) {
            cout << "Возвращение в меню." << endl;
            break;
        }
        if (is_avianum_correct(inp, DB->avianum_size)) {
            flight* found = nullptr;
            inp.erase(3, 1);
            found = find_element(DB->flights, inp.c_str());
            if (found == nullptr) {
                cout << "|\\/| Авиарейс не найден. Попробуйте заново" << endl;
                cout << "|/\\| или введите \"/\" для выхода в меню:" << endl;
                cin.clear();
                cin.ignore(cin.rdbuf()->in_avail(),'\n');
                continue;
            }
            else {
                cout << "Авиарейс найден. Информация о нём:" << endl;
                std::cout << "Рейс №" << found->number << std::endl;
                std::cout << "Компания: " << found->company << std::endl;
                std::cout << "Отправляется из: " << found->departure << std::endl;
                std::cout << "В: " << found->arriving << std::endl;
                std::cout << "Время отправления: " << found->dep_time << std::endl;
                std::cout << "Время прибытия: " << found->arv_time << std::endl;
                std::cout << "Всего " << found->places << " мест, из которых " << found->free << "свободно." << std::endl;
                break;
            }
        }
        else {
            cout << "|\\/| Номер введён неверно. Попробуйте заново" << endl;
            cout << "|/\\| или введите \"/\" для выхода в меню:" << endl;
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail(), '\n');
            continue;
        }
    }
    return 0;
}

int menu_find_dest_avr(database* const DB) {
    if (DB->flights == nullptr) {
        cout << "Список авиарейсов пуст. Операция не выполнена." << endl;
        return 1;
    }
    while (true) {
        cout << "Поиск рейсов. Введите пункт назначения:" << endl;
        string inp;
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(),'\n');
        getline(cin, inp);
        if (strcmp(inp.c_str(), "/") == 0) {
            cout << "Возвращение в меню." << endl;
            break;
        }
        found_flights* found = nullptr;
        find_elements_bytext(DB->flights, found, inp);
        if (found == nullptr) {
            cout << "|\\/| Авиарейс не найден. Попробуйте заново" << endl;
            cout << "|/\\| или введите \"/\" для выхода в меню:" << endl;
            cin.clear();
            cin.ignore(cin.rdbuf()->in_avail(),'\n');
            continue;
        }
        else {
            cout << "Авиарейс(ы) с указанными фрагментами названия аэропорта прибытия:" << endl;
            output_flights(found);
            clear_list(found);
            break;
        }
    }
    return 0;
}

void menu_show_avr(database* const DB) {
    if (DB->flights == nullptr) {
        cout << "Список авиарейсов пуст. Операция не выполнена." << endl;
    }
    else {
        cout << "Авиарейсы:" << endl;
        output_flights(DB->flights);
        cout << boolalpha << tree_accuracy(DB->flights) << endl;
    }
}


