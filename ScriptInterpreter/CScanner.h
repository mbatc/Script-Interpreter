#pragma once
#include "CScriptFile.h"
#include "CCharacter.h"
#include <stdio.h>

class CScanner
{
public:
    CScanner();
    ~CScanner();

    void SetFile(CScriptFile* file);
    unsigned int ScanFile();

    CCharacter* GetCharacters();
    int         GetCharacterCount();

private:
    void ScanCharacter(char c);

    CScriptFile*    m_pCurrentFile;
    CCharacter*     m_pCharacter;
    int             m_nCharacters;

    int m_row, m_col;
};
