#include <main.h>
#include <functionality.h>

char* extend_passport(const char passport[], const int pass_size) {
    char* ext = new char[pass_size + 1]{};
    strncpy(ext, passport, 4);
    ext[4] = '-';
    for (int i = 5; i < pass_size; i++) {
        ext[i] = passport[i - 1];
    }
    return ext;
}

char* extend_flight(const char flight[], const int avia_size) {
    char* ext = new char[avia_size + 1]{};
    strncpy(ext, flight, 4);
    ext[3] = '-';
    for (int i = 4; i < avia_size; i++) {
        ext[i] = flight[i - 1];
    }
    return ext;
}

bool is_number(const std::string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) { 
        ++it;
    }
    return !s.empty() && it == s.end();
}
