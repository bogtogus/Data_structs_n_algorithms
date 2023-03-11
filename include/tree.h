#pragma once

struct flight {
    char number[7]{}; // AAANNN (AAA-NNN)
    std::string company;
    std::string departure;
    std::string arriving;
    std::string dep_time;
    std::string arv_time;
    int places = 0;
    int free = 0;
    int height = 1;
    flight* prev = nullptr;
    flight* left = nullptr;
    flight* right = nullptr;
};

struct found_flights {
    flight* fl = nullptr;
    found_flights* next = nullptr;
};

int add_element(flight*& root, const flight& data);
int delete_element(flight*& root, const int number);
bool is_exists(const flight* root, const  std::string number);
void output_flights(const flight* const);
void output_flights(found_flights*);
void output_tree_height(flight *subroot, long int n, const int direction, bool changed=false);
flight* find_element(flight*, const int);
bool find_elements_bytext(flight* root, found_flights*&, const  std::string text);
flight* find_maxleft(flight*);
flight* find_minright(flight*);
void clear_flights(flight*&);
bool tree_accuracy(flight*);
void SmallRightRotate(flight*&);
void SmallLeftRotate(flight*&);
void Balance(flight*&);
void FullBalance(flight*&);
int delta_height(const flight* const Left, const flight* const Right);
int height_recalculation(flight*&);
bool is_tree_empty(const flight* const);
bool is_balanced(const flight*);
flight* to_root(flight*);
bool is_num_correct(const std::string, const int);
bool compare_fragments(const std::string&, const std::string&);
void push_back(found_flights *&, flight*&);
void copy_element(const flight&, flight*&);
