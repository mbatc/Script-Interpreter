#include "CParser.h"
#include "ErrorDefinitions.h"
#include "ScriptTreeFunctions.h"
#include "ScriptLanguageDefinition.h"
#include "MemoryHelper.h"

#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

CParser::CParser()
:
    m_currentScope(0),
    m_pToken(0),
    m_nTokens(0),
    m_inIf(false),
    m_functionParser(*this),
    m_tempIndex(-1),
    m_inFor(false),
    m_nInitVars(0),
    m_pInitVars(0)
{}

CParser::~CParser()
{}

void CParser::SetTokenList(CToken* pTokens, int nTokens)
{
    m_nTokens = nTokens;
    m_pToken = pTokens;

    m_functionParser.SetTokenList(m_pToken);
}

unsigned int CParser::ParseTokens()
{
    int index = 0;

	unsigned int result = NO_ERROR;
	unsigned int last_result = NO_ERROR;
    do
    {
        result = GenerateStep(index);
		if (result != NO_ERROR)
		{
			last_result = result;

			do
			{
				index++;
			} while (m_pToken[index].GetTokenString()[0] != ';' && 
				!strcmp(S_SYMBOL,m_pToken[index].GetType()));
		}

        index++;
    }while(m_pToken[index].GetTokenString()[0] != END_MARK);

    return last_result;
}

unsigned int CParser::GenerateStep(int& index)
{
    unsigned int result = NO_ERROR;
    if(!strcmp(m_pToken[index].GetType(), S_TYPE))
    {
        result = ProcessType(index, true);
    }
    else if(!strcmp(m_pToken[index].GetType(), S_FUNCTION))
    {
        result = ProcessFunction(index);
    }
    else if(!strcmp(m_pToken[index].GetType(), S_KEYWORD))
    {
        result = ProcessKeyword(index);
    }
    else if(!strcmp(m_pToken[index].GetType(), S_IDENTIFIER))
    {
        result = ProcessIdentifier(index);
    }
    else if(!strcmp(m_pToken[index].GetType(), S_SYMBOL))
    {
        result = ProcessSymbol(index);
    }
    else
    {
        OutputErrorMsg(ERROR_UNEXPECTED_TOKEN, m_pToken[index]);
        result = ERROR_UNEXPECTED_TOKEN;
    }

    return result;
}

void CParser::SetScript(CScriptFile* pScript)
{
    m_pScript = pScript;
    m_functionParser.SetScript(pScript);
}

unsigned int CParser::ProcessIdentifier(int& index)
{
    if(!strcmp(m_pToken[index].GetTokenString(), "PERSISTANT_VARIABLES"))
    {
        GetPersistantVars(index);
    }
    else if(!strcmp(m_pToken[index].GetType(), S_FUNCTION))
    {
        ProcessFunction(index);
    }
    else
    {
        index--;
		if (!GetStatementVar(index, true))
			return ERROR_EXPECTED_SYMBOL;
    }
    return NO_ERROR;
}

unsigned int CParser::ProcessKeyword(int& index)
{
    if(!strcmp(m_pToken[index].GetTokenString(),"if"))
    {
        return ParseIf(index);
    }
    if(!strcmp(m_pToken[index].GetTokenString(), "else"))
    {
        return ParseElse(index);
    }
    if(!strcmp(m_pToken[index].GetTokenString(), "do"))
    {
        return ParseDo(index);
    }
    if(!strcmp(m_pToken[index].GetTokenString(), "break"))
    {
        return ParseBreak(index);
    }
    if(!strcmp(m_pToken[index].GetTokenString(), "for"))
    {
        return ParseFor(index);
    }

    return ERROR_UNDEFINED_ERROR;
}

unsigned int CParser::ProcessSymbol(int& index)
{
    if(m_pToken[index].GetTokenString()[0] == '{')
    {
        if(!m_inIf && !m_inFor)
            m_currentScope++;
    }
    if(m_pToken[index].GetTokenString()[0] == '}')
    {
        if(m_inFor)
        {
            GenerateStep(m_tempIndex);
            m_inFor = false;

            ScriptStep step;
            step.funcData = 0;
            step.nVars = 0;
            step.func = S_FUNC::FOR_END;
            step.scope = m_currentScope - 1;
            m_pScript->m_funcTree.AddScriptStep(step);
        }

        m_currentScope--;
        UpdateInitVarList();
    }

    return NO_ERROR;
}

