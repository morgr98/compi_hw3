//
// Created by Gilad on 02/12/2022.
//

#ifndef COMPI_HW3_STYPES_H
#define COMPI_HW3_STYPES_H

#include <iostream>
#include <vector>
#include "string"
#define NO_OFFSET 0xffffffff
#define YYSTYPE Node*


enum type_enum {
    Int_t,
    Bool_t,
    Byte_t,
    String_t,
    Void_t,
    None_t
};

class Node {
public:
     virtual ~Node() {};
};

class Type_c : public Node {
public:
    type_enum type;

    Type_c(type_enum type) : type(type) {};
};

class RetType_c : public Node {
public:
    type_enum type;

    RetType_c(type_enum type) : type(type) {};
};

class Call_c : public Node {
public:
    type_enum type;

    Call_c(type_enum type1) : type(type1) {};
};

class Exp_c : public Node {
public:
    type_enum type;
    Exp_c(type_enum type) : type(type){}
    
};

class ExpList_c : public Node {
public:
    std::vector<Exp_c> expressions;

    ExpList_c(const std::vector<Exp_c>& expressions) : expressions(expressions) {};
};

class FormalDecl_c : public Node {
public:
    type_enum type;
    const std::string name;

    FormalDecl_c(type_enum type, const std::string& name) : type(type), name(name) {};
};

class FuncDecl_c : public Node{
    public:
    type_enum type;
    std::string name;
    std::vector<FormalDecl_c*> decls;
    FuncDecl_c(type_enum type , const std::vector<FormalDecl_c*>& decls, std::string name) :
     type(type), decls(decls), name(name){};
};



class FormalsList_c: public Node {
public:
    std::vector<FormalDecl_c*> decls;

    FormalsList_c(const std::vector<FormalDecl_c*>& decls) : decls(decls) {};
};

class Formals_c : public Node {
public:
    std::vector<FormalDecl_c*> decls;
    Formals_c(){};
    Formals_c(const std::vector<FormalDecl_c*>& decls) : decls(decls) {};
};



class ID_c : public Node {
public:
    const std::string name;
    type_enum type = None_t;
    ID_c(const std::string name) : name(name){};
};

class Num_c : public Node {
public:
    const std::string num_str;
    type_enum type = None_t;
    Num_c(const std::string num_str) : num_str(num_str){};
};

bool checkBoolExp(Exp_c& exp);
bool checkBoolExp(Exp_c& exp1, Exp_c& exp2);
bool checkTypeExp(Type_c& type, Exp_c& exp);
bool checkTypeExpId(ID_c& id, Exp_c& exp);
bool isDec(ID_c *id);
std::string typeToString(type_enum type);
type_enum checkNumType(Exp_c& exp1, Exp_c& exp2);
//bool check



#endif //COMPI_HW3_STYPES_H
