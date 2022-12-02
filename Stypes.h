//
// Created by Gilad on 02/12/2022.
//

#ifndef COMPI_HW3_STYPES_H
#define COMPI_HW3_STYPES_H

#define YYSTYPE Node*

enum type_enum {
    Int_t,
    Bool_t,
    Byte_t,
    String_t,
    Void_t,
};

class Node {

};

class Type : public Node {
    type_enum type;

    Type(type_enum type);
};

class Call : public Node {
    type_enum type;

    Call(type_enum type);
};

class Exp : public Node {
    type_enum type;

    Exp(type_enum type);
};

class ExpList : public Node {
    std::vecotr<Exp> expressions;

    ExpList(const std::vector<Exp>& expressions);
}

class FormalDecl : public Node {
    type_enum type;
    const string id;

    FormalDecl(type_enum type, const string& id);
};

class FormalsList: public Node {
    std::vector<FormalDecl> decls;

    FormalsList(const std::vector<FormalDecl>& decls);
};

class Formals : public Node {
    std::vector<FromalDecl> decls;
    Formals(const std::vector<FormalDecl>& decls);

};

class RetType : public Node {
    type_enum type;

    RetType(type_enum type);
};

bool checkBoolExp(Exp& exp);
bool checkBoolExp(Exp& exp1, Exp& exp2);




#endif //COMPI_HW3_STYPES_H
