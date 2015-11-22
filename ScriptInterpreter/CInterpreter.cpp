#include "CInterpreter.h"
#include "ErrorDefinitions.h"

#include "main.h"
#include "MemoryHelper.h"

CInterpreter::CInterpreter()
:
    _compile_done(false),
    _compile_result(0)
{}

CInterpreter::~CInterpreter()
{}

void CInterpreter::SetFileTree(CFileTree fileTree)
{
    m_fileTree = fileTree;
}

unsigned int CInterpreter::CompileFileList()
{
    char msg[512] = {0};
    MEMORY::SafeDeleteArr(_compile_result);

	unsigned int result = NO_ERROR;
    for(int i = 0; i < m_fileTree.GetNumberOfFiles(); i++)
    {
		result = CompileFile(m_fileTree.GetFile(i));
    }

	return result;
}

unsigned int CInterpreter::CompileFile(CScriptFile* file)
{
    unsigned int* temp = _compile_result;
    file->m_funcTree.Reset();
    file->m_varList.Reset();
	file->GetSourceFromFile();

    _compile_result = new unsigned int[m_fileTree.GetNumberOfFiles()];
    if(temp)
    {
        for(int i = 0; i < m_fileTree.GetNumberOfFiles(); i++)
            _compile_result[i] = temp[i];
    }
    else
    {
        for(int i = 0; i < m_fileTree.GetNumberOfFiles(); i++)
            _compile_result[i] = ERROR_NOT_COMPILED;
    }
    if(temp)
        delete[] temp;

    m_scanner.SetFile(file);
    unsigned int result = m_scanner.ScanFile();
    if(result != NO_ERROR)
    {
        return result;
    }

    m_lexer.SetCharacters(m_scanner.GetCharacters(), m_scanner.GetCharacterCount());
    result =  m_lexer.ProcessCharacters();
    if(result != NO_ERROR)
    {
        return result;
    }

    m_parser.SetScript(file);
    m_parser.SetTokenList(m_lexer.GetTokens(), m_lexer.GetTokenCount());
    result = m_parser.ParseTokens();

    for(int i = 0; i < m_fileTree.GetNumberOfFiles(); i++)
    {
        if(!strcmp(m_fileTree.GetFile(i)->GetFilename(), file->GetFilename()))
            _compile_result[i] = result;
    }

    return result;
}

bool CInterpreter::RunCompiledScripts()
{
	if (!_compile_result)
	{
		cout << "Could not run scripts: " << GetErrorText(ERROR_NOT_COMPILED) << endl;
		return false;
	}

    char msg[512] = {0};

    if(m_fileTree.GetNumberOfFiles() == 0)
        cout << "No Files in file list";

    for(m_scriptRunIndex = 0; m_scriptRunIndex < m_fileTree.GetNumberOfFiles(); m_scriptRunIndex++)
    {
		if (_compile_result[m_scriptRunIndex] == NO_ERROR)
		{
			cout << "Running Script: " << m_fileTree.GetFile(m_scriptRunIndex)->GetFilename() << endl;
			m_fileTree.GetFile(m_scriptRunIndex)->doScript();
			m_fileTree.GetFile(m_scriptRunIndex)->PrintVariableList(true);
		}
        else
        {
            sprintf(msg, "Could Not Run Script: %s | %s\n", m_fileTree.GetFile(m_scriptRunIndex)->GetFilename(),
                    GetErrorText(_compile_result[m_scriptRunIndex]));
            debug.Log(msg, true);
        }
    }

    return true;
}

void CInterpreter::RunScript(char* filename)
{
    for(int i = 0; i < m_fileTree.GetNumberOfFiles(); i++)
    {
        if(!strcmp(filename, m_fileTree.GetFile(i)->GetFilename()))
        {
			if (!_compile_result)
			{
				cout << "Please Compile Script before running them...\n";
				return;
			}
            if(_compile_result[i] == NO_ERROR)
            {
                m_scriptRunIndex = i;
                m_fileTree.GetFile(i)->doScript();
            }
            else
            {
                cout << "Compiling this script failed... Unable to run\n";
            }
        }
    }
}

CScriptFile* CInterpreter::GetRunningScript()
{
    return m_fileTree.GetFile(m_scriptRunIndex);
}

CScriptFile* CInterpreter::GetCompiledScript(char* scriptFilename)
{
    return m_fileTree.GetFile(scriptFilename);
}