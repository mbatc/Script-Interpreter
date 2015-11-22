#pragma once
#include "CScriptVariable.h"
#include "ErrorDefinitions.h"

#include "main.h"
#include "MemoryHelper.h"

#include <iostream>

using namespace std;

/*IN SCRIPT STEP doFunction, add ability to get variable list
and get the variables from list before calling the func. This is
to help implement scopes.
*/
struct ScriptStep
{
    ScriptStep()
    :
        funcData(0),
        func(0),
        scope(0),
        m_pVariableNames(0),
        nVars(0)
    {}
    ~ScriptStep()
    {}
    int nVars;
    int scope;
    char**              m_pVariableNames;
    CScriptVariable**   funcData;
    unsigned int (*func)(int& scope, CScriptVariable** data);

    unsigned int doFunction(int& scriptScope);
    void SetVarNames(char** varNames);
    void GetVars();
    void PrintVariablesToConsole()
    {
        for(int i = 0; i < nVars; i++)
        {
            funcData[i]->PrintDataToConsole();
        }
    }

	void Cleanup()
	{
		if (m_pVariableNames)
		{
			for (int i = 0; i < nVars; i++)
			{
				MEMORY::SafeDeleteArr(m_pVariableNames[i]);
			}

			MEMORY::SafeDeleteArr(m_pVariableNames);
		}

		MEMORY::SafeDeleteArr(funcData);
	}
};

class CScriptFunctionTree
{
public:
    CScriptFunctionTree();
    ~CScriptFunctionTree();

    unsigned int runScript();

    void AddScriptStep(ScriptStep step);

    void Reset();
private:

    ScriptStep* m_pSteps;
    int m_nSteps;
    int m_currentScope;
};
