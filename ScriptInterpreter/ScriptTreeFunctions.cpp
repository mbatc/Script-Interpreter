#include "ScriptTreeFunctions.h"
#include "OperatorFunctions.h"
#include "String.h"
#include "main.h"
#include "CInterpreter.h"

#include <stdio.h>


unsigned int S_FUNC::ADD(int& scope, CScriptVariable** data)
{
    char msg[512] = {0};
    if(!data[0] || !data[1] || !data[2])
        return ERROR_INVALID_VALUE;
    data[0]->OperatorAssign(data[1]);

    sprintf(msg, "ADD : %s : %s : %s |\n",data[0]->GetName(),
            data[1]->GetName(),
            data[2]->GetName());
    debug.Log(msg);

    return data[0]->OperatorAdd(data[2]);
}
unsigned int S_FUNC::SUB(int& scope, CScriptVariable** data)
{
    char msg[512] = {0};
    if(!data[0] || !data[1] || !data[2])
        return ERROR_INVALID_VALUE;
    data[0]->OperatorAssign(data[1]);

    sprintf(msg, "SUB : %s : %s : %s |\n",data[0]->GetName(),
            data[1]->GetName(),
            data[2]->GetName());
    debug.Log(msg);
    return data[0]->OperatorSubtract(data[2]);
}
unsigned int S_FUNC::MUL(int& scope, CScriptVariable** data)
{
    char msg[512] = {0};
    if(!data[0] || !data[1] || !data[2])
        return ERROR_INVALID_VALUE;
    data[0]->OperatorAssign(data[1]);

    sprintf(msg, "MUL : %s : %s : %s |\n",data[0]->GetName(),
            data[1]->GetName(),
            data[2]->GetName());
    debug.Log(msg);
    return data[0]->OperatorMultiply(data[2]);
}
unsigned int S_FUNC::DIV(int& scope, CScriptVariable** data)
{
    char msg[512] = {0};
    if(!data[0] || !data[1] || !data[2])
        return ERROR_INVALID_VALUE;
    data[0]->OperatorAssign(data[1]);

    sprintf(msg, "DIV : %s : %s : %s |\n",data[0]->GetName(),
            data[1]->GetName(),
            data[2]->GetName());
    debug.Log(msg);
    return data[0]->OperatorDivide(data[2]);
}
unsigned int S_FUNC::ASSIGN(int& scope, CScriptVariable** data)
{
    char msg[512] = {0};
    if(!data[0] || !data[1])
        return ERROR_INVALID_VALUE;
    sprintf(msg, "ASSIGN : %s : %s |\n", data[0]->GetName(),
            data[1]->GetName());
    debug.Log(msg);
    return data[0]->OperatorAssign(data[1]);
}

unsigned int S_FUNC::EQUALS(int& scope, CScriptVariable** data)
{
    char msg[512] = {0};
    if(!data[0] || !data[1])
        return ERROR_INVALID_VALUE;
    sprintf(msg, "EQUALS : %s : %s |\n", data[0]->GetName(),
            data[1]->GetName());
    debug.Log(msg);

    bool result;
    unsigned int ret = SCRIPT::LOGIC::equals(result, data[1]->GetData(), data[1]->GetType(),
                            data[2]->GetData(), data[2]->GetType());
    data[0]->SetData(&result);
    return ret;
}

unsigned int S_FUNC::LESSTHAN(int& scope, CScriptVariable** data)
{
    char msg[512] = {0};
    if(!data[0] || !data[1])
        return ERROR_INVALID_VALUE;
    sprintf(msg, "LESSTHAN : %s : %s |\n", data[0]->GetName(),
            data[1]->GetName());
    debug.Log(msg);

    bool result;
    unsigned int ret = SCRIPT::LOGIC::lessThan(result, data[1]->GetData(), data[1]->GetType(),
                            data[2]->GetData(), data[2]->GetType());
    data[0]->SetData(&result);
    return ret;
}

unsigned int S_FUNC::MORETHAN(int& scope, CScriptVariable** data)
{
    char msg[512] = {0};
    if(!data[0] || !data[1])
        return ERROR_INVALID_VALUE;
    sprintf(msg, "MORETHAN : %s : %s |\n", data[0]->GetName(),
            data[1]->GetName());
    debug.Log(msg);

    bool result;
    unsigned int ret = SCRIPT::LOGIC::moreThan(result, data[1]->GetData(), data[1]->GetType(),
                            data[2]->GetData(), data[2]->GetType());
    data[0]->SetData(&result);
    return ret;
}