unsigned int CParser::ProcessType(int& index, bool CreateStep)
{
    SCRIPT_VAR_TYPE type;
    int i = 0;
    bool b = false;
    float f = 0.0f;
    String s;
    void* data = 0;

    if(!strcmp(m_pToken[index].GetTokenString(), "int"))
    {
        type = INT;
        data = &i;
    }
    else if(!strcmp(m_pToken[index].GetTokenString(), "float"))
    {
        type = FLOAT;
        data = &f;
    }
    else if(!strcmp(m_pToken[index].GetTokenString(), "bool"))
    {
        type = BOOL;
        data = &b;
    }
    else if(!strcmp(m_pToken[index].GetTokenString(), "string"))
    {
        type = STR;
        data = &s;
    }
    else
    {
        OutputErrorMsg(ERROR_UNDEFINED_DATA_TYPE, m_pToken[index]);
        return ERROR_UNDEFINED_DATA_TYPE;
    }

    index++;
    CScriptVariable* var = m_pScript->m_varList.GetVariable(m_pToken[index].GetTokenString());
    char* var_name = m_pToken[index].GetTokenString();

    if(var)
    {
        OutputErrorMsg(ERROR_REDEFINITION, m_pToken[index]);
        return ERROR_REDEFINITION;
    }

    if(CreateStep)
    {
        String s_type;
        String s_name;

        s_type.SetString(m_pToken[index - 1].GetTokenString());
        s_name.SetString(m_pToken[index].GetTokenString());

		char* nme[2];
		nme[0] = new char[strlen("VAR_TYPE") + 1];
		nme[1] = new char[strlen("VAR_NAME") + 1];

		strcpy(nme[0], "VAR_TYPE");
		strcpy(nme[1], "VAR_NAME");

        ScriptStep step;
        step.nVars = 2;
        step.scope = m_currentScope;
        step.funcData = new CScriptVariable*[3];
        step.funcData[0] = new CScriptVariable(STR, &s_type, m_currentScope, "VAR_TYPE");
        step.funcData[1] = new CScriptVariable(STR, &s_name, m_currentScope, "VAR_NAME");
        step.func = &S_FUNC::INITIALIZE_VAR;
		step.SetVarNames(nme);

        unsigned int result = AddInitVar(s_name.GetString(), type);

        if(result != NO_ERROR)
        {
            OutputErrorMsg(result, m_pToken[index]);
            return result;
        }

        var_name = s_name.GetString();

        m_pScript->m_funcTree.AddScriptStep(step);
    }
    else
    {
        var = new CScriptVariable(type, data, m_currentScope, m_pToken[index].GetTokenString());
        if(!var)
            cout << "Could not create variable: " << m_pToken[index].GetTokenString()
                 << "\n\t- Error: Out of Memory...\n";
        m_pScript->m_varList.AddVariable(var);
    }

    index++;
    if(m_pToken[index].GetTokenString()[0] == '=')
    {
        CScriptVariable* var_2 = GetStatementVar(index, true);
		if (!var_2)
		{
			if (!strcmp(m_pToken[index].GetType(), S_SYMBOL))
			{
				return ERROR_EXPECTED_SYMBOL;
			}
		}

        char* stepVarNames[2] = {var_name, var_2->GetName()};

        ScriptStep step;

        CScriptVariable** s_data = new CScriptVariable*[2];
        s_data[0] = var;
        s_data[1] = var_2;

        step.funcData = s_data;
        step.nVars = 2;
        step.func = &S_FUNC::ASSIGN;
        step.scope = m_currentScope;
        step.SetVarNames(stepVarNames);

        if(CreateStep)
            m_pScript->m_funcTree.AddScriptStep(step);
        else
            S_FUNC::ASSIGN(m_currentScope, s_data);

        return NO_ERROR;
    }
    else if(m_pToken[index].GetTokenString()[0] == ';')
    {
        return NO_ERROR;
    }
    else
    {
        return NO_ERROR;
    }
}

