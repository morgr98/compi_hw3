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
    output::endScope();
    Table* table_out = this->tables.top();
    for (std::vector<TableEntry*>::iterator it = table_out->entry_list.begin() ; it != table_out->entry_list.end(); ++it)
    {
        if(!(*it)->isfunction){
            output::printID((*it)->name, (*it)->offest, typeToString((*it)->type));
        }
        else{
            
        }
    }
    this->offsets.pop();
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

void SymbolTable::addFunction(Table *table, const std::string& name, type_enum type, int offset)
{
    TableEntry *new_entry = new TableEntry(name, type, offset);
    table->parent->insert(new_entry);
}

bool SymbolTable::isDec(const std::string& name, bool function) {
    bool found = false;
    Table* curr_table = this->tables.top();
    while (curr_table != nullptr) {
        for (auto & entry : curr_table->entry_list) {
            if (entry->name == name) {
                if(function && !entry->isfunction)
                {
                    found = false;
                }
            else{
                found = true;
            }
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




