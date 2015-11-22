#pragma once

#include "CScriptFunctionTree.h"
#include "CScriptVariableList.h"

//Needs to be a component child

class CScriptFile //: public CComponent
{
public:
    CScriptFile();
    ~CScriptFile();

    void Update(double deltaTime);
    void Render(){}

	void SetFile(char* filename);
	void GetSourceFromFile();

    char* GetFilename();
    char* GetSource();
    void doScript();

    void PrintVariableList(bool c_out = false);

    CScriptFunctionTree m_funcTree;
    CScriptVariableList m_varList;
private:

    char* m_pFilename;
    char* m_pSrcCode;
};
