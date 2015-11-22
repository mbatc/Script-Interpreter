#include "CFunctionParser.h"
#include "ScriptTreeFunctions.h"
#include "CParser.h"


CFunctionParser::CFunctionParser(CParser& parser)
:
    m_parser(parser)
{}

CFunctionParser::~CFunctionParser()
{}

void CFunctionParser::SetScript(CScriptFile* pScript)
{
    m_pScript = pScript;
}

void CFunctionParser::SetTokenList(CToken* pToken)
{
    m_pToken = pToken;
}

unsigned int CFunctionParser::ParseOutput(CScriptVariable*& retVar, int& index)
{
    char* varName[2] = {0};
    CParser::VariableInfo* varInfo = 0;
    int i_marker;

    bool b = false;
    retVar = new CScriptVariable(BOOL, &b, -1, "RETURN_VAR");
    index++;
    if(m_pToken[index].GetTokenString()[0] != '(')
    {
        OutputErrorMsg(ERROR_UNEXPECTED_TOKEN, m_pToken[index]);
        return ERROR_UNEXPECTED_TOKEN;
    }
    ScriptStep step;
    step.func = S_FUNC::OUTPUT;
    step.nVars = 2;
    step.funcData = new CScriptVariable*[2];
    i_marker = index + 1;
    step.funcData[0] = m_parser.GetStatementVar(index, true);

    if(!step.funcData[0])
    {
        varInfo = m_parser.GetInitVar(m_pToken[i_marker].GetTokenString());
        if(!varInfo)
        {
            OutputErrorMsg(ERROR_UNDEFINED_VARIABLE, m_pToken[i_marker]);
            return ERROR_UNDEFINED_VARIABLE;
        }
        varName[0] = varInfo->m_name;
    }
    step.funcData[1] = retVar;
    step.scope = m_parser.m_currentScope;
    step.SetVarNames(varName);
    m_pScript->m_funcTree.AddScriptStep(step);

    return NO_ERROR;
}

unsigned int CFunctionParser::ParseGetComponent(CScriptVariable*& retVar, int& index)
{
    index++;
    if(m_pToken[index].GetTokenString()[0] != '(')
        return ERROR_EXPECTED_SYMBOL;

    ScriptStep step;
    bool b = false;
    step.funcData = new CScriptVariable*[2];
    step.funcData[0] = m_parser.GetStatementVar(index, true);
    step.funcData[1] = new CScriptVariable(BOOL, &b,-1,"RETURN_VAR");
    step.func = &S_FUNC::ENGINE::GETCOMPONENT;
    step.nVars = 2;
    step.scope = m_parser.m_currentScope;

    m_pScript->m_funcTree.AddScriptStep(step);
    return NO_ERROR;
}

unsigned int CFunctionParser::ParseSaveToFile(CScriptVariable*& retVar, int& index)
{
    index++;
    bool b = false;
    if(m_pToken[index].GetTokenString()[0] != '(')
        return ERROR_EXPECTED_SYMBOL;

    ScriptStep step;

    char* varName[3] = {0};
    CParser::VariableInfo* varInfo = 0;
    int i_marker = index + 1;

    step.funcData = new CScriptVariable*[3];
    step.funcData[0] = m_parser.GetStatementVar(index,true);
    if(!step.funcData[0])
    {
		varInfo = m_parser.GetInitVar(m_pToken[i_marker].GetTokenString());
		if (!varInfo && !strcmp(m_pToken[i_marker].GetType(), S_IDENTIFIER))
        {
            OutputErrorMsg(ERROR_UNDEFINED_VARIABLE, m_pToken[i_marker]);
            return ERROR_UNDEFINED_VARIABLE;
        }
        varName[0] = varInfo->m_name;

    }

    i_marker = index + 1;
    step.funcData[1] = m_parser.GetStatementVar(index,true);
    if(!step.funcData[0])
    {
        varInfo = m_parser.GetInitVar(m_pToken[i_marker].GetTokenString());
        if(!varInfo && !strcmp(m_pToken[i_marker].GetType(),S_IDENTIFIER))
        {
            OutputErrorMsg(ERROR_UNDEFINED_VARIABLE, m_pToken[i_marker]);
            return ERROR_UNDEFINED_VARIABLE;
        }
        varName[0] = varInfo->m_name;

    }

    step.funcData[2] = new CScriptVariable(BOOL, &b, -1, "RETURN_VAR");
    step.nVars = 3;
    step.func = &S_FUNC::ENGINE::SAVETOFILE;
    step.scope = m_parser.m_currentScope;
    step.SetVarNames(varName);

    m_pScript->m_funcTree.AddScriptStep(step);
    return NO_ERROR;
}

unsigned int CFunctionParser::ParseReadFromFile(CScriptVariable*& retVar, int& index)
{
    index++;
    bool b = false;
    if(m_pToken[index].GetTokenString()[0] != '(')
        return ERROR_EXPECTED_SYMBOL;

    ScriptStep step;
    step.funcData = new CScriptVariable*[4];

    CParser::VariableInfo* varInfo = 0;
    char* varName[4] = {0};

    int i_marker = index + 1;
    step.funcData[0] = m_parser.GetStatementVar(index, true);
    if(!step.funcData[0])
    {
        varInfo = m_parser.GetInitVar(m_pToken[i_marker].GetTokenString());
        if(!varInfo)
        {
            OutputErrorMsg(ERROR_UNDEFINED_VARIABLE, m_pToken[i_marker]);
            return ERROR_UNDEFINED_VARIABLE;
        }
        varName[0] = varInfo->m_name;
    }

    i_marker = index + 1;
    step.funcData[1] = m_parser.GetStatementVar(index, true);
    if(!step.funcData[1])
    {
        varInfo = m_parser.GetInitVar(m_pToken[i_marker].GetTokenString());
        if(!varInfo)
        {
            OutputErrorMsg(ERROR_UNDEFINED_VARIABLE, m_pToken[i_marker]);
            return ERROR_UNDEFINED_VARIABLE;
        }
        varName[1] = varInfo->m_name;
    }

    i_marker = index + 1;
    step.funcData[2] = m_parser.GetStatementVar(index, true);
    if(!step.funcData[2])
    {
        varInfo = m_parser.GetInitVar(m_pToken[i_marker].GetTokenString());
        if(!varInfo)
        {
            OutputErrorMsg(ERROR_UNDEFINED_VARIABLE, m_pToken[i_marker]);
            return ERROR_UNDEFINED_VARIABLE;
        }
        varName[2] = varInfo->m_name;
    }

    step.funcData[3] = new CScriptVariable(BOOL, &b, -1, "RETURN_VAR");
    step.nVars = 4;
    step.func = &S_FUNC::ENGINE::READFROMFILE;
    step.scope = m_parser.m_currentScope;
    step.SetVarNames(varName);

    m_pScript->m_funcTree.AddScriptStep(step);
    return NO_ERROR;
}


unsigned int ParseGetScriptVar(CScriptVariable*& retVar, int& index)
{
    index++;

    return NO_ERROR;
}
