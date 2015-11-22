#include "CScanner.h"
#include "ErrorDefinitions.h"
#include "MemoryHelper.h"
#include "main.h"

CScanner::CScanner()
:
    m_pCharacter(0),
    m_nCharacters(0),
    m_pCurrentFile(0),
    m_row(1),
    m_col(1)
{}

CScanner::~CScanner()
{}

void CScanner::SetFile(CScriptFile* file)
{
    m_pCurrentFile = file;

	MEMORY::SafeDeleteArr(m_pCharacter);
	m_nCharacters = 0;
	m_col = 1;
	m_row = 1;
}

unsigned int CScanner::ScanFile()
{
    FILE* pFile = fopen(m_pCurrentFile->GetFilename(), "r");
    if(!pFile)
    {
        debug.Log("Could Not Open File: ");
        debug.Log(m_pCurrentFile->GetFilename());
        debug.Log("\n");
        return ERROR_FILE_NOT_FOUND;
    }

	int index = 0;
    do
    {
		ScanCharacter(m_pCurrentFile->GetSource()[index]);
		index++;
	} while (m_pCurrentFile->GetSource()[index - 1] != '\0');

    fclose(pFile);

    CCharacter charScan('\0', m_row, m_col, m_nCharacters, m_pCurrentFile->GetSource());
    MEMORY::AddToList(m_pCharacter, charScan, m_nCharacters);
    m_pCharacter[m_nCharacters - 1].PrintDataToConsole();

    return NO_ERROR;
}

void CScanner::ScanCharacter(char c)
{
    CCharacter charScan(c, m_row, m_col, m_nCharacters, m_pCurrentFile->GetSource());
    if(c == '\n')
    {
        m_col = 1;
        m_row++;
    }
    else
    {
        m_col++;
    }

    MEMORY::AddToList(m_pCharacter, charScan, m_nCharacters);
    m_pCharacter[m_nCharacters - 1].PrintDataToConsole();
}

CCharacter* CScanner::GetCharacters()
{
    return m_pCharacter;
}

int CScanner::GetCharacterCount()
{
    return m_nCharacters;
}
