#pragma once
#include "CScriptFile.h"

class CParser;

class CFunctionParser
{
public:
    CFunctionParser(CParser& parser);
    ~CFunctionParser();

    void SetScript(CScriptFile* pScript);
    void SetTokenList(CToken* pTokens);

    unsigned int ParseOutput(CScriptVariable*& retVar, int& index);
    unsigned int ParseGetComponent(CScriptVariable*& retVar, int& index);
    unsigned int ParseSaveToFile(CScriptVariable*& retVar, int& index);
    unsigned int ParseReadFromFile(CScriptVariable*& retVar, int& index);
    unsigned int ParseGetScriptVar(CScriptVariable*& retVar, int& index);

private:
    CScriptFile*    m_pScript;
    CToken*         m_pToken;
    CParser&        m_parser;
};
