#include "symbol_table.hpp"


Table SymbolTable::makeTable(Table* parent) {
    Table table = Table(parent);
    return table;
}

void SymbolTable::insert(Table *table, std::string& name, type_enum type, int offset) {
    TableEntry *new_entry = new TableEntry(name, type, offset);
    table->insert(new_entry);
}



void Table::insert(TableEntry *entry)
{
    this->entry_list.push_back(entry);
}