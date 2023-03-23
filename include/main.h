#pragma once

#include <iostream>
#include <windows.h>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sqlite3.h>

struct database {
	struct passenger* passengers = nullptr;
	struct flight* flights = nullptr;
	struct ticket_trade* tickets = nullptr;
	const int passnum_size = 11;
	const int avianum_size = 7;
	const int sheet_size = 2000;
};
