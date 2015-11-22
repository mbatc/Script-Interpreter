#include <iostream>
#include "CSystem.h"
#include "main.h"

using namespace std;

CDebugLog debug;
CDebugLog debugScript;
CScriptVariableLoader varLoader;
CInterpreter* pInterpreter;

int main()
{
    cout << "Interpreter Test Project!\n\n";

    CSystem _system;
    return _system.Run();
}
