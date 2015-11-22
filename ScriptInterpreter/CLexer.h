#pragma once

#include "CScanner.h"
#include "CToken.h"

class CLexer
{
public:
    CLexer();
    ~CLexer();

    void SetCharacters(CCharacter* pCharacter, int nCharacters);
    CToken* GetTokens();
    int GetTokenCount();

    unsigned int ProcessCharacters();

private:
    unsigned int ConstructToken(int& index);
    char* GetTokenType(char* tokenString);

    CCharacter* m_pCharacter;
    CToken* m_pToken;

    int m_nTokens;
    int m_nCharacters;
};
