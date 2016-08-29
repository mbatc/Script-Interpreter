#include "CSystem.h"
#include "main.h"

CSystem::CSystem()
:
    m_system_settings(*this)
{
    cout << "COMPILER DEBUG LOG - \"Compiler Logs\\LOG - DATE.txt\"\n";
    debug.SetLogFile("Compiler Logs\\LOG - ");
    cout << "SCRIPT OUTPUT LOG - \"Script Output\\LOG - DATE.txt\"\n";
    debugScript.SetLogFile("Script Output\\OUTPUT -");

    pInterpreter = &m_interpreter;
}

CSystem::~CSystem()
{}

int CSystem::Run()
{
    RunMain();
    return 0;
}

bool CSystem::RunMain()
{
    cout << "Main Menu - \n";
    cout << "   "<<_IN_SETTINGS<<" - Goto the settings menu\n";
    cout << "   "<<_IN_COMPILE<<" - Compile/Recompile the files in the list\n";
    cout << "   "<<_IN_RUN<<" - Runs the compiled scripts (must compile first)\n";
    cout << "   "<<_IN_PRINT<<" - Print information (PRINT:HELP for more info)\n";
	cout << "   "<<_IN_EXIT<< " - Exit the application\n";

	char** args = new char*[2];
    do
    {
		cout << endl;
        char buffer[512];
        CMDGetLine(buffer, 512);
		args[1] = SplitCmdLine(buffer)[1];
		args[0] = buffer;

        if(args[1] == 0)
        {
			if (!strcmp(buffer, _IN_SETTINGS))
				RunSettings();
			else if (!strcmp(args[0], _IN_EXIT))
				break;
            else
                cout << "Invalid Input - Please check spelling and spacing\n";

            continue;
        }

        if(!strcmp(args[0],_IN_PRINT))
            RunPrint(args[1]);
        else if(!strcmp(args[0],_IN_COMPILE))
            RunCompile(args[1]);
        else if(!strcmp(args[0],_IN_RUN))
            RunScript(args[1]);
        else
            cout << "Invalid Input - Please check spelling and spacing\n";

    }while(true);

	MEMORY::SafeDeleteArr(args);
    return false;
}

void CSystem::RunSettings()
{
    cout << "   Settings Menu - \n";
    cout << "       ADDFILE - Add a file to the file tree\n";
    cout << "       REMOVEFILE - Remove a file from the list\n";
    cout << "       COMPILE_RUN - Compile the file then run it\n";
    cout << "       EXIT - Return to the main menu\n";
    cout << "       e.g. COMPILE_RUN:TRUE\n";

    do
    {
        char buf[512] = {0};
        CMDGetLine(buf, 512);

        if(!strcmp(buf,"EXIT"))
            break;

        m_system_settings.ProcessSetting(buf);
    }while(true);
}

void CSystem::RunCompile(char* arg)
{
    if(!strcmp(arg, "ALL"))
    {
		for (int i = 0; i < m_interpreter.GetFileTree().GetNumberOfFiles(); i++)
		{
			CScriptFile* file = m_interpreter.GetFileTree().GetFile(i);
			cout << "Compiling file: " << file->GetFilename() << endl;
			unsigned int result = m_interpreter.CompileFile(file);
			if (result != NO_ERROR)
				cout << "Compiled with error: " << GetErrorText(result) << endl;
			else
				cout << "Compiled with successfully!\n";

			if (m_system_settings._compile_and_run)
			{
				RunScript("ALL");
			}
		}
    }
    else
    {
        CScriptFile* file = m_interpreter.GetFileTree().GetFile(arg);
		if (file)
		{
			cout << "Compiling file: " << file->GetFilename() << endl;
			unsigned int result = m_interpreter.CompileFile(file);
			if (result != NO_ERROR)
				cout << "Compiled with error: " << GetErrorText(result) << endl;
			else
				cout << "Compiled with successfully!\n";
		}
        else
            cout << "Invalid Argument - Please check spelling and spaces\n";


		if (m_system_settings._compile_and_run)
		{
			RunScript(file->GetFilename());
		}

    }
}

void CSystem::RunPrint(char* arg)
{
    if(!strcmp(arg,"SCRIPT_LIST"))
    {
        OutputScript();
    }
    else if(!strcmp(arg, "HELP"))
    {
        OutputHelp();
    }
    else if (!strcmp(arg, "SCRIPT_VAR"))
    {
        OutputScriptVars();
    }
    else if (!strcmp(arg, "COMPILE_RESULT"))
    {
        OutputScriptErrors();
    }
}

void CSystem::RunScript(char* arg)
{
    if(!strcmp(arg,"ALL"))
    {
        m_interpreter.RunCompiledScripts();
    }
    else
    {
        CScriptFile* file = m_interpreter.GetFileTree().GetFile(arg);
		if (file)
		{
			m_interpreter.RunScript(arg);
			file->PrintVariableList(true);
		}
        else
            cout << "Invalid Argument - Please check spelling and spaces";
    }
}

