//
// Created by Gilad on 02/12/2022.
//

#ifndef COMPI_HW3_STYPES_H
#define COMPI_HW3_STYPES_H

#include <iostream>
#include <vector>
#include "string"
#define YYSTYPE Node*

enum type_enum {
    Int_t,
    Bool_t,
    Byte_t,
    String_t,
    Void_t,
    NONE_t
};

class Node {
public:
     ~Node() = default;
};

class Type_c : public Node {
public:
    type_enum type;

    Type_c(type_enum type);
};

class Call_c : public Node {
public:
    type_enum type;

    Call_c(type_enum type);
};

class Exp_c : public Node {
public:
    type_enum type;
    Exp_c(type_enum type) : type(type){}
    
};

class ExpList_c : public Node {
public:
    std::vector<Exp_c> expressions;

    ExpList_c(const std::vector<Exp_c>& expressions);
};

class FormalDecl_c : public Node {
public:
    type_enum type;
    const std::string id;

    FormalDecl_c(type_enum type, const std::string& id);
};

class FormalsList_c: public Node {
public:
    std::vector<FormalDecl_c> decls;

    FormalsList_c(const std::vector<FormalDecl_c>& decls);
};

class Formals_c : public Node {
public:
    std::vector<FormalDecl_c> decls;
    Formals_c(const std::vector<FormalDecl_c>& decls);

};

class RetType_c : public Node {
public:
    type_enum type;

    RetType_c(type_enum type);
};

bool checkBoolExp(Exp_c& exp);
bool checkBoolExp(Exp_c& exp1, Exp_c& exp2);




#endif //COMPI_HW3_STYPES_H
