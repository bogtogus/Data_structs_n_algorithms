// 862
// 4 - ������� �����������
// 2 - �������� ����������� � ������������ ������������
// 1 - ���������� ����������
// 2 - ������ ����������� ����������������
// 1 - ����� ������ ��������
// 0 - ����� ����� ������ � ����

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
    cout << boolalpha << compare_fragments("����������", "������") << endl;;
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
