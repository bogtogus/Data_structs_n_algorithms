// Продажа авиабилетов
// Закрытое хеширование с квадратичным опробованием
// сортировка Включением
// список Циклический однонаправленный
// обход дерева Обратный
// поиск слова Боуера и Мура

//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
//#ifdef _DEBUG
//#ifndef DBG_NEW
//#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
//#define newDBG_NEW
//#endif
//#endif

#include <main.h>
#include <menu.h>
#include <hash.h>
#include <tree.h>
#include <list.h>
#include <functionality.h>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cin.sync_with_stdio(false);
    srand(time(0));

    cout << boolalpha << compare_fragments("смабоданныевы", "данные") << endl;;
    
    database* const DB = new database();
    DB->passengers = new passenger[DB->sheet_size]{};
    DB->flights = nullptr;
    DB->tickets = nullptr;

    menu(DB);
    
    delete[]  DB->passengers;
    clear_list(DB->tickets);
    clear_flights(DB->flights);
    delete DB;

    //_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    //_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    //_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    //_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    //_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    //_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
    //_CrtDumpMemoryLeaks();
    return 0;
}
