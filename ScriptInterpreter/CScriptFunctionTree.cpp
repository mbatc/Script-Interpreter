#include "CScriptFunctionTree.h"
#include "MemoryHelper.h"
#include "ScriptTreeFunctions.h"
#include "CInterpreter.h"

#include "main.h"

#include <iostream>
#include <string.h>

using namespace std;

CScriptFunctionTree::CScriptFunctionTree()
:
    m_nSteps(0),
    m_pSteps(0)
{}

CScriptFunctionTree::~CScriptFunctionTree()
{}

void CScriptFunctionTree::AddScriptStep(ScriptStep step)
{
    CScriptVariable** temp = step.funcData;
    step.funcData = new CScriptVariable*[step.nVars];
    for(int i = 0; i < step.nVars; i++)
    {
        step.funcData[i] = temp[i];
    }
    MEMORY::AddToList(m_pSteps, step, m_nSteps);
}

void CScriptFunctionTree::Reset()
{
	for (int i = 0; i < m_nSteps; i++)
	{
		m_pSteps[i].Cleanup();
	}
	MEMORY::SafeDeleteArr(m_pSteps);
    m_nSteps = 0;
}

unsigned int CScriptFunctionTree::runScript()
{
    char msg[512] = {0};
    bool skipScope = false;
    bool inLoop = false;
    int loopScope = -1; 
    int tempPos = -2;

    for(int i = 0; i < m_nSteps; i++)
    {
        //*****************************************
        //DOING CHECKS FOR SCOPE SKIPPING AND LOOPS

        if(m_currentScope >= m_pSteps[i].scope)
        {
            if(skipScope)
                skipScope = false;
        }

        if(skipScope)
        {
            debug.Log("SKIPPING STEP\n");
            continue;
        }

        m_currentScope = m_pSteps[i].scope;

        if(inLoop)
        {
            if(m_currentScope < loopScope)
            {
                inLoop = false;
                i = tempPos;
                debug.Log("LOOP: JUMP TO START\n\n");
            }
        }

        //*****************************
        //PRINTING STEP INFO TO CONSOLE

        pInterpreter->GetRunningScript()->m_varList.UpdateVarList(m_currentScope);

        sprintf(msg,"STEP: %d\n\n", i);
        debug.Log("____________________\n");
        debug.Log(msg);

        debug.Log("DATA FOR STEP:\n");

        m_pSteps[i].GetVars();
        for(int ii = 0; ii < m_pSteps[i].nVars; ii++)
        {
            if(m_pSteps[i].funcData[ii])
            {
                sprintf(msg,"funcData[%d]: ", ii );
                debug.Log(msg);
                m_pSteps[i].funcData[ii]->PrintDataToConsole();
            }
        }
        debug.Log("\n\n");

        unsigned int result = m_pSteps[i].doFunction(m_currentScope);
        if(m_pSteps[i].func == &S_FUNC::FOR)
        {
            loopScope = m_currentScope + 1;
            tempPos = i;
        }
        if(m_currentScope == loopScope &&
           m_pSteps[i].func == &S_FUNC::IF)
        {
            if(*((bool*)m_pSteps[i].funcData[0]->GetData()) == true)
            {
                inLoop = true;
            }
        }

        if(m_currentScope < m_pSteps[i].scope)
        {
            debug.Log("EXITING SCOPE\n");
            skipScope = true;
        }

        if(result != NO_ERROR)
        {
            sprintf(msg, "STEP INCOMPLETE: %s\n", GetErrorText(result));
            debug.Log(msg);
            return result;
        }

           debug.Log("STEP COMPLETED: NO_ERROR\n");

        m_pSteps[i].PrintVariablesToConsole();
        debug.Log("\n\n");
    }

    return NO_ERROR;
}


unsigned int ScriptStep::doFunction(int& scriptScope)
{
    if(func == 0)
    {
        debug.Log("Function Not Set For Step\n");
        return ERROR_UNDEFINED_ERROR;
    }
    return (*func)(scriptScope, funcData);
}

void ScriptStep::SetVarNames(char** varNames)
{
    if(m_pVariableNames)
    {
        for(int i = 0; i < nVars; i++)
        {
            if(m_pVariableNames[i])
                delete[] m_pVariableNames[i];
        }
        delete[] m_pVariableNames;
    }
    m_pVariableNames = 0;

    if(nVars <= 0)
        return;

    m_pVariableNames = new char*[nVars];
    for(int i = 0; i < nVars; i++)
    {
        m_pVariableNames[i] = 0;

        if(!varNames[i])
            continue;

        m_pVariableNames[i] = new char[strlen(varNames[i]) + 2];
        strcpy(m_pVariableNames[i], varNames[i]);
    }
}

void ScriptStep::GetVars()
{
    for(int i = 0; i < nVars; i++)
    {
        if(!funcData[i])
            funcData[i] = pInterpreter->GetRunningScript()->
                m_varList.GetVariable(m_pVariableNames[i]);
    }
}
