#include "CFileTree.h"
#include "MemoryHelper.h"

CFileTree::CFileTree()
:
    m_pFileList(0),
    m_nFiles(0)
{}

CFileTree::~CFileTree()
{}

void CFileTree::AddFileToList(CScriptFile file)
{
    MEMORY::AddToList(m_pFileList, file, m_nFiles);
}

CScriptFile* CFileTree::GetFile(int index)
{
    return &m_pFileList[index];
}

int CFileTree::GetNumberOfFiles()
{
    return m_nFiles;
}

CScriptFile* CFileTree::GetFile(char* filename)
{
    if(!filename)
        return 0;
    for(int i = 0; i < m_nFiles; i++)
    {
        if(!strcmp(filename, m_pFileList[i].GetFilename()))
            return &m_pFileList[i];
    }

    return 0;
}
