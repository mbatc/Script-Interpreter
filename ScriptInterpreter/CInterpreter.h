#pragma once
#include "CScanner.h"
#include "CLexer.h"
#include "CFileTree.h"
#include "CParser.h"

class CInterpreter
{
public:
    CInterpreter();
    ~CInterpreter();

    void SetFileTree(CFileTree fileTree);

    unsigned int CompileFileList();

    CScriptFile* GetCompiledScript(char* scriptFilename);
    unsigned int CompileFile(CScriptFile* file);

    bool         RunCompiledScripts();
    void         RunScript(char* filename);
    CScriptFile* GetRunningScript();

    CFileTree& GetFileTree() {return m_fileTree;}
	unsigned int* GetScriptError() { return _compile_result; }
private:

    int m_scriptRunIndex;

    bool _compile_done;
    unsigned int* _compile_result;

    CFileTree m_fileTree;

    CScanner m_scanner;
    CLexer m_lexer;
    CParser m_parser;
};