unsigned int S_FUNC::MORETHAN_EQUALS(int& scope, CScriptVariable** data)
{
    char msg[512] = {0};
    if(!data[0] || !data[1])
        return ERROR_INVALID_VALUE;
    sprintf(msg, "MORETHAN_EQUALS : %s : %s |\n", data[0]->GetName(),
            data[1]->GetName());
    debug.Log(msg);

    bool result_final = false;
    bool result_1;
    bool result_2;
    unsigned int ret = SCRIPT::LOGIC::moreThan(result_1,data[1]->GetData(), data[1]->GetType(),
                            data[2]->GetData(), data[2]->GetType());
    if(ret != NO_ERROR)
        return ret;

    ret = SCRIPT::LOGIC::equals(result_2, data[1]->GetData(), data[1]->GetType(),
                            data[2]->GetData(), data[2]->GetType());

    if(ret != NO_ERROR)
        return ret;
    if(result_1 || result_2)
        result_final = true;

    data[0]->SetData(&result_final);
    return NO_ERROR;
}

unsigned int S_FUNC::LESSTHAN_EQUALS(int& scope, CScriptVariable** data)
{
    char msg[512] = {0};
    if(!data[0] || !data[1])
        return ERROR_INVALID_VALUE;
    sprintf(msg, "LESSTHAN_EQUALS : %s : %s |\n", data[0]->GetName(),
            data[1]->GetName());
    debug.Log(msg);

    bool result_final = false;
    bool result_1;
    bool result_2;
    unsigned int ret = SCRIPT::LOGIC::lessThan(result_1,data[1]->GetData(), data[1]->GetType(),
                            data[2]->GetData(), data[2]->GetType());
    if(ret != NO_ERROR)
        return ret;

    ret = SCRIPT::LOGIC::equals(result_2, data[1]->GetName(), data[1]->GetType(),
                            data[2]->GetName(), data[2]->GetType());

    if(ret != NO_ERROR)
        return ret;
    if(result_1 || result_2)
        result_final = true;

    data[0]->SetData(&result_final);
    return NO_ERROR;
}

unsigned int S_FUNC::IF(int& scope, CScriptVariable** data)
{
    char msg[512] = {0};
    if(!data[0])
        return ERROR_INVALID_VALUE;
    sprintf(msg, "IF : %s |\n", data[0]->GetName());
    debug.Log(msg);

    if(*(bool*)data[0]->GetData() == true)
        return NO_ERROR;

    scope--;
    return NO_ERROR;
}

unsigned int S_FUNC::OUTPUT(int& scope, CScriptVariable** data)
{
    if(!data[0] || !data[1])
        return ERROR_INVALID_VALUE;

    char msg[512] = {0};
    sprintf(msg, "OUTPUT : %s : %s |\n", data[0]->GetName(),
            data[1]->GetName());
    debug.Log(msg);

    switch(data[0]->GetType())
    {
    case BOOL:
        sprintf(msg,"%s\n", *(bool*)data[0]->GetData() ? "true" : "false");
        break;
    case FLOAT:
        sprintf(msg,"%f\n", *(float*)data[0]->GetData());
        break;
    case INT:
        sprintf(msg,"%d\n", *(int*)data[0]->GetData());
        break;
    case STR:
        debugScript.Log((*(String*)data[0]->GetData()).GetString());
        debugScript.Log("\n");
        return NO_ERROR;
    default:
        return ERROR_UNDEFINED_DATA_TYPE;
    }

    debugScript.Log(msg);
    return NO_ERROR;
}


