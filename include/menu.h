#pragma once
#include <main.h>
#include <hash.h>
#include <tree.h>
#include <list.h>
#include <functionality.h>

int menu(passenger*& sheet, flight*& flights, ticket_trade*& tickets, int sheet_size);
int menu_pass(passenger*& sheet, flight*& flights, ticket_trade*& tickets, int size, const int passnum_size);
int menu_avia(passenger*& sheet, flight*& flights, ticket_trade*& tickets, int size, const int passnum_size);
int menu_reg_ticket(ticket_trade*& tickets, passenger*& sheet, flight*& flights, const int pass_size, const int sheet_size);
int menu_ref_ticket(ticket_trade*&, passenger*& sheet, flight*& flights, const int, const int);
int menu_load_data(passenger*& sheet, flight*& flights, ticket_trade*& tickets, int sheet_size, const int passnum_size);
int load_pass(std::ifstream& file, passenger*& sheet, int sheet_size, const int passnum_size);
int load_avia(std::ifstream& file, flight*& flights);
int load_tickets(std::ifstream& file, ticket_trade*& tickets, const int passnum_size);
void menu_help();

int input_int(int& num);
int menu_add_psg(passenger*& sheet, int size, const int passnum_size);
int menu_del_psg(passenger*& sheet, int size, const int passnum_size);
int menu_find_num_psg(passenger* sheet, int size, const int passnum_size);
int menu_find_fio_psg(passenger* sheet, int size, const int passnum_size);
void menu_show_psg(passenger* sheet, int size, const int passnum_size);
void menu_help_psg();

int menu_add_avr(flight*&, const int);
int menu_del_avr(flight*&, const int);
int menu_find_num_avr(flight*, const int);
int menu_find_dest_avr(flight*, const int);
void menu_show_avr(flight*, const int);
void menu_help_avr();
