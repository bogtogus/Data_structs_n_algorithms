#pragma once
#include <main.h>
#include <hash.h>
#include <tree.h>
#include <list.h>
#include <functionality.h>


int menu(database* const);
int menu_pass(database* const);
int menu_avia(database* const);
int menu_reg_ticket(database* const);
int menu_ref_ticket(database* const);
void menu_show_tickets(const database* const);
int menu_load_data(database* const);
int load_pass(std::ifstream& file, database* const);
int load_avia(std::ifstream& file, database* const);
int load_tickets(std::ifstream& file, database* const);
void menu_help();

int input_int(int& num);
int menu_add_psg(database* const);
int menu_del_psg(database* const);
int menu_find_num_psg(database* const);
int menu_find_fio_psg(database* const);
void menu_show_psg(database* const);
void menu_help_psg();

int menu_add_avr(database* const);
int menu_del_avr(database* const);
int menu_find_num_avr(database* const);
int menu_find_dest_avr(database* const);
void menu_show_avr(database* const);
void menu_help_avr();
