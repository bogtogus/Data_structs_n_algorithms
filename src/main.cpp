// 862
// 4 - Продажа авиабилетов
// 2 - Закрытое хеширование с квадратичным опробованием
// 1 - сортировка Включением
// 2 - список Циклический однонаправленный
// 1 - обход дерева Обратный
// 0 - поиск слова Боуера и Мура

#include <main.h>
#include <menu.h>
#include <hash.h>
#include <tree.h>
#include <list.h>
#include <functionality.h>

using namespace std;
//13

int main() {
    setlocale(LC_ALL, "1251");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cin.sync_with_stdio(false);
    srand(time(0));
    cout << boolalpha << compare_fragments("абоданныев", "данные") << endl;;
    const int sheet_size = 2000;
    
    passenger* sheet = new passenger[sheet_size]{};
    flight* flights = nullptr;
    ticket_trade* tickets = nullptr;

    menu(sheet, flights, tickets, sheet_size);
    
    delete[] sheet;
    clear_list(tickets);
    clear_flights(flights);

    return 0;
}
