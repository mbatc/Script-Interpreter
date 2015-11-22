#include "CScriptVariableList.h"
#include "MemoryHelper.h"

#include "main.h"

#include <iostream>

using namespace std;

CScriptVariableList::CScriptVariableList()
:
    m_pTempVars(0),
    m_pVariable(0),
    m_nTempVars(0),
    m_nVariables(0)
{}

CScriptVariableList::~CScriptVariableList()
{}

unsigned int CScriptVariableList::AddVariable(CScriptVariable* newVar)
{
    if(!newVar)
        return ERROR_UNDEFINED_ERROR;

    for(int i = 0; i < m_nVariables; i++)
    {
        if(!strcmp(newVar->GetName(), m_pVariable[i]->GetName()))
            return ERROR_REDEFINITION;
    }

    CScriptVariable** temp = new CScriptVariable*[m_nVariables+1];
    for(int i = 0; i < m_nVariables; i++)
        temp[i] = m_pVariable[i];

    temp[m_nVariables] = newVar;

    MEMORY::SafeDeleteArr(m_pVariable);
    m_pVariable = temp;
    m_nVariables++;

    return NO_ERROR;
}

void CScriptVariableList::CreateTempVariable(SCRIPT_VAR_TYPE type)
{
    int i = 0;
    float f = 0.0f;
    bool b = false;
    CScriptVariable* temp = 0;
    switch(type)
    {
    case INT:
        temp = new CScriptVariable(type, &i, 0, "TEMP_VAR");
        break;
    case FLOAT:
        temp = new CScriptVariable(type, &f, 0, "TEMP_VAR");
        break;
    case BOOL:
        temp = new CScriptVariable(type, &b, 0, "TEMP_VAR");
        break;
    }
    CScriptVariable** tempList = new CScriptVariable*[m_nTempVars + 1];

    for(int i = 0; i < m_nTempVars; i++)
    {
        tempList[i] = m_pTempVars[i];
    }
    tempList[m_nTempVars] = temp;
    MEMORY::SafeDeleteArr(m_pTempVars);

    m_pTempVars = tempList;
}

void CScriptVariableList::RemoveVariable(char* name)
{
    int removeIndex = -1;
    for(int i = 0; i < m_nVariables; i++)
    {
        if(!strcmp(m_pVariable[i]->GetName(), name))
        {
           removeIndex = i;
           break;
        }
    }

    CScriptVariable** tempList = new CScriptVariable*[m_nVariables - 1];
    for(int i = 0; i < m_nVariables; i++)
    {
        if(i < removeIndex)
        {
            tempList[i] = m_pVariable[i];
        }
        else if(i > removeIndex)
        {
            tempList[i - 1] = m_pVariable[i];
        }
    }
    MEMORY::SafeDeleteArr(m_pVariable);
    m_pVariable = tempList;
    m_nVariables--;
}

CScriptVariable* CScriptVariableList::GetVariable(char* name)
{
    int index = -1;
    int scope = -1;

	if (!name)
		return NULL;

    for(int i = 0; i < m_nVariables; i++)
    {
        if(!strcmp(m_pVariable[i]->GetName(), name))
        {
            index = i;
        }
    }
    if(index < 0)
        return NULL;


    return m_pVariable[index];
}

CScriptVariable* CScriptVariableList::GetTempVar(SCRIPT_VAR_TYPE type)
{
    CreateTempVariable(type);
    return m_pTempVars[m_nTempVars - 1];
}

void CScriptVariableList::Reset()
{
    MEMORY::SafeDeleteArr(m_pTempVars);
    MEMORY::SafeDeleteArr(m_pVariable);
    m_nTempVars = 0;
    m_nVariables = 0;
}


void CScriptVariableList::PrintVariableListToConsole(bool c_out)
{
    char msg[512] = {0};
    sprintf(msg, "Variable Count: %i\n", m_nVariables);
    debug.Log(msg, c_out);

    for(int i = 0; i < m_nVariables; i++)
    {
		m_pVariable[i]->PrintDataToConsole(c_out);
    }

    if(m_nTempVars <= 0)
        return;

	debug.Log("____________________________\n", c_out);
	debug.Log("TEMP VARIABLES\n\n", c_out);

    for(int i = 0; i < m_nTempVars; i++)
    {
        debug.Log("\t");
		m_pTempVars[i]->PrintDataToConsole(c_out);
    }
}

void CScriptVariableList::UpdateVarList(int scope)
{
    for(int i = 0; i < m_nVariables; i++)
    {
        if(m_pVariable[i]->GetScope() > scope)
        {
            RemoveVariable(m_pVariable[i]->GetName());
            i--;
        }
    }
}
