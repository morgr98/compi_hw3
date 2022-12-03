//
// Created by Gilad on 02/12/2022.
//

#include "Stypes.h"

bool checkBoolExp(Exp_c& exp){
    return exp.type==Bool_t;
}
bool checkBoolExp(Exp_c& exp1, Exp_c& exp2)
{
    return exp1.type==Bool_t && exp2.type == Bool_t;
}

