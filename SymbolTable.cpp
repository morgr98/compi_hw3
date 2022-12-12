#include "SymbolTable.hpp"

SymbolTable* SymbolTable::getSymTable() {
    static SymbolTable sym_table;
    return &sym_table;
}

Table* SymbolTable::makeGlob() {
    this->offsets.push(0);
    Table *new_table = this->makeTable(nullptr, false);
    this->tables.push(new_table);
    /* Add print and printi functions */
    this->insert(this->tables.top(), "print", Void_t, NO_OFFSET, true);//chane to void type
    this->tables.top()->entry_list.back()->argtypes.push_back("STRING");
    this->insert(this->tables.top(), "printi", Void_t, NO_OFFSET, true);
    this->tables.top()->entry_list.back()->argtypes.push_back("INT");
    return new_table;
}

Table* SymbolTable::newScope(bool iswhile) {
    /* Add the same offset for a new scope */
    this->offsets.push(this->offsets.top());
    /* New table which points to it's parent */
    /* TODO: is the parent always the one currently in the top of the stack? */
    Table *new_table = this->makeTable(this->tables.top(), iswhile);
    this->tables.push(new_table);
    return new_table;
}

void SymbolTable::closeScope() {
    output::endScope();
    Table* table_out = this->tables.top();
    for (auto & entry : table_out->entry_list)
    {
        //std::cout <<"Entry is: " << entry->name << " offset is: " << entry->offset << endl;
        if(!entry->isfunction){
            output::printID(entry->name, entry->offset, typeToString(entry->type));
        }
        else{
            output::printID(entry->name, 0, output::makeFunctionType(typeToString(entry->type),  entry->argtypes));
        }
    }
    this->offsets.pop();
    this->tables.pop();
}


Table* SymbolTable::makeTable(Table* parent, bool iswhile) {
    Table *table = new Table(parent, iswhile);
    return table;
}

void SymbolTable::insert(Table *table, const std::string& name, type_enum type, int offset, bool isfunc) {
    //If symbol at the top is a funciton, then offset should be 0.
    //TODO: make sure is ok
    if (!isfunc && offset > 0 && this->isFirstInCurScope(table)) {
        offset--;
        }
    //std::cout << "Inserting: " << name << " type: " << type << " offset: " << offset << " is func:" << isfunc <<endl;
    TableEntry *new_entry = new TableEntry(name, type, offset, isfunc);
    table->insert(new_entry);
    this->offsets.push(offset);
}

bool SymbolTable::isFirstInCurScope(Table* table) {
    if (table->entry_list.empty() && table->parent->entry_list.back() && table->parent->entry_list.back()->isfunction == true)
        return true;
    return false;
}

void SymbolTable::addFunction(Table *table, const std::string& name, type_enum type, int offset)
{
    TableEntry *new_entry = new TableEntry(name, type, offset, true);
    table->parent->insert(new_entry);
}

void SymbolTable::addFunctionParams(const std::vector<FormalDecl_c*>& decls) {
    int offset = -1;
    // while entering function params, the top of the parent table is the symbol of the funciton itself
    TableEntry *function_sym = this->tables.top()->parent->entry_list.back();
    for (auto& dec : decls) {
        this->insert(this->tables.top(), dec->name, dec->type, offset);
        offset--;
        function_sym->argtypes.push_back(typeToString(dec->type));
    }
}

bool SymbolTable::checkFunctionParams(ExpList_c& exp_list, const std::string& name)
{
    Table* curr_table = this->tables.top();
    TableEntry* table_entry;
    while (curr_table != nullptr) {
        for (auto & entry : curr_table->entry_list) {
            if (entry->name == name) {
                table_entry = entry;
                break;
            }
        }
        curr_table = curr_table->parent;
    }
    if(table_entry->argtypes.size() != exp_list.expressions.size())
    {
        errorPrototypeMismatch(yylineno, name, table_entry->argtypes);
        exit(1);
    }
    int i = 0;
    for(auto argtype : table_entry->argtypes)
    {
        if(typeToString(exp_list.expressions[i]->type).compare(argtype))
        {
            errorPrototypeMismatch(yylineno, name, table_entry->argtypes);
            exit(1);
        }
    }

}

bool SymbolTable::checkFunctionParams(const std::string& name)
{
    Table* curr_table = this->tables.top();
    TableEntry* table_entry;
    while (curr_table != nullptr) {
        for (auto & entry : curr_table->entry_list) {
            if (entry->name == name) {
                table_entry = entry;
                break;
            }
        }
        curr_table = curr_table->parent;
    }
    if(table_entry->argtypes.size() !=0)
    {
        errorPrototypeMismatch(yylineno, name, table_entry->argtypes);
        exit(1);
    }
}



bool SymbolTable::isDec(const std::string& name, bool function) {
    bool found = false;
    Table* curr_table = this->tables.top();
    while (curr_table != nullptr) {
        for (auto & entry : curr_table->entry_list) {
            //cout << "comparing " << entry->name << " to " << name << endl;
            if (entry->name == name) {
                if(function == entry->isfunction)
                {
                    found = true;
                }
            else{
                found = false;
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

bool SymbolTable::inScopeWhile(Table *table)
{
    Table* curr_table = table;
    bool found = false;
    while (curr_table != nullptr) {
        if(curr_table->iswhile)
        {
            return true;
        }
        curr_table = curr_table->parent;
    }
    return false;
}

bool SymbolTable::checkSamefunctionReturnType(type_enum type)
{
    cout<<"here";
    if(this->tables.top()->parent->entry_list.back()->type == type)
        return true;
    return false;
}

type_enum SymbolTable::getTypeByName(const std::string& name)
{
    Table* curr_table = this->tables.top();
    while (curr_table != nullptr) {
        for (auto & entry : curr_table->entry_list) {
            //cout << "comparing " << entry->name << " to " << name << endl;
            if (entry->name == name) {
                return entry->type;
            }
        }
        curr_table = curr_table->parent;
    }
    return None_t;
}

void Table::insert(TableEntry *entry)
{
    this->entry_list.push_back(entry);
}




