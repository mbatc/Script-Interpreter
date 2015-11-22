#pragma once
#include "DataTypeDefinitions.h"

class CScriptVariable
{
public:
    CScriptVariable();
    CScriptVariable(unsigned int type, void* data, unsigned int scope, char* name);
    ~CScriptVariable();

    void* GetData();
    char* GetName();
    unsigned int GetType();
    unsigned int GetScope();
    unsigned int SetData(void* var);

    unsigned int OperatorAdd(CScriptVariable* add);
    unsigned int OperatorSubtract(CScriptVariable* sub);
    unsigned int OperatorMultiply(CScriptVariable* mul);
    unsigned int OperatorDivide(CScriptVariable* div);
    unsigned int OperatorAssign(CScriptVariable* sign);

	void PrintDataToConsole(bool c_out = false);
private:
    void* m_pData;
    unsigned int m_dataType;
    unsigned int m_scope;

    char* m_pName;
};
