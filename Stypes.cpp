//
// Created by Gilad on 02/12/2022.
//

#include "Stypes.h"

bool checkBoolExp(Exp& exp){
    return exp.type==Bool_t;
}
bool checkBoolExp(Exp& exp1, Exp& exp2)
{
    return exp.type==Bool_t && exp2.type == Bool_t;
}