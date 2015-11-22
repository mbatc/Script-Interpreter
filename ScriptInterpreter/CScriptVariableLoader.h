#pragma once

#include <stdio.h>
#include "CScriptVariable.h"

class CScriptVariableLoader
{
public:
    CScriptVariableLoader();
    ~CScriptVariableLoader();

    void SaveToFile(CScriptVariable* var, char* filename);
    void LoadFromFile(CScriptVariable*& var, char* pVarName, char* filename);
private:
    FILE* m_pFile;
    char* m_pFileSource;
};
