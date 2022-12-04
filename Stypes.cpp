//
// Created by Gilad on 02/12/2022.
//

#include "Stypes.hpp"

bool checkBoolExp(Exp_c& exp) {
    return exp.type==Bool_t;
}
bool checkBoolExp(Exp_c& exp1, Exp_c& exp2) {
    return exp1.type==Bool_t && exp2.type == Bool_t;
}
bool checkTypeExp(Type_c& type, Exp_c& exp) {
    return type.type==exp.type;
}

bool checkTypeExpId(ID_c& id, Exp_c& exp) {
    return id.type==exp.type;
}