unsigned int S_FUNC::ENGINE::GETCOMPONENT(int& scope, CScriptVariable** data)
{
    if(!data[0])
        return ERROR_INVALID_VALUE;
    if(data[0]->GetType() != STR)
        return ERROR_INVALID_DATA_TYPE;

    char msg[512] = {0};
    sprintf(msg, "GETCOMPONENT : %s : %s |\n", data[0]->GetName(),
            data[1]->GetName());
    debug.Log(msg);
    //Probably Get Parsed tokens after this call as strings.
    //Steps to take
        //Find Component
        //Call function
        //Get Variables Needed
        //Parse Variables To Function
    debug.Log("GetComponent() has not been implemented yet\n");

    return NO_ERROR;
}
unsigned int S_FUNC::ENGINE::SAVETOFILE(int& scope, CScriptVariable** data)
{
    //INDEX INFO
    //0 == File Name
    //1 == Variable to save
    //2 == Return Value
    if(!data[0] || !data[1] || !data[2])
        return ERROR_INVALID_VALUE;

    if(data[1]->GetType() != STR)
        return ERROR_INVALID_DATA_TYPE;

    char msg[512] = {0};
    sprintf(msg, "SAVETOFILE : %s : %s |\n", data[0]->GetName(),
            data[1]->GetName());
    debug.Log(msg);

    varLoader.SaveToFile(data[0],(*(String*)data[1]->GetData()).GetString());
    return NO_ERROR;
}
unsigned int S_FUNC::ENGINE::READFROMFILE(int& scope, CScriptVariable** data)
{
    //INDEX INFO
    //0 == File Name
    //1 == Name of variable to load
    //2 == Return Value

    if(!data[0] || !data[1] || !data[2])
        return ERROR_INVALID_VALUE;

    if(data[0]->GetType() != STR)
        return ERROR_INVALID_DATA_TYPE;
    if(data[1]->GetType() != STR)
        return ERROR_INVALID_DATA_TYPE;

    char msg[512] = {0};
    sprintf(msg, "READFROMFILE : %s : %s |\n", data[0]->GetName(),
            data[1]->GetName());
    debug.Log(msg);

    varLoader.LoadFromFile(data[2],
                           (*(String*)data[1]->GetData()).GetString(),
                           (*(String*)data[0]->GetData()).GetString());
    return NO_ERROR;
}

unsigned int S_FUNC::ENGINE::GETSCRIPTVAR(int& scope, CScriptVariable** data)
{
    //INDEX INFO
    //0 = Script Name
    //1 = Script Variable Name
    //2 = Returned Variable Value

    if(!data[0] || !data[1] || !data[2])
        return ERROR_INVALID_VALUE;

    if(data[0]->GetType() != STR)
        return ERROR_INVALID_DATA_TYPE;
    if(data[1]->GetType() != STR)
        return ERROR_INVALID_DATA_TYPE;

    char msg[512] = {0};
    sprintf(msg, "GETSCRIPTVAR : %s : %s : %s|\n", data[0]->GetName(),
            data[1]->GetName(), data[2]->GetName());

    debug.Log(msg);

    char* file = ((String*)data[0]->GetData())->GetString();
    char* name = ((String*)data[1]->GetData())->GetString();

    CScriptFile* script = pInterpreter->GetCompiledScript(file);
    data[2]->OperatorAssign(script->m_varList.GetVariable(name));

    return NO_ERROR;
}

unsigned int S_FUNC::FOR(int& index, CScriptVariable** data)
{
    char msg[512] = {0};
    debug.Log("FOR LOOP : NO DATA REQUIRE | \n\n");
    debug.Log("  __                   __\n");
    debug.Log("//  MARKS START OF LOOP  \\\\\n\n");
    return NO_ERROR;
}

unsigned int S_FUNC::FOR_END(int& index, CScriptVariable** data)
{
    debug.Log("FOR LOOP END : NO DATA REQUIRED |\n");
    debug.Log("\\\\__MARKS END OF LOOP__//\n\n");
    return NO_ERROR;
}

unsigned int S_FUNC::INITIALIZE_VAR(int& scope, CScriptVariable** data)
{
    char msg[512] = {0};
    sprintf(msg, "INIT_VAR : %s : %s ",
            data[0]->GetName(),
            data[1]->GetName());
    debug.Log(msg);

    String type = (*(String*)data[0]->GetData());
    String name = (*(String*)data[1]->GetData());

    CScriptVariable* newVar = 0;

    if(!strcmp(type.GetString(), "bool"))
    {
        newVar = new CScriptVariable(BOOL, 0, scope, name.GetString());

    }
    if(!strcmp(type.GetString(), "int"))
    {
        newVar = new CScriptVariable(INT, 0, scope, name.GetString());

    }
    if(!strcmp(type.GetString(), "float"))
    {
        newVar = new CScriptVariable(FLOAT, 0, scope, name.GetString());
    }
    if(!strcmp(type.GetString(), "string"))
    {
        newVar = new CScriptVariable(STR, 0, scope, name.GetString());
    }
    if(!newVar)
        return ERROR_UNDEFINED_DATA_TYPE;

    return pInterpreter->GetRunningScript()->m_varList.AddVariable(newVar);
}
