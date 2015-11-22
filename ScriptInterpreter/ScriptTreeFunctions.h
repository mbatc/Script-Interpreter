#pragma once

#include "CScriptVariable.h"
#include "ErrorDefinitions.h"

#include <iostream>

#define _FUNC_EQUALS 0
#define _FUNC_LESSTHAN 1
#define _FUNC_MORETHAN 2
#define _FUNC_MORETHAN_EQUALS 3
#define _FUNC_LESSTHAN_EQUALS 4

using namespace std;

namespace S_FUNC
{
    unsigned int ADD(int& scope, CScriptVariable** data);
    unsigned int SUB(int& scope, CScriptVariable** data);
    unsigned int MUL(int& scope, CScriptVariable** data);
    unsigned int DIV(int& scope, CScriptVariable** data);
    unsigned int ASSIGN(int& scope, CScriptVariable** data);
    unsigned int LESSTHAN(int& scope, CScriptVariable** data);
    unsigned int MORETHAN(int& scope, CScriptVariable** data);
    unsigned int MORETHAN_EQUALS(int& scope, CScriptVariable** data);
    unsigned int LESSTHAN_EQUALS(int& scope, CScriptVariable** data);
    unsigned int EQUALS(int& scope, CScriptVariable** data);

    unsigned int IF(int& scope, CScriptVariable** data);

    unsigned int OUTPUT(int& scope, CScriptVariable** data);

    namespace ENGINE
    {
        unsigned int GETCOMPONENT(int& scope, CScriptVariable** data);
        unsigned int SAVETOFILE(int& scope, CScriptVariable** data);
        unsigned int READFROMFILE(int& scope, CScriptVariable** data);
        unsigned int GETSCRIPTVAR(int& scope, CScriptVariable** data);
    }

    unsigned int FOR(int& scope, CScriptVariable** data);
    unsigned int FOR_END(int& scope, CScriptVariable** data);
    unsigned int INITIALIZE_VAR(int& scope, CScriptVariable** data);
}
