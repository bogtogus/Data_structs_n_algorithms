#include <main.h>
#include <functionality.h>

void extend_passport(const char passport[], char*& dest, const int pass_size) {
    strncpy_s(dest, pass_size + 1, passport, 4);
    dest[4] = '-';
    for (int i = 5; i < pass_size; i++) {
        dest[i] = passport[i - 1];
    }
    dest[pass_size] = '\0';
}

void extend_flight(const char flight[], char*& dest, const int avia_size) {
    strncpy_s(dest, avia_size + 1, flight, 4);
    dest[3] = '-';
    for (int i = 4; i < avia_size; i++) {
        dest[i] = flight[i - 1];
    }
    dest[avia_size] = '\0';
}

bool is_number(const std::string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) { 
        it++;
    }
    return (!s.empty() && it == s.end());
}

bool compare_fragments(const std::string& line, const std::string& need) { // Боуэра Мура
    if (need.length() > line.length() || need.length() == 0) {
        return false;
    }
    int st = 0;
    int c2 = 0;
    int i = 0;
    int s1 = 0;
    int nlen = need.length();
    int* stopsymb = new int[nlen] {};
    for (int c1 = nlen - 2; c1 >= 0; c1--) { // построение таблицы с конца слова
        if (need[c1] == need[nlen - 1] && stopsymb[nlen - 1] == 0) { // если символ в конце слова есть и в другом его месте
            stopsymb[nlen - 1] = nlen - c1 - 1;
            stopsymb[c1] = nlen - c1 - 1;
            continue;
        }
        for (c2 = c1 + 1; c2 < nlen; c2++) { // если символ уже вычислялся
            if (need[c2] == need[c1]) {
                stopsymb[c1] = stopsymb[c2]; // то записываем число в самом правом вхождении
                break;
            }
        }
        if (c2 == nlen && stopsymb[c1] == 0) {
            stopsymb[c1] = nlen - c1 - 1;
        }
    }
    if (nlen == 1) {
        stopsymb[0] = 1;
    }
    //for (int y = 0; y < nlen; y++) {
    //    cout << stopsymb[y] << ' ';
    //} 
    //cout << endl << endl;
    while (st <= line.length() - nlen) {
        i = 0;
        //cout << st << endl;
        for (i = nlen - 1; i >= 0; i--) { // сравнение с конца слова
            if (line[i + st] != need[i]) { // если не совпало
                for (s1 = 0; s1 < nlen; s1++) { // ищется несовпавший в предложении символ в таблице
                    if (line[i + st] == need[s1]) {
                        break;
                    }
                }
                if (s1 < nlen) { // если такой символ есть в таблице
                    st += stopsymb[s1];
                }
                else {
                    st += nlen;
                }
                break;
            }
        }
        if (i == -1) {
            delete[] stopsymb;
            return true;
        }
    }
    delete[] stopsymb;
    return false;
}

bool is_avianum_correct(const std::string number, const int num_size) { // AAA-NNN
    if (number.length() > num_size) {
        return false;
    }
    std::string mask = "AAA-NNN";
    for (int i = 0; i < num_size; i++) {
        if (mask[i] == 'A' && !isalpha(number[i])) {
            return false;
        }
        else if (mask[i] == '-' && number[i] != '-') {
            return false;
        }
        else if (mask[i] == 'N' && !isdigit(number[i])) {
            return false;
        }
    }
    
    return true;
}

bool validate_date(const std::string date, bool birth) {
    std::string mask = "DD.MM.YYYY";
    
    if (date.length() > mask.length()) {
        return false;
    }
    for (int i = 0; i < mask.length(); i++) {
        if (mask[i] == 'D' || mask[i] == 'M' || mask[i] == 'Y') {
            if (!isdigit((unsigned char)date[i])) {
                return false;
            }
        }
        else {
            if (date[i] != '.') {
                return false;
            }
        }
    }
    int* months = new int[12] {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    std::string::size_type ind = 0;
    int day = stoi((date).substr(ind, ind + 2));
    ind = date.find('.', ind + 1) + 1;
    int month = stoi((date).substr(ind, ind + 2));
    ind = date.find('.', ind + 1) + 1;
    int year = stoi((date).substr(ind, ind + 4));
    if (month < 1 || month > 12) {
        delete[] months;
        return false;
    }
    else if (!birth && year < 2000 || year > 2023) {
        delete[] months;
        return false;
    }
    else if (year % 400 != 0 && 
            year % 4 == 0 && 
            month == 2 && 
            (day < 1 || day > months[month - 1] + 1)) {
        delete[] months;
        return false;
    }
    else if (day < 1 || day > months[month - 1]) {
        delete[] months;
        return false;
    }
    delete[] months;
    
    return true;
}

bool validate_dateNtime(const std::string dateNtime) {
    std::string mask = "DD.MM.YYYY HH:MM";
    if (dateNtime.length() > mask.length()) {
        return false;
    }
    for (int i = 0; i < mask.length(); i++) {
        if (mask[i] == 'D' || mask[i] == 'M' || 
                mask[i] == 'Y' || mask[i] == 'H') {
            if (!isdigit((unsigned char)dateNtime[i])) {
                return false;
            }
        }
        else if (dateNtime[i] != mask[i]) {
            return false;
        }
    }
    int* months = new int[12] {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    std::string::size_type ind = 0;
    int day = stoi((dateNtime).substr(ind, ind + 2));
    ind = dateNtime.find('.', ind + 1) + 1;
    int month = stoi((dateNtime).substr(ind, ind + 2));
    ind = dateNtime.find('.', ind + 1) + 1;
    int year = stoi((dateNtime).substr(ind, ind + 4));
    if (month < 1 || month > 12) {
        delete[] months;
        return false;
    }
    else if (year < 2000 || year > 2023) {
        delete[] months;
        return false;
    }
    else if (year % 400 != 0 &&
        year % 4 == 0 &&
        month == 2 &&
        (day < 1 || day > months[month - 1] + 1)) {
        delete[] months;
        return false;
    }
    else if (day < 1 || day > months[month - 1]) {
        delete[] months;
        return false;
    }
    delete[] months;
    ind = dateNtime.find(' ', ind + 1) + 1;
    int hour = stoi((dateNtime).substr(ind, ind + 2));
    ind = dateNtime.find(' ', ind + 1) + 1;
    int min = stoi((dateNtime).substr(ind, ind + 2));
    if (hour < 0 || hour > 23) {
        return false;
    }
    else if (min < 0 || min > 59) {
        return false;
    }
    
    return true;
}

bool validate_name(const std::string name, bool fio) {
    std::string nval = "1234567890!@#№\"\';$%^:&?*(){}[]|\\/_+=`~";
    if (name.find_first_of(nval) != std::string::npos) {
        return false;
    }
    else if (fio && name.find('.') == std::string::npos) {
        return false;
    }
    return true;
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
