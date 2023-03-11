#pragma once
#include <main.h>
#include <functionality.h>

struct ticket_trade {
    char passport[11]{}; // NNNNNNNNNN (NNNN-NNNNNN)
    char flight_number[7]{}; // AAANNN (AAA-NNN)
    char ticket[10]{}; // NNNNNNNNN
    ticket_trade* next = nullptr;
};

void clear_list(ticket_trade*&);
int pop_ticket(ticket_trade*& head, const std::string passport, const std::string flight);
void push_ticket(ticket_trade*& head, const std::string passport, const std::string flight);
void push_ticket_ff(ticket_trade*& head, const std::string, const std::string passport, const std::string flight);
unsigned int decode_ticket(const char tnum[]);
char* encode_ticket(const unsigned int number);
bool is_exists(ticket_trade*& head, const std::string);
void show_list(ticket_trade* head, const int, const int);
bool is_copy(ticket_trade*& head, const std::string, std::string);
bool is_list_empty(ticket_trade*& head);
void sort(ticket_trade*& head);
void del_tickets_byAvr(ticket_trade*& head, const char* number);
void del_tickets_byPass(ticket_trade*& head, const char* passport);