CScriptVariable* CParser::GetStatementVar(int& index, bool CreateStep)
{
    index++;
    CScriptVariable* var = 0;
    SCRIPT_VAR_TYPE type;
    char* varNames[3] = {0};
    VariableInfo* varInfo[3] = {0};


    if(m_pToken[index].GetTokenString()[0] == END_STATEMENT)
        return NULL;

    if(!strcmp(m_pToken[index].GetType(), S_IDENTIFIER))
    {
        var = m_pScript->m_varList.GetVariable(m_pToken[index].GetTokenString());
        if(!var)
        {
            varInfo[0] = GetInitVar(m_pToken[index].GetTokenString());
            if(!varInfo[0])
            {
                OutputErrorMsg(ERROR_UNDEFINED_VARIABLE, m_pToken[index]);
                return NULL;
            }

            varNames[0] = varInfo[0]->m_name;
        }

    }
    else if(!strcmp(m_pToken[index].GetType(), S_STRING))
    {
        String s;
        s.SetString(m_pToken[index].GetTokenString());
        var = new CScriptVariable(STR, &s, 0, "TEMP_VAR");
    }
    else if(!strcmp(m_pToken[index].GetType(), S_NUMBER))
    {
        int i = atoi(m_pToken[index].GetTokenString());
        var = new CScriptVariable(INT, &i, 0, "TEMP_VAR");
    }
    else if(!strcmp(m_pToken[index].GetType(), S_DECIMAL))
    {
        float f = atof(m_pToken[index].GetTokenString());
        var = new CScriptVariable(FLOAT, &f, 0, "TEMP_VAR");
    }
    else if(!strcmp(m_pToken[index].GetType(), S_BOOL))
    {
        bool b;
        if(!strcmp(m_pToken[index].GetTokenString(), "false"))
        {
            b = false;
        }
        else
        {
            b = true;
        }

        var = new CScriptVariable(BOOL, &b, 0, "TEMP_VAR");
    }
    else
    {
        OutputErrorMsg(ERROR_INVALID_VALUE, m_pToken[index]);
        return 0;
    }
    index++;

    if(m_pToken[index].GetTokenString()[0] == END_STATEMENT)
    {
        return var;
    }
    else if(m_pToken[index].GetTokenString()[0] == ')')
    {
        return var;
    }
    else if(m_pToken[index].GetTokenString()[0] == ',')
    {
        return var;
    }
    else
    {
        unsigned int (*func)(int& scope, CScriptVariable** data);
        CScriptVariable* tempVar = 0;
        CScriptVariable* tempVar_1 = 0;
        switch(m_pToken[index].GetTokenString()[0])
        {
        case '+':
            func = &S_FUNC::ADD;
            tempVar_1 = var;
            if(!var)
                var = new CScriptVariable(varInfo[0]->m_type, 0,
                0, "TEMP_VAR");
            else
                var = new CScriptVariable(var->GetType(), var->GetData(),
                0, "TEMP_VAR");
            break;
        case '-':
            func = &S_FUNC::SUB;
            tempVar_1 = var;
            if(!var)
                var = new CScriptVariable(varInfo[0]->m_type, 0,
                0, "TEMP_VAR");
            else
                var = new CScriptVariable(var->GetType(), var->GetData(),
                0, "TEMP_VAR");

            break;
        case '*':
            func = &S_FUNC::MUL;
            tempVar_1 = var;
            if(!var)
                var = new CScriptVariable(varInfo[0]->m_type, 0,
                0, "TEMP_VAR");
            else
                var = new CScriptVariable(var->GetType(), var->GetData(),
                0, "TEMP_VAR");
            break;
        case '/':
            func = &S_FUNC::DIV;
            tempVar_1 = var;
            if(!var)
                var = new CScriptVariable(varInfo[0]->m_type, 0,
                0, "TEMP_VAR");
            else
                var = new CScriptVariable(var->GetType(), var->GetData(),
                0, "TEMP_VAR");
            break;
        case '=':
            func = &S_FUNC::ASSIGN;
            break;
        default:
			OutputErrorMsg(ERROR_EXPECTED_SYMBOL, m_pToken[index]);
            return NULL;
        }

        ScriptStep step;

        CScriptVariable** tempData = 0;
        if(func == &S_FUNC::ASSIGN)
        {
            tempData = new CScriptVariable*[2];
            tempVar = GetStatementVar(index, CreateStep);
			if (!tempVar)
			{
				if (strcmp(m_pToken[index].GetType(), S_SYMBOL))
					return NULL;
			}

            if(!tempVar)
                return var;
            tempData[0] = var;
            tempData[1] = tempVar;

            step.nVars = 2;
        }
        else
        {
            varNames[1] = varNames[0];
            varNames[0] = 0;

            varInfo[0] = varInfo[1];
            varInfo[1] = 0;

            tempData = new CScriptVariable*[3];
            tempVar = GetStatementVar(index, CreateStep);
			if (!tempVar && strcmp(m_pToken[index].GetType(), S_SYMBOL))
			{
				return NULL;
			}

            if(!tempVar)
                return var;

            tempData[0] = var;
            tempData[1] = tempVar_1;
            tempData[2] = tempVar;

            step.nVars = 3;
        }

        step.funcData = tempData;
        step.func = func;
        step.scope = m_currentScope;
        step.SetVarNames(varNames);

        if(CreateStep)
            m_pScript->m_funcTree.AddScriptStep(step);
        else
            step.doFunction(m_currentScope);
    }
    return var;
}

