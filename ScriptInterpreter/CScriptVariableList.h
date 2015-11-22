#pragma once

#include "CScriptVariable.h"

class CScriptVariableList
{
public:
    CScriptVariableList();
    ~CScriptVariableList();

    void UpdateVarList(int scope);

    CScriptVariable* GetVariable(char* name);
    CScriptVariable* GetTempVar(SCRIPT_VAR_TYPE type);
    unsigned int AddVariable(CScriptVariable* newVar);
    unsigned int AddVariable(SCRIPT_VAR_TYPE type, void* data, unsigned int scope, char* name);
    void RemoveVariable(char* name);

    void PrintVariableListToConsole(bool c_out = false);

    void Reset();
private:
    void CreateTempVariable(SCRIPT_VAR_TYPE type);

    CScriptVariable** m_pVariable;
    CScriptVariable** m_pTempVars;
    int m_nVariables;
    int m_nTempVars;

    int m_currentScope;
};
