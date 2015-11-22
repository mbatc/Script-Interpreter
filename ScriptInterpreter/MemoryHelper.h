#pragma once

#include "ErrorDefinitions.h"
#include "DataTypeDefinitions.h"
#include "String.h"

#include <string.h>

namespace MEMORY
{
    template <class T> void SafeDelete(T* in)
    {
        if(in == 0)
            return;

        delete in;
        in = 0;
    }
    template <class T> void SafeDeleteArr(T*& in)
    {
        if(in == 0)
            return;

        delete[] in;
        in = 0;
    }
    template <class T>void AddToList(T*& List, T item, int& n)
    {
        T* temp = new T[n + 1];
        for(int i = 0; i < n; i++)
        {
            temp[i] = List[i];
        }
        temp[n] = item;

        SafeDeleteArr(List);
        n++;
        List = temp;
    }
    namespace SCRIPT
    {
        template <class T> unsigned int SafeAlloc(T*& in,const unsigned int type )
        {
            switch(type)
            {
            case BOOL:
                MEMORY::SafeDelete((bool*)in);
                in = 0;
                in = (T*) new bool;
                if(in == 0)
                    return ERROR_UNDEFINED_ERROR;

                return NO_ERROR;
            case FLOAT:
                MEMORY::SafeDelete((float*)in);
                in = 0;
                in = (T*) new float;
                if(in == 0)
                    return ERROR_UNDEFINED_ERROR;

                return NO_ERROR;
            case INT:
                MEMORY::SafeDelete((int*)in);
                in = 0;
                in = (T*) new int;
                if(in == 0)
                    return ERROR_UNDEFINED_ERROR;

                return NO_ERROR;
            case STR:
                MEMORY::SafeDelete((String*)in);
                in = 0;
                in = (T*) new String;
                if(in == 0)
                    return ERROR_UNDEFINED_ERROR;

                return NO_ERROR;
            default:
                return ERROR_UNDEFINED_DATA_TYPE;
            }
        }
    }
}
namespace STRING
{
    void Copy(char*& out, const char* in);
}
