#include "MemoryHelper.h"
#include "OperatorFunctions.h"
#include "CScriptVariable.h"

#include "main.h"

#include <iostream>
#include <stdio.h>

using namespace std;


CScriptVariable::CScriptVariable()
:
    m_pData(0),
    m_pName(0)
{}

CScriptVariable::CScriptVariable(unsigned int type, void* data, unsigned int scope, char* name)
:
    m_pData(0),
    m_dataType (type),
    m_scope(scope)
{
    MEMORY::SCRIPT::SafeAlloc(m_pData,type);
    if(data)
        SCRIPT::OPERATOR::assignVar(m_pData,type, data, m_dataType);

    m_pName = new char[strlen(name) + 1];
    strcpy(m_pName, name);
}

CScriptVariable::~CScriptVariable()
{
    MEMORY::SafeDelete((int*)m_pData);
    MEMORY::SafeDeleteArr(m_pName);
}

void* CScriptVariable::GetData()
{
    return m_pData;
}

char* CScriptVariable::GetName()
{
    return m_pName;
}

unsigned int CScriptVariable::GetType()
{
    return m_dataType;
}

unsigned int CScriptVariable::GetScope()
{
    return m_scope;
}

unsigned int CScriptVariable::SetData(void* var)
{
    switch(m_dataType)
    {
    case INT:
        *(int*)m_pData = *(int*)var;
         break;
    case BOOL:
         *(bool*)m_pData = *(bool*)var;
         break;
    case FLOAT:
        *(float*)m_pData = *(float*)var;
         break;
    case STR:
        *(String*)m_pData = *(String*)var;
         break;
    default:
        return ERROR_UNDEFINED_DATA_TYPE;
    }
    return NO_ERROR;
}

unsigned int CScriptVariable::OperatorAdd(CScriptVariable* add)
{
    if(!add)
        return ERROR_INVALID_VALUE;
    CScriptVariable temp(m_dataType, m_pData, -1, "temp");
    return SCRIPT::OPERATOR::add(m_pData, m_dataType,
                                 temp.GetData(), temp.GetType(),
                                 add->GetData(), add->GetType());
}
unsigned int CScriptVariable::OperatorSubtract(CScriptVariable* sub)
{
    if(!sub)
        return ERROR_INVALID_VALUE;
    CScriptVariable temp(m_dataType, m_pData, -1, "temp");
    return SCRIPT::OPERATOR::subtract(m_pData, m_dataType,
                                      temp.GetData(), temp.GetType(),
                                      sub->GetData(), sub->GetType());
}
unsigned int CScriptVariable::OperatorMultiply(CScriptVariable* mult)
{
    if(!mult)
        return ERROR_INVALID_VALUE;
    CScriptVariable temp(m_dataType, m_pData, -1, "temp");
    return SCRIPT::OPERATOR::multiply(m_pData, m_dataType,
                                      temp.GetData(), temp.GetType(),
                                      mult->GetData(), mult->GetType());
}
unsigned int CScriptVariable::OperatorDivide(CScriptVariable* div)
{
    if(!div)
        return ERROR_INVALID_VALUE;
    CScriptVariable temp(m_dataType, m_pData, -1, "temp");
    return SCRIPT::OPERATOR::divide(m_pData, m_dataType,
                                    temp.GetData(), temp.GetType(),
                                    div->GetData(), div->GetType());
}

unsigned int CScriptVariable::OperatorAssign(CScriptVariable* sign)
{
    if(!sign)
        return ERROR_INVALID_VALUE;
    return SCRIPT::OPERATOR::assignVar(m_pData, m_dataType,
                                       sign->GetData(), sign->GetType());
}

void CScriptVariable::PrintDataToConsole(bool c_out)
{
    bool undefined = false;
    if(m_pData == 0)
        undefined = true;

	char* msg = new char[512];

    switch(m_dataType)
    {
    case INT:
        if(undefined)
            sprintf(msg, "0x%x\t: %s\t: NOT SET\t: INT\n", (unsigned int)GetData(), GetName());
        else
            sprintf(msg, "0x%x\t: %s\t: %i\t: INT\n", (unsigned int)GetData(), GetName(), *(int*)GetData());
        break;
    case FLOAT:
        if(undefined)
            sprintf(msg, "0x%x\t: %s\t: NOT SET\t: FLOAT\n", (unsigned int)GetData(), GetName());
        else
            sprintf(msg, "0x%x\t: %s\t: %.2f\t: FLOAT\n", (unsigned int)GetData(), GetName(), *(float*)GetData());
        break;
    case BOOL:
        if(undefined)
            sprintf(msg, "0x%x\t: %s\t: NOT SET\t: BOOL\n", (unsigned int)GetData(), GetName());
        else
            sprintf(msg, "0x%x\t: %s\t: %s\t: BOOL\n", (unsigned int)GetData(), GetName(), *(bool*)GetData() ? "true" : "false");
        break;
    case STR:
        if(undefined)
            sprintf(msg, "0x%x\t: %s\t: NOT_SET\t: STRING\n", (unsigned int)GetData(), GetName());
		else
		{
			MEMORY::SafeDeleteArr(msg);
			msg = new char[512 + (*(String*)GetData()).GetStringLen() + 1];
			sprintf(msg, "0x%x\t: %s\t: %s\t: STRING\n", (unsigned int)GetData(), GetName(), (*(String*)GetData()).GetString());
		}
    }
    debug.Log(msg, c_out);

	MEMORY::SafeDeleteArr(msg);
}
