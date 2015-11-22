#include "CScriptFile.h"
#include "MemoryHelper.h"
#include "ScriptTreeFunctions.h"

#include "main.h"

#include <stdio.h>
#include <iostream>
using namespace std;

CScriptFile::CScriptFile()
:
    m_pFilename(0),
    m_pSrcCode(0)
{}

CScriptFile::~CScriptFile()
{}

void CScriptFile::Update(double deltaTime)
{
    doScript();
}

void CScriptFile::doScript()
{
    PrintVariableList();
    debug.Log("|***********************************************|\n");
    debug.Log("|              BEGINNING OF SCRIPT              |\n");
    m_funcTree.runScript();
    debug.Log("|                 END OF SCRIPT                 |\n");
    debug.Log("|***********************************************|\n\n\n");
    PrintVariableList();
}

void CScriptFile::SetFile(char* filename)
{
    MEMORY::SafeDeleteArr(m_pFilename);
    m_pFilename = new char[strlen(filename) + 2]; //+ 2 for null terminating char and padding
    strcpy(m_pFilename, filename);

	GetSourceFromFile();
}

void CScriptFile::GetSourceFromFile()
{
	FILE* pFile = fopen(m_pFilename, "rb");

	if (!pFile)
	{
		cout << "Could Not Open Script: " << m_pFilename << endl;
		return;
	}

	int fileLen = 0;
	do
	{
		char c;
		if (!feof(pFile))
		{
			fread(&c, sizeof(char), 1, pFile);
			fileLen++;
		}
	} while (!feof(pFile));

	m_pSrcCode = new char[fileLen];
	if (!m_pSrcCode)
		return;

	rewind(pFile);

	fread(m_pSrcCode, sizeof(char), fileLen, pFile);
	m_pSrcCode[fileLen - 1] = '\0';
}

void CScriptFile::PrintVariableList(bool c_out)
{
    char msg[512] = {0};
    sprintf(msg, "SCRIPT: %s\n", m_pFilename);
    debug.Log("____________________\n");
    debug.Log(msg);
    debug.Log("VARIABLE LIST - \n\n");

	m_varList.PrintVariableListToConsole(c_out);

    debug.Log("END OF LIST \n\n\n");
}

char* CScriptFile::GetFilename()
{
    return m_pFilename;
}

char* CScriptFile::GetSource()
{
    return m_pSrcCode;
}
