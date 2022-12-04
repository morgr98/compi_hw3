#include "SymbolTable.hpp"

Table* SymbolTable::newScope() {
    /* Add the same offset for a new scope */
    this->offsets.push(this->offsets.top());
    /* New table which points to it's parent */
    /* TODO: is the parent always the one currently in the top of the stack? */
    Table *new_table = this->makeTable(this->tables.top());
    this->tables.push(new_table);
    return new_table;
}

void SymbolTable::closeScope() {
    this->offsets.pop();
    this->tables.pop();
}

Table* SymbolTable::makeTable(Table* parent) {
    Table *table = new Table(parent);
    return table;
}

void SymbolTable::insert(Table *table, const std::string& name, type_enum type, int offset) {
    TableEntry *new_entry = new TableEntry(name, type, offset);
    table->insert(new_entry);
    this->offsets.push(offset);
}

bool SymbolTable::isDec(const std::string& name) {
    bool found = false;
    Table* curr_table = this->tables.top();
    while (curr_table != nullptr) {
        for (auto & entry : curr_table->entry_list) {
            if (entry->name == name) {
                found = true;
                break;
            }
        }
        if (found)
            break;
        curr_table = curr_table->parent;
    }
    return found;
}

bool SymbolTable::isAlreadyDecInScope(const std::string& name) {
    Table* curr_table = this->tables.top();
    bool found = false;
    for (auto & entry : curr_table->entry_list) {
        if (entry->name == name) {
            found = true;
            break;
        }
    }
    return found;
}

void Table::insert(TableEntry *entry)
{
    this->entry_list.push_back(entry);
}