unsigned int CParser::GetPersistantVars(int& index)
{
    index++;
    int openBracketIndex = index;
    if(m_pToken[index].GetTokenString()[0] != '{')
    {
        OutputErrorMsg(ERROR_UNEXPECTED_TOKEN, m_pToken[index]);
        return ERROR_UNEXPECTED_TOKEN;
    }
    index++;
    do
    {
        ProcessType(index, false);
        index++;
        if(m_pToken[index].GetTokenString()[0] == END_MARK)
        {
            OutputErrorMsg(ERROR_EXPECTED_CLOSING_BRACKET, m_pToken[openBracketIndex]);
            return ERROR_EXPECTED_CLOSING_BRACKET;
        }
    }while(m_pToken[index].GetTokenString()[0] != '}');
}

unsigned int CParser::ParseIf(int& index)
{
    m_inIf = true;
    index++;
    m_currentScope++;
    if(m_pToken[index].GetTokenString()[0] != '(')
    {
        OutputErrorMsg(ERROR_UNEXPECTED_TOKEN, m_pToken[index]);
        return ERROR_UNEXPECTED_TOKEN;
    }

    ScriptStep step;
    CScriptVariable** tempData = new CScriptVariable*[1];
    tempData[0] = GetStatementCompare(index);

    if(!tempData[0])
        return ERROR_INVALID_VALUE;

    step.func = &S_FUNC::IF;
    step.nVars = 1;
    step.funcData = tempData;
    step.scope = m_currentScope;

    m_pScript->m_funcTree.AddScriptStep(step);

    return NO_ERROR;
}

unsigned int CParser::ParseBreak(int& index)
{
    return NO_ERROR;
}

unsigned int CParser::ParseDo(int& index)
{
    return NO_ERROR;
}

unsigned int CParser::ParseElse(int& index)
{
    return NO_ERROR;
}

unsigned int CParser::ParseFor(int& index)
{
    m_inFor = true;
    index++;
    if(m_pToken[index].GetTokenString()[0] != '(')
    {
        OutputErrorMsg(ERROR_UNEXPECTED_TOKEN,m_pToken[index]);
        return ERROR_UNEXPECTED_TOKEN;
    }

    ScriptStep step;
    step.funcData = 0;
    step.func = &S_FUNC::FOR;
    step.nVars = 0;
    step.scope = m_currentScope;
    m_pScript->m_funcTree.AddScriptStep(step);

    index++;
    m_currentScope++;

    step.funcData = new CScriptVariable*[1];
    step.funcData[0] = GetStatementCompare(index);
    step.nVars = 1;
    step.func = S_FUNC::IF;
    step.scope = m_currentScope;
    if(!step.funcData[0])
        return ERROR_INVALID_VALUE;
    index++;

    m_pScript->m_funcTree.AddScriptStep(step);
    m_tempIndex = index;

    return NO_ERROR;
}