void CSystem::OutputScript()
{
    cout << "Files List - \n";
    for(int i =0 ; i < m_interpreter.GetFileTree().GetNumberOfFiles(); i++)
    {
        CScriptFile* file = m_interpreter.GetFileTree().GetFile(i);
        cout <<"\t"<< file->GetFilename() << endl;
    }
}

void CSystem::OutputScriptErrors()
{
	cout << "SCRIPT COMPILE RESULTS\n";
	for (int i = 0; i < m_interpreter.GetFileTree().GetNumberOfFiles(); i++)
	{
		if (m_interpreter.GetScriptError())
		{
			cout << m_interpreter.GetFileTree().GetFile(i)->GetFilename() << ": ";
			cout << GetErrorText(m_interpreter.GetScriptError()[i]) << endl;
		}
		else
		{
			cout << m_interpreter.GetFileTree().GetFile(i)->GetFilename() << ": ";
			cout << "Please compile at least once.\n";
		}
	}

	if (m_interpreter.GetFileTree().GetNumberOfFiles() == 0)
	{
		cout << "No files have been added. To Add files go to SETTINGS.\n";
	}

	cout << endl;
}

void CSystem::OutputScriptVars()
{
    cout << "\t-This is not supported yet...\n";
}

void CSystem::OutputHelp()
{
	cout << "MENU COMMANDS - \n";
	cout << "\tSETTING - Go to the settings menu\n";
	cout << "\tCOMPILE - Call compile commands\n";
	cout << "\t\tALL - Compile all the files in the file list\n";
	cout << "\t\t'Filename' - Compiles the specified file\n";
	cout << "\tRUN - Run a compiled script\n";
	cout << "\t\tALL - Run all the scripts in the file list\n";
	cout << "\t\t'Filename' - Runs the specified script\n";
	cout << "\tPRINT - Prints information to the console\n";
	cout << "\t\tHELP - Prints help(this) to the console\n";
	cout << "\t\tSCRIPT_LIST - Prints a list of the scripts to be compiled\n";
	cout << "\t\tSCRIPT_VAR - Prints the variable list for each file\n";
	cout << "\t\tCOMPILE_RESULT - Print the compiling results for each file\n";

	cout << "SETTINGS COMMANDS - \n";
	cout << "\
\tCOMPILE_RUN - Can be true or false. Sets whether scripts are run \n\
\t              directly after being compiled\n";
	cout << "\tADDFILE - Adds the specified file to the file list\n";
	cout << "\tREMOVEFILE - Removes the specified file from the list\n";
}

char CSystem::CMDGetChar()
{
    char ret;
    ret = getchar();
    do
    {
        if(getchar() == '\n')
            break;
    }while(true);

    return ret;
}

void CSystem::CMDGetLine(char* buffer, int bufLen)
{
    for(int i = 0;i < bufLen; i++)
    {
        buffer[i] = getchar();
        if(buffer[i] == '\n')
        {
            buffer[i] = '\0';
            break;
        }
    }
}

char** CSystem::SplitCmdLine(char* cmdLine)
{
    char* ret[2] = {0};
    ret[0] = cmdLine;
    int cmdLen = strlen(cmdLine);
    for(int i = 0; i < cmdLen + 1; i++)
    {
        if(cmdLine[i] == ':')
        {
            cmdLine[i] = '\0';
            ret[1] = &cmdLine[i + 1];
            break;
        }
    }

    return ret;
}

CSystem::CSystemSettings::CSystemSettings(CSystem& system)
:
    m_system(system)
{}

CSystem::CSystemSettings::~CSystemSettings()
{}

void CSystem::CSystemSettings::ProcessSetting(char* cmdLine)
{
	char** args = new char*[2];
	args[1] = SplitCmdLine(cmdLine)[1];
	args[0] = cmdLine;


    if(!args[1])
    {
        cout << "Please give an argument e.g. SETTING:ARGUMENT\n";
        return;
    }

    if(!strcmp(args[0], "ADDFILE"))
    {
        CScriptFile file;
        file.SetFile(args[1]);
        m_system.m_interpreter.GetFileTree().AddFileToList(file);
    }
    else if(!strcmp(args[0], "REMOVEFILE"))
    {
        cout << "Can't remove files yet\n";
    }
    else if(!strcmp(args[0], "COMPILE_RUN"))
    {
        if(!strcmp(args[1], "TRUE"))
        {
            _compile_and_run = true;
            cout << "Compile and Run set to True\n";
        }
        else if(!strcmp(args[1], "FALSE"))
        {
            _compile_and_run = false;
            cout << "Compile and Run set to False\n";
        }
        else
            cout << "Invalid Setting - Please select TRUE or FALSE\n";
    }
    else
        cout << "Invalid Setting - Please check spelling and spaces\n";

	MEMORY::SafeDeleteArr(args);
}


char** CSystem::CSystemSettings::SplitCmdLine(char* cmdLine)
{
    char* ret[2] = {0};
    ret[0] = cmdLine;
    int cmdLen = strlen(cmdLine);
    for(int i = 0; i < cmdLen; i++)
    {
        if(cmdLine[i] == ':')
        {
            cmdLine[i] = '\0';
            ret[1] = &cmdLine[i + 1];
            break;
        }
    }

    return ret;
}
