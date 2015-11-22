#pragma once

#include "CScriptFile.h"
#include "CScriptVariable.h"
#include "CScriptFunctionTree.h"
#include "CScriptVariableList.h"
#include "CScanner.h"
#include "CInterpreter.h"
#include "ScriptLanguageDefinition.h"
#include "CDebugLog.h"

#define _IN_SETTINGS "SETTING"
#define _IN_COMPILE "COMPILE"
#define _IN_RUN "RUN"
#define _IN_PRINT "PRINT"
#define _IN_EXIT "EXIT"

class CSystem
{
    class CSystemSettings
    {
        friend CSystem;
    public:
        CSystemSettings(CSystem& system);
        ~CSystemSettings();

        void ProcessSetting(char* cmdLine);
    private:
        char** SplitCmdLine(char* cmdLine);

        bool _compile_and_run;
        CSystem& m_system;
    };


public:
    CSystem();
    ~CSystem();

    int Run();
private:
    bool RunMain();
    void RunSettings();
    void RunCompile(char* arg);
    void RunScript(char* arg);
    void RunPrint(char* arg);

    void OutputScript();
    void OutputScriptErrors();
    void OutputScriptVars();
    void OutputHelp();

    char CMDGetChar();
    void CMDGetLine(char* buffer, int bufLen);


    char** SplitCmdLine(char* cmdLine);

    CInterpreter    m_interpreter;
    CSystemSettings m_system_settings;
};
