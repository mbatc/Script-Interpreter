#include "CScriptVariableLoader.h"
#include "MemoryHelper.h"
#include "main.h"

#include <string>
#include <stdio.h>

CScriptVariableLoader::CScriptVariableLoader()
:
    m_pFile(0)
{}

CScriptVariableLoader::~CScriptVariableLoader()
{}

void CScriptVariableLoader::LoadFromFile(CScriptVariable*& var, char* pVarName, char* filename)
{
    if(!filename)
        return;
    if(!pVarName)
        return;
    m_pFile = fopen(filename, "r");
    if(!m_pFile)
    {
        debug.Log("Could Not Open File: ");
        debug.Log(filename);
        debug.Log("\n");
        return;
    }

    do
    {
        char msg[512] = {0};
        if(!feof(m_pFile))
        {
            fscanf(m_pFile, "%s", msg);
            if(msg[0] == '!')
            {
                fscanf(m_pFile, "%s", msg);
                if(!strcmp(msg, pVarName))
                {
                    char type[64];
                    fscanf(m_pFile, "%s", type);
                    if(!strcmp(type,"BOOL"))
                    {
                        bool b;
                        fscanf(m_pFile, "%B", &b);
                        if(var->GetType() != BOOL)
                            return;
                        var->SetData(&b);

                    }
                    else if(!strcmp(type, "STRING"))
                    {
                        char c = '\0';
                        char* buffer = NULL;
                        int bufLen = 0;
                        String s;
                        if(var->GetType() != STR)
                            return;

                        bool inString = false;
                        do
                        {
                            if(c == '"')
                                inString = true;
                            fread(&c, sizeof(char), 1, m_pFile);
                            if(c != '"' && inString == true)
                            {
                                MEMORY::AddToList(buffer, c,bufLen);
                            }

                        }while(c != '"' || inString == false);
                        MEMORY::AddToList(buffer, '\0', bufLen);
                        s.SetString(buffer);
                        var->SetData(&s);
                    }
                    else if(!strcmp(type, "FLOAT"))
                    {
                        float f;
                        fscanf(m_pFile, "%f", &f);
                        if(var->GetType() != FLOAT)
                            return;
                        var->SetData(&f);
                    }
                    else if(!strcmp(type, "INT"))
                    {
                        int i;
                        fscanf(m_pFile, "%i", &i);
                        if(var->GetType() != INT)
                            return;

                        var->SetData(&i);
                    }
                    else
                    {
                        var = 0;
                    }
                }
            }
        }
    }while(!feof(m_pFile));

    fclose(m_pFile);
}

void CScriptVariableLoader::SaveToFile(CScriptVariable* var, char* filename)
{
    if(!filename)
        return;

    m_pFile = fopen(filename, "r+");
    if(!m_pFile)
    {
        m_pFile = fopen(filename, "w+");
        if(!m_pFile)
        {
            char msg[512] = {0};
            sprintf(msg,"Could Not Open File: %s\n", filename);
            debug.Log(msg);
            return;
        }
    }


    int _filelen = 0;
    do
    {
        char c;
        fread(&c, sizeof(char),1, m_pFile);
        if(!feof(m_pFile))
            _filelen++;

    }while(!feof(m_pFile));

    char* buffer = new char[_filelen + 2];
    memset(buffer, '\0', _filelen + 1);
    rewind(m_pFile);
    fread(buffer,sizeof(char), _filelen, m_pFile);

    fclose(m_pFile);

    char* strLoc = strstr(buffer, var->GetName());
    char* fileBuffer = NULL;
    if(strLoc)
    {
        int dataIndex = 0;
        int scanIndex = 0;
        bool whiteSpace = false;
        do
        {
            dataIndex++;
            if(strLoc[dataIndex] == ' ')
            {
                if(!whiteSpace)
                    scanIndex++;

                whiteSpace = true;
            }
            else
            {
                if(scanIndex == 2)
                    break;
                whiteSpace = false;
            }
        }while(true);

        int start_index = dataIndex;
        int end_index = start_index;

        if(var->GetType() != STR)
        {
            for(; strLoc[end_index] != ' ' &&
                strLoc[end_index] != '\n' &&
                strLoc[end_index] != '\0';
                end_index++);
        }
        else
        {
            for(; strLoc[end_index] != '"' ||
                end_index == start_index; end_index++);
        }

        strLoc[start_index] = '\0';
        if(var->GetType() == STR)
            fileBuffer = new char[_filelen + strlen((*(String*)var->GetData()).GetString())];
        else
            fileBuffer = new char[_filelen + 50];

        switch(var->GetType())
        {
        case STR:
            sprintf(fileBuffer, "%s\"%s%s",
                    buffer,
                    (*(String*)var->GetData()).GetString(),
                    &strLoc[end_index]);
            break;
        case INT:
            sprintf(fileBuffer, "%s%d%s",
                    buffer,
                    (*(int*)var->GetData()),
                    &strLoc[end_index]);
            break;
        case FLOAT:
            sprintf(fileBuffer, "%s%f%s",
                    buffer,
                    (*(float*)var->GetData()),
                    &strLoc[end_index]);
            break;
        case BOOL:
            sprintf(fileBuffer, "%s%B%s",
                    buffer,
                    (*(bool*)var->GetData()),
                    &strLoc[end_index]);
            break;
        }
    }
    else
    {
        if(var->GetType() != STR)
            fileBuffer = new char[_filelen + 14 + strlen(var->GetName()) + 50];

        switch(var->GetType())
        {
        case BOOL:
            sprintf(fileBuffer, "%s\n! %s BOOL %B",buffer, var->GetName(), *(bool*)var->GetData());
            break;
        case INT:
            sprintf(fileBuffer, "%s\n! %s INT %d",buffer, var->GetName(),*(int*)var->GetData());
            break;
        case FLOAT:
            sprintf(fileBuffer, "%s\n! %s FLOAT %f",buffer, var->GetName(),*(float*)var->GetData());
            break;
        case STR:
            MEMORY::SafeDeleteArr(fileBuffer);
            fileBuffer = new char[_filelen + 14 + strlen(var->GetName()) +
                strlen((*(String*)var->GetData()).GetString())];
            sprintf(fileBuffer, "%s\n! %s STRING \"%s\"\n",buffer, var->GetName(), (*(String*)var->GetData()).GetString());
            break;
        }
    }

    m_pFile = fopen(filename,"w");
    fprintf(m_pFile,"%s",fileBuffer);
    fclose(m_pFile);
}
