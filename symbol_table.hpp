#ifndef COMPI_HW3_SYMBOL_TABLE_HPP
#define COMPI_HW3_SYMBOL_TABLE_HPP

#include <iostream>
#include <vector>
#include "string"
#include "Stypes.h"
#include "stack"

class table_entry{
    private:
    std::string name;
    type_enum type;
    int offest;

    public:
    table_entry(std::string name, type_enum type, int offest) :
    name(name), type(type), offest(offest){};
    
};

class table{
    public:
    std::vector<table_entry> table_list;
    table();
    void insert(table_entry entry);
    bool contains(std::string name);
};

class symbol_table{

    std::stack<table> tables;
    std::stack<int> offsets;

    symbol_table();
    table Maketable(table parrent);
    void insert(table table, std::string, type_enum type, int offest);
    void push_t(table table);
    void push_o(int offest);
    table pop_t();
    int pop_o();
    table top_t();
    int top_o();

};


#endif