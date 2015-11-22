#pragma once
#include "CToken.h"
#include "CScriptFile.h"
#include "CFunctionParser.h"

class CParser
{
    friend CFunctionParser;
    struct VariableInfo
    {
        char* m_name;
        SCRIPT_VAR_TYPE m_type;
        int m_scope;
    };

public:
    CParser();
    ~CParser();

    void SetTokenList(CToken* pTokens, int nTokens);
    void SetScript(CScriptFile* pScript);

    unsigned int ParseTokens();

private:
    unsigned int GenerateStep(int& index);
    unsigned int ProcessIdentifier(int& index);
    unsigned int ProcessSymbol(int& index);
    unsigned int ProcessKeyword(int& index);
    unsigned int ProcessType(int& index, bool CreateStep);
    unsigned int ProcessFunction(int& index);

    unsigned int ParseIf(int& index);
    unsigned int ParseBreak(int& index);
    unsigned int ParseDo(int& index);
    unsigned int ParseElse(int& index);
    unsigned int ParseFor(int& index);

    unsigned int GetPersistantVars(int& index);

    unsigned int AddInitVar(char* name, SCRIPT_VAR_TYPE type);
    VariableInfo* GetInitVar(char* name);
    void UpdateInitVarList();
    void RemoveInitVar(int index);

    CScriptVariable* GetStatementVar(int& index, bool CreateStep);
    CScriptVariable* GetStatementCompare(int& index);

    CFunctionParser m_functionParser;

    CScriptFile* m_pScript;
    CToken*      m_pToken;
    int          m_nTokens;
    int          m_currentScope;
    int          m_tempIndex;
    bool         m_inIf;
    bool         m_inFor;

    VariableInfo*   m_pInitVars;
    int             m_nInitVars;
};
