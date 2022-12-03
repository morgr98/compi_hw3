#ifndef COMPI_HW3_SYMBOL_TABLE_HPP
#define COMPI_HW3_SYMBOL_TABLE_HPP

#include <iostream>
#include <vector>
#include "string"
#include "Stypes.h"
#include "stack"

class TableEntry{
public:
    std::string name;
    type_enum type;
    int offest;

    TableEntry(std::string& name, type_enum type, int offest) : name(name), type(type), offest(offest){};
    
};

class Table{
public:
    std::vector<TableEntry*> entry_list;
    Table* parent;

    Table(Table* parent) : parent(parent) {};
    void insert(TableEntry *entry);
    bool contains(std::string name);
};

class SymbolTable {
public:
    std::stack<Table*> tables;
    std::stack<int> offsets;

    SymbolTable();
    /* Maketable makes a table which points to it's parent */
    Table makeTable(Table *parent);
    void insert(Table *table, std::string& name, type_enum type, int offest);
    void push_t(Table& table);
    void push_o(int offest);
    Table pop_t();
    int pop_o();
    Table top_t();
    int top_o();

};


#endif