#pragma once
#include "CScriptFile.h"

class CFileTree
{
public:
    CFileTree();
    ~CFileTree();

    void AddFileToList(CScriptFile file);
    int  GetNumberOfFiles();
    CScriptFile* GetFile(int index);
    CScriptFile* GetFile(char* filename);

private:

    int m_nFiles;
    CScriptFile* m_pFileList;
};