CScriptVariable* CParser::GetStatementCompare(int& index)
{
    index++;
    bool b = false;
    char* varNames[3] = {0};
    CScriptVariable* var = new CScriptVariable(BOOL, &b, 0, "TEMP_BOOL");
    CScriptVariable* var_2 = m_pScript->m_varList.GetVariable(m_pToken[index].GetTokenString());
    VariableInfo* varInfo = 0;
    if(!var_2)
    {
        varInfo = GetInitVar(m_pToken[index].GetTokenString());
        if(!varInfo)
        {
            OutputErrorMsg(ERROR_UNDEFINED_VARIABLE, m_pToken[index]);
            return 0;
        }
    }

    unsigned int (*func)(int& scope, CScriptVariable** data);

    index++;
    switch(m_pToken[index].GetTokenString()[0])
    {
    case '=':
        if(m_pToken[index+1].GetTokenString()[0] == '=')
        {
            index++;
            func = &S_FUNC::EQUALS;
        }
        else
        {
            func = &S_FUNC::ASSIGN;
        }
        break;
    case '<':
        if(m_pToken[index + 1].GetTokenString()[0] == '=')
        {
            index++;
            func = &S_FUNC::LESSTHAN_EQUALS;
        }
        else
        {
            func = &S_FUNC::LESSTHAN;
        }
        break;
    case '>':
        if(m_pToken[index + 1].GetTokenString()[0] == '=' )
        {
            index++;
            func = &S_FUNC::MORETHAN_EQUALS;
        }
        else
        {
            func = &S_FUNC::MORETHAN;
        }
        break;
    default:
        OutputErrorMsg(ERROR_UNDEFINED_OPERATOR, m_pToken[index]);
        return 0;
    }


    ScriptStep step;
    CScriptVariable** tempData = new CScriptVariable*[3];
    tempData[0] = var;
    tempData[1] = var_2;
    tempData[2] = GetStatementVar(index,true);
    step.funcData = tempData;
    step.nVars = 3;
    step.scope = m_currentScope;
    step.func = func;

    if(tempData[2])
        varNames[2] = tempData[2]->GetName();

    if(!var_2)
        varNames[1] = varInfo->m_name;
    step.SetVarNames(varNames);

    m_pScript->m_funcTree.AddScriptStep(step);
    MEMORY::SafeDeleteArr(tempData);
    return var;
}

unsigned int CParser::ProcessFunction(int& index)
{
    ScriptStep step;
    CScriptVariable* retVar = 0;
    if(!strcmp(m_pToken[index].GetTokenString(), "OUTPUT"))
    {
        return m_functionParser.ParseOutput(retVar, index);
    }
    else if(!strcmp(m_pToken[index].GetTokenString(), "GetComponent"))
    {
        return m_functionParser.ParseGetComponent(retVar,index);
    }
    else if(!strcmp(m_pToken[index].GetTokenString(), "SaveToFile"))
    {
		return m_functionParser.ParseSaveToFile(retVar, index);
    }
    else if(!strcmp(m_pToken[index].GetTokenString(), "ReadFromFile"))
    {
		return m_functionParser.ParseReadFromFile(retVar, index);
    }
    else if(!strcmp(m_pToken[index].GetTokenString(), "GetScriptVar"))
    {
        //m_functionParser.ParseGetScriptVar(retVar, index);
    }
    else
    {
        OutputErrorMsg(ERROR_UNDEFINED_VARIABLE, m_pToken[index]);
        return ERROR_UNDEFINED_VARIABLE;
    }
    return NO_ERROR;
}

unsigned int CParser::AddInitVar(char* name, SCRIPT_VAR_TYPE type)
{
    for(int i = 0; i < m_nInitVars; i++)
    {
        if(!strcmp(name, m_pInitVars[i].m_name))
        {
            return ERROR_REDEFINITION;
        }
    }

    VariableInfo* pTempList;
    pTempList = m_pInitVars;
    m_pInitVars = new VariableInfo[m_nInitVars + 1];
    if(!m_pInitVars)
        return ERROR_UNDEFINED_ERROR;

    for(int i = 0; i < m_nInitVars; i++)
    {
        m_pInitVars[i] = pTempList[i];
    }

    if(pTempList)
        delete[] pTempList;

    m_pInitVars[m_nInitVars].m_name = name;
    m_pInitVars[m_nInitVars].m_type = type;
    m_pInitVars[m_nInitVars].m_scope = m_currentScope;

    m_nInitVars++;

    return NO_ERROR;
}
CParser::VariableInfo* CParser::GetInitVar(char* name)
{
    for(int i = 0; i < m_nInitVars; i++)
    {
        if(!strcmp(name, m_pInitVars[i].m_name))
            return &m_pInitVars[i];
    }

    return 0;
}
void CParser::UpdateInitVarList()
{
    for(int i = 0; i < m_nInitVars; i++)
    {
        if(m_pInitVars[i].m_scope > m_currentScope)
        {
            RemoveInitVar(i);
            i--;
        }
    }
}

void CParser::RemoveInitVar(int index)
{
    if(index > m_nInitVars || index < 0)
        return;

    VariableInfo* pTempList = 0;
    pTempList = new VariableInfo[m_nInitVars - 1];

    int listIndex = 0;
    for(int i = 0; i < m_nInitVars; i++)
    {
        if(i == index)
            continue;

        pTempList[listIndex] = m_pInitVars[i];

        listIndex++;
    }

    if(m_pInitVars)
        delete[] m_pInitVars;
    m_pInitVars = pTempList;

    m_nInitVars--;
}
