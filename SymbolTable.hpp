#ifndef COMPI_HW3_SYMBOL_TABLE_HPP
#define COMPI_HW3_SYMBOL_TABLE_HPP

#include <iostream>
#include <vector>
#include "string"
#include <stack>
#include "Stypes.hpp"
#include "hw3_output.hpp"
#define NO_OFFSET 0xffffffff

class TableEntry{
public:
    const std::string name;
    type_enum type;
    int offest;
    bool isfunction;
    TableEntry(const std::string& name, type_enum type, int offest) : name(name), type(type), offest(offest){};
    
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
    /* Using vectors so we could use iterators (stacks don't have)*/
    std::stack<Table*> tables;
    std::stack<int> offsets;

    SymbolTable() = default;
    /* Creates a new scope and returns a pointer to the new table added */
    Table* newScope();
    /* Closes current scope */
    void closeScope();
    /* Maketable makes a table which points to it's parent */
    Table *makeTable(Table *parent);
    void insert(Table *table, const std::string& name, type_enum type, int offest);
    void addFunction(Table *table, const std::string& name, type_enum type, int offest);
    void push_t(Table& table);
    void push_o(int offest);
    Table pop_t();
    int pop_o();
    Table top_t();
    int top_o();

    bool isDec(const std::string& name, bool function);
    bool isAlreadyDecInScope(const std::string& name);

};


#endif